/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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


#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <common.h>
#include <utls.h>
#include <ProtoCommon.h>
#include <ProtoClient.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneServer.h>
#include <ProtoSceneClient.h>
#include <rvo2/RVO.h>

class Entity
{
public:
    Entity();
    ~Entity();
    double getSpeed();
    double getElapsed(double now);
    double getSuckBlood();
    double getAttack();
    EntityFullData getFullData();
    AvatarBaseInfo _baseInfo;
    AvatarPropMap _baseProps;
    EntityInfo  _info;
    EntityPoint  _point;
    EntityControl _control;
    EntityReport _report;
    SessionID _clientSessionID = InvalidSessionID;
    bool _isClientDirty = false;
    bool _isPointDirty = false;
};

using EntityPtr = std::shared_ptr<Entity>;


































#endif
