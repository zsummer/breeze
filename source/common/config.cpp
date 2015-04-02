

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

#include "config.h"
extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "lua/lpack.h"
	int luaopen_protoz_bit(lua_State *L);
	int luaopen_cjson(lua_State *l);
}


static ServerNode toServerNode(std::string strNode)
{
	if (strNode == "logic")
	{
		return LogicNode;
	}
	else if (strNode == "stress")
	{
		return StressNode;
	}
	return InvalidServerNode;
}

static DBConfigID toDBConfigID(std::string db)
{
	if (db == "auth")
	{
		return AuthDB;
	}
	else if (db == "info")
	{
		return InfoDB;
	}
	else if (db == "log")
	{
		return LogDB;
	}
	return InvalidDB;
}


const ::ListenConfig & ServerConfig::getConfigListen(ServerNode node, NodeIndex index)
{
	if (index == InvalidNodeIndex)
	{
		index = _ownNodeIndex;
	}
	auto founder = std::find_if(_configListen.begin(), _configListen.end(),
		[node, index](const ::ListenConfig & lc){return lc._node == node && lc._index == index; });
	if (founder == _configListen.end())
	{
		static ::ListenConfig lc;
		return lc;
	}
	return *founder;
}


std::vector<ConnectorConfig > ServerConfig::getConfigConnect(ServerNode node)
{
	std::vector<ConnectorConfig > ret;
	for (const auto & cc : _configConnect)
	{
		if (cc._srcNode != node)
		{
			continue;
		}
		ret.push_back(cc);
	}
	
	return ret;
}


const DBConfig & ServerConfig::getDBConfig(DBConfigID id)
{
	auto founder = std::find_if(_configDB.begin(), _configDB.end(),
		[id](const DBConfig & db){return db._id == id; });
	if (founder == _configDB.end())
	{
		static DBConfig db;
		return db;
	}
	return *founder;
}



static int panichHandler(lua_State * L)
{
	std::string errMsg = lua_tostring(L, -1);
	LOGE(errMsg);
	return 0;
}


bool ServerConfig::parse(std::string filename, ServerNode ownNode, NodeIndex ownIndex)
{
	_ownServerNode = ownNode;
	_ownNodeIndex = ownIndex;


	int status;
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		return EXIT_FAILURE;
	}
	luaL_openlibs(L);  /* open libraries */
	lua_atpanic(L, panichHandler);

	status = luaL_dofile(L, filename.c_str());
	int index = lua_gettop(L);
	lua_getfield(L, -1, "traits");
	lua_getfield(L, -1, "platid");
	_platid = (unsigned short)luaL_checkinteger(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, -1, "areaid");
	_areaid = (unsigned short)luaL_checkinteger(L, -1);
	lua_pop(L, 2);

	lua_getfield(L, -1, "db");
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		if (!lua_isstring(L, -2))
		{
			LOGE("config parse db false. key is not string type");
			return false;
		}
		

		DBConfig lconfig;
		lua_getfield(L, -1, "ip");
		lconfig._ip = lua_tostring(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "port");
		lconfig._port = (unsigned short)lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "db");
		lconfig._db = lua_tostring(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "user");
		lconfig._user = lua_tostring(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "pwd");
		lconfig._pwd = lua_tostring(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "db");
		lconfig._db = lua_tostring(L, -1);
		lua_pop(L, 1);

		lconfig._id = toDBConfigID(lua_tostring(L, -2));
		if (lconfig._id != InvalidDB)
		{
			_configDB.push_back(lconfig);
			LOGI("DBConfig=" << lconfig);
		}
		else
		{
			LOGE("unknown DBConfig=" << lconfig);
		}

		//saved key to next while.
		lua_pop(L, 1);
	}
	//pop "db" table.
	lua_pop(L, 1);


	lua_getfield(L, -1, "listen");
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		if (!lua_isstring(L, -2))
		{
			LOGE("config parse listen false. key is not string type");
			return false;
		}
		std::string node = lua_tostring(L, -2);

		lua_pushnil(L);
		while (lua_next(L, -2))
		{
			::ListenConfig lconfig;

			lua_getfield(L, -1, "ip");
			lconfig._ip = lua_tostring(L, -1);
			lua_pop(L, 1);

			lua_getfield(L, -1, "port");
			lconfig._port = (unsigned short)lua_tointeger(L, -1);
			lua_pop(L, 1);

			lua_getfield(L, -1, "index");
			lconfig._index = (NodeIndex)lua_tointeger(L, -1);
			lua_pop(L, 1);


			lconfig._node = toServerNode(node);
			if (lconfig._node != InvalidServerNode)
			{
				_configListen.push_back(lconfig);
				LOGI("ListenConfig=" << lconfig);
			}
			else
			{
				LOGE("UNKNOWN ListenConfig=" << lconfig);
			}

			//saved key to next while.
			lua_pop(L, 1);
		}
		
		//saved key to next while.
		lua_pop(L, 1);
	}
	//pop "listen" table.
	lua_pop(L, 1);


	lua_getfield(L, -1, "connect");
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		if (!lua_isstring(L, -2))
		{
			LOGE("config parse connect false. key is not string type");
			return false;
		}
		std::string node = lua_tostring(L, -2);

		lua_pushnil(L);
		while (lua_next(L, -2))
		{
			ConnectorConfig lconfig;

			lua_getfield(L, -1, "ip");
			lconfig._remoteIP = lua_tostring(L, -1);
			lua_pop(L, 1);

			lua_getfield(L, -1, "port");
			lconfig._remotePort = (unsigned short)lua_tointeger(L, -1);
			lua_pop(L, 1);

			lua_getfield(L, -1, "index");
			lconfig._dstNodeIndex = (NodeIndex)lua_tointeger(L, -1);
			lua_pop(L, 1);

			lua_getfield(L, -1, "dstNode");
			lconfig._dstNode = toServerNode(lua_tostring(L, -1));
			lua_pop(L, 1);

			lconfig._srcNode = toServerNode(node);

			if (lconfig._srcNode != InvalidServerNode && lconfig._dstNode != InvalidServerNode)
			{
				_configConnect.push_back(lconfig);
				LOGI("_configConnect=" << lconfig);
			}
			else
			{
				LOGE("UNKNOWN ConnectConfig=" << lconfig);
			}

			//saved key to next while.
			lua_pop(L, 1);
		}

		//saved key to next while.
		lua_pop(L, 1);
	}
	//pop "connect" table.
	lua_pop(L, 1);

	lua_close(L);
	return true;
}


























