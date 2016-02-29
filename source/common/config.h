

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
*  all server configure for start and configure defined from this.
*/


#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include <defined.h>
#include <single.h>




class ServerConfig : public Singleton<ServerConfig>
{
public:
    bool parse(std::string filename, ServerType ownType,ServerNode ownNode);
public:
    const ListenConfig& getConfigListen(ServerType node, ServerNode index = InvalidServerNode);
    std::vector<ConnectConfig > getConfigConnect(ServerType node);
    const DBConfig & getDBConfig(DBConfigID id);

    inline ServerType getOwnServerType(){ return _ownServerType; }
    inline ServerNode getOwnServerNode(){ return _ownServerNode; }
    inline AreaID getAreaID() { return _areaid; }



private:
    ServerType _ownServerType = InvalidServerType;
    ServerNode _ownServerNode = InvalidServerNode;
    AreaID _areaid = 0;

    std::vector<ListenConfig> _configListen;
    std::vector<ConnectConfig> _configConnect;
    std::vector<DBConfig> _configDB;
};






























#endif