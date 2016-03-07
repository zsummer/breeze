#include "../config.h"
#include "application.h"
#include "dbMgr.h"

Application::Application()
{

}

bool Application::init(const std::string & config, ClusterIndex idx)
{
    if (!ServerConfig::getRef().parse(config, idx))
    {
        return false;
    }
    return true;
}
bool Application::run()
{
    return SessionManager::getRef().run();
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
        auto &options = SessionManager::getRef().getConnecterOptions(cID);
        options._onSessionLinked = std::bind(&Application::event_onServiceLinked, this, _1);
        options._onSessionClosed = std::bind(&Application::event_onServiceClosed, this, _1);
        options._onBlockDispatch = std::bind(&Application::event_onServiceMessage, this, _1, _2, _3);
        options._reconnects = 50;
        options._connectPulseInterval = 5000;
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
        _clusterState[cID] = 0;
        for (auto serviceType : cluster._services)
        {
            auto & second = _services[serviceType];
            auto & servicePtr =  second[InvalidServiceID];
            if (servicePtr)
            {
            }
            else
            {
                if (serviceType == ServiceDictDBMgr)
                {
                    servicePtr = std::make_shared<DBBase>();
                }
                else
                {
                    servicePtr = std::make_shared<Service>();
                }
            }
            servicePtr->setServiceType(serviceType);
            servicePtr->setServiceID(InvalidServiceID);
            if (cluster._cluster != ServerConfig::getRef().getClusterID())
            {
                servicePtr->setShell(true);
                servicePtr->setSessionID(cID);
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
            options._sessionOptions._sessionPulseInterval = 10000;
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
            }
        }
    }
    return true;
}






void Application::event_onServiceLinked(TcpSessionPtr session)
{
    auto founder = _clusterState.find(session->getSessionID());
    if (founder == _clusterState.end())
    {
        LOGE("event_onServiceLinked error");
        return;
    }
    founder->second = 1;
    checkServiceState();
}

void Application::event_onServiceClosed(TcpSessionPtr session)
{
    auto founder = _clusterState.find(session->getSessionID());
    if (founder == _clusterState.end())
    {
        LOGE("event_onServiceClosed error");
        return;
    }
    founder->second = 0;
    _clusterNetWorking = false;
}

void Application::initService(const std::vector<ServiceType> & services)
{

}
void Application::checkServiceState()
{
    for (auto & c : _clusterState)
    {
        if (c.second == 0)
        {
            return;
        }
    }
    if (!_clusterNetWorking)
    {
        _clusterNetWorking = true;
        LOGI("Application::checkServiceState _clusterNetWorking change to true");
    }
    
    
    if (!_clusterServiceInited)
    {
        _clusterServiceInited = true;
        LOGI("Application::checkServiceState _clusterServiceInited change to true");
        std::vector<ServiceType> services;
        const auto & clusters = ServerConfig::getRef().getClusterConfig();
        for (const auto c : clusters)
        {
            if (c._cluster == ServerConfig::getRef().getClusterID())
            {
                initService(services);
                break;
            }
        }
        
    }
    
    for (auto & second : _services)
    {
        for (auto & service : second.second)
        {
            if (!service.second || !service.second->getInited() || !service.second->getWorked())
            {
                return;
            }
        }

    }
    if (!_clusterServiceWorking)
    {
        _clusterServiceWorking = true;
        LOGI("Application::checkServiceState _clusterServiceWorking change to true");
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
            return;
        }
        auto fder = founder->second.find(service.serviceID);
        if (fder == founder->second.end() || !fder->second)
        {
            return;
        }
        fder->second->setInited(true);
        fder->second->setWorked(true);
        checkServiceState();
        return;
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

