

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
*  文件说明
*  所有服务节点务必在这里写节点的启动配置信息.
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



//数据库
const std::string AuthMongoDB = "auth";
const std::string InfoMongoDB = "info";
const std::string LogMongoDB = "log";

struct MongoConfig 
{
	std::string ip;
	unsigned short port = 28017;
	std::string db;
	bool needAuth = true;
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

	inline const MongoConfig & getAuthMongoDB(){ return m_authMongo; }
	inline const MongoConfig & getInfoMongoDB(){ return m_infoMongo; }
	inline const MongoConfig & getLogMongoDB(){ return m_logMongo; }

private:
	ServerNode m_ownServerNode = InvalideServerNode;
	NodeIndex m_ownNodeIndex = InvalidNodeIndex;
	PlatID m_platid = 0;
	AreaID m_areaid = 0;

	std::vector<ListenConfig> m_configListen;
	std::vector<ConnectorConfig> m_configConnect;

	MongoConfig m_authMongo;
	MongoConfig m_infoMongo;
	MongoConfig m_logMongo;
};






























#endif