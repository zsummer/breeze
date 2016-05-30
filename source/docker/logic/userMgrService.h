
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



struct UserStatus
{
    int _status = 0; //0 no Client no UserService,  1 Creating UserService, 2 normal, 3 destroying 
    UserPreview _preview;
};





class UserMgrService : public Service
{
public:
    UserMgrService();
    ~UserMgrService();
    bool onInit() override final;
    void onUninit() override final;
    void onTick() override final;
public:
    void onSelectUserPreviewsFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onSelectUserPreviewsFromUserMgrReqFromDB(zsummer::proto4z::ReadStream &, const Tracing & trace, const SelectUserPreviewsFromUserMgrReq & req);
    void onCreateUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onSelectUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
public:
    time_t _lastTime = 0;
    std::map<ui64, UserStatus> _userStatus;
    std::map<std::string, ui64> _userName;
    std::map<std::string, UserPreviewArray> _accountPreviews;
    Balance _balance;
};





































#endif
