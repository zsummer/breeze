

/*
* breeze License
* Copyright (C) 2014-2016 YaweiZhang <yawei.zhang@foxmail.com>.
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

/*
*  file desc
*  common header file.
*
*/

#ifndef _COMMON_H_
#define _COMMON_H_




#include "defined.h"
#include "utls.h"
#include "single.h"
#include "genID.h"
#include <proto4z/dbHelper.h>
#include "md5/md5.h"
#include "dbAsync.h"
#include "balance.h"
#include "config.h"
#include <ProtoCommon.h>
#include <slot.h>





const int MAX_ACCOUNT_USERS = 5;
struct UserInfo
{
    BaseInfo base;
    SessionToken token;
    SessionID sID = InvalidSessionID;
};
using UserInfoPtr = std::shared_ptr<UserInfo>;
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserInfo & info)
{
    return stm;
}
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserInfoPtr & info)
{
    return stm;
}




#endif
