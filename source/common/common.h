

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
*  common header file.
*
*/

#ifndef _COMMON_H_
#define _COMMON_H_

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
int luaopen_proto4z_util(lua_State *L);
int luaopen_cjson(lua_State *l);
}
#include "lua/summer.h"

#include "defined.h"
#include "utls.h"
#include "single.h"
#include "genID.h"
#include <proto4z/dbHelper.h>
#include "md5/md5.h"
#include "dbAsync.h"
#include "config.h"
#include "dispatch.h"
#include "balance.h"


using namespace zsummer::mysql;




//! 逻辑类型


enum SessionStatus
{
    SSTATUS_UNKNOW = 0,
    SSTATUS_PLAT_LOGINING,
    SSTATUS_PLAT_LOGINED,
    SSTATUS_PLAT_LOADING,
    SSTATUS_PLAT_CREATING,
    SSTATUS_PLAT_SELECTING,
    SSTATUS_LOGINED,
    SSTATUS_TRUST, //受信任的服务器内部session 
};

enum SessionUserData
{
    UPARAM_SESSION_STATUS,
    UPARAM_ACCOUNT,
    UPARAM_USER_ID,
    UPARAM_LOGIN_TIME,
    UPARAM_LAST_ACTIVE_TIME,
};

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


template <class MSG>
void sendMessage(TcpSessionPtr & session, MSG & msg)
{
    WriteStream ws(MSG::GetProtoID());
    ws << msg;
    session->send(ws.getStream(), ws.getStreamLen());
}

template <class MSG>
void sendMessage(SessionID & sID, MSG & msg)
{
    WriteStream ws(MSG::GetProtoID());
    ws << msg;
    SessionManager::getRef().sendSessionData(sID, ws.getStream(), ws.getStreamLen());
}

inline void DispatchFunction(TcpSessionPtr   session, const char * begin, unsigned int len)
{
    ReadStream rs(begin, len);
    if (rs.getProtoID() < 200 
        || (rs.getProtoID() < 50000 && std::get<TupleParamNumber>(session->getUserParam(UPARAM_SESSION_STATUS)) == SSTATUS_LOGINED)
        || std::get<TupleParamNumber>(session->getUserParam(UPARAM_SESSION_STATUS)) == SSTATUS_TRUST)
    {
        MessageDispatcher::getRef().dispatch(session, rs.getProtoID(), rs);
    }
}

#endif
