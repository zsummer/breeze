

/*
* breeze License
* Copyright (C) 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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



#ifndef _UTLS_IMPL_H_
#define _UTLS_IMPL_H_



//string
template<class T>
std::string toString(const T &t)
{
    std::stringstream os;
    os << t;
    return os.str();
}


template<class RET>
RET fromString(const std::string & t, RET def)
{
    if (t.empty()) return def;
    if (typeid(RET) == typeid(float) || typeid(RET) == typeid(double))
    {
        return (RET)atof(t.c_str());
    }
    else if (typeid(RET) == typeid(unsigned long long))
    {

        char *cursor = nullptr;
        return (RET)strtoull(t.c_str(), &cursor, 10);
//        unsigned long long ull = 0;
//#ifndef WIN32
//        sscanf(t.c_str(), "%llu", &ull);
//#else
//        int count = sscanf(t.c_str(), "%I64u", &ull);
//#endif
//        return (RET)ull;
    }
    return (RET)atoll(t.c_str());
}

inline double getTick()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch()).count();
}
inline double getSteadyTick()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline long long getMSecTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline long long getSteadyMSecTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline time_t getUTCTime()
{
    return time(NULL);
}
inline time_t getTZZoneOffset()
{
    time_t fixday = 7 * 24 * 3600;
    tm tm = gettm(fixday);
    return ((tm.tm_mday - 1) * 24 + tm.tm_hour) * 3600 - fixday;
}
inline time_t getLocalDay(time_t t, time_t offset)
{
    time_t fix = getTZZoneOffset();
    return (t + fix + offset) / 24 / 3600;
}
inline time_t getLocalDay(time_t offset)
{
    return getLocalDay(getUTCTime(), offset);
}
inline time_t getDaySecond(time_t t)
{
    return (t + getTZZoneOffset()) % (24 * 3600);
}
inline time_t getLocalDayByReadable(time_t t, time_t offset)
{
    tm st = gettm(t);
    return (st.tm_year + 1900) * 10000 + (st.tm_mon + 1) * 100 + st.tm_mday;
}
inline time_t getLocalDayByReadable(time_t offset)
{
    return getLocalDayByReadable(getUTCTime(), offset);
}
//safe method for get tm from unix timestamp
// 
// struct tm {
//             int tm_sec;    /* Seconds (0-60) */
//             int tm_min;    /* Minutes (0-59) */
//             int tm_hour;   /* Hours (0-23) */
//             int tm_mday;   /* Day of the month (1-31) */
//             int tm_mon;    /* Month (0-11) */
//             int tm_year;   /* Year - 1900 */
//             int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
//             int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
//             int tm_isdst;  /* Daylight saving time */
//            };
// 
inline tm gettm(time_t ts)
{
    tm * tstm = localtime(&ts);
    if (!tstm)
    {
        ts = 0;
        tstm = localtime(&ts);
    }
    return *tstm;
}

inline std::string formatDateString(time_t ts)
{
    tm tstm = gettm(ts);
    char buff[50];
    sprintf(buff, "%04d-%02d-%02d", tstm.tm_year + 1900, tstm.tm_mon + 1, tstm.tm_mday);
    return buff;
}
inline std::string formatTimeString(time_t ts)
{
    tm tstm = gettm(ts);
    char buff[50];
    sprintf(buff, "%02d:%02d:%02d", tstm.tm_hour, tstm.tm_min, tstm.tm_sec);
    return buff;
}
inline std::string formatDateTimeString(time_t ts)
{
    tm tstm = gettm(ts);
    char buff[50];
    sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d",
        tstm.tm_year + 1900, tstm.tm_mon + 1, tstm.tm_mday,
        tstm.tm_hour, tstm.tm_min, tstm.tm_sec);
    return buff;
}

inline bool isSameYear(time_t first, time_t second, time_t offset)
{
    return gettm(first + offset).tm_year == gettm(second + offset).tm_year;
}
inline bool isSameMonth(time_t first, time_t second, time_t offset)
{
    tm ftm = gettm(first + offset);
    tm stm = gettm(second + offset);
    return ftm.tm_year == stm.tm_year && ftm.tm_mon == stm.tm_mon;
}
inline bool isSameWeak(time_t first, time_t second, time_t offset)
{
    tm ftm = gettm(first + offset);
    time_t begin = first + offset - (ftm.tm_wday * 24 * 3600) - ftm.tm_hour * 3600 - ftm.tm_min * 60 - ftm.tm_sec;
    return second + offset >= begin && second + offset < begin + 7 * 24 * 3600;
}
// example: if 03:00::00 is the day bound you can set offset = -3*3600
inline bool isSameDay(time_t first, time_t second, time_t offset)
{
    tm ftm = gettm(first + offset);
    tm stm = gettm(second + offset);
    return ftm.tm_year == stm.tm_year && ftm.tm_yday == stm.tm_yday;
}





