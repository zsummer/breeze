
#include "docker.h"
#include "dbService.h"
#include "avatarMgrService.h"
#include "avatarService.h"
#include "shellService.h"
#include "webService.h"
#include "monitorService.h"
#include "offlineService.h"
#include <ProtoClient.h>
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
    options._sessionOptions._sessionPulseInterval = (unsigned int)(ServerPulseInterval*1000);
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
        options._reconnects = 90000;
        options._connectPulseInterval = (unsigned int)(ServerPulseInterval * 1000);
        options._reconnectClean = false;
        options._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if(getFloatSteadyNowTime() - last >ServerPulseInterval *3.0)
            {
                LOGE("docker timeout . diff time=" << getFloatSteadyNowTime() - last << ", sessionID=" << session->getSessionID());
                session->close();
            }
        };

        if (!SessionManager::getRef().openConnecter(cID))
        {
            LOGE("Docker::startDockerConnect openConnecter error. remote ip=" << docker._dockerPubHost << ", remote port=" << docker._dockerListenPort << ", cID=" << cID);
            return false;
        }
        LOGA("Docker::startDockerConnect success. remote ip=" << docker._dockerPubHost << ", remote port=" << docker._dockerListenPort << ", cID=" << cID);
        session->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_TRUST);
        session->setUserParamInteger(UPARAM_REMOTE_DOCKERID, docker._dockerID);
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
            ServiceInfo si;
            si.serviceDockerID = stc.at(sd.first).front();
            si.serviceType = sd.first;
            si.serviceID = InvalidServiceID;
            si.serviceName = getServiceName(sd.first);
            si.clientDockerID = InvalidDockerID;
            si.clientSessionID = InvalidSessionID;
            si.status = SS_CREATED;

            if (!createService(si, stc.at(sd.first).front() != ServerConfig::getRef().getDockerID(), true))
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
        AccepterID aID = SessionManager::getRef().addAccepter("::", docker._clientPubPort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Docker::startDockerWideListen addAccepter error. bind ip=::, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        //options._whitelistIP;// = docker._dockerWhite;
        options._maxSessions = 5000;
        options._sessionOptions._sessionPulseInterval = (unsigned int)(ClientPulseInterval * 1000);
        options._sessionOptions._onSessionPulse = std::bind(&Docker::event_onClientPulse, this, _1);
        options._sessionOptions._onSessionLinked = std::bind(&Docker::event_onClientLinked, this, _1);
        options._sessionOptions._onSessionClosed = std::bind(&Docker::event_onClientClosed, this, _1);
        options._sessionOptions._onBlockDispatch = std::bind(&Docker::event_onClientMessage, this, _1, _2, _3);
        if (!SessionManager::getRef().openAccepter(aID))
        {
            LOGE("Docker::startDockerWideListen openAccepter error. bind ip=::, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort);
            return false;
        }
        LOGA("Docker::startDockerWideListen openAccepter success. bind ip=::, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort << ", listen aID=" << aID);
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
        AccepterID aID = SessionManager::getRef().addAccepter("::", docker._webPubPort);
        if (aID == InvalidAccepterID)
        {
            LOGE("Docker::startDockerWebListen addAccepter error. bind ip=::, show web ip=" << docker._webPubHost << ", bind port=" << docker._webPubPort);
            return false;
        }
        auto &options = SessionManager::getRef().getAccepterOptions(aID);
        options._sessionOptions._protoType = PT_HTTP;
        //options._whitelistIP;// = docker._dockerWhite;
        options._maxSessions = 200;
        options._sessionOptions._sessionPulseInterval = (unsigned int)(WebPulseTimeout * 1000);
        options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
        {
            auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
            if (getFloatSteadyNowTime() - last > ServerPulseInterval *3.0)
            {
                LOGW("web client timeout diff time=" << getFloatSteadyNowTime() - last << ", sessionID=" << session->getSessionID());
                session->close();
            }
        };
        options._sessionOptions._onSessionLinked = [](TcpSessionPtr session)
        {
            session->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
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
            LOGE("Docker::startDockerWebListen openAccepter error. bind ip=::, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort);
            return false;
        }
        LOGA("Docker::startDockerWebListen openAccepter success. bind ip=::, show wide ip=" << docker._clientPubHost << ", bind port=" << docker._clientPubPort << ", listen aID=" << aID);
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
    session->setUserParamNumber(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
    DockerID ci = (DockerID)session->getUserParamInteger(UPARAM_REMOTE_DOCKERID);
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
        if (std::find_if(dc._services.begin(), dc._services.end(), [](ServiceType st) {return st == STAvatar; }) != dc._services.end())
        {
            LOGA("_avatarBalance.enableNode dockerID=" << dc._dockerID);
            _avatarBalance.enableNode(dc._dockerID);
        }
    }
    if (true)
    {
        if (!dc._webPubHost.empty() && dc._webPubPort != 0)
        {
            LOGA("_avatarBalance.enableNode dockerID=" << dc._dockerID << ", port=" << dc._webPubPort);
            _webBalance.enableNode(dc._dockerID);
        }
    }
    if (true)
    {
        DockerKnock knock(ServerConfig::getRef().getAreaID(), ServerConfig::getRef().getDockerID());
        sendViaSessionID(session->getSessionID(), knock);
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
                notice.shellServiceInfos.push_back(ServiceInfo(
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
    sendViaSessionID(session->getSessionID(), notice);
    buildCluster();
}

void Docker::event_onServiceClosed(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamInteger(UPARAM_REMOTE_DOCKERID);
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
        if (std::find_if(dc._services.begin(), dc._services.end(), [](ServiceType st) {return st == STAvatar; }) != dc._services.end())
        {
            LOGW("_avatarBalance.disableNode dockeriD=" << ci);
            _avatarBalance.disableNode(ci);
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

    if (rsShell.getProtoID() == DockerKnock::getProtoID())
    {
        DockerKnock knock;
        rsShell >> knock;
        LOGA("event_onServiceMessage sessionID=" << session->getSessionID()
            << ", areaID=" << knock.areaID << ", dockerID=" << knock.dockerID);
        session->setUserParamInteger(UPARAM_AREA_ID, knock.areaID);
    }
    else if (rsShell.getProtoID() == DockerPulse::getProtoID())
    {
        session->setUserParamNumber(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
        return;
    }
    else if (rsShell.getProtoID() == ShutdownClusterServer::getProtoID())
    {
        LOGA("onShutdownClusterServer.. fromSessionID=" << session->getSessionID());
        onShutdown();
        return;
    }
    else if (rsShell.getProtoID() == LoadService::getProtoID())
    {
        event_onLoadService(session, rsShell);
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
    else if (rsShell.getProtoID() == KickClientsNotice::getProtoID())
    {
        event_onKickClientsNotice(session, rsShell);
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
    else if (rsShell.getProtoID() == ForwardToDocker::getProtoID())
    {
        event_onForwardToDocker(session, rsShell);
        return;
    }
    else if (rsShell.getProtoID() == WebServerRequest::getProtoID())
    {
        event_onWebServerRequest(session, rsShell);
    }
    else if (rsShell.getProtoID() == ReloadDBDictNotice::getProtoID())
    {
        size_t nowDate = getNowTime();
        double now = getFloatSteadyNowTime();
        DBDict::getRef().load();
        now = getFloatSteadyNowTime() - now;
        Tracing trace;
        trace.routing.toServiceType = STWebAgent;
        trace.routing.toServiceID = InvalidServiceID;
        trace.routing.traceBackID = InvalidServiceID;
        toService(trace, ReloadDBDictFinish(ServerConfig::getRef().getDockerID(), (double)nowDate, now));
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

ServicePtr Docker::createService(const ServiceInfo& si, bool isShell, bool failExit)
{
    if (isShell)
    {
        LOGI("Docker::createServic create local service: self dockerID=" << ServerConfig::getRef().getDockerID() << ",  serviceInfo=" << si  << ", isShell=" << isShell << ",faileExit=" << failExit);
    }
    else
    {
        LOGI("Docker::createServic create shell service: self dockerID=" << ServerConfig::getRef().getDockerID() << ",  serviceInfo=" << si << ", isShell=" << isShell << ",faileExit=" << failExit);
    }

    ServicePtr & service = _services[si.serviceType][si.serviceID];
    if (service)
    {
        LOGE("Docker::createServic service alread exist: self dockerID=" << ServerConfig::getRef().getDockerID() << ",  serviceInfo=" << si 
            << ", isShell=" << isShell << ",faileExit=" << failExit << zsummer::traceback());
        if (failExit)
        {
            goto goExit;
        }
        return nullptr;
    }
    if (isShell || getServiceTrait(si.serviceType) == STrait_Heterogenous)
    {
        service = std::make_shared<ShellService>();
        service->setShell(isShell);
    }
    else if (si.serviceType == STInfoDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (si.serviceType == STLogDBMgr)
    {
        service = std::make_shared<DBService>();
    }
    else if (si.serviceType == STAvatarMgr)
    {
        service = std::make_shared<AvatarMgrService>();
    }
    else if (si.serviceType == STAvatar)
    {
        service = std::make_shared<AvatarService>();
    }
    else if (si.serviceType == STWebAgent)
    {
        service = std::make_shared<WebService>();
    }
    else if (si.serviceType == STOfflineMgr)
    {
        service = std::make_shared<OfflineService>();
    }
    else if (si.serviceType == STMinitorMgr)
    {
        service = std::make_shared<MonitorService>();
    }
    else
    {
        LOGE("createService invalid service type " << si.serviceType);
        if (failExit)
        {
            goto goExit;
        }
        return nullptr;
    }

    service->setServiceDockerID(si.serviceDockerID);
    service->setServiceType(si.serviceType);
    service->setServiceID(si.serviceID);
    service->setServiceName(si.serviceName);
    service->setClientSessionID(si.clientSessionID);
    service->setClientDockerID(si.clientDockerID);
    service->setStatus(SS_CREATED);
    if (!isShell && getServiceTrait(si.serviceType) == STrait_Multi)
    {
        LoadServiceNotice notice;
        notice.shellServiceInfos.push_back(si);
        notice.shellServiceInfos.at(0).status = SS_CREATED;
        broadcastToDockers(notice, false);
    }


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
void Docker::event_onForwardToService(TcpSessionPtr session, ReadStream & rsShell)
{
    Tracing trace;
    rsShell >> trace;
//    LOGT("event_onForwardToService " << trace << ", ReadStream len = " << rsShell.getStreamLen() << ", unread len=" << rsShell.getStreamUnreadLen());
    toService(trace, rsShell.getStreamUnread(), rsShell.getStreamUnreadLen());
}

void Docker::event_onForwardToRealClient(TcpSessionPtr session, ReadStream & rsShell)
{
    Tracing trace;
    rsShell >> trace;
//    LOGT("event_onForwardToRealClient trace=" << trace << ", ReadStream len = " << rsShell.getStreamLen() << ", unread len=" << rsShell.getStreamUnreadLen());
    SessionManager::getRef().sendSessionData(trace.oob.clientSessionID, rsShell.getStreamUnread(), rsShell.getStreamUnreadLen());
}

void Docker::event_onForwardToDocker(TcpSessionPtr session, ReadStream & rsShell)
{
    Tracing trace;
    rsShell >> trace;
//    LOGT("event_onForwardToDocker trace=" << trace << ", ReadStream len = " << rsShell.getStreamLen() << ", unread len=" << rsShell.getStreamUnreadLen());
    ReadStream rs(rsShell.getStreamUnread(), rsShell.getStreamUnreadLen());

    if (rs.getProtoID() == ClientAuthResp::getProtoID())
    {
        ClientAuthResp resp;
        rs >> resp;
        auto clientSession = SessionManager::getRef().getTcpSession(trace.oob.clientSessionID);
        if (!clientSession)
        {
            LOGE("can not found client session. sessionID=" << trace.oob.clientSessionID);
            return;
        }
        if (resp.retCode == EC_SUCCESS)
        {
            clientSession->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_AUTHED);
            clientSession->setUserParamString(UPARAM_ACCOUNT, resp.account);
        }
        else
        {
            clientSession->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
        }
        sendViaSessionID(trace.oob.clientSessionID, rs.getStream(), rs.getStreamLen());
        return;
    }
    else if (rs.getProtoID() == AttachAvatarResp::getProtoID())
    {
        AttachAvatarResp resp;
        rs >> resp;
        auto clientSession = SessionManager::getRef().getTcpSession(trace.oob.clientSessionID);
        if (!clientSession)
        {
            LOGE("can not found client session. sessionID=" << trace.oob.clientSessionID);
            return;
        }
        if (resp.retCode == EC_SUCCESS)
        {
            clientSession->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_ATTACHED);
            clientSession->setUserParamInteger(UPARAM_AVATAR_ID, resp.baseInfo.avatarID);
            clientSession->setUserParamInteger(UPARAM_LOGIN_TIME, getNowTime());
        }
        sendViaSessionID(trace.oob.clientSessionID, rs.getStream(), rs.getStreamLen());
        do
        {
            auto onlineAvatar = peekService(STAvatar, resp.baseInfo.avatarID);
            if (!onlineAvatar)
            {
                break;
            }
            Tracing trace;
            trace.routing.fromServiceType = InvalidServiceType;
            trace.routing.fromServiceID = InvalidServiceID;
            trace.routing.traceBackID = 0;
            trace.routing.traceID = 0;
            trace.routing.toServiceType = STClient;
            

            ChatResp resp;
            resp.channelID = CC_SYSTEM;
            resp.chatTime = getNowTime();
            resp.msg = "player <color=blue>[" + onlineAvatar->getServiceName() + "]</color> is online.  online client["
                + toString(Docker::getRef().peekService(STAvatar).size()) + "].";
            for (auto kv : peekService(STAvatar))
            {
                trace.routing.toServiceID = kv.second->getServiceID();
                toService(trace, resp);
            }
        } while (false);

        return;
    }


}

void Docker::event_onLoadService(TcpSessionPtr session, ReadStream & rs)
{
    LoadService service;
    rs >> service;
    LOGI("Docker::event_onLoadService type=" << service.serviceType << ", name=" << service.serviceName << ", id=" << service.serviceID);
    ServiceInfo info;
    info.serviceDockerID = ServerConfig::getRef().getDockerID();
    info.serviceType = service.serviceType;
    info.serviceID = service.serviceID;
    info.serviceName = service.serviceName;
    info.clientDockerID = service.clientDockerID;
    info.clientSessionID = service.clientSessionID;
    info.status = SS_CREATED;
    auto ret = createService(info, false, false);
    if (ret)
    {
        ret->onLoad();
    }
}

void Docker::event_onLoadServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    LoadServiceNotice service;
    rs >> service;
    for (const auto & si : service.shellServiceInfos)
    {
        LOGI("Docker::event_onLoadServiceNotice type=" << si.serviceType
            << ", name=" << si.serviceName << ", id=" << si.serviceID << ", status=" << si.status);
        auto svc = peekService(si.serviceType, si.serviceID);
        if (!svc && si.status == SS_CREATED)
        {
            createService(si, true, false);
        }
        else if (svc && si.status == SS_WORKING)
        {
            svc->setStatus(SS_WORKING);
            svc->setServiceName(si.serviceName);
            svc->setClientDockerID(si.clientDockerID);
            svc->setClientSessionID(si.clientSessionID);
        }
        else
        {
            LOGE("event_onLoadServiceNotice error status. svc=" << (bool)svc << ", status=" << si.status);
        }
    }
}


void Docker::event_onSwitchServiceClientNotice(TcpSessionPtr session, ReadStream & rs)
{
    SwitchServiceClientNotice change;
    rs >> change;
    LOGI("Docker::event_onSwitchServiceClientNotice type=" << change.serviceType << ", id=" << change.serviceID);
    auto svc = peekService(change.serviceType, change.serviceID);
    if (!svc)
    {
        LOGW("event_onSwitchServiceClientNotice can't founder service. service=" << getServiceName(change.serviceType) << ", serviceID=" << change.serviceID);
        return;
    }
   
    if (svc->getClientSessionID() != InvalidSessionID && !svc->isShell())
    {
        KickRealClient kick(svc->getClientSessionID());
        Docker::getRef().sendViaDockerID(svc->getClientDockerID(), kick);
    }
    svc->setClientSessionID(change.clientSessionID);
    svc->setClientDockerID(change.clientDockerID);
    svc->onClientChange();



    if (getServiceTrait(svc->getServiceType()) == STrait_Multi && !svc->isShell())
    {
        RefreshServiceToMgrNotice refreshNotice;
        refreshNotice.shellServiceInfos.push_back( ServiceInfo(
            svc->getServiceDockerID(),
            svc->getServiceType(),
            svc->getServiceID(),
            svc->getServiceName(),
            svc->getStatus(),
            svc->getClientDockerID(),
            svc->getClientSessionID()));
        for (auto sd : ServiceDepends)
        {
            if (getServiceTrait(sd.first) == STrait_Single)
            {
                svc->toService(sd.first, refreshNotice, nullptr);
            }
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

void Docker::event_onKickClientsNotice(TcpSessionPtr session, ReadStream & rs)
{
    KickClientsNotice notice;
    rs >> notice;
    LOGI("Docker::event_onKickClientsNotice kick all client .  ");
    if (_widelisten != InvalidAccepterID)
    {
        SessionManager::getRef().kickClientSession(_widelisten);
    }
}

void Docker::event_onUnloadServiceInDocker(TcpSessionPtr session, ReadStream & rs)
{
    UnloadServiceInDocker service;
    rs >> service;
    LOGD("event_onUnloadServiceInDocker. service=" << service.serviceType << ", serviceID=" << service.serviceID);
    auto svc = peekService(service.serviceType, service.serviceID);
    if (!svc)
    {
        LOGE("event_onUnloadServiceInDocker can't founder remote service. service=" << getServiceName(service.serviceType) << ", serviceID=" << service.serviceID);
        return;
    }
    if (svc->getStatus() != SS_WORKING || svc->isShell())
    {
        LOGE("event_onUnloadServiceInDocker status error.  status=" << svc->getStatus() << ", isShell=" << svc->isShell());
        return;
    }
    svc->setStatus(SS_UNLOADING);
    svc->onUnload();
}

void Docker::event_onUnloadedServiceNotice(TcpSessionPtr session, ReadStream & rs)
{
    UnloadedServiceNotice service;
    rs >> service;
    LOGD("destroyService. service=" << service.serviceType << ", serviceID=" << service.serviceID);
    destroyService(service.serviceType, service.serviceID);
}



void Docker::event_onClientLinked(TcpSessionPtr session)
{
    session->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
    session->setUserParamNumber(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
    session->setUserParamString(UPARAM_ACCOUNT, "");
    session->setUserParamInteger(UPARAM_AVATAR_ID, InvalidServiceID);
    LOGD("Docker::event_onClientLinked. SessionID=" << session->getSessionID()
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}
void Docker::event_onClientPulse(TcpSessionPtr session)
{
    auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
    if (getFloatSteadyNowTime() - last > ClientPulseInterval *3.0)
    {
        LOGW("client timeout . diff time=" << getFloatSteadyNowTime() - last << ", sessionID=" << session->getSessionID());
        session->close();
        return;
    }
    SessionStatus sStatus = (SessionStatus)session->getUserParamInteger(UPARAM_SESSION_STATUS);
    if (sStatus == SSTATUS_ATTACHED)
    {
        const auto & services = peekService(STAvatar);
        ServiceID serviceID = session->getUserParamInteger(UPARAM_AVATAR_ID);
        auto iter = services.find(serviceID);
        if (iter == services.end())
        {
            LOGE("SSTATUS_ATTACHED session not found service ID. service id=" << serviceID << ", session id=" << session->getSessionID());
        }
    }
    sendViaSessionID(session->getSessionID(), ClientPulse());
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
        if (session->getUserParamInteger(UPARAM_SESSION_STATUS) == SSTATUS_ATTACHED)
        {
            Tracing trace;
            trace.routing.fromServiceType = STClient;
            trace.routing.fromServiceID = session->getUserParamInteger(UPARAM_AVATAR_ID);

            trace.routing.toServiceType = STAvatarMgr;
            trace.routing.toServiceID = InvalidServiceID;

            RealClientClosedNotice notice;
            notice.serviceID = session->getUserParamInteger(UPARAM_AVATAR_ID);
            notice.clientDockerID = ServerConfig::getRef().getDockerID();
            notice.clientSessionID = session->getSessionID();
            toService(trace, notice);
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
    SessionStatus sessionStatus = (SessionStatus) session->getUserParamInteger(UPARAM_SESSION_STATUS);
    if (rs.getProtoID() == ClientPulse::getProtoID())
    {
        session->setUserParamNumber(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
        return;
    }
    if (!_dockerServiceWorking || (!peekService(STAvatarMgr, InvalidServiceID)) || peekService(STAvatarMgr, InvalidServiceID)->getStatus() != SS_WORKING)
    {
        session->close();
        return;
    }
    Tracing trace;
    trace.routing.fromServiceType = STClient;
    trace.routing.fromServiceID = session->getUserParamInteger(UPARAM_AVATAR_ID);
    trace.oob.clientDockerID = ServerConfig::getRef().getDockerID();
    trace.oob.clientSessionID = session->getSessionID();
    trace.oob.clientAvatarID = trace.routing.fromServiceID;
    if (rs.getProtoID() == ClientAuthReq::getProtoID())
    {
        LOGD("ClientAuthReq sID=" << session->getSessionID() << ", block len=" << len);
        if (sessionStatus != SSTATUS_UNKNOW)
        {
            LOGE("duplicate ClientAuthReq. sID=" << session->getSessionID());
            return;
        }
        ClientAuthReq clientReq;
        rs >> clientReq;
        trace.routing.toServiceType = STAvatarMgr;
        trace.routing.toServiceID = InvalidServiceID;

        toService(trace, clientReq);
        session->setUserParamInteger(UPARAM_SESSION_STATUS, SSTATUS_AUTHING);
        return;
    }
    else if (rs.getProtoID() == CreateAvatarReq::getProtoID())
    {
        LOGD("CreateAvatarReq sID=" << session->getSessionID() << ", block len=" << len);
        if (sessionStatus != SSTATUS_AUTHED)
        {
            LOGE("CreateAvatarReq : client not authed. sID=" << session->getSessionID() << ", sessionStatus=" << (short)sessionStatus);
            return;
        }
        CreateAvatarReq clientReq;
        rs >> clientReq;
        clientReq.accountName = session->getUserParamString(UPARAM_ACCOUNT); //填充该字段. 
        trace.routing.toServiceType = STAvatarMgr;
        trace.routing.toServiceID = InvalidServiceID;
        toService(trace, clientReq);
        return;
    }
    else if (rs.getProtoID() == AttachAvatarReq::getProtoID())
    {
        LOGD("AttachAvatarReq sID=" << session->getSessionID() << ", block len=" << len);
        if (sessionStatus != SSTATUS_AUTHED)
        {
            LOGE("AttachAvatarReq : client not authed. sID=" << session->getSessionID());
            return;
        }
        AttachAvatarReq clientReq;
        rs >> clientReq;
        clientReq.accountName = session->getUserParamString(UPARAM_ACCOUNT); //填充该字段. 
        trace.routing.toServiceType = STAvatarMgr;
        trace.routing.toServiceID = InvalidServiceID;

        toService(trace, clientReq);
        return;
    }
    else if (rs.getProtoID() >= 40000 && sessionStatus == SSTATUS_ATTACHED )
    {
        LOGD("recvfrom client: avatarID=" << trace.oob.clientAvatarID << ", proto[" << rs.getProtoID() << "]= " << ProtoReflection::getProtoName(rs.getProtoID()));
        trace.routing.toServiceType = STAvatar;
        trace.routing.toServiceID = trace.routing.fromServiceID;
        toService(trace, rs.getStream(), rs.getStreamLen());
        return;
    }

    else
    {
        LOGE("client unknow proto or wrong status. proto[" << rs.getProtoID() << "]= " << ProtoReflection::getProtoName(rs.getProtoID()) << ", status=" << sessionStatus << ", sessionID=" << session->getSessionID());
        session->close();
        return;
    }
}



void Docker::event_onWebClientRequestAPI(TcpSessionPtr session, const std::string & method, const std::string & methodLine, 
    const std::map<std::string,std::string> &head, const std::string & body)
{
    LOGD("onWebMessage sessionID=" << session->getSessionID() << ", method=" << method << ", methodLine=" << methodLine);
    WebAgentClientRequestAPI notice;
    notice.method = method;
    notice.methodLine = methodLine;
    notice.heads = head;
    notice.body = body;

    Tracing trace;
    trace.routing.fromServiceType = InvalidServiceType;
    trace.routing.fromServiceID = InvalidServiceID;
    trace.oob.clientDockerID = ServerConfig::getRef().getDockerID();
    trace.oob.clientSessionID = session->getSessionID();
    trace.routing.toServiceType = STWebAgent;
    trace.routing.toServiceID = InvalidServiceID;
    toService(trace, notice);
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
            wh.get(req.uri + "?" + urlEncode(req.webparams));
        }
        else
        {
            wh.post(req.uri, req.webparams);
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
        trace.routing.toServiceType = req.fromServiceType;
        trace.routing.toServiceID = req.fromServiceID;
        trace.routing.traceBackID = req.traceID;
        toService(trace, resp);
    };
    option._onHTTPBlockDispatch = std::bind(onResponse, _1, _2, _3, _4, _5, req);
    SessionManager::getRef().openConnecter(cID);
}


void Docker::sendViaSessionID(SessionID sessionID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sessionID, block, len);
}


void Docker::sendViaDockerID(DockerID dockerID, const char * block, unsigned int len)
{
    SessionID sID = getDockerLinked(dockerID);
    if (sID == InvalidSessionID)
    {
        LOGF("Docker::sendViaDockerID fatal error. dockerID not linked. dockerID=" << dockerID);
        return;
    }
    sendViaSessionID(sID, block, len);
}

void Docker::sendViaServiceID(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len)
{
//    LOGT("Docker::sendViaServiceID serviceType=" << serviceType << ", serviceID=" << serviceID << ", block len=" << len);
    ServicePtr svc = peekService((serviceType == STClient ? STAvatar : serviceType) , serviceID);
    if (!svc)
    {
        LOGE("sendViaServiceID error. not found service. serviceType=" << serviceType
            << ", serviceID=" << serviceID << ", protoID=" << ReadStream(block, len).getProtoID());
        return;
    }
    if (serviceType != STClient)
    {
        sendViaDockerID(svc->getServiceDockerID(), block, len);
    }
    else
    {
        sendViaDockerID(svc->getClientDockerID(), block, len);
    }
}


void Docker::forwardToRemoteService(Tracing  trace, const char * block, unsigned int len)
{
    if (trace.routing.toServiceType == STClient)
    {
        if (trace.oob.clientDockerID == InvalidDockerID)
        {
            ServicePtr svc = peekService(STAvatar, trace.routing.toServiceID );
            if (!svc)
            {
                LOGW("forwardToRemoteService error. not found service. trace=" << trace
                        << ", protoID=" << ReadStream(block, len).getProtoID());
                return;
            }
            trace.oob.clientDockerID = svc->getClientDockerID();
            trace.oob.clientSessionID = svc->getClientSessionID();
        }
        if (trace.oob.clientDockerID == InvalidDockerID)
        {
            LOGW("forwardToRemoteService error. client not attach. trace=" << trace
                << ", protoID=" << ReadStream(block, len).getProtoID());
            return;
        }
        ReadStream rs(block, len);
        LOGD("sendto client: avatarID=" << trace.routing.toServiceID << ", proto[" << rs.getProtoID() << "]= " << ProtoReflection::getProtoName(rs.getProtoID()));
        if (trace.oob.clientDockerID == ServerConfig::getRef().getDockerID())
        {
            sendViaSessionID(trace.oob.clientSessionID, block, len);
            return;
        }
        WriteStream ws(ForwardToRealClient::getProtoID());
        ws << trace;
        ws.appendOriginalData(block, len);
        sendViaDockerID(trace.oob.clientDockerID, ws.getStream(), ws.getStreamLen());
        
    }
    else
    {
        WriteStream ws(ForwardToService::getProtoID());
        ws << trace;
        ws.appendOriginalData(block, len);
        sendViaServiceID(trace.routing.toServiceType, trace.routing.toServiceID, ws.getStream(), ws.getStreamLen());
    }
}



void Docker::toService(Tracing trace, const char * block, unsigned int len, bool syncCall)
{
    ProtoID protoID = ReadStream(block, len).getProtoID();
//    LOGT("Docker::toService " << trace << ", len=" << len << ", syncCall=" << syncCall);
    if (getServiceTrait(trace.routing.toServiceType) == STrait_Single && trace.routing.toServiceID != InvalidServiceID)
    {
        LOGE("toService dst Type is Single[" << getServiceName(trace.routing.toServiceType) << "] but dst Service ID is " << trace.routing.toServiceID << ", block protoID=" << protoID);
        return;
    }
    if (getServiceTrait(trace.routing.toServiceType) == STrait_Multi && trace.routing.toServiceType != STClient && trace.routing.toServiceID == InvalidServiceID)
    {
        LOGE("toService dst Type is Multi[" << getServiceName(trace.routing.toServiceType) << "] but dst Service ID is " << trace.routing.toServiceID << ", block protoID=" << protoID);
        return;
    }
    if (trace.routing.toServiceType == STClient)
    {
        forwardToRemoteService(trace, block, len);
        return;
    }

    ui16 toServiceType = trace.routing.toServiceType;
    ServiceID toServiceID = trace.routing.toServiceID;
    auto svc = peekService(toServiceType, toServiceID);
       
    if (!svc)
    {
        if (getServiceTrait(toServiceType) != STrait_Single)
        {
            LOGW("Docker::toService can not found toService  trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
        }
        else
        {
            LOGF("Docker::toService can not found toService  trace =" << trace << ", block len=" << len << ", protoID=" << protoID);
        }
        return;
    }
        
    if (svc->isShell()) //forward 
    {
        forwardToRemoteService(trace, block, len);
    }
    else //direct process
    {
        if (!syncCall)
        {
//             LOGT("Docker::toService local post process4bind " << trace << ", len=" << len 
//                 << ", syncCall=" << syncCall << ", protoID=" << protoID);
            std::string bk;
            bk.assign(block, len);
            SessionManager::getRef().post(std::bind(&Service::process4bind, svc, trace, std::move(bk)));
        }
        else
        {
//             LOGT("Docker::toService  local process " << trace << ", len=" << len 
//                     << ", syncCall=" << syncCall << ", protoID=" << protoID);
            svc->process(trace, block, len);
        }
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




