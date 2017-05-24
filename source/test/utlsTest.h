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



inline int checkString()
{
    std::string t1 = "%^&123^=&";
    auto ret = splitString<std::string>(t1, "=", "&%^");
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
    if (splitString<std::string>("==", "==", "adf123").size() != 2)
    {
        return 4;
    }
    if (true)
    {
        std::vector<int> array = { 1,2,3,4 };
        std::string dstString = mergeToString(array, ",");
        if (dstString.length() != 7)
        {
            return 5;
        }
        dstString.clear();
        for (auto i : array)
        {
            mergeToString(dstString, ",", i);
        }
        if (dstString.length() != 7)
        {
            return 6;
        }

         auto now = getFloatNowTime();
         for (int i=0; i<10000; i++)
         {
             auto v = splitDictString<int, short, float, std::string>("1|2|3|a,|||,2|2|3|a,|||,3|2|3|a,|||,4|2|3|a,|||,5|2|3|a,|||,6|2|3|a,|||,7|2|3|a,|||,8|2|3|a,|||,8|2|3|a,|||,", ",", "|", " ");
             std::get<0>(v.begin()->second) = 0;
         }
         LOGA("splitDictString used time=" << getFloatNowTime() - now);

    }

    
    if (!compareStringIgnCase("Fad123123", "fAd123123"))
    {
        return 7;
    }
    if (compareStringIgnCase("1234", "123", true))
    {
        return 8;
    }
    if (!compareStringIgnCase("a123", "A1234", true))
    {
        return 9;
    }
    if (compareStringIgnCase("a123", "A1234", false))
    {
        return 10;
    }
    if (strcmp(toUpperString("aaaa").c_str(), "AAAA") != 0)
    {
        return 11;
    }
    if (strcmp(toLowerString("AAAA").c_str(), "aaaa") != 0)
    {
        return 12;
    }
    if (!isEqual(fromString<float>("0.1", 0.0), 0.1, 1e-5))
    {
        return 13;
    }
    if (!isEqual(fromString<double>("1e-1", 0.0), 0.1))
    {
        return 14;
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
        double now = getFloatNowTime();
        for (int i = 0; i < 10 * 10000; i++)
        {
            if (fromString<unsigned long long>("18446744073709551615", 0) != 18446744073709551615U)
            {
                return 16;
            }
            if (fromString<long long>("-8446744073709551615", 0) != -8446744073709551615L)
            {
                return 16;
            }
        }
        LOGD("fromString used time=" << (getFloatNowTime() - now));
        for (int i = 0; i < 10 * 10000; i++)
        {

        }
        LOGD("toString used time=" << (getFloatNowTime() - now));

    }
    if (true)
    {
        double now = getFloatNowTime();
        for (int i = 0; i < 10 * 10000; i++)
        {
            compareStringWildcard("a---bc-e-bc-----------e", "a*bc***e*e");
        }
        LOGD("compareStringWildcard used time=" << (getFloatNowTime() - now));
    }

    if (subString("aa/bb/cc", "/").first != "aa")
    {
        return 25;
    }
    if (subString("aa/bb/cc", "/", true, true).second != "cc")
    {
        return 26;
    }
    if (subString("aa/bb/cc", "/").second != "bb/cc")
    {
        return 27;
    }
    if (subString("aa/bb/cc", "/", true, true).first != "aa/bb")
    {
        return 28;
    }

    if (subString("aa", "/", false).second != "aa")
    {
        return 29;
    }
    if (subString("aa", "/", true).first != "aa")
    {
        return 30;
    }


    if (true)
    {
        //蓝天and҉😌   
        char org[] = { (char)0xe8,  (char)0x93,  (char)0x9d,    (char)0xe5,  (char)0xa4,  (char)0xa9,    (char)0x61,  (char)0x6e,  (char)0x64,    (char)0xd2,  (char)0x89,    (char)0xf0, (char)0x9f, (char)0x98, (char)0x8c,   (char)0x00 };
        if (getCharUTF8Count(org) != 7)
        {
            return 31;
        }
        if (getCharASCIICount(org) != 3)
        {
            return 32;
        }
        if (getCharNoASCIICount(org) != 4)
        {
            return 33;
        }
        if (!hadIllegalChar(org))
        {
            return 34;
        }

    }

    return 0;
}

