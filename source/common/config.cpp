

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

#include "config.h"
extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
int luaopen_protoz_util(lua_State *L);
int luaopen_cjson(lua_State *l);
}
#include "utls.h"

static int panichHandler(lua_State * L)
{
    std::string errMsg = lua_tostring(L, -1);
    LOGE(errMsg);
    return 0;
}


bool ServerConfig::parse(std::string filename, DockerID idx)
{
    srand(time(NULL));
    _dockerIdx = idx;
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);  /* open libraries */
    lua_atpanic(L, panichHandler);
    if (luaL_dofile(L, filename.c_str()))
    {
        LOGE("can't found the config file. filename=" << filename);
        return false;
    }
    lua_getfield(L, -1, "areaid");
    _areaid = (unsigned short)luaL_optinteger(L, -1, 0);
    lua_pop(L, 1);
    LOGI("ServerConfig::parse dockerID=" << idx << ", areaid=" << _areaid << ", getMinServiceID=" << getMinServiceID());

    lua_getfield(L, -1, "db");
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        if (!lua_isstring(L, -2))
        {
            LOGE("config parse db false. key is not string type");
            return false;
        }
        if (!lua_istable(L, -1))
        {
            LOGE("config parse db false. value is not table type");
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

        lconfig._name = luaL_checkstring(L, -2);
        _configDB.push_back(lconfig);
        LOGI("DBConfig=" << lconfig);
        lua_pop(L, 1);
    }
    //pop key "db".
    lua_pop(L, 1);


    lua_getfield(L, -1, "docker");
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        if (!lua_istable(L, -1))
        {
            LOGE("config parse docker false. value is not table type");
            return false;
        }

        DockerConfig lconfig;
        lua_getfield(L, -1, "serviceBindIP");
        lconfig._serviceBindIP = luaL_optstring(L, -1, "0.0.0.0");
        lua_pop(L, 1);

        lua_getfield(L, -1, "serviceIP");
        lconfig._serviceIP = luaL_optstring(L, -1, "127.0.0.1");
        lua_pop(L, 1);
        lua_getfield(L, -1, "servicePort");
        lconfig._servicePort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);


        lua_getfield(L, -1, "wideIP");
        lconfig._wideIP = luaL_optstring(L, -1, "");
        lua_pop(L, 1);
        lua_getfield(L, -1, "widePort");
        lconfig._widePort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);

        lua_getfield(L, -1, "webIP");
        lconfig._webIP = luaL_optstring(L, -1, "");
        lua_pop(L, 1);
        lua_getfield(L, -1, "webPort");
        lconfig._webPort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);

        lua_getfield(L, -1, "dockerID");
        lconfig._dockerID = (DockerID)luaL_checkinteger(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "serviceWhite");
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
            lua_pop(L, 1);
        }

        lua_getfield(L, -1, "services");
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
        }
        else
        {
            lua_pushnil(L);
            while (lua_next(L, -2))
            {
                std::string service = luaL_checkstring(L, -1);
                auto founder = std::find(ServiceTypeNames.begin(), ServiceTypeNames.end(), service);
                if (founder != ServiceTypeNames.end())
                {
                    lconfig._services.push_back((founder - ServiceTypeNames.begin()));
                }
                else
                {
                    LOGE("not found service [" << service << "]");
                    return false;
                }
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }
        _configDocker.push_back(lconfig);
        lua_pop(L, 1);
    }
    //pop listen table.
    lua_pop(L, 1);

    lua_close(L);

    for (auto & config : _configDocker)
    {
        for (auto & serviceType : config._services)
        {
            auto &dockerIDs = _configServiceType[serviceType];
            dockerIDs.push_back(config._dockerID);
        }
    }
    for (ui16 i = ServiceInvalid + 1; i < ServiceMulti; i++)
    {
        auto founder = _configServiceType.find(i);
        if (founder == _configServiceType.end() || founder->second.empty())
        {
            LOGE("not found service in docker config. the service name=" << ServiceTypeNames.at(i));
            return false;
        }
        if (founder->second.size() != 1)
        {
            LOGE("service in docker config not single. the service name=" << ServiceTypeNames.at(i));
            return false;
        }
    }
    for (ui16 i = ServiceMulti + 1; i < ServiceMax; i++)
    {
        if (i == ServiceClient)
        {
            continue;
        }
        auto founder = _configServiceType.find(i);
        if (founder == _configServiceType.end() || founder->second.empty())
        {
            LOGE("not found service in docker config. the service name=" << ServiceTypeNames.at(i));
            return false;
        }
    }

    return true;
}


























