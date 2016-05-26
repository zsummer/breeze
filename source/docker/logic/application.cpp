#include "../config.h"
#include "application.h"
#include "dbService.h"
#include "userMgrService.h"
#include "userService.h"
#include "shellService.h"
#include <ProtoUser.h>
int g_closeState = 0;

Application::Application()
{

}

bool Application::init(const std::string & config, DockerID idx)
{
    if (!ServerConfig::getRef().parse(config, idx))
    {
        LOGE("Application::init error. parse config error. config path=" << config << ", docker ID = " << idx);
        return false;
    }
    if (idx == InvalidDockerID)
    {
        LOGE("Application::init error. current docker id invalid. config path=" << config << ", docker ID = " << idx);
        return false;
    }
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._docker == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Application::init error. current docker id not found in config file.. config path=" << config << ", docker ID = " << idx);
        return false;
    }
    LOGA("Application::init  success. dockerID=" << idx);
    SessionManager::getRef().createTimer(1000, std::bind(&Application::checkServiceState, Application::getPtr()));
    return true;
}
void sigInt(int sig)
{
    if (g_closeState == 0)
    {
        g_closeState = 1;
        SessionManager::getRef().post(std::bind(&Application::stop, Application::getPtr()));
    }
}

void Application::onCheckSafeExit()
{
    LOGA("Application::onCheckSafeExit. checking.");
    if (_wlisten != InvalidAccepterID)
    {
        auto &options = SessionManager::getRef().getAccepterOptions(_wlisten);
        if (options._currentLinked != 0)
        {
            SessionManager::getRef().createTimer(1000, std::bind(&Application::onCheckSafeExit, this));
            return;
        }
    }
    if (g_closeState == 1)
    {
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
        LOGA("Application::onNetworkStoped. service all closed.");
        SessionManager::getRef().stopAccept();
        SessionManager::getRef().kickClientSession();
        SessionManager::getRef().kickConnect();
        SessionManager::getRef().stop();
    }
    else
    {
        SessionManager::getRef().createTimer(1000, std::bind(&Application::onCheckSafeExit, this));
    }
}
bool Application::run()
{
    SessionManager::getRef().run();
    LOGA("Application::run exit!");
    return true;
}

bool Application::isStoping()
{
    return g_closeState != 0;
}

void Application::stop()
{
    SessionManager::getRef().stopAccept();
    if (_wlisten != InvalidAccepterID)
    {
        SessionManager::getRef().kickClientSession(_wlisten);
    }
    onCheckSafeExit();
    return ;
}

