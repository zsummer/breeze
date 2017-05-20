/*
* breeze License
* Copyright (C) 2014-2016 YaweiZhang <yawei.zhang@foxmail.com>.
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
#include "test.h"

#include "aoeTest.h"

#define TestUtls(func) do \
{ \
    LOGA("begin " << #func); \
    double now = getFloatNowTime(); \
    int ret = func(); \
    if (ret == 0) \
    { \
        LOGA("end " << #func << ", used second=" <<getFloatNowTime() - now); \
    } \
    else \
    { \
        LOGE("end " << #func << ", used second=" <<getFloatNowTime() - now << ", ret=" << ret); \
        return ret; \
    } \
} while (false)






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
    setenv("TZ", "GMT-8", 1);
#else
    //system("chcp 65001");
#endif
    srand((ui32)time(NULL));

    //AoeTest();
    ILog4zManager::getPtr()->start();
    SessionManager::getRef().start();

    

    checkBalance();
    auto ret =getHostByName("github.com", 3389);
    LOGA("getHostByName=" << ret);

    std::tuple<double, int, std::string> kvv = splitTupleString<double, int, std::string>("1.0:2:aha", ":", "");

    LOGA("1=" << std::get<0>(kvv) << ", 2=" << std::get<1>(kvv) << ", 3=" << std::get<2>(kvv));

    LOGI("0second" << formatDateTimeString(0));
    LOGI("now" << formatDateTimeString(getNowTime()));
    LOGA("version released by " << __DATE__ << " " << __TIME__);
    TestUtls(checkString);
    TestUtls(checkFile);
    TestUtls(checkFloat);
    TestUtls(checkBalance);
    TestUtls(checkRandom);
    TestUtls(checkTime);
    LOGA("check all success.");
    sleepMillisecond(3000);
    return 0;
}

