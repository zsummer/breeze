
#include "docker.h"
#include "dbService.h"
#include "userMgrService.h"
#include "userService.h"
#include "shellService.h"
#include "webService.h"
#include "monitorService.h"
#include "offlineService.h"
#include <ProtoUser.h>
#include <ProtoUserMgr.h>
#include <ProtoWebAgent.h>


Docker::Docker()
{

}

bool Docker::init(const std::string & config, DockerID idx)
{
    if (!ServerConfig::getRef().parse(config, idx))
    {
        LOGE("Docker::init error. parse config error. config path=" << config << ", docker ID = " << idx);
        return false;
    }
    if (idx == InvalidDockerID)
    {
        LOGE("Docker::init error. current docker id invalid. config path=" << config << ", docker ID = " << idx);
        return false;
    }
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::init error. current docker id not found in config file.. config path=" << config << ", docker ID = " << idx);
        return false;
    }
    LOGA("Docker::init  success. dockerID=" << idx);
    SessionManager::getRef().createTimer(1000, std::bind(&Docker::buildCluster, Docker::getPtr()));
    return true;
}

void sigInt(int sig)
{
    if (!Docker::getRef().isStopping())
    {
        SessionManager::getRef().post(std::bind(&Docker::stop, Docker::getPtr()));
    }
}

void Docker::forceStop()
{
    if (!_dockerStopping)
    {
        _dockerStopping = true;
        SessionManager::getRef().stopAccept();
        SessionManager::getRef().kickClientSession();
        SessionManager::getRef().kickClientSession();
        SessionManager::getRef().kickConnect();
        SessionManager::getRef().stop();
    }
}

void Docker::stop()
{
    LOGA("Docker::stop");
    Docker::getRef().onShutdown();
    ShutdownClusterServer notice;
    Docker::getRef().broadcastToDockers(notice, false);

    for (auto &second : _services)
    {
        if (second.first == ServiceClient || second.first == ServiceInvalid)
        {
            continue;
        }
        for (auto & svc : second.second)
        {
            if (!svc.second->isShell())
            {
                LOGD("unload service [" << svc.second->getServiceName() << "], cur DockerID=" << svc.second->getServiceDockerID());
                svc.second->setStatus(SS_UNLOADING);
                svc.second->onUnload();
            }
            else
            {
                UnloadServiceInDocker notice(svc.second->getServiceType(), svc.second->getServiceID());
                sendToDocker((ServiceType)svc.second->getServiceType(), svc.second->getServiceID(), notice);
            }
        }
    }
    LOGA("Docker::stop  broadcast all docker. ");
}

void Docker::destroyCluster()
{
    LOGA("Docker::destroyCluster. checking ....");

    bool safe =  true;
    for(auto &second : _services)
    {
        if (second.first == ServiceClient || second.first == ServiceInvalid)
        {
            continue;
        }
        for (auto & svc : second.second)
        {
            if (!svc.second->isShell() && (svc.second->getStatus() == SS_WORKING || svc.second->getStatus() == SS_UNLOADING))   //状态判断需要改  
            {
                safe = false;
            }
        }
    }
    if(safe)
    {
        LOGA("all services closed.");
        SessionManager::getRef().kickConnect();
        SessionManager::getRef().stop();
    }
    else
    {
        SessionManager::getRef().createTimer(1000, std::bind(&Docker::destroyCluster, this));
    }
}
bool Docker::run()
{
    SessionManager::getRef().run();
    LOGA("Docker::run exit!");
    return true;
}

bool Docker::isStopping()
{
    return _dockerStopping;
}

void Docker::onShutdown()
{
    if (!_dockerStopping)
    {
        _dockerStopping = true;
        if (_widelisten != InvalidAccepterID)
        {
            SessionManager::getRef().stopAccept(_widelisten);
            SessionManager::getRef().kickClientSession(_widelisten);
        }
        if (_weblisten != InvalidAccepterID)
        {
            SessionManager::getRef().stopAccept(_weblisten);
            SessionManager::getRef().kickClientSession(_weblisten);
        }
        destroyCluster();
    }
    return ;
}

