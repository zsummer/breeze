

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

//每个service拥有两个唯一的基础属性ServiceID, ServiceName
typedef ui64 ServiceID;
const ServiceID InvalidServiceID = (ServiceID)0;

typedef std::string ServiceName;
const ServiceName InvalidServiceName = "";

typedef ui16 ServiceType;
const ServiceType InvalidServiceType = (ServiceType)0;
const ServiceType STInfoDBMgr = (ServiceType)1;
const ServiceType STLogDBMgr = (ServiceType)2;
const ServiceType STUserMgr = (ServiceType)3;
const ServiceType STWebAgent = (ServiceType)4;
const ServiceType STOfflineMgr = (ServiceType)5;
const ServiceType STMinitorMgr = (ServiceType)6;

const ServiceType STUser = (ServiceType)11;
const ServiceType STClient = (ServiceType)20;

//std::tuple<isSingleton, serviceKey, serviceDepends>
struct  ServiceDependInfo
{
    ServiceDependInfo(bool single, const char *const name, const std::set<ServiceType>& dps)
        :isSingleton(single),
        serviceName(name),
        depends(dps)
    {
    }
    ServiceDependInfo(bool single, const char *const name)
        :isSingleton(single),
        serviceName(name)
    {
    }
    bool isSingleton;
    ServiceName serviceName;
    std::set<ServiceType > depends;
};



const std::map<ServiceType, ServiceDependInfo> ServiceDepends =
{
    { STInfoDBMgr, { true, "STInfoDBMgr" } },
    { STLogDBMgr,  { true, "STLogDBMgr" } },
    { STUserMgr, { true, "STUserMgr", { STInfoDBMgr , STLogDBMgr } } },
    { STWebAgent, { true, "STWebAgent",{ STInfoDBMgr , STLogDBMgr } } },
    { STOfflineMgr,{ true, "STOfflineMgr",{ STInfoDBMgr , STLogDBMgr } } },
    { STMinitorMgr,{ true, "STMinitorMgr",{ STInfoDBMgr , STLogDBMgr } } },
    { STUser,{ false, "STUser",{ STUserMgr } } },
    { STClient,{ false, "STClient" } }
};

inline bool isSingletonService(ServiceType serviceType);
inline ServiceType getServiceTypeByKey(const ServiceName & serviceName);
inline const ServiceName& getServiceName(ServiceType serviceType);

inline std::set<ServiceType> getServiceSubsidiary(ServiceType serviceType);










struct DockerConfig
{
    std::string _serviceBindIP;
    std::string _serviceIP;
    unsigned short _servicePort = 0;
    std::string _wideIP;
    unsigned short _widePort = 0;
    std::string _webIP;
    unsigned short _webPort = 0;
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

enum SessionStatus : ui16
{
    SSTATUS_UNKNOW = 0,
    SSTATUS_TRUST, //受信任的服务器内部session, docker 互通session  
    SSTATUS_AUTHING,
    SSTATUS_AUTHED,
    SSTATUS_ATTACHED,
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

inline bool isSingletonService(ServiceType serviceType)
{
    auto founder = ServiceDepends.find(serviceType);
    if (founder == ServiceDepends.end())
    {
        return false;
    }
    return founder->second.isSingleton;
}
inline const ServiceName& getServiceName(ServiceType serviceType)
{
    auto founder = ServiceDepends.find(serviceType);
    if (founder == ServiceDepends.end())
    {
        return InvalidServiceName;
    }
    return founder->second.serviceName;
}
inline const std::set<ServiceType>& getServiceDepends(ServiceType serviceType)
{
    auto founder = ServiceDepends.find(serviceType);
    if (founder == ServiceDepends.end())
    {
        static std::set<ServiceType> _noDepends;
        return _noDepends;
    }
    return founder->second.depends;
}

inline ServiceType getServiceTypeByKey(const ServiceName & serviceName)
{
    if (serviceName.empty())
    {
        return InvalidServiceType;
    }
    for (const auto & sd : ServiceDepends)
    {
        if (sd.second.serviceName == serviceName)
        {
            return sd.first;
        }
    }
    return InvalidServiceType;
}





inline std::set<ServiceType> getServiceSubsidiary(ServiceType serviceType)
{
    std::set<ServiceType> ret;
    for (const auto & sd : ServiceDepends)
    {
        for (const auto & st : sd.second.depends)
        {
            if (st == serviceType)
            {
                ret.insert(sd.first);
            }
        }
    }
    return std::move(ret);
}

#endif
