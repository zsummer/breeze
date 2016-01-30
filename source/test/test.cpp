/*
* breeze License
* Copyright (C) 2014-2015 YaweiZhang <yawei.zhang@foxmail.com>.
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
#include <utls.h>
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

    ILog4zManager::getPtr()->start();
    
    //test trim, split
    if (true)
    {
        LOGA("begin check trim, split");
        std::string t1 = "%^&123^=&";
        auto ret = splitString(t1, "=", "&%^");
        if (ret.size() != 2)
        {
            return -1;
        }
        if (ret.front() != "123")
        {
            return -1;
        }
        if (!ret.back().empty())
        {
            return -1;
        }
        if (splitString("==", "==", "adf123").size() != 2)
        {
            return -1;
        }
        LOGA("end check trim, split");
    }
    if (true)
    {
        LOGA("begin check file, md5, upper, lower, compareigncase");
        std::string content = "1234567890";
        std::string md5 = "e807f1fcf82d132f9bb018ca6738a19F";
        writeFileContent("./aaaa", content.c_str(), content.length(), false);
        content.clear();
        size_t lastSize = 0;
        do 
        {
            std::string str = readFileContent("./aaaa", true, 4, lastSize);
            lastSize += str.length();
            content += str;
            if (str.length() < 4)
            {
                break;
            }
            
        } while (true);

        
        if (true)
        {
            MD5Data d;
            d << content;
            std::string mmd5 = d.genMD5();
            if (!compareStringIgnCase(toUpperString(mmd5), toLowerString(md5)))
            {
                return -1;
            }
        }
        if (!compareStringIgnCase(toUpperString(genFileMD5("./aaaa")), toLowerString(md5)))
        {
            return -1;
        }
        LOGA("end check file, md5, upper, lower, compareigncase");
        
    }
    
    sleepMillisecond(3000);
    LOGA("check all success.");
    return 0;
}

