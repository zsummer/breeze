#include "../config.h"
#include "application.h"
#include "dbService.h"
#include "userMgr.h"
int g_closeState = 0;

Application::Application()
{

}

bool Application::init(const std::string & config, ClusterID idx)
{
    if (!ServerConfig::getRef().parse(config, idx))
    {
        return false;
    }
    LOGA("Application::init clusterID=" << idx);
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
                    svc.second->onStop();
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
            if (!svc.second->isShell() && svc.second->isWorked())
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

bool Application::start()
{
    const auto & clusters = ServerConfig::getRef().getClusterConfig();
    for (const auto & cluster : clusters)
    {
        SessionID cID = SessionManager::getRef().addConnecter(cluster._serviceIP, cluster._servicePort);
        if (cID == InvalidSessionID)
        {
            LOGE("addConnecter error.");
            return false;
        }
        auto session = SessionManager::getRef().getTcpSession(cID);
        if (!session)
        {
            LOGE("getTcpSession error. connect add faild");
            return false;
        }
        LOGD("connect cluster. clusterID=" << cluster._cluster << ", cID=" << cID << ", ip=" << cluster._serviceIP << ", port=" << cluster._servicePort);
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
            LOGE("openConnecter error.");
            return false;
        }
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_TRUST);
        session->setUserParam(UPARAM_REMOTE_CLUSTER, cluster._cluster);
        _clusterSession[cluster._cluster] = std::make_pair(cID, 0);
        for (auto st : cluster._services)
        {
            auto & second = _services[st];
            auto & servicePtr =  second[InvalidServiceID];
            if (servicePtr)
            {
                LOGE("duplicat service");
                return false;
            }
            else
            {
                servicePtr = createLocalService(st);
            }
            if (!servicePtr)
            {
                LOGE("unsupport service");
                return false;
            }
            
            servicePtr->setServiceType(st);
            if (cluster._cluster != ServerConfig::getRef().getClusterID())
            {
                servicePtr->setShell(cluster._cluster);
            }

        }

        if (cluster._cluster == ServerConfig::getRef().getClusterID())
        {
            AccepterID aID = SessionManager::getRef().addAccepter(cluster._serviceBindIP, cluster._servicePort);
            if (aID == InvalidAccepterID)
            {
                LOGE("addAccepter error");
                return false;
            }
            auto &options = SessionManager::getRef().getAccepterOptions(aID);
            options._whitelistIP = cluster._whiteList;
            options._maxSessions = 1000;
            options._sessionOptions._sessionPulseInterval = 5000;
            options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
            {
                ClusterPulse pulse;
                WriteStream ws(pulse.GetProtoID());
                ws << pulse;
                session->send(ws.getStream(), ws.getStreamLen());
            };
            options._sessionOptions._onBlockDispatch = std::bind(&Application::event_onServiceMessage, this, _1, _2, _3);
            if (!SessionManager::getRef().openAccepter(aID))
            {
                LOGE("openAccepter error");
                return false;
            }


            if (!cluster._wideIP.empty() && cluster._widePort != 0)
            {
                aID = SessionManager::getRef().addAccepter("0.0.0.0", cluster._widePort);
                if (aID == InvalidAccepterID)
                {
                    LOGE("addAccepter error");
                    return false;
                }
                auto &options = SessionManager::getRef().getAccepterOptions(aID);
                options._whitelistIP = cluster._whiteList;
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
                    LOGE("openAccepter error");
                    return false;
                }
                _wlisten = aID;
            }
        }
    }
    return true;
}






void Application::event_onServiceLinked(TcpSessionPtr session)
{
    ClusterID ci = (ClusterID)session->getUserParamNumber(UPARAM_REMOTE_CLUSTER);
    auto founder = _clusterSession.find(ci);
    if (founder == _clusterSession.end())
    {
        LOGE("event_onServiceLinked error cID=" << session->getSessionID() << ", clusterID=" << ci);
        return;
    }
    LOGI("event_onServiceLinked cID=" << session->getSessionID() << ", clusterID=" << ci);
    founder->second.second = 1;
    for (auto & second : _services)
    {
        if (second.first == ServiceClient || second.first == ServiceUser || second.first == ServiceInvalid)
        {
            continue;
        }
        for (auto & svc : second.second )
        {
            if (!svc.second->isShell() && svc.second->isInited())
            {
                ClusterServiceInited inited(svc.second->getServiceType(), svc.second->getServiceID());
                Application::getRef().broadcast(inited);
            }
        }
    }
    checkServiceState();
}

void Application::event_onServiceClosed(TcpSessionPtr session)
{
    ClusterID ci = (ClusterID)session->getUserParamNumber(UPARAM_REMOTE_CLUSTER);
    auto founder = _clusterSession.find(ci);
    if (founder == _clusterSession.end())
    {
        LOGE("event_onServiceClosed error cID=" << session->getSessionID() << ", clusterID=" << ci);
        return;
    }
    LOGW("event_onServiceClosed cID=" << session->getSessionID() << ", clusterID=" << ci);
    founder->second.second = 0;
}


