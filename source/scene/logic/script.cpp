#include "script.h"
#include "scene.h"
#include "sceneMgr.h"

static const char * SceneKey = "Scene";

static void * luaAllocFunc(void *ud, void *ptr, size_t osize, size_t nsize)
{
    SceneID id = (SceneID)ud;
    if (nsize == 0)
    {
        free(ptr);
        return NULL;
    }
    return realloc(ptr, nsize);
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


static void flushSceneToScript(Scene * scene, lua_State * L);
static void safeDoString(ScenePtr scene, lua_State * L, const std::string & lua)
{
    int status = luaL_dostring(L, lua.c_str());
    if (status && !lua_isnil(L, -1))
    {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGW("load scene script error. scene Type=" << (int)scene->getSceneType() << ", scene map id=" << scene->getMapID() << ", error=" << msg);
        lua_pop(L, 1);
    }
}


static int lAddEntity(lua_State * L)
{
	if (lua_gettop(L) != 4)
	{
		LOGE("Script lAddEntity  lua_gettop(L)=" << lua_gettop(L));
		return 0;
	}


    size_t propLen = 0;
    const char * propData = luaL_checklstring(L, 1, &propLen);
    if (!propData)
    {
        return 0;
    }

    size_t stateLen = 0;
    const char * stateData = luaL_checklstring(L, 2, &stateLen);
    if (!stateData)
    {
        return 0;
    }

    size_t skillLen = 0;
    const char * skillData = luaL_checklstring(L, 3, &skillLen);
    if (!skillData)
    {
        return 0;
    }

    size_t ctlLen = 0;
    const char * ctlData = luaL_checklstring(L, 4, &ctlLen);
    if (!ctlData)
    {
        return 0;
    }

    DictProp prop;
    try
    {
        ReadStream rs(propData, propLen, false);
        rs >> prop;
    }
    catch (const std::exception & e)
    {
        LOGE("Script lAddEntity  DictProp except error. e=" << e.what());
        return 0;
    }

    EntityState state;
    try
    {
        ReadStream rs(stateData, stateLen, false);
        rs >> state;
    }
    catch (const std::exception & e)
    {
        LOGE("Script lAddEntity  EntityState except error. e=" << e.what());
        return 0;
    }


    EntitySkillSystem skills;
    try
    {
        ReadStream rs(skillData, skillLen, false);
        rs >> skills;
    }
    catch (const std::exception & e)
    {
        LOGE("Script lAddEntity EntitySkillSystem except error. e=" << e.what());
        return 0;
    }

    EntityControl ctls;
    try
    {
        ReadStream rs(ctlData, ctlLen, false);
        rs >> ctls;
    }
    catch (const std::exception & e)
    {
        LOGE("Script lAddEntity EntityControl except error. e=" << e.what());
        return 0;
    }

	lua_getglobal(L, SceneKey);
	Scene * scene = nullptr;
    if (!lua_istable(L, -1))
    {
        LOGE("Script not found Scene class.");
        return 0;
    }

    lua_getfield(L, -1, "__scene");
    if (!lua_islightuserdata(L, -1))
    {
        LOGE(SceneKey << ".__scene not userdata");
        return 0;
    }
    scene = (Scene*)lua_touserdata(L, -1);

    EntityPtr entity = scene->makeEntity(state.modelID, state.avatarID, state.avatarName, {}, InvalidGroupID);
    entity->_props = prop;
    entity->_skillSys = skills;
    entity->_state = state;
    entity->_control = ctls;

    entity->_state.eid = entity->_report.eid;
    entity->_state.maxHP = entity->_props.hp;
    entity->_state.curHP = entity->_state.maxHP;


    entity->_skillSys.eid = entity->_report.eid;
    entity->_control.eid = entity->_report.eid;


    entity->_move.position = entity->_control.spawnpoint;
    entity->_control.agentNo = RVO::RVO_ERROR;

    scene->addEntity(entity);
    lua_pushnumber(L, entity->_state.eid);
	return 1;
}



static int lRemoveEntity(lua_State * L)
{
	if (lua_gettop(L) != 1)
	{
		LOGE("Script lRemoteEntity  lua_gettop(L)=" << lua_gettop(L));
		return 0;
	}
	EntityID eid = (EntityID)luaL_checknumber(L, 1);
	lua_getglobal(L, SceneKey);
	Scene * scene = nullptr;
	if (!lua_istable(L, -1))
	{
		LOGE("Script lRemoteEntity  not found Scene class.");
		return 0;
	}

	lua_getfield(L, -1, "__scene");
	if (!lua_islightuserdata(L, -1))
	{
		LOGE(SceneKey << "lRemoteEntity __scene not userdata");
		return 0;
	}
	scene = (Scene*)lua_touserdata(L, -1);
	bool ret = scene->removeEntity(eid);
	lua_pushboolean(L, ret ? 1 : 0);
	return 1;
}

static int lDoMove(lua_State * L)
{
	ui64 eid;
	unsigned short  action;
	double speed;
	ui64 follow;
	EPositionArray dsts;
	if (lua_gettop(L) == 4)
	{
		eid = (ui64)luaL_checknumber(L, 1);
		action = (unsigned short)luaL_checknumber(L, 2);
		speed = luaL_checknumber(L, 3);
		follow = (ui64)luaL_checknumber(L, 4);
		if (lua_istable(L, 5))
		{

		}
	}
	else if (lua_gettop(L) == 5)
	{
		eid = (ui64)luaL_checknumber(L, 1);
		action = (unsigned short)luaL_checknumber(L, 2);
		speed = luaL_checknumber(L, 3);
		follow = (ui64)luaL_checknumber(L, 4);
		if (lua_istable(L, 5))
		{

		}
	}
	else 
	{
		LOGE("Script lDoMove  lua_gettop(L)=" << lua_gettop(L));
		return 0;
	}


	lua_getglobal(L, SceneKey);
	Scene * scene = nullptr;
	if (!lua_istable(L, -1))
	{
		LOGE("Script lRemoteEntity  not found Scene class.");
		return 0;
	}

	lua_getfield(L, -1, "__scene");
	if (!lua_islightuserdata(L, -1))
	{
		LOGE(SceneKey << "lRemoteEntity __scene not userdata");
		return 0;
	}
	scene = (Scene*)lua_touserdata(L, -1);

	return 1;
}


static luaL_Reg SceneReg[] = {
	{ "addEntity", lAddEntity },
	{ "removeEntity", lRemoveEntity },
	{ "doMove", lDoMove },
	{ NULL, NULL }
};




Script::Script()
{

}
Script::~Script()
{
    if (_luaState)
    {
        lua_close(_luaState);
        _luaState = nullptr;
    }
    
}


void Script::init(std::weak_ptr<Scene> scene)
{
    _scene = scene;
    ScenePtr s = scene.lock();
    if (_luaState)
    {
        lua_close(_luaState);
        _luaState = nullptr;
    }
    _luaState = lua_newstate(luaAllocFunc, (void*)s.get());
    if (_luaState == NULL)
    {
        LOGF("lua_newstate error.");
        return;
    }
    lua_gc(_luaState, LUA_GCSTOP, 0);  /* stop collector during initialization */
    luaL_openlibs(_luaState);  /* open libraries */
    lua_newtable(_luaState);
    lua_setglobal(_luaState, "Proto4z");
    luaopen_summer(_luaState);
    luaopen_proto4z_util(_luaState);
    lua_newtable(_luaState);
    for (luaL_Reg *l = SceneReg; l->name != NULL; l++) {
        lua_pushcclosure(_luaState, l->func, 0);  
        lua_setfield(_luaState, -2, l->name);
    }
    lua_setglobal(_luaState, SceneKey);
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

	safeDoString(s, _luaState, R"(package.path = package.path .. ";" .. "../?.lua"  )");
	safeDoString(s, _luaState, R"(package.path = package.path .. ";" .. "../script/scene/?.lua"  )");
	safeDoString(s, _luaState, R"(package.path = package.path .. ";" .. "../../protocol/lua/?.lua" )");
	safeDoString(s, _luaState, R"(package.path = package.path .. ";" .. "../../depends/include/proto4z/?.lua" )");

    flushSceneToScript(s.get(), _luaState);

    std::string sceneScript = "require 'scene_" + toString((int)s->getSceneType()) + "_" + toString(s->getMapID()) + "'";
    safeDoString(s, _luaState, sceneScript);
}


void Script::update()
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
    }
    if (!_luaState)
    {
        return;
    }

    lua_settop(_luaState, 0);
    flushSceneToScript(scene.get(), _luaState);
    

    lua_pushcfunction(_luaState, pcall_error);
    lua_getglobal(_luaState, "onUpdate");
    if (!lua_isfunction(_luaState, 1))
    {
        LOGW("Script::update scene[" << scene->getSceneID() << "] not found script onUpdate type=" 
            << (int)scene->getSceneType() << ", mapID=" << scene->getMapID());
        return;
    }
    int status = lua_pcall(_luaState, 0, 0, 1);
    lua_remove(_luaState, 1);
    if (status)
    {
        const char *msg = lua_tostring(_luaState, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGE(msg);
        lua_pop(_luaState, 1);
    }
}

