

/*
* mini-breeze License
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
*  文件说明
*  所有服务通用的定义可以放在这里
*
*/

#ifndef _DEFINE_PROTO_H_
#define _DEFINE_PROTO_H_
#ifdef WIN32
#pragma warning(disable:4996)
#pragma warning(disable:4819)
#endif

#include <string>
#include <algorithm>
#include <zsummerX/frameX.h>
#include <ProtoCommon.h>


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
typedef ui64 AccountID;
const ui64 InvalidAccountID = (AccountID) -1;
typedef ui64 CharacterID;
const ui64 InvalidCharacterID = (CharacterID)-1;
typedef ui64 ItemID;
const ui64 InvalidItemID = (ItemID)-1;
typedef ui32 NodeIndex;
const NodeIndex InvalidNodeIndex = (NodeIndex)-1;

//服务节点类型
typedef ui32 ServerNode;
const ServerNode InvalideServerNode = (ServerNode)-1;
const ServerNode MiniBreezeNode = 0;
const ServerNode StressNode = 1;

//服务节点编号
typedef ui32 NodeIndex;
const NodeIndex InvalideNodeIndex = (NodeIndex)-1;

typedef ui16 PlatID;
typedef ui16 AreaID;




//非认证情况下客户端通讯协议[)
const ui16 MIN_OUT_UNAUTH_PROTO_ID = 0;
const ui16 MAX_OUT_UNAUTH_PROTO_ID = 100;

//认证后的通讯协议区间为[)
const ui16 MIN_OUT_PROTO_ID = 100;
const ui16 MAX_OUT_PROTO_ID = 30000;

//客户端的请求协议可以根据以下函数判断
inline bool isNeedAuthClientPROTO(ui16 protoID) { return protoID >= MIN_OUT_PROTO_ID && protoID < MAX_OUT_PROTO_ID; }




//session info
struct SessionInfo 
{
	//client
	AccountID accID = InvalidAccountID;
	CharacterID charID = InvalidCharacterID;
	SessionID sID = InvalidSeesionID;
	//login time
	ui64 loginTime = time(NULL);
	time_t lastLoginTime = time(NULL);
	time_t lastActiveTime = time(NULL);
};


struct InnerCharInfo
{
	SessionInfo sesionInfo;
	AccountInfo accInfo;
	CharacterInfo charInfo;
	enum InnerCharInfoType
	{
		ICIT_UNAUTH = 0,
		ICIT_AUTHING,
		ICIT_AUTHED,
		ICIT_LOGINING,
		ICIT_LOGINED,
	};
	InnerCharInfoType status = ICIT_UNAUTH;
};


inline zsummer::log4z::CStringStream & operator << (zsummer::log4z::CStringStream & stm, const SessionInfo & info)
{
	stm << "accID=" << info.accID << ", charID=" << info.charID
		<< ", sID=" << info.sID
		<< ", loginTime=" << info.loginTime
		<< ",lastLoginTime=" << info.lastActiveTime << ", lastActiveTime=" << info.lastActiveTime;
	return stm;
}

class GenObjectID
{
public:
	GenObjectID(){}
	inline void InitConfig(PlatID pID, AreaID aID)
	{
		m_platID = pID;
		m_areaID = aID;
		m_minObjID = (((ui64)m_platID << 16) | (ui64)m_areaID) << 32;
		m_maxObjID = m_minObjID | (ui64)((ui32)-1);
		m_seqObjID = m_minObjID;
	}
	inline ui64 GetMinObjID(){ return m_minObjID; }
	inline ui64 GetMaxObjID(){ return m_maxObjID; }
	inline ui64 GetCurObjID(){ return m_seqObjID; }

	inline ui64 GenNewObjID(){ return ++m_seqObjID; }
	inline void SetCurObjID(ui64 seq){ m_seqObjID = seq; }
protected:
private:
	PlatID m_platID = 0;
	AreaID m_areaID = 0;
	ui64 m_minObjID = 0;
	ui64 m_maxObjID = 0;
	ui64 m_seqObjID = 0;
};
















#endif
