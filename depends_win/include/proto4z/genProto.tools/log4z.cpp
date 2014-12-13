/*
 * Log4z License
 * -----------
 * 
 * Log4z is licensed under the terms of the MIT license reproduced below.
 * This means that Log4z is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2010-2013 YaweiZhang <yawei_zhang@foxmail.com>.
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

#include "log4z.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include <string>
#include <vector>
#include <map>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


#ifdef WIN32
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#pragma comment(lib, "shlwapi")
#pragma warning(disable:4996)
#else
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <semaphore.h>
#endif



#ifndef WIN32
__thread char g_log4zstreambuf[LOG4Z_LOG_BUF_SIZE];
#endif

_ZSUMMER_BEGIN
_ZSUMMER_LOG4Z_BEGIN

static const char *const LOG_STRING[]=
{
	"LOG_TRACE",
	"LOG_DEBUG",
	"LOG_INFO ",
	"LOG_WARN ",
	"LOG_ERROR",
	"LOG_ALARM",
	"LOG_FATAL",
};

#ifdef WIN32
const static WORD LOG_COLOR[LOG_LEVEL_FATAL + 1] = {
	0,
	0,
	FOREGROUND_BLUE | FOREGROUND_GREEN,
	FOREGROUND_GREEN | FOREGROUND_RED,
	FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_RED | FOREGROUND_BLUE };
#else

const static char LOG_COLOR[LOG_LEVEL_FATAL + 1][50] = {
	"\e[0m",
	"\e[0m",
	"\e[34m\e[1m",//hight blue
	"\e[33m", //yellow
	"\e[31m", //red
	"\e[32m", //green
	"\e[35m" };
#endif

//////////////////////////////////////////////////////////////////////////
//! Log4zFileHandler
//////////////////////////////////////////////////////////////////////////
class Log4zFileHandler
{
public:
	Log4zFileHandler(){ _file = NULL; }
	~Log4zFileHandler(){ close(); }
	bool isOpen(){ return _file != NULL; }
	bool open(const char *path, const char * mod)
	{
		if (_file != NULL){fclose(_file);_file = NULL;}
		_file = fopen(path, mod);
		return _file != NULL;
	}
	void close()
	{
		if (_file != NULL){fclose(_file);_file = NULL;}
	}
	void write(const char * data, size_t len)
	{
		if (_file && len > 0)
		{
			if (fwrite(data, 1, len, _file) != len)
			{
				close();
			}
		}
	}
	void flush(){ if (_file) fflush(_file); }

	std::string readLine()
	{
		char buf[500] = { 0 };
		if (_file && fgets(buf, 500, _file) != NULL)
		{
			return std::string(buf);
		}
		return std::string();
	}
	const std::string readContent();
public:
	FILE *_file;
};


//////////////////////////////////////////////////////////////////////////
//! LogData
//////////////////////////////////////////////////////////////////////////
struct LogData
{
	LoggerId _id;		//dest logger id
	int	_level;	//log level
	time_t _time;		//create time
	unsigned int _precise; //create time 
	int _contentLen;
	char _content[LOG4Z_LOG_BUF_SIZE]; //content
};

//////////////////////////////////////////////////////////////////////////
//! LoggerInfo
//////////////////////////////////////////////////////////////////////////
struct LoggerInfo 
{
	//! attribute
	std::string _name;	// one logger one name.
	std::string _pid;	//process id(handle)
	std::string _path;	//path for log file.
	int  _level;		//filter level
	bool _display;		//display to screen 
	bool _monthdir;		//create directory per month 
	unsigned int _limitsize; //limit file's size, unit Million byte.
	bool _enable;		//logger is enable 

	//! runtime info
	time_t _curFileCreateTime;	//file create time
	unsigned int _curFileIndex; //rolling file index
	unsigned int _curWriteLen;  //current file length
	Log4zFileHandler	_handle;		//file handle.

	LoggerInfo()
	{
		setDefaultInfo();
		_curFileCreateTime = 0;
		_curFileIndex = 0;
		_curWriteLen = 0;
	}
	void setDefaultInfo()
	{ 
		_path = LOG4Z_DEFAULT_PATH; 
		_level = LOG4Z_DEFAULT_LEVEL; 
		_display = LOG4Z_DEFAULT_DISPLAY; 
		_enable = false; 
		_monthdir = LOG4Z_DEFAULT_MONTHDIR; 
		_limitsize = LOG4Z_DEFAULT_LIMITSIZE;
	}
};

//////////////////////////////////////////////////////////////////////////
//! UTILITY
//////////////////////////////////////////////////////////////////////////
static void sleepMillisecondLine(unsigned int ms);
static tm timeToTm(time_t t);
static bool isSameDay(time_t t1, time_t t2);

static void fixPath(std::string &path);
static void trimLogConfig(std::string &str, std::string extIgnore = std::string());
static std::pair<std::string, std::string> splitPairString(const std::string & str, const std::string & delimiter);
static bool parseConfig(const std::string& file, std::map<std::string, LoggerInfo> & outInfo);

static bool isDirectory(std::string path);
static bool createRecursionDir(std::string path);
void getProcessInfo(std::string &name, std::string &pid);



//////////////////////////////////////////////////////////////////////////
//! LockHelper
//////////////////////////////////////////////////////////////////////////
class LockHelper
{
public:
	LockHelper();
	virtual ~LockHelper();

public:
	void lock();
	void unLock();
private:
#ifdef WIN32
	CRITICAL_SECTION _crit;
#else
	pthread_mutex_t  _crit;
#endif
};

//////////////////////////////////////////////////////////////////////////
//! AutoLock
//////////////////////////////////////////////////////////////////////////
class AutoLock
{
public:
	explicit AutoLock(LockHelper & lk):_lock(lk){_lock.lock();}
	~AutoLock(){_lock.unLock();}
private:
	LockHelper & _lock;
};

//////////////////////////////////////////////////////////////////////////
//! SemHelper
//////////////////////////////////////////////////////////////////////////
class SemHelper
{
public:
	SemHelper();
	virtual ~SemHelper();
public:
	bool create(int initcount);
	bool wait(int timeout = 0);
	bool post();
private:
#ifdef WIN32
	HANDLE _hSem;
#else
	sem_t _semid;
	bool  _isCreate;
#endif
};



//////////////////////////////////////////////////////////////////////////
//! ThreadHelper
//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
static unsigned int WINAPI  threadProc(LPVOID lpParam);
#else
static void * threadProc(void * pParam);
#endif

class ThreadHelper
{
public:
	ThreadHelper(){_hThreadID = 0;}
	virtual ~ThreadHelper(){}
public:
	bool start();
	bool wait();
	virtual void run() = 0;
private:
	unsigned long long _hThreadID;
#ifndef WIN32
	pthread_t _phtreadID;
#endif
};

#ifdef WIN32
unsigned int WINAPI  threadProc(LPVOID lpParam)
{
	ThreadHelper * p = (ThreadHelper *) lpParam;
	p->run();
	return 0;
}
#else
void * threadProc(void * pParam)
{
	ThreadHelper * p = (ThreadHelper *) pParam;
	p->run();
	return NULL;
}
#endif



//////////////////////////////////////////////////////////////////////////
//! LogerManager
//////////////////////////////////////////////////////////////////////////
class LogerManager : public ThreadHelper, public ILog4zManager
{
public:
	LogerManager();
	virtual ~LogerManager();

	//! 读取配置文件并覆写
	virtual bool config(const char* configPath);

	//! 覆写式创建
	virtual LoggerId createLogger(const char* loggerName, const char* path, int level, bool display, bool monthdir, unsigned int limitsize);
	virtual bool start();
	virtual bool stop();
	virtual bool prePushLog(LoggerId id, int level);
	virtual bool pushLog(LoggerId id, int level, const char * log);
	//! 查找ID
	virtual LoggerId findLogger(const char*  loggerName);
	virtual bool setLoggerLevel(LoggerId id, int nLevel);
	virtual bool setLoggerDisplay(LoggerId id, bool enable);
	virtual bool setLoggerMonthdir(LoggerId id, bool enable);
	virtual bool setLoggerLimitsize(LoggerId id, unsigned int limitsize);
	virtual bool updateConfig();
	virtual unsigned long long getStatusTotalWriteCount(){return _ullStatusTotalWriteFileCount;}
	virtual unsigned long long getStatusTotalWriteBytes(){return _ullStatusTotalWriteFileBytes;}
	virtual unsigned long long getStatusWaitingCount(){return _ullStatusTotalPushLog - _ullStatusTotalPopLog;}
	virtual unsigned int getStatusActiveLoggers();
protected:
	void showColorText(const char *text, int level = LOG_LEVEL_DEBUG);
	bool openLogger(LogData * log);
	bool closeLogger(LoggerId id);
	bool popLog(LogData *& log);
	virtual void run();
private:

	//! thread status.
	bool		_runing;
	//! wait thread started.
	SemHelper		_semaphore;

	//! config file name
	std::string _configFile;

	//! logger id manager, [logger name]:[logger id].
	std::map<std::string, LoggerId> _ids; 
	// the last used id of _loggers
	LoggerId	_lastId; 
	LoggerInfo _loggers[LOG4Z_LOGGER_MAX];

	//! log queue
	std::list<LogData *> _logs;
	LockHelper	_lock;

	//show color lock
	LockHelper _scLock;
	//status statistics
	//write file
	unsigned long long _ullStatusTotalWriteFileCount;
	unsigned long long _ullStatusTotalWriteFileBytes;

	//Log queue statistics
	unsigned long long _ullStatusTotalPushLog;
	unsigned long long _ullStatusTotalPopLog;

};




//////////////////////////////////////////////////////////////////////////
//! Log4zFileHandler
//////////////////////////////////////////////////////////////////////////

const std::string Log4zFileHandler::readContent()
{
	std::string content;

	if (!_file)
	{
		return content;
	}
	fseek(_file, 0, SEEK_SET);
	int beginpos = ftell(_file);
	fseek(_file, 0, SEEK_END);
	int endpos = ftell(_file);
	fseek(_file, 0, SEEK_SET);
	int filelen = endpos - beginpos;
	if (filelen > 10*1024*1024 || filelen <= 0)
	{
		return content;
	}
	content.resize(filelen+10);
	if (fread(&content[0], 1, filelen, _file) != (size_t)filelen)
	{
		content.clear();
		return content;
	}
	content = content.c_str();
	return content;
}




//////////////////////////////////////////////////////////////////////////
//! utility
//////////////////////////////////////////////////////////////////////////


void sleepMillisecondLine(unsigned int ms)
{
#ifdef WIN32
	::Sleep(ms);
#else
	usleep(1000*ms);
#endif
}

struct tm timeToTm(time_t t)
{
#ifdef WIN32
#if _MSC_VER < 1400 //VS2003
	return * localtime(&t);
#else //vs2005->vs2013->
	struct tm tt = { 0 };
	localtime_s(&tt, &t);
	return tt;
#endif
#else //linux
	struct tm tt = { 0 };
	localtime_r(&t, &tt);
	return tt;
#endif
}

bool isSameDay(time_t t1, time_t t2)
{
	tm tm1 = timeToTm(t1);
	tm tm2 = timeToTm(t2);
	if ( tm1.tm_year == tm2.tm_year
		&& tm1.tm_yday == tm2.tm_yday)
	{
		return true;
	}
	return false;
}


void fixPath(std::string &path)
{
	if (path.empty()){return;}
	for (std::string::iterator iter = path.begin(); iter != path.end(); ++iter)
	{
		if (*iter == '\\'){*iter = '/';}
	}
	if (path.at(path.length()-1) != '/'){path.append("/");}
}

static void trimLogConfig(std::string &str, std::string extIgnore)
{
	if (str.empty()){return;}
	extIgnore += "\r\n\t ";
	int length = (int)str.length();
	int posBegin = 0;
	int posEnd = 0;

	//trim utf8 file bom
	if (str.length() >= 3 
		&& (unsigned char)str[0] == 0xef
		&& (unsigned char)str[1] == 0xbb
		&& (unsigned char)str[2] == 0xbf)
	{
		posBegin = 3;
	}

	//trim character 
	for (int i = posBegin; i<length; i++)
	{
		bool bCheck = false;
		for (int j = 0; j < (int)extIgnore.length(); j++)
		{
			if (str[i] == extIgnore[j])
			{
				bCheck = true;
			}
		}
		if (bCheck)
		{
			if (i == posBegin)
			{
				posBegin++;
			}
		}
		else
		{
			posEnd = i + 1;
		}
	}
	if (posBegin < posEnd)
	{
		str = str.substr(posBegin, posEnd-posBegin);
	}
	else
	{
		str.clear();
	}
}

//split
static std::pair<std::string, std::string> splitPairString(const std::string & str, const std::string & delimiter)
{
	std::string::size_type pos = str.find(delimiter.c_str());
	if (pos == std::string::npos)
	{
		return std::make_pair(str, "");
	}
	return std::make_pair(str.substr(0, pos), str.substr(pos+delimiter.length()));
}

static bool parseConfig(const std::string& file, std::map<std::string, LoggerInfo> & outInfo)
{
	//! read file content
	Log4zFileHandler f;
	f.open(file.c_str(), "r");
	if (!f.isOpen())
	{
		return false;
	}

	std::string curLoggerName;
	int curLineNum = 0;
	std::pair<std::string, std::string> kv;
	
	do 
	{
		kv = splitPairString(f.readLine(), "=");
		curLineNum++;
		if (kv.first.empty())
		{
			break;
		}
		
		trimLogConfig(kv.first);
		trimLogConfig(kv.second);
		if (kv.first.empty() || kv.first.at(0) == '#')
		{
			continue;
		}

		if (kv.first.at(0) == '[')
		{
			trimLogConfig(kv.first, "[]");
			curLoggerName = kv.first;
			{
				std::string tmpstr = kv.first;
				std::transform(tmpstr.begin(), tmpstr.end(), tmpstr.begin(), ::tolower);
				if (tmpstr == "main")
				{
					curLoggerName = "Main";
				}
			}
			std::map<std::string, LoggerInfo>::iterator iter = outInfo.find(curLoggerName);
			if (iter == outInfo.end())
			{
				LoggerInfo li;
				li.setDefaultInfo();
				li._name = curLoggerName;
				outInfo.insert(std::make_pair(li._name, li));
			}
			else
			{
				std::cout << "log4z configure warning: dumplicate logger name:["<< curLoggerName << "] at line:" << curLineNum << std::endl;
			}
			continue;
		}
		trimLogConfig(kv.first);
		trimLogConfig(kv.second);
		std::map<std::string, LoggerInfo>::iterator iter = outInfo.find(curLoggerName);
		if (iter == outInfo.end())
		{
			std::cout << "log4z configure warning: not found current logger name:["<< curLoggerName << "] at line:" << curLineNum 
				<< ", key=" <<kv.first << ", value=" << kv.second << std::endl;
			continue;
		}
		std::transform(kv.first.begin(), kv.first.end(), kv.first.begin(), ::tolower);
		//! path
		if (kv.first == "path")
		{
			iter->second._path = kv.second;
			continue;
		}
		std::transform(kv.second.begin(), kv.second.end(), kv.second.begin(), ::tolower);
		//! level
		if (kv.first == "level")
		{
			if (kv.second == "trace" || kv.second == "all")
			{
				iter->second._level = LOG_LEVEL_TRACE;
			}
			else if (kv.second == "debug")
			{
				iter->second._level = LOG_LEVEL_DEBUG;
			}
			else if (kv.second == "info")
			{
				iter->second._level = LOG_LEVEL_INFO;
			}
			else if (kv.second == "warn" || kv.second == "warning")
			{
				iter->second._level = LOG_LEVEL_WARN;
			}
			else if (kv.second == "error")
			{
				iter->second._level = LOG_LEVEL_ERROR;
			}
			else if (kv.second == "alarm")
			{
				iter->second._level = LOG_LEVEL_ALARM;
			}
			else if (kv.second == "fatal")
			{
				iter->second._level = LOG_LEVEL_FATAL;
			}
		}
		//! display
		else if (kv.first == "display")
		{
			if (kv.second == "false" || kv.second == "0")
			{
				iter->second._display = false;
			}
			else
			{
				iter->second._display = true;
			}
		}
		//! monthdir
		else if (kv.first == "monthdir")
		{
			if (kv.second == "false" || kv.second == "0")
			{
				iter->second._monthdir = false;
			}
			else
			{
				iter->second._monthdir = true;
			}
		}			
		//! limit file size
		else if (kv.first == "limitsize")
		{
			iter->second._limitsize = atoi(kv.second.c_str());
		}			

	} while (1);
	return true;
}



bool isDirectory(std::string path)
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
}



bool createRecursionDir(std::string path)
{
	if (path.length() == 0) return true;
	std::string sub;
	fixPath(path);

	std::string::size_type pos = path.find('/');
	while (pos != std::string::npos)
	{
		std::string cur = path.substr(0, pos-0);
		if (cur.length() > 0 && !isDirectory(cur))
		{
			bool ret = false;
#ifdef WIN32
			ret = CreateDirectoryA(cur.c_str(), NULL) ? true : false;
#else
			ret = (mkdir(cur.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == 0);
#endif
			if (!ret)
			{
				return false;
			}
		}
		pos = path.find('/', pos+1);
	}

	return true;
}

void getProcessInfo(std::string &name, std::string &pid)
{
	name = "MainLog";
	pid = "0";
#ifdef WIN32
	
	char buf[260] = {0};
	if (GetModuleFileNameA(NULL, buf, 259) > 0)
	{
		name = buf;
	}
	std::string::size_type pos = name.rfind("\\");
	if (pos != std::string::npos)
	{
		name = name.substr(pos+1, std::string::npos);
	}
	pos = name.rfind(".");
	if (pos != std::string::npos)
	{
		name = name.substr(0, pos-0);
	}
	DWORD pidd = GetCurrentProcessId();
	sprintf(buf, "%06d", pidd);
	pid = buf;
#else
	pid_t id = getpid();
	char buf[260];
	sprintf(buf, "/proc/%d/cmdline", (int)id);
	Log4zFileHandler i;
	i.open(buf, "r");
	if (!i.isOpen())
	{
		return ;
	}
	name = i.readLine();
	i.close();

	std::string::size_type pos = name.rfind("/");
	if (pos != std::string::npos)
	{
		name = name.substr(pos+1, std::string::npos);
	}
	sprintf(buf, "%06d", id);
	pid = buf;
#endif
}







//////////////////////////////////////////////////////////////////////////
// LockHelper
//////////////////////////////////////////////////////////////////////////
LockHelper::LockHelper()
{
#ifdef WIN32
	InitializeCriticalSection(&_crit);
#else
	//_crit = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&_crit, &attr);
	pthread_mutexattr_destroy(&attr);
#endif
}
LockHelper::~LockHelper()
{
#ifdef WIN32
	DeleteCriticalSection(&_crit);
#else
	pthread_mutex_destroy(&_crit);
#endif
}

void LockHelper::lock()
{
#ifdef WIN32
	EnterCriticalSection(&_crit);
#else
	pthread_mutex_lock(&_crit);
#endif
}
void LockHelper::unLock()
{
#ifdef WIN32
	LeaveCriticalSection(&_crit);
#else
	pthread_mutex_unlock(&_crit);
#endif
}
//////////////////////////////////////////////////////////////////////////
// SemHelper
//////////////////////////////////////////////////////////////////////////
SemHelper::SemHelper()
{
#ifdef WIN32
	_hSem = NULL;
#else
	_isCreate = false;
#endif
}
SemHelper::~SemHelper()
{
#ifdef WIN32
	if (_hSem != NULL)
	{
		CloseHandle(_hSem);
		_hSem = NULL;
	}
#else
	if (_isCreate)
	{
		_isCreate = false;
		sem_destroy(&_semid);
	}
#endif
}

bool SemHelper::create(int initcount)
{
	if (initcount < 0)
	{
		initcount = 0;
	}
#ifdef WIN32
	if (initcount > 64)
	{
		return false;
	}
	_hSem = CreateSemaphore(NULL, initcount, 64, NULL);
	if (_hSem == NULL)
	{
		return false;
	}
#else
	if (sem_init(&_semid, 0, initcount) != 0)
	{
		return false;
	}
	_isCreate = true;
#endif
	return true;
}
bool SemHelper::wait(int timeout)
{
#ifdef WIN32
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	if (WaitForSingleObject(_hSem, timeout) != WAIT_OBJECT_0)
	{
		return false;
	}
#else
	if (timeout <= 0)
	{
		return (sem_wait(&_semid) == 0);
	}
	else
	{
		struct timeval tm;
		gettimeofday(&tm, NULL);
		long long endtime = tm.tv_sec *1000 + tm.tv_usec/1000 + timeout;
		do 
		{
			sleepMillisecondLine(50);
			int ret = sem_trywait(&_semid);
			if (ret == 0)
			{
				return true;
			}
			struct timeval tv_cur;
			gettimeofday(&tv_cur, NULL);
			if (tv_cur.tv_sec*1000 + tv_cur.tv_usec/1000 > endtime)
			{
				return false;
			}
			
			if (ret == -1 && errno == EAGAIN)
			{
				continue;
			}
			else
			{
				return false;
			}
		} while (true);
		return false;
	}
#endif
	return true;
}

bool SemHelper::post()
{
#ifdef WIN32
	return ReleaseSemaphore(_hSem, 1, NULL) ? true : false;
#else
	return (sem_post(&_semid) == 0);
#endif
}

//////////////////////////////////////////////////////////////////////////
//! ThreadHelper
//////////////////////////////////////////////////////////////////////////
bool ThreadHelper::start()
{
#ifdef WIN32
	unsigned long long ret = _beginthreadex(NULL, 0, threadProc, (void *) this, 0, NULL);

	if (ret == -1 || ret == 1  || ret == 0)
	{
		std::cout << "log4z: create log4z thread error! \r\n" <<std::endl;
		return false;
	}
	_hThreadID = ret;
#else
	int ret = pthread_create(&_phtreadID, NULL, threadProc, (void*)this);
	if (ret != 0)
	{
		std::cout <<"log4z: create log4z thread error! \r\n" << std::endl;
		return false;
	}
#endif
	return true;
}

bool ThreadHelper::wait()
{
#ifdef WIN32
	if (WaitForSingleObject((HANDLE)_hThreadID, INFINITE) != WAIT_OBJECT_0)
	{
		return false;
	}
#else
	if (pthread_join(_phtreadID, NULL) != 0)
	{
		return false;
	}
#endif
	return true;
}

//////////////////////////////////////////////////////////////////////////
//! LogerManager
//////////////////////////////////////////////////////////////////////////
LogerManager::LogerManager()
{
	_runing = false;
	_lastId = LOG4Z_MAIN_LOGGER_ID;
	getProcessInfo(_loggers[LOG4Z_MAIN_LOGGER_ID]._name, _loggers[LOG4Z_MAIN_LOGGER_ID]._pid);
	_ids[LOG4Z_MAIN_LOGGER_NAME] = LOG4Z_MAIN_LOGGER_ID;

	_ullStatusTotalPushLog = 0;
	_ullStatusTotalPopLog = 0;
	_ullStatusTotalWriteFileCount = 0;
	_ullStatusTotalWriteFileBytes = 0;
}
LogerManager::~LogerManager()
{
	stop();
}




void LogerManager::showColorText(const char *text, int level)
{
	if (level <= LOG_LEVEL_DEBUG || level > LOG_LEVEL_FATAL)
	{
		printf("%s", text);
		return;
	}
#ifndef WIN32
	printf("%s%s\e[0m", LOG_COLOR[level], text);
#else

	AutoLock l(_scLock);
	HANDLE hStd = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStd == INVALID_HANDLE_VALUE) return;
	CONSOLE_SCREEN_BUFFER_INFO oldInfo;
	if (!GetConsoleScreenBufferInfo(hStd, &oldInfo))
	{
		return;
	}
	else 
	{
		SetConsoleTextAttribute(hStd, LOG_COLOR[level]);
		printf("%s", text);
		SetConsoleTextAttribute(hStd, oldInfo.wAttributes);
	}
#endif
	return;
}


//! read configure and create with overwriting
bool LogerManager::config(const char* configPath)
{
	if (!_configFile.empty())
	{
		std::cout << " !!! !!! !!! !!!" << std::endl;
		std::cout << " !!! !!! log4z configure error: too many too call Config. the old config file=" << _configFile << ", the new config file=" << configPath << " !!! !!! " << std::endl;
		std::cout << " !!! !!! !!! !!!" << std::endl;
		return false;
	}
	_configFile = configPath;
	std::map<std::string, LoggerInfo> loggerMap;
	if (!parseConfig(configPath, loggerMap))
	{
		std::cout << " !!! !!! !!! !!!" << std::endl;
		std::cout << " !!! !!! log4z load config file error. filename=" << configPath << " !!! !!! " << std::endl;
		std::cout << " !!! !!! !!! !!!" << std::endl;
		return false;
	}
	for (std::map<std::string, LoggerInfo>::iterator iter = loggerMap.begin(); iter != loggerMap.end(); ++iter)
	{
		createLogger(iter->second._name.c_str(), 
			iter->second._path.c_str(), 
			iter->second._level, 
			iter->second._display, 
			iter->second._monthdir,
			iter->second._limitsize);
	}
	return true;
}

//! create with overwriting
LoggerId LogerManager::createLogger(const char* loggerName, const char* path, int nLevel, bool display, bool monthdir, unsigned int limitsize)
{
	std::string _tmp;
	std::string _pid;
	getProcessInfo(_tmp, _pid);
	std::string name = loggerName;
	std::string pathname = path;
	if (name.length() == 0)
	{
		showColorText("log4z: create logger error, name is empty ! \r\n", LOG_LEVEL_FATAL);
		return -1;
	}
	trimLogConfig(pathname);
	fixPath(pathname);

	LoggerId newID = -1;
	{
		std::map<std::string, LoggerId>::iterator iter = _ids.find(name);
		if (iter != _ids.end())
		{
			newID = iter->second;
		}
	}
	if (newID == -1)
	{
		if (_lastId +1 >= LOG4Z_LOGGER_MAX)
		{
			showColorText("log4z: CreateLogger can not create|writeover, because loggerid need < LOGGER_MAX! \r\n", LOG_LEVEL_FATAL);
			return -1;
		}
		newID = ++ _lastId;
		_ids[name] = newID;
	}

	if (!pathname.empty())
	{
		_loggers[newID]._path = pathname;
	}

	if (newID > LOG4Z_MAIN_LOGGER_ID)
	{
		_loggers[newID]._name = name;
	}
	_loggers[newID]._pid = _pid;
	_loggers[newID]._level = nLevel;
	_loggers[newID]._enable = true;
	_loggers[newID]._display = display;
	_loggers[newID]._monthdir = monthdir;
	_loggers[newID]._limitsize = limitsize;
	if (limitsize == 0)
	{
		_loggers[newID]._limitsize = 4000;
	}

	return newID;
}


bool LogerManager::start()
{
	if (_runing)
	{
		return false;
	}
	_semaphore.create(0);
	bool ret = ThreadHelper::start();
	return ret && _semaphore.wait(3000);
}
bool LogerManager::stop()
{
	if (_runing == true)
	{
		_runing = false;
		wait();
		return true;
	}
	return false;
}
bool LogerManager::prePushLog(LoggerId id, int level)
{
	if (id < 0 || id >= LOG4Z_LOGGER_MAX)
	{
		return false;
	}
	if (!_runing || !_loggers[id]._enable)
	{
		return false;
	}
	if (level < _loggers[id]._level)
	{
		return false;
	}
	return true;
}
bool LogerManager::pushLog(LoggerId id, int level, const char * log)
{
	if (id < 0 || id >= LOG4Z_LOGGER_MAX)
	{
		return false;
	}
	if (!_runing || !_loggers[id]._enable)
	{
		return false;
	}
	if (level < _loggers[id]._level)
	{
		return false;
	}

	LogData * pLog = new LogData;
	pLog->_id =id;
	pLog->_level = level;

	{
#ifdef WIN32
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		unsigned long long now = ft.dwHighDateTime;
		now <<= 32;
		now |= ft.dwLowDateTime;
		now /=10;
		now -=11644473600000000ULL;
		now /=1000;
		pLog->_time = now/1000;
		pLog->_precise = (unsigned int)(now%1000);
#else
		struct timeval tm;
		gettimeofday(&tm, NULL);
		pLog->_time = tm.tv_sec;
		pLog->_precise = tm.tv_usec/1000;
#endif
	}
	{
		tm tt = timeToTm(pLog->_time);
#ifdef WIN32
		int ret = _snprintf_s(pLog->_content, LOG4Z_LOG_BUF_SIZE, _TRUNCATE, "%d-%02d-%02d %02d:%02d:%02d.%03d %s %s \r\n",
			tt.tm_year + 1900, tt.tm_mon + 1, tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec, pLog->_precise,
			LOG_STRING[pLog->_level], log);
		if (ret == -1)
		{
			ret = LOG4Z_LOG_BUF_SIZE - 1;
		}
		pLog->_contentLen = ret;
#else
		int ret = snprintf(pLog->_content, LOG4Z_LOG_BUF_SIZE, "%d-%02d-%02d %02d:%02d:%02d.%03d %s %s \r\n",
			tt.tm_year + 1900, tt.tm_mon + 1, tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec, pLog->_precise,
			LOG_STRING[pLog->_level], log);
		if (ret == -1)
		{
			ret = 0;
		}
		if (ret >= LOG4Z_LOG_BUF_SIZE)
		{
			ret = LOG4Z_LOG_BUF_SIZE-1;
		}
		
		pLog->_contentLen = ret;
#endif
		if (pLog->_contentLen >= 2)
		{
			pLog->_content[pLog->_contentLen - 2] = '\r';
			pLog->_content[pLog->_contentLen - 1] = '\n';
		}
	
	}

	if (_loggers[pLog->_id]._display && LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
		showColorText(pLog->_content, pLog->_level);
	}

	if (LOG4Z_ALL_DEBUGOUTPUT_DISPLAY && LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
#ifdef WIN32
		OutputDebugStringA(pLog->_content);
#endif
	}

	if (LOG4Z_ALL_WRITE_TO_FILE && LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
		AutoLock l(_lock);
		if (openLogger(pLog))
		{
			_loggers[pLog->_id]._handle.write(pLog->_content, pLog->_contentLen);
			closeLogger(pLog->_id);
			_ullStatusTotalWriteFileCount++;
			_ullStatusTotalWriteFileBytes += pLog->_contentLen;
		}
	}

	if (LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
		delete pLog;
		return true;
	}
	
	AutoLock l(_lock);
	_logs.push_back(pLog);
	_ullStatusTotalPushLog ++;
	return true;
}

//! 查找ID
LoggerId LogerManager::findLogger(const char * loggerName)
{
	std::map<std::string, LoggerId>::iterator iter;
	iter = _ids.find(loggerName);
	if (iter != _ids.end())
	{
		return iter->second;
	}
	return LOG4Z_INVALID_LOGGER_ID;
}

bool LogerManager::setLoggerLevel(LoggerId id, int level)
{
	if (id <0 || id >= LOG4Z_LOGGER_MAX || level < LOG_LEVEL_TRACE || level >LOG_LEVEL_FATAL) return false;
	_loggers[id]._level = level;
	return true;
}
bool LogerManager::setLoggerDisplay(LoggerId id, bool enable)
{
	if (id <0 || id >= LOG4Z_LOGGER_MAX) return false;
	_loggers[id]._display = enable;
	return true;
}
bool LogerManager::setLoggerMonthdir(LoggerId id, bool enable)
{
	if (id <0 || id >= LOG4Z_LOGGER_MAX) return false;
	_loggers[id]._monthdir = enable;
	return true;
}
bool LogerManager::setLoggerLimitsize(LoggerId id, unsigned int limitsize)
{
	if (id <0 || id >= LOG4Z_LOGGER_MAX) return false;
	if (limitsize == 0 ) {limitsize = (unsigned int)-1;}
	_loggers[id]._limitsize = limitsize;
	return true;
}
bool LogerManager::updateConfig()
{
	if (_configFile.empty())
	{
		LOGW("log4z update config file error. filename is empty.");
		return false;
	}
	std::map<std::string, LoggerInfo> loggerMap;
	if (!parseConfig(_configFile, loggerMap))
	{
		LOGW(" !!! !!! !!! !!!");
		LOGW(" !!! !!! log4z update config file error. filename=" << _configFile << " !!! !!! ");
		LOGW(" !!! !!! !!! !!!");
		return false;
	}
	for (std::map<std::string, LoggerInfo>::iterator iter = loggerMap.begin(); iter != loggerMap.end(); ++iter)
	{
		LoggerId id = findLogger(iter->first.c_str());
		if (id != LOG4Z_INVALID_LOGGER_ID)
		{
			setLoggerDisplay(id, iter->second._display);
			setLoggerLevel(id, iter->second._level);
			setLoggerMonthdir(id, iter->second._monthdir);
			setLoggerLimitsize(id, iter->second._limitsize);
		}
	}
	return true;
}

unsigned int LogerManager::getStatusActiveLoggers()
{
	unsigned int actives = 0;
	for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
	{
		if (_loggers[i]._enable)
		{
			actives ++;
		}
	}
	return actives;
}


bool LogerManager::openLogger(LogData * pLog)
{
	int id = pLog->_id;
	if (id < 0 || id >_lastId)
	{
		showColorText("log4z: openLogger can not open, invalide logger id! \r\n", LOG_LEVEL_FATAL);
		return false;
	}

	LoggerInfo * pLogger = &_loggers[id];
	if (!pLogger->_enable || pLog->_level < pLogger->_level)
	{
		return false;
	}

	bool sameday = isSameDay(pLog->_time, pLogger->_curFileCreateTime);
	bool needChageFile = pLogger->_curWriteLen > pLogger->_limitsize * 1024 * 1024;
	if (!sameday || needChageFile)
	{
		if (!sameday)
		{
			pLogger->_curFileIndex = 0;
			pLogger->_curWriteLen = 0;
			pLogger->_curFileCreateTime = pLog->_time;
		}
		else if (needChageFile)
		{
			pLogger->_curFileIndex++;
			pLogger->_curWriteLen = 0;
		}
		if (pLogger->_handle.isOpen())
		{
			pLogger->_handle.close();
		}
	}
	if (!pLogger->_handle.isOpen())
	{
		
		tm t = timeToTm(pLogger->_curFileCreateTime);
		std::string path = pLogger->_path;
		char buf[100] = { 0 };
		if (pLogger->_monthdir)
		{
			sprintf(buf, "%04d_%02d/", t.tm_year + 1900, t.tm_mon + 1);
			path += buf;
		}

		if (!isDirectory(path))
		{
			createRecursionDir(path);
		}

		sprintf(buf, "%s_%04d%02d%02d%02d%02d_%s_%03d.log",
			pLogger->_name.c_str(), t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
			t.tm_hour, t.tm_min, pLogger->_pid.c_str(), pLogger->_curFileIndex);
		path += buf;
		pLogger->_handle.open(path.c_str(), "ab");
		return pLogger->_handle.isOpen();
	}
	return true;
}
bool LogerManager::closeLogger(LoggerId id)
{
	if (id < 0 || id >_lastId)
	{
		showColorText("log4z: closeLogger can not close, invalide logger id! \r\n", LOG_LEVEL_FATAL);
		return false;
	}
	LoggerInfo * pLogger = &_loggers[id];
	if (pLogger->_handle.isOpen())
	{
		pLogger->_handle.close();
		return true;
	}
	return false;
}
bool LogerManager::popLog(LogData *& log)
{
	AutoLock l(_lock);
	if (_logs.empty())
	{
		return false;
	}
	log = _logs.front();
	_logs.pop_front();
	return true;
}

void LogerManager::run()
{
	_runing = true;
	_loggers[LOG4Z_MAIN_LOGGER_ID]._enable = true;

	pushLog(0, LOG_LEVEL_ALARM, "-----------------  log4z thread started!   ----------------------------");
	for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
	{
		if (_loggers[i]._enable)
		{
			std::stringstream ss;
			ss <<"logger id=" <<i 
				<<" path=" <<_loggers[i]._path
				<<" name=" <<_loggers[i]._name
				<<" level=" << _loggers[i]._level
				<<" display=" << _loggers[i]._display;
			pushLog(0, LOG_LEVEL_ALARM, ss.str().c_str());
		}
	}

	_semaphore.post();


	LogData * pLog = NULL;
	int needFlush[LOG4Z_LOGGER_MAX] = {0};
	while (true)
	{
		while(popLog(pLog))
		{
			//
			_ullStatusTotalPopLog ++;
			//discard
			LoggerInfo & curLogger = _loggers[pLog->_id];
			if (!curLogger._enable || pLog->_level <curLogger._level  )
			{
				delete pLog;
				pLog = NULL;
				continue;
			}


			if (curLogger._display && !LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
				showColorText(pLog->_content, pLog->_level);
			}
			if (LOG4Z_ALL_DEBUGOUTPUT_DISPLAY && !LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
#ifdef WIN32
				OutputDebugStringA(pLog->_content);
#endif
			}


			if (LOG4Z_ALL_WRITE_TO_FILE && !LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
				if (!openLogger(pLog))
				{
					delete pLog;
					pLog = NULL;
					continue;
				}

				curLogger._handle.write(pLog->_content, pLog->_contentLen);
				curLogger._curWriteLen += (unsigned int)pLog->_contentLen;
				needFlush[pLog->_id] ++;
				_ullStatusTotalWriteFileCount++;
				_ullStatusTotalWriteFileBytes += pLog->_contentLen;
			}
			else if (!LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
				_ullStatusTotalWriteFileCount++;
				_ullStatusTotalWriteFileBytes += pLog->_contentLen;
			}

			delete pLog;
			pLog = NULL;
		}

		for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
		{
			if (_loggers[i]._enable && needFlush[i] > 0)
			{
				_loggers[i]._handle.flush();
				needFlush[i] = 0;
			}
		}

		//! delay. 
		sleepMillisecondLine(100);

		//! quit
		if (!_runing && _logs.empty())
		{
			break;
		}

	}

	for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
	{
		if (_loggers[i]._enable)
		{
			_loggers[i]._enable = false;
			closeLogger(i);
		}
	}

}

//////////////////////////////////////////////////////////////////////////
//ILog4zManager::getInstance
//////////////////////////////////////////////////////////////////////////
ILog4zManager * ILog4zManager::getInstance()
{
	static LogerManager m;
	return &m;
}



_ZSUMMER_LOG4Z_END
_ZSUMMER_END

