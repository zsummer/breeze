
#include "world.h"

#include <ProtoUser.h>
#include <ProtoUserMgr.h>
#include <ProtoDocker.h>



World::World()
{

}

bool World::init(const std::string & configName)
{
    if (!ServerConfig::getRef().parseDB(configName) || !ServerConfig::getRef().parseWorld(configName) )
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
    if (_dockerListen != InvalidAccepterID)
    {
        SessionManager::getRef().stopAccept(_dockerListen);
        SessionManager::getRef().kickClientSession(_dockerListen);
    }
    if (_spaceListen != InvalidAccepterID)
    {
        SessionManager::getRef().stopAccept(_spaceListen);
        SessionManager::getRef().kickClientSession(_spaceListen);
    }
    return ;
}

bool World::startDockerListen()
{
    auto wc = ServerConfig::getRef().getWorldConfig();

   _dockerListen = SessionManager::getRef().addAccepter(wc._dockerListenHost, wc._dockerListenPort);
    if (_dockerListen == InvalidAccepterID)
    {
        LOGE("World::startDockerListen addAccepter error. bind ip=" << wc._dockerListenHost << ", bind port=" << wc._dockerListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(_dockerListen);
//    options._whitelistIP = wc._dockerListenHost;
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
    if (!SessionManager::getRef().openAccepter(_dockerListen))
    {
        LOGE("World::startDockerListen openAccepter error. bind ip=" << wc._dockerListenHost << ", bind port=" << wc._dockerListenPort);
        return false;
    }
    LOGA("World::startDockerListen openAccepter success. bind ip=" << wc._dockerListenHost << ", bind port=" << wc._dockerListenPort
        <<", _dockerListen=" << _dockerListen);
    return true;
}



bool World::startSpaceListen()
{
    auto wc = ServerConfig::getRef().getWorldConfig();

    _spaceListen = SessionManager::getRef().addAccepter(wc._spaceListenHost, wc._spaceListenPort);
    if (_spaceListen == InvalidAccepterID)
    {
        LOGE("World::startSpaceListen addAccepter error. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(_spaceListen);
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
    if (!SessionManager::getRef().openAccepter(_spaceListen))
    {
        LOGE("World::startSpaceListen openAccepter error. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort);
        return false;
    }
    LOGA("World::startSpaceListen openAccepter success. bind ip=" << wc._spaceListenHost 
        << ", bind port=" << wc._spaceListenPort <<", _spaceListen=" << _spaceListen);
    return true;
}

void World::sendToSession(SessionID sessionID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sessionID, block, len);
}

bool World::start()
{
    return startDockerListen() && startSpaceListen();
}

void World::event_onDockerLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_AREA_ID, InvalidAreaID);
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
    sendToSession(session->getSessionID(), notice);
    LOGI("event_onDockerLinked cID=" << session->getSessionID() );
}


void World::event_onDockerClosed(TcpSessionPtr session)
{
    AreaID areaID = (DockerID)session->getUserParamNumber(UPARAM_AREA_ID);
    LOGW("event_onDockerClosed sessionID=" << session->getSessionID() << ", areaID=" << areaID);
    if (areaID != InvalidAreaID)
    {
        auto founder = _services.find(areaID);
        if (founder != _services.end())
        {
            for (auto & ws : founder->second)
            {
                if (areaID == ws.second.areaID && session->getSessionID() == ws.second.sessionID)
                {
                    ws.second.sessionID = InvalidSessionID;
                }
            }
        }
    }

}


void World::event_onDockerMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);
    if (DockerPulse::getProtoID() != rsShell.getProtoID())
    {
        LOGT("event_onDockerMessage protoID=" << rsShell.getProtoID() << ", len=" << len);
    }

    if (rsShell.getProtoID() == DockerPulse::getProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    else if (rsShell.getProtoID() == SelfBeingPulse::getProtoID())
    {
        SelfBeingPulse pulse;
        rsShell >> pulse;
        LOGA("SelfBeingPulse sessionID=" << session->getSessionID() << ", areaID=" << pulse.areaID << ",dockerID=" << pulse.dockerID);
        session->setUserParam(UPARAM_AREA_ID, pulse.areaID);
    }
    else if (rsShell.getProtoID() == LoadServiceNotice::getProtoID())
    {
        AreaID areaID = session->getUserParamNumber(UPARAM_AREA_ID);
        if (areaID == InvalidAreaID)
        {
            LOGE("not found area id. sessionID=" << session->getSessionID());
            return;
        }
        LoadServiceNotice notice;
        rsShell >> notice;
        for (auto &shell : notice.shellServiceInfos)
        {
            auto & wss = _services[areaID][shell.serviceType];
            wss.areaID = areaID;
            wss.serviceType = shell.serviceType;
            wss.sessionID = session->getSessionID();
        }
    }
    else if (rsShell.getProtoID() == ForwardToService::getProtoID())
    {
        Tracing trace;
        rsShell >> trace;
        ReadStream rs(rsShell.getStreamUnread(), rsShell.getStreamUnreadLen());
        event_onServiceForwardMessage(session, trace.fromServiceType, rs);
    }
}




void World::event_onServiceForwardMessage(TcpSessionPtr   session, ServiceType serviceType, ReadStream & rs)
{

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





SessionID World::getDockerLinked(AreaID areaID, ServiceType serviceType)
{
    auto founder = _services.find(areaID);
    if (founder == _services.end())
    {
        return InvalidSessionID;
    }
    auto fder = founder->second.find(serviceType);
    if (fder != founder->second.end() && fder->second.sessionID != InvalidSessionID)
    {
        return fder->second.sessionID;
    }
    for (auto &wss : founder->second)
    {
        if (wss.second.sessionID != InvalidSessionID)
        {
            return wss.second.sessionID;
        }
    }
    return InvalidSessionID;
}


