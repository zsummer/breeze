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

#include "utility.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <algorithm>
#include <locale>
#include <assert.h>
#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <io.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi")
#pragma warning(disable:4996)
#else
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include<pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

#ifndef zs_ut_s
#define zs_ut_s zsummer::utility
#endif


static const char * gsc_strVersion	=""
"\n***********************************\n"
"zsummer current version: 1.0.0 \n"
"build by: zhangyawei\n"
"e-mail: yawei_zhang@foxmail.com\n"
"build time: 2010.08.29\n"
"update time: 2012.05.06\n"
"***********************************\n";

static const char * gsc_strVersionLog = ""
"* 2010.8.29  iocp test\n"
"* 2010.9.24	实现windows下临界区的封装\n"
"* 2010.9.26	实现windows下多线程的封装\n"
"* 2010.9.29	解决iocp socket close 资源释放\n"
"* 2010.10.4  抽象出IOCP高级封装接口\n"
"* 2010.12.7  重构IOCP的设计封装, 服务器趋于稳定\n"
"* -------------- *\n"

"* 2011.3.15  iocp / epoll project build\n"
"* 2011.3.19	实现跨平台的互斥锁, 信号量, 线程包装类的封装,  跨平台的时间获取 休眠 转换小函数\n"
"* 2011.3.22	增加跨平台的网络封装接口雏形, CLog 封装, createdir函数, splitstring, selfmemqueue等\n"
"* 2011.3.23	修正代码风格, 去掉linux c的全小写风格\n"
"* 2011.4.1	epoll实现经过功能测试, iocp移植到新的网络接口下, CLog采用环形队列\n"
"* 2011.4.9   功能测试完成\n"
"* -------------- *\n"

"* 2012.4.21 新的封装, 全新编写\n"
"* 2012.5.7 增加跨平台的系统进程监控记录模块\n"
"* 2012.5.8  增加minidump模块\n"
"* 2012.5.28 IOCP实现完成\n"
"* 2012.6.6 EPOLL实现完成\n"
"* 2012.6.7 代码整理, 测试服务编写\n"
"* 2012.6.8 asio测试客户端编写完成\n"
"* 2012.6.9 调测\n"
"* 2012.7.18 多种环境下的压力测试完成\n"
"* 2012.12.16 日志类由单日志输出改为多日志输出 并可灵活配置 屏显上色等\n"
"*--------------- *\n";

static const char * gsc_strUtilityVersion = ""
"\n***********************************\n"
"module name: utility\n"
"builder: zhangyawei\n"
"e-mail: yawei_zhang@foxmail.com\n"
"build time: 2011.3.19\n"
"update time: 2012.12.13\n"
"***********************************\n";
static const char * gsc_strUtilityVersionLog = ""
"* 2012.12.12 去掉头文件中的base.h包含, 减小utility模块的依赖.增加彩色字体输出.命名规则更改\n"
"* 2012.12.13 合并splite.h 改为utility模块的一个方法\n"
"* 2012.12.16 增加字符串处理小函数, 配置文件处理小函数等\n";



const char * zs_ut_s::GetVersion()
{
	return gsc_strVersion;
}
const char * zs_ut_s::GetVersionLog()
{
	return gsc_strVersionLog;
}

const char * zs_ut_s::GetUtilityVersion()
{
	return gsc_strUtilityVersion;
}
const char * zs_ut_s::GetUtilityVersionLog()
{
	return gsc_strUtilityVersionLog;
}



//-------------------------------------------------------------------
void zs_ut_s::SleepMillisecond(unsigned int ms)
{
#ifdef WIN32
	::Sleep(ms);
#else
	usleep(1000*ms);
#endif
}

unsigned int zs_ut_s::GetTimeMillisecond()
{
#ifdef WIN32
	return ::GetTickCount();
#else
	struct timeval tm;
	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + (tm.tv_usec/1000));
#endif
}


//获得一个时间值 精确到微秒
unsigned long long zs_ut_s::GetTimeMicrosecond()
{
#ifdef WIN32
	LARGE_INTEGER lip;
	LARGE_INTEGER lic;
	QueryPerformanceFrequency(&lip);
	QueryPerformanceCounter(&lic);
	return (unsigned long long)(lic.QuadPart*1000/(lip.QuadPart/1000));
#else
	struct timeval tm;
	gettimeofday(&tm, NULL);
	return ((unsigned long long )tm.tv_sec) * 1000 * 1000 + (unsigned long long)tm.tv_usec;
#endif
}




