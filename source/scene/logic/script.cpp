#include "script.h"
#include "scene.h"
#include "sceneMgr.h"

static const char * SceneKey = "Scene";

static void * luaAllocFunc(void *ud, void *ptr, size_t osize, size_t nsize);
static int pcall_error(lua_State *L);

static void flushSceneToScript(Scene * scene, lua_State * L);
static void safeDoString(ScenePtr scene, lua_State * L, const std::string & lua);

static Scene* fetchScenePtr(lua_State * L);
static EntityPtr fetchEntityPtr(lua_State * L, Scene * scene, int pos);
static EPosition fetchEPosition(lua_State * L, int pos);
static EPositionArray fetchWaypoints(lua_State * L, int pos);
static void pushEPosition(lua_State * L, const EPosition& pos);
static void pushWaypoints(lua_State * L, const EPositionArray& ways);



static int lAddEntity(lua_State * L);
static int lRemoveEntity(lua_State * L);
static int lDoMove(lua_State * L);
static int lAddObstacle(lua_State * L);
static int lCleanObstacle(lua_State * L);
static int lProcessObstacle(lua_State * L);
static int lProcessObstacle(lua_State * L);
static int lWayFinding(lua_State * L);

static int lNow(lua_State * L)
{
    lua_pushnumber(L, getFloatSteadyNowTime());
    return 1;
}
static int lSysNow(lua_State * L)
{
    lua_pushnumber(L, getFloatNowTime());
    return 1;
}

static luaL_Reg SceneReg[] = {
    { "addEntity", lAddEntity },
    { "removeEntity", lRemoveEntity },
    { "doMove", lDoMove },
    { "addObstacle", lAddObstacle },
    { "cleanObstacle", lCleanObstacle },
    { "processObstacle", lProcessObstacle },
    { "wayFinding", lWayFinding },
    { "now", lNow },
    { "sysNow", lSysNow },
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

void Script::protoSync(const std::string & protoName, const char * data, unsigned int len)
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
    lua_pushlstring(_luaState, data, len);
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

    lua_pushnumber(L, PATH_PRECISION);
    lua_setfield(L, -2, "pathPrecision");

    lua_pop(L, 1);
}





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



static void safeDoString(ScenePtr scene, lua_State * L, const std::string & lua)
{
    int status = luaL_dostring(L, lua.c_str());
    if (status && !lua_isnil(L, -1))
    {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        LOGE("load scene script error. scene Type=" << (int)scene->getSceneType() << ", scene map id=" << scene->getMapID() << ", error=" << msg);
        lua_pop(L, 1);
    }
}

static Scene* fetchScenePtr(lua_State * L)
{
    int top = lua_gettop(L);
    lua_getglobal(L, SceneKey);
    Scene * scene = nullptr;
    if (!lua_istable(L, -1))
    {
        LOGE("fetchScenePtr error. not found " << SceneKey);
        lua_settop(L, top);
        return nullptr;
    }

    lua_getfield(L, -1, "__scene");
    if (!lua_islightuserdata(L, -1))
    {
        LOGE("fetchScenePtr error. not found " << SceneKey << ".__scene");
        lua_settop(L, top);
        return nullptr;
    }
    scene = (Scene*)lua_touserdata(L, -1);
    lua_settop(L, top);
    return scene;
}


static EntityPtr fetchEntityPtr(lua_State * L, Scene * scene, int pos)
{
    if (!lua_isnumber(L, pos))
    {
        return nullptr;
    }
    EntityID eid = (EntityID) luaL_checknumber(L, pos);
    return scene->getEntity(eid);
}

static EPosition fetchEPosition(lua_State * L, int pos)
{
    double x = 0;
    double y = 0;
    int top = lua_gettop(L);
    if (!lua_istable(L, pos))
    {
        return EPosition();
    }

    if (lua_geti(L, pos, 1) != LUA_TNUMBER)
    {
        lua_pop(L, 1);
        if (lua_getfield(L, pos, "x") != LUA_TNUMBER)
        {
            lua_pop(L, 1);
            return EPosition();
        }
    }
    x = luaL_checknumber(L, -1);
    lua_pop(L, 1);

    if (lua_geti(L, pos, 2) != LUA_TNUMBER)
    {
        lua_pop(L, 1);
        if (lua_getfield(L, pos, "y") != LUA_TNUMBER)
        {
            lua_pop(L, 1);
            return EPosition();
        }
    }
    y = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return EPosition(x, y);
}

static EPositionArray fetchWaypoints(lua_State * L, int pos)
{
    EPositionArray waypoints;
    if (!lua_istable(L, pos))
    {
        return waypoints;
    }

    lua_pushnil(L);
    while (lua_next(L, pos) != 0)
    {
        int ptpos = lua_gettop(L);
        if (lua_istable(L, ptpos))
        {
            waypoints.push_back(fetchEPosition(L, ptpos));
        }
        lua_pop(L, 1);
    }
    return waypoints;
}

static void pushEPosition(lua_State * L, const EPosition& pos)
{
    lua_newtable(L);
    lua_pushnumber(L, pos.x);
    lua_seti(L, -2, 1);
    lua_pushnumber(L, pos.y);
    lua_seti(L, -2, 2);
}
static void pushWaypoints(lua_State * L, const EPositionArray& ways)
{
    lua_newtable(L);
    for (size_t i = 0; i < ways.size(); i++)
    {
        pushEPosition(L, ways[i]);
        lua_seti(L, -2, i+1);
    }
}




