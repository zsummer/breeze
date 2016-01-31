

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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#endif

#ifdef WIN32
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
#include <utility>
#include <algorithm>

#include <functional>
#include <memory>

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <log4z/log4z.h>
#include <proto4z/proto4z.h>
#include <zsummerX/zsummerX.h>
#include <ProtoCommon.h>
#include <dispatch.h>

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



//服务节点类型
typedef ui16 ServerType;
const ServerType InvalidServerType = (ServerType)0;

//节点索引ID
typedef ui16 ServerNode;
const ServerNode InvalidServerNode = (ServerNode)0;

//服务节点
const ServerType LogicServer = 1;
const ServerType StressClient = 2;



struct Route
{
    ServerType _fromType = InvalidServerType;
    ServerNode _fromNode = InvalidServerNode;
    ServerType _toType = InvalidServerType;
    ServerNode _toNode = InvalidServerNode;
    SessionID _fromSessionID = InvalidSessionID;
    SessionID _toSessionID = InvalidSessionID;
};

inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Route & data)
{
    ws << data._fromType;
    ws << data._fromNode;
    ws << data._fromSessionID;
    ws << data._toType;
    ws << data._toNode;
    ws << data._toSessionID;
    return ws;
}
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Route & data)
{
    rs >> data._fromType;
    rs >> data._fromNode;
    rs >> data._fromSessionID;
    rs >> data._toType;
    rs >> data._toNode;
    rs >> data._toSessionID;
    return rs;
}


//DB类型
typedef ui8 DBConfigID;
const DBConfigID InfoDB = 1;
const DBConfigID LogDB = 2;
const DBConfigID InvalidDB = (DBConfigID)0;


//分区分服的ID
typedef ui16 PlatID;
typedef ui16 AreaID;



struct ListenConfig
{
    std::string _ip;
    unsigned short _port = 0;
    std::vector<std::string> _whiteList;
    std::string _wip;
    unsigned short _wport = 0;
    ServerType _node = InvalidServerType;
    ServerNode _index = InvalidServerNode;
};

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ListenConfig & config)
{
    os << "[_ip=" << config._ip << ", _port=" << config._port << ", _node=" << config._node << ", _index=" << config._index << "]";
    return os;
}

struct ConnectConfig
{
    ServerType _srcType = InvalidServerType;
    ServerType _dstType = InvalidServerType;
    ServerNode  _dstServerNode = InvalidServerNode;
    std::string _remoteIP;
    unsigned short _remotePort = 0;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ConnectConfig & config)
{
    os << "[_srcType=" << config._srcType << ", _dstType=" << config._dstType << ", _remoteIP=" << config._remoteIP << ", _remotePort=" << config._remotePort << "]";
    return os;
}

struct DBConfig
{
    DBConfigID _id = InvalidDB;
    std::string _ip;
    unsigned short _port = 3306;
    std::string _db;
    std::string _user;
    std::string _pwd;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const DBConfig & config)
{
    os << "[id=" << (int)config._id << ", ip=" << config._ip << ", port=" << config._port << ", db=" << config._db << ", user=" << config._user << ", pwd=" << config._pwd << "]";
    return os;
}















#endif