bool Docker::startDockerListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::startDockerListen error. current docker id not found in config file." );
        return false;
    }
    const DockerConfig & docker = *founder;
    if (docker._serviceBindIP.empty() || docker._servicePort == 0)
    {
        LOGE("Docker::startDockerListen check config error. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort);
        return false;
    }
    AccepterID aID = SessionManager::getRef().addAccepter(docker._serviceBindIP, docker._servicePort);
    if (aID == InvalidAccepterID)
    {
        LOGE("Docker::startDockerListen addAccepter error. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(aID);
    options._whitelistIP = docker._whiteList;
    options._maxSessions = 1000;
    options._sessionOptions._sessionPulseInterval = 5000;
    options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
    {
        DockerPulse pulse;
        WriteStream ws(pulse.getProtoID());
        ws << pulse;
        session->send(ws.getStream(), ws.getStreamLen());
    };
    options._sessionOptions._onBlockDispatch = std::bind(&Docker::event_onServiceMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(aID))
    {
        LOGE("Docker::startDockerListen openAccepter error. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort);
        return false;
    }
    LOGA("Docker::startDockerListen openAccepter success. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort <<", aID=" << aID);
    return true;
}
bool Docker::startDockerConnect()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    for (const auto & docker : dockers)
    {
        SessionID cID = SessionManager::getRef().addConnecter(docker._serviceIP, docker._servicePort);
        if (cID == InvalidSessionID)
        {
            LOGE("Docker::startDockerConnect addConnecter error. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort);
            return false;
        }
        auto session = SessionManager::getRef().getTcpSession(cID);
        if (!session)
        {
            LOGE("Docker::startDockerConnect addConnecter error.  not found connect session. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort << ", cID=" << cID);
            return false;
        }
        auto &options = session->getOptions();
        options._onSessionLinked = std::bind(&Docker::event_onServiceLinked, this, _1);
        options._onSessionClosed = std::bind(&Docker::event_onServiceClosed, this, _1);
        options._onBlockDispatch = std::bind(&Docker::event_onServiceMessage, this, _1, _2, _3);
        options._reconnects = 50;
        options._connectPulseInterval = 5000;
        options._reconnectClean = false;
        options._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if (last != 0 && getNowTime() - (time_t)last > session->getOptions()._connectPulseInterval * 3)
            {
                LOGE("docker timeout . diff time=" << getNowTime() - (time_t)last << ", sessionID=" << session->getSessionID());
                session->close();
            }
        };

        if (!SessionManager::getRef().openConnecter(cID))
        {
            LOGE("Docker::startDockerConnect openConnecter error. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort << ", cID=" << cID);
            return false;
        }
        LOGA("Docker::startDockerConnect success. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort << ", cID=" << cID);
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_TRUST);
        session->setUserParam(UPARAM_REMOTE_DOCKERID, docker._dockerID);
        auto &ds = _dockerSession[docker._dockerID];
        ds.dokerID = docker._dockerID;
        ds.sessionID = cID;
    }

    for (ui16 i = ServiceInvalid; i <= ServiceMax; i++)
    {
        _services.insert(std::make_pair(i, std::unordered_map<ServiceID, ServicePtr >()));
    }
    const auto & stc = ServerConfig::getRef().getServiceTypeConfig();
    for (ui16 i = ServiceInvalid + 1; i < ServiceMulti; i++)
    {
        if (!createService(stc.at(i).front(), i, InvalidServiceID, ServiceTypeNames.at(i), InvalidDockerID, InvalidSessionID, stc.at(i).front() != ServerConfig::getRef().getDockerID(), true))
        {
            return false;
        }
    }
    return true;
}
bool Docker::startDockerWideListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::startDockerWideListen error. current docker id not found in config file.");
        return false;
    }
    const DockerConfig & docker = *founder;
    if (!docker._wideIP.empty() && docker._widePort != 0)
    {
        AccepterID aID = SessionManager::getRef().addAccepter("0.0.0.0", docker._widePort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Docker::startDockerWideListen addAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        //options._whitelistIP;// = docker._whiteList;
        options._maxSessions = 5000;
        options._sessionOptions._sessionPulseInterval = 40000;
        options._sessionOptions._onSessionPulse = std::bind(&Docker::event_onClientPulse, this, _1);
        options._sessionOptions._onSessionLinked = std::bind(&Docker::event_onClientLinked, this, _1);
        options._sessionOptions._onSessionClosed = std::bind(&Docker::event_onClientClosed, this, _1);
        options._sessionOptions._onBlockDispatch = std::bind(&Docker::event_onClientMessage, this, _1, _2, _3);
        if (!SessionManager::getRef().openAccepter(aID))
        {
            LOGE("Docker::startDockerWideListen openAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort);
            return false;
        }
        LOGA("Docker::startDockerWideListen openAccepter success. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort << ", listen aID=" << aID);
        _widelisten = aID;
    }
    return true;
}

bool Docker::startDockerWebListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc) {return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::startDockerWebListen error. current docker id not found in config file.");
        return false;
    }
    const DockerConfig & docker = *founder;
    if (!docker._webIP.empty() && docker._webPort != 0)
    {
        AccepterID aID = SessionManager::getRef().addAccepter("0.0.0.0", docker._webPort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Docker::startDockerWebListen addAccepter error. bind ip=0.0.0.0, show web ip=" << docker._webIP << ", bind port=" << docker._webPort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        options._sessionOptions._protoType = PT_HTTP;
        //options._whitelistIP;// = docker._whiteList;
        options._maxSessions = 200;
        options._sessionOptions._sessionPulseInterval = 10000; 
        options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if (getNowTime() - (time_t)last > session->getOptions()._sessionPulseInterval * 3)
            {
                LOGW("web client timeout diff time=" << getNowTime() - (time_t)last << ", sessionID=" << session->getSessionID());
                session->close();
            }
        };
        options._sessionOptions._onSessionLinked = [](TcpSessionPtr session)
        {
            session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
            LOGD("Docker::event_onWebLinked. SessionID=" << session->getSessionID()
                << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
        };
        options._sessionOptions._onSessionClosed = [](TcpSessionPtr session)
        {
            LOGD("Docker::event_onWebClosed. SessionID=" << session->getSessionID()
                << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
        };
        options._sessionOptions._onHTTPBlockDispatch = std::bind(&Docker::event_onWebClientRequestAPI, this, _1, _2, _3, _4, _5);
        if (!SessionManager::getRef().openAccepter(aID))
        {
            LOGE("Docker::startDockerWebListen openAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort);
            return false;
        }
        LOGA("Docker::startDockerWebListen openAccepter success. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort << ", listen aID=" << aID);
        _weblisten = aID;
    }

    return true;
}

bool Docker::start()
{
    return startDockerListen() && startDockerConnect() && startDockerWideListen() && startDockerWebListen();
}






void Docker::event_onServiceLinked(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_DOCKERID);
    auto founder = _dockerSession.find(ci);
    if (founder == _dockerSession.end())
    {
        LOGE("event_onServiceLinked error cID=" << session->getSessionID() << ", dockerID=" << ci);
        return;
    }
    LOGI("event_onServiceLinked cID=" << session->getSessionID() << ", dockerID=" << ci);
    founder->second.status = 1;
    for (auto & second : _services)
    {
        if (second.first == ServiceClient || second.first == ServiceUser || second.first == ServiceInvalid)
        {
            continue;
        }
        for (auto & svc : second.second )
        {
            if (!svc.second->isShell() && svc.second->getStatus() == SS_WORKING)
            {
                LoadServiceNotice notice(
                    svc.second->getServiceDockerID(),
                    svc.second->getServiceType(),
                    svc.second->getServiceID(),
                    svc.second->getServiceName(),
                    svc.second->getStatus(),
                    svc.second->getClientDockerID(), 
                    svc.second->getClientSessionID());
                Docker::getRef().sendToSession(session->getSessionID(), notice);
            }
        }
    }
    buildCluster();
}

void Docker::event_onServiceClosed(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_DOCKERID);
    auto founder = _dockerSession.find(ci);
    if (founder == _dockerSession.end())
    {
        LOGE("event_onServiceClosed error cID=" << session->getSessionID() << ", dockerID=" << ci);
        return;
    }
    LOGW("event_onServiceClosed cID=" << session->getSessionID() << ", dockerID=" << ci);
    founder->second.status = 0;
}

void Docker::destroyService(ui16 serviceType, ServiceID serviceID)
{
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        return;
    }
    auto fder = founder->second.find(serviceID);
    if (fder == founder->second.end())
    {
        return;
    }
    founder->second.erase(fder);
    return;
}

ServicePtr Docker::createService(DockerID serviceDockerID, ui16 serviceType, ServiceID serviceID, ServiceName serviceName, DockerID clientDockerID, SessionID clientSessionID, bool isShell, bool failExit)
{
    if (isShell)
    {
        LOGI("Docker::createServic self dockerID=" << ServerConfig::getRef().getDockerID() << ", serviceType=" << serviceType
            << ", serviceID=" << serviceID << ", serviceDockerID=" << serviceDockerID << ", clientDockerID=" << clientDockerID
            << ", clientSessionID=" << clientSessionID << ", isShell=" << isShell << ",faileExit=" << failExit);
    }
    else
    {
        LOGI("refresh Shell Service self dockerID=" << ServerConfig::getRef().getDockerID() << ", serviceType=" << serviceType
            << ", serviceID=" << serviceID << ", serviceDockerID=" << serviceDockerID << ", clientDockerID=" << clientDockerID
            << ", clientSessionID=" << clientSessionID << ", isShell=" << isShell << ",faileExit=" << failExit);
    }

    ServicePtr & service = _services[serviceType][serviceID];
    if (service && !service->isShell())
    {
        LOGE("Docker::createService error. service alread exist. serviceType=" << ServiceTypeNames.at(serviceType) << ", serviceID="
            << serviceID << ", serviceDockerID=" << serviceDockerID << ", clientDockerID=" << clientDockerID << ", clientSessionID=" << clientSessionID
            << ", isShell=" << isShell << ", failExit=" << failExit << zsummer::traceback());
        if (failExit)
        {
            goto goExit;
        }
        return nullptr;
    }
    if (isShell)
    {
        service = std::make_shared<ShellService>();
        service->setShell(isShell);
    }
    else if (serviceType == ServiceDictDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (serviceType == ServiceInfoDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (serviceType == ServiceLogDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (serviceType == ServiceUserMgr)
    {
        service = std::make_shared<UserMgrService>();
    }
    else if (serviceType == ServiceUser)
    {
        service = std::make_shared<UserService>();
    }
    else if (serviceType == ServiceWebAgent)
    {
        service = std::make_shared<WebService>();
    }
    else if (serviceType == ServiceOfflineMgr)
    {
        service = std::make_shared<OfflineService>();
    }
    else if (serviceType == ServiceMinitorMgr)
    {
        service = std::make_shared<MonitorService>();
    }
    else
    {
        LOGE("createService invalid service type " << serviceType);
        if (failExit)
        {
            goto goExit;
        }
        return nullptr;
    }

    service->setServiceDockerID(serviceDockerID);
    service->setServiceType(serviceType);
    service->setServiceID(serviceID);
    service->setServiceName(serviceName);
    service->setClientSessionID(clientSessionID);
    service->setClientDockerID(clientDockerID);
    service->setStatus(SS_CREATED);

    return service;
goExit:
    Docker::getRef().forceStop();
    return nullptr;
}

void Docker::buildCluster()
{
    SessionManager::getRef().createTimer(1000, std::bind(&Docker::buildCluster, Docker::getPtr()));
    if (!_dockerNetWorking)
    {
        for (auto & c : _dockerSession)
        {
            if (c.second.status == 0)
            {
                return;
            }
        }
        _dockerNetWorking = true;
        LOGA("docker net worked");
    }

    for (auto & second : _services)
    {
        for (auto service : second.second)
        {
            if (service.second && !service.second->isShell() && service.second->getServiceType() != ServiceUser 
                && (service.second->getStatus() == SS_INITING || service.second->getStatus() == SS_WORKING || service.second->getStatus() == SS_UNLOADING) )
            {
                service.second->onTick();
            }
        }
    }
    if (!_dockerServiceWorking)
    {
        for (ui16 i = ServiceInvalid+1; i != ServiceMulti; i++)
        {
            auto founder = _services.find(i);
            if (founder == _services.end())
            {
                LOGE("not found service id=" << i);
                continue;
            }
            for (auto service : founder->second)
            {
                if (!service.second)
                {
                    LOGE("local service nulptr ...");
                    Docker::getRef().forceStop();
                    return;
                }
                if (service.second->isShell() && service.second->getStatus() != SS_WORKING)
                {
                    LOGD("waiting shell service[" << service.second->getServiceType() << "] working.. ");
                    return;
                }
                if (!service.second->isShell() && service.second->getStatus() == SS_INITING)
                {
                    LOGD("waiting local service[" << service.second->getServiceType() << "] initing.. ");
                    return;
                }
                if (!service.second->isShell() && service.second->getStatus() == SS_CREATED)
                {
                    LOGI("local service [" << ServiceTypeNames.at(service.second->getServiceType()) << "] begin init. [" << service.second->getServiceID() << "] ...");
                    service.second->setStatus(SS_INITING);
                    bool ret = service.second->onLoad();
                    if (ret)
                    {
                        LOGD("local service [" << ServiceTypeNames.at(service.second->getServiceType()) << "] call onLoad success. [" << service.second->getServiceID() << "] ...");
                    }
                    else
                    {
                        LOGE("local service [" << ServiceTypeNames.at(service.second->getServiceType()) << "]  call onLoad error.[" << service.second->getServiceID() << "] ...");
                        Docker::getRef().forceStop();
                        return;
                    }
                    return;
                }
                if (service.second->getStatus() == SS_DESTROY || service.second->getStatus() == SS_UNLOADING)
                {
                    LOGE("local service [" << ServiceTypeNames.at(service.second->getServiceType()) << "]  init error.[" << service.second->getServiceID() << "] ...");
                    Docker::getRef().forceStop();
                    return;
                }
            }
        }
        LOGA("-----------------------------------------------");
        LOGA("all service inited .  docker begin working ....");
        LOGA("-----------------------------------------------");
        _dockerServiceWorking = true;

    }
   
}
void Docker::event_onForwardToService(TcpSessionPtr session, ReadStream & rs)
{
    Tracing trace;
    rs >> trace;
    LOGT("event_onForwardToService " << trace << ", ReadStream len = " << rs.getStreamLen() << ", unread len=" << rs.getStreamUnreadLen());
    toService(trace, rs.getStreamUnread(), rs.getStreamUnreadLen(), false, false);
}

void Docker::event_onForwardToRealClient(TcpSessionPtr session, ReadStream & rs)
{
    SessionID sID;
    rs >> sID;
    LOGT("event_onForwardToRealClient sessionID=" << sID << ", ReadStream len = " << rs.getStreamLen() << ", unread len=" << rs.getStreamUnreadLen());
    SessionManager::getRef().sendSessionData(sID, rs.getStreamUnread(), rs.getStreamUnreadLen());
}

void Docker::event_onLoadServiceInDocker(TcpSessionPtr session, ReadStream & rs)
{
    LoadServiceInDocker service;
    rs >> service;
    LOGI("Docker::event_onLoadServiceInDocker type=" << service.serviceType << ", name=" << service.serviceName << ", id=" << service.serviceID);
    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("LoadServiceInDocker can't founder service type. service=" << ServiceTypeNames.at(service.serviceType));
        return;
    }
    auto ret = createService(ServerConfig::getRef().getDockerID(), service.serviceType, service.serviceID, service.serviceName, service.clientDockerID, service.clientSessionID, false, false);
    if (ret)
    {
        ret->onLoad();
    }
}

void Docker::event_onSwitchServiceClient(TcpSessionPtr session, ReadStream & rs)
{
    SwitchServiceClient change;
    rs >> change;
    LOGI("Docker::event_onSwitchServiceClient type=" << change.serviceType << ", id=" << change.serviceID);
    auto founder = _services.find(change.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onSwitchServiceClient can't founder service type. service=" << ServiceTypeNames.at(change.serviceType));
        return;
    }
    auto fder = founder->second.find(change.serviceID);
    if (fder == founder->second.end() || fder->second->isShell())
    {
        LOGE("event_onSwitchServiceClient can't founder service id. service=" << ServiceTypeNames.at(change.serviceType) << ", id=" << change.serviceID);
        return;
    }
    if (fder->second->getClientSessionID() != InvalidSessionID)
    {
        KickRealClient kick(fder->second->getClientSessionID());
        Docker::getRef().sendToDocker(fder->second->getClientDockerID(), kick);
    }
    fder->second->setClientSessionID(change.clientSessionID);
    fder->second->setClientDockerID(change.clientDockerID);
    fder->second->onClientChange();
    SwitchServiceClientNotice notice(change.serviceType, change.serviceID, change.clientDockerID, change.clientSessionID);
    Docker::getRef().broadcastToDockers(notice, false);

    if (fder->second->getServiceType() > ServiceMulti)
    {
        RefreshServiceToMgrNotice refreshNotice(
            fder->second->getServiceDockerID(),
            fder->second->getServiceType(),
            fder->second->getServiceID(),
            fder->second->getServiceName(),
            fder->second->getStatus(),
            fder->second->getClientDockerID(),
            fder->second->getClientSessionID());
        for (ui16 i = ServiceInvalid + 1; i < ServiceMulti; i++)
        {
            fder->second->toService(i, refreshNotice, nullptr);
        }
    }
}
void Docker::event_onSwitchServiceClientNotice(TcpSessionPtr session, ReadStream & rs)
{
    SwitchServiceClientNotice change;
    rs >> change;
    LOGI("Docker::event_onSwitchServiceClient type=" << change.serviceType << ", id=" << change.serviceID);

    auto founder = _services.find(change.serviceType);
    if (founder == _services.end())
    {
        LOGW("event_onSwitchServiceClientNotice can't founder remote service type. type=" << change.serviceType << ", id=" << change.serviceID);
        return;
    }
    auto fder = founder->second.find(change.serviceID);
    if (fder != founder->second.end() && fder->second)
    {
        fder->second->setClientSessionID(change.clientSessionID);
        fder->second->setClientDockerID(change.clientDockerID);
        fder->second->onClientChange();
    }
    else
    {
        LOGW("event_onSwitchServiceClientNotice can't founder remote service id. type=" << change.serviceType << ", id=" << change.serviceID);
    }
}


void Docker::event_onLoadServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    LoadServiceNotice service;
    rs >> service;
    LOGI("Docker::event_onLoadServiceNotice type=" << service.serviceType << ", name=" << service.serviceName << ", id=" << service.serviceID);

    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onLoadServiceNotice can't founder remote service. service=" << ServiceTypeNames.at(service.serviceType));
        return;
    }
    auto servicePtr = createService(service.serviceDockerID, service.serviceType, service.serviceID, service.serviceName, service.clientDockerID, service.clientSessionID, true, false);
    if (servicePtr)
    {
        servicePtr->setStatus(SS_WORKING);
    }
}

void Docker::event_onKickRealClient(TcpSessionPtr session, ReadStream & rs)
{
    KickRealClient notice;
    rs >> notice;
    LOGI("Docker::event_onKickRealClient kick client .  client session id=" << notice.clientSessionID);
    SessionManager::getRef().kickSession(notice.clientSessionID);
}




void Docker::event_onUnloadServiceInDocker(TcpSessionPtr session, ReadStream & rs)
{
    UnloadServiceInDocker service;
    rs >> service;
    LOGD("event_onUnloadServiceInDocker. type=" << service.serviceType << ", id=" << service.serviceID);
    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onUnloadServiceInDocker can't founder remote service. service=" << ServiceTypeNames.at(service.serviceType));
        return;
    }
    auto fder = founder->second.find(service.serviceID);
    if (fder != founder->second.end() && fder->second && fder->second->getStatus() == SS_WORKING && !fder->second->isShell())
    {
        LOGD("unload service [" << fder->second->getServiceName() << "], cur DockerID=" << fder->second->getServiceDockerID());
        fder->second->setStatus(SS_UNLOADING);
        fder->second->onUnload();
    }
}

void Docker::event_onUnloadedServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    UnloadedServiceNotice service;
    rs >> service;

    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onUnloadedServiceNotice can't founder remote service. service=" << ServiceTypeNames.at(service.serviceType));
        return;
    }
    destroyService(service.serviceType, service.serviceID);
}


void Docker::event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);
    if (DockerPulse::getProtoID() != rsShell.getProtoID())
    {
        LOGT("event_onServiceMessage protoID=" << rsShell.getProtoID() << ", len=" << len);
    }

    if (rsShell.getProtoID() == DockerPulse::getProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    else if (rsShell.getProtoID() == ShutdownClusterServer::getProtoID() )
    {
        LOGA("onShutdownClusterServer.. fromSessionID=" << session->getSessionID());
        onShutdown();
        return;
    }
    else if (rsShell.getProtoID() == LoadServiceInDocker::getProtoID())
    {
        event_onLoadServiceInDocker(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == LoadServiceNotice::getProtoID())
    {
        event_onLoadServiceNotice(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == SwitchServiceClient::getProtoID())
    {
        event_onSwitchServiceClient(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == SwitchServiceClientNotice::getProtoID())
    {
        event_onSwitchServiceClientNotice(session, rsShell);
        return;
    }

    else if (rsShell.getProtoID() == KickRealClient::getProtoID())
    {
        event_onKickRealClient(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == UnloadServiceInDocker::getProtoID())
    {
        event_onUnloadServiceInDocker(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == UnloadedServiceNotice::getProtoID())
    {
        event_onUnloadedServiceNotice(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == ForwardToService::getProtoID())
    {
        event_onForwardToService(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == ForwardToRealClient::getProtoID())
    {
        event_onForwardToRealClient(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == WebServerRequest::getProtoID())
    {
        event_onWebServerRequest(session, rsShell);
    }
    else if (rsShell.getProtoID() == SessionPulse::getProtoID())
    {
        SessionPulse pulse;
        rsShell >> pulse;
        auto service = peekService(ServiceUser, pulse.serviceID);
        if (service && !service->isShell() && service->getStatus() == SS_WORKING)
        {
            service->onTick();
        }
        else
        {
            LOGE("onSessionPulse error. serviceID=" << pulse.serviceID);
        }
    }
    else if (rsShell.getProtoID() == SelectUserPreviewsFromUserMgrResp::getProtoID())
    {
        SelectUserPreviewsFromUserMgrResp resp;
        rsShell >> resp;
        auto clientSession = SessionManager::getRef().getTcpSession(resp.clientSessionID);
        if (!clientSession)
        {
            LOGE("can not found client session. sessionID=" << resp.clientSessionID);
            return;
        }
        if (resp.retCode == EC_SUCCESS)
        {
            clientSession->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_AUTHED);
            clientSession->setUserParam(UPARAM_ACCOUNT, resp.account);
        }
        else
        {
            clientSession->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
        }
        ClientAuthResp clientResp;
        clientResp.account = resp.account;
        clientResp.retCode = resp.retCode;
        clientResp.token = resp.token;
        clientResp.previews = std::move(resp.previews);
        sendToSession(resp.clientSessionID, clientResp);
        return;
    }
    else if (rsShell.getProtoID() == CreateUserFromUserMgrResp::getProtoID())
    {
        CreateUserFromUserMgrResp resp;
        rsShell >> resp;
        CreateUserResp clientResp;
        clientResp.retCode = resp.retCode;
        clientResp.serviceID = resp.serviceID;
        clientResp.previews = std::move(resp.previews);
        sendToSession(resp.clientSessionID, clientResp);
        return;
    }
    else if (rsShell.getProtoID() == AttachUserFromUserMgrResp::getProtoID())
    {
        AttachUserFromUserMgrResp resp;
        rsShell >> resp;
        auto clientSession = SessionManager::getRef().getTcpSession(resp.clientSessionID);
        if (!clientSession)
        {
            LOGE("can not found client session. sessionID=" << resp.clientSessionID);
            return;
        }
        if (resp.retCode == EC_SUCCESS)
        {
            clientSession->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_ATTACHED);
            clientSession->setUserParam(UPARAM_SERVICE_ID, resp.serviceID);
            clientSession->setUserParam(UPARAM_LOGIN_TIME, getNowTime());
        }
        AttachUserResp clientResp;
        clientResp.retCode = resp.retCode;
        sendToSession(resp.clientSessionID, clientResp);
        return;
    }
}











void Docker::event_onClientLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
    LOGD("Docker::event_onClientLinked. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}
void Docker::event_onClientPulse(TcpSessionPtr session)
{
    auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
    if (getNowTime() - (time_t)last > session->getOptions()._sessionPulseInterval * 3)
    {
        LOGW("client timeout . diff time=" << getNowTime() - (time_t)last << ", sessionID=" << session->getSessionID());
        session->close();
        return;
    }
    SessionStatus sStatus = (SessionStatus)session->getUserParamNumber(UPARAM_SESSION_STATUS);
    if (sStatus == SSTATUS_ATTACHED)
    {
        const auto & services = peekService(ServiceUser);
        ServiceID serviceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        auto iter = services.find(serviceID);
        if (iter == services.end())
        {
            LOGE("SSTATUS_ATTACHED session not found service ID. service id=" << serviceID << ", session id=" << session->getSessionID());
        }
        else
        {
            SessionPulse pulse;
            pulse.serviceID = serviceID;
            sendToDocker(iter->second->getServiceDockerID(), pulse);
        }
    }
}
void Docker::event_onClientClosed(TcpSessionPtr session)
{
    LOGD("Docker::event_onClientClosed. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
    if (isConnectID(session->getSessionID()))
    {
        LOGF("Unexpected");
    }
    else
    {
        if (session->getUserParamNumber(UPARAM_SESSION_STATUS) == SSTATUS_ATTACHED)
        {
            Tracing trace;
            trace.fromServiceType = ServiceClient;
            trace.fromServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
            trace.toServiceType = ServiceUserMgr;
            trace.toServiceID = InvalidServiceID;

            RealClientClosedNotice notice;
            notice.serviceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
            notice.clientDockerID = ServerConfig::getRef().getDockerID();
            notice.clientSessionID = session->getSessionID();
            toService(trace, notice, true, true);
        }
    }
}



void Docker::event_onClientMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
    if (!_dockerServiceWorking || _dockerStopping)
    {
        LOGW("cluster not open service or closing service");
        return;
    }
    ReadStream rs(begin, len);
    SessionStatus sessionStatus = (SessionStatus) session->getUserParamNumber(UPARAM_SESSION_STATUS);
    if (rs.getProtoID() == ClientPulse::getProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    else if (rs.getProtoID() == ClientAuthReq::getProtoID())
    {
        LOGD("ClientAuthReq sID=" << session->getSessionID() << ", block len=" << len);
        if (sessionStatus != SSTATUS_UNKNOW)
        {
            LOGE("duplicate ClientAuthReq. sID=" << session->getSessionID());
            return;
        }
        ClientAuthReq clientReq;
        rs >> clientReq;
        Tracing trace;
        trace.fromServiceType = ServiceClient;
        trace.fromServiceID = InvalidServiceID;
        trace.toServiceType = ServiceUserMgr;
        trace.toServiceID = InvalidServiceID;

        SelectUserPreviewsFromUserMgrReq serviceReq;
        serviceReq.account = clientReq.account;
        serviceReq.token = clientReq.token;
        serviceReq.clientDockerID = ServerConfig::getRef().getDockerID();
        serviceReq.clientSessionID = session->getSessionID();
        toService(trace, serviceReq, true, true);
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_AUTHING);
        return;
    }
    else if (rs.getProtoID() == CreateUserReq::getProtoID())
    {
        LOGD("CreateUserReq sID=" << session->getSessionID() << ", block len=" << len);
        if (sessionStatus != SSTATUS_AUTHED)
        {
            LOGE("CreateUserReq : client not authed. sID=" << session->getSessionID() << ", sessionStatus=" << (short)sessionStatus);
            return;
        }
        CreateUserReq clientReq;
        rs >> clientReq;
        Tracing trace;
        trace.fromServiceType = ServiceClient;
        trace.fromServiceID = InvalidServiceID;
        trace.toServiceType = ServiceUserMgr;
        trace.toServiceID = InvalidServiceID;

        CreateUserFromUserMgrReq serviceReq;
        serviceReq.account = session->getUserParamString(UPARAM_ACCOUNT);
        serviceReq.serviceName = clientReq.serviceName;
        serviceReq.clientDockerID = ServerConfig::getRef().getDockerID();
        serviceReq.clientSessionID = session->getSessionID();
        toService(trace, serviceReq, true, true);
        return;
    }
    else if (rs.getProtoID() == AttachUserReq::getProtoID())
    {
        LOGD("AttachUserReq sID=" << session->getSessionID() << ", block len=" << len);
        if (sessionStatus != SSTATUS_AUTHED)
        {
            LOGE("AttachUserReq : client not authed. sID=" << session->getSessionID());
            return;
        }
        AttachUserReq clientReq;
        rs >> clientReq;
        Tracing trace;
        trace.fromServiceType = ServiceClient;
        trace.fromServiceID = InvalidServiceID;
        trace.toServiceType = ServiceUserMgr;
        trace.toServiceID = InvalidServiceID;

        AttachUserFromUserMgrReq serviceReq;
        serviceReq.serviceID = clientReq.serviceID;
        serviceReq.account = session->getUserParamString(UPARAM_ACCOUNT);
        serviceReq.clientDockerID = ServerConfig::getRef().getDockerID();
        serviceReq.clientSessionID = session->getSessionID();
        toService(trace, serviceReq, true, true);
        return;
    }
    else if (rs.getProtoID() >= 40000 && sessionStatus == SSTATUS_ATTACHED)
    {
        LOGD("client other proto to user service. sID=" << session->getSessionID() << ", block len=" << len);
        Tracing trace;
        trace.fromServiceType = ServiceClient;
        trace.fromServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        trace.toServiceType = ServiceUser;
        trace.toServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        toService(trace, rs.getStream(), rs.getStreamLen(), true, true);
        return;
    }
    else
    {
        LOGE("client unknow proto or wrong status. protoID=" << rs.getProtoID() << ", status=" << (ui16)sessionStatus << ", sessionID=" << session->getSessionID());
    }
}



void Docker::event_onWebClientRequestAPI(TcpSessionPtr session, const std::string & method, const std::string & methodLine, 
    const std::map<std::string,std::string> &head, const std::string & body)
{
    LOGD("onWebMessage sessionID=" << session->getSessionID() << ", method=" << method << ", methodLine=" << methodLine);
    WebAgentClientRequestAPI notice;
    notice.webClientID = session->getSessionID();
    notice.method = method;
    notice.methodLine = methodLine;
    notice.heads = head;
    notice.body = body;

    Tracing trace;
    trace.fromDockerID = ServerConfig::getRef().getDockerID();
    trace.fromServiceType = ServiceInvalid;
    trace.fromServiceID = InvalidServiceID;
    trace.toDockerID = InvalidDockerID;
    trace.toServiceType = ServiceWebAgent;
    trace.toServiceID = InvalidServiceID;
    toService(trace, notice, true, false);
}

void Docker::event_onWebServerRequest(TcpSessionPtr session, ReadStream & rs)
{
    WebServerRequest req;
    rs >> req;
    SessionID cID =  SessionManager::getRef().addConnecter(req.ip, req.port);
    if (cID == InvalidServiceID)
    {
        LOGE("");
        return;
    }
    auto  connecter = SessionManager::getRef().getTcpSession(cID);
    if (!connecter)
    {
        LOGE("");
        return;
    }
    auto & option = connecter->getOptions();
    option._protoType = PT_HTTP;
    option._connectPulseInterval = 10000;
    option._reconnects = 0;
    auto onLinked = [](TcpSessionPtr   session, const WebServerRequest & req)
    {
        WriteHTTP wh;
        for (const auto & head : req.heads)
        {
            wh.addHead(head.first, head.second);
        }
        if (req.isGet)
        {
            wh.get(req.uri + "?" + urlEncode(req.params));
        }
        else
        {
            wh.post(req.uri, req.params);
        }
        SessionManager::getRef().sendSessionData(session->getSessionID(), wh.getStream(), wh.getStreamLen());
    };
    option._onSessionLinked = std::bind(onLinked, _1, req);
    option._onSessionClosed = [](TcpSessionPtr   session)
    {

    };
    auto onResponse = [this](TcpSessionPtr session, const std::string& method, const std::string &methodLine,
        const std::map<std::string, std::string> &head, const std::string & body, const WebServerRequest & req)
    {
        SessionManager::getRef().kickConnect(session->getSessionID());
        WebServerResponse resp;
        resp.heads = head;
        resp.method = method;
        resp.methodLine = methodLine;
        resp.body = body;
        Tracing trace;
        trace.toServiceType = req.fromServiceType;
        trace.toServiceID = req.fromServiceID;
        trace.traceBackID = req.traceID;
        toService(trace, resp, true, false);
    };
    option._onHTTPBlockDispatch = std::bind(onResponse, _1, _2, _3, _4, _5, req);
    SessionManager::getRef().openConnecter(cID);
}


void Docker::sendToSession(SessionID sessionID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sessionID, block, len);
}


void Docker::packetToSessionWithTracing(SessionID sessionID, const Tracing & trace, const char * block, unsigned int len)
{
    try
    {
        WriteStream ws(ForwardToService::getProtoID());
        ws << trace;
        ws.appendOriginalData(block, len);
        sendToSession(sessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::packetToSessionWithTracing catch except error. e=" << e.what());
    }
}


void Docker::sendToDocker(DockerID dockerID, const char * block, unsigned int len)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder == _dockerSession.end())
    {
        LOGF("Docker::sendToDocker fatal error. dockerID not found. dockerID=" << dockerID);
        return;
    }
    if (founder->second.sessionID == InvalidSessionID)
    {
        LOGF("Docker::sendToDocker fatal error. dockerID not have session. dockerID=" << dockerID);
        return;
    }
    if (founder->second.status == 0)
    {
        LOGW("Docker::sendToDocker warning error. session try connecting. dockerID=" << dockerID << ", client session ID=" << founder->second.sessionID);
    }
    sendToSession(founder->second.sessionID, block, len);
}


void Docker::packetToDockerWithTracing(DockerID dockerID, const Tracing & trace, const char * block, unsigned int len)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.sessionID != InvalidSessionID && founder->second.status != 0)
    {
        packetToSessionWithTracing(founder->second.sessionID, trace, block, len);
    }
    else
    {
        LOGE("Docker::packetToDockerWithTracing not found docker. dockerID=" << dockerID);
    }
}

void Docker::packetToClientViaDocker(DockerID dockerID, SessionID clientSessionID, const char * block, unsigned int len)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.sessionID != InvalidSessionID && founder->second.status != 0)
    {
        WriteStream ws(ForwardToRealClient::getProtoID());
        ws << clientSessionID;
        ws.appendOriginalData(block, len);
        sendToSession(founder->second.sessionID, ws.getStream(), ws.getStreamLen());
    }
    else
    {
        LOGE("Docker::packetToClientViaDocker not found docker. dockerID=" << dockerID);
    }
}

void Docker::sendToDocker(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len)
{
    LOGT("Docker::sendToDocker serviceType=" << (ui16)serviceType << ", serviceID=" << serviceID << ", block len=" << len);
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        LOGE("Docker::sendToDocker error. type not found. serviceType=" << (ui16)serviceType << ", serviceID=" << serviceID << ", block len=" << len);
        return;
    }
    auto fder = founder->second.find(serviceID);
    if (fder == founder->second.end())
    {
        LOGE("Docker::sendToDocker error. service id not found. serviceType=" << (ui16)serviceType << ", serviceID=" << serviceID << ", block len=" << len);
        return;
    }
    sendToDocker(fder->second->getServiceDockerID(), block, len);
}






void Docker::toService(Tracing trace, const char * block, unsigned int len, bool canForwardToOtherService, bool needPost)
{
    try
    {
        ProtoID protoID = InvalidProtoID;
        if (trace.toServiceType != ServiceClient)
        {
            ReadStream rs(block, len);
            protoID = rs.getProtoID();
        }
        if (trace.fromServiceType >= ServiceMax || trace.toServiceType >= ServiceMax || trace.toServiceType == ServiceInvalid)
        {
            LOGF("Docker::sendToService Illegality trace. trace=" << trace << ", block len=" << len << ", protoID=" << protoID);
            return;
        }
        LOGT("Docker::toService " << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);

        if (trace.toDockerID != InvalidDockerID && trace.toDockerID != ServerConfig::getRef().getDockerID()) //service shell maybe not success. do this.
        {
            packetToDockerWithTracing(trace.toDockerID, trace, block, len);
            return;
        }
        ui16 toServiceType = trace.toServiceType;
        if (trace.toServiceType == ServiceClient)
        {
            toServiceType = ServiceUser;
        }

        auto founder = _services.find(toServiceType);
        if (founder == _services.end())
        {
            LOGF("Docker::toService can not found toServiceType type  trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
            return;
        }
        auto fder = founder->second.find(trace.toServiceID);
        if (fder == founder->second.end())
        {
            if (toServiceType == ServiceUser)
            {
                LOGW("Docker::toService can not found ServiceUser ID. trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
            }
            else
            {
                LOGE("Docker::toService can not found toServiceType ID. trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
            }
            return;
        }
        auto & service = *fder->second;
        if (service.isShell() && !canForwardToOtherService)
        {
            LOGE("local service is shell but the call from other docker. trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
            return;
        }
        if (service.isShell()) //forward 
        {
            DockerID dockerID = service.getServiceDockerID();
            packetToDockerWithTracing(dockerID, trace, block, len);
        }
        else //direct process
        {
            if (trace.toServiceType == ServiceClient)
            {
                if (service.getClientDockerID() == InvalidDockerID || service.getClientSessionID() == InvalidSessionID)
                {
                    LOGW("Docker::toService  ServiceClient sendToSession (client) warning. client dockerID or sessionID is Invalid "
                        <<", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                        << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                }
                else if (service.getClientDockerID() == ServerConfig::getRef().getDockerID())
                {

                    LOGT("Docker::toService  ServiceClient sendToSession (client) " << trace 
                        << ", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                        << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                    sendToSession(service.getClientSessionID(), block, len);
                }
                else
                {
                    LOGT("Docker::toService  ServiceClient ForwardToRealClient " << trace
                        << ", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                        << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                    packetToClientViaDocker(service.getClientDockerID(), service.getClientSessionID(), block, len);
                }

            }
            else if (needPost)
            {
                LOGT("Docker::toService local post process4bind " << trace << ", len=" << len 
                    << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                std::string bk;
                bk.assign(block, len);
                SessionManager::getRef().post(std::bind(&Service::process4bind, fder->second, trace, std::move(bk)));
            }
            else
            {
                LOGT("Docker::toService  local process " << trace << ", len=" << len 
                    << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                fder->second->process(trace, block, len);
            }
        }
    }
    catch (const std::exception& e)
    {
        LOGE("Docker::toService catch one exception. trace=" << trace << ", block len=" << len << ", e=" << e.what() );
    }
    catch (...)
    {
        LOGE("Docker::toService catch one exception. trace=" << trace << ", block len=" << len );
    }
}



ServicePtr Docker::peekService(ServiceType serviceType, ServiceID serviceID)
{
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        return nullptr;
    }
    auto fder = founder->second.find(serviceID);
    if (fder == founder->second.end())
    {
        return nullptr;
    }
    return fder->second;
}

std::unordered_map<ServiceID, ServicePtr > & Docker::peekService(ServiceType serviceType)
{
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        return _invalidServices;
    }
    return founder->second;
}




