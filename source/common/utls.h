

/*
* breeze License
* Copyright (C) 2016 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
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



#pragma once
#ifndef _UTLS_H_
#define _UTLS_H_

#ifdef WIN32
#pragma warning(disable:4996)
#pragma warning(disable:4819)
#define WIN32_LEAN_AND_MEAN
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <windows.h>
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include<pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#endif 

#ifdef __APPLE__
#include<mach/mach_time.h>
#include <dispatch/dispatch.h>
#include <libproc.h>
#endif

#include <iomanip>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <cstdint>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <limits>

#include <functional>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <random>

#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>

#ifdef max
#undef  max
#endif // max

#ifdef min
#undef  min
#endif // min



//file
//==========================================================================
//it's will jump UTF-8 BOM when isBinary  is false .
std::string readFileContent(const std::string & filename, bool isBinary = false, size_t limitSize = 1024 * 1024, size_t beginIndex = 0);
size_t writeFileContent(const std::string & filename, const char * buff, size_t buffLen, bool isAppend = true);
bool isDirectory(const std::string & path);
bool createDirectory(std::string path);
bool removeFile(const std::string &pathfile);
bool removeDir(const std::string &path);
bool accessFile(const std::string &pathfile);
std::string fixPathString(const std::string &path);
struct SearchFileInfo
{
    char filename[260];
    char fullpath[260];
    unsigned long long filesize;
    bool bDir;
};
//path support wildcard like : 
//  /var/log
//  /var/log/
//  /var/log/*
//  /var/log/*.log
//  /var/log/mysql*1*2.log
//it's will recursion subdirectory when recursion is true
bool searchFiles(std::string path, std::vector<SearchFileInfo> & files, bool recursion = false);

//md5
class MD5Data;
std::string genFileMD5(std::string filename);


//string
//==========================================================================
/* template<class T>
std::string toString(const T &t); */
/*
template<class To>
typename To fromString(const std::string & t);*/
inline void trimImpl(const char * buf, size_t len, const char ign, size_t & offset, size_t & outLen, int flag);
inline void trimL(const char * begin, size_t len, const char ign, size_t & offset, size_t & outLen) { return trimImpl(begin, len, ign, offset, outLen, 1); }
inline void trimR(const char * begin, size_t len, const char ign, size_t & offset, size_t & outLen) { return trimImpl(begin, len, ign, offset, outLen, 2); }
inline void trim(const char * begin, size_t len, const char ign, size_t & offset, size_t & outLen) { return trimImpl(begin, len, ign, offset, outLen, 0); }





template<class Container>  //example: Container = std::vector<int>
std::string mergeToString(const Container & contariner, char deli);
template<class T>  //example: Container = std::vector<int>
void mergeToString(std::string & dstString, char deli, const T & t);

// text, deli, store text in pair.first when not found deli, greedy search
std::pair<std::string, std::string> subString(const std::string & text, const std::string & deli, bool preStore = true, bool isGreedy = false);
std::string replaceString(const std::string & text, const std::string & pattern, const std::string &rep, bool once);



std::string toUpperString(std::string  org);
std::string toLowerString(std::string  org);

bool compareStringIgnCase(const std::string & left, const std::string & right, bool canTruncate = false);
bool compareStringWildcard(std::string source, std::string mod, bool ignCase = false);

int getCharUTF8Count(const std::string & str);
int getCharASCIICount(const std::string & str);
int getCharNoASCIICount(const std::string & str);
bool hadIllegalChar(const std::string & str); // return true when have invisible char, mysql unsupport char, mysql escape char.

//date, time, tick
//==========================================================================

//----- sleep thread ------
void sleepMillisecond(unsigned int ms);

//----- time check ------
//check used time. don't used it as datetime.
inline double getFloatNowTime();
inline double getFloatSteadyNowTime();
inline long long getNowTick();
inline long long getNowSteadyTick();

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
//get current second from day begin.
inline time_t getDaySecond(time_t t);

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
//
inline int distanceDays(time_t first, time_t second);


//float
//==========================================================================
const double POINT_DOUBLE = 1E-15; // the number N is decimal places (decimalism). N=log10(1/POINT_DOUBLE) . example 1E-15 ==> 15 number of decimal places.
const double PI = 3.14159265358979323;


inline bool isEqual(double f1, double f2, double acc = POINT_DOUBLE);
inline bool isZero(double f, double acc = POINT_DOUBLE);

