
#include "world.h"

#include <ProtoClient.h>
#include <ProtoDocker.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneServer.h>


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
    if (_sceneListen != InvalidAccepterID)
    {
        SessionManager::getRef().stopAccept(_sceneListen);
        SessionManager::getRef().kickClientSession(_sceneListen);
    }
    SessionManager::getRef().stop();
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
    options._sessionOptions._sessionPulseInterval = ServerPulseInterval;
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



bool World::startSceneListen()
{
    auto wc = ServerConfig::getRef().getWorldConfig();

    _sceneListen = SessionManager::getRef().addAccepter(wc._sceneListenHost, wc._sceneListenPort);
    if (_sceneListen == InvalidAccepterID)
    {
        LOGE("World::startSceneListen addAccepter error. bind ip=" << wc._sceneListenHost << ", bind port=" << wc._sceneListenPort);
        return false;
    }
    auto &options = SessionManager::getRef().getAccepterOptions(_sceneListen);
    options._maxSessions = 1000;
    options._sessionOptions._sessionPulseInterval = ServerPulseInterval;
    options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
    {
		if (getFloatSteadyNowTime() - session->getUserParamDouble(UPARAM_LAST_ACTIVE_TIME) > ServerPulseInterval *3.0 / 1000.0)
		{
			LOGE("World check session last active timeout. diff=" << getFloatNowTime() - session->getUserParamDouble(UPARAM_LAST_ACTIVE_TIME));
			session->close();
			return;
		}
        ScenePulse pulse;
        WriteStream ws(pulse.getProtoID());
        ws << pulse;
        session->send(ws.getStream(), ws.getStreamLen());
    };
    options._sessionOptions._onSessionLinked = std::bind(&World::event_onSceneLinked, this, _1);
    options._sessionOptions._onSessionClosed = std::bind(&World::event_onSceneClosed, this, _1);
    options._sessionOptions._onBlockDispatch = std::bind(&World::event_onSceneMessage, this, _1, _2, _3);
    if (!SessionManager::getRef().openAccepter(_sceneListen))
    {
        LOGE("World::startSceneListen openAccepter error. bind ip=" << wc._sceneListenHost << ", bind port=" << wc._sceneListenPort);
        return false;
    }
    LOGA("World::startSceneListen openAccepter success. bind ip=" << wc._sceneListenHost 
        << ", bind port=" << wc._sceneListenPort <<", _sceneListen=" << _sceneListen);
    return true;
}

void World::sendViaSessionID(SessionID sessionID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sessionID, block, len);
}
void World::toService(SessionID sessionID, const Tracing &trace, const char * block, unsigned int len)
{
	WriteStream fd(ForwardToService::getProtoID());
	fd << trace;
	fd.appendOriginalData(block, len);
	sendViaSessionID(sessionID, fd.getStream(), fd.getStreamLen());
}

bool World::start()
{
    return startDockerListen() && startSceneListen();
}

void World::event_onDockerLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_AREA_ID, InvalidAreaID);
	session->setUserParam(UPARAM_DOCKER_ID, InvalidDockerID);
    LoadServiceNotice notice;
    ServiceInfo info;
    info.serviceDockerID = InvalidDockerID;
    info.serviceType = STWorldMgr;
    info.serviceID = InvalidServiceID;
    info.serviceName = "STWorldMgr";
    info.clientDockerID = InvalidDockerID;
    info.clientSessionID = InvalidSessionID;
    info.status = SS_WORKING;
    notice.shellServiceInfos.push_back(info);
    sendViaSessionID(session->getSessionID(), notice);

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
    if (ScenePulse::getProtoID() != rsShell.getProtoID())
    {
        LOGT("event_onDockerMessage protoID=" << rsShell.getProtoID() << ", len=" << len);
    }

    if (rsShell.getProtoID() == ScenePulse::getProtoID())
    {
        session->setUserParamDouble(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
        return;
    }
    else if (rsShell.getProtoID() == DockerKnock::getProtoID())
    {
        DockerKnock knock;
        rsShell >> knock;
        LOGA("DockerKnock sessionID=" << session->getSessionID() << ", areaID=" << knock.areaID << ",dockerID=" << knock.dockerID);
		session->setUserParam(UPARAM_AREA_ID, knock.areaID);
		session->setUserParam(UPARAM_DOCKER_ID, knock.dockerID);

    }
    else if (rsShell.getProtoID() == LoadServiceNotice::getProtoID())
    {
        AreaID areaID = (ui32)session->getUserParamNumber(UPARAM_AREA_ID);
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
        event_onServiceForwardMessage(session, trace, rs);
    }
}



