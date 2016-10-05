#include "sceneModule.h"
#include "../avatarService.h"




void SceneModule::onSceneGroupGetStatusReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    if (!Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
    {
        LOGW("STWorldMgr service not open. " << trace);
        avatar.toService(STClient, trace.oob, SceneGroupGetStatusResp(EC_SERVICE_NOT_OPEN));
        return;
    }
    avatar.toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
}













