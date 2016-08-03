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
    resp.fromAvatarID = getServiceID();
    resp.msg = req.msg;
    toService(STClient, req.avatarID, resp);
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