//转换time_t tm
bool zs_ut_s::TimeToTm(time_t t, tm * tt)
{
#ifdef WIN32
	if (localtime_s(tt, &t) == 0)
	{
		return true;
	}
	return false;
#else
	if (localtime_r(&t, tt) != NULL)
	{
		return true;
	}
	return false;
#endif
}

// 转换错误返回-1
time_t zs_ut_s::TmToTime(tm * tt)
{
	return mktime(tt);
}

std::string zs_ut_s::TimeToString(time_t t)
{
	char m[128] = {0};
	tm tt;
	if (TimeToTm(t, &tt))
	{
		sprintf(m, "%d-%02d-%02d %02d:%02d:%02d", tt.tm_year+1900, tt.tm_mon+1, tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec);
	}
	else
	{
		sprintf(m, "0000-00-00 00:00:00");
	}
	return m;
}

bool zs_ut_s::isTimeSameDay(time_t t1, time_t t2)
{
	struct tm tm1;
	struct tm tm2;
	TimeToTm(t1, &tm1);
	TimeToTm(t2, &tm2);
	if (tm1.tm_year == tm2.tm_year && 
	    tm1.tm_yday == tm2.tm_yday)
	{
		return true;
	}
	return false;
}
bool zs_ut_s::isTimeSameWeek(time_t t1, time_t t2)
{
	struct tm tm1;
	TimeToTm(t1, &tm1);
	//one year
	time_t pre = (tm1.tm_wday)*24*3600 + tm1.tm_hour*3600 + tm1.tm_min*60 + tm1.tm_sec;
	pre = t1 - pre;

	time_t suffix = (6-tm1.tm_wday)*24*3600 + (23-tm1.tm_hour)*3600 + (59-tm1.tm_min)*60 + (59-tm1.tm_sec);
	suffix = t1+suffix;

	if (t2 > pre && t2 < suffix)
	{
		return true;
	}
	return false;
}
bool zs_ut_s::isTimeSameMon(time_t t1, time_t t2)
{
	struct tm tm1;
	struct tm tm2;
	TimeToTm(t1, &tm1);
	TimeToTm(t2, &tm2);
	if (tm1.tm_year == tm2.tm_year && 
		tm1.tm_mon == tm2.tm_mon)
	{
		return true;
	}
	return false;
}
bool zs_ut_s::isTimeSameYear(time_t t1, time_t t2)
{
	struct tm tm1;
	struct tm tm2;
	TimeToTm(t1, &tm1);
	TimeToTm(t2, &tm2);
	if (tm1.tm_year == tm2.tm_year)
	{
		return true;
	}
	return false;
}
//[范围)
int zs_ut_s::Rand(int begin, int end)
{
	assert(end >= begin);
	if (end == begin)
	{
		return 0;
	}
	int  region = end - begin;
	int ret = rand()%region;
	return begin + ret;
}
//[0-*)
int zs_ut_s::Rand(int end)
{
	return Rand(0, end);
}

bool zs_ut_s::SplitString(std::string strText, 
			     std::string strSegmentation, 
			     std::vector<std::string> &vctOut,
			     bool bIgnoreMulti)
{
	vctOut.clear();
	if (strText.length() == 0 || strSegmentation.length() == 0)
	{
		vctOut.push_back(strText);
		return true;
	}


	std::string strSub;
	std::string::size_type lastPos = 0; //循环查找中 下一次查找字符串的起始位置
	std::string::size_type segLen = strSegmentation.length();
	//分割
	while (1)
	{
		std::string::size_type pos = strText.find(strSegmentation, lastPos);
		strSub = strText.substr(lastPos, pos-lastPos);
		if (bIgnoreMulti)
		{
			if (strSub.length() > 0)
			{
				vctOut.push_back(strSub);
			}
		}
		else
		{
			vctOut.push_back(strSub);
		}

		if (pos == std::string::npos)
		{
			break;
		}

		lastPos+= strSub.length() + segLen;
		if (lastPos >= strText.length())
		{
			break;
		}
	}
	return true;		
}

void zs_ut_s::TrimString(std::string & str, int flag)
{
	if (str.length() == 0)
	{
		return ;
	}
	if (flag == 0 || flag == 2)
	{
		std::string::size_type pos = str.find_first_not_of(' ');
		if (pos != std::string::npos)
		{
			str = str.substr(pos, std::string::npos);
		}
	}
	if (flag == 1 || flag == 2)
	{
		std::string::size_type pos = str.find_last_not_of(' ');
		if (pos != std::string::npos)
		{
			str = str.substr(0, pos+1);
		}
	}
}
void zs_ut_s::TrimString(char * str, int flag)
{
	assert(str != NULL);
	std::string s = str;
	TrimString(s, flag);
	strcpy(str, s.c_str());
}

