

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
*  all server configure for start and configure defined from this.
*/


#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_


#include "defined.h"
#include "single.h"


class ServerConfig : public Singleton<ServerConfig>
{
    //所有数据库配置 
public:
    bool parseDB(std::string configName);
    inline const std::vector<DBConfig> & getDBConfig() { return _configDB; }
private:
    std::vector<DBConfig> _configDB;

    //service服务器配置  
public:
    bool parseDocker(std::string configName, DockerID dockerID);
public:
    //服务器配置 
    inline const std::vector<DockerConfig> & getDockerConfigs() { return _configs; }
    //记录每个类型的service可以被装载的docker id
    inline const std::map<ui16, std::vector<DockerID> > & getServiceLoadDockers() { return _serviceLoadDockers; }
    //当前docker进程的docker id
    inline DockerID getDockerID(){ return _dockerID; }
    //本组服务器的区ID ,用于实例ID的分段, 用于分区和方便合服 
    inline AreaID getAreaID() { return _areaID; }
    //通过area id计算出的初始化实例id. 使用时候 要先自增. 
    inline ui64   getMinServiceID() { return _areaID * (ui64)pow(10, 8); }
private:
    DockerID _dockerID = InvalidDockerID;
    AreaID _areaID = 0;
    std::vector<DockerConfig> _configs;
    std::map<ServiceType, std::vector<DockerID> > _serviceLoadDockers;

    //异构的世界同步服务器 配置
public:
    bool parseWorld(std::string configName);
    inline const WorldConfig & getWorldConfig() { return _worldConfig; }
private:
    WorldConfig _worldConfig;

    //异构的世界同步服务器的scene配置
public:
    bool parseScenes(std::string configName, ui32 serverID);
    inline const LineConfig & getSceneConfig() { return _scene; }
private:
    LineConfig _scene;
};






























#endif