
/*
* breeze License
* Copyright (C) 2016 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/





#ifndef _SCENE_MODULE_H_
#define _SCENE_MODULE_H_
#include <common.h>
#include <ProtoSceneServer.h>

class AvatarService;
class SceneModule
{
public:
    void onModuleInit(AvatarService & avatar);
public:
    void onSceneGroupInfoNotice(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);

    void onSceneGroupGetReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupEnterReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupCancelReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);

    void fillGroupInfo(AvatarService & avatar, SceneServerJoinGroupIns& ins);
    void refreshGroupInfo(AvatarService & avatar);
    void onSceneGroupCreateReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupJoinReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupInviteReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupRejectReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupLeaveReq(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);

    void onSceneGroupGetStatusResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupEnterResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupCancelResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);

    void onSceneServerJoinGroupAck(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupInviteResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupInviteNotice(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupRejectResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);
    void onSceneGroupLeaveResp(AvatarService & avatar, const Tracing & trace, zsummer::proto4z::ReadStream & rs);



};



































#endif
