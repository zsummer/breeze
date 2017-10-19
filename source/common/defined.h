

/*
* breeze License
* Copyright (C) 2014-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
#include "luaextra/summer.h"
#include "luaextra/performance.h"

using namespace zsummer::log4z;
using namespace zsummer::network;
using namespace zsummer::proto4z;
using namespace std::placeholders;
using namespace zsummer::mysql;

//字典ID
using DictID = unsigned long long;
const DictID InvalidDictID = 0;

//分区ID  跨服交互时需要该ID表名分区ID, 该ID因为要merge到ServiceID的头部, 表达范围不能超过20bit(100万以下)
typedef ui64 AreaID;
const AreaID InvalidAreaID = 0;

//DockerID(集装箱ID) 集装箱可视为一个进程, 所有Service(服务)都装载于Docker中   
typedef ui64 DockerID;
const DockerID InvalidDockerID = 0;

//服务ID  服务==>可满足某种业务需求的,可独立部署到分布式节点中的服务, 例如游戏角色,公会,  以及对应的管理器服务等
//表达范围<=52bit, 其中areaid占用20bit, 自增部分占用32bit
typedef ui64 ServiceID;
const ServiceID InvalidServiceID = (ServiceID)0;
typedef ServiceID AvatarID;
const AvatarID InvalidAvatarID = InvalidServiceID;

//服务名字 
typedef std::string ServiceName;
const ServiceName InvalidServiceName = "";

//组队ID
typedef ui64 GroupID;
const GroupID InvalidGroupID = 0;

//场景服务器的分线ID  标识具体的场景服务器  
typedef ui64 LineID;
const LineID InvalidLineID = 0;

//场景ID  标识具体的场景实例 例如主城 副本 竞技场等  
typedef ui64 SceneID;
const SceneID InvalidSceneID = 0;

typedef ui64 MapID;
const MapID InvalidMapID = 0;

//战报ID
typedef ui64 ReportID;
const ReportID InvalidReportID = 0;

//实体ID 标识场景中的实体对象 例如怪物 玩家 飞行道具  
typedef ui64 EntityID;
const EntityID InvalidEntityID = 0;


//服务器心跳超时检测间隔 
const double ServerPulseInterval = 10.0;
//客户端心跳超时检测间隔 
const double ClientPulseInterval = 30.0;
//web服务器响应超时时间 
const double WebPulseTimeout = 10.0;
//SCENE服务帧DELAY
const double SceneFrameInterval = 0.1;

//服务类型和依赖关系

typedef ui16 ServiceType;
const ServiceType InvalidServiceType = (ServiceType)0;
const ServiceType STInfoDBMgr = (ServiceType)1;
const ServiceType STLogDBMgr = (ServiceType)2;
const ServiceType STAvatarMgr = (ServiceType)3;
const ServiceType STWebAgent = (ServiceType)4;
const ServiceType STOfflineMgr = (ServiceType)5;
const ServiceType STMinitorMgr = (ServiceType)6;
const ServiceType STWorldMgr = (ServiceType)7;


const ServiceType STAvatar = (ServiceType)11;
const ServiceType STClient = (ServiceType)20;


enum ServiceTrait
{
    //非法服务 
    Strait_None,   


    //多例模式的Service . 
    //docker启动时 不会自动装载该类型Service, 所以需要对应的单例来触发装载和卸载 ,例如用户Service需要用户管理Service, 公会Service需要公会管理Service, 
    //      如果服务器不介意该类型的Service所占用的服务器资源, 也可以在管理器装载时候一次性手动装载全部 
    //docker关闭时, 会自动调用所有该类型的服务的卸载, 并且这个卸载调用是不检查依赖的.  
    //因此 设计原则上 这些服务不允许被任何其他服务依赖, 并且需要对应的单例服务来手动管理. 
    //对于'依赖'该服务的模块, 以模块的形式使用, 即ServiceMgr管理Service, Service管理Module. 
    STrait_Multi, 


    //单例模式的Service .
    //docker启动时 会根据依赖关系进行逐一装载 
    //docker关闭时 会根据被依赖关系逐一卸载 
    //单例模式的ServiceID使用装载该服务的dockerID, 默认在查找/使用时不传该参数或者传InvalidServiceID即可正确获得本组服务器的该服务. 
    STrait_Single,


    //异构系统的Service. 该状态服务不装载, 本地永远是一个shell .Heterogenous
    //docker启动时 如果有该service的配置,则进行网络连接操作, 并按照依赖关系装载本地单例. 
    //          如果没有该配置,则不进行网络连接操作,并设置该服务状态为未装载状态.  
    //docker关闭时 会忽略该服务的存在. 
    STrait_Heterogenous,
};

//std::tuple<isSingleton, serviceKey, serviceDepends>
struct  ServiceDependInfo
{
    ServiceDependInfo(ServiceTrait trait, const char *const name, const std::set<ServiceType>& dps)
        :serviceTrait(trait),
        serviceName(name),
        depends(dps) {}
    ServiceDependInfo(ServiceTrait trait, const char *const name)
        :serviceTrait(trait),
        serviceName(name) { }
    ServiceTrait serviceTrait;
    ServiceName serviceName;
    std::set<ServiceType > depends;
};

//{服务类型, {ServiceTrait, 对应的字符串名称, {依赖的service列表(装载和卸载会根据这个依赖关系组织顺序)} }
const std::map<ServiceType, ServiceDependInfo> ServiceDepends =
{
    { STInfoDBMgr, { STrait_Single, "STInfoDBMgr" } },
    { STLogDBMgr,  { STrait_Single, "STLogDBMgr" } },

    { STWebAgent,{ STrait_Single, "STWebAgent",{ STInfoDBMgr , STLogDBMgr } } },
    { STOfflineMgr,{ STrait_Single, "STOfflineMgr",{ STInfoDBMgr , STLogDBMgr } } },
    { STMinitorMgr,{ STrait_Single, "STMinitorMgr",{ STInfoDBMgr , STLogDBMgr } } },

    { STAvatarMgr,{ STrait_Single, "STAvatarMgr",{ STInfoDBMgr , STLogDBMgr,STWebAgent, STOfflineMgr,STMinitorMgr } } },

    { STWorldMgr,{ STrait_Heterogenous, "STWorldMgr"} },

    { STAvatar,{ STrait_Multi, "STAvatar",{ STAvatarMgr } } },
    { STClient,{ STrait_Multi, "STClient" } },
};

inline ServiceTrait getServiceTrait(ServiceType serviceType);
inline ServiceType getServiceTypeByKey(const ServiceName & serviceName);
inline const ServiceName& getServiceName(ServiceType serviceType);

inline std::set<ServiceType> getServiceSubsidiary(ServiceType serviceType);










struct DockerConfig
{
    std::string _dockerListenHost;
    std::string _dockerPubHost;
    unsigned short _dockerListenPort = 0;
    std::string _clientPubHost;
    unsigned short _clientPubPort = 0;
    std::string _webPubHost;
    unsigned short _webPubPort = 0;
    std::vector<std::string> _dockerWhite;
    std::vector<ServiceType> _services;
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



struct WorldConfig 
{
    DockerID _dockerID = InvalidDockerID;
    std::string _dockerListenHost;
    unsigned short _dockerListenPort = 0;
    std::string _sceneListenHost;
    std::string _scenePubHost;
    unsigned short _sceneListenPort = 0;
};

struct LineConfig
{
    std::string _clientListenHost;
    std::string _clientPubHost;
    unsigned short _clientListenPort = 0;
    LineID _lineID = InvalidLineID;
};

using ProtoID = zsummer::proto4z::ProtoInteger;
const ProtoID InvalidProtoID = -1;

enum ServiceStatus
{
    SS_NONE,
    SS_CREATED,
    SS_INITING,
    SS_WORKING,
    SS_UNLOADING,
    SS_DESTROY,
};




const int MAX_ACCOUNT_AVATARS = 5;



enum SessionStatus : ui16
{
    SSTATUS_UNKNOW = 0,
    SSTATUS_TRUST, //受信任的服务器内部session, docker 互通session  
    SSTATUS_AUTHING, //user
    SSTATUS_AUTHED,
    SSTATUS_ATTACHED,
};

enum ClientSessionData
{
    UPARAM_SESSION_STATUS, //通用 
    UPARAM_LAST_ACTIVE_TIME, //通用 

    UPARAM_REMOTE_DOCKERID, //docker集群 
    UPARAM_ACCOUNT,
    UPARAM_AVATAR_ID,
    UPARAM_LOGIN_TIME,

    UPARAM_AREA_ID, //world集群用
    UPARAM_DOCKER_ID,
    UPARAM_SCENE_ID,

};


inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os,  SessionStatus ss)
{
    switch (ss)
    {
    case SSTATUS_TRUST:
        os << "SSTATUS_TRUST";
        break;
    case SSTATUS_AUTHING:
        os << "SSTATUS_AUTHING";
        break;
    case SSTATUS_AUTHED:
        os << "SSTATUS_AUTHED";
        break;
    case SSTATUS_ATTACHED:
        os << "SSTATUS_ATTACHED";
        break;
    default:
        os << "SSTATUS_UNKNOW";
        break;
    }
    return os;
}

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const DockerConfig & config)
{
    os << "[_dockerListenHost=" << config._dockerListenHost << ", _dockerPubHost=" << config._dockerPubHost
        << ", _dockerListenPort=" << config._dockerListenPort << ", _clientPubHost=" << config._clientPubHost
        << ", _clientPubPort=" << config._clientPubPort << ", _dockerWhite=" << config._dockerWhite
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

inline ServiceTrait getServiceTrait(ServiceType serviceType)
{
    auto founder = ServiceDepends.find(serviceType);
    if (founder == ServiceDepends.end())
    {
        return Strait_None;
    }
    return founder->second.serviceTrait;
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
    return ret;
}

#endif