std::shared_ptr<AvatarSceneTokenStatus> World::getAvatarToken(AreaID areaID, ServiceID serviceID)
{
	auto founder = _avatarToken.find(areaID);
	if (founder == _avatarToken.end())
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



void World::event_onServiceForwardMessage(TcpSessionPtr   session, const Tracing & trace, ReadStream & rs)
{
	AreaID areaID = (AreaID)session->getUserParamNumber(UPARAM_AREA_ID);
	if (areaID == InvalidAreaID)
	{
		LOGE("event_onServiceForwardMessage: docker session not knock world. sessionID=" << session->getSessionID() << ", cur proto ID=" << rs.getProtoID());
		return;
	}
	if (trace.oob.clientAvatarID == InvalidServiceID)
	{
		LOGE("event_onServiceForwardMessage: trace have not oob. sessionID=" << session->getSessionID() << ", cur proto ID=" << rs.getProtoID());
		return;
	}
    if (rs.getProtoID() == GetSceneTokenInfoReq::getProtoID())
    {
		GetSceneTokenInfoReq req;
		rs >> req;
		GetSceneTokenInfoResp resp;
		resp.retCode = EC_SUCCESS;
		resp.tokenInfo.sceneType = SCENE_TYPE_NONE;
		resp.tokenInfo.sceneStatus = SCENE_STATUS_NONE;
		auto token = getAvatarToken(areaID, trace.oob.clientAvatarID);
		if (token)
		{
			resp.tokenInfo = token->token;
		}
		backToService(session->getSessionID(), trace, resp);
		return;
    }
	else if (rs.getProtoID() == JoinSceneReq::getProtoID())
	{
		JoinSceneReq req;
		rs >> req;
		JoinSceneResp resp;
		auto token = getAvatarToken(areaID, trace.oob.clientAvatarID);
		if (!token)
		{
			token = std::make_shared<AvatarSceneTokenStatus>();
			token->token.sceneType = SCENE_TYPE_NONE;
			token->token.sceneStatus = SCENE_STATUS_NONE;
			_avatarToken[areaID][trace.oob.clientAvatarID] = token;
		}
		double now = getFloatSteadyNowTime();
		if (now - token->lastSwitchTime < 5.0)
		{
			resp.retCode = EC_ERROR;
			backToService(session->getSessionID(), trace, resp);
			return;
		}
		if (token->token.sceneType != SCENE_TYPE_NONE)
		{

		}
		return;
	}
}









void World::event_onSceneLinked(TcpSessionPtr session)
{
    LOGD("World::event_onSceneLinked. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}
void World::event_onScenePulse(TcpSessionPtr session)
{
    auto last = session->getUserParamDouble(UPARAM_LAST_ACTIVE_TIME);
    if (getFloatSteadyNowTime() - last > session->getOptions()._sessionPulseInterval * 3)
    {
        LOGW("client timeout . diff time=" << getFloatSteadyNowTime() - last << ", sessionID=" << session->getSessionID());
        session->close();
        return;
    }
}
void World::event_onSceneClosed(TcpSessionPtr session)
{
    LOGD("World::event_onSceneClosed. SessionID=" << session->getSessionID() 
        << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
    if (isConnectID(session->getSessionID()))
    {
        LOGF("Unexpected");
    }
    else
    {
		while (session->getUserParamNumber(UPARAM_SCENE_ID) != InvalidSceneID)
		{
			auto founder = _scenes.find((SceneID)session->getUserParamNumber(UPARAM_SCENE_ID));
			if (founder == _scenes.end())
			{
				break;
			}
            founder->second.sessionID = InvalidSessionID;
            _homeBalance.disableNode(founder->second.knock.sceneID);
            _otherBalance.disableNode(founder->second.knock.sceneID);
			break;
		}

    }
}


void World::event_onSceneMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    if (rs.getProtoID() == AllocateSceneResp::getProtoID())
    {

    }
	else if (rs.getProtoID() == SceneKnock::getProtoID())
	{
		SceneKnock knock;
		rs >> knock;
		session->setUserParam(UPARAM_SCENE_ID, knock.sceneID);
        SceneSessionStatus status;
        status.sessionID = session->getSessionID();
        status.knock = knock;
		_scenes[knock.sceneID] = status;
        _homeBalance.enableNode(knock.sceneID);
        _otherBalance.enableNode(knock.sceneID);
	}

}