inline int checkFile()
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
    if (!accessFile(path + filename))
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
    if (accessFile(path + filename))
    {
        return 9;
    }
    
    return 0;
}

inline int checkTime()
{
    double now = getFloatNowTime();
    double snow = getFloatSteadyNowTime();
    long long nowt = getNowTick();
    long long nowst = getNowSteadyTick();
    time_t nowts = getNowTime();
    sleepMillisecond(3000);
    now = getFloatNowTime() - now - 3.0;
    snow = getFloatSteadyNowTime() - snow - 3.0;
    nowt = getNowTick() - nowt - 3000;
    nowst = getNowSteadyTick() - nowst - 3000;
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
    if (distanceDays(1451577599, 1451577599+1) != 1)
    {
        return 6;
    }
    if (distanceDays(1451577599, 1451577599 + 1+24*3600) != 2)
    {
        return 7;
    }
    if (distanceDays(1451577599, 1451577599 +1 - 24 * 3600) != 0)
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
        bit = setBitFlag(bit, 1);
        bit = setBitFlag(bit, 2);
        if (!getBitFlag(bit, 1))
        {
            return 16;
        }
        bit = setBitFlag(bit, 1, false);
        if (getBitFlag(bit, 1))
        {
            return 17;
        }
        if (!getBitFlag(bit, 2))
        {
            return 18;
        }
        bit = setBitFlag(bit, 2, false);
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

inline int checkFloat()
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
    if (!isEqual(getRadian(1.0, 0.0), 0.0))
    {
        return 18;
    }
    if (!isEqual(getRadian(-1.0, 0.0), PI))
    {
        return 19;
    }
    if (!isEqual(std::get<1>(getFarPoint(0.0, 0.0, PI/2.0*3.0, 1.0)), -1.0))
    {
        return 20;
    }
    if (!isEqual(calcELORatingUpper(1500, 1800, 1), 1527, 1E0))
    {
        return 21;
    }
    if (det(1,0, 0, 1) <= 0)
    {
        return 22;
    }
    if (det(1, 0, 0, -1) >= 0)
    {
        return 23;
    }
    if (!isEqual(det(1, 0, 1, 0)+1 , 1, 1E-10))
    {
        return 24;
    }
    if (!isEqual(dot(1, 0, 0, 1) + 1, 1, 1E-10))
    {
        return 25;
    }
    if (dot(1, 0, 1, 1) <= 0 )
    {
        return 26;
    }
    if (dot(1, 0, -1, 1) >= 0)
    {
        return 27;
    }

    if (true)
    {
        double vx, vy, s;
        for (int i=0; i<10000; i++)
        {
            if (i < 1000)
            {
                vx = rand() % 2 - 1;
                vy = rand() % 2 - 1;
            }
            else
            {
                vx = rand() % 200 - 100;
                vy = rand() % 200 - 100;
            }

            auto ret = rotateVertical(vx, vy, true);
            if (i%2 == 0)
            {
                ret = rotateVertical(vx, vy, false);
            }
            ret = normalize(std::get<0>(ret), std::get<1>(ret));
            s = std::get<0>(ret)*vx + std::get<1>(ret)*vy;
            if (s < -1E-12 || s > 1E-12)
            {
                LOGE("radian = " << getRadian(vx, vy) / PI / 2 * 360 << ", ret = " << getRadian(std::get<0>(ret), std::get<1>(ret)) / PI / 2 * 360 );
                return 28;
            }
            if (s > 0 && s < 0)
            {
                return 29;
            }
        }
    }
    if (true)
    {
        double now = getFloatNowTime();
        volatile double f = 0.0;
        for (int i = 0; i < 100 * 10000; i++)
        {
            f = isEqual(1e55, 1e55);
        }
        f = 0.0;
        LOGD("isEqual used time=" << (getFloatNowTime() - now) << f);
    }

    if (true)
    {
        double owner = 2500;
        double dst = 2500;
        for (int i = 0; i < 10; i++)
        {
            double newOwner = owner + calcELORatingUpper(owner, dst, 1);
            double newDst = dst + calcELORatingUpper(dst, owner, -1);
            LOGD("owner[" << newOwner << ":" << 1.0 - (newOwner - owner) / 32 << "] , dst[" << newDst << ":" <<  (newDst - dst) / -32 << "]");
            owner = newOwner;
            dst = newDst;
        }
    }



    return 0;
}


