#include "sceneModule.h"
#include "../avatarService.h"
#include <ProtoSceneServer.h>

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

void SceneModule::refreshGroupInfo(AvatarService & avatar)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        return;
    }
    SceneServerJoinGroupIns ins;
    ins.baseInfo = avatar._baseInfo._data;
    ins.baseProps = avatar._baseProps;
    ins.groupID = InvalidGroupID;
    ins.refresh = 1;
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
    ins.baseInfo = avatar._baseInfo._data;
    ins.baseProps = avatar._baseProps;
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
    ins.baseInfo = avatar._baseInfo._data;
    ins.baseProps = avatar._baseProps;
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










