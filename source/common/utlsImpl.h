

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

inline double getNow()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch()).count();
}
inline double getSteadyNow()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline long long getNowTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline long long getSteadyNowTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline time_t getTimestampNow()
{
    return time(NULL);
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
inline tm getTimestampStruct(time_t ts)
{
    tm * tstm = localtime(&ts);
    if (!tstm)
    {
        ts = 0;
        tstm = localtime(&ts);
    }
    return *tstm;
}

inline std::string getDateString(time_t ts)
{
    tm tstm = getTimestampStruct(ts);
    char buff[50];
    sprintf(buff, "%04d-%02d-%02d", tstm.tm_year + 1900, tstm.tm_mon + 1, tstm.tm_mday);
    return buff;
}
inline std::string getTimeString(time_t ts)
{
    tm tstm = getTimestampStruct(ts);
    char buff[50];
    sprintf(buff, "%02d:%02d:%02d", tstm.tm_hour, tstm.tm_min, tstm.tm_sec);
    return buff;
}
inline std::string getDateTimeString(time_t ts)
{
    tm tstm = getTimestampStruct(ts);
    char buff[50];
    sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d",
        tstm.tm_year + 1900, tstm.tm_mon + 1, tstm.tm_mday,
        tstm.tm_hour, tstm.tm_min, tstm.tm_sec);
    return buff;
}
inline bool isSameYear(time_t first, time_t second, time_t offset)
{
    return getTimestampStruct(first + offset).tm_year == getTimestampStruct(second + offset).tm_year;
}
inline bool isSameMonth(time_t first, time_t second, time_t offset)
{
    tm ftm = getTimestampStruct(first + offset);
    tm stm = getTimestampStruct(second + offset);
    return ftm.tm_year == stm.tm_year && ftm.tm_mon == stm.tm_mon;
}
inline bool isSameWeak(time_t first, time_t second, time_t offset)
{
    tm ftm = getTimestampStruct(first + offset);
    time_t begin = first + offset - (ftm.tm_wday * 24 * 3600) - ftm.tm_hour * 3600 - ftm.tm_min * 60 - ftm.tm_sec;
    return second + offset >= begin && second + offset < begin + 7 * 24 * 3600;
}
// example: if 03:00::00 is the day bound you can set offset = -3*3600
inline bool isSameDay(time_t first, time_t second, time_t offset)
{
    tm ftm = getTimestampStruct(first + offset);
    tm stm = getTimestampStruct(second + offset);
    return ftm.tm_year == stm.tm_year && ftm.tm_yday == stm.tm_yday;
}





inline bool isZero(double f, double acc)
{
    return fabs(f) <= acc;
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















#endif