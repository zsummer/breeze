
#include "eventTrigger.h"
using namespace zsummer::mysql;

EventTrigger::EventTrigger()
{

}

EventTrigger::~EventTrigger()
{
	if (_luaState)
	{
		lua_close(_luaState);
		_luaState = nullptr;
	}
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

static int trigger_watching(lua_State * L)
{
	if (lua_gettop(L) != 2 || !lua_isnumber(L, 1) || !lua_isfunction(L, 2))
	{
		LOGE("trigger_watching param error.");
		lua_settop(L, 0);
		return 0;
	}
	unsigned short triggerID = (unsigned short)luaL_checknumber(L, 1);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	EventTrigger::getRef().watching((EventTriggerEnum)triggerID, ref);
	lua_settop(L, 0);
	return 0;
}

static int trigger_unwatching(lua_State * L)
{
	if (lua_gettop(L) != 1 || !lua_isnumber(L, 1))
	{
		LOGE("trigger_unwatching param error.");
		lua_settop(L, 0);
		return 0;
	}
	unsigned short ref = (unsigned short)luaL_checknumber(L, 1);
	luaL_unref(L,LUA_REGISTRYINDEX, ref);
	return 0;
}

const char * __triggerEntry = "trigger";
static luaL_Reg trigger[] = 
{
	{ "watching", trigger_watching }, //start network
	{ "unwatching", trigger_unwatching }, //start network
	{ NULL, NULL }
};

bool EventTrigger::init()
{
	_luaState = luaL_newstate();
	if (!_luaState)
	{
		return false;
	}
	lua_gc(_luaState, LUA_GCSTOP, 0);  /* stop collector during initialization */
	luaL_openlibs(_luaState);  /* open libraries */
	luaopen_summer(_luaState);
	luaopen_pack(_luaState);
	luaopen_protoz_bit(_luaState);
	luaopen_cjson(_luaState);
	lua_gc(_luaState, LUA_GCRESTART, 0);

	lua_getglobal(_luaState, "summer");
	lua_getfield(_luaState, -1, "logd");
	lua_setglobal(_luaState, "logd");
	lua_getfield(_luaState, -1, "logi");
	lua_setglobal(_luaState, "logi");
	lua_getfield(_luaState, -1, "logw");
	lua_setglobal(_luaState, "logw");
	lua_getfield(_luaState, -1, "loge");
	lua_setglobal(_luaState, "loge");
	lua_getfield(_luaState, -1, "logi");
	lua_setglobal(_luaState, "print");
	lua_pop(_luaState, 1);


	lua_newtable(_luaState);
	for (luaL_Reg *l = ::trigger; l->name != NULL; l++) {
		lua_pushcclosure(_luaState, l->func, 0);  /* closure with those upvalues */
		lua_setfield(_luaState, -2, l->name);
	}
	lua_setglobal(_luaState, __triggerEntry);

	int status = luaL_dostring(_luaState, R"(package.path = package.path .. ";" .. "../script/mission/?.lua"  .. ";" .. "../?.lua")");
	if (status && !lua_isnil(_luaState, -1))
	{
		const char *msg = lua_tostring(_luaState, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		return false;
	}

	status = luaL_dofile(_luaState, "../script/mission/entry.lua");
	if (status && !lua_isnil(_luaState, -1))
	{
		const char *msg = lua_tostring(_luaState, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		return false;
	}
	return true;
}




void EventTrigger::trigger(EventTriggerEnum triggerID)
{
	int nargs = lua_gettop(_luaState);
	lua_pushcfunction(_luaState, pcall_error);
	for (auto ref : _watchings[triggerID])
	{
		lua_rawgeti(_luaState, LUA_REGISTRYINDEX, ref);
		if (lua_isnil(_luaState, -1))
		{
			LOGW("found not the watching reference function. refID=" << ref);
			lua_pop(_luaState, 1);
			continue;
		}
		for (int i = 1; i <= nargs; i++)
		{
			lua_pushvalue(_luaState, i);
		}
		lua_pcall(_luaState, nargs, 0, nargs + 1);
	}
}

