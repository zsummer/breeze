
#include "docker.h"
#include "dbService.h"
#include "userMgrService.h"
#include "userService.h"
#include "shellService.h"
#include <ProtoUser.h>
#include <ProtoUserMgr.h>
int g_closeState = 0;

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
    SessionManager::getRef().createTimer(1000, std::bind(&Docker::checkServiceState, Docker::getPtr()));
    return true;
}
void sigInt(int sig)
{
    if (g_closeState == 0)
    {
        g_closeState = 1;
        SessionManager::getRef().post(std::bind(&Docker::stop, Docker::getPtr()));
    }
}

void Docker::onCheckSafeExit()
{
    LOGA("Docker::onCheckSafeExit. checking.");

    if (g_closeState == 1)
    {
        LOGA("Docker::onCheckSafeExit. g_closeState change to 2.");
        g_closeState = 2;
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
                    svc.second->onUninit(); //需要逐依赖关系uninit  
                }
            }
        }
    }

    bool safe =  true;
    for(auto &second : _services)
    {
        if (second.first == ServiceClient || second.first == ServiceUser || second.first == ServiceInvalid)
        {
            continue;
        }
        for (auto & svc : second.second)
        {
            if (!svc.second->isShell() && svc.second->getStatus() == SS_WORKING)   //状态判断需要改  
            {
                safe = false;
            }
        }
    }
    if(safe)
    {
        LOGA("all services closed.");
        SessionManager::getRef().stopAccept();
        SessionManager::getRef().kickClientSession();
        SessionManager::getRef().kickConnect();
        SessionManager::getRef().stop();
    }
    else
    {
        SessionManager::getRef().createTimer(1000, std::bind(&Docker::onCheckSafeExit, this));
    }
}
bool Docker::run()
{
    SessionManager::getRef().run();
    LOGA("Docker::run exit!");
    return true;
}

bool Docker::isStoping()
{
    return g_closeState != 0;
}

void Docker::stop()
{
    g_closeState = 1;
    SessionManager::getRef().stopAccept();
    if (_wlisten != InvalidAccepterID)
    {
        SessionManager::getRef().stopAccept();
        SessionManager::getRef().kickClientSession(_wlisten);
    }
    onCheckSafeExit();
    return ;
}

bool Docker::startDockerListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    ServerConfig::getRef().getDockerID();
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
                LOGE("options._onSessionPulse check timeout failed. diff time=" << getNowTime() - (time_t)last);
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
        if (!createService(i, InvalidServiceID, stc.at(i).front(), InvalidDockerID, InvalidSessionID, stc.at(i).front() != ServerConfig::getRef().getDockerID(), true))
        {
            return false;
        }
    }
    return true;
}
bool Docker::startDockerWideListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    ServerConfig::getRef().getDockerID();
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
        options._whitelistIP = docker._whiteList;
        options._maxSessions = 5000;
        options._sessionOptions._sessionPulseInterval = 10000;
        options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if (getNowTime() - (time_t)last > session->getOptions()._sessionPulseInterval * 3)
            {
                LOGE("options._onSessionPulse check timeout failed. diff time=" << getNowTime() - (time_t)last);
                session->close();
            }
        };
        options._sessionOptions._onSessionLinked = std::bind(&Docker::event_onClientLinked, this, _1);
        options._sessionOptions._onSessionClosed = std::bind(&Docker::event_onClientClosed, this, _1);
        options._sessionOptions._onBlockDispatch = std::bind(&Docker::event_onClientMessage, this, _1, _2, _3);
        if (!SessionManager::getRef().openAccepter(aID))
        {
            LOGE("Docker::startDockerWideListen openAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort);
            return false;
        }
        LOGA("Docker::startDockerWideListen openAccepter success. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort << ", listen aID=" << aID);
        _wlisten = aID;
    }
    return true;
}

bool Docker::start()
{
    return startDockerListen() && startDockerConnect() && startDockerWideListen();
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
                CreateOrRefreshServiceNotice notice(svc.second->getServiceType(), svc.second->getServiceID(), svc.second->getDockerID(), svc.second->getClientDockerID(), svc.second->getClientSessionID());
                Docker::getRef().sendToSession(session->getSessionID(), notice);
            }
        }
    }
    checkServiceState();
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