static int lAddEntity(lua_State * L)
{
    if (lua_gettop(L) != 4)
    {
        LOGE("Script lAddEntity  lua_gettop(L)=" << lua_gettop(L));
        return 0;
    }
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lAddEntity fetchScenePtr error");
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
        ReadStream rs(propData, (zsummer::proto4z::Integer)propLen, false);
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
        ReadStream rs(stateData, (zsummer::proto4z::Integer)stateLen, false);
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
        ReadStream rs(skillData, (zsummer::proto4z::Integer)skillLen, false);
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
        ReadStream rs(ctlData, (zsummer::proto4z::Integer)ctlLen, false);
        rs >> ctls;
    }
    catch (const std::exception & e)
    {
        LOGE("Script lAddEntity EntityControl except error. e=" << e.what());
        return 0;
    }





    LOGD("from script addEntity. state=" << state);

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
    entity->_control.stateChageTime = getFloatSteadyNowTime();

    scene->addEntity(entity);
    lua_pushnumber(L, (lua_Number)entity->_state.eid);
    return 1;
}



static int lRemoveEntity(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        LOGE("Script lRemoteEntity  lua_gettop(L)=" << lua_gettop(L));
        return 0;
    }
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lRemoveEntity fetchScenePtr error");
        return 0;
    }


    EntityID eid = (EntityID)luaL_checknumber(L, 1);

    bool ret = scene->removeEntity(eid);
    lua_pushboolean(L, ret ? 1 : 0);
    return 1;
}

static int lDoMove(lua_State * L)
{
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lDoMove fetchScenePtr error");
        return 0;
    }

    int top = lua_gettop(L);

    unsigned short  action;
    double speed;
    ui64 follow;
    EPositionArray waypoints;
    action = (unsigned short)luaL_checknumber(L, 2);
    auto entity = fetchEntityPtr(L, scene, 1);
    if (!entity)
    {
        LOGE("Script lDoMove  not found entity ");
        return 0;
    }


    if (top == 4)
    {
        speed = entity->getSpeed();
        follow = (ui64)luaL_checknumber(L, 3);
        waypoints = fetchWaypoints(L, 4);
    }
    else if (top == 5)
    {
        speed = luaL_checknumber(L, 3);
        follow = (ui64)luaL_checknumber(L, 4);
        waypoints = fetchWaypoints(L, 5);
    }
    else
    {
        LOGE("Script lDoMove  lua_gettop(L)=" << lua_gettop(L));
        return 0;
    }
    scene->_move->doMove(entity->_state.eid, (MOVE_ACTION)action, speed, follow, waypoints);
    lua_pushboolean(L, 1);
    return 1;
}

static int lAddObstacle(lua_State * L)
{
    if (lua_gettop(L) != 1)
    {
        LOGE("Script lAddObstacle  lua_gettop(L)=" << lua_gettop(L));
        return 0;
    }
    if (!lua_istable(L, 1))
    {
        LOGE("Script lAddObstacle param error.");
        return 0;
    }
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lDoMove fetchScenePtr error");
        return 0;
    }
    auto waypoints = fetchWaypoints(L, 1);
    std::vector<RVO::Vector2> obs;
    for (auto & pt : waypoints)
    {
        obs.push_back(toRVOVector2(pt));
    }
    scene->_move->addObstacle(obs);
    return 0;
}

static int lCleanObstacle(lua_State * L)
{
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lDoMove fetchScenePtr error");
        return 0;
    }
    scene->_move->cleanObstacle();
    scene->_move->processObstacles();
    return 0;
}
static int lProcessObstacle(lua_State * L)
{
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lDoMove fetchScenePtr error");
        return 0;
    }
    scene->_move->processObstacles();
    return 0;
}

static int lWayFinding(lua_State * L)
{
    Scene * scene = fetchScenePtr(L);
    if (!scene)
    {
        LOGE("lWayFinding fetchScenePtr error");
        return 0;
    }

    if (!lua_istable(L, 1))
    {
        LOGE("lWayFinding not found org pos");
        return 0;
    }
    if (!lua_istable(L, 2))
    {
        LOGE("lWayFinding not found waypoints");
        return 0;
    }
    EPosition org = fetchEPosition(L, 1);
    EPositionArray ways = fetchWaypoints(L, 2);
    if (ways.empty())
    {
        LOGE("lWayFinding waypoints empty.");
        return 0;
    }
    EPositionArray fdways;
    if (ways.size() == 1)
    {
        fdways = ways;
    }
    else
    {
        double dist = 1E100;
        EPosition fwp;
        size_t index = 0;
        for (size_t i = 0; i< ways.size() -1; i++)
        {
            EPosition spt = toEPosition(shortestLine(ways[i].x, ways[i].y, ways[i + 1].x, ways[i + 1].y, org.x, org.y));
            double sdist = getDistance(spt, org);
            if (sdist < dist)
            {
                fwp = spt;
                dist = sdist;
                index = i;
            }
        }
        if (getDistance(ways[index+1], fwp) > 1)
        {
            fdways.push_back(fwp);
        }
        for (size_t i = index+1; i < ways.size(); i++)
        {
            fdways.push_back(ways[i]);
        }
    }
    pushWaypoints(L, fdways);
    return 1;
}




