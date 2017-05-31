#include "script.h"
#include "scene.h"
#include "sceneMgr.h"


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

static int l(lua_State * L)
{

    return 0;
}

static luaL_Reg summer[] = {
    { "l", l },
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
    lua_setglobal(_luaState, "Scene");
    lua_gc(_luaState, LUA_GCRESTART, 0);
}


void Script::update()
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
    }

}
