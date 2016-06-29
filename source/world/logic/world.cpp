
#include "world.h"

#include <ProtoUser.h>
#include <ProtoUserMgr.h>
#include <ProtoWebAgent.h>
#include <ProtoDocker.h>



World::World()
{

}

bool World::init(const std::string & configName)
{
    if (!ServerConfig::getRef().parseDB(configName) || !ServerConfig::getRef().parseWorld(configName) || !ServerConfig::getRef().parseSpaces(configName, 1))
    {
        LOGE("World::init error. parse config error. config path=" << configName);
        return false;
    }

    if (!DBDict::getRef().initHelper())
    {
        LOGE("World::init error. DBDict initHelper error. ");
        return false;
    }

    if (!DBDict::getRef().load())
    {
        LOGE("World::init error. DBDict load error. ");
        return false;
    }

    return true;
}

void sigInt(int sig)
{
    if (!World::getRef().isStopping())
    {
        SessionManager::getRef().post(std::bind(&World::stop, World::getPtr()));
    }
}

void World::forceStop()
{

}

void World::stop()
{
    LOGA("World::stop");
    World::getRef().onShutdown();

}

bool World::run()
{
    SessionManager::getRef().run();
    LOGA("World::run exit!");
    return true;
}

bool World::isStopping()
{
    return false;
}

void World::onShutdown()
{

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

    return ;
}

bool World::startDockerListen()
{
    const auto & dockers = ServerConfig::getRef().getDockerConfigs();
    auto founder = std::find_if(dockers.begin(), dockers.end(), [](const DockerConfig& cc){return cc._dockerID == ServerConfig::getRef().getDockerID(); });
    if (founder == dockers.end())
    {
        LOGE("World::startDockerListen error. current docker id not found in config file." );
        return false;
    }
    const DockerConfig & docker = *founder;
    if (docker._dockerListenHost.empty() || docker._dockerListenPort == 0)
    {
        LOGE("World::startDockerListen check config error. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort);
        return false;
    }
    AccepterID aID = SessionManager::getRef().addAccepter(docker._dockerListenHost, docker._dockerListenPort);
    if (aID == InvalidAccepterID)
    {
        LOGE("World::startDockerListen addAccepter error. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort);
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
    options._sessionOptions._onBlockDispatch = std::bind(&World::event_onServiceMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(aID))
    {
        LOGE("World::startDockerListen openAccepter error. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort);
        return false;
    }
    LOGA("World::startDockerListen openAccepter success. bind ip=" << docker._dockerListenHost << ", bind port=" << docker._dockerListenPort <<", aID=" << aID);
    return true;
}



bool World::start()
{
    return startDockerListen()   ;
}






void World::event_onServiceLinked(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_DOCKERID);

    LOGI("event_onServiceLinked cID=" << session->getSessionID() << ", dockerID=" << ci);

    DockerConfig dc;
    if (true)
    {
        const auto & configs = ServerConfig::getRef().getDockerConfigs();
        for (const auto & ci : configs)
        {

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



}

void World::event_onServiceClosed(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_DOCKERID);
   
    LOGW("event_onServiceClosed cID=" << session->getSessionID() << ", dockerID=" << ci);
    
    DockerConfig dc;
    if (true)
    {
        const auto & configs = ServerConfig::getRef().getDockerConfigs();
        for (const auto & ci : configs)
        {

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







void World::event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);
    if (DockerPulse::getProtoID() != rsShell.getProtoID())
    {
        LOGT("event_onServiceMessage protoID=" << rsShell.getProtoID() << ", len=" << len);
    }

}











void World::event_onClientLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
    LOGD("World::event_onClientLinked. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}
void World::event_onClientPulse(TcpSessionPtr session)
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

    }
}
void World::event_onClientClosed(TcpSessionPtr session)
{
    LOGD("World::event_onClientClosed. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
    if (isConnectID(session->getSessionID()))
    {
        LOGF("Unexpected");
    }
    else
    {
        if (session->getUserParamNumber(UPARAM_SESSION_STATUS) == SSTATUS_ATTACHED)
        {

        }
    }
}



void World::event_onClientMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    SessionStatus sessionStatus = (SessionStatus) session->getUserParamNumber(UPARAM_SESSION_STATUS);
 
    {
        LOGE("client unknow proto or wrong status. protoID=" << rs.getProtoID() << ", status=" << sessionStatus << ", sessionID=" << session->getSessionID());
    }
}





SessionID World::getDockerLinked(DockerID dockerID)
{
    return InvalidSessionID;
}


