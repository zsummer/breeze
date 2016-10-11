
#include "world.h"

#include <ProtoClient.h>
#include <ProtoDocker.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneServer.h>


World::World()
{
    _matchPools.resize(SCENE_MAX);
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
    _matchTimerID = SessionManager::getRef().createTimer(1000, std::bind(&World::onMatchTimer, this));
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
    options._sessionOptions._sessionPulseInterval = (unsigned int)(ServerPulseInterval * 1000);
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
    options._sessionOptions._sessionPulseInterval = (unsigned int)(ServerPulseInterval * 1000);
    options._sessionOptions._onSessionPulse = [](TcpSessionPtr session)
    {
		if (getFloatSteadyNowTime() - session->getUserParamDouble(UPARAM_LAST_ACTIVE_TIME) > ServerPulseInterval *3.0 )
		{
			LOGE("World check session last active timeout. diff=" << getFloatSteadyNowTime() - session->getUserParamDouble(UPARAM_LAST_ACTIVE_TIME));
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
    session->setUserParamDouble(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
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
    if (rsShell.getProtoID() == DockerKnock::getProtoID())
    {
        DockerKnock knock;
        rsShell >> knock;
        LOGA("DockerKnock sessionID=" << session->getSessionID() << ", areaID=" << knock.areaID << ",dockerID=" << knock.dockerID);
		session->setUserParam(UPARAM_AREA_ID, knock.areaID);
		session->setUserParam(UPARAM_DOCKER_ID, knock.dockerID);

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
        event_onServiceForwardMessage(session, trace, rs);
    }
}

SceneGroupInfoPtr World::getGroupInfoByAvatarID(ServiceID serviceID)
{
    auto founder = _avatars.find(serviceID);
    if (founder == _avatars.end())
    {
        return nullptr;
    }
    return getGroupInfo(founder->second);
}

SceneLineInfoPtr World::getLineInfo(LineID lineID)
{
    auto founder = _lines.find(lineID);
    if (founder != _lines.end())
    {
        return founder->second;
    }
    return nullptr;
}

SceneLineInfoPtr World::pickHomeLineNode(double step, double autoAdd)
{
    LineID id = _homeBalance.pickNode(step, autoAdd);
    if (id == InvalidLineID)
    {
        return nullptr;
    }
    return getLineInfo(id);
}

SceneLineInfoPtr World::pickOtherLineNode(double step, double autoAdd)
{
    LineID id = _otherBalance.pickNode(step, autoAdd);
    if (id == InvalidLineID)
    {
        return nullptr;
    }
    return getLineInfo(id);
}


SceneGroupInfoPtr World::getGroupInfo(GroupID groupID)
{
    auto founder = _groups.find(groupID);
    if (founder == _groups.end())
    {
        return nullptr;
    }
    return founder->second;
}

void World::pushGroupInfoToClient(SceneGroupInfoPtr groupPtr)
{
    if (!groupPtr)
    {
        return;
    }
    SceneGroupInfoNotice notice(*groupPtr);
    for (auto &kv : groupPtr->members)
    {
        toService(kv.second.areaID, STAvatarMgr, STAvatar, kv.second.baseInfo.avatarID, notice);
    }
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
    if (rs.getProtoID() == SceneServerJoinGroupIns::getProtoID())
    {
        SceneServerJoinGroupIns ins;
        rs >> ins;
        onSceneServerJoinGroupIns(session, trace, ins);
        return;
    }
    else if (rs.getProtoID() == ChatReq::getProtoID())
    {
        ChatReq req;
        rs >> req;
        onChatReq(session, trace, req);
        return;
    }
    else if (rs.getProtoID() == SceneGroupGetStatusReq::getProtoID())
    {
        SceneGroupGetStatusReq req;
        rs >> req;
        onSceneGroupGetStatusReq(session, trace, req);
        return;
    }
    else if (rs.getProtoID() == SceneGroupEnterSceneReq::getProtoID())
    {
        SceneGroupEnterSceneReq req;
        rs >> req;
        onSceneGroupEnterSceneReq(session, trace, req);
        return;
    }
    else if (rs.getProtoID() == SceneGroupCancelEnterReq::getProtoID())
    {
        SceneGroupCancelEnterReq req;
        rs >> req;
        onSceneGroupCancelEnterReq(session, trace, req);
        return;
    }
    else if (rs.getProtoID() == SceneGroupInviteReq::getProtoID())
    {
        SceneGroupInviteReq req;
        rs >> req;
        onSceneGroupInviteReq(session, trace, req);
        return;
    }
    else if (rs.getProtoID() == SceneGroupRejectReq::getProtoID())
    {
        SceneGroupRejectReq req;
        rs >> req;
        onSceneGroupRejectReq(session, trace, req);
        return;
    }
    else if (rs.getProtoID() == SceneGroupLeaveReq::getProtoID())
    {
        SceneGroupLeaveReq req;
        rs >> req;
        onSceneGroupLeaveReq(session, trace, req);
        return;
    }
    
}


void World::event_onSceneLinked(TcpSessionPtr session)
{
    session->setUserParamDouble(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
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
			auto founder = _lines.find((SceneID)session->getUserParamNumber(UPARAM_SCENE_ID));
			if (founder == _lines.end() || !founder->second)
			{
				break;
			}
            founder->second->sessionID = InvalidSessionID;
            _homeBalance.disableNode(founder->second->knock.lineID);
            _otherBalance.disableNode(founder->second->knock.lineID);
			break;
		}

    }
}


void World::event_onSceneMessage(TcpSessionPtr session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    if (rs.getProtoID() == SceneServerGroupStatusChangeIns::getProtoID())
    {
        SceneServerGroupStatusChangeIns ins;
        rs >> ins;
        auto group = getGroupInfo(ins.groupID);
        if (group->sceneStatus == SCENE_STATE_ALLOCATE && ins.status == SCENE_STATE_WAIT)
        {
            group->sceneID = ins.sceneID;
            group->sceneStatus = ins.status;
            pushGroupInfoToClient(group);
        }
        else if (group->sceneStatus == SCENE_STATE_WAIT && ins.status == SCENE_STATE_ACTIVE)
        {
            group->sceneStatus = ins.status;
            pushGroupInfoToClient(group);
        }
        else if (group->sceneStatus == SCENE_STATE_ACTIVE && ins.status == SCENE_STATE_NONE)
        {
            group->sceneStatus = ins.status;
            group->sceneType = SCENE_NONE;
            pushGroupInfoToClient(group);
            //write report to db
            //push report to client
        }
    }
	else if (rs.getProtoID() == SceneKnock::getProtoID())
	{
		SceneKnock knock;
		rs >> knock;
		session->setUserParam(UPARAM_SCENE_ID, knock.lineID);
        SceneLineInfoPtr line = std::make_shared<SceneLineInfo>();
        line->sessionID = session->getSessionID();
        line->knock = knock;
        _lines[knock.lineID] = line;
        _homeBalance.enableNode(knock.lineID);
        _otherBalance.enableNode(knock.lineID);
	}
    else if (rs.getProtoID() == ScenePulse::getProtoID())
    {
        session->setUserParamDouble(UPARAM_LAST_ACTIVE_TIME, getFloatSteadyNowTime());
    }
    else if (rs.getProtoID() == ChatResp::getProtoID())
    {
        ChatResp resp;
        rs >> resp;

        auto group = getGroupInfoByAvatarID(resp.targetID);
        if (group)
        {
            for ( auto &mber : group->members)
            {
                if (mber.second.baseInfo.avatarID == resp.targetID)
                {
                    toService(mber.second.areaID, STAvatarMgr, STAvatar, resp.targetID, resp);
                    return;
                }
            }
            
        }
        return;
        
    }
}


void World::onMatchTimer()
{
    if (_matchTimerID != InvalidTimerID)
    {
        _matchTimerID = SessionManager::getRef().createTimer(1000, std::bind(&World::onMatchTimer, this));
    }
    onMatchHomeTimer();
    onMatchMeleeTimer();
    onMatchArenaTimer();
}

void World::onMatchHomeTimer()
{
    auto &pool = _matchPools[SCENE_HOME];
    const size_t MatchCount = 1;
    while (pool.size() >= MatchCount)
    {
        auto linePtr = pickHomeLineNode(30, 1);
        if (!linePtr)
        {
            break;
        }
        SceneServerEnterSceneIns ins;
        ins.mapID = InvalidMapID;
        ins.sceneType = SCENE_HOME;
        for (size_t i = 0; i < MatchCount; i++)
        {
            auto groupPtr = pool.front();
            pool.pop_front();
            groupPtr->sceneStatus = SCENE_STATE_CHOISE;
            groupPtr->sceneStatus = SCENE_STATE_ALLOCATE;
            groupPtr->lineID = linePtr->knock.lineID;
            groupPtr->host = linePtr->knock.pubHost;
            groupPtr->port = linePtr->knock.pubPort;
            ins.mapID = groupPtr->mapID;
            ins.groups.push_back(*groupPtr);
            pushGroupInfoToClient(groupPtr);
        }
        sendViaSessionID(linePtr->sessionID, ins);
    }
}

void World::onMatchMeleeTimer()
{
    auto &pool = _matchPools[SCENE_MELEE];
    const size_t MatchCount = 6;
    while (pool.size() >= MatchCount)
    {
        auto linePtr = pickOtherLineNode(1, 1);
        if (!linePtr)
        {
            break;
        }
        SceneServerEnterSceneIns ins;
        ins.mapID = InvalidMapID;
        ins.sceneType = SCENE_MELEE;
        for (size_t i = 0; i < MatchCount; i++)
        {
            auto groupPtr = pool.front();
            pool.pop_front();
            groupPtr->sceneStatus = SCENE_STATE_CHOISE;
            groupPtr->sceneStatus = SCENE_STATE_ALLOCATE;
            groupPtr->lineID = linePtr->knock.lineID;
            groupPtr->host = linePtr->knock.pubHost;
            groupPtr->port = linePtr->knock.pubPort;
            ins.mapID = groupPtr->mapID;
            ins.groups.push_back(*groupPtr);
            pushGroupInfoToClient(groupPtr);
        }
        sendViaSessionID(linePtr->sessionID, ins);
    }
}

void World::onMatchArenaTimer()
{
    auto &pool = _matchPools[SCENE_ARENA];
    const size_t MatchCount = 2;
    while (pool.size() >= MatchCount)
    {
        auto linePtr = pickOtherLineNode(1, 1);
        if (!linePtr)
        {
            break;
        }
        SceneServerEnterSceneIns ins;
        ins.mapID = InvalidMapID;
        ins.sceneType = SCENE_ARENA;
        for (size_t i = 0; i < MatchCount; i++)
        {
            auto groupPtr = pool.front();
            pool.pop_front();
            groupPtr->sceneStatus = SCENE_STATE_CHOISE;
            groupPtr->sceneStatus = SCENE_STATE_ALLOCATE;
            groupPtr->lineID = linePtr->knock.lineID;
            groupPtr->host = linePtr->knock.pubHost;
            groupPtr->port = linePtr->knock.pubPort;
            ins.mapID = groupPtr->mapID;
            ins.groups.push_back(*groupPtr);
            pushGroupInfoToClient(groupPtr);
        }
        sendViaSessionID(linePtr->sessionID, ins);
    }
}


void World::onChatReq(TcpSessionPtr session, const Tracing & trace, ChatReq & req)
{
    SceneGroupInfoPtr groupPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if (!groupPtr)
    {
        LOGE("World::onChatReq not found the avatar's group info. avatar=" << trace.oob.clientAvatarID);
        return;
    }

    ChatResp resp;
    resp.channelID = req.channelID;
    resp.chatTime = time(NULL);
    resp.msg = req.msg;
    resp.sourceID = trace.oob.clientAvatarID;
    for (auto &kv : groupPtr->members)
    {
        if (kv.second.baseInfo.avatarID == trace.oob.clientAvatarID)
        {
            resp.sourceName = kv.second.baseInfo.avatarName;
            break;
        }
    }


    if (req.channelID == CC_GROUP)
    {

        for (auto &kv : groupPtr->members)
        {
            if (kv.second.baseInfo.avatarID == trace.oob.clientAvatarID)
            {
                resp.targetID = kv.second.baseInfo.avatarID;
                resp.targetName = kv.second.baseInfo.avatarName;
                toService(kv.second.areaID, STAvatarMgr, STAvatar, resp.targetID, resp);
            }
        }
    }
    else 
    {
        auto line = getLineInfo(groupPtr->lineID);
        if (line)
        {
            sendViaSessionID(line->sessionID, resp);  // to scene server
        }
    }
}

void World::onSceneServerJoinGroupIns(TcpSessionPtr session, const Tracing & trace, SceneServerJoinGroupIns & req)
{
    SceneServerJoinGroupAck ack;
    ack.oldGroupID = req.groupID;
    ack.newGroupID = InvalidGroupID;
    ack.retCode = EC_SUCCESS;

    SceneGroupInfoPtr groupPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if ((groupPtr && req.groupID == InvalidGroupID) || (groupPtr&& req.groupID != InvalidGroupID && groupPtr->sceneStatus != SCENE_STATE_NONE))
    {
        LOGE("World::onSceneServerJoinGroupIns the avatar already had group. avatar=" << trace.oob.clientAvatarID);
        ack.retCode = EC_ERROR;
        backToService(session->getSessionID(), trace, ack);
        return;
    }
    SceneGroupAvatarInfo avatar;
    avatar.areaID = session->getUserParamNumber(UPARAM_AREA_ID);
    avatar.baseInfo = req.baseInfo;
    avatar.baseProps = req.baseProps;
    avatar.powerType = 1; //leader
    avatar.token = toMD5(avatar.baseInfo.avatarName + toString(rand()));

    

    if (req.groupID == InvalidGroupID)
    {
        groupPtr = std::make_shared<SceneGroupInfo>();
        auto &group = *groupPtr;
        group.groupID = ++_lastGroupID;
        group.sceneType = SCENE_NONE;
        group.sceneStatus = SCENE_STATE_NONE;
        group.sceneID = InvalidSceneID;
        group.lineID = InvalidLineID;
        group.mapID = InvalidMapID;
        group.host;
        group.port = 0;
        group.members.insert(std::make_pair(avatar.baseInfo.avatarID,avatar));
        
        _avatars[avatar.baseInfo.avatarID] = group.groupID;
        _groups[group.groupID] = groupPtr;
        
        ack.newGroupID = group.groupID;
        backToService(session->getSessionID(), trace, ack);
        pushGroupInfoToClient(groupPtr);

        return;
    }

    if (groupPtr)
    {
        _avatars.erase(req.baseInfo.avatarID);
        _groups.erase(groupPtr->groupID);
    }
    groupPtr = getGroupInfo(req.groupID);
    if (!groupPtr )
    {
        LOGE("World::onSceneServerJoinGroupIns the dst group not group. avatar=" << trace.oob.clientAvatarID << ", groupID=" << req.groupID);
        ack.retCode = EC_ERROR;
        backToService(session->getSessionID(), trace, ack);
        return;
    }
    if (groupPtr->invitees.find(req.baseInfo.avatarID) == groupPtr->invitees.end())
    {
        LOGE("World::onSceneServerJoinGroupIns the dst group not invite the avatar. avatar=" << trace.oob.clientAvatarID << ", groupID=" << req.groupID);
        ack.retCode = EC_ERROR;
        backToService(session->getSessionID(), trace, ack);
        return;
    }
    if (groupPtr->sceneStatus != SCENE_STATE_NONE)
    {
        LOGE("World::onSceneServerJoinGroupIns the dst group status busy. avatar=" << trace.oob.clientAvatarID << ", groupID=" << req.groupID);
        ack.retCode = EC_ERROR;
        backToService(session->getSessionID(), trace, ack);
        return;
    }
    auto founder = groupPtr->members.find(req.baseInfo.avatarID);
    if (founder == groupPtr->members.end())
    {
        if (groupPtr->members.size() > 10) //组队上限  
        {
            LOGE("World::onSceneServerJoinGroupIns the dst group members already full. avatar=" << trace.oob.clientAvatarID << ", groupID=" << req.groupID);
            ack.retCode = EC_ERROR;
            backToService(session->getSessionID(), trace, ack);
            return;
        }
        if (!groupPtr->members.empty())
        {
            avatar.powerType = 0;
        }
        groupPtr->members.insert(std::make_pair(avatar.baseInfo.avatarID, avatar));
    }
    else
    {
        founder->second.areaID = avatar.areaID;
        founder->second.baseInfo = avatar.baseInfo;
        founder->second.baseProps = avatar.baseProps;
        founder->second.token;
    }
    _avatars[req.baseInfo.avatarID] = groupPtr->groupID;
    backToService(session->getSessionID(), trace, ack); 
    pushGroupInfoToClient(groupPtr);
}



void World::onSceneGroupGetStatusReq(TcpSessionPtr session, const Tracing & trace, SceneGroupGetStatusReq & req)
{
    SceneGroupGetStatusResp resp;
    SceneGroupInfoNotice notice;
    resp.retCode = EC_SUCCESS;
    notice.groupInfo.groupID = InvalidGroupID;
    notice.groupInfo.sceneType = SCENE_NONE;
    notice.groupInfo.sceneStatus = SCENE_STATE_NONE;
    auto groupInfoPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if (groupInfoPtr)
    {
        notice.groupInfo = *groupInfoPtr;
    }
    backToService(session->getSessionID(), trace, resp);
    backToService(session->getSessionID(), trace, notice);
    return;
}

void World::onSceneGroupEnterSceneReq(TcpSessionPtr session, const Tracing & trace, SceneGroupEnterSceneReq & req)
{
    SceneGroupInfoPtr groupPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if (!groupPtr)
    {
        LOGE("World::onSceneGroupEnterSceneReq not found the avatar  group. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }
    if (req.sceneType >= SCENE_MAX || req.sceneType == SCENE_NONE)
    {
        LOGE("World::onSceneGroupEnterSceneReq the scene type error. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }
    if (groupPtr->sceneStatus != SCENE_STATE_NONE)
    {
        LOGE("World::onSceneGroupEnterSceneReq the group is busy. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }
    auto found = groupPtr->members.find(trace.oob.clientAvatarID);
    if (found == groupPtr->members.end())
    {
        LOGE("World::onSceneGroupEnterSceneReq the group is busy. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }
    if (found->second.powerType != 1)
    {
        LOGE("World::onSceneGroupEnterSceneReq the avatar no power. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }
    if (req.sceneType == SCENE_MELEE && groupPtr->members.size() > 1)
    {
        LOGE("World::onSceneGroupEnterSceneReq the goup had too many member. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }
    if (req.sceneType == SCENE_ARENA && groupPtr->members.size() != 3)
    {
        LOGE("World::onSceneGroupEnterSceneReq the goup had too many member. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_ERROR));
        return;
    }


    groupPtr->sceneType = req.sceneType;
    groupPtr->sceneStatus = SCENE_STATE_MATCHING;
    groupPtr->mapID = req.mapID;
    _matchPools[req.sceneType].push_back(groupPtr);
    backToService(session->getSessionID(), trace, SceneGroupEnterSceneResp(EC_SUCCESS));
    pushGroupInfoToClient(groupPtr);
}

void World::onSceneGroupCancelEnterReq(TcpSessionPtr session, const Tracing & trace, SceneGroupCancelEnterReq & req)
{
    SceneGroupInfoPtr groupPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if (!groupPtr)
    {
        LOGE("World::onSceneGroupCancelEnterReq not found the avatar  group. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupCancelEnterResp(EC_ERROR));
        return;
    }
    if (groupPtr->sceneStatus != SCENE_STATE_MATCHING && groupPtr->sceneStatus != SCENE_STATE_NONE)
    {
        LOGE("World::onSceneGroupCancelEnterReq the scene sceneStatus error. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupCancelEnterResp(EC_ERROR));
        return;
    }
    if (groupPtr->sceneType == SCENE_NONE || groupPtr->sceneType >= SCENE_MAX)
    {
        LOGE("World::onSceneGroupCancelEnterReq the scene sceneStatus error. avatar=" << trace.oob.clientAvatarID);
        backToService(session->getSessionID(), trace, SceneGroupCancelEnterResp(EC_ERROR));
        return;
    }
    auto founder = std::find_if(_matchPools[groupPtr->sceneType].begin(), _matchPools[groupPtr->sceneType].end(),
        [groupPtr](SceneGroupInfoPtr gp) {return groupPtr->groupID == gp->groupID; });
    if (founder != _matchPools[groupPtr->sceneType].end())
    {
        _matchPools[groupPtr->sceneType].erase(founder);
    }
    groupPtr->sceneType = SCENE_NONE;
    groupPtr->sceneStatus = SCENE_STATE_NONE;
    groupPtr->mapID = InvalidMapID;
    backToService(session->getSessionID(), trace, SceneGroupCancelEnterResp(EC_SUCCESS));
    pushGroupInfoToClient(groupPtr);

}




void World::onSceneGroupInviteReq(TcpSessionPtr session, const Tracing & trace, SceneGroupInviteReq & req)
{
    SceneGroupInfoPtr groupPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if (!groupPtr)
    {
        LOGE("World::onSceneGroupInviteReq not found the avatar's group info. avatar=" << trace.oob.clientAvatarID);
        return;
    }


    auto found = groupPtr->members.find(trace.oob.clientAvatarID);
    if (found == groupPtr->members.end())
    {
        backToService(session->getSessionID(), trace, SceneGroupInviteResp(EC_ERROR));
        return;
    }
    if (found->second.powerType == 0)
    {
        backToService(session->getSessionID(), trace, SceneGroupInviteResp(EC_ERROR));
        return;
    }
    groupPtr->invitees[req.avatarID] = 0;
    backToService(session->getSessionID(), trace, SceneGroupInviteNotice(found->second.baseInfo.avatarID, found->second.baseInfo.avatarName, groupPtr->groupID));
    pushGroupInfoToClient(groupPtr);
}

void World::onSceneGroupRejectReq(TcpSessionPtr session, const Tracing & trace, SceneGroupRejectReq & req)
{
    SceneGroupInfoPtr groupPtr = getGroupInfo(req.groupID);
    if (!groupPtr)
    {
        LOGE("World::onSceneGroupRejectReq not found the avatar's group info. avatar=" << trace.oob.clientAvatarID);
        return;
    }
    auto found = groupPtr->invitees.find(trace.oob.clientAvatarID);
    if (found == groupPtr->invitees.end())
    {
        return;
    }
    found->second = 1;
    backToService(session->getSessionID(), trace, SceneGroupRejectResp(EC_SUCCESS));
    pushGroupInfoToClient(groupPtr);
}


void World::onSceneGroupLeaveReq(TcpSessionPtr session, const Tracing & trace, SceneGroupLeaveReq & req)
{
    SceneGroupInfoPtr groupPtr = getGroupInfoByAvatarID(trace.oob.clientAvatarID);
    if (!groupPtr)
    {
        LOGE("World::onSceneGroupInviteReq not found the avatar's group info. avatar=" << trace.oob.clientAvatarID);
        return;
    }
    if (groupPtr->sceneStatus != SCENE_STATE_NONE)
    {
        LOGE("World::onSceneGroupLeaveReq the dst group status busy. avatar=" << trace.oob.clientAvatarID << ", groupID=" << groupPtr->groupID);
        backToService(session->getSessionID(), trace, SceneGroupLeaveResp(EC_ERROR));
        return;
    }

    auto found = groupPtr->members.find(trace.oob.clientAvatarID);
    if (found == groupPtr->members.end())
    {
        backToService(session->getSessionID(), trace, SceneGroupLeaveResp(EC_ERROR));
        return;
    }
    auto powerType = found->second.powerType;
    groupPtr->members.erase(found);
    if (powerType == 1 && !groupPtr->members.empty())
    {
        groupPtr->members.begin()->second.powerType = 1;
    }
    backToService(session->getSessionID(), trace, SceneGroupLeaveResp(EC_SUCCESS));
    pushGroupInfoToClient(groupPtr);
}




