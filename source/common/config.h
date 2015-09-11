

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
    bool parse(std::string filename, ServerNode ownNode,NodeIndex ownIndex);
public:
    const ListenConfig& getConfigListen(ServerNode node, NodeIndex index = InvalidNodeIndex);
    std::vector<ConnectConfig > getConfigConnect(ServerNode node);
    const DBConfig & getDBConfig(DBConfigID id);

    inline ServerNode getOwnServerNode(){ return _ownServerNode; }
    inline NodeIndex getOwnNodeIndex(){ return _ownNodeIndex; }
    inline PlatID getPlatID() { return _platid; }
    inline AreaID getAreaID() { return _areaid; }



private:
    ServerNode _ownServerNode = InvalidServerNode;
    NodeIndex _ownNodeIndex = InvalidNodeIndex;
    PlatID _platid = 0;
    AreaID _areaid = 0;

    std::vector<ListenConfig> _configListen;
    std::vector<ConnectConfig> _configConnect;
    std::vector<DBConfig> _configDB;
};






























#endif