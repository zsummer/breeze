

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
#include "lua/lpack.h"
    int luaopen_protoz_bit(lua_State *L);
    int luaopen_cjson(lua_State *l);
}
#include "lua/summer.h"

#include "defined.h"
#include "single.h"
#include "genID.h"
#include "dbhelper/dbHelper.h"
#include "md5/md5.h"
#include "dbAsync.h"
#include "config.h"


using namespace zsummer::mysql;







template<class T>
std::string toString(const T &t)
{
    std::stringstream os;
    os << t;
    return os.str();
}

inline unsigned  int getNowTick()
{
    return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

template <class MSG>
void sendMessage(TcpSessionPtr & session, MSG & msg)
{
    WriteStream ws(MSG::GetProtoID());
    ws << msg;
    session->doSend(ws.getStream(), ws.getStreamLen());
}

template <class MSG>
void sendMessage(SessionID & sID, MSG & msg)
{
    WriteStream ws(MSG::GetProtoID());
    ws << msg;
    SessionManager::getRef().sendSessionData(sID, ws.getStream(), ws.getStreamLen());
}

#endif
