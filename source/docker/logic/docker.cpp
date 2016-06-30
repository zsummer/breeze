
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
#include <ProtoDocker.h>



Docker::Docker()
{

}

bool Docker::init(const std::string & configName, DockerID configID)
{
    if (!ServerConfig::getRef().parseDB(configName) || !ServerConfig::getRef().parseDocker(configName, configID))
    {
        LOGE("Docker::init error. parse config error. config path=" << configName << ", docker ID = " << configID);
        return false;
    }
    if (configID == InvalidDockerID)
    {
        LOGE("Docker::init error. current docker id invalid. config path=" << configName << ", docker ID = " << configID);
        return false;
    }
    if (!DBDict::getRef().initHelper())
    {
        LOGE("Docker::init error. DBDict initHelper error. ");
        return false;
    }
    
    if (!DBDict::getRef().load())
    {
        LOGE("Docker::init error. DBDict load error. ");
        return false;
    }

    const auto & dockers = ServerConfig::getRef().getDockerConfigs();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::init error. current docker id not found in config file.. config path=" << configName << ", docker ID = " << configID);
        return false;
    }
    LOGA("Docker::init  success. dockerID=" << configID);
    SessionManager::getRef().createTimer(10, std::bind(&Docker::buildCluster, Docker::getPtr()));
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
    LOGA("Docker::stop  broadcast all docker. ");
}

