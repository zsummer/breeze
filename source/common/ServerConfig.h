

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

#include <InnerDefined.h>
#include <BaseMessageHandler.h>
#include <Single.h>
#include <tinyxml2.h>



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


inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const DBConfig & config)
{
	os << "[ip=" << config.ip << ", port=" << config.port << ", db=" << config.db << ", user=" << config.user << ", pwd=" << config.pwd << "]";
	return os;
}



class ServerConfig : public Singleton<ServerConfig>
{
public:
	bool parse(std::string filename, ServerNode ownNode,NodeIndex ownIndex);
public:
	const ListenConfig getConfigListen(ServerNode node, NodeIndex index = InvalidNodeIndex);
	std::vector<ConnectorConfig > getConfigConnect(ServerNode node);

	ServerNode getOwnServerNode(){ return _ownServerNode; }
	NodeIndex getOwnNodeIndex(){ return _ownNodeIndex; }
	PlatID getPlatID() { return _platid; }
	AreaID getAreaID() { return _areaid; }

	inline const DBConfig & getAuthDBConfig(){ return _authDBConfig; }
	inline const DBConfig & getInfoDBConfig(){ return _infoDBConfig; }
	inline const DBConfig & getLogDBConfig(){ return _logDBConfig; }

private:
	ServerNode _ownServerNode = InvalideServerNode;
	NodeIndex _ownNodeIndex = InvalidNodeIndex;
	PlatID _platid = 0;
	AreaID _areaid = 0;

	std::vector<ListenConfig> _configListen;
	std::vector<ConnectorConfig> _configConnect;

	DBConfig _authDBConfig;
	DBConfig _infoDBConfig;
	DBConfig _logDBConfig;
};






























#endif