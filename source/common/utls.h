

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

//-------------------------------------------------------------------------------
//isBinary if false it's will auto fix UTF-8 BOM. only this.
std::string readFileContent(const std::string & filename, bool isBinary = false, size_t limitSize = 1024 * 1024, size_t beginIndex = 0);
size_t writeFileContent(const std::string & filename, const char * buff, size_t buffLen, bool isAppend = true);
bool isDirectory(const std::string & path);
bool createRecursionDir(std::string path);

//md5
class MD5Data;
std::string genFileMD5(std::string filename);


//string
template<class T>
std::string toString(const T &t);
//tonumber
//both 1 left, 2right, 3 both
void trim(std::string &str, std::string ign, int both = 3);
std::vector<std::string> splitString(const std::string & text, std::string deli, std::string ign);
std::string toUpperString(std::string  org);
std::string toLowerString(std::string  org);
bool compareStringIgnCase(const std::string & left, const std::string & right, bool canTruncate = false);

//date, time, tick
//==========================================================================
void sleepMillisecond(unsigned int ms);

inline double getNow();
inline double getSteadyNow();
inline long long getNowTick();
inline long long getSteadyNowTick();

inline time_t getTimestampNow();
inline tm getTimestampStruct(time_t ts);

inline std::string getDateString(time_t ts);
inline std::string getTimeString(time_t ts);
inline std::string getDateTimeString(time_t ts);

//default offset set 0
//example method isSameDay: if 03:00::00 is the day bound you can set offset = -3*3600
inline bool isSameYear(time_t first, time_t second, time_t offset = 0);
inline bool isSameMonth(time_t first, time_t second, time_t offset = 0);
inline bool isSameWeak(time_t first, time_t second, time_t offset = 0);
inline bool isSameDay(time_t first, time_t second, time_t offset = 0);


//float process
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



//process
std::string getProcessID();
std::string getProcessName();

#include "utlsImpl.h"
#endif