void Docker::destroyCluster()
{
    LOGA("Docker::destroyCluster. checking ....");

    bool safe =  true;
    for (auto &second : _services)
    {
        if (second.first == STClient || second.first == InvalidServiceType )
        {
            continue;
        }
        for (auto & svc : second.second)
        {
            if (true)
            {
                if (getServiceTrait(svc.second->getServiceType()) != STrait_Heterogenous)
                {
                    safe = false;
                }
            }
            
            if (svc.second->isShell())
            {
                continue;
            }
            if (svc.second->getStatus() != SS_WORKING)
            {
                continue;
            }


            if (getServiceTrait(svc.second->getServiceType()) == STrait_Multi && svc.second->getClientSessionID() == InvalidSessionID)
            {
                LOGI("unload service [" << svc.second->getServiceName() << "] ..");
                svc.second->setStatus(SS_UNLOADING);
                svc.second->onUnload();
            }
            else
            {
                auto subs = getServiceSubsidiary(svc.second->getServiceType());
                bool allsubsDestroy = true;
                for (auto sub : subs)
                {
                    auto ss = peekService(sub);
                    if (!ss.empty())
                    {
                        auto checkHeterogenous = ss.begin();
                        if (getServiceTrait(checkHeterogenous->second->getServiceType()) != STrait_Heterogenous)
                        {
                            allsubsDestroy = false;
                            break;
                        }
                    }
                }
                if (allsubsDestroy)
                {
                    LOGI("unload service [" << svc.second->getServiceName() << "] ..");
                    svc.second->setStatus(SS_UNLOADING);
                    svc.second->onUnload();
                }
            }
        }
    }

    if(safe)
    {
        LOGA("------------------------------------------------------");
        LOGA("all services closed.");
        LOGA("------------------------------------------------------");
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
    const auto & dockers = ServerConfig::getRef().getDockerConfigs();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::startDockerListen error. current docker id not found in config file." );
        return false;
    }
    const DockerConfig & docker = *founder;
    if (docker._dockerListenHost.empty() || docker._dockerListenPort == 0)
    {
        LOGE("Docker::startDockerListen check config error. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort);
        return false;
    }
    AccepterID aID = SessionManager::getRef().addAccepter(docker._dockerListenHost, docker._dockerListenPort);
    if (aID == InvalidAccepterID)
    {
        LOGE("Docker::startDockerListen addAccepter error. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(aID);
    options._whitelistIP = docker._dockerWhite;
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
        LOGE("Docker::startDockerListen openAccepter error. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort);
        return false;
    }
    LOGA("Docker::startDockerListen openAccepter success. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort <<", aID=" << aID);
    return true;
}
bool Docker::startDockerConnect()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfigs();
    for (const auto & docker : dockers)
    {
        SessionID cID = SessionManager::getRef().addConnecter(docker._dockerPubHost, docker._dockerListenPort);
        if (cID == InvalidSessionID)
        {
            LOGE("Docker::startDockerConnect addConnecter error. remote ip=" << docker._dockerPubHost << ", remote port=" << docker._dockerListenPort);
            return false;
        }
        auto session = SessionManager::getRef().getTcpSession(cID);
        if (!session)
        {
            LOGE("Docker::startDockerConnect addConnecter error.  not found connect session. remote ip=" << docker._dockerPubHost << ", remote port=" << docker._dockerListenPort << ", cID=" << cID);
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
            LOGE("Docker::startDockerConnect openConnecter error. remote ip=" << docker._dockerPubHost << ", remote port=" << docker._dockerListenPort << ", cID=" << cID);
            return false;
        }
        LOGA("Docker::startDockerConnect success. remote ip=" << docker._dockerPubHost << ", remote port=" << docker._dockerListenPort << ", cID=" << cID);
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_TRUST);
        session->setUserParam(UPARAM_REMOTE_DOCKERID, docker._dockerID);
        auto &ds = _dockerSession[docker._dockerID];
        ds.dokerID = docker._dockerID;
        ds.sessionID = cID;
    }
    const auto & stc = ServerConfig::getRef().getServiceLoadDockers();
    for (auto sd: ServiceDepends)
    {
        _services.insert(std::make_pair(sd.first, std::unordered_map<ServiceID, ServicePtr >()));
        if (getServiceTrait(sd.first) == STrait_Single || 
            (getServiceTrait(sd.first) == STrait_Heterogenous  && !ServerConfig::getRef().getServiceLoadDockers().at(sd.first).empty()))
        {
            if (!createService(stc.at(sd.first).front(), sd.first, InvalidServiceID, getServiceName(sd.first),
                InvalidDockerID, InvalidSessionID, stc.at(sd.first).front() != ServerConfig::getRef().getDockerID(), true))
            {
                return false;
            }
        }
    }

    
    return true;
}
bool Docker::startDockerWideListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfigs();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::startDockerWideListen error. current docker id not found in config file.");
        return false;
    }
    const DockerConfig & docker = *founder;
    if (!docker._clientPubHost.empty() && docker._clientPubPort != 0)
    {
        AccepterID aID = SessionManager::getRef().addAccepter("0.0.0.0", docker._clientPubPort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Docker::startDockerWideListen addAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        //options._whitelistIP;// = docker._dockerWhite;
        options._maxSessions = 5000;
        options._sessionOptions._sessionPulseInterval = 40000;
        options._sessionOptions._onSessionPulse = std::bind(&Docker::event_onClientPulse, this, _1);
        options._sessionOptions._onSessionLinked = std::bind(&Docker::event_onClientLinked, this, _1);
        options._sessionOptions._onSessionClosed = std::bind(&Docker::event_onClientClosed, this, _1);
        options._sessionOptions._onBlockDispatch = std::bind(&Docker::event_onClientMessage, this, _1, _2, _3);
        if (!SessionManager::getRef().openAccepter(aID))
        {
            LOGE("Docker::startDockerWideListen openAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort);
            return false;
        }
        LOGA("Docker::startDockerWideListen openAccepter success. bind ip=0.0.0.0, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort << ", listen aID=" << aID);
        _widelisten = aID;
    }
    return true;
}

bool Docker::startDockerWebListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfigs();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc) {return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("Docker::startDockerWebListen error. current docker id not found in config file.");
        return false;
    }
    const DockerConfig & docker = *founder;
    if (!docker._webPubHost.empty() && docker._webPubPort != 0)
    {
        AccepterID aID = SessionManager::getRef().addAccepter("0.0.0.0", docker._webPubPort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Docker::startDockerWebListen addAccepter error. bind ip=0.0.0.0, show web ip=" << docker._webPubHost << ", bind port=" << docker._webPubPort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        options._sessionOptions._protoType = PT_HTTP;
        //options._whitelistIP;// = docker._dockerWhite;
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
            LOGE("Docker::startDockerWebListen openAccepter error. bind ip=0.0.0.0, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort);
            return false;
        }
        LOGA("Docker::startDockerWebListen openAccepter success. bind ip=0.0.0.0, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort << ", listen aID=" << aID);
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
    DockerConfig dc;
    if (true)
    {
        const auto & configs = ServerConfig::getRef().getDockerConfigs();
        for (const auto & ci : configs)
        {
            if (ci._dockerID == founder->second.dokerID)
            {
                dc = ci;
                break;
            }
        }
    }
    if (true)
    {
        if (std::find_if(dc._services.begin(), dc._services.end(), [](ServiceType st) {return st == STUser; }) != dc._services.end())
        {
            LOGA("_userBalance.enableNode dockerID=" << dc._dockerID);
            _userBalance.enableNode(dc._dockerID);
        }
    }
    if (true)
    {
        if (!dc._webPubHost.empty() && dc._webPubPort != 0)
        {
            LOGA("_userBalance.enableNode dockerID=" << dc._dockerID << ", port=" << dc._webPubPort);
            _webBalance.enableNode(dc._dockerID);
        }
    }
    if (true)
    {
        SelfBeingPulse pulse(ServerConfig::getRef().getAreaID(), ServerConfig::getRef().getDockerID());
        sendToSession(session->getSessionID(), pulse);
    }

    LoadServiceNotice notice;
    for (auto & second : _services)
    {
        if (second.first == STClient  || getServiceTrait(second.first) == STrait_Multi || getServiceTrait(second.first) == Strait_None || second.first == InvalidServiceType)
        {
            continue;
        }

        for (auto & svc : second.second )
        {
            if (!svc.second->isShell() && svc.second->getStatus() == SS_WORKING )
            {
                notice.shellServiceInfos.push_back(ShellServiceInfo(
                    svc.second->getServiceDockerID(),
                    svc.second->getServiceType(),
                    svc.second->getServiceID(),
                    svc.second->getServiceName(),
                    svc.second->getStatus(),
                    svc.second->getClientDockerID(),
                    svc.second->getClientSessionID()));
            }
        }
    }
    sendToSession(session->getSessionID(), notice);
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
    DockerConfig dc;
    if (true)
    {
        const auto & configs = ServerConfig::getRef().getDockerConfigs();
        for (const auto & ci : configs)
        {
            if (ci._dockerID == founder->second.dokerID)
            {
                dc = ci;
                break;
            }
        }
    }

    if (true)
    {
        if (std::find_if(dc._services.begin(), dc._services.end(), [](ServiceType st) {return st == STUser; }) != dc._services.end())
        {
            LOGW("_userBalance.disableNode dockeriD=" << ci);
            _userBalance.disableNode(ci);
        }
    }
    if (true)
    {
        if (!dc._webPubHost.empty() && dc._webPubPort != 0)
        {
            LOGW("_webBalance.disableNode dockeriD=" << dc._dockerID << ", webPort=" << dc._webPubPort);
            _webBalance.disableNode(dc._dockerID);
        }
    }

}



void Docker::event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);

    if (rsShell.getProtoID() == SelfBeingPulse::getProtoID())
    {
        SelfBeingPulse pulse;
        rsShell >> pulse;
        LOGA("event_onServiceMessage sessionID=" << session->getSessionID()
            << ", areaID=" << pulse.areaID << ", dockerID=" << pulse.dockerID);
        session->setUserParam(UPARAM_AREA_ID, pulse.areaID);
    }
    else if (rsShell.getProtoID() == DockerPulse::getProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    else if (rsShell.getProtoID() == ShutdownClusterServer::getProtoID())
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






void Docker::destroyService(ServiceType serviceType, ServiceID serviceID)
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

ServicePtr Docker::createService(DockerID serviceDockerID, ServiceType serviceType, ServiceID serviceID, ServiceName serviceName, DockerID clientDockerID, SessionID clientSessionID, bool isShell, bool failExit)
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
        LOGE("Docker::createService error. service alread exist. serviceName=" << serviceName << ", serviceID="
            << serviceID << ", serviceDockerID=" << serviceDockerID << ", clientDockerID=" << clientDockerID << ", clientSessionID=" << clientSessionID
            << ", isShell=" << isShell << ", failExit=" << failExit << zsummer::traceback());
        if (failExit)
        {
            goto goExit;
        }
        return nullptr;
    }
    if (isShell || getServiceTrait(serviceType) == STrait_Heterogenous)
    {
        service = std::make_shared<ShellService>();
        service->setShell(isShell);
    }
    else if (serviceType == STInfoDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (serviceType == STLogDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (serviceType == STUserMgr)
    {
        service = std::make_shared<UserMgrService>();
    }
    else if (serviceType == STUser)
    {
        service = std::make_shared<UserService>();
    }
    else if (serviceType == STWebAgent)
    {
        service = std::make_shared<WebService>();
    }
    else if (serviceType == STOfflineMgr)
    {
        service = std::make_shared<OfflineService>();
    }
    else if (serviceType == STMinitorMgr)
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

    if (!_dockerServiceWorking)
    {
        for (auto sd : ServiceDepends)
        {
            if (getServiceTrait(sd.first) != STrait_Single && getServiceTrait(sd.first) != STrait_Heterogenous)
            {
                continue;
            }
            if (getServiceTrait(sd.first) == STrait_Heterogenous && ServerConfig::getRef().getServiceLoadDockers().at(sd.first).empty())
            {
                continue;
            }
            auto service = peekService(sd.first, InvalidServiceID);
            if (!service)
            {
                LOGE("nullptr ");
                Docker::getRef().forceStop();
                return;
            }

            if (!service->isShell() && service->getStatus() == SS_INITING)
            {
                LOGD("waiting local service[" << service->getServiceName() << "] initing.. ");
                return;
            }
            if (!service->isShell() && service->getStatus() == SS_CREATED)
            {
                bool doInit = true;
                do 
                {
                    auto depends = getServiceDepends(service->getServiceType());
                    if (depends.empty())
                    {
                        break;
                    }
                    for (auto tp : depends)
                    {
                        auto dps = peekService(tp, InvalidServiceID);
                        if (dps && dps->getStatus() != SS_WORKING)
                        {
                            doInit = false;
                            break;
                        }
                    }
                } while (false);
                if (!doInit)
                {
                    continue;
                }

                LOGI("begin call service [" << service->getServiceName() << "].onLoad() ...");
                service->setStatus(SS_INITING);
                bool ret = service->onLoad();
                if (ret)
                {
                    LOGI("end call service [" << service->getServiceName() << "].onLoad()");
                    service->createTimer(1000, -1, 1000, true, std::bind(&Service::onTick, service, _1, _2, _3));
                }
                else
                {
                    LOGI("error call service [" << service->getServiceName() << "].onLoad()");
                    Docker::getRef().forceStop();
                    return;
                }
                return;
            }
        }

        for (auto sd : ServiceDepends)
        {
            if (getServiceTrait(sd.first) != STrait_Single && getServiceTrait(sd.first) != STrait_Heterogenous)
            {
                continue;
            }
            auto service = peekService(sd.first, InvalidServiceID);
            if (!service && getServiceTrait(sd.first) != STrait_Heterogenous)
            {
                LOGD("nullptr ");
                Docker::getRef().forceStop();
                return;
            }
            if (service && service->getStatus() != SS_WORKING)
            {
                return;
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
        LOGE("LoadServiceInDocker can't founder service type. service=" <<  getServiceName(service.serviceType));
        return;
    }
    auto ret = createService(ServerConfig::getRef().getDockerID(), service.serviceType, service.serviceID, service.serviceName, service.clientDockerID, service.clientSessionID, false, false);
    if (ret)
    {
        ret->onLoad();
    }
}

void Docker::event_onSwitchServiceClientNotice(TcpSessionPtr session, ReadStream & rs)
{
    SwitchServiceClientNotice change;
    rs >> change;
    LOGI("Docker::event_onSwitchServiceClientNotice type=" << change.serviceType << ", id=" << change.serviceID);
    auto founder = _services.find(change.serviceType);
    if (founder == _services.end())
    {
        LOGW("event_onSwitchServiceClientNotice can't founder service type. service=" << getServiceName(change.serviceType));
        return;
    }
    auto fder = founder->second.find(change.serviceID);
    if (fder == founder->second.end())
    {
        LOGW("event_onSwitchServiceClientNotice can't founder service id. service=" << getServiceName(change.serviceType) << ", id=" << change.serviceID);
        return;
    }
    if (fder->second->getClientSessionID() != InvalidSessionID && !fder->second->isShell())
    {
        KickRealClient kick(fder->second->getClientSessionID());
        Docker::getRef().sendToDocker(fder->second->getClientDockerID(), kick);
    }
    fder->second->setClientSessionID(change.clientSessionID);
    fder->second->setClientDockerID(change.clientDockerID);
    fder->second->onClientChange();



    if (getServiceTrait(fder->second->getServiceType()) == STrait_Multi && !fder->second->isShell())
    {
        RefreshServiceToMgrNotice refreshNotice;
        refreshNotice.shellServiceInfos.push_back( ShellServiceInfo(
            fder->second->getServiceDockerID(),
            fder->second->getServiceType(),
            fder->second->getServiceID(),
            fder->second->getServiceName(),
            fder->second->getStatus(),
            fder->second->getClientDockerID(),
            fder->second->getClientSessionID()));
        for (auto sd : ServiceDepends)
        {
            if (getServiceTrait(sd.first) == STrait_Single)
            {
                fder->second->toService(sd.first, refreshNotice, nullptr);
            }
        }
    }
}



void Docker::event_onLoadServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    LoadServiceNotice service;
    rs >> service;
    for (const auto & si : service.shellServiceInfos)
    {
        LOGI("Docker::event_onLoadServiceNotice type=" << si.serviceType
            << ", name=" << si.serviceName << ", id=" << si.serviceID);

        auto founder = _services.find(si.serviceType);
        if (founder == _services.end())
        {
            LOGE("event_onLoadServiceNotice can't founder remote service. service=" << getServiceName(si.serviceType));
            return;
        }
        auto servicePtr = createService(si.serviceDockerID, si.serviceType, si.serviceID,
            si.serviceName, si.clientDockerID, si.clientSessionID, true, false);
        if (servicePtr)
        {
            servicePtr->setStatus(SS_WORKING);
        }
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
        LOGE("event_onUnloadServiceInDocker can't founder remote service. service=" << getServiceName(service.serviceType));
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
        LOGE("event_onUnloadedServiceNotice can't founder remote service. service=" << getServiceName(service.serviceType));
        return;
    }
    destroyService(service.serviceType, service.serviceID);
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
        const auto & services = peekService(STUser);
        ServiceID serviceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        auto iter = services.find(serviceID);
        if (iter == services.end())
        {
            LOGE("SSTATUS_ATTACHED session not found service ID. service id=" << serviceID << ", session id=" << session->getSessionID());
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
            trace.fromServiceType = STClient;
            trace.fromServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
            trace.fromDockerID = ServerConfig::getRef().getDockerID();

            trace.toServiceType = STUserMgr;
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
        trace.fromServiceType = STClient;
        trace.fromServiceID = InvalidServiceID;
        trace.fromDockerID = ServerConfig::getRef().getDockerID();
        trace.toServiceType = STUserMgr;
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
        trace.fromServiceType = STClient;
        trace.fromServiceID = InvalidServiceID;
        trace.toServiceType = STUserMgr;
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
        trace.fromServiceType = STClient;
        trace.fromServiceID = InvalidServiceID;
        trace.toServiceType = STUserMgr;
        trace.toServiceID = InvalidServiceID;

        AttachUserFromUserMgrReq serviceReq;
        serviceReq.serviceID = clientReq.serviceID;
        serviceReq.account = session->getUserParamString(UPARAM_ACCOUNT);
        serviceReq.clientDockerID = ServerConfig::getRef().getDockerID();
        serviceReq.clientSessionID = session->getSessionID();
        toService(trace, serviceReq, true, true);
        return;
    }
    else if (rs.getProtoID() >= 40000 && sessionStatus == SSTATUS_ATTACHED )
    {
        LOGD("client other proto to user service. sID=" << session->getSessionID() << ", block len=" << len);
        Tracing trace;
        trace.fromServiceType = STClient;
        trace.fromServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        trace.toServiceType = STUser;
        trace.toServiceID = session->getUserParamNumber(UPARAM_SERVICE_ID);
        toService(trace, rs.getStream(), rs.getStreamLen(), true, true);
        return;
    }

    else
    {
        LOGE("client unknow proto or wrong status. protoID=" << rs.getProtoID() << ", status=" << sessionStatus << ", sessionID=" << session->getSessionID());
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
    trace.fromServiceType = InvalidServiceType;
    trace.fromServiceID = InvalidServiceID;

    trace.toDockerID = InvalidDockerID;
    trace.toServiceType = STWebAgent;
    trace.toServiceID = InvalidServiceID;
    toService(trace, notice, true, false);
}

void Docker::event_onWebServerRequest(TcpSessionPtr session, ReadStream & rs)
{
    WebServerRequest req;
    rs >> req;
    SessionID cID =  SessionManager::getRef().addConnecter(req.ip, req.port);
    if (cID == InvalidSessionID)
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
        wh.addHead("Host", req.host);
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
    SessionID sID = getDockerLinked(dockerID);
    if (sID == InvalidSessionID)
    {
        LOGF("Docker::sendToDocker fatal error. dockerID not linked. dockerID=" << dockerID);
        return;
    }
    sendToSession(sID, block, len);
}


void Docker::packetToDockerWithTracing(DockerID dockerID, const Tracing & trace, const char * block, unsigned int len)
{
    auto sID = getDockerLinked(dockerID);
    if (sID != InvalidSessionID)
    {
        packetToSessionWithTracing(sID, trace, block, len);
    }
    else
    {
        LOGE("Docker::packetToDockerWithTracing not found docker. dockerID=" << dockerID);
    }
}

void Docker::packetToClientViaDocker(DockerID dockerID, SessionID clientSessionID, const char * block, unsigned int len)
{
    auto sID = getDockerLinked(dockerID);
    if (sID != InvalidSessionID)
    {
        WriteStream ws(ForwardToRealClient::getProtoID());
        ws << clientSessionID;
        ws.appendOriginalData(block, len);
        sendToSession(sID, ws.getStream(), ws.getStreamLen());
    }
    else
    {
        LOGE("Docker::packetToClientViaDocker not found docker. dockerID=" << dockerID);
    }
}

void Docker::sendToDocker(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len)
{
    LOGT("Docker::sendToDocker serviceType=" << serviceType << ", serviceID=" << serviceID << ", block len=" << len);
    auto founder = _services.find(serviceType);
    if (founder == _services.end())
    {
        LOGE("Docker::sendToDocker error. type not found. serviceType=" << serviceType << ", serviceID=" << serviceID << ", block len=" << len);
        return;
    }
    auto fder = founder->second.find(serviceID);
    if (fder == founder->second.end())
    {
        LOGE("Docker::sendToDocker error. service id not found. serviceType=" << serviceType << ", serviceID=" << serviceID << ", block len=" << len);
        return;
    }
    sendToDocker(fder->second->getServiceDockerID(), block, len);
}






void Docker::toService(Tracing trace, const char * block, unsigned int len, bool canForwardToOtherService, bool needPost)
{
    try
    {
        ProtoID protoID = InvalidProtoID;
        if (true)
        {
            ReadStream rs(block, len);
            protoID = rs.getProtoID();
        }

        LOGT("Docker::toService " << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost);

        if (trace.toDockerID != InvalidDockerID) //Specified DockerID is high priority.
        {
            if (trace.toDockerID != ServerConfig::getRef().getDockerID())
            {
                packetToDockerWithTracing(trace.toDockerID, trace, block, len);
                return;
            }
            else
            {
                
                //return;
            }
        }
        ui16 toServiceType = trace.toServiceType;
        ServiceID toServiceID = trace.toServiceID;
        if (trace.toServiceType == STClient)
        {
            toServiceType = STUser;
        }


        auto founder = _services.find(toServiceType);
        if (founder == _services.end())
        {
            LOGF("Docker::toService can not found toServiceType type  trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
            return;
        }
        auto fder = founder->second.find(toServiceID);
        if (fder == founder->second.end())
        {
            if (toServiceType == STUser)
            {
                LOGW("Docker::toService can not found STUser ID. trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
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
            if (trace.toServiceType == STClient)
            {
                if (service.getClientDockerID() == InvalidDockerID || service.getClientSessionID() == InvalidSessionID)
                {
                    LOGW("Docker::toService  STClient sendToSession (client) warning. client dockerID or sessionID is Invalid "
                        <<", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                        << trace << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                }
                else if (service.getClientDockerID() == ServerConfig::getRef().getDockerID())
                {

                    LOGT("Docker::toService  STClient sendToSession (client) " << trace 
                        << ", clientDockerID=" << service.getClientDockerID() << ", clientSessionID=" << service.getClientSessionID()
                        << ", len=" << len << ", canForwardToOtherService=" << canForwardToOtherService << ", needPost=" << needPost << ", protoID=" << protoID);
                    sendToSession(service.getClientSessionID(), block, len);
                }
                else
                {
                    LOGT("Docker::toService  STClient ForwardToRealClient " << trace
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

SessionID Docker::getDockerLinked(DockerID dockerID)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder == _dockerSession.end() || founder->second.status == 0)
    {
        return InvalidSessionID;
    }

    return founder->second.sessionID;
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