inline bool isZero(double f, double acc)
{
    return fabs(f) < acc;
}

using std::max;
using std::min;
inline bool isEqual(double f1, double f2, double acc)
{
    return fabs(f1 - f2) <= max(fabs(f1), fabs(f2)) * acc;
}


inline double getDistance(double org, double dst)
{
    return fabs(org - dst);
}

inline double getDistance(double orgx, double orgy, double dstx, double dsty)
{
    return sqrt(pow(orgx - dstx, 2) + pow(orgy - dsty, 2));
}


inline double getRadian(double orgx, double orgy, double dstx, double dsty)
{
    double disx = dstx - orgx;
    double disy = dsty - orgy;
    double h = getDistance(orgx, orgy, dstx, dsty);
    if (h == 0)
    {
        h = 1;
    }
    double rad = acos(disx / h);
    if (disy < 0)
    {
        rad = PI * 2.0f - rad;
    }
    return rad;
}

inline std::tuple<double, double> getFarPoint(double orgx, double orgy, double radian, double distance)
{
    return std::make_tuple(orgx + cos(radian) * distance, orgy + sin(radian) * distance);
}

inline std::tuple<double, double> getFarOffset(double orgx, double orgy, double dstx, double dsty, double distance)
{
    double rate = distance / getDistance(orgx, orgy, dstx, dsty);
    return std::make_tuple(orgx + (dstx - orgx) * rate, orgy + (dsty - orgy) * rate);
}



inline std::tuple<double, double> rotatePoint(double orgx, double orgy, double orgrad, double distance, double radian)
{
    return std::make_tuple(orgx + cos(orgrad + radian)*distance, orgy + sin(orgrad + radian)*distance);
}




template<class Integer, class Number>
inline bool checkBitFlag(Integer n, Number f)
{
    return (n & ((Integer)1 << (f - 1))) != 0;
}

template<class Integer, class Number>
inline Integer appendBitFlag(Integer n, Number f)
{
    return n | ((Integer)1 << (f - 1));
}

template<class Integer, class Number>
inline Integer removeBitFlag(Integer n, Number f)
{
    return n & ~((Integer)1 << (f - 1));
}



//integer
//==========================================================================
//return value is [min, max]
template<class T>
inline T pruning(T v, T min, T max)
{
    return v < min ? min : (v > max ? max : v);
}


template<class RandIt>
inline void randomShuffle(RandIt first, RandIt end)
{
    std::random_shuffle(first, end);
}

template<class RandIt>
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount)
{
    std::vector<RandIt> temp;
    temp.reserve(128);
    if (true)
    {
        auto cur = first;
        while (cur != end)
        {
            temp.push_back(cur);
            cur++;
        }
    }
    randomShuffle(temp.begin(), temp.end());
    while (temp.size() > (size_t)takeCount)
    {
        temp.pop_back();
    }
    return std::move(temp);
}

template<class RandIt, class GetWeightFunc> 
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount, GetWeightFunc getWeight)
{
    std::vector<std::pair<RandIt, int> > temp;
    temp.reserve(128);
    int sumWeight = 0;
    if (true)
    {
        auto cur = first;
        while (cur != end)
        {
            int curWeight = getWeight(cur);
            curWeight = curWeight >= 0 ? curWeight : 0;
            sumWeight += curWeight;
            temp.push_back(std::make_pair(cur, curWeight));
            cur++;
        }
    }
    std::vector<RandIt> ret;
    while (ret.size() < (size_t)takeCount && ret.size() < temp.size())
    {
        int rd = realRand() % (sumWeight+1);
        int curWeight = 0;
        for (auto &v: temp)
        {
            if (v.second < 0)
            {
                continue;
            }
            curWeight += v.second;
            if (rd <= curWeight)
            {
                ret.push_back(v.first);
                sumWeight -= v.second;
                v.second = -1;
                break;
            }
        }
    }
    return std::move(ret);
}






#endif