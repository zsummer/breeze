#include "avatarService.h"
#include <ProtoClient.h>


AvatarService::AvatarService()
{
    slotting<ChatReq>(std::bind(&AvatarService::onChatReq, this, _1, _2));
    slotting<PingPongReq>(std::bind(&AvatarService::onPingPongReq, this, _1, _2));

    slotting<GetSceneTokenInfoReq>(std::bind(&AvatarService::onGetSceneTokenInfoReq, this, _1, _2));
    slotting<JoinSceneReq>(std::bind(&AvatarService::onJoinSceneReq, this, _1, _2));
    slotting<LeaveSceneReq>(std::bind(&AvatarService::onLeaveSceneReq, this, _1, _2));

}

AvatarService::~AvatarService() 
{

}


void AvatarService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    LOGI("AvatarService::onTick");
}




void AvatarService::onClientChange()
{
    if (getClientDockerID() != InvalidDockerID && getClientSessionID() != InvalidSessionID)
    {
        AttachAvatarResp resp(EC_SUCCESS, getServiceID());
        toDocker(getClientDockerID(), resp);
    }
}

bool AvatarService::onLoad()
{
    AvatarBaseInfo ubi;
    ubi.avatarID = getServiceID();
    ubi.userName = getServiceName();
    _baseInfo.loadFromDB(shared_from_this(), ubi, std::bind(&AvatarService::onModuleLoad, std::static_pointer_cast<AvatarService>(shared_from_this()), _1, _2));
    return true;
}

void AvatarService::onUnload()
{
    _baseInfo.writeToDB(std::bind(&AvatarService::onModuleUnload, std::static_pointer_cast<AvatarService>(shared_from_this()), _1, _2));
}


void AvatarService::onModuleLoad(bool success, const std::string & moduleName)
{
    if (success)
    {
        _curLoadModuleCount++;
    }
    else 
    { 
        LOGE(" AvatarService::onModuleLoad false");
        return ; 
    }
    if (_curLoadModuleCount == _totalModuleCount)
    {
        finishLoad();
        AttachAvatarResp resp(EC_SUCCESS, getServiceID());
        toDocker(getClientDockerID(), resp);
    }
    return ;
}


void AvatarService::onModuleUnload(bool success, const std::string & moduleName)
{
    if (success)
    {
        _curUnloadModuleCount++;
    }
    else
    {
        LOGE(" AvatarService::onModuleUnload false");
        return;
    }
    if (_curLoadModuleCount == _totalModuleCount)
    {
        finishUnload();
    }
    return;
}


void AvatarService::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    ChatReq req;
    rs >> req;
    LOGI("onChatReq" << req );
    _baseInfo._data.level++;
    _baseInfo.writeToDB();

    ChatResp resp;
    resp.sourceID = getServiceID();
    resp.sourceName = getServiceName();
    resp.targetID = req.targetID;
    resp.msg = req.msg;
    resp.channelID = req.channelID;
    resp.chatTime = getNowTime();

    double now = getFloatNowTime();
    double limit = 0.0;
    if (req.channelID == CC_PRIVATE) limit = 1.0;
    else if (req.channelID == CC_WORLD) limit = 5.0;

    if (now - _lastChatTime < limit)
    {
        resp.msg = "<color=yellow>chat speed limit " + toString((int)(limit - (now - _lastChatTime))) + " s</color>";
        resp.targetID = getServiceID();
        resp.targetName = getServiceName();
        resp.channelID = CC_SYSTEM;
        resp.sourceID = 0;
        resp.sourceName = "system";
        toService(STClient, getServiceID(), resp);
        return;
    }



    _lastChatTime = now;
    if (req.channelID == CC_PRIVATE)
    {
        auto tgr = Docker::getRef().peekService(STAvatar, req.targetID);
        if (tgr)
        {
            resp.targetName = tgr->getServiceName();
        }
        toService(STClient, req.targetID, resp);
    }
    else if (req.channelID == CC_WORLD)
    {
        auto onlines = Docker::getRef().peekService(STAvatar);
        for (auto kv : onlines)
        {
            toService(STClient, kv.second->getServiceID(), resp);
        }
    }
    if (true)
    {
        LogChat log;
        log.id = 0;
        log.channelID = resp.channelID;
        log.chatTime = resp.chatTime;
        log.sourceID = resp.sourceID;
        log.sourceName = resp.sourceName;
        log.targetID = resp.targetID;
        log.targetName = resp.targetName;
        log.msg = resp.msg;
        DBQueryReq logReq(log.getDBInsert());
        toService(STLogDBMgr, logReq);
    }
    
}

void AvatarService::onPingPongReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    PingPongReq req;
    rs >> req;
    PingPongResp resp;
    resp.msg = req.msg;
    toService(STClient, getServiceID(), resp);
    static int testCount = 0;
    testCount++;
    if (testCount %10000 == 0)
    {
        LOGA("onPingPongReq " << *this << " count=" << testCount);
    }
}




void AvatarService::onGetSceneTokenInfoReq(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        toService(STClient, trace.oob, GetSceneTokenInfoResp(EC_SERVICE_NOT_OPEN, SceneTokenInfo()));
        return;
    }
    toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}

void AvatarService::onJoinSceneReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        toService(STClient, trace.oob, JoinSceneResp(EC_SERVICE_NOT_OPEN, SceneTokenInfo()));
        return;
    }
    toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}
void AvatarService::onLeaveSceneReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        toService(STClient, trace.oob, LeaveSceneResp(EC_SERVICE_NOT_OPEN, SceneTokenInfo()));
        return;
    }
    toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}