bool Application::startDockerListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    ServerConfig::getRef().getDockerID();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._docker == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Application::startDockerListen error. current docker id not found in config file." );
        return false;
    }
    const DockerConfig & docker = *founder;
    if (docker._serviceBindIP.empty() || docker._servicePort == 0)
    {
        LOGE("Application::startDockerListen check config error. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort);
        return false;
    }
    AccepterID aID = SessionManager::getRef().addAccepter(docker._serviceBindIP, docker._servicePort);
    if (aID == InvalidAccepterID)
    {
        LOGE("Application::startDockerListen addAccepter error. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort);
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
    options._sessionOptions._onBlockDispatch = std::bind(&Application::event_onServiceMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(aID))
    {
        LOGE("Application::startDockerListen openAccepter error. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort);
        return false;
    }
    LOGA("Application::startDockerListen openAccepter success. bind ip=" << docker._serviceBindIP << ", bind port=" << docker._servicePort <<", aID=" << aID);
    return true;
}
bool Application::startDockerConnect()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    for (const auto & docker : dockers)
    {
        SessionID cID = SessionManager::getRef().addConnecter(docker._serviceIP, docker._servicePort);
        if (cID == InvalidSessionID)
        {
            LOGE("Application::startDockerConnect addConnecter error. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort);
            return false;
        }
        auto session = SessionManager::getRef().getTcpSession(cID);
        if (!session)
        {
            LOGE("Application::startDockerConnect addConnecter error.  not found connect session. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort << ", cID=" << cID);
            return false;
        }
        auto &options = session->getOptions();
        options._onSessionLinked = std::bind(&Application::event_onServiceLinked, this, _1);
        options._onSessionClosed = std::bind(&Application::event_onServiceClosed, this, _1);
        options._onBlockDispatch = std::bind(&Application::event_onServiceMessage, this, _1, _2, _3);
        options._reconnects = 50;
        options._connectPulseInterval = 5000;
        options._reconnectClean = false;
        options._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if (last != 0 && getNowTime() - (time_t)last > 30000)
            {
                LOGE("options._onSessionPulse check timeout failed. diff time=" << getNowTime() - (time_t)last);
                session->close();
            }
        };

        if (!SessionManager::getRef().openConnecter(cID))
        {
            LOGE("Application::startDockerConnect openConnecter error. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort << ", cID=" << cID);
            return false;
        }
        LOGA("Application::startDockerConnect success. remote ip=" << docker._serviceIP << ", remote port=" << docker._servicePort << ", cID=" << cID);
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_TRUST);
        session->setUserParam(UPARAM_REMOTE_CLUSTER, docker._docker);
        _dockerSession[docker._docker] = std::make_pair(cID, 0);
        for (ui16 i = ServiceInvalid; i <= ServiceMax; i++)
        {
            _services.insert(std::make_pair(i, std::unordered_map<ServiceID, ServicePtr >()));
        }
        for (auto st : docker._services)
        {
            if (!createService(st, InvalidServiceID, docker._docker, docker._docker != ServerConfig::getRef().getDockerID(), InvalidSessionID,true))
            {
                return false;
            }
        }
    }
    return true;
}
bool Application::startWideListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfig();
    ServerConfig::getRef().getDockerID();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._docker == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Application::startWideListen error. current docker id not found in config file.");
        return false;
    }
    const DockerConfig & docker = *founder;
    if (!docker._wideIP.empty() && docker._widePort != 0)
    {
        AccepterID aID = SessionManager::getRef().addAccepter("0.0.0.0", docker._widePort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Application::startWideListen addAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        options._whitelistIP = docker._whiteList;
        options._maxSessions = 5000;
        options._sessionOptions._sessionPulseInterval = 10000;
        options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if (getNowTime() - (time_t)last > 45000)
            {
                LOGE("options._onSessionPulse check timeout failed. diff time=" << getNowTime() - (time_t)last);
                session->close();
            }
        };
        options._sessionOptions._onSessionLinked = std::bind(&Application::event_onClientLinked, this, _1);
        options._sessionOptions._onSessionClosed = std::bind(&Application::event_onClientClosed, this, _1);
        options._sessionOptions._onBlockDispatch = std::bind(&Application::event_onClientMessage, this, _1, _2, _3);
        if (!SessionManager::getRef().openAccepter(aID))
        {
            LOGE("Application::startWideListen openAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort);
            return false;
        }
        LOGA("Application::startWideListen openAccepter success. bind ip=0.0.0.0, show wide ip=" << docker._wideIP << ", bind port=" << docker._widePort << ", listen aID=" << aID);
        _wlisten = aID;
    }
    return true;
}

bool Application::start()
{
    return startDockerListen() && startDockerConnect() && startWideListen();
}






void Application::event_onServiceLinked(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_CLUSTER);
    auto founder = _dockerSession.find(ci);
    if (founder == _dockerSession.end())
    {
        LOGE("event_onServiceLinked error cID=" << session->getSessionID() << ", dockerID=" << ci);
        return;
    }
    LOGI("event_onServiceLinked cID=" << session->getSessionID() << ", dockerID=" << ci);
    founder->second.second = 1;
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
                CreateServiceNotice notice(svc.second->getServiceType(), svc.second->getServiceID(), svc.second->getDockerID(), svc.second->getClientID());
                Application::getRef().broadcast(notice);
            }
        }
    }
    checkServiceState();
}

void Application::event_onServiceClosed(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_CLUSTER);
    auto founder = _dockerSession.find(ci);
    if (founder == _dockerSession.end())
    {
        LOGE("event_onServiceClosed error cID=" << session->getSessionID() << ", dockerID=" << ci);
        return;
    }
    LOGW("event_onServiceClosed cID=" << session->getSessionID() << ", dockerID=" << ci);
    founder->second.second = 0;
}

bool Application::destroyService(ui16 serviceType, ServiceID serviceID)
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
    founder->second.erase(fder);
    return true;
}

bool Application::createService(ui16 serviceType, ServiceID serviceID, DockerID dockerID, SessionID clientID, bool isShell, bool failExit)
{
    ServicePtr & service = _services[serviceType][InvalidServiceID];
    if (service)
    {
        LOGE("Application::createService error. service alread exist. serviceType=" << serviceType << ", serviceID="
            << serviceID << ", dockerID=" << dockerID << ", isShell=" << isShell << ", failExit=" << failExit);
        if (failExit)
        {
            goto goExit;
        }
        return false;
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
        return false;
    }
    service->setServiceType(serviceType);
    service->setServiceID(serviceID);
    service->setDockerID(dockerID);
    service->setClientID(clientID);
    service->setStatus(SS_CREATED);


    return true;
goExit:
    Application::getRef().stop();
    return false;
}