void zs_ut_s::FixWinSep(std::string &path)
{
	if (path.length() == 0)
	{
		return;
	}
	for (std::string::iterator iter = path.begin(); iter != path.end(); ++iter)
	{
		if (*iter == '\\')
		{
			*iter = '/';
		}
	}
}

void zs_ut_s::FixPath(std::string &path)
{
	if (path.length() == 0)
	{
		return;
	}
	FixWinSep(path);
	if (path.at(path.length()-1) != '/')
	{
		path += "/";
	}
}

std::string zs_ut_s::GetPathName(std::string path)
{
	FixWinSep(path);
	std::string::size_type pos = path.rfind('/');
	if (pos == std::string::npos)
	{
		pos = 0;
	}
	else
	{
		pos +=1;
	}
	return path.substr(pos, std::string::npos);
}

std::string zs_ut_s::GetPathSuffix(std::string path)
{
	FixWinSep(path);
	std::string::size_type pos = path.rfind('.');
	if (pos == std::string::npos)
	{
		pos = 0;
	}
	return path.substr(pos, std::string::npos);
}

static void TrimXmlContent(std::string &content)
{
	if (content.length() == 0)
	{
		return ;
	}
	std::string dest;
	std::string::size_type pos1 = 0;
	std::string::size_type pos2 = 0;
	do 
	{
		pos2 = content.find("<!--", pos1);
		if (pos2 == std::string::npos)
		{
			dest.append(content.substr(pos1, std::string::npos));
			break;
		}

		dest.append(content.substr(pos1, pos2 - pos1));
		pos1 = pos2;
		pos2 = content.find("-->",pos1+4);
		if (pos2 == std::string::npos)
		{
			break;
		}
		pos1 = pos2+3;
	} while (1);
	content = dest;
}

