

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

#include "config.h"
extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
int luaopen_protoz_util(lua_State *L);
int luaopen_cjson(lua_State *l);
}


static ServerType toServerType(std::string strType)
{
    if (strType == "logic")
    {
        return LogicServer;
    }
    else if (strType == "stress")
    {
        return StressClient;
    }
    return InvalidServerType;
}

static DBConfigID toDBConfigID(std::string db)
{
    if (db == "info")
    {
        return InfoDB;
    }
    else if (db == "log")
    {
        return LogDB;
    }
    return InvalidDB;
}


const ListenConfig & ServerConfig::getConfigListen(ServerType node, ServerNode index)
{
    if (index == InvalidServerNode)
    {
        index = _ownServerNode;
    }
    auto founder = std::find_if(_configListen.begin(), _configListen.end(),
        [node, index](const ListenConfig & lc){return lc._node == node && lc._index == index; });
    if (founder == _configListen.end())
    {
        throw std::runtime_error("getConfigListen not found config.");
    }
    return *founder;
}


std::vector<ConnectConfig > ServerConfig::getConfigConnect(ServerType node)
{
    std::vector<ConnectConfig > ret;
    for (const auto & cc : _configConnect)
    {
        if (cc._srcType != node)
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


bool ServerConfig::parse(std::string filename, ServerType ownType, ServerNode ownNode)
{
    _ownServerType = ownType;
    _ownServerNode = ownNode;


    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);  /* open libraries */
    lua_atpanic(L, panichHandler);

    luaL_dofile(L, filename.c_str());
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
        lconfig._ip = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "port");
        lconfig._port = (unsigned short)luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "db");
        lconfig._db = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "user");
        lconfig._user = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "pwd");
        lconfig._pwd = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "db");
        lconfig._db = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lconfig._id = toDBConfigID(luaL_checkstring(L, -2));
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
        std::string node = luaL_checkstring(L, -2);

        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            ListenConfig lconfig;

            lua_getfield(L, -1, "ip");
            lconfig._ip = luaL_checkstring(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "port");
            lconfig._port = (unsigned short)luaL_checkinteger(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "wip");
            lconfig._wip = luaL_optstring(L, -1, "0.0.0.0");
            lua_pop(L, 1);

            lua_getfield(L, -1, "wport");
            lconfig._wport = (unsigned short)luaL_optinteger(L, -1, 0);
            lua_pop(L, 1);

            lua_getfield(L, -1, "index");
            lconfig._index = (ServerNode)luaL_checkinteger(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "white");
            if (lua_isnil(L, -1))
            {
                lua_pop(L, 1);
            }
            else
            {
                lua_pushnil(L);
                while (lua_next(L, -2))
                {
                    lconfig._whiteList.push_back(luaL_checkstring(L, -1));
                    lua_pop(L, 1);
                }
                //pop white table
                lua_pop(L, 1);
            }
            

            lconfig._node = toServerType(node);
            if (lconfig._node != InvalidServerType)
            {
                _configListen.push_back(lconfig);
                LOGI("ListenConfig=" << lconfig);
            }
            else
            {
                LOGE("UNKNOWN ListenConfig=" << lconfig);
            }
            //pop node table
            lua_pop(L, 1);
        }
        
        //pop node tables
        lua_pop(L, 1);
    }
    //pop listen table.
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
        std::string node = luaL_checkstring(L, -2);

        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            ConnectConfig lconfig;

            lua_getfield(L, -1, "ip");
            lconfig._remoteIP = luaL_checkstring(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "port");
            lconfig._remotePort = (unsigned short)luaL_checkinteger(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "index");
            lconfig._dstServerNode = (ServerNode)luaL_checkinteger(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "dstType");
            lconfig._dstType = toServerType(luaL_checkstring(L, -1));
            lua_pop(L, 1);

            lconfig._srcType = toServerType(node);

            if (lconfig._srcType != InvalidServerType && lconfig._dstType != InvalidServerType)
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


