ServicePtr Docker::createService(ui16 serviceType, ServiceID serviceID, DockerID dockerID, DockerID clientDockerID, SessionID clientSessionID, bool isShell, bool failExit)
{
    LOGI("Docker::createServic self dockerID=" << ServerConfig::getRef().getDockerID() << ", serviceType=" << serviceType
         << ", serviceID=" << serviceID << ", dockerID=" << dockerID << ", clientDockerID=" << clientDockerID
            <<", clientSessionID=" << clientSessionID << ", isShell=" << isShell <<",faileExit=" << failExit);
    ServicePtr & service = _services[serviceType][serviceID];
    if (service && !service->isShell())
    {
        LOGE("Docker::createService error. service alread exist. serviceType=" << ServiceNames.at(serviceType) << ", serviceID="
            << serviceID << ", dockerID=" << dockerID << ", clientDockerID=" << clientDockerID << ", clientSessionID=" << clientSessionID 
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
    else
    {
        LOGE("createService invalid service type " << serviceType);
        if (failExit)
        {
            goto goExit;
        }
        return nullptr;
    }
    service->setServiceType(serviceType);
    service->setServiceID(serviceID);
    service->setDockerID(dockerID);
    service->setClientSessionID(clientSessionID);
    service->setClientDockerID(clientDockerID);
    service->setStatus(SS_CREATED);

    
    return service;
goExit:
    Docker::getRef().stop();
    return nullptr;
}

void Docker::checkServiceState()
{
    SessionManager::getRef().createTimer(1000, std::bind(&Docker::checkServiceState, Docker::getPtr()));
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
                && (service.second->getStatus() == SS_INITING || service.second->getStatus() == SS_WORKING || service.second->getStatus() == SS_UNINITING) )
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
                    Docker::getRef().stop();
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
                    LOGI("local service [" << ServiceNames.at(service.second->getServiceType()) << "] begin init. [" << service.second->getServiceID() << "] ...");
                    service.second->setStatus(SS_INITING);
                    bool ret = service.second->onInit();
                    if (ret)
                    {
                        LOGD("local service [" << ServiceNames.at(service.second->getServiceType()) << "] call onInit success. [" << service.second->getServiceID() << "] ...");
                    }
                    else
                    {
                        LOGE("local service [" << ServiceNames.at(service.second->getServiceType()) << "]  call onInit error.[" << service.second->getServiceID() << "] ...");
                        Docker::getRef().stop();
                        return;
                    }
                    return;
                }
                if (service.second->getStatus() == SS_DESTROY || service.second->getStatus() == SS_UNINITING)
                {
                    LOGE("local service [" << ServiceNames.at(service.second->getServiceType()) << "]  init error.[" << service.second->getServiceID() << "] ...");
                    Docker::getRef().stop();
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

void Docker::event_onCreateServiceInDocker(TcpSessionPtr session, ReadStream & rs)
{
    CreateServiceInDocker service;
    rs >> service;
    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("CreateServiceInDocker can't founder service type. service=" << ServiceNames.at(service.serviceType));
        return;
    }
    auto ret = createService(service.serviceType, service.serviceID, ServerConfig::getRef().getDockerID(), service.clientDockerID, service.clientSessionID, false, false);
    if (ret)
    {
        ret->onInit();
    }
}

void Docker::event_onChangeServiceClient(TcpSessionPtr session, ReadStream & rs)
{
    CreateServiceInDocker service;
    rs >> service;
    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onChangeServiceClient can't founder service type. service=" << ServiceNames.at(service.serviceType));
        return;
    }
    auto fder = founder->second.find(service.serviceID);
    if (fder == founder->second.end() || fder->second->isShell())
    {
        LOGE("event_onChangeServiceClient can't founder service id. service=" << ServiceNames.at(service.serviceType) << ", id=" << service.serviceID);
        return;
    }
    fder->second->setClientSessionID(service.clientSessionID);
    fder->second->setClientDockerID(service.clientDockerID);
    
    Docker::getRef().broadcastToDockers(CreateOrRefreshServiceNotice(service.serviceType, service.serviceID, fder->second->getDockerID(), service.clientDockerID, service.clientSessionID), false);
}