bool zs_ut_s::GetXmlParam(std::string content, std::string param, std::vector<std::string> & data)
{
	TrimXmlContent(content);

	data.clear();
	std::string preParam = "<";
	preParam += param;
	preParam += ">";
	std::string suffParam = "</";
	suffParam += param;
	suffParam += ">";

	std::string::size_type pos1 = 0;
	while(1)
	{
		pos1 = content.find(preParam, pos1);
		if (pos1 == std::string::npos)
		{
			break;
		}
		pos1 += preParam.length();
		std::string::size_type pos2 = content.find(suffParam, pos1);
		if (pos2 == std::string::npos)
		{
			break;
		}

		data.push_back(content.substr(pos1, pos2-pos1));
		TrimString(data.back());
	}
	return true;
}
bool zs_ut_s::GetXmlParam(std::string content, std::string param, std::string & data)
{
	data.clear();
	std::vector<std::string> vct;
	GetXmlParam(content, param, vct);
	if (vct.size() > 0)
	{
		data = vct.at(0);
		return true;
	}
	return false;
}
bool zs_ut_s::GetXmlParam(std::string content, std::string param, int & data)
{
	std::string str;
	if (!GetXmlParam(content, param, str))
	{
		return false;
	}
	if (str.length() == 0)
	{
		return false;
	}
	data = atoi(str.c_str());
	return true;
}
bool zs_ut_s::GetXmlParam(std::string content, std::string param, bool & data)
{
	std::string str;
	if (!GetXmlParam(content, param, str))
	{
		return false;
	}
	if (str.length() == 0)
	{
		return false;
	}
	int n = atoi(str.c_str());
	if (n == 0)
	{
		data = false;
	}
	else
	{
		data = true;
	}
	return true;
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------

//mod: 00, 02, 04, 06, exsit, read, write both  
bool zs_ut_s::GetFileStatus(std::string file, int mod)
{
#ifdef WIN32
	return (_access(file.c_str(), mod) == 0);
#else
	int _mod = 0;
	if (mod == 0) _mod = F_OK;
	else if (mod == 2) _mod = R_OK;
	else if (mod == 4) _mod = W_OK;
	else if (mod == 6) _mod = R_OK|W_OK;
	else
	{
		return false;
	}
	return access(file.c_str(), _mod) == 0;
#endif
}


bool zsummer::utility::CopyFileZ(std::string src, std::string dst)
{
#ifdef WIN32
	return ::CopyFileA(src.c_str(), dst.c_str(), FALSE) != FALSE;
#else
	std::fstream i;
	i.open(src.c_str(), std::ios::binary|std::ios::in);
	if (!i.is_open())
	{
		return false;
	}
	std::fstream o;
	o.open(dst.c_str(), std::ios::binary|std::ios::out|std::ios::trunc);
	if (!o.is_open())
	{
		i.close();
		return false;
	}

	i.seekg(0, std::ios::beg);
	size_t filelenth = i.tellg();
	i.seekg(0, std::ios::end);

	filelenth = (size_t)i.tellg() - filelenth;
	i.seekg(0, std::ios::beg);
	char buf[1024*64];
	const size_t buflen = 1024*64;
	size_t readlen = 0;
	while (filelenth > 0)
	{
		if (filelenth <= buflen)
		{
			readlen = filelenth;
			filelenth = 0;
		}
		else
		{
			readlen = buflen;
			filelenth -= readlen;
		}
		i.read(buf, (std::streamsize)readlen);
		o.write(buf, (std::streamsize)readlen);
	}
	i.close();
	o.close();
	return true;
#endif
}

bool zs_ut_s::MoveFileZ(std::string src, std::string dst)
{
	return rename(src.c_str(), dst.c_str()) == 0;
// #ifdef WIN32
// 	return ::MoveFileA(src.c_str(), dst.c_str()) != FALSE;
// #endif
}
bool zs_ut_s::DeleteFileZ(std::string file)
{
	return remove(file.c_str()) == 0;
// #ifdef WIN32
// 	return ::DeleteFile(file.c_str()) != FALSE;
// #endif
}





//-------------------------------------------------------------------


bool zs_ut_s::IsDirectory(std::string path)
{
#ifdef WIN32
	return PathIsDirectoryA(path.c_str()) ? true : false;
#else
	DIR * pdir = opendir(path.c_str());
	if (pdir == NULL)
	{
		return false;
	}
	else
	{
		closedir(pdir);
		pdir = NULL;
		return true;
	}
#endif
	return false;
}

//创建文件夹
bool zs_ut_s::CreateDir(std::string path)
{
#ifdef WIN32
	return CreateDirectoryA(path.c_str(), NULL) ? true : false;
#else
	return (mkdir(path.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == 0);
#endif
	return false;
}

//删除空文件夹
bool zs_ut_s::DeleteDir(std::string path)
{
#ifdef WIN32
	return RemoveDirectoryA(path.c_str()) ? true : false;
#else
	return (rmdir(path.c_str()) == 0) ? true : false;
#endif
}


//若是不存在上级文件夹则自动创建
bool zs_ut_s::CreateRecursionDir(std::string path)
{
	if (path.length() == 0) return true;
	std::string sub;
	//预处理
	FixPath(path);
	std::string::size_type pos = path.find('/');
	while (pos != std::string::npos)
	{
		std::string cur = path.substr(0, pos-0);
		if (cur.length() > 0 && !IsDirectory(cur))
		{
			if (!CreateDir(cur))
			{
				return false;
			}
		}
		pos = path.find('/', pos+1);
	}
	
	return true;
}

bool zs_ut_s::DeleteRecursionDir(std::string path)
{
	std::vector<_FileInfo> files;
	searchFiles(path, files);

	for (std::vector<_FileInfo>::const_reverse_iterator iter =files.rbegin(); iter != files.rend(); ++iter)
	{
		if (iter->bDir)
		{
			zs_ut_s::DeleteDir(iter->fullpath);
		}
		else
		{
			zs_ut_s::DeleteFileZ(iter->fullpath);
		}
	}
	return zs_ut_s::DeleteDir(path);
}


static bool tmpSearchPath(std::string  path, std::vector<zs_ut_s::_FileInfo> & files)
{
	if (path.length() == 0)
	{
		return false;
	}
	zsummer::utility::FixPath(path);

#ifdef WIN32
	WIN32_FIND_DATAA fd;
	std::string findpath = path;
	findpath.append("*");
	HANDLE hFile = FindFirstFileA(findpath.c_str(), &fd);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	zs_ut_s::_FileInfo file;
	do 
	{
		if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0 )
			{
				memset(&file, 0, sizeof(file));
				file.bDir = true;
				strcpy_s(file.filename, sizeof(file.filename), fd.cFileName);
				sprintf(file.fullpath, "%s%s", path.c_str(), fd.cFileName);
				files.push_back(file);
				tmpSearchPath(file.fullpath, files);
			}
		}
		else
		{
			memset(&file, 0, sizeof(file));
			file.bDir = false;
			file.filesize = fd.nFileSizeHigh;
			file.filesize = file.filesize << 32;
			file.filesize += fd.nFileSizeLow;
			strcpy_s(file.filename, sizeof(file.filename), fd.cFileName);
			sprintf(file.fullpath, "%s%s", path.c_str(), fd.cFileName);
			files.push_back(file);
		}
	} while (FindNextFileA(hFile, &fd));
	FindClose(hFile);

#else
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(path.c_str())) == NULL) 
	{
		return false;
	}
	zs_ut_s::_FileInfo file;
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
			{
				continue;
			}
			memset(&file, 0, sizeof(file));
			file.bDir = true;
			file.filesize = statbuf.st_size;
			strcpy(file.filename, entry->d_name);
			sprintf(file.fullpath, "%s%s", path.c_str(), entry->d_name);
			files.push_back(file);
			tmpSearchPath(file.fullpath, files);
		}
		else 
		{
			memset(&file, 0, sizeof(file));
			file.bDir = false;
			file.filesize = statbuf.st_size;
			strcpy(file.filename, entry->d_name);
			file.fullpath[0] = '\0';
			files.push_back(file);
		}
	}
	closedir(dp);
