

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
typedef ui32 DockerID;
const DockerID InvalidDockerID = 0;

typedef ui64 ServiceID;
const ui64 InvalidServiceID = (ServiceID)0;


enum ServiceType : ui16
{
    ServiceInvalid = 0,//有效的服务ID从这里开始到ServiceMax结束, 必须连续,  前后依赖 
    ServiceDictDBMgr,
    ServiceInfoDBMgr,
    ServiceLogDBMgr,
    ServiceUserMgr,

    ServiceMulti,

    ServiceUser,
    ServiceClient, 
    
    //...
    ServiceMax,
};
const std::vector<std::string> ServiceNames =
{
    "ServiceInvalid",
    "ServiceDictDBMgr",
    "ServiceInfoDBMgr",
    "ServiceLogDBMgr",
    "ServiceUserMgr",

    "ServiceMulti",

    "ServiceUser",
    "ServiceClient",
    
    
    //...
    "ServiceMax",
};

struct Tracing
{
    ui16 _toServiceType;
    ServiceID _toServiceID = InvalidServiceID;
    ui16 _fromServiceType;
    ServiceID _fromServiceID = InvalidServiceID;
    ui32 _traceID = 0; //本地cbID  
    ui32 _traceBackID = 0; //把远程cbID透传回去  
};








struct DockerConfig
{
    std::string _serviceBindIP;
    std::string _serviceIP;
    unsigned short _servicePort = 0;
    std::string _wideIP;
    unsigned short _widePort = 0;
    std::vector<std::string> _whiteList;
    std::vector<ui16> _services;
    DockerID _dockerID = InvalidDockerID;
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



const int MAX_ACCOUNT_USERS = 5;

enum SessionStatus
{
    SSTATUS_UNKNOW = 0,
    SSTATUS_TRUST, //受信任的服务器内部session 
    SSTATUS_AUTHING,
    SSTATUS_AUTHED,
    SSTATUS_LOGINED,
};

enum SessionUserData
{
    UPARAM_SESSION_STATUS,
    UPARAM_LAST_ACTIVE_TIME,
    UPARAM_REMOTE_DOCKERID,
    UPARAM_ACCOUNT,
    UPARAM_SERVICE_ID,
    UPARAM_LOGIN_TIME,
};




inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const Tracing & trace)
{
    if (trace._fromServiceType < ServiceMax && trace._toServiceType < ServiceMax)
    {
        os << "[_toServiceType=" << ServiceNames.at(trace._toServiceType) << ", _toServiceID=" << trace._toServiceID
            << ", _fromServiceType=" << ServiceNames.at(trace._fromServiceType) << ", _fromServiceID=" << trace._fromServiceID
            << ", _traceID=" << trace._traceID << ", _traceBackID=" << trace._traceBackID
            << "]";
    }
    else
    {
        os << "[_toServiceType=" << trace._toServiceType << ", _toServiceID=" << trace._toServiceID
            << ", _fromServiceType=" << trace._fromServiceType << ", _fromServiceID=" << trace._fromServiceID
            << ", _traceID=" << trace._traceID << ", _traceBackID=" << trace._traceBackID
            << "]";
    }
    return os;
}

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const DockerConfig & config)
{
    os << "[_serviceBindIP=" << config._serviceBindIP << ", _serviceIP=" << config._serviceIP
        << ", _servicePort=" << config._servicePort << ", _wideIP=" << config._wideIP
        << ", _widePort=" << config._widePort << ", _whiteList=" << config._whiteList
        << ", _services=" << config._services << ", _dockerID=" << config._dockerID
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
    ws << data._toServiceType;
    ws << data._toServiceID;
    ws << data._fromServiceType;
    ws << data._fromServiceID;
    ws << data._traceID;
    ws << data._traceBackID;
    return ws;
}
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Tracing & data)
{
    rs >> data._toServiceType;
    rs >> data._toServiceID;
    rs >> data._fromServiceType;
    rs >> data._fromServiceID;
    rs >> data._traceID;
    rs >> data._traceBackID;
    return rs;
}




#endif