void Docker::event_onCreateOrRefreshServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    CreateOrRefreshServiceNotice service;
    rs >> service;

    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onCreateOrRefreshServiceNotice can't founder remote service. service=" << ServiceNames.at(service.serviceType));
        return;
    }
    auto servicePtr = createService(service.serviceType, service.serviceID, service.dockerID, service.clientDockerID, service.clientSessionID, true, false);
    if (servicePtr)
    {
        servicePtr->setStatus(SS_WORKING);
    }
}

void Docker::event_onDestroyServiceInDocker(TcpSessionPtr session, ReadStream & rs)
{
    DestroyServiceInDocker service;
    rs >> service;

    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onDestroyServiceInDocker can't founder remote service. service=" << ServiceNames.at(service.serviceType));
        return;
    }
    auto fder = founder->second.find(service.serviceID);
    if (fder != founder->second.end() && fder->second && fder->second->getStatus() == SS_WORKING && !fder->second->isShell())
    {
        fder->second->setStatus(SS_UNINITING);
        fder->second->onUninit();
    }
}

void Docker::event_onDestroyServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    DestroyServiceNotice service;
    rs >> service;

    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onDestroyServiceNotice can't founder remote service. service=" << ServiceNames.at(service.serviceType));
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
    else if (rsShell.getProtoID() == CreateServiceInDocker::getProtoID())
    {
        event_onCreateServiceInDocker(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == ChangeServiceClient::getProtoID())
    {
        event_onChangeServiceClient(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == CreateOrRefreshServiceNotice::getProtoID())
    {
        event_onCreateOrRefreshServiceNotice(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == DestroyServiceInDocker::getProtoID())
    {
        event_onDestroyServiceInDocker(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == DestroyServiceNotice::getProtoID())
    {
        event_onDestroyServiceNotice(session, rsShell);
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

void Docker::event_onClientClosed(TcpSessionPtr session)
{
    LOGD("Docker::event_onClientClosed. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
    if (isConnectID(session->getSessionID()))
    {
    }
    else
    {
        if (session->getUserParamNumber(UPARAM_SESSION_STATUS) == SSTATUS_ATTACHED)
        {
            Tracing trace;
            trace._fromServiceType = ServiceClient;
            trace._fromServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
            trace._toServiceType = ServiceUserMgr;
            trace._toServiceID = InvalidServiceID;

            ClientDisconnectReq serviceReq;
            serviceReq.serviceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
            serviceReq.clientDockerID = ServerConfig::getRef().getDockerID();
            serviceReq.clientSessionID = session->getSessionID();
            toService(trace, serviceReq, true, true);
        }
    }
}



void Docker::event_onClientMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
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
        trace._fromServiceType = ServiceClient;
        trace._fromServiceID = InvalidServiceID;
        trace._toServiceType = ServiceUserMgr;
        trace._toServiceID = InvalidServiceID;

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
        trace._fromServiceType = ServiceClient;
        trace._fromServiceID = InvalidServiceID;
        trace._toServiceType = ServiceUserMgr;
        trace._toServiceID = InvalidServiceID;

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
        trace._fromServiceType = ServiceClient;
        trace._fromServiceID = InvalidServiceID;
        trace._toServiceType = ServiceUserMgr;
        trace._toServiceID = InvalidServiceID;

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
        trace._fromServiceType = ServiceClient;
        trace._fromServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        trace._toServiceType = ServiceUser;
        trace._toServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        toService(trace, rs.getStream(), rs.getStreamLen(), true, true);
        return;
    }
    else
    {
        LOGE("client unknow proto or wrong status. protoID=" << rs.getProtoID() << ", status=" << (ui16)sessionStatus << ", sessionID=" << session->getSessionID());
    }
}






void Docker::sendToSession(SessionID sessionID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sessionID, block, len);
}


void Docker::sendToSession(SessionID sessionID, const Tracing & trace, const char * block, unsigned int len)
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
        LOGE("Docker::sendToSession catch except error. e=" << e.what());
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


void Docker::sendToDocker(DockerID dockerID, const Tracing & trace, const char * block, unsigned int len)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.sessionID != InvalidSessionID && founder->second.status != 0)
    {
        sendToSession(founder->second.sessionID, trace, block, len);
    }
    else
    {
        LOGE("Docker::sendToDocker not found docker. dockerID=" << dockerID);
    }
}

void Docker::sendToDocker(DockerID dockerID, SessionID clientSessionID, const char * block, unsigned int len)
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
        LOGE("Docker::sendToDocker not found docker. dockerID=" << dockerID);
    }
}