inline int checkBalance()
{
    Balance<ui32> balance;
    balance.enableNode(1);
    balance.enableNode(2);
    balance.enableNode(3);
    for (unsigned i = 0; i < 12 ; ++i)
    {
        balance.pickNode(1, 1);
    }
    if (balance.getBalanceDeviation() > 1+1)
    {
        return 1;
    }
    for (unsigned i = 0; i < 20000; ++i)
    {
        balance.pickNode(50, 1);
    }
    if (balance.getBalanceDeviation() > 50 + 1)
    {
        return 2;
    }
    balance.disableNode(3);
    balance.enableNode(4);
    for (unsigned i = 0; i < 20000; ++i)
    {
        balance.pickNode(50, 1);
    }
    if (balance.getBalanceDeviation() > 50 + 1)
    {
        return 3;
    }

    for (unsigned i = 0; i < 20000; ++i)
    {
        balance.pickNode(1, 1);
    }
    if (balance.getBalanceDeviation() > 1 + 1)
    {
        return 4;
    }
   
    LOGD( balance.getBalanceStatus());
    return 0;
}

inline int checkRandom()
{
    if (true)
    {
        int sum1 = 0;
        int sum50 = 0;
        int sum100 = 0;
        int loop = 10000 * 10;
        for (int i = 0; i < loop; i++)
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
            unsigned int rd = realRand(1, 100);
            if (rd == 1)
            {
                sum1++;
            }
            if (rd == 50)
            {
                sum50++;
            }
            if (rd == 100)
            {
                sum100++;
            }
        }
        LOGD("realRand 1-100.  1=" << sum1 << ", 50=" << sum50 << ", sum100=" << sum100);
        if (abs(sum1 - loop/100) > loop/100*20/100 || abs(sum50 - loop / 100) > loop / 100 * 20 / 100 || abs(sum100 - loop / 100) > loop / 100 * 20 / 100 )
        {
            return 2;
        }


    }

    std::vector<int> cards;
    if (true)
    {
        cards.push_back(100);
        cards.push_back(200);
        auto ret = raffle(cards.begin(), cards.end(), 2, false, [](std::vector<int>::iterator iter) {return *iter; });
        if (ret.size() != 2)
        {
            return 3;
        }
        ret = raffle(cards.begin(), cards.end(), 2, true, [](std::vector<int>::iterator iter) {return *iter; });
        if (ret.size() != 2 || ret.front() == ret.back())
        {
            return 4;
        }

        ret = raffle(cards.begin(), cards.end(), 3, false, [](std::vector<int>::iterator iter) {return *iter; });
        if (ret.size() != 3)
        {
            return 5;
        }
        ret = raffle(cards.begin(), cards.end(), 3, true, [](std::vector<int>::iterator iter) {return *iter; });
        if (ret.size() != 2)
        {
            return 6;
        }
        //weight is 0
        ret = raffle(cards.begin(), cards.end(), 3, false, [](std::vector<int>::iterator iter) {return 0; });
        if (ret.size() != 0)
        {
            return 7;
        }
        //pound is empty
        ret = raffle(cards.end(), cards.end(), 3, false, [](std::vector<int>::iterator iter) {return *iter; });
        if (ret.size() != 0)
        {
            return 8;
        }
        ret = raffle(cards.begin(), cards.end(), 3, true, [](std::vector<int>::iterator iter) {return 0; });
        if (ret.size() != 0)
        {
            return 9;
        }
        //pound is empty
        ret = raffle(cards.end(), cards.end(), 3, true, [](std::vector<int>::iterator iter) {return *iter; });
        if (ret.size() != 0)
        {
            return 10;
        }
    }
    cards.clear();
    for (int i = 100; i > 0; i--)
    {
        cards.push_back(i);
    }
    if (true)
    {
        int loopCount = 1*10000;
        int takeCount = 10;
        double sumRaffle = 0.0;// sumRaffle ≈ (1/100)*loopCount*10
        double sumRaffleWeight = 0.0; //sumRaffleWeight ≈ (100/5050)*loopCount*10
        for (int i = 0; i < loopCount; i++)
        {
            auto ret = raffle(cards.begin(), cards.end(), takeCount, false);
            for (auto v : ret)
            {
                if (*v == 100)
                {
                    sumRaffle += 1.0;
                    break;
                }
            }
            ret = raffle(cards.begin(), cards.end(), takeCount, false, [](std::vector<int>::iterator iter){return *iter; });
            for (auto v : ret)
            {
                if (*v == 100)
                {
                    sumRaffleWeight += 1.0;
                    break;
                }
            }
        }
        auto diff = fabs(sumRaffle - loopCount* (1.0 / 100.0)*takeCount);
        auto target = loopCount* (1.0 / 100.0)*takeCount * 0.2;
        LOGD("diff=" << diff << ", target=" << target);
        if (fabs(sumRaffle - loopCount* (1.0 / 100.0)*takeCount) > loopCount* (1.0 / 100.0)*takeCount * 0.2)
        {
            return 11;
        }
        diff = fabs(sumRaffleWeight - loopCount* (100.0 / 5050.0)*takeCount);
        target = loopCount* (1.0 / 5050.0)*takeCount * 0.2;
        LOGD("diff=" << diff << ", target=" << target);
        if (fabs(sumRaffleWeight - loopCount *(100.0 / 5050.0)*takeCount) > loopCount *(100.0 / 5050.0)*takeCount * 0.2)
        {
            return 12;
        }


    }


    if (true)
    {
        std::vector<std::pair<int, double>> cards;
        for (int i=1; i<=100; i++)
        {
            cards.push_back(std::make_pair(i, i / 100.0));
        }
        int loop = 10000;
        int takeCount = 10;
        int sum1 = 0;   //sum 1 ≈ 0.01 * 10000*10
        int sum50 = 0;   //sum 50 ≈ 0.5*10000*10
        int sum100 = 0;  //sum 100 = 10000*10
        for (int i=0; i<loop; i++)
        {
            auto ret = raffle(cards.begin(), cards.end(), takeCount, 
                [](std::vector<std::pair<int, double>>::iterator iter) {return iter->second; });
            for (auto iter : ret)
            {
                if (iter->first == 1)
                {
                    sum1++;
                }
                else if (iter->first == 50)
                {
                    sum50++;
                }
                else if (iter->first == 100)
                {
                    sum100++;
                }
            }
            
        }
        LOGD("sum1=" << sum1 << ", sum50=" << sum50 << ", sum100=" << sum100);
        if (sum100 != loop*takeCount)
        {
            return 20;
        }
        if (abs(sum1 - loop*takeCount/100) > (loop*takeCount/100*20/100))
        {
            return 21;
        }
        if (abs(sum50 - loop*takeCount / 2) > (loop*takeCount / 2 * 20 / 100))
        {
            return 22;
        }
    }
    return 0;
}