void Script::protoSync(const std::string & protoName, const std::string & data)
{
	auto scene = _scene.lock();
	if (!scene)
	{
		return;
	}
	if (!_luaState)
	{
		return;
	}

	lua_settop(_luaState, 0);
	flushSceneToScript(scene.get(), _luaState);


	lua_pushcfunction(_luaState, pcall_error);
	if (lua_getglobal(_luaState, "onSyncEntry") != LUA_TFUNCTION)
	{
		LOGW("Script::protoSync scene[" << scene->getSceneID() << "] not found onSyncEntry type="
			<< (int)scene->getSceneType() << ", mapID=" << scene->getMapID());
		return;
	}

	lua_pushstring(_luaState, protoName.c_str());
	lua_pushlstring(_luaState, data.c_str(), data.size());
	int status = lua_pcall(_luaState, 2, 0, 1);
    lua_remove(_luaState, 1);
    if (status)
	{
		const char *msg = lua_tostring(_luaState, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		lua_pop(_luaState, 1);
	}

}






void flushSceneToScript(Scene * scene, lua_State * L)
{
    lua_getglobal(L, SceneKey);
    if (!lua_istable(L, -1))
    {
        LOGE("Script not found Scene");
        lua_settop(L, 0);
        return;
    }

    lua_pushlightuserdata(L, scene);
    lua_setfield(L, -2, "__scene");

    lua_pushinteger(L, scene->getSceneID());
    lua_setfield(L, -2, "sceneID");

    lua_pushinteger(L, scene->getMapID());
    lua_setfield(L, -2, "mapID");

    lua_pushinteger(L, scene->getSceneType());
    lua_setfield(L, -2, "sceneType");

    lua_pop(L, 1);
}