inline double getDistance(double posx1, double posy1, double posx2, double posy2);
inline double getDistance(const std::tuple<double, double> & pos1, const std::tuple<double, double> & pos2);

inline double getRadian(double vx, double vy);
inline double getRadian(double vx1, double vy1, double vx2, double vy2);
inline double getRadian(const std::tuple<double, double> & v);
inline double getRadian(const std::tuple<double, double> & v1, const std::tuple<double, double> & v2);


inline std::tuple<double, double> getFarPoint(double orgx, double orgy, double radian, double distance);

inline std::tuple<double, double> rotateVertical(double vx, double vy, bool isClockwise);
inline std::tuple<double, double> rotateVertical(std::tuple<double, double> vt, bool isClockwise);
inline std::tuple<double, double> normalize(double vx, double vy);
inline std::tuple<double, double> normalize(std::tuple<double, double> vt);
inline double dot(std::tuple<double, double> vt1, std::tuple<double, double> vt2);
inline double det(std::tuple<double, double> vt1, std::tuple<double, double> vt2);
inline double dot(double vx1, double vy1, double vx2, double vy2);
inline double det(double vx1, double vy1, double vx2, double vy2);
inline double distLine(double linex1, double liney1, double linex2, double liney2, double cx, double cy);
inline double distLine(std::tuple<double, double> line1, std::tuple<double, double> line2, std::tuple<double, double> pos);
inline std::tuple<double, double> shortestLine(std::tuple<double, double> line1, std::tuple<double, double> line2, std::tuple<double, double> pos);
inline std::tuple<double, double> shortestLine(double linex1, double liney1, double linex2, double liney2, double cx, double cy);

//bit
//==========================================================================
template<class Integer, class Pos>
inline bool getBitFlag(Integer bin, Pos pos);// f [1-32] or [1-64], begin 1 not 0.
template<class Integer, class Pos>
inline Integer setBitFlag(Integer bin, Pos pos, bool flag = true);// f [1-32] or [1-64], begin 1 not 0.


//rand 随机数, 抽卡, 
//==========================================================================
//[0-0xffffffff]
unsigned int realRand();
//[mi-mx]
unsigned int realRand(unsigned int mi, unsigned int mx);
//[0.0-1.0]
double realRandF();
//[mi, mx]
double realRandF(double mi, double mx);
template<class RandIt>
inline void randomShuffle(RandIt first, RandIt end);



//从池子里面根据每个元素的权重获取元素.
//某个元素被抽中的概率是: 该元素的权重/所有元素的权重
//takeCount为抽取次数, 结果累加到返回集中 
//uniqueTake为是否允许抽到同一个元素, 如果是false 则每次抽取会移除池子中的已抽取元素. 
//某个元素的权重为0,则该元素永远不可能被获取到. 
template<class RandIt, class GetWeightFunc> // func example  [](RandIt iter){return iter->weight;}
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount, bool uniqueTake, GetWeightFunc getWeight);
template<class RandIt>
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount, bool uniqueTake)
{
    return raffle(first, end, takeCount, uniqueTake, [](RandIt) {return 10; }); //平均权重 
}

//和上面的机制不同,根据每个元素的概率进行独立随机 然后加入返回集 
//某个元素被抽中的概率是: 该元素的概率, 概率为浮点数范围为[0-1]
//某个元素的概率为0 则该元素永远不可能被获取到
//某个元素的概率为1 则该元素一定会被获取到 
//如果所有元素的概率介于0~1之间, 那么一次抽取可能所有元素都会被抽中 也可能一个也没有. 
template<class RandIt, class GetProbabilityFunc> // func example  [](RandIt iter){return iter->probability;}
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount, GetProbabilityFunc getProbability);




//rank,rating
//==========================================================================
//winFlag:
//     1 win,  0 draw, -1 lose
//return:
//      return the upper score
inline double calcELORatingUpper(double ownerScore, double dstScore, int winFlag);

//integer
//==========================================================================
//return value is [min, max]
template<class T>
inline T pruning(T v, T min, T max);

//process
//==========================================================================
std::string getProcessID();
std::string getProcessName();

//need call WSAStartup to init winsock in windows
//support ipv6 & ipv4, it's will blocking when get host.
std::string getHostByName(const std::string & name, unsigned short port);






#include "utlsImpl.h"
#endif