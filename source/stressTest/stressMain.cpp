/*
* breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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
#include <ProtoLogin.h>
#include <unordered_map>
extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lpack.h"
int luaopen_protoz_bit(lua_State *L);
}


#include <dbHelper.h>
#include "lua/summer.h"

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
#endif
// 	signal(SIGINT, &sigInt);
// 	signal(SIGTERM, &sigInt);

		
	ILog4zManager::getPtr()->config("log.config");
	ILog4zManager::getPtr()->start();
	ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);

    //parse config
    {
        
        std::string filename = "../serverConfig.xml";
        bool ret = false;
        ret = ServerConfig::getRef().parse(filename, StressNode, 0);
        if (!ret)
        {
            LOGE("parse ServerConfig failed.");
            return ret;
        }
        LOGI("parse ServerConfig success. configFile=" << filename << ", node=" << StressNode << ", index=" << 0);
        
    }
	// insert account
	{
        const auto authConfig = ServerConfig::getRef().getDBConfig(AuthDB);
		DBHelper helper;
		helper.init(authConfig._ip, authConfig._port, authConfig._db, authConfig._user, authConfig._pwd);
		if (helper.connect())
		{
			for (int i = 0; i < 1000; i++)
			{
				DBRequest req("insert ignore into tb_auth(`user`, passwd)values(?, ?)");
				char buf[100];
				sprintf(buf, "zhangyawei%04d", i);
				std::string str(buf);
				req.add(buf);
				req.add("123");
				DBResultPtr result = helper.query(req.genSQL());
				if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
				{
					LOGE("mysql querry error. the error=" << result->getLastError() << ", sql=" << req.genSQL());
					break;
				}
				if (result->getAffectedRows() == 0)
				{
					LOGW("mysql insert account not affect any rows. the user=" << buf);
					continue;
				}
			}

		}
	}

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
		luaopen_pack(L);
		luaopen_protoz_bit(L);

		lua_gc(L, LUA_GCRESTART, 0);
		status = luaL_dofile(L, "./main.lua");

		if (status && !lua_isnil(L, -1))
		{
			const char *msg = lua_tostring(L, -1);
			if (msg == NULL) msg = "(error object is not a string)";
			LOGE(msg);
			lua_pop(L, 1);
		}
		lua_close(L);
		return (status) ? EXIT_FAILURE : EXIT_SUCCESS;
	}

	return 0;
}

