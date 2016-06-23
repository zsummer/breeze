

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
*  all server configure for start and configure defined from this.
*/


#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_


#include "defined.h"
#include "single.h"


class ServerConfig : public Singleton<ServerConfig>
{
public:
    bool parse(std::string configName, DockerID dockerID);
public:
    //服务器配置 
    inline const std::vector<DockerConfig> & getConfigs() { return _configs; }
    inline bool isLocalDocker(DockerID dockerID) {
        return std::find_if(_configs.begin(), _configs.end(),
            [dockerID, this](const DockerConfig &dc) {return dc._dockerID == dockerID && dc._areaID == _areaID; }) != _configs.end();}
    //记录每个类型的service可以被装载的docker id, 不包含共享组的docker
    inline const std::map<ui16, std::vector<DockerID> > & getLocalServiceDockers() { return _localServiceDockers; }
    //共享组的single service
    inline const std::map<ui16, std::vector<DockerID> > & getSharedServiceDockers() { return _sharedServiceDockers; }
    //所有数据库配置 
    inline const std::vector<DBConfig> & getDBConfig(){ return _configDB; }
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
    std::vector<DBConfig> _configDB;
    std::map<ServiceType, std::vector<DockerID> > _localServiceDockers;
    std::map<ServiceType, std::vector<DockerID> > _sharedServiceDockers;

};






























#endif