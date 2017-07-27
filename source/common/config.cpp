

/*
* breeze License
* Copyright (C) 2014-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
    LOGE("panichHandler:" << errMsg);
    return 0;
}


bool ServerConfig::parseDocker(std::string configName, DockerID dockerID)
{
    srand((unsigned int)time(NULL));
    _dockerID = dockerID;
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);  /* open libraries */
    lua_atpanic(L, panichHandler);
    if (luaL_dofile(L, configName.c_str()))
    {
        LOGE("can't found the config file. configName=" << configName);
        return false;
    }
    lua_getfield(L, -1, "areaID");
    _areaID = (unsigned short)luaL_optinteger(L, -1, 0);
    lua_pop(L, 1);
    LOGI("ServerConfig::parse dockerID=" << dockerID << ", _areaID=" << _areaID << ", getMinServiceID=" << getMinServiceID());




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
        lua_getfield(L, -1, "dockerListenHost");
        lconfig._dockerListenHost = luaL_optstring(L, -1, "::");
        lua_pop(L, 1);

        lua_getfield(L, -1, "dockerPubHost");
        lconfig._dockerPubHost = luaL_optstring(L, -1, "127.0.0.1");
        lua_pop(L, 1);
        lua_getfield(L, -1, "dockerListenPort");
        lconfig._dockerListenPort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);


        lua_getfield(L, -1, "clientPubHost");
        lconfig._clientPubHost = luaL_optstring(L, -1, "");
        lua_pop(L, 1);
        lua_getfield(L, -1, "clientPubPort");
        lconfig._clientPubPort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);

        lua_getfield(L, -1, "webPubHost");
        lconfig._webPubHost = luaL_optstring(L, -1, "");
        lua_pop(L, 1);
        lua_getfield(L, -1, "webPort");
        lconfig._webPubPort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);

        lua_getfield(L, -1, "dockerID");
        lconfig._dockerID = (DockerID)luaL_checkinteger(L, -1);
        lua_pop(L, 1);




        lua_getfield(L, -1, "dockerWhite");
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
        }
        else
        {
            lua_pushnil(L);
            while (lua_next(L, -2))
            {
                lconfig._dockerWhite.push_back(luaL_checkstring(L, -1));
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
                std::string serviceName = luaL_checkstring(L, -1);
                ServiceType serviceType = getServiceTypeByKey(serviceName);
                if (serviceType != InvalidServiceType)
                {
                    lconfig._services.push_back(serviceType);
                }
                else
                {
                    LOGE("not found serviceName [" << serviceName << "]");
                    return false;
                }
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }
        _configs.push_back(lconfig);
        lua_pop(L, 1);
    }
    //pop listen table.
    lua_pop(L, 1);

    lua_close(L);

    //构建service和docker的装载关系  
    for (auto & config : _configs)
    {
        for (auto & serviceType : config._services)
        {
             _serviceLoadDockers[serviceType].push_back(config._dockerID);
        }
    }
    //异构Service如果没有配置docker 则添加一个空的关系
    for (const auto & sd : ServiceDepends)
    {
        if (getServiceTrait(sd.first) == STrait_Heterogenous )
        {
            _serviceLoadDockers[sd.first];
        }
    }

    //检查装载关系, 单例模式必须有且只有一个docker, 多例模式必须有,但可以多于一个docker  
    for (const auto & sd : ServiceDepends)
    {
        if (sd.first == STClient)
        {
            continue;
        }
        auto founder = _serviceLoadDockers.find(sd.first);
        if ((founder == _serviceLoadDockers.end() || founder->second.empty()) && getServiceTrait(sd.first) != STrait_Heterogenous)
        {
            LOGE("not found service in docker config. the service name=" << getServiceName(sd.first));
            return false;
        }
        if (getServiceTrait(sd.first) == STrait_Single  && founder->second.size() != 1)
        {
            LOGE("duplicate service name in docker config . the service name=" << getServiceName(sd.first));
            return false;
        }
    }

    return true;
}






bool ServerConfig::parseDB(std::string configName)
{
    srand((unsigned int)time(NULL));
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);  /* open libraries */
    lua_atpanic(L, panichHandler);
    if (luaL_loadfile(L, configName.c_str()))
    {
        LOGE("ServerConfig can't load  file [" << configName << "]");
        return false;
    }
    if (lua_pcall(L, 0, LUA_MULTRET, 0))
    {
        LOGE("ServerConfig can't pcall  file [" << configName << "]");
        return false;
    }

    lua_getfield(L, -1, "db");
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        if (!lua_isstring(L, -2))
        {
            LOGE("ServerConfig  parse db config failed. key is not string type");
            return false;
        }
        if (!lua_istable(L, -1))
        {
            LOGE("ServerConfig parse db config failed. value is not table type");
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
    lua_close(L);
    return true;
}

bool ServerConfig::parseWorld(std::string configName)
{
    srand((unsigned int)time(NULL));
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);  /* open libraries */
    lua_atpanic(L, panichHandler);
    if (luaL_dofile(L, configName.c_str()))
    {
        LOGE("can't found the config file. configName=" << configName);
        return false;
    }
    lua_getfield(L, -1, "world");

    lua_getfield(L, -1, "dockerID");
    _worldConfig._dockerID = (DockerID)luaL_checkinteger(L, -1);
    _dockerID = _worldConfig._dockerID;
    lua_pop(L, 1);

    lua_getfield(L, -1, "dockerListenHost");
    _worldConfig._dockerListenHost = luaL_checkstring(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "dockerListenPort");
    _worldConfig._dockerListenPort = (unsigned short)luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "sceneListenHost");
    _worldConfig._sceneListenHost = luaL_checkstring(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "scenePubHost");
    _worldConfig._scenePubHost = luaL_checkstring(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "sceneListenPort");
    _worldConfig._sceneListenPort = (unsigned short)luaL_checkinteger(L, -1);
    lua_pop(L, 1);
    lua_close(L);
    return true;
}


bool ServerConfig::parseScenes(std::string configName, ui32 serverID)
{
    srand((unsigned int)time(NULL));
    _scene._lineID = serverID;
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return EXIT_FAILURE;
    }
    luaL_openlibs(L);  /* open libraries */
    lua_atpanic(L, panichHandler);
    if (luaL_dofile(L, configName.c_str()))
    {
        LOGE("can't found the config file. configName=" << configName);
        return false;
    }

    LOGI("ServerConfig::parse serverID=" << serverID << ", configName=" << configName);




    lua_getfield(L, -1, "scenes");
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        if (!lua_istable(L, -1))
        {
            LOGE("config parse scenes false. value is not table type");
            return false;
        }

        LineConfig sconfig;
        lua_getfield(L, -1, "clientListenHost");
        sconfig._clientListenHost = luaL_optstring(L, -1, "::");
        lua_pop(L, 1);

        lua_getfield(L, -1, "clientPubHost");
        sconfig._clientPubHost = luaL_optstring(L, -1, "127.0.0.1");
        lua_pop(L, 1);

        lua_getfield(L, -1, "clientListenPort");
        sconfig._clientListenPort = (unsigned short)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);


        lua_getfield(L, -1, "lineID");
        sconfig._lineID = (unsigned int)luaL_optinteger(L, -1, 0);
        lua_pop(L, 1);

        if (_scene._lineID == sconfig._lineID)
        {
            _scene = sconfig;
        }

        lua_pop(L, 1);
    }
    //pop listen table.
    lua_pop(L, 1);

    lua_close(L);

    if (_scene._clientListenPort == 0)
    {
        return false;
    }
    return true;
}




















