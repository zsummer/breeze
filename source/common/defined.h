

/*
* breeze License
* Copyright (C) 2014-2015 YaweiZhang <yawei.zhang@foxmail.com>.
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
*  type define
*
*/

#ifndef _INNER_TYPE_DEFINE_H_
#define _INNER_TYPE_DEFINE_H_
#ifdef WIN32
#pragma warning(disable:4996)
#pragma warning(disable:4819)
#endif

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <log4z/log4z.h>
#include <proto4z/proto4z.h>
#include <zsummerX/zsummerX.h>
#include <ProtoCommon.h>

using namespace zsummer::log4z;
using namespace zsummer::network;
using namespace zsummer::proto4z;
using namespace std::placeholders;



//! 基本类型
typedef char i8;
typedef unsigned char ui8;
typedef short i16;
typedef unsigned short ui16;
typedef int i32;
typedef unsigned int ui32;
typedef long long i64;
typedef unsigned long long ui64;

//! 逻辑类型
typedef ui64 UserID;
const ui64 InvalidUserID = (UserID)-1;

//服务节点类型
typedef ui16 ServerNode;
const ServerNode InvalidServerNode = (ServerNode)-1;
const ServerNode LogicNode = 0;
const ServerNode StressNode = 1;

//节点索引ID
typedef ui16 NodeIndex;
const NodeIndex InvalidNodeIndex = (NodeIndex)-1;

//DB类型
typedef ui8 DBConfigID;
const DBConfigID InfoDB = 1;
const DBConfigID LogDB = 2;
const DBConfigID InvalidDB = (DBConfigID)-1;


//分区分服的ID
typedef ui16 PlatID;
typedef ui16 AreaID;



enum SessionStatus
{
    SS_UNLOGIN = 0,
    SS_LOGINED,
};


struct InnerUserInfo
{
    UserInfo userInfo;
    SessionToken token;
    SessionID sID = InvalidSeesionID;
    time_t loginTime = 0;
};


inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const InnerUserInfo & info)
{
//    stm << "[UserInfo]" << info.userInfo << " [SessionToken]" << info.token << " sID=" << info.sID << ", loginTime=" << info.loginTime;
    return stm;
}



















#endif
