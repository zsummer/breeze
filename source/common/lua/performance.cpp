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


#include "performance.h"

static void hook_run_fn(lua_State *L, lua_Debug *ar);

static int newindex(lua_State * L)
{
    lua_pushvalue(L, 1);
    lua_pushvalue(L, 2);
    lua_pushvalue(L, 3);
    lua_rawset(L, 4);
    lua_pop(L, 1);
    const char * key = luaL_checkstring(L, 2);
    const char * v = luaL_typename(L, 3);
    std::stringstream ss;
    ss << "catch one operation that it's set a global value. key=" << key << ", type(v)=" << v << ", is it correct ?";
    if (lua_getglobal(L, "summer") == LUA_TTABLE && lua_getfield(L, -1, "logw") == LUA_TFUNCTION)
    {
        lua_pushstring(L, ss.str().c_str());
        lua_pcall(L, 1, 0, 0);
    }
    else if (lua_getglobal(L, "print") == LUA_TFUNCTION)
    {
        lua_pushstring(L, ss.str().c_str());
        lua_pcall(L, 1, 0, 0);
    }
    lua_pop(L, lua_gettop(L) - 3);
    
    return 0;
}


zsummer::Performence __perf;
void luaopen_performence(lua_State * L)
{
    //lua_Hook oldhook = lua_gethook(L);
    //int oldmask = lua_gethookmask(L);
    lua_sethook(L, &hook_run_fn, LUA_MASKCALL | LUA_MASKRET, 0);
    lua_getglobal(L, "_G");
    lua_newtable(L);
    lua_pushcclosure(L, newindex, 0);
    lua_setfield(L, -2, "__newindex");
    lua_setmetatable(L, -2);
}

void hook_run_fn(lua_State *L, lua_Debug *ar)
{
    // 获取Lua调用信息
    lua_getinfo(L, "Snl", ar);
    std::string key;
    if (ar->source)
    {
        key += ar->source;
    }
    key += "_";
    if (ar->what)
    {
        key += ar->what;
    }
    key += "_";
    if (ar->namewhat)
    {
        key += ar->namewhat;
    }
    key += "_";
    if (ar->name)
    {
        key += ar->name;
    }
    if (ar->event == LUA_HOOKCALL)
    {
        __perf._stack.push(key, lua_gc(L, LUA_GCCOUNT, 0) * 1024 + lua_gc(L, LUA_GCCOUNTB, 0));
    }
    else if (ar->event == LUA_HOOKRET)
    {
        //lua_gc(L, LUA_GCCOLLECT, 0);
        auto t = __perf._stack.pop(key, lua_gc(L, LUA_GCCOUNT, 0) * 1024 + lua_gc(L, LUA_GCCOUNTB, 0));
        if (std::get<0>(t))
        {
            __perf.call(key, std::get<1>(t), std::get<2>(t));
        }
        if (__perf.expire(10000.0))
        {
            __perf.dump(100);
        }
    }
}

