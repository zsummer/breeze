
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






#ifndef _USER_MGR_SERVICE_H_
#define _USER_MGR_SERVICE_H_
#include <common.h>
#include "service.h"
#include <ProtoUserMgr.h>




/*
UserMgrService
    userService管理器服务. 
*/

struct UserStatus
{
    ui16 _status = SS_NONE;
    DockerID _clientDockerID = InvalidDockerID;
    SessionID _clientSessionID = InvalidSessionID;
    time_t _lastChangeTime = 0;
    UserPreview _preview;
};
using UserStatusPtr = std::shared_ptr<UserStatus>;

struct AccountStatus
{
    ui64 _lastCreateTime = 0;
    std::map<ui64, UserStatusPtr> _users;
};



class UserMgrService : public Service
{
public:
    UserMgrService();
    ~UserMgrService();
    bool onLoad() override final;
    void onLoadUserPreviewsFromDB(zsummer::proto4z::ReadStream & rs, int curLimit, const std::string &sql);
    void onClientChange() override final;
    void onUnload() override final;
    void onTick(TimerID tID, ui32 count, ui32 repeat) override final;

private:
    void updateUserPreview(const UserPreview & pre);
private:
    void onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onClientAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onClientAuthReqFromDB(zsummer::proto4z::ReadStream &, const Tracing & trace, const ClientAuthReq & req);
    void onCreateUserReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onCreateUserReqFromDB(zsummer::proto4z::ReadStream &, const UserBaseInfo & ubi, const Tracing & trace, const CreateUserReq & req);
    void onAttachUserReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onRealClientClosedNotice(const Tracing & trace, zsummer::proto4z::ReadStream &);

private:
    time_t _lastTime = 0;
    std::map<ui64, UserStatusPtr> _freeList;
    std::map<ui64, UserStatusPtr> _userStatusByID;
    std::map<std::string, UserStatusPtr> _userStatusByName;
    std::map<std::string, AccountStatus> _accountStatus;
    ui64 _nextUserID = 0;
};





































#endif
