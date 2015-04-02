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
 * Copyright (C) 2010-2015 YaweiZhang <yawei_zhang@foxmail.com>.
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

static int pcall_error(lua_State* L)
{
	lua_getglobal(L, "debug");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);
	lua_pushinteger(L, 2);
	lua_call(L, 2, 1);
	return 1;
}

//////////////////////////////////////////////////////////////////////////

static int _connectCB = LUA_NOREF;
static int _messageCB = LUA_NOREF;
static int _disconnectCB = LUA_NOREF;

//在回调前检测模块是否已经被卸载
static std::vector<lua_State*> _vmCheck;

static int start(lua_State *L)
{
	SessionManager::getRef().start();
	return 0;
}

static int stop(lua_State *L)
{
	SessionManager::getRef().stop();
	return 0;
}

static int runOnce(lua_State * L)
{
	bool isImmediately = false;
	if (lua_gettop(L) > 0 && !lua_isnil(L, -1))
	{
		isImmediately = true;
	}
	SessionManager::getRef().runOnce(isImmediately);
	return 0;
}



static int addConnect(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1)
	{
		LOGE("addConnect error. argc is not 1.  the argc=" << argc);
		lua_settop(L, 0);
		lua_pushnil(L);
		return 1;
	}

	ConnectConfig config;


	{
		lua_getfield(L, 1, "ip");
		if (lua_isnil(L, -1))
		{
			lua_settop(L, 0);
			lua_pushnil(L);
			return 1;
		}
		else
		{
			size_t len = 0;
			const char * str = luaL_checklstring(L, -1, &len);
			if (str && len > 0)
			{
				config._remoteIP.clear();
				config._remoteIP.append(str, len);
			}
		}

	}


	{
		lua_getfield(L, 1, "port");
		if (lua_isnil(L, -1))
		{
			lua_settop(L, 0);
			lua_pushnil(L);
			return 1;
		}
		else
		{
			config._remotePort = (unsigned short)luaL_checknumber(L, -1);
		}
	}

	{
		lua_getfield(L, 1, "key");
		if (!lua_isnil(L, -1))
		{
			size_t len = 0;
			const char * str = luaL_checklstring(L, -1, &len);
			if (str && len > 0)
			{
				config._rc4TcpEncryption.clear();
				config._rc4TcpEncryption.append(str, len);
			}
		}
	}

	{
		lua_getfield(L, 1, "reconnect");
		if (!lua_isnil(L, -1))
		{
			config._reconnectMaxCount = (unsigned int)luaL_checknumber(L, -1);
		}
	}

	{
		lua_getfield(L, 1, "interval");
		if (!lua_isnil(L, -1))
		{
			config._pulseInterval = (unsigned int)luaL_checknumber(L, -1);
		}
	}


	lua_settop(L, 0);
	LOGD("lua: addConnect:" << config);
	SessionID id = SessionManager::getRef().addConnector(config);
	if (id == InvalidSeesionID)
	{
		lua_pushnil(L);
	}
	else
	{
		lua_pushnumber(L, id);
	}
	return 1;
}



static int addListen(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1)
	{
		LOGE("addListen error. argc is not 1.  the argc=" << argc);
		lua_settop(L, 0);
		lua_pushnil(L);
		return 1;
	}

	ListenConfig config;

	{
		lua_getfield(L, 1, "ip");
		if (lua_isnil(L, -1))
		{
			lua_settop(L, 0);
			lua_pushnil(L);
			return 1;
		}
		else
		{
			size_t len = 0;
			const char * str = luaL_checklstring(L, -1, &len);
			if (str && len > 0)
			{
				config._listenIP.clear();
				config._listenIP.append(str, len);
			}
		}

	}


	{
		lua_getfield(L, 1, "port");
		if (lua_isnil(L, -1))
		{
			lua_settop(L, 0);
			lua_pushnil(L);
			return 1;
		}
		else
		{
			config._listenPort = (unsigned short)luaL_checknumber(L, -1);
		}
	}

	{
		lua_getfield(L, 1, "key");
		if (!lua_isnil(L, -1))
		{
			size_t len = 0;
			const char * str = luaL_checklstring(L, -1, &len);
			if (str && len > 0)
			{
				config._rc4TcpEncryption.clear();
				config._rc4TcpEncryption.append(str, len);
			}
		}
	}

	{
		lua_getfield(L, 1, "maxSessions");
		if (!lua_isnil(L, -1))
		{
			config._maxSessions = (unsigned int)luaL_checknumber(L, -1);
		}
	}

	{
		lua_getfield(L, 1, "interval");
		if (!lua_isnil(L, -1))
		{
			config._pulseInterval = (unsigned int)luaL_checknumber(L, -1);
		}
	}


	lua_settop(L, 0);
	LOGD("lua: addListen:" << config);
	AccepterID id = SessionManager::getRef().addAcceptor(config);
	if (id == InvalidAccepterID)
	{
		lua_pushnil(L);
	}
	else
	{
		lua_pushnumber(L, id);
	}
	return 1;
}





