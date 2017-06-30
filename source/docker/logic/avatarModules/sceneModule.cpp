#include "sceneModule.h"
#include "../avatarService.h"
#include <ProtoSceneServer.h>

void SceneModule::onModuleInit(AvatarService & avatar)
{
    avatar.slotting<SceneGroupInfoNotice>(std::bind(&SceneModule::onSceneGroupInfoNotice, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupGetReq>(std::bind(&SceneModule::onSceneGroupGetReq, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupEnterReq>(std::bind(&SceneModule::onSceneGroupEnterReq, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupCancelReq>(std::bind(&SceneModule::onSceneGroupCancelReq, this, std::ref(avatar), _1, _2));

    avatar.slotting<SceneGroupCreateReq>(std::bind(&SceneModule::onSceneGroupCreateReq, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupJoinReq>(std::bind(&SceneModule::onSceneGroupJoinReq, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupInviteReq>(std::bind(&SceneModule::onSceneGroupInviteReq, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupRejectReq>(std::bind(&SceneModule::onSceneGroupRejectReq, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupLeaveReq>(std::bind(&SceneModule::onSceneGroupLeaveReq, this, std::ref(avatar), _1, _2));

    avatar.slotting<SceneGroupGetResp>(std::bind(&SceneModule::onSceneGroupGetStatusResp, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupEnterResp>(std::bind(&SceneModule::onSceneGroupEnterResp, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupCancelResp>(std::bind(&SceneModule::onSceneGroupCancelResp, this, std::ref(avatar), _1, _2));

    avatar.slotting<SceneServerJoinGroupAck>(std::bind(&SceneModule::onSceneServerJoinGroupAck, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupInviteResp>(std::bind(&SceneModule::onSceneGroupInviteResp, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupInviteNotice>(std::bind(&SceneModule::onSceneGroupInviteNotice, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupRejectResp>(std::bind(&SceneModule::onSceneGroupRejectResp, this, std::ref(avatar), _1, _2));
    avatar.slotting<SceneGroupLeaveResp>(std::bind(&SceneModule::onSceneGroupLeaveResp, this, std::ref(avatar), _1, _2));
}

void SceneModule::onSceneGroupInfoNotice(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupGetReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupGetResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupEnterReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupEnterResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}
void SceneModule::onSceneGroupCancelReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupCancelResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}
void SceneModule::fillGroupInfo(AvatarService & avatar, SceneServerJoinGroupIns& ins)
{
    ins.groupID = InvalidGroupID;
    ins.refresh = 1;
    ins.avatarID = avatar._baseInfo._data.avatarID;
    ins.avatarName = avatar._baseInfo._data.avatarName;
    ins.modelID = avatar._baseInfo._data.modeID;
}
void SceneModule::refreshGroupInfo(AvatarService & avatar)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        return;
    }
    SceneServerJoinGroupIns ins;
    fillGroupInfo(avatar, ins);
    OutOfBand oob;
    oob.clientAvatarID = avatar.getServiceID();
    avatar.toService(STWorldMgr, oob, ins);
}
void SceneModule::onSceneGroupCreateReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupCreateResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    SceneServerJoinGroupIns ins;
    fillGroupInfo(avatar, ins);
    ins.groupID = InvalidGroupID;
    ins.refresh = 0;
    avatar.toService(STWorldMgr, trace.oob, ins);
}

void SceneModule::onSceneGroupJoinReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupJoinResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    SceneGroupJoinReq req;
    rs >> req;
    SceneServerJoinGroupIns ins;
    fillGroupInfo(avatar, ins);
    ins.groupID = req.groupID;
    ins.refresh = 0;
    avatar.toService(STWorldMgr, trace.oob, ins);
}
void SceneModule::onSceneGroupInviteReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupInviteResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}
void SceneModule::onSceneGroupRejectReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupRejectResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}
void SceneModule::onSceneGroupLeaveReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupGetResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupGetStatusResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupEnterResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupCancelResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}


void SceneModule::onSceneServerJoinGroupAck(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    SceneServerJoinGroupAck ack;
    rs >> ack;
    if (ack.oldGroupID == InvalidGroupID)
    {
        avatar.toService(STClient, trace.oob, SceneGroupCreateResp(ack.retCode));
    }
    else
    {
        avatar.toService(STClient, trace.oob, SceneGroupJoinResp(ack.retCode));
    }
}

void SceneModule::onSceneGroupInviteResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupInviteNotice(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupRejectResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}

void SceneModule::onSceneGroupLeaveResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    avatar.toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}










