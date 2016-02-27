

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




#ifndef _UTLS_H_
#define _UTLS_H_

#include <defined.h>
#include <single.h>

//file
//==========================================================================
//isBinary if false it's will auto fix UTF-8 BOM. only this.
std::string readFileContent(const std::string & filename, bool isBinary = false, size_t limitSize = 1024 * 1024, size_t beginIndex = 0);
size_t writeFileContent(const std::string & filename, const char * buff, size_t buffLen, bool isAppend = true);
bool isDirectory(const std::string & path);
bool createRecursionDir(std::string path);
bool removeFile(const std::string &pathfile);
bool removeDir(const std::string &path);

//md5
class MD5Data;
std::string genFileMD5(std::string filename);


//string
//==========================================================================
template<class T>
std::string toString(const T &t);
template<class RET>
RET fromString(const std::string & t, RET def);
//tonumber
//both 1 left, 2right, 3 both
void trim(std::string &str, std::string ign, int both = 3);
std::vector<std::string> splitString(std::string text, std::string deli, std::string ign);
std::string toUpperString(std::string  org);
std::string toLowerString(std::string  org);
bool compareStringIgnCase(const std::string & left, const std::string & right, bool canTruncate = false);

//date, time, tick
//==========================================================================

//----- sleep thread ------
void sleepMillisecond(unsigned int ms);

//----- time check ------
//check used time. don't used it as datetime.
inline double getTick();
inline double getSteadyTick();
inline long long getMSecTick();
inline long long getSteadyMSecTick();

//-----date time---------
//the second through 1900-01-01 00:00:00
inline time_t getUTCTime();
inline time_t getNowTime(){ return getUTCTime(); }

// GMT+8 the mean is the area hour fast than gmt area that is + 8*3600 second.
// the method return the offset of second.  in GMT+8 return 8*3600.
//used: 
//  get local date time needn't via system tzzone.
//  like get one day's begin UTC time not via localtime.
//  like get server's local datetime in any area client. server date time = localtime(UTC + (server offset - client offset)); 
//
inline time_t getTZZoneOffset();
//the day through 1900-01-01 00:00:00
inline time_t getLocalDay(time_t offset);
//the day through 1900-01-01 00:00:00 @ $t
inline time_t getLocalDay(time_t t, time_t offset);
//the day through 1900-01-01 00:00:00
inline time_t getLocalDayByReadable(time_t offset);
//the day through 1900-01-01 00:00:00 @ $t
inline time_t getLocalDayByReadable(time_t t, time_t offset);


//get struct tm via safe method
inline tm gettm(time_t ts);

//to print date time
inline std::string formatDateString(time_t ts);
inline std::string formatTimeString(time_t ts);
inline std::string formatDateTimeString(time_t ts);
time_t getUTCTimeFromLocalString(const std::string & str);
time_t getSecondFromTimeString(const std::string & str);// format like "hour:min:second"

//default offset set 0
//example method isSameDay: if 03:00::00 is the day bound you can set offset = -3*3600
inline bool isSameYear(time_t first, time_t second, time_t offset = 0);
inline bool isSameMonth(time_t first, time_t second, time_t offset = 0);
inline bool isSameWeak(time_t first, time_t second, time_t offset = 0);
inline bool isSameDay(time_t first, time_t second, time_t offset = 0);


//float
//==========================================================================
const double POINT_DOUBLE = 1e-14;
const double PI = 3.14159265358979323;

inline bool isEqual(double f1, double f2, double acc = POINT_DOUBLE);
inline bool isZero(double f, double acc = POINT_DOUBLE);
inline double getDistance(double org, double dst);
inline double getDistance(double orgx, double orgy, double dstx, double dsty);
inline double getRadian(double orgx, double orgy, double dstx, double dsty);
inline std::tuple<double, double> getFarPoint(double orgx, double orgy, double radian, double distance);
inline std::tuple<double, double> getFarOffset(double orgx, double orgy, double dstx, double dsty, double distance);
inline std::tuple<double, double> rotatePoint(double orgx, double orgy, double orgrad, double distance, double radian);

//bit
//==========================================================================
template<class Integer, class Number>
inline bool checkBitFlag(Integer n, Number f) // f [1-32] or [1-64], begin 1 not 0.
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
    return n ^ ((Integer)1 << (f - 1));
}

//rand
//==========================================================================
inline double randfloat()
{
    return (rand() % 10000) / 10000.0;
}
inline double randfloat(double min, double max)
{
    return  min + randfloat() * (max - min);
}

//integer
//==========================================================================
//return value is [min, max]
template<class T>
inline T pruning(T v, T min, T max)
{
    return v < min ? min : (v > max ? max : v);
}


//process
//==========================================================================
std::string getProcessID();
std::string getProcessName();

#include "utlsImpl.h"
#endif