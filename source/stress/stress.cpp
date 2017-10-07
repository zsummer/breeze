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


//! 测试

#include <common.h>





using namespace zsummer::log4z;
using namespace zsummer::mysql;



int main(int argc, char* argv[])
{

#ifndef _WIN32
    //! linux下需要屏蔽的一些信号
    signal( SIGHUP, SIG_IGN );
    signal( SIGALRM, SIG_IGN ); 
    signal( SIGPIPE, SIG_IGN );
    signal( SIGXCPU, SIG_IGN );
    signal( SIGXFSZ, SIG_IGN );
    signal( SIGPROF, SIG_IGN ); 
    signal( SIGVTALRM, SIG_IGN );
    signal( SIGQUIT, SIG_IGN );
    signal( SIGCHLD, SIG_IGN);
    //setenv("TZ", "GMT-8", 1);
#else
    //system("chcp 65001");
#endif
//    signal(SIGINT, &sigFun);
//    signal(SIGTERM, &sigFun);

    srand((ui32)time(NULL));
    ILog4zManager::getPtr()->config("../log.cfg");
    ILog4zManager::getPtr()->start();
    ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);

    // lua script
    {
        int status;
        lua_State *L = luaL_newstate();  /* create state */
        if (L == NULL)
        {
            return EXIT_FAILURE;
        }

        lua_gc(L, LUA_GCSTOP, 0);  /* stop collector during initialization */
        luaL_openlibs(L);  /* open libraries */
        luaopen_summer(L);
        luaopen_proto4z_util(L);
        luaopen_cjson(L);
        lua_gc(L, LUA_GCRESTART, 0);

        lua_getglobal(L, "summer");
        lua_getfield(L, -1, "logd");
        lua_setglobal(L, "logd");
        lua_getfield(L, -1, "logi");
        lua_setglobal(L, "logi");
        lua_getfield(L, -1, "logw");
        lua_setglobal(L, "logw");
        lua_getfield(L, -1, "loge");
        lua_setglobal(L, "loge");
        lua_getfield(L, -1, "logi");
        lua_setglobal(L, "print");
        lua_pop(L, 1);

        //luaopen_performence(L);

        status = luaL_dostring(L, R"(package.path = package.path .. ";" .. "../?.lua" .. ";" .. "../script/stress/?.lua" .. ";" .. "../../protocol/lua/?.lua" )");
        if (status && !lua_isnil(L, -1))
        {
            const char *msg = lua_tostring(L, -1);
            if (msg == NULL) msg = "(error object is not a string)";
            LOGE(msg);
        }
        status = luaL_dofile(L, "../script/stress/main.lua");
        if (status && !lua_isnil(L, -1))
        {
            const char *msg = lua_tostring(L, -1);
            if (msg == NULL) msg = "(error object is not a string)";
            LOGE(msg);
            lua_pop(L, 1);
        }
        lua_close(L);
        getchar();
        return (status) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    return 0;
}

