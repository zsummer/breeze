
#include "spaceMgr.h"

#include <ProtoUser.h>
#include <ProtoUserMgr.h>
#include <ProtoDocker.h>
#include <ProtoSpaceCommon.h>
#include <ProtoSpaceServer.h>


SpaceMgr::SpaceMgr()
{

}

bool SpaceMgr::init(const std::string & configName, ui32 serverID)
{
    if (!ServerConfig::getRef().parseDB(configName) || !ServerConfig::getRef().parseWorld(configName) || !ServerConfig::getRef().parseSpaces(configName, serverID))
    {
        LOGE("SpaceMgr::init error. parse config error. config path=" << configName);
        return false;
    }

    if (!DBDict::getRef().initHelper())
    {
        LOGE("SpaceMgr::init error. DBDict initHelper error. ");
        return false;
    }

    if (!DBDict::getRef().load())
    {
        LOGE("SpaceMgr::init error. DBDict load error. ");
        return false;
    }

    return true;
}

void sigInt(int sig)
{
    if (!SpaceMgr::getRef().isStopping())
    {
        SessionManager::getRef().post(std::bind(&SpaceMgr::stop, SpaceMgr::getPtr()));
    }
}

void SpaceMgr::forceStop()
{

}

void SpaceMgr::stop()
{
    LOGA("SpaceMgr::stop");
    SpaceMgr::getRef().onShutdown();
}

bool SpaceMgr::run()
{
    SessionManager::getRef().run();
    LOGA("SpaceMgr::run exit!");
    return true;
}

bool SpaceMgr::isStopping()
{
    return false;
}

void SpaceMgr::onShutdown()
{
    if (_clientListen != InvalidAccepterID)
    {
        SessionManager::getRef().stopAccept(_clientListen);
        SessionManager::getRef().kickClientSession(_clientListen);
    }
    SessionManager::getRef().kickClientSession();
    SessionManager::getRef().stop();
    return ;
}

bool SpaceMgr::startClientListen()
{
    auto sc = ServerConfig::getRef().getSpaceConfig();

    _clientListen = SessionManager::getRef().addAccepter(sc._clientListenHost, sc._clientListenPort);
    if (_clientListen == InvalidAccepterID)
    {
        LOGE("SpaceMgr::startClientListen addAccepter error. bind ip=" << sc._clientListenHost << ", bind port=" << sc._clientListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(_clientListen);
    options._maxSessions = 1000;
    options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
    {
        ClientPulse pulse;
        WriteStream ws(pulse.getProtoID());
        ws << pulse;
        session->send(ws.getStream(), ws.getStreamLen());
    };
    options._sessionOptions._onSessionLinked = std::bind(&SpaceMgr::event_onClientLinked, this, _1);
    options._sessionOptions._onSessionClosed = std::bind(&SpaceMgr::event_onClientClosed, this, _1);
    options._sessionOptions._onBlockDispatch = std::bind(&SpaceMgr::event_onClientMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(_clientListen))
    {
        LOGE("SpaceMgr::startClientListen openAccepter error. bind ip=" << sc._clientListenHost << ", bind port=" << sc._clientListenPort);
        return false;
    }
    LOGA("SpaceMgr::startClientListen openAccepter success. bind ip=" << sc._clientListenHost << ", bind port=" << sc._clientListenPort
        <<", _clientListen=" << _clientListen);
    return true;
}



bool SpaceMgr::startWorldConnect()
{
    auto wc = ServerConfig::getRef().getWorldConfig();
    
    SessionID worldID= SessionManager::getRef().addConnecter(wc._spaceListenHost, wc._spaceListenPort);
    if (worldID == InvalidSessionID)
    {
        LOGE("SpaceMgr::startWorldConnect openConnecter error. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getConnecterOptions(worldID);
    options._sessionPulseInterval = 5000;
    options._onSessionPulse = [](TcpSessionPtr session)
    {
        DockerPulse pulse;
        WriteStream ws(pulse.getProtoID());
        ws << pulse;
        session->send(ws.getStream(), ws.getStreamLen());
    };
    options._onSessionLinked = std::bind(&SpaceMgr::event_onWorldLinked, this, _1);
    options._onSessionClosed = std::bind(&SpaceMgr::event_onWorldClosed, this, _1);
    options._onBlockDispatch = std::bind(&SpaceMgr::event_onWorldMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openConnecter(worldID))
    {
        LOGE("SpaceMgr::startWorldConnect openConnecter error. bind ip=" << wc._spaceListenHost << ", bind port=" << wc._spaceListenPort);
        return false;
    }
    LOGA("SpaceMgr::startWorldConnect openAccepter success. bind ip=" << wc._spaceListenHost 
        << ", bind port=" << wc._spaceListenPort <<", openConnecter=" << worldID);
    return true;
}


void SpaceMgr::sendToSession(SessionID sessionID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sessionID, block, len);
}

bool SpaceMgr::start()
{
    return startClientListen() && startWorldConnect();
}

void SpaceMgr::event_onWorldLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_AREA_ID, InvalidAreaID);

    SpaceInfoToWorldNotice notice;
    notice.host = ServerConfig::getRef().getSpaceConfig()._clientPubHost;
    notice.port = ServerConfig::getRef().getSpaceConfig()._clientListenPort;
    for (auto kv : _spaces)
    {
    }
    sendToSession(session->getSessionID(), notice);
    LOGI("event_onWorldLinked cID=" << session->getSessionID() );
}


void SpaceMgr::event_onWorldClosed(TcpSessionPtr session)
{


}


void SpaceMgr::event_onWorldMessage(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rsShell(begin, len);
    if (DockerPulse::getProtoID() != rsShell.getProtoID())
    {
        LOGT("event_onWorldMessage protoID=" << rsShell.getProtoID() << ", len=" << len);
    }

    if (rsShell.getProtoID() == DockerPulse::getProtoID())
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, getNowTime());
        return;
    }
    else if (rsShell.getProtoID() == FillUserToSpaceNotice::getProtoID())
    {

    }

}









void SpaceMgr::event_onClientLinked(TcpSessionPtr session)
{
    LOGD("SpaceMgr::event_onClientLinked. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}

void SpaceMgr::event_onClientPulse(TcpSessionPtr session)
{
    auto last = session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME);
    if (getNowTime() - (time_t)last > session->getOptions()._sessionPulseInterval * 3)
    {
        LOGW("client timeout . diff time=" << getNowTime() - (time_t)last << ", sessionID=" << session->getSessionID());
        session->close();
        return;
    }
}
void SpaceMgr::event_onClientClosed(TcpSessionPtr session)
{
    LOGD("SpaceMgr::event_onClientClosed. SessionID=" << session->getSessionID() 
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



void SpaceMgr::event_onClientMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    if (rs.getProtoID() == SpaceInfoToWorldNotice::getProtoID())
    {
        SpaceInfoToWorldNotice notice;
        rs >> notice;

    }
    SessionStatus sessionStatus = (SessionStatus) session->getUserParamNumber(UPARAM_SESSION_STATUS);
 
    {
        LOGE("client unknow proto or wrong status. protoID=" << rs.getProtoID() << ", status=" << sessionStatus << ", sessionID=" << session->getSessionID());
    }
}