void Application::checkServiceState()
{
    SessionManager::getRef().createTimer(1000, std::bind(&Application::checkServiceState, Application::getPtr()));
    if (!_dockerNetWorking)
    {
        for (auto & c : _dockerSession)
        {
            if (c.second.second == 0)
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
                    Application::getRef().stop();
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
                        LOGI("local service [" << ServiceNames.at(service.second->getServiceType()) << "] inited. [" << service.second->getServiceID() << "] ...");
                    }
                    else
                    {
                        LOGE("local service [" << ServiceNames.at(service.second->getServiceType()) << "]  init error.[" << service.second->getServiceID() << "] ...");
                        Application::getRef().stop();
                        return;
                    }
                    return;
                }
                if (service.second->getStatus() == SS_DESTROY || service.second->getStatus() == SS_UNINITING)
                {
                    LOGE("local service [" << ServiceNames.at(service.second->getServiceType()) << "]  init error.[" << service.second->getServiceID() << "] ...");
                    Application::getRef().stop();
                    return;
                }
            }
        }
        LOGA("all service worked.");
        _dockerServiceWorking = true;

    }
   
}
void Application::event_onRemoteShellForward(TcpSessionPtr session, ReadStream & rs)
{
    Tracing trace;
    rs >> trace;
    auto founder = _services.find(trace._toService);
    if (founder == _services.end())
    {
        LOGE("Application::event_onRemoteShellForward error. unknown service. trace=" << trace);
        return;
    }
    auto fder = founder->second.find(trace._toServiceID);
    if (fder == founder->second.end())
    {
        LOGE("Application::event_onRemoteShellForward error. not found service id. trace=" << trace);
        return;
    }
    Service & svc = *fder->second;
    if (svc.isShell())
    {
        LOGE("Application::event_onRemoteShellForward error. service not local. trace=" << trace);
        return;
    }
    svc.process(trace, rs.getStreamUnread(), rs.getStreamUnreadLen());
}

void Application::event_onCreateServiceInDocker(TcpSessionPtr session, ReadStream & rs)
{
    CreateServiceNotice service;
    rs >> service;

    auto founder = _services.find(service.serviceType);
    if (founder == _services.end())
    {
        LOGE("event_onServiceMessage can't founder remote service. service=" << ServiceNames.at(service.serviceType));
        return;
    }
    auto fder = founder->second.find(service.serviceID);
    if (fder == founder->second.end() || !fder->second)
    {
        LOGE("event_onServiceMessage can't founder remote service with id. service=" << ServiceNames.at(service.serviceType) << ", id=" << service.serviceID);
        return;
    }
    if (fder->second->isShell() && fder->second->getStatus() != SS_WORKING)
    {
        LOGI("remote service [" << ServiceNames.at(fder->second->getServiceType()) << "]begin init. [" << fder->second->getServiceID() << "] ...");
        fder->second->setStatus(SS_WORKING);  //serviceShell
        LOGI("remote service [" << ServiceNames.at(fder->second->getServiceType()) << "] inited. [" << fder->second->getServiceID() << "] ...");
        checkServiceState();
    }
}

void Application::event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);
    if (rsShell.getProtoID() == DockerPulse::getProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    if (rsShell.getProtoID() == CreateServiceNotice::getProtoID())
    {
        event_onCreateServiceInDocker(session, rsShell);
        return;
    }
    if (rsShell.getProtoID() == ShellForward::getProtoID())
    {
        event_onRemoteShellForward(session, rsShell);
        return;
    }
    if (rsShell.getProtoID() == ClientForward::getProtoID())
    {
        Tracing trace;
        rsShell >> trace;
        ReadStream rs(rsShell.getStreamUnread(), rsShell.getStreamUnreadLen());
        if (rs.getProtoID() == UserAuthResp::getProtoID())
        {
            UserAuthResp resp;
            rs >> resp;
            auto client = SessionManager::getRef().getTcpSession(resp.clientSessionID);
            if (client)
            {
                if (resp.retCode == EC_SUCCESS)
                {
                    client->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_AUTHED);
                }
                else
                {
                    client->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
                }
                ClientAuthResp clientresp;
                clientresp.retCode = resp.retCode;
                clientresp.account = resp.account;
                clientresp.token = resp.token;
                clientresp.previews = resp.previews;
                WriteStream ws(ClientAuthResp::getProtoID());
                ws << clientresp;
                client->send(ws.getStream(), ws.getStreamLen());
            }
            return;
        }
        else
        {
            auto founder = _services.find(ServiceUser);
            if (founder == _services.end())
            {
                LOGW("not have any client.");
                return;
            }
            auto fder = founder->second.find(trace._toServiceID);
            if (fder == founder->second.end())
            {
                LOGW("not have the client.");
                return;
            }
            fder->second->process(trace, rsShell.getStreamUnread(), rsShell.getStreamUnreadLen());
        }
    }
    
}




