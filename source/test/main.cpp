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

int screenX = 50;
int screenY = 50;

//! 测试
#include "utlsTest.h"

#include "aoeViewer.h"
#include "vectorViewer.h"
#include "arith_prime.h"
#include "arith_gray_code.h"
#include "arith_sort.h"

void TestUtls(std::function<int(void)> fun, std::string name)
{
    LOG_STREAM(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_ALARM, nullptr, 0, "");
    LOGA("begin test ----[" << name << "]----"); 
    double now = getFloatNowTime();
    int ret = fun();
    if (ret == 0)
    {
        LOGA("end test ----[" << name << "](0)----" << " used second=" << getFloatNowTime() - now);
    }
    else
    {
        LOGE("end test ----[" << name << "](" << ret << ")----" << " used second=" << getFloatNowTime() - now );
        exit(ret);
    }
}




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

    //AoeViewer();
    //vectorViewer();
    ILog4zManager::getPtr()->start();
    SessionManager::getRef().start();

    LOGA("version released by " << __DATE__ << " " << __TIME__);

    arith_prime();
    arith_gray_code();
    arith_sort();
    TestUtls(checkOther, "checkOther");
    TestUtls(checkString, "checkString");
    TestUtls(checkFile, "checkFile");
    TestUtls(checkFloat, "checkFloat");
    TestUtls(checkBalance, "checkBalance");
    TestUtls(checkRandom, "checkRandom");
    TestUtls(checkTime, "checkTime");
    LOGA("check all success.");
    sleepMillisecond(3000);
    return 0;
}

