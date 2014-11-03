

/*
* mini-breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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

#include <ProtoDefine.h>




struct ListenConfig 
{
	std::string ip;
	unsigned short port = 0;
	ServerNode node = InvalideServerNode;
	NodeIndex index = InvalideNodeIndex;
};

struct ConnectorConfig 
{
	ServerNode srcNode = InvalideServerNode;
	ServerNode dstNode = InvalideServerNode;
	std::string remoteIP;
	unsigned short remotePort = 0;
};



//db name list.  db name same as db config name.
const std::string AuthDBName = "auth";
const std::string InfoDBName = "info";
const std::string LogDBName = "log";

struct DBConfig 
{
	std::string ip;
	unsigned short port = 3306;
	std::string db;
	std::string user;
	std::string pwd;
};


class ServerConfig
{
public:
	bool Parse(std::string filename, ServerNode ownNode,NodeIndex ownIndex);
public:
	const ListenConfig getConfigListen(ServerNode node, NodeIndex index = InvalidNodeIndex);
	std::vector<ConnectorConfig > getConfigConnect(ServerNode node);

	ServerNode getOwnServerNode(){ return m_ownServerNode; }
	NodeIndex getOwnNodeIndex(){ return m_ownNodeIndex; }
	PlatID getPlatID() { return m_platid; }
	AreaID getAreaID() { return m_areaid; }

	inline const DBConfig & getAuthDBConfig(){ return m_authDBConfig; }
	inline const DBConfig & getInfoDBConfig(){ return m_infoDBConfig; }
	inline const DBConfig & getLogDBConfig(){ return m_logDBConfig; }

private:
	ServerNode m_ownServerNode = InvalideServerNode;
	NodeIndex m_ownNodeIndex = InvalidNodeIndex;
	PlatID m_platid = 0;
	AreaID m_areaid = 0;

	std::vector<ListenConfig> m_configListen;
	std::vector<ConnectorConfig> m_configConnect;

	DBConfig m_authDBConfig;
	DBConfig m_infoDBConfig;
	DBConfig m_logDBConfig;
};






























#endif