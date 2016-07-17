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
#include <ProtoUser.h>
#include <ProtoSpaceCommon.h>
#include <ProtoSpaceServer.h>
#include <ProtoSpaceClient.h>
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
    void pickProto(EntityFullInfo & info);
    UserBaseInfo _base;
    EntityInfo  _info;
    EntityControl _control;
    EntityReport _report;
    SessionID _clientSessionID = InvalidSessionID;
    std::string _token;
    bool _isClientDirty = false;
};

using EntityPtr = std::shared_ptr<Entity>;


































#endif
