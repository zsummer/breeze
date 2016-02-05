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

#include <common.h>
#include <utls.h>
#include <balance.h>
using namespace zsummer::log4z;
using namespace zsummer::mysql;

int checkString();
int checkFile();
int checkTime();
int checkFloat();
int checkBalance();
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
    
    ILog4zManager::getPtr()->start();
    LOGI("0second" << getDateTimeString(24*3600));
    LOGI("now" << getDateTimeString(getCurTime()));
    LOGA("version released by " << __DATE__ << " " << __TIME__);

    int ret = checkString();
    if (ret != 0)
    {
        return ret;
    }
    ret = checkFile();
    if (ret != 0)
    {
        return ret;
    }
    ret = checkTime();
    if (ret != 0)
    {
        return ret;
    }
    ret = checkFloat();
    if (ret != 0)
    {
        return ret;
    }
    ret = checkString();
    if (ret != 0)
    {
        return ret;
    }
    ret = checkBalance();
    if( ret != 0 )
    {
        return ret;
    }

    LOGA("check all success.");
    sleepMillisecond(3000);
    return 0;
}



int checkString()
{
    LOGA("begin check trim, splitString, toUpperString,toLowerString,compareStringIgnCase");
    std::string t1 = "%^&123^=&";
    auto ret = splitString(t1, "=", "&%^");
    if (ret.size() != 2)
    {
        return 1;
    }
    if (ret.front() != "123")
    {
        return 2;
    }
    if (!ret.back().empty())
    {
        return 3;
    }
    if (splitString("==", "==", "adf123").size() != 2)
    {
        return 4;
    }
    if (!compareStringIgnCase("Fad123123", "fAd123123"))
    {
        return 5;
    }
    if (compareStringIgnCase("1234", "123", true))
    {
        return 6;
    }
    if (!compareStringIgnCase("a123", "A1234", true))
    {
        return 7;
    }
    if (compareStringIgnCase("a123", "A1234", false))
    {
        return 8;
    }
    if (strcmp(toUpperString("aaaa").c_str(), "AAAA") != 0)
    {
        return 9;
    }
    if (strcmp(toLowerString("AAAA").c_str(), "aaaa") != 0)
    {
        return 10;
    }
    if (!isEqual(fromString<float>("0.1", 0.0), 0.1, 1e-5))
    {
        return 11;
    }
    if (!isEqual(fromString<double>("1e-1", 0.0), 0.1))
    {
        return 12;
    }
    if (fromString<int>("-1", 0) != -1)
    {
        return 15;
    }
    if (fromString<unsigned long long>("18446744073709551615", 0) != 18446744073709551615U)
    {
        return 16;
    }
    LOGA("end check trim, splitString, toUpperString,toLowerString,compareStringIgnCase");
    return 0;
}

int checkFile()
{
    LOGA("begin check readFileContent, writeFileContent, isDirectory, createRecursionDir, MD5Data genMD5,genFileMD5");
    std::string content = "1234567890";
    std::string path = "./log2/log3/";
    std::string filename = "aaaa";
    std::string md5 = "e807f1fcf82d132f9bb018ca6738a19F";
    if (isDirectory(path))
    {
        return 1;
    }
    if (!createRecursionDir(path))
    {
        return 2;
    }
    if (!isDirectory(path))
    {
        return 3;
    }
    writeFileContent(path + filename, content.c_str(), content.length(), false);
    content.clear();
    size_t lastSize = 0;
    do
    {
        std::string str = readFileContent(path + filename, true, 4, lastSize);
        lastSize += str.length();
        content += str;
        if (str.length() < 4)
        {
            break;
        }

    } while (true);


    MD5Data d;
    d << content;
    std::string mmd5 = d.genMD5();
    if (!compareStringIgnCase(toUpperString(mmd5), toLowerString(md5)))
    {
        return 4;
    }

    if (!compareStringIgnCase(toUpperString(genFileMD5(path + filename)), toLowerString(md5)))
    {
        return 5;
    }
    if (!removeFile(path + filename))
    {
        return 6;
    }
    if (!removeDir(path))
    {
        return 7;
    }
    LOGA("end check readFileContent, writeFileContent, isDirectory, createRecursionDir, MD5Data genMD5,genFileMD5");
    return 0;
}

