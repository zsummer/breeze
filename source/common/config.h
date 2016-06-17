

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
    bool parse(std::string filename, DockerID idx);
public:
    inline const std::vector<DockerConfig> & getDockerConfig() { return _configDocker; }
    inline const std::map<ui16, std::vector<DockerID> > & getServiceTypeConfig() { return _configServiceType; }
    inline const std::vector<DBConfig> & getDBConfig(){ return _configDB; }
    inline DockerID getDockerID(){ return _dockerIdx; }
    inline AreaID getAreaID() { return _areaid; }
    inline ui64   getMinServiceID() { return _areaid * (ui64)pow(10, 8); }
private:
    DockerID _dockerIdx = InvalidDockerID;
    AreaID _areaid = 0;
    std::vector<DockerConfig> _configDocker;
    std::vector<DBConfig> _configDB;
    std::map<ServiceType, std::vector<DockerID> > _configServiceType;

};






























#endif