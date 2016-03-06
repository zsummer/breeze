

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
*  type define
*
*/

#ifndef _INNER_TYPE_DEFINE_H_
#define _INNER_TYPE_DEFINE_H_
#ifdef WIN32
#pragma warning(disable:4996)
#pragma warning(disable:4819)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include<pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif 

#ifdef __APPLE__
#include<mach/mach_time.h>
#include <dispatch/dispatch.h>
#include <libproc.h>
#endif

#include <iomanip>
#include <string.h>
#include <signal.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>

#include <functional>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <random>

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>


//! 基本类型
typedef char i8;
typedef unsigned char ui8;
typedef short i16;
typedef unsigned short ui16;
typedef int i32;
typedef unsigned int ui32;
typedef long long i64;
typedef unsigned long long ui64;


#include <log4z/log4z.h>
#include <proto4z/proto4z.h>
#include <proto4z/dbHelper.h>
#include <multimod_matching_tree/match_tree.h>
#include <rc4/rc4_encryption.h>
#include <zsummerX/zsummerX.h>



extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
    int luaopen_proto4z_util(lua_State *L);
    int luaopen_cjson(lua_State *l);
}
#include "lua/summer.h"

using namespace zsummer::log4z;
using namespace zsummer::network;
using namespace zsummer::proto4z;
using namespace std::placeholders;
using namespace zsummer::mysql;

//分区
typedef ui32 AreaID;

//节点索引ID
typedef ui32 ClusterIndex;
const ClusterIndex InvalidClusterIndex = 0;

const std::string EntityClient = "client"; //特殊
const std::string EntityUser = "user"; //特殊, 需要uid
const std::string EntityUserCenter = "userCenter";
const std::vector<std::string> EntityServices = { EntityUserCenter };

struct EntitySession 
{
    ClusterIndex _cluster = InvalidClusterIndex;
    SessionID _sID = InvalidSessionID;
    bool _worked = false;
};


typedef ui64 UserID;
const ui64 InvalidUserID = (UserID)0;

struct Tracing
{
    std::string _toService;
    UserID _toUID = InvalidUserID;
    std::string _fromService;
    UserID _fromUID = InvalidUserID;
};

const std::string InfoDB = "info";
const std::string LogDB = "log";
const std::vector<std::string> DBCluster = { InfoDB, LogDB };


struct ClusterConfig
{
    std::string _serviceBindIP;
    std::string _serviceIP;
    unsigned short _servicePort = 0;
    std::string _wideIP;
    unsigned short _widePort = 0;
    std::vector<std::string> _whiteList;
    std::vector<std::string> _services;
    ClusterIndex _cluster = InvalidClusterIndex;
};



struct DBConfig
{
    std::string _name;
    std::string _ip;
    unsigned short _port = 3306;
    std::string _db;
    std::string _user;
    std::string _pwd;
};





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
    UPARAM_LAST_ACTIVE_TIME,
    UPARAM_ACCOUNT,
    UPARAM_USER_ID,
    UPARAM_LOGIN_TIME,
   
};


template <class MSG>
void sendMessage(zsummer::network::TcpSessionPtr & session, MSG & msg)
{
    zsummer::proto4z::WriteStream ws(MSG::GetProtoID());
    ws << msg;
    session->send(ws.getStream(), ws.getStreamLen());
}

template <class MSG>
void sendMessage(zsummer::network::SessionID & sID, MSG & msg)
{
    zsummer::proto4z::WriteStream ws(MSG::GetProtoID());
    ws << msg;
    zsummer::network::SessionManager::getRef().sendSessionData(sID, ws.getStream(), ws.getStreamLen());
}



inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ClusterConfig & config)
{
    os << "[_serviceBindIP=" << config._serviceBindIP << ", _serviceIP=" << config._serviceIP
        << ", _servicePort=" << config._servicePort << ", _wideIP=" << config._wideIP
        << ", _widePort=" << config._widePort << ", _whiteList=" << config._whiteList
        << ", _services=" << config._services << ", _cluster=" << config._cluster
        << "]";
    return os;
}


inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const DBConfig & config)
{
    os << "[_name=" << config._name << ", ip=" << config._ip << ", port=" << config._port
        << ", db=" << config._db << ", user=" << config._user << ", pwd=" << config._pwd << "]";
    return os;
}


inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Tracing & data)
{
    ws << data._toService;
    ws << data._toUID;
    ws << data._fromService;
    ws << data._fromUID;
    return ws;
}
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Tracing & data)
{
    rs >> data._toService;
    rs >> data._toUID;
    rs >> data._fromService;
    rs >> data._fromUID;
    return rs;
}




#endif
