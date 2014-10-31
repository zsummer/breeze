/*
 * ZSUMMER License
 * -----------
 * 
 * ZSUMMER is licensed under the terms of the MIT license reproduced below.
 * This means that ZSUMMER is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2012 YaweiZhang <yawei_zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */


/*
 * AUTHORS:  YaweiZhang <yawei_zhang@foxmail.com>
 * VERSION:  1.0.0
 * PURPOSE:  A lightweight C++ library for network.
 * CREATION: 2010.8.29
 * LCHANGE:  -
 * LICENSE:  Expat/MIT License, See Copyright Notice at the begin of this file.
 */


/*
 *
 * QQ Group: 19811947
 * Web Site: www.zsummer.net
 * mail: yawei_zhang@foxmail.com
 */

/*
module:	public tools	公共小零件
builder:	zhangyawei	张亚伟
e-mail:	yawei_zhang@foxmail.com
version:	-
build time:	2011.3.19

file:		utility.cpp
depend:	-
intro:		时间获取类函数, 休眠函数, 计时函数, 线程安全的时间转换函数,文件操作函数 文件夹函数 进程路径等函数
*/

/*   更新日志
**********************************
2012.9.8
2012.12.12
	去掉头文件中的base.h包含, 减小utility模块的依赖.
	增加彩色字体输出
	命名规则更改
2012.12.22 增加彩色字体上屏等

**********************************
*/

#pragma once
#ifndef _ZSUMMER_UTILITY_H_
#define _ZSUMMER_UTILITY_H_

#ifndef _ZSUMMER_BEGIN
#define _ZSUMMER_BEGIN namespace zsummer {
#endif
#ifndef _ZSUMMER_UTILITY_BEGIN
#define _ZSUMMER_UTILITY_BEGIN namespace utility {
#endif

#include <string>
#include <vector>
#include <sstream>
_ZSUMMER_BEGIN
_ZSUMMER_UTILITY_BEGIN


const char * GetVersion();
const char * GetVersionLog();
const char * GetUtilityVersion();
const char * GetUtilityVersionLog();

//时间类
void SleepMillisecond(unsigned int ms);
unsigned int GetTimeMillisecond();
unsigned long long GetTimeMicrosecond();
bool TimeToTm(time_t t, tm * tt);
time_t TmToTime(tm * tt);
std::string TimeToString(time_t t);
bool isTimeSameDay(time_t t1, time_t t2);
bool isTimeSameWeek(time_t t1, time_t t2);
bool isTimeSameMon(time_t t1, time_t t2);
bool isTimeSameYear(time_t t1, time_t t2);

//随机: [begin-end)
int Rand(int begin, int end);
//[0-end)
int Rand(int end);

//字符处理
//bIgnoreMulti 忽略多个分隔符;
bool SplitString(std::string strText, 
		   std::string strSegmentation, 
		   std::vector<std::string> &vctOut,
		   bool bIgnoreMulti=false); 

//flag 0: left trim,  1:right trim,  2:double trim
void TrimString(std::string & str, int flag = 2);
void TrimString(char * str, int flag = 2);
void FixWinSep(std::string &path);
void FixPath(std::string &path); 
std::string GetPathName(std::string path);
std::string GetPathSuffix(std::string path);
bool GetXmlParam(std::string content, std::string param, std::string & data);
bool GetXmlParam(std::string content, std::string param, std::vector<std::string> & data);
bool GetXmlParam(std::string content, std::string param, int & data);
bool GetXmlParam(std::string content, std::string param, bool & data);

//文件与文件夹
bool GetFileStatus(std::string file, int mod);
bool CopyFileZ(std::string src, std::string dst);
bool MoveFileZ(std::string src, std::string dst);
bool DeleteFileZ(std::string file);
bool IsDirectory(std::string path);
bool CreateDir(std::string path);
bool DeleteDir(std::string path);
bool CreateRecursionDir(std::string path);
bool DeleteRecursionDir(std::string path); 

struct _FileInfo
{
	char filename[260];
	char fullpath[260];
	unsigned long long filesize;
	bool bDir;
};
bool SearchFiles(std::string path, std::vector<_FileInfo> & files);


//进程
std::string GetInstancePath();
std::string GetInstanceName();





enum SHOW_TEXT_COLOR
{
	TEXT_COLOR_NORMAL,
	TEXT_COLOR_RED,
	TEXT_COLOR_GREEN,
	TEXT_COLOR_BLUE,
	TEXT_COLOR_YELLOW,
	TEXT_COLOR_VIOLET,
};
void ShowText(const char *text, 
		     const SHOW_TEXT_COLOR color =TEXT_COLOR_RED);



#ifndef _ZSUMMER_END
#define _ZSUMMER_END }
#endif
#ifndef _ZSUMMER_UTILITY_END
#define _ZSUMMER_UTILITY_END }
#endif

_ZSUMMER_UTILITY_END
_ZSUMMER_END



#ifndef PUT_STREAM
#define PUT_STREAM(x, c)\
{\
std::stringstream ss;\
ss << zsummer::utility::TimeToString(time(NULL)) <<" ShowText " << x <<"  \t"\
	<< zsummer::utility::GetPathName(__FILE__) <<":"<<__LINE__ <<std::endl;\
zsummer::utility::ShowText(ss.str().c_str(), c);\
}
#endif

#ifndef PUTN
#define PUTN(x) PUT_STREAM(x, zsummer::utility::TEXT_COLOR_NORMAL)
#endif
#ifndef PUTR
#define PUTR(x) PUT_STREAM(x, zsummer::utility::TEXT_COLOR_RED)
#endif
#ifndef PUTG
#define PUTG(x) PUT_STREAM(x, zsummer::utility::TEXT_COLOR_GREEN)
#endif
#ifndef PUTB
#define PUTB(x) PUT_STREAM(x, zsummer::utility::TEXT_COLOR_BLUE)
#endif
#ifndef PUTY
#define PUTY(x) PUT_STREAM(x, zsummer::utility::TEXT_COLOR_YELLOW)
#endif
#ifndef PUTV
#define PUTV(x) PUT_STREAM(x, zsummer::utility::TEXT_COLOR_VIOLET)
#endif


#ifndef ZSUMMER_ASSERT
#define ZSUMMER_ASSERT(x)\
{\
	bool ret = (x);\
	if (!ret)\
	{\
		PUTR("ZUMMER_ASSERT FAILED! ");\
		assert(0);\
	}\
}
#endif




namespace boost
{
	template <class RET, class ORG>
	RET lexical_cast(ORG org)
	{
		std::stringstream os;
		os << org;
		RET ret;
		os >> ret;
		return ret;
	}
}






#endif