#endif
	return true;
}

bool zs_ut_s::searchFiles(std::string path, std::vector<_FileInfo> & files)
{
	if (files.capacity() < 2000)
	{
		files.reserve(2000);
	}
	return tmpSearchPath(path, files);
}



std::string zs_ut_s::GetInstancePath()
{
#ifdef WIN32
	char buf[260] = {0};
	GetModuleFileNameA(NULL, buf, 259);
	std::string retstr;
	retstr = buf;
	retstr = retstr.substr(0, retstr.rfind('\\') - 0);
	return retstr;
#else
	char buf[260]={0};
	getcwd(buf, 259);
	return buf;
#endif
}

std::string zs_ut_s::GetInstanceName()
{
#ifdef WIN32
	char buf[260] = {0};
	GetModuleFileNameA(NULL, buf, 259);
	std::string retstr;
	retstr = buf;
	std::string::size_type pos = retstr.rfind("\\");
	if (pos == std::string::npos)
	{
		return retstr;
	}
	return  retstr.substr(pos+1);
#else
	std::string retstr;
	pid_t id = getpid();
	char buf[100];
	sprintf(buf, "/proc/%d/cmdline", (int)id);
	std::fstream i;
	i.open(buf, std::ios::in);
	if (!i.is_open())
	{
		return retstr;
	}
	std::getline(i, retstr);
	i.close();
	std::string::size_type pos = retstr.rfind("/");
	if (pos == std::string::npos)
	{
		return retstr;
	}
	retstr = retstr.substr(pos+1);
	return retstr;
#endif
}


#ifdef WIN32

const static WORD cs_sColor[zs_ut_s::TEXT_COLOR_VIOLET+1] = {0,
FOREGROUND_RED,
FOREGROUND_GREEN,
FOREGROUND_BLUE|FOREGROUND_GREEN,
FOREGROUND_GREEN|FOREGROUND_RED,
FOREGROUND_RED|FOREGROUND_BLUE};
#else

const static char cs_strColor[zs_ut_s::TEXT_COLOR_VIOLET+1][20] = { "\e[0m",
"\e[31m",
"\e[32m",
"\e[34m\e[1m",
"\e[33m",
"\e[35m"};
#endif
void zs_ut_s::ShowText(const char *text, const SHOW_TEXT_COLOR color)
{
	if (color < TEXT_COLOR_RED || color > TEXT_COLOR_VIOLET) goto showfail;

#ifndef WIN32
	printf("%s%s\e[0m", cs_strColor[color], text);
#else
	HANDLE hStd = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStd == INVALID_HANDLE_VALUE) goto showfail;

	CONSOLE_SCREEN_BUFFER_INFO oldInfo;
	if (!GetConsoleScreenBufferInfo(hStd, &oldInfo)) goto showfail;

	if (SetConsoleTextAttribute(hStd, cs_sColor[color]))
	{
		printf(text);
		SetConsoleTextAttribute(hStd, oldInfo.wAttributes);
	}
	else
	{
		goto showfail;
	}
#endif

	return;

showfail:
	printf(text);
}