int checkTime()
{
    LOGA("begin check Time");

    getCurDay();
    double now = getNow();
    double snow = getSteadyNow();
    long long nowt = getNowTick();
    long long nowst = getSteadyNowTick();
    time_t nowts = getCurTime();
    sleepMillisecond(3000);
    now = getNow() - now - 3.0;
    snow = getSteadyNow() - snow - 3.0;
    nowt = getNowTick() - nowt - 3000;
    nowst = getSteadyNowTick() - nowst - 3000;
    nowts = getCurTime() - nowts -3;
    if (now > 1 || snow > 1 || nowt >1000 || nowst >1000 || nowts > 1)
    {
        LOGE("now =" << now << ", snow=" << snow << ", nowt=" << nowt << ", nowst=" << nowst << ", nowts=" << nowts);
        return 1;
    }
    LOGI(getDateString(getCurTime()) << " " << getTimeString(getCurTime()));
    LOGI(getDateTimeString(getCurTime()));

    //2015周四/2016周五
    time_t dt2015 = 1451577599;
    time_t dt2016 = 1451577600;
    if (isSameDay(dt2015, dt2016) || isSameMonth(dt2015, dt2016)
        || isSameYear(dt2015, dt2016))
    {
        return 2;
    }
    if (!isSameDay(dt2015, dt2016, -1) || !isSameMonth(dt2015, dt2016, -1)
        || !isSameYear(dt2015, dt2016, -1))
    {
        return 3;
    }
    if (!isSameWeak(dt2015, dt2016) || isSameWeak(dt2015+3*24*3600, dt2016 + 3*24+3600))
    {
        return 4;
    }
    if (!isSameWeak(dt2015+3*24*3600+1, dt2015+3*24*3600+3))
    {
        return 5;
    }
    if (getDay(1451577599) == getDay(1451577600))
    {
        return 6;
    }
    
    LOGA("end check Time");
    return 0;
}

int checkFloat()
{
    LOGA("begin check float");
    if(isZero(POINT_DOUBLE*2))
    {
        return 1;
    }
    if (!isZero(POINT_DOUBLE / -10.0))
    {
        return 2;
    }
    if (!isZero(POINT_DOUBLE / 10.0))
    {
        return 3;
    }
    if (!isEqual(1.0 + POINT_DOUBLE, 1.0 + POINT_DOUBLE/2.0))
    {
        return 4;
    }
    if (isEqual(1.0 + POINT_DOUBLE*2, 1.0))
    {
        return 5;
    }
    if (!isEqual(getDistance(1.0, -1.0), 2.0))
    {
        return 6;
    }
    if (!isEqual(getDistance(1.0, 0.0, 2.0, 0.0), 1.0))
    {
        return 7;
    }
    if (!isEqual(getRadian(0.0, 0.0, 1.0, 0.0), 0.0))
    {
        return 8;
    }
    if (!isEqual(getRadian(0.0, 0.0, -1.0, 0.0), PI))
    {
        return 9;
    }
    if (!isEqual(std::get<1>(getFarPoint(0.0, 0.0, PI/2.0*3.0, 1.0)), -1.0))
    {
        return 10;
    }
    if (!isEqual(std::get<1>(getFarOffset(0.0, 0.0, 0.0, -2.0, 1.0)), -1.0))
    {
        return 11;
    }
    if (!isEqual(std::get<1>(getFarOffset(0.0, 0.0, 0.0, 2.0, 1.0)), 1.0))
    {
        return 12;
    }
    if (!isEqual(std::get<0>(rotatePoint(0.0, 0.0, PI/2.0, 1.0, PI/2.0)), -1.0))
    {
        return 15;
    }
    if (!isEqual(std::get<1>(rotatePoint(0.0, 0.0, PI / 2.0, 1.0, PI)), -1.0))
    {
        return 16;
    }

    LOGA("end check float");
    return 0;
}


int checkBalance()
{
    LOGA("begin check balance");
    Balance balance;
    balance.enableNode(1);
    balance.enableNode(2);
    balance.enableNode(3);
    for (int i = 0; i <6 ; ++i)
    {
        if(balance.selectAuto() != i%3+1)
        {
            return 1;
        }
    }
    for (int i=0; i<6; ++i)
    {
        if(balance.selectManual() != i%3+1)
        {
            return 2; //select light when lost weight
        }
        balance.changeWeight(i%3+1, 5);
    }
    balance.disableNode(3);
    for (int i = 0; i < 6; ++i)
    {
        if(balance.selectAuto() != i%2+1)
        {
            return 3;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        if(balance.selectManual() != i%2+1)
        {
            return 4;
        }
        balance.changeWeight(i%2+1, 5);
    }
    balance.enableNode(4);
    for (int i = 0; i < 3; ++i)
    {
        if(balance.selectAuto() != 4)
        {
            return 5;
        }
        if(balance.selectManual() != 4)
        {
            return 6;
        }
        balance.changeWeight(4, 1);
    }
    LOGD("rate=" << balance.getBalanceRate() << ", status=" << balance.getBalanceStatus());
    LOGA("end check balance");
    return 0;
}





