
/*
* breeze License
* Copyright (C) 2014 YaweiZhang <yawei.zhang@foxmail.com>.
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

#include <common.h>
using namespace zsummer::log4z;




void sigInt(int sig);


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
    //system("chcp 65001"); //需要配合设置显示用的字体为TrueType字体 
#endif


    std::string filename = "../config.lua";

    if (argc > 1)
    {
        filename = argv[1];
    }

    if (!ILog4zManager::getPtr()->start())
    {
        std::cout << "ILog4zManager start false." << std::endl;
        return 1;
    }
    LOGA("version released by " << __DATE__ << " " << __TIME__);
    //LOGD("filecontent=" << readFileContent(filename));
    
    if (!ServerConfig::getRef().parseDB(filename))
    {
        LOGE("parse db config error. config path=" << filename);
        return 2;
    }
    if (!DBDict::getRef().buildDictTable())
    {
        LOGE("buildDictTable error. config path=" << filename);
        return 3;
    }
    if (!DBDict::getRef().buildInfoTable())
    {
        LOGE("buildInfoTable error. config path=" << filename);
        return 4;
    }
    if (!DBDict::getRef().buildLogTable())
    {
        LOGE("buildLogTable error. config path=" << filename);
        return 5;
    }

    return 0;
}

