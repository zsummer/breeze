
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
    auto wc = ServerConfig::getRef().getWorldConfig();

    AccepterID aID = SessionManager::getRef().addAccepter(wc._worldListenHost, wc._worldListenPort);
    if (aID == InvalidAccepterID)
    {
        LOGE("World::startDockerListen addAccepter error. bind ip=" << wc._worldListenHost << ", bind port=" << wc._worldListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(aID);
//    options._whitelistIP = wc._worldListenHost;
    options._maxSessions = 1000;
    options._sessionOptions._sessionPulseInterval = 5000;
    options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
    {
        DockerPulse pulse;
        WriteStream ws(pulse.getProtoID());
        ws << pulse;
        session->send(ws.getStream(), ws.getStreamLen());
    };
    options._sessionOptions._onSessionLinked = std::bind(&World::event_onDockerLinked, this, _1);
    options._sessionOptions._onSessionClosed = std::bind(&World::event_onDockerClosed, this, _1);
    options._sessionOptions._onBlockDispatch = std::bind(&World::event_onDockerMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(aID))
    {
        LOGE("World::startDockerListen openAccepter error. bind ip=" << wc._worldListenHost << ", bind port=" << wc._worldListenPort);
        return false;
    }
    LOGA("World::startDockerListen openAccepter success. bind ip=" << wc._worldListenHost << ", bind port=" << wc._worldListenPort
        <<", aID=" << aID);
    return true;
}



bool World::startSpaceListen()
{
    auto wc = ServerConfig::getRef().getWorldConfig();

    AccepterID aID = SessionManager::getRef().addAccepter(wc._spaceListenHost, wc._spaceListenPort);
    if (aID == InvalidAccepterID)
    {
        LOGE("World::startSpaceListen addAccepter error. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(aID);
    options._maxSessions = 1000;
    options._sessionOptions._sessionPulseInterval = 5000;
    options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
    {
        DockerPulse pulse;
        WriteStream ws(pulse.getProtoID());
        ws << pulse;
        session->send(ws.getStream(), ws.getStreamLen());
    };
    options._sessionOptions._onSessionLinked = std::bind(&World::event_onSpaceLinked, this, _1);
    options._sessionOptions._onSessionClosed = std::bind(&World::event_onSpaceClosed, this, _1);
    options._sessionOptions._onBlockDispatch = std::bind(&World::event_onSpaceMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(aID))
    {
        LOGE("World::startSpaceListen openAccepter error. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort);
        return false;
    }
    LOGA("World::startSpaceListen openAccepter success. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort <<", aID=" << aID);
    return true;
}



bool World::start()
{
    return startDockerListen() && startSpaceListen();
}

void World::event_onDockerLinked(TcpSessionPtr session)
{
    LoadServiceNotice notice;
    ShellServiceInfo info;
    info.serviceDockerID = InvalidDockerID;
    info.serviceType = STWorldMgr;
    info.serviceID = InvalidServiceID;
    info.serviceName = "STWorldMgr";
    info.clientDockerID = InvalidDockerID;
    info.clientSessionID = InvalidSessionID;
    info.status = SS_WORKING;
    notice.shellServiceInfos.push_back(info);
    LOGI("event_onDockerLinked cID=" << session->getSessionID() );
}


void World::event_onDockerClosed(TcpSessionPtr session)
{
    DockerID ci = (DockerID)session->getUserParamNumber(UPARAM_REMOTE_DOCKERID);
    LOGW("event_onDockerClosed cID=" << session->getSessionID() << ", dockerID=" << ci);
}







void World::event_onDockerMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);
    if (DockerPulse::getProtoID() != rsShell.getProtoID())
    {
        LOGT("event_onDockerMessage protoID=" << rsShell.getProtoID() << ", len=" << len);
    }

}











void World::event_onSpaceLinked(TcpSessionPtr session)
{
    LOGD("World::event_onSpaceLinked. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}
void World::event_onSpacePulse(TcpSessionPtr session)
{
    auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
    if (getNowTime() - (time_t)last > session->getOptions()._sessionPulseInterval * 3)
    {
        LOGW("client timeout . diff time=" << getNowTime() - (time_t)last << ", sessionID=" << session->getSessionID());
        session->close();
        return;
    }
}
void World::event_onSpaceClosed(TcpSessionPtr session)
{
    LOGD("World::event_onSpaceClosed. SessionID=" << session->getSessionID() 
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



void World::event_onSpaceMessage(TcpSessionPtr session, const char * begin, unsigned int len)
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


