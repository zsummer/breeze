
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





#ifndef _SPACE_SERVICE_H_
#define _SPACE_SERVICE_H_
#include <common.h>
#include "service.h"
#include "module.h"
#include <ProtoOffline.h>
#include <ProtoDBService.h>

/*
SpaceService
    提供离线协议驻留.
    比如给一个userservice发送离线消息,邮件等, 只需要检测玩家service没有装载直接发到该服务即可, 对应的玩家service装载后 会自动推送过去. 
*/

class SpaceService : public Service
{
public:
    SpaceService();
    ~SpaceService();
    bool onLoad() override final;
    void onModuleLoad(bool success, const std::string & moduleName);
    void onClientChange() override final;
    void onUnload() override final;
    void onTick() override final;
private:
    void onLoadMaxOfflineID(zsummer::proto4z::ReadStream &);
    void onUserOffline(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onInsert(bool success, const UserOffline & offline);
    void onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &);


private:
    ui64 _offlineNextID = 0;
    ModuleMultiData<UserOffline> _offlines;
};

































#endif
