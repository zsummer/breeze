
/*
* breeze License
* Copyright (C) 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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





#ifndef _USER_SERVICE_H_
#define _USER_SERVICE_H_
#include <common.h>
#include "service.h"
#include "module.h"
#include "docker.h"




class UserService : public Service
{
public:
    UserService();
    ~UserService();
public:
    bool onLoad() override final;
    void onUnload() override final;
    void onClientChange() override final;
    void onTick() override final;
private:
    void onModuleLoad(bool success, const std::string & moduleName);
    void onModuleUnload(bool success, const std::string & moduleName);
private:
    void onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onUserPingPongReq(const Tracing & trace, zsummer::proto4z::ReadStream &);

private:
    int _curLoadModuleCount = 0;
    int _curUnloadModuleCount = 0;
    int _totalModuleCount = 1;
    ModuleData<UserBaseInfo> _baseInfo;


    int _testCount = 0;
};



































#endif