ServicePtr Application::createLocalService(ui16 st)
{
    if (st == ServiceDictDBMgr)
    {
        return std::make_shared<DBService>();
    }
    else if (st == ServiceInfoDBMgr)
    {
        return std::make_shared<DBService>();
    }
    else if (st == ServiceLogDBMgr)
    {
        return std::make_shared<DBService>();
    }
    else if (st == ServiceUserMgr)
    {
        return std::make_shared<UserMgr>();
    }
    else
    {
        LOGE("createLocalService invalid service type " << st);
    }
    return nullptr;
}

void Application::checkServiceState()
{
    SessionManager::getRef().createTimer(1000, std::bind(&Application::checkServiceState, Application::getPtr()));
    if (!_clusterNetWorking)
    {
        for (auto & c : _clusterSession)
        {
            if (c.second.second == 0)
            {
                return;
            }
        }
        _clusterNetWorking = true;
        LOGA("cluster net worked");
    }

    for (auto & second : _services)
    {
        for (auto service : second.second)
        {
            if (service.second && !service.second->isShell() && service.second->isInited())
            {
                service.second->onTick();
            }
        }
    }
    if (!_clusterServiceInited)
    {
        for (ui16 i = ServiceInvalid+1; i != ServiceMax; i++)
        {
            auto founder = _services.find(i);
            if (founder == _services.end())
            {
                LOGE("not found service id=" << i);
                continue;
            }
            for (auto service : founder->second)
            {
                if (service.second && !service.second->isShell() && !service.second->isInited())
                {
                    LOGI("local service [" << ServiceNames.at(service.second->getServiceType()) << "] begin init. [" << service.second->getServiceID() << "] ...");
                    service.second->setInited();
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
            }
        }
        LOGA("all local service inited");
        _clusterServiceInited = true;
    }
    

    if (!_clusterServiceWorking)
    {
        for (auto & second : _services)
        {
            for (auto & service : second.second)
            {
                if (!service.second || !service.second->isInited() || !service.second->isWorked())
                {
                    return;
                }
            }
        }
        _clusterServiceWorking = true;
        LOGA("all service worked.");
    }
    
    
}

void Application::event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    if (rs.getProtoID() == ClusterPulse::GetProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    if (rs.getProtoID() == ClusterServiceInited::GetProtoID())
    {
        ClusterServiceInited service;
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
        if (fder->second->isShell() && !fder->second->isInited())
        {
            LOGI("remote service [" << ServiceNames.at(fder->second->getServiceType()) << "]begin init. [" << fder->second->getServiceID() << "] ...");
            fder->second->setInited();
            fder->second->setWorked(true);
            LOGI("remote service [" << ServiceNames.at(fder->second->getServiceType()) << "] inited. [" << fder->second->getServiceID() << "] ...");
            checkServiceState();
        }
        return;
    }
    if (rs.getProtoID() == ClusterShellForward::GetProtoID())
    {
        Tracing trace;
        rs >> trace;
        auto founder = _services.find(trace._toService);
        if (founder == _services.end())
        {
            return;
        }
        auto fder = founder->second.find(trace._toServiceID);
        if (fder == founder->second.end())
        {
            return;
        }
        Service & svc = *fder->second;
        if (svc.isShell())
        {
            return;
        }
        svc.process(trace, rs.getStreamUnread(), rs.getStreamUnreadLen());
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



void Application::event_onClientMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{

}

void Application::globalCall(Tracing trace, const char * block, unsigned int len)
{
    if (trace._fromService >= ServiceMax || trace._toService >= ServiceMax)
    {
        LOGF("Application::globalCall Illegality trace. trace=" << trace << ", block len=" << len);
        return;
    }
    auto founder = _services.find(trace._toService);
    if (founder != _services.end())
    {
        auto fder = founder->second.find(trace._toServiceID);
        if (fder != founder->second.end())
        {
            auto & service = *fder->second;
            if (service.isShell()) //forward 
            {
                WriteStream ws(ClusterShellForward::GetProtoID());
                ws << trace;
                ws.appendOriginalData(block, len);
                ClusterID cltID = service.getClusterID();
                auto fsder = _clusterSession.find(cltID);
                if (fsder == _clusterSession.end())
                {
                    LOGE("Application::globalCall not found session by shell service. clusterID=" << cltID << ", tracing=" << trace);
                }
                else
                {
                    SessionManager::getRef().sendSessionData(fsder->second.first, ws.getStream(), ws.getStreamLen());
                    if (fsder->second.second == 0)
                    {
                        LOGW("Application::globalCall session not connected when global call by shell service. sID=" << fsder->second.first 
                            << ", clusterID=" << cltID << ", tracing=" << trace);
                    }
                }
                
            }
            else //direct process
            {
                service.process(trace, block, len);
            }
            
        }
        else
        {
            LOGD("Application::globalCall can not found _toService ID. trace =" << trace << ", block len=" << len);
        }
    }
    else
    {
        LOGF("Application::globalCall can not found _toService type  trace =" << trace << ", block len=" << len);
    }
}




