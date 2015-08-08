/*
 * zsummerX License
 * -----------
 * 
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2010-2015 YaweiZhang <yawei.zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */

#include "summer.h"

#include <zsummerX/zsummerX.h>
using namespace zsummer::proto4z;
using namespace zsummer::network;




static int logt(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGT("from lua: " << log);
    return 0;
}
static int logd(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGD("from lua: " << log);
    return 0;
}
static int logi(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGI("from lua: " << log);
    return 0;
}
static int logw(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGW("from lua: " << log);
    return 0;
}
static int loge(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGE("from lua: " << log);
    return 0;
}
static int logf(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGF("from lua: " << log);
    return 0;
}
static int loga(lua_State * L)
{
    const char * log = luaL_checkstring(L, 1);
    LOGA("from lua: " << log);
    return 0;
}

static int pcall_error(lua_State *L) 
{
    const char *msg = lua_tostring(L, 1);
    if (msg)
    {
        luaL_traceback(L, L, msg, 1);
    }
    else if (!lua_isnoneornil(L, 1)) 
    {  /* is there an error object? */
        if (!luaL_callmeta(L, 1, "__tostring"))  /* try its 'tostring' metamethod */
        {
            lua_pushliteral(L, "(no error message)");
        }
    }
    return 1;
}


//////////////////////////////////////////////////////////////////////////

static int _connectCB = LUA_NOREF;
static int _messageCB = LUA_NOREF;
static int _disconnectCB = LUA_NOREF;
static lua_State * _L = nullptr;

static int lua53_rawgeti(lua_State * L, int index, lua_Integer n)
{
    lua_rawgeti(L, index, n);
    return lua_type(L, -1);
}

static void onStopServersFinish()
{
    SessionManager::getRef().stop();
}

static void onStopClientsFinish()
{
    SessionManager::getRef().stopServers();
}


static int start(lua_State *L)
{
    SessionManager::getRef().start();
    SessionManager::getRef().setStopClientsHandler(onStopClientsFinish);
    SessionManager::getRef().setStopServersHandler(onStopServersFinish);
    return 0;
}


static int stop(lua_State *L)
{
    SessionManager::getRef().stopAccept();
    SessionManager::getRef().stopClients();
    return 0;
}

static int runOnce(lua_State * L)
{
    int isImmediately = lua_toboolean(L, -1);
    bool ret = SessionManager::getRef().runOnce(!!isImmediately);
    lua_pushboolean(L, ret);
    return 1;
}

static int run(lua_State * L)
{
    while (SessionManager::getRef().runOnce());
    return 0;
}

static int addConnect(lua_State *L)
{
    ConnectConfig config;
    config._remoteIP = luaL_optstring(L, 1,  config._remoteIP.c_str());
    config._remotePort = (unsigned short)luaL_optinteger(L, 2, config._remotePort);
    config._rc4TcpEncryption = luaL_optstring(L, 3, config._rc4TcpEncryption.c_str());
    config._reconnectMaxCount = (unsigned int)luaL_optinteger(L, 4, config._reconnectMaxCount);
    config._reconnectInterval = (unsigned int)luaL_optinteger(L, 5, config._reconnectInterval);

    LOGD("lua: addConnect:" << config);
    SessionID id = SessionManager::getRef().addConnector(config);
    if (id == InvalidSeesionID)
    {
        return 0;
    }
    lua_pushnumber(L, id);
    return 1;
}



static int addListen(lua_State *L)
{
    ListenConfig config;
    config._listenIP = luaL_optstring(L, 1, config._listenIP.c_str());
    config._listenPort = (unsigned short)luaL_optinteger(L, 2, config._listenPort);
    config._rc4TcpEncryption = luaL_optstring(L, 3, config._rc4TcpEncryption.c_str());
    config._maxSessions = (unsigned int)luaL_optinteger(L, 4, config._maxSessions);
    config._pulseInterval = (unsigned int)luaL_optinteger(L, 5, config._pulseInterval);

    LOGD("lua: addListen:" << config);
    AccepterID id = SessionManager::getRef().addAcceptor(config);
    if (id == InvalidAccepterID)
    {
        return 0;
    }
    lua_pushnumber(L, id);
    return 1;
}


static void _onConnecterCallback(lua_State * L, TcpSessionPtr session)
{
    lua_pushcfunction(L, pcall_error);
    lua_rawgeti(L, LUA_REGISTRYINDEX, _connectCB);
    lua_pushnumber(L, session->getSessionID());
    lua_pushstring(L, session->getRemoteIP().c_str());
    lua_pushnumber(L, session->getRemotePort());
    int status = lua_pcall(L, 3, 0, 1);
    lua_remove(L, 1);
    if (status)
    {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGE(msg);
        lua_pop(L, 1);
    }
}

static int registerConnect(lua_State * L)
{
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_settop(L, 1);
    if (_connectCB != LUA_NOREF)
    {
        LOGE("registerConnect error. connect callback already .");
        return 0;
    }
    _connectCB = luaL_ref(L, LUA_REGISTRYINDEX);
    MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(_onConnecterCallback, L, std::placeholders::_1));
    return 0;
}