static void _onConnecterCallback(lua_State * L, SessionID sID)
{
	auto founder = std::find_if(_vmCheck.begin(), _vmCheck.end(), [L](lua_State* l){return l == L; });
	if (founder == _vmCheck.end())
	{
		LOGW("_onConnecterCallback _vmCheck warning: L is not found . L=" << L);
		return;
	}
	if (_connectCB == LUA_NOREF)
	{
		LOGW("_onConnecterCallback warning: cannot found ther callback. L=" << L);
		return;
	}
	int index = lua_gettop(L);
	lua_pushcfunction(L, pcall_error);
	lua_rawgeti(L, LUA_REGISTRYINDEX, _connectCB);
	if (lua_isnil(L, -1))
	{
		LOGW("_onConnecterCallback warning: cannot found ther callback. L=" << L << ", ref=" << _connectCB);
		lua_settop(L, 0);
		return;
	}

	lua_pushnumber(L, sID);
	int status = lua_pcall(L, 1, 0, index+1);
	if (status && !lua_isnil(L, -1))
	{
		const char *msg = lua_tostring(L, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		lua_pop(L, 1);
	}
}

static int registerConnect(lua_State * L)
{
	int index = lua_gettop(L);
	if (index != 1)
	{
		LOGE("registerConnect error. argc is not 1.  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	if (_connectCB != LUA_NOREF)
	{
		LOGE("registerConnect error. connect callback already .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	
	int ret = luaL_ref(L, LUA_REGISTRYINDEX);
	if (ret == LUA_REFNIL)
	{
		LOGE("registerConnect error. callback function is nil .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	_connectCB = ret;
	
	MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(_onConnecterCallback, L, std::placeholders::_1));
	return 0;
}


static void _onMessageCallback(lua_State * L, SessionID sID, ProtoID pID, ReadStream & rs)
{
	auto founder = std::find_if(_vmCheck.begin(), _vmCheck.end(), [L](lua_State* l){return l == L; });
	if (founder == _vmCheck.end())
	{
		LOGW("_onMessageCallback _vmCheck warning: L is not found . L=" << L);
		return;
	}
	if (_messageCB == LUA_NOREF)
	{
		LOGW("_onMessageCallback warning: cannot found ther callback. L=" << L);
		return;
	}
	int index = lua_gettop(L);
	lua_pushcfunction(L, pcall_error);
	lua_rawgeti(L, LUA_REGISTRYINDEX, _messageCB);
	if (lua_isnil(L, -1))
	{
		LOGW("_onMessageCallback warning: cannot found ther callback. L=" << L << ", ref=" << _messageCB);
		lua_settop(L, 0);
		return;
	}

	lua_pushinteger(L, sID);
	lua_pushinteger(L, pID);
	lua_pushlstring(L, rs.getStreamBody(), rs.getStreamBodyLen());
	int status = lua_pcall(L, 3, 0, index + 1);
	if (status && !lua_isnil(L, -1))
	{
		const char *msg = lua_tostring(L, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		lua_pop(L, 1);
	}
}

static int registerMessage(lua_State * L)
{
	int index = lua_gettop(L);
	if (index != 1)
	{
		LOGE("registerMessage error. argc is not 1.  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	if (_messageCB != LUA_NOREF)
	{
		LOGE("registerMessage error. connect callback already .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}

	int ret = luaL_ref(L, LUA_REGISTRYINDEX);
	if (ret == LUA_REFNIL)
	{
		LOGE("registerMessage error. callback function is nil .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	_messageCB = ret;

	MessageDispatcher::getRef().registerSessionDefaultMessage(std::bind(_onMessageCallback, L, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	return 0;
}



static void _onDisconnectCallback(lua_State * L, SessionID sID)
{
	auto founder = std::find_if(_vmCheck.begin(), _vmCheck.end(), [L](lua_State* l){return l == L; });
	if (founder == _vmCheck.end())
	{
		LOGW("_onDisconnectCallback _vmCheck warning: L is not found . L=" << L);
		return;
	}
	if (_disconnectCB == LUA_NOREF)
	{
		LOGW("_onDisconnectCallback warning: cannot found ther callback. L=" << L);
		return;
	}
	int index = lua_gettop(L);
	lua_pushcfunction(L, pcall_error);
	lua_rawgeti(L, LUA_REGISTRYINDEX, _disconnectCB);
	if (lua_isnil(L, -1))
	{
		LOGW("_onDisconnectCallback warning: cannot found ther callback. L=" << L << ", ref=" << _disconnectCB);
		lua_settop(L, 0);
		return;
	}

	lua_pushnumber(L, sID);
	int status = lua_pcall(L, 1, 0, index + 1);
	if (status && !lua_isnil(L, -1))
	{
		const char *msg = lua_tostring(L, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		lua_pop(L, 1);
	}
}

static int registerDisconnect(lua_State * L)
{
	int index = lua_gettop(L);
	if (index != 1)
	{
		LOGE("registerDisconnect error. argc is not 1.  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	if (_disconnectCB != LUA_NOREF)
	{
		LOGE("registerDisconnect error. connect callback already .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}

	int ret = luaL_ref(L, LUA_REGISTRYINDEX);
	if (ret == LUA_REFNIL)
	{
		LOGE("registerDisconnect error. callback function is nil .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	_disconnectCB = ret;

	MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(_onDisconnectCallback, L, std::placeholders::_1));
	return 0;
}


static int sendContent(lua_State * L)
{
	int index = lua_gettop(L);
	if (index != 3)
	{
		LOGE("sendContent error. argc is not 3.  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	SessionID sID = (SessionID)luaL_checkinteger(L, 1);
	zsummer::proto4z::ProtoInteger pID = (zsummer::proto4z::ProtoInteger)luaL_checkinteger(L, 2);


	size_t len = 0;
	const char * content = luaL_checklstring(L, 3, &len);
	WriteStream ws(pID);
	ws.appendOriginalData(content, (zsummer::proto4z::Integer)len);
	SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());

	return 0;
}

static int sendData(lua_State * L)
{
	int index = lua_gettop(L);
	if (index != 2)
	{
		LOGE("sendData error. argc is not 2.  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	SessionID sID = (SessionID)luaL_checkinteger(L, 1);
	size_t len = 0;
	const char * data = luaL_checklstring(L, 2, &len);
	if (data == NULL || len == 0)
	{
		LOGE("sendData error. no any data.");
		lua_settop(L, 0);
		return 0;
	}

	SessionManager::getRef().sendOrgSessionData(sID, data, (unsigned short)len);
	return 0;
}

static int kick(lua_State * L)
{
	int index = lua_gettop(L);
	if (index != 1)
	{
		LOGE("kick error. argc is not 1.  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
	SessionID sID = (SessionID)luaL_checkinteger(L, 1);

	SessionManager::getRef().kickSession(sID);
	return 0;
}

static void onPost(lua_State * L, int delay, int refID)
{
	auto founder = std::find_if(_vmCheck.begin(), _vmCheck.end(), [L](lua_State* l){return l == L; });
	if (founder == _vmCheck.end())
	{
		LOGW("onPost _vmCheck warning: L is not found . L=" << L);
		return;
	}

	int index = lua_gettop(L);
	lua_pushcfunction(L, pcall_error);
	lua_rawgeti(L, LUA_REGISTRYINDEX, refID);
	if (lua_isnil(L, -1))
	{
		LOGW("onPost warning: cannot found ther callback. L=" << L << ", ref=" << refID);
		lua_settop(L, 0);
		return;
	}
	int status = lua_pcall(L, 0, 0, index + 1);
	if (status && !lua_isnil(L, -1))
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
	int index = lua_gettop(L);
	if (index != 2)
	{
		LOGE("post error. argc is not 2 [delay,function].  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}

	int delay = (int)luaL_checkinteger(L, 1);
	if (!lua_isfunction(L, -1))
	{
		LOGE("post error. found out callback function.  the argc=" << index);
		lua_settop(L, 0);
	}
	
	int ret = luaL_ref(L, LUA_REGISTRYINDEX);
	if (ret == LUA_REFNIL)
	{
		LOGE("post error. callback function is nil .  the argc=" << index);
		lua_settop(L, 0);
		return 0;
	}
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

luaL_Reg summer[] = {
	{ "logd", logd },
	{ "logi", logi },
	{ "logt", logt },
	{ "logw", logw },
	{ "loge", loge },
	{ "logf", logf },
	{ "loga", loga },

	{ "start", start }, //start network
	{ "stop", stop }, //stop network
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
	auto founder = std::find_if(_vmCheck.begin(), _vmCheck.end(), [L](lua_State* l){return l == L; });
	if (founder == _vmCheck.end())
	{
		LOGI("registerSummer: L=" << L);
		_vmCheck.push_back(L);
	}
	else
	{
		LOGW("registerSummer warning: L is registered . L=" << L);
	}

	lua_newtable(L);
	for (luaL_Reg *l = summer; l->name != NULL; l++) {  
		lua_pushcclosure(L, l->func, 0);  /* closure with those upvalues */
		lua_setfield(L, -2, l->name);
	}
	lua_setglobal(L, "summer");

	return 0;
}

int luaclose_summer(lua_State *L)
{
	auto founder = std::find_if(_vmCheck.begin(), _vmCheck.end(), [L](lua_State* l){return l == L; });
	if (founder != _vmCheck.end())
	{
		LOGI("unregisterSummer: L=" << L);
		_vmCheck.erase(founder);
	}
	else
	{
		LOGW("unregisterSummer warning: L is not found. L=" << L);
	}
	return 0;
}