void Application::event_onClientPulse(TcpSessionPtr session)
{
    if (isSessionID(session->getSessionID()))
    {
        if (time(NULL) - session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME) > session->getOptions()._sessionPulseInterval / 1000 * 2)
        {
            session->close();
            return;
        }
    }
}






void Application::event_onClientLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
    LOGD("Application::event_onClientLinked. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}

void Application::event_onClientClosed(TcpSessionPtr session)
{
    LOGD("Application::event_onClientClosed. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
    if (isConnectID(session->getSessionID()))
    {
    }
    else
    {
        if (session->getUserParamNumber(UPARAM_SESSION_STATUS) == SSTATUS_LOGINED)
        {

        }

    }
}



void Application::event_onClientMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    SessionStatus ss = (SessionStatus) session->getUserParamNumber(UPARAM_SESSION_STATUS);
    if (rs.getProtoID() == ClientAuthReq::getProtoID())
    {
        LOGD("ClientAuthReq sID=" << session->getSessionID() << ", block len=" << len);
        if (ss != SSTATUS_UNKNOW)
        {
            LOGE("duplicate ClientAuthReq. sID=" << session->getSessionID());
            return;
        }
        ClientAuthReq careq;
        rs >> careq;
        Tracing trace;
        trace._fromService = ServiceClient;
        trace._fromServiceID = session->getSessionID();
        trace._toService = ServiceUserMgr;
        trace._toServiceID = InvalidServiceID;
        WriteStream ws(UserAuthReq::getProtoID());
        UserAuthReq req;
        req.account = careq.account;
        req.token = careq.token;
        req.clientSessionID = session->getSessionID();
        req.clientDockerID = ServerConfig::getRef().getDockerID();
        ws << req;
        callOtherService(trace, ws.getStream(), ws.getStreamLen());
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_AUTHING);
        return;
    }

}

void Application::callOtherDocker(DockerID cltID, const char * block, unsigned int len)
{
    auto founder = _dockerSession.find(cltID);
    if (founder == _dockerSession.end())
    {
        LOGF("Application::callOtherDocker fatal error. cltID not found. cltID=" << cltID);
        return;
    }
    if (founder->second.first == InvalidServiceID)
    {
        LOGF("Application::callOtherDocker fatal error. cltID not have session. cltID=" << cltID);
        return;
    }
    if (founder->second.second == 0)
    {
        LOGW("Application::callOtherDocker warning error. session try connecting. cltID=" << cltID << ", client session ID=" << founder->second.first);
    }
    SessionManager::getRef().sendSessionData(founder->second.first, block, len);
}

void Application::callOtherService(Tracing trace, const char * block, unsigned int len)
{
    if (trace._fromService >= ServiceMax || trace._toService >= ServiceMax || trace._toService == ServiceInvalid)
    {
        LOGF("Application::callOtherService Illegality trace. trace=" << trace << ", block len=" << len);
        return;
    }

    ui16 toService = trace._toService;
    if (trace._toService == ServiceUser && trace._toService == ServiceClient)
    {
        toService = ServiceUserMgr;
    }

    auto founder = _services.find(toService);
    if (founder == _services.end())
    {
        LOGF("Application::callOtherService can not found _toService type  trace =" << trace << ", block len=" << len);
        return;
    }
    auto fder = founder->second.find(trace._toServiceID);
    if (fder == founder->second.end())
    {
        LOGD("Application::callOtherService can not found _toService ID. trace =" << trace << ", block len=" << len);
        return;
    }
    auto & service = *fder->second;
    if (service.isShell()) //forward 
    {
        WriteStream ws(ShellForward::getProtoID());
        ws << trace;
        ws.appendOriginalData(block, len);
        DockerID cltID = service.getDockerID();
        auto fsder = _dockerSession.find(cltID);
        if (fsder == _dockerSession.end())
        {
            LOGE("Application::callOtherService not found session by shell service. dockerID=" << cltID << ", tracing=" << trace);
        }
        else
        {
            SessionManager::getRef().sendSessionData(fsder->second.first, ws.getStream(), ws.getStreamLen());
            if (fsder->second.second == 0)
            {
                LOGW("Application::callOtherService session not connected when global call by shell service. sID=" << fsder->second.first
                    << ", dockerID=" << cltID << ", tracing=" << trace);
            }
        }
    }
    else //direct process
    {
        std::string bk;
        bk.assign(block, len);
        SessionManager::getRef().post(std::bind(&Service::process4bind, fder->second, trace, std::move(bk)));
    }

}