void Docker::sendToDockerByService(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len)
{
    LOGT("Docker::sendToDockerByService serviceType=" << (ui16)serviceType << ", serviceID=" << serviceID << ", block len=" << len);
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        LOGE("Docker::sendToDockerByService error. type not found. serviceType=" << (ui16)serviceType << ", serviceID=" << serviceID << ", block len=" << len);
        return;
    }
    auto fder = founder->second.find(serviceID);
    if (fder == founder->second.end())
    {
        LOGE("Docker::sendToDockerByService error. service id not found. serviceType=" << (ui16)serviceType << ", serviceID=" << serviceID << ", block len=" << len);
        return;
    }
    sendToDocker(fder->second->getDockerID(), block, len);
}






void Docker::toService(Tracing trace, const char * block, unsigned int len, bool canForwardToOtherService, bool needPost)
{
    if (trace._fromServiceType >= ServiceMax || trace._toServiceType >= ServiceMax || trace._toServiceType == ServiceInvalid)
    {
        LOGF("Docker::sendToService Illegality trace. trace=" << trace << ", block len=" << len);
        return;
    }
    LOGT("Docker::toService " << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);

    if (trace._toDockerID != InvalidDockerID && trace._toDockerID != ServerConfig::getRef().getDockerID())
    {
        sendToDocker(trace._toDockerID, trace, block, len);
        LOGT("Docker::toService  sendToDocker" << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
        return;
    }
    ui16 toServiceType = trace._toServiceType;
    if (trace._toServiceType == ServiceClient)
    {
        toServiceType = ServiceUser;
    }

    auto founder = _services.find(toServiceType);
    if (founder == _services.end())
    {
        LOGF("Docker::toService can not found _toServiceType type  trace =" << trace << ", block len=" << len);
        return;
    }
    auto fder = founder->second.find(trace._toServiceID);
    if (fder == founder->second.end())
    {
        LOGE("Docker::toService can not found _toServiceType ID. trace =" << trace << ", block len=" << len);
        return;
    }
    auto & service = *fder->second;
    if (service.isShell() && !canForwardToOtherService)
    {
        LOGE("local service is shell but the call from other docker.");
        return;
    }
    if (service.isShell()) //forward 
    {
        DockerID dockerID = service.getDockerID();
        sendToDocker(dockerID, trace, block, len);
        LOGT("Docker::toService  sendToDocker" << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
    }
    else //direct process
    {
        if (trace._toServiceType == ServiceClient)
        {
            if (service.getClientDockerID() == InvalidDockerID || service.getClientSessionID() != InvalidSessionID)
            {
                LOGW("Docker::toService  ServiceClient sendToSession (client) warning. client dockerID or sessionID is Invalid "
                    <<", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                    << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
            }
            if (service.getClientDockerID() == ServerConfig::getRef().getDockerID())
            {

                LOGT("Docker::toService  ServiceClient sendToSession (client) " << trace 
                    << ", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                    << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
                sendToSession(service.getClientSessionID(), block, len);

            }
            else
            {
                LOGT("Docker::toService  ServiceClient ForwardToRealClient " << trace
                    << ", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                    << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
                sendToDocker(service.getClientDockerID(), service.getClientSessionID(), block, len);
            }

        }
        else if (needPost)
        {
            LOGT("Docker::toService local post process4bind " << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
            std::string bk;
            bk.assign(block, len);
            SessionManager::getRef().post(std::bind(&Service::process4bind, fder->second, trace, std::move(bk)));
        }
        else
        {
            LOGT("Docker::toService  local process " << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);
            fder->second->process(trace, block, len);
        }
    }

}



bool Docker::isHadService(ServiceType serviceType, ServiceID serviceID)
{
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        return false;
    }
    auto fder = founder->second.find(serviceID);
    if (fder == founder->second.end())
    {
        return false;
    }
    return true;
}






