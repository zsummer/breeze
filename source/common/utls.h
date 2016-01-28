

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

/*
*  file desc
*  all server configure for start and configure defined from this.
*/


#ifndef _UTLS_H_
#define _UTLS_H_

#include <defined.h>
#include <single.h>

//file
//read file. write file.

//md5
class MD5Data;
std::string genFileMD5(std::string filename);


//string
template<class T>
std::string toString(const T &t);
//tonumber
//split
//trim


//date, time, tick
//==========================================================================
inline double getNow();
inline double getSteadyNow();
inline long long getNowTick();
inline long long getSteadyNowTick();

inline time_t getTimestampNow();
inline tm getTimestampStruct(time_t ts);

inline std::string getDateString(time_t ts);
inline std::string getDateTimeString(time_t ts);

//default offset set 0
//example method isSameDay: if 03:00::00 is the day bound you can set offset = -3*3600
inline bool isSameYear(time_t first, time_t second, time_t offset);
inline bool isSameMonth(time_t first, time_t second, time_t offset);
inline bool isSameWeak(time_t first, time_t second, time_t offset);
inline bool isSameDay(time_t first, time_t second, time_t offset);


//double
const double POINT_DOUBLE = 1e-14;
const float POINT_FLOAT = 1e-5f;
const double PI = 3.14159265359;

inline bool isEqual(double f1, double f2, double acc = POINT_DOUBLE);
inline bool isEqual(float f1, float f2, double acc = POINT_FLOAT);
inline bool isZero(double f, double acc = POINT_DOUBLE);
inline bool isZero(float f, float acc = POINT_FLOAT);
inline double getDistance(double org, double dst);
inline double getDistance(float org, float dst);
inline double getDistance(double orgx, double orgy, double dstx, double dsty);
inline float getDistance(float orgx, float orgy, float dstx, float dsty);
inline double getRadian(double orgx, double orgy, double dstx, double dsty);
inline float getRadian(float orgx, float orgy, float dstx, float dsty);
inline std::tuple<double, double> getFarPoint(double orgx, double orgy, double radian, double distance);
inline std::tuple<float, float> getFarPoint(float orgx, float orgy, float radian, float distance);
inline std::tuple<double, double> getFarOffset(double orgx, double orgy, double dstx, double dsty, double distance);
inline std::tuple<float, float> getFarOffset(float orgx, float orgy, float dstx, float dsty, float distance);
inline std::tuple<double, double> rotatePoint(double orgx, double orgy, double orgrad, double distance, double radian);
inline std::tuple<float, float> rotatePoint(float orgx, float orgy, float orgrad, float distance, float radian);



#include "utlsImpl.h"
#endif