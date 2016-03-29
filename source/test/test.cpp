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
int checkRandom();


#define TestUtls(func) do \
{ \
    LOGA("begin " << #func); \
    double now = getTick(); \
    int ret = func(); \
    if (ret == 0) \
    { \
        LOGA("end " << #func << ", used second=" <<getTick() - now); \
    } \
    else \
    { \
        LOGE("end " << #func << ", used second=" <<getTick() - now << ", ret=" << ret); \
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
    
    ILog4zManager::getPtr()->start();
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



int checkString()
{
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
    if (!compareStringWildcard("", ""))
    {
        return 17;
    }
    if (!compareStringWildcard("", "*"))
    {
        return 18;
    }
    if (!compareStringWildcard("afda*fa", "*"))
    {
        return 19;
    }
    if (!compareStringWildcard("a---bc-e-bc-----------e", "a*bc***e*e"))
    {
        return 21;
    }
    if (compareStringWildcard("a---bc-e-bc-----------e-", "a*bc***e*e"))
    {
        return 22;
    }
    if (true)
    {
        double now = getTick();
        volatile int f = 0.0;
        for (int i = 0; i < 10 * 10000; i++)
        {
            f = compareStringWildcard("a---bc-e-bc-----------e", "a*bc***e*e");
        }
        f = 0.0;
        LOGD("compareStringWildcard used time=" << (getTick() - now) << f);
    }

    if (subStringFront("aa/bb/cc", "/") != "aa")
    {
        return 25;
    }
    if (subStringBack("aa/bb/cc", "/") != "cc")
    {
        return 26;
    }
    if (subStringWithoutFront("aa/bb/cc", "/") != "bb/cc")
    {
        return 27;
    }
    if (subStringWithoutBack("aa/bb/cc", "/") != "aa/bb")
    {
        return 28;
    }


    return 0;
}

int checkFile()
{
    std::string content = "1234567890";
    std::string path = "./log2/log3/";
    std::string filename = "aaaa";
    std::string md5 = "e807f1fcf82d132f9bb018ca6738a19F";
    if (isDirectory(path))
    {
        return 1;
    }
    if (!createDirectory(path))
    {
        return 2;
    }
    if (!isDirectory(path))
    {
        return 3;
    }
    writeFileContent(path + filename, content.c_str(), content.length(), false);
    if (!hadFile(path + filename))
    {
        return 4;
    }
    
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
        return 5;
    }

    if (!compareStringIgnCase(toUpperString(genFileMD5(path + filename)), toLowerString(md5)))
    {
        return 6;
    }
    if (!removeFile(path + filename))
    {
        return 7;
    }
    if (!removeDir(path))
    {
        return 8;
    }
    if (hadFile(path + filename))
    {
        return 9;
    }
    
    return 0;
}

int checkTime()
{
    getLocalDay(0);
    double now = getTick();
    double snow = getSteadyTick();
    long long nowt = getMSecTick();
    long long nowst = getSteadyMSecTick();
    time_t nowts = getNowTime();
    sleepMillisecond(3000);
    now = getTick() - now - 3.0;
    snow = getSteadyTick() - snow - 3.0;
    nowt = getMSecTick() - nowt - 3000;
    nowst = getSteadyMSecTick() - nowst - 3000;
    nowts = getNowTime() - nowts -3;
    if (now > 1 || snow > 1 || nowt >1000 || nowst >1000 || nowts > 1)
    {
        LOGE("now =" << now << ", snow=" << snow << ", nowt=" << nowt << ", nowst=" << nowst << ", nowts=" << nowts);
        return 1;
    }
    LOGI(formatDateString(getNowTime()) << " " << formatTimeString(getNowTime()));
    LOGI(formatDateTimeString(getNowTime()));

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
    if (getLocalDay(1451577599, 0) == getLocalDay(1451577600, 0))
    {
        return 6;
    }
    if (getLocalDayByReadable(1451577599, 0) == getLocalDayByReadable(1451577600, 0))
    {
        return 7;
    }
    if (getUTCTimeFromLocalString("2015/12/31 23:59:59") != 1451577599)
    {
        return 8;
    }
    if (getUTCTimeFromLocalString("     31-12-2015    23:59        ") != 1451577599 - 59)
    {
        return 9;
    }
    if (getUTCTimeFromLocalString("12-2015    23:59") != 1451577599 - (31-1)*24*3600 - 59)
    {
        return 10;
    }
    if (getUTCTimeFromLocalString("20151231") != 1451577599 -  24 * 3600 + 1)
    {
        return 10;
    }
    if (!isSameDay(getUTCTimeFromLocalString(toString<time_t>(getLocalDayByReadable(1451577599, 0))), 1451577599))
    {
        return 11;
    }
    //hypothesis server is GMT+9, unknown client time area, utc second is 1451577599, in client get server's localtime.
    if (gettm(1451577599 + (9 * 3600 - getTZZoneOffset())).tm_hour != 0)
    {
        return 12;
    }
    if (getSecondFromTimeString("1:2:3") != 1*3600 + 2*60 + 3)
    {
        return 15;
    }
    if (true)
    {
        int bit = 0;
        bit = appendBitFlag(bit, 1);
        bit = appendBitFlag(bit, 2);
        if (!checkBitFlag(bit, 1))
        {
            return 16;
        }
        bit = removeBitFlag(bit, 1);
        if (checkBitFlag(bit, 1))
        {
            return 17;
        }
        if (!checkBitFlag(bit, 2))
        {
            return 18;
        }
        bit = removeBitFlag(bit, 2);
        if (bit != 0)
        {
            return 19;
        }
        
    }
    if (pruning(1, 2,3) != 2)
    {
        return 19;
    }
    if (pruning(4, 2, 3) != 3)
    {
        return 20;
    }
    if (true)
    {
        time_t now = getUTCTime();
        time_t scd = getDaySecond(now);
        tm ts = gettm(now);
        if (scd != ts.tm_hour * 3600 + ts.tm_min*60 + ts.tm_sec)
        {
            return 21;
        }
    }

    return 0;
}

int checkFloat()
{
    if (isZero(POINT_DOUBLE))
    {
        return 1;
    }
    if (!isZero(0.0))
    {
        return 2;
    }
    if(isZero(POINT_DOUBLE*1.00000000001))
    {
        return 3;
    }
    if (isZero(POINT_DOUBLE*-1.00000000001))
    {
        return 4;
    }
    if (!isZero(POINT_DOUBLE * 0.999999999))
    {
        return 5;
    }
    if (!isZero(POINT_DOUBLE * -0.999999999))
    {
        return 6;
    }
    if (!isEqual(0.0, 0.0))
    {
        return 7;
    }
    if (isEqual(0.0, POINT_DOUBLE))
    {
        return 8;
    }
    if (isEqual(0.0, POINT_DOUBLE*0.999999))
    {
        return 9;
    }
    if (isEqual(0.0, POINT_DOUBLE*-0.999999))
    {
        return 10;
    }

    if (!isEqual(POINT_DOUBLE, POINT_DOUBLE))
    {
        return 11;
    }


    if (isEqual(POINT_DOUBLE*1E55, POINT_DOUBLE*1E55 + POINT_DOUBLE*1E55*POINT_DOUBLE*1.1))
    {
        return 12;
    }
    if (!isEqual(POINT_DOUBLE*1E55, POINT_DOUBLE*1E55 + (POINT_DOUBLE*1E55*POINT_DOUBLE)*0.99999))
    {
        return 13;
    }
    if (isEqual(POINT_DOUBLE*1E-55, POINT_DOUBLE*1E-55 + POINT_DOUBLE*1E-55*POINT_DOUBLE*1.1))
    {
        return 14;
    }
    if (!isEqual(POINT_DOUBLE*1E-55, POINT_DOUBLE*1E-55 - (POINT_DOUBLE*1E-55*POINT_DOUBLE)*0.99999))
    {
        return 15;
    }
    if (!isEqual(getDistance(1.0, -1.0), 2.0))
    {
        return 16;
    }
    if (!isEqual(getDistance(1.0, 0.0, 2.0, 0.0), 1.0))
    {
        return 17;
    }
    if (!isEqual(getRadian(0.0, 0.0, 1.0, 0.0), 0.0))
    {
        return 18;
    }
    if (!isEqual(getRadian(0.0, 0.0, -1.0, 0.0), PI))
    {
        return 19;
    }
    if (!isEqual(std::get<1>(getFarPoint(0.0, 0.0, PI/2.0*3.0, 1.0)), -1.0))
    {
        return 20;
    }
    if (!isEqual(std::get<1>(getFarOffset(0.0, 0.0, 0.0, -2.0, 1.0)), -1.0))
    {
        return 21;
    }
    if (!isEqual(std::get<1>(getFarOffset(0.0, 0.0, 0.0, 2.0, 1.0)), 1.0))
    {
        return 22;
    }
    if (!isEqual(std::get<0>(rotatePoint(0.0, 0.0, PI/2.0, 1.0, PI/2.0)), -1.0))
    {
        return 25;
    }
    if (!isEqual(std::get<1>(rotatePoint(0.0, 0.0, PI / 2.0, 1.0, PI)), -1.0))
    {
        return 26;
    }

    if (true)
    {
        double now = getTick();
        volatile double f = 0.0;
        for (int i = 0; i < 100 * 10000; i++)
        {
            f = isEqual(1e55, 1e55);
        }
        f = 0.0;
        LOGD("isEqual used time=" << (getTick() - now) << f);
    }
    

    return 0;
}


int checkBalance()
{
    Balance balance;
    balance.enableNode(1);
    balance.enableNode(2);
    balance.enableNode(3);
    for (unsigned i = 0; i <6 ; ++i)
    {
        if(balance.selectAuto() != i%3+1)
        {
            return 1;
        }
    }
    for (unsigned i = 0; i<6; ++i)
    {
        if(balance.selectManual() != i%3+1)
        {
            return 2; //select light when lost weight
        }
        balance.changeWeight(i%3+1, 5);
    }
    balance.disableNode(3);
    for (unsigned i = 0; i < 6; ++i)
    {
        if(balance.selectAuto() != i%2+1)
        {
            return 3;
        }
    }
    for (unsigned i = 0; i < 6; ++i)
    {
        if(balance.selectManual() != i%2+1)
        {
            return 4;
        }
        balance.changeWeight(i%2+1, 5);
    }
    balance.enableNode(4);
    for (unsigned i = 0; i < 3; ++i)
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
    return 0;
}

int checkRandom()
{
    for (int i = 0; i < 10000; i++)
    {
        unsigned int rr = realRand(1000, 2000);
        if (rr < 1000 || rr > 2000)
        {
            return 1;
        }
        double rrf = realRandF(100.234, 200.999);
        if (rrf < 100.234 || rrf > 200.999)
        {
            return 2;
        }
        continue;
    }
    std::vector<int> cards;
    for (int i = 100; i > 0; i--)
    {
        cards.push_back(i);
    }
    if (true)
    {
        int loopCount = 1*10000;
        double sumRaffle = 0.0;
        double sumRaffleWeight = 0.0;
        for (int i = 0; i < loopCount; i++)
        {
            auto ret = raffle(cards.begin(), cards.end(), 10);
            for (auto v : ret)
            {
                if (*v == 100)
                {
                    sumRaffle += 1.0;
                    break;
                }
            }
            ret = raffle(cards.begin(), cards.end(), 10, [](std::vector<int>::iterator iter){return *iter; });
            for (auto v : ret)
            {
                if (*v == 100)
                {
                    sumRaffleWeight += 1.0;
                    break;
                }
            }
        }
        if (fabs(sumRaffle - loopCount* (1.0 / 100.0) * 10.0) > loopCount* (1.0 / 100.0) * 10.0)
        {
            return 3;
        }
        if (fabs(sumRaffleWeight - loopCount *(100.0 / 5050.0) * 10.0) > loopCount *(100.0 / 5050.0) * 10.0)
        {
            return 4;
        }
        if (raffle(cards.begin(), cards.end(), 101).size() != 100)
        {
            return 5;
        }
        if (raffle(cards.begin(), cards.end(), 101, [](std::vector<int>::iterator iter){return *iter; }).size() != 100)
        {
            return 6;
        }
        if (raffle(cards.begin(), cards.end(), 101, [](std::vector<int>::iterator iter){return 0; }).size() != 100)
        {
            return 7;
        }
        if (raffle(cards.end(), cards.end(), 101, [](std::vector<int>::iterator iter){return 0; }).size() != 0)
        {
            return 8;
        }
        if (raffle(cards.end(), cards.end(), 101).size() != 0)
        {
            return 9;
        }

    }

    return 0;
}



