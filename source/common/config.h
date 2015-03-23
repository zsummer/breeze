

/*
* breeze License
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

#include <defined.h>
#include <handler.h>
#include <single.h>
#include <tinyxml2.h>



struct ListenConfig 
{
	std::string _ip;
	unsigned short _port = 0;
	ServerNode _node = InvalidServerNode;
	NodeIndex _index = InvalidNodeIndex;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ::ListenConfig & config)
{
	os << "[_ip=" << config._ip << ", _port=" << config._port << ", _node=" << config._node << ", _index=" << config._index << "]";
	return os;
}

struct ConnectorConfig 
{
	ServerNode _srcNode = InvalidServerNode;
	ServerNode _dstNode = InvalidServerNode;
	std::string _remoteIP;
	unsigned short _remotePort = 0;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ConnectorConfig & config)
{
	os << "[srcNode=" << config._srcNode << ", _dstNode=" << config._dstNode << ", _remoteIP=" << config._remoteIP << ", _remotePort=" << config._remotePort << "]";
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


class ServerConfig : public Singleton<ServerConfig>
{
public:
	bool parse(std::string filename, ServerNode ownNode,NodeIndex ownIndex);
public:
	const ::ListenConfig& getConfigListen(ServerNode node, NodeIndex index = InvalidNodeIndex);
	std::vector<ConnectorConfig > getConfigConnect(ServerNode node);
	const DBConfig & getDBConfig(DBConfigID id);

	ServerNode getOwnServerNode(){ return _ownServerNode; }
	NodeIndex getOwnNodeIndex(){ return _ownNodeIndex; }
	PlatID getPlatID() { return _platid; }
	AreaID getAreaID() { return _areaid; }



private:
	ServerNode _ownServerNode = InvalidServerNode;
	NodeIndex _ownNodeIndex = InvalidNodeIndex;
	PlatID _platid = 0;
	AreaID _areaid = 0;

	std::vector<::ListenConfig> _configListen;
	std::vector<ConnectorConfig> _configConnect;
	std::vector<DBConfig> _configDB;
};






























#endif