static void _onMessageCallback(lua_State * L,TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
    lua_pushcfunction(L, pcall_error);
    lua_rawgeti(L, LUA_REGISTRYINDEX, _messageCB);
    lua_pushinteger(L, session->getSessionID());
    lua_pushinteger(L, pID);
    lua_pushlstring(L, rs.getStreamBody(), rs.getStreamBodyLen());
    int status = lua_pcall(L, 3, 0, 1);
    lua_remove(L, 1);
    if (status)
    {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGE(msg);
        lua_pop(L, 1);
    }
}

static int registerMessage(lua_State * L)
{
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_settop(L, 1);
    if (_messageCB != LUA_NOREF)
    {
        LOGE("registerMessage error. connect callback already .");
        return 0;
    }
    _messageCB = luaL_ref(L, LUA_REGISTRYINDEX);
    MessageDispatcher::getRef().registerSessionDefaultMessage(std::bind(_onMessageCallback, L, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    return 0;
}



static void _onDisconnectCallback(lua_State * L, TcpSessionPtr session)
{
    if (_disconnectCB == LUA_NOREF)
    {
        LOGW("_onDisconnectCallback warning: cannot found ther callback.");
        return;
    }
    lua_pushcfunction(L, pcall_error);
    lua_rawgeti(L, LUA_REGISTRYINDEX, _disconnectCB);
    lua_pushnumber(L, session->getSessionID());
    lua_pushstring(L, session->getRemoteIP().c_str());
    lua_pushnumber(L, session->getRemotePort());
    int status = lua_pcall(L, 3, 0, 1);
    lua_remove(L, 1);
    if (status)
    {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGE(msg);
        lua_pop(L, 1);
    }
}

static int registerDisconnect(lua_State * L)
{
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_settop(L, 1);
    if (_disconnectCB != LUA_NOREF)
    {
        LOGE("registerDisconnect error. connect callback already .");
        return 0;
    }

    _disconnectCB = luaL_ref(L, LUA_REGISTRYINDEX);
    MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(_onDisconnectCallback, L, std::placeholders::_1));
    return 0;
}


static int sendContent(lua_State * L)
{
    SessionID sID = (SessionID)luaL_checkinteger(L, 1);
    zsummer::proto4z::ProtoInteger pID = (zsummer::proto4z::ProtoInteger)luaL_checkinteger(L, 2);
    size_t len = 0;
    const char * content = luaL_checklstring(L, 3, &len);
    WriteStream ws(pID);
    ws.appendOriginalData(content, (zsummer::proto4z::Integer)len);
    SessionManager::getRef().sendSessionData(sID, ws.getStream(), ws.getStreamLen());
    return 0;
}

static int sendData(lua_State * L)
{
    SessionID sID = (SessionID)luaL_checkinteger(L, 1);
    size_t len = 0;
    const char * data = luaL_checklstring(L, 2, &len);
    SessionManager::getRef().sendSessionData(sID, data, (unsigned short)len);
    return 0;
}

static int kick(lua_State * L)
{
    SessionID sID = (SessionID)luaL_checkinteger(L, 1);
    SessionManager::getRef().kickSession(sID);
    return 0;
}

static void onPost(lua_State * L, int delay, int refID)
{
    lua_pushcfunction(L, pcall_error);
    lua_rawgeti(L, LUA_REGISTRYINDEX, refID);
    int status = lua_pcall(L, 0, 0, 1);
    lua_remove(L, 1);
    if (status)
    {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGE(msg);
        lua_pop(L, 1);
    }
    luaL_unref(L, LUA_REGISTRYINDEX, refID);
}

static int _post(lua_State * L)
{
    int delay = (int)luaL_checkinteger(L, 1);
    luaL_checktype(L, -1, LUA_TFUNCTION);
    int ret = luaL_ref(L, LUA_REGISTRYINDEX);
    if (delay <= 0)
    {
        SessionManager::getRef().post(std::bind(onPost, L, delay, ret));
    }
    else
    {
        SessionManager::getRef().createTimer(delay, std::bind(onPost, L, delay, ret));
    }
    return 0;
}

static luaL_Reg summer[] = {
    { "logd", logd },
    { "logi", logi },
    { "logt", logt },
    { "logw", logw },
    { "loge", loge },
    { "logf", logf },
    { "loga", loga },

    { "start", start }, //start network
    { "stop", stop }, //stop network
    { "run", run }, //run
    { "runOnce", runOnce }, //message pump, run it once.
    { "addConnect", addConnect }, //add one connect.
    { "addListen", addListen }, //add listen.
    { "registerConnect", registerConnect }, //register event when connect success.
    { "registerMessage", registerMessage }, //register event when recv message.
    { "registerDisconnect", registerDisconnect }, //register event when disconnect.
    { "sendContent", sendContent }, //send content, don't care serialize and package.
    { "sendData", sendData }, // send original data, need to serialize and package via proto4z. 
    { "kick", kick }, // kick session. 
    { "post", _post }, // kick session. 

    { NULL, NULL }
};


int luaopen_summer(lua_State *L)
{
    lua_newtable(L);
    for (luaL_Reg *l = summer; l->name != NULL; l++) {  
        lua_pushcclosure(L, l->func, 0);  /* closure with those upvalues */
        lua_setfield(L, -2, l->name);
    }
    lua_setglobal(L, "summer");
    return 0;
}



