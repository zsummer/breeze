
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






#ifndef _AVATAR_MGR_SERVICE_H_
#define _AVATAR_MGR_SERVICE_H_
#include <common.h>
#include "service.h"





/*
AvatarMgrService
    userService管理器服务. 
*/

struct AvatarStatus
{
    ui16 _status = SS_NONE;
    DockerID _clientDockerID = InvalidDockerID;
    SessionID _clientSessionID = InvalidSessionID;
    time_t _lastChangeTime = 0;
    AvatarPreview _preview;
};
using AvatarStatusPtr = std::shared_ptr<AvatarStatus>;

struct AccountStatus
{
    ui64 _lastCreateTime = 0;
    std::map<ui64, AvatarStatusPtr> _players;
};
using AccountStatusPtr = std::shared_ptr<AccountStatus>;


class AvatarMgrService : public Service
{
public:
    AvatarMgrService();
    ~AvatarMgrService();
    bool onLoad() override final;
    void onLoadAvatarPreviewsFromDB(zsummer::proto4z::ReadStream & rs, int curLimit, const std::string &sql);
    void onClientChange() override final;
    void onUnload() override final;
    void onTick(TimerID tID, ui32 count, ui32 repeat) override final;
    void checkOfflineList();
    void systemAutoChat();

private:
    void updateAvatarPreview(const AvatarPreview & pre);
private:
    void onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onClientAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onClientAuthReqFromDB(zsummer::proto4z::ReadStream &, const Tracing & trace, const ClientAuthReq & req);
    void onCreateAvatarReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onCreateAvatarReqFromDB(zsummer::proto4z::ReadStream &, const AvatarBaseInfo & ubi, const Tracing & trace, const CreateAvatarReq & req);
    void onAttachAvatarReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onRealClientClosedNotice(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onKickClientsNotice(const Tracing & trace, zsummer::proto4z::ReadStream &);

private:




public:
    AvatarStatusPtr getAvatarStatus(ServiceID avatarID);
    AvatarStatusPtr getAvatarStatus(std::string avatarName);
    AccountStatusPtr getAccountStatus(std::string account);
private:
    double _lastCheckOfflineList = getFloatSteadyNowTime();
    double _lastSystemChat = getFloatSteadyNowTime();
    std::map<ui64, AvatarStatusPtr> _offlineAvatars;
    std::map<ui64, AvatarStatusPtr> _avatarStatusByID;
    std::map<std::string, AvatarStatusPtr> _avatarStatusByName;
    std::map<std::string, AccountStatusPtr> _accountStatus;
    ui64 _nextAvatarID = 0;

public:
    bool isForbid(std::string account);
    bool isForbid(ServiceID avatarID);
private:
    //kickclients with forbid.
    time_t _tmpForbidAllClientTime = 0;
    std::map<std::string, time_t> _tmpForbidAccount;
    std::map<ServiceID, time_t> _tmpForbidAvatar;
};





































#endif
