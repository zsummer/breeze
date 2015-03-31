

/*
* breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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
#include <algorithm>
#include <zsummerX/zsummerX.h>
#include <ProtoCommon.h>
using namespace zsummer::network;
using namespace zsummer::proto4z;



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
const DBConfigID AuthDB = 0;
const DBConfigID InfoDB = 1;
const DBConfigID LogDB = 2;
const DBConfigID InvalidDB = (DBConfigID)-1;





//分区分服的ID
typedef ui16 PlatID;
typedef ui16 AreaID;






//session info
struct SessionInfo 
{
	//client
	std::string user;
	std::string passwd;
	UserID uid = InvalidUserID;
	SessionID sID = InvalidSeesionID;

	//log timestamp
	time_t authTime = 0;
	time_t loginTime = 0;

	//check active
	time_t lastActiveTime = 0;
	unsigned int lastDelayTick = 0;
};


struct InnerUserInfo
{
	SessionInfo sesionInfo;
	UserInfo userInfo;
	enum InnerUserInfoType
	{
		IUIT_UNAUTH = 0,
		IUIT_AUTHING,
		IUIT_AUTHED,
		IUIT_LOGINING,
		IUIT_LOGINED,
	};
	InnerUserInfoType status = IUIT_UNAUTH;
};


inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SessionInfo & info)
{
	stm << "user=" << info.user << ", passwd=" << info.passwd
		<< ", uid=" << info.uid << ", sID=" << info.sID
		<< ", loginTime=" << info.loginTime
		<< ",lastLoginTime=" << info.lastActiveTime << ", lastActiveTime=" << info.lastActiveTime
		<< ", lastDelayTick=" << info.lastDelayTick;
	return stm;
}



















#endif
