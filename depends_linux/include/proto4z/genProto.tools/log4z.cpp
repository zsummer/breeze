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

//////////////////////////////////////////////////////////////////////////
//! CLog4zFile
//////////////////////////////////////////////////////////////////////////
class CLog4zFile
{
public:
	CLog4zFile();
	~CLog4zFile();
	bool IsOpen();
	bool Open(const char *path, const char * mod);
	void Close();
	void Write(const char * data, size_t len);
	void Flush();
	bool ReadLine(char *buf, int count);
	const std::string ReadContent();
public:
	FILE *m_file;
};


//////////////////////////////////////////////////////////////////////////
//! LogData
//////////////////////////////////////////////////////////////////////////
struct LogData
{
	LoggerId _id;		//dest logger id
	int	_level;	//log level
	time_t _time;		//create time
	unsigned int _precise;
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
	CLog4zFile	_handle;		//file handle.

	LoggerInfo()
	{
		SetDefaultInfo();
		_curFileCreateTime = 0;
		_curFileIndex = 0;
		_curWriteLen = 0;
	}
	void SetDefaultInfo()
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
static void SleepMillisecond(unsigned int ms);
static tm TimeToTm(time_t t);
static bool IsSameDay(time_t t1, time_t t2);

static void FixPath(std::string &path);
static void TrimLogConfig(std::string &str, char ignore = '\0');
static void ParseConfig(std::string file, std::map<std::string, LoggerInfo> & outInfo);

static bool IsDirectory(std::string path);
static bool CreateRecursionDir(std::string path);
void GetProcessInfo(std::string &name, std::string &pid);



//////////////////////////////////////////////////////////////////////////
//! CLock
//////////////////////////////////////////////////////////////////////////
class CLock
{
public:
	CLock();
	virtual ~CLock();

public:
	void Lock();
	void UnLock();
private:
#ifdef WIN32
	CRITICAL_SECTION m_crit;
#else
	pthread_mutex_t  m_crit;
#endif
};

//////////////////////////////////////////////////////////////////////////
//! CAutoLock
//////////////////////////////////////////////////////////////////////////
class CAutoLock
{
public:
	explicit CAutoLock(CLock & lk):m_lock(lk){m_lock.Lock();}
	~CAutoLock(){m_lock.UnLock();}
private:
	CLock & m_lock;
};

//////////////////////////////////////////////////////////////////////////
//! CSem
//////////////////////////////////////////////////////////////////////////
class CSem
{
public:
	CSem();
	virtual ~CSem();
public:
	bool Create(int initcount);
	bool Wait(int timeout = 0);
	bool Post();
private:
#ifdef WIN32
	HANDLE m_hSem;
#else
	sem_t m_semid;
	bool  m_bCreate;
#endif
};



//////////////////////////////////////////////////////////////////////////
//! CThread
//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
static unsigned int WINAPI  ThreadProc(LPVOID lpParam);
#else
static void * ThreadProc(void * pParam);
#endif

class CThread
{
public:
	CThread(){m_hThreadID = 0;}
	virtual ~CThread(){}
public:
	bool Start();
	bool Wait();
	virtual void Run() = 0;
private:
	unsigned long long m_hThreadID;
#ifndef WIN32
	pthread_t m_phtreadID;
#endif
};

#ifdef WIN32
unsigned int WINAPI  ThreadProc(LPVOID lpParam)
{
	CThread * p = (CThread *) lpParam;
	p->Run();
	return 0;
}
#else
void * ThreadProc(void * pParam)
{
	CThread * p = (CThread *) pParam;
	p->Run();
	return NULL;
}
#endif



//////////////////////////////////////////////////////////////////////////
//! CLogerManager
//////////////////////////////////////////////////////////////////////////
class CLogerManager : public CThread, public ILog4zManager
{
public:
	CLogerManager();
	virtual ~CLogerManager();

	virtual std::string GetExampleConfig();
	//! 读取配置文件并覆写
	virtual bool Config(const char* strCfgPath);

	//! 覆写式创建
	virtual LoggerId CreateLogger(const char* strName, const char* strPath, int nLevel, bool display, bool monthdir, unsigned int limitsize);
	virtual bool Start();
	virtual bool Stop();
	virtual bool PrePushLog(LoggerId id, int level);
	virtual bool PushLog(LoggerId id, int level, const char * log);
	//! 查找ID
	virtual LoggerId FindLogger(const char*  strName);
	virtual bool SetLoggerLevel(LoggerId nLoggerID, int nLevel);
	virtual bool SetLoggerDisplay(LoggerId nLoggerID, bool enable);
	virtual bool SetLoggerMonthdir(LoggerId nLoggerID, bool use);
	virtual bool SetLoggerLimitSize(LoggerId nLoggerID, unsigned int limitsize);
	virtual bool UpdateConfig();
	virtual unsigned long long GetStatusTotalWriteCount(){return m_ullStatusTotalWriteFileCount;}
	virtual unsigned long long GetStatusTotalWriteBytes(){return m_ullStatusTotalWriteFileBytes;}
	virtual unsigned long long GetStatusWaitingCount(){return m_ullStatusTotalPushLog - m_ullStatusTotalPopLog;}
	virtual unsigned int GetStatusActiveLoggers();
protected:
	void ShowColorText(const char *text, int level = LOG_LEVEL_DEBUG);
	bool OpenLogger(LogData * pLog);
	bool CloseLogger(LoggerId id);
	bool PopLog(LogData *& log);
	virtual void Run();
private:

	//! thread status.
	bool		m_bRuning;
	//! wait thread started.
	CSem		m_semaphore;

	//! config file name
	std::string m_configFile;

	//! logger id manager, [logger name]:[logger id].
	std::map<std::string, LoggerId> m_ids; 
	// the last used id of m_loggers
	LoggerId	m_lastId; 
	LoggerInfo m_loggers[LOG4Z_LOGGER_MAX];

	//! log queue
	std::list<LogData *> m_logs;
	CLock	m_lock;

	//show color lock
	CLock m_scLock;
	//status statistics
	//write file
	unsigned long long m_ullStatusTotalWriteFileCount;
	unsigned long long m_ullStatusTotalWriteFileBytes;

	//Log queue statistics
	unsigned long long m_ullStatusTotalPushLog;
	unsigned long long m_ullStatusTotalPopLog;

};




//////////////////////////////////////////////////////////////////////////
//! CLog4zFile
//////////////////////////////////////////////////////////////////////////

CLog4zFile::CLog4zFile()
{
	m_file = NULL;
}
CLog4zFile::~CLog4zFile()
{
	Close();
}
bool CLog4zFile::IsOpen()
{
	if (m_file)
	{
		return true;
	}
	return false;
}
bool CLog4zFile::Open(const char *path, const char * mod)
{
	if (m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
	m_file = fopen(path, mod);
	if (m_file == NULL)
	{
		return false;
	}
	return true;
}
void CLog4zFile::Close()
{
	if (m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
}
void CLog4zFile::Write(const char * data, size_t len)
{
	if (!m_file)
	{
		return;
	}
	if (len == 0)
	{
		return;
	}
	
	size_t wlen = fwrite(data, 1, len, m_file);
	if (wlen != len)
	{
		Close();
	}
}
void CLog4zFile::Flush()
{
	if (!m_file)
	{
		return;
	}
	fflush(m_file);
}
bool CLog4zFile::ReadLine(char *buf, int count)
{
	if (fgets(buf, count, m_file) == NULL)
	{
		return false;
	}
	return true;
}

const std::string CLog4zFile::ReadContent()
{
	std::string content;

	if (!m_file)
	{
		return content;
	}
	fseek(m_file, 0, SEEK_SET);
	int beginpos = ftell(m_file);
	fseek(m_file, 0, SEEK_END);
	int endpos = ftell(m_file);
	fseek(m_file, 0, SEEK_SET);
	int filelen = endpos - beginpos;
	if (filelen > 10*1024*1024 || filelen <= 0)
	{
		return content;
	}
	content.resize(filelen+10);
	if (fread(&content[0], 1, filelen, m_file) != (size_t)filelen)
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


void SleepMillisecond(unsigned int ms)
{
#ifdef WIN32
	::Sleep(ms);
#else
	usleep(1000*ms);
#endif
}

struct tm TimeToTm(time_t t)
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

bool IsSameDay(time_t t1, time_t t2)
{
	tm tm1 = TimeToTm(t1);
	tm tm2 = TimeToTm(t2);
	if ( tm1.tm_year == tm2.tm_year
		&& tm1.tm_yday == tm2.tm_yday)
	{
		return true;
	}
	return false;
}


void FixPath(std::string &path)
{
	if (path.empty())
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
	if (path.at(path.length()-1) != '/')
	{
		path += "/";
	}
}
static void TrimLogConfig(std::string &str, char ignore)
{
	if (str.empty())
	{
		return;
	}
	size_t endPos = str.length();
	int posBegin = (int)endPos;
	int posEnd = -1;

	for (size_t i = 0; i<str.length(); i++)
	{
		char ch = str[i];
		if (ch != '\r' && ch != '\n' && ch != ' ' && ch != '\t' && ch != ignore)
		{
			posBegin = (int)i;
			break;
		}
	}
	for (size_t i = endPos; i> 0; i--)
	{
		char ch = str[i-1];
		if (ch != '\r' && ch != '\n' && ch != ' ' && ch != '\t' && ch != ignore)
		{
			posEnd = (int)i-1;
			break;
		}
	}
	if (posBegin <= posEnd)
	{
		str = str.substr(posBegin, posEnd-posBegin+1);
	}
	else
	{
		str.clear();
	}
}

static void ParseConfig(std::string file, std::map<std::string, LoggerInfo> & outInfo)
{
	//! read file content
	{
		CLog4zFile f;
		f.Open(file.c_str(), "r");

		if (f.IsOpen())
		{
			std::string curLoggerName;
			int curLineNum = 0;
			char buf[500];
			std::string line;
			std::string key;
			std::string value;
			do 
			{
				memset(buf, 0, 500);
				if (!f.ReadLine(buf, 500-1))
				{
					break;
				}
				line = buf;
				curLineNum++;
				TrimLogConfig(line);

				if (line.empty())
				{
					continue;
				}
				if (*(line.begin()) == '#')
				{
					continue;
				}
				if (*(line.begin()) == '[')
				{
					TrimLogConfig(line, '[');
					TrimLogConfig(line, ']');
					curLoggerName = line;
					{
						std::string tmpstr = line;
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
						li.SetDefaultInfo();
						li._name = curLoggerName;
						outInfo.insert(std::make_pair(li._name, li));
					}
					else
					{
						std::cout << "log4z configure warning: dumplicate logger name:["<< curLoggerName << "] at line:" << curLineNum << std::endl;
					}
					continue;
				}
				size_t pos = line.find_first_of('=');
				if (pos == std::string::npos)
				{
					std::cout << "log4z configure warning: unresolved line:["<< line << "] at line:" << curLineNum << std::endl;
					continue;
				}
				key = line.substr(0, pos);
				value = line.substr(pos+1);
				TrimLogConfig(key);
				TrimLogConfig(value);
				std::map<std::string, LoggerInfo>::iterator iter = outInfo.find(curLoggerName);
				if (iter == outInfo.end())
				{
					std::cout << "log4z configure warning: not found current logger name:["<< curLoggerName << "] at line:" << curLineNum 
						<< ", key=" <<key << ", value=" << value << std::endl;
					continue;
				}
				std::transform(key.begin(), key.end(), key.begin(), ::tolower);
				//! path
				if (key == "path")
				{
					iter->second._path = value;
					continue;
				}
				std::transform(value.begin(), value.end(), value.begin(), ::tolower);
				//! level
				if (key == "level")
				{
					if (value == "trace" || value == "all")
					{
						iter->second._level = LOG_LEVEL_TRACE;
					}
					else if (value == "debug")
					{
						iter->second._level = LOG_LEVEL_DEBUG;
					}
					else if (value == "info")
					{
						iter->second._level = LOG_LEVEL_INFO;
					}
					else if (value == "warn" || value == "warning")
					{
						iter->second._level = LOG_LEVEL_WARN;
					}
					else if (value == "error")
					{
						iter->second._level = LOG_LEVEL_ERROR;
					}
					else if (value == "alarm")
					{
						iter->second._level = LOG_LEVEL_WARN;
					}
					else if (value == "fatal")
					{
						iter->second._level = LOG_LEVEL_FATAL;
					}
				}
				//! display
				else if (key == "display")
				{
					if (value == "false" || value == "0")
					{
						iter->second._display = false;
					}
					else
					{
						iter->second._display = true;
					}
				}
				//! monthdir
				else if (key == "monthdir")
				{
					if (value == "false" || value == "0")
					{
						iter->second._monthdir = false;
					}
					else
					{
						iter->second._monthdir = true;
					}
				}			
				//! limit file size
				else if (key == "limitsize")
				{
					iter->second._limitsize = atoi(value.c_str());
				}			

			} while (1);
		}
	}
}



bool IsDirectory(std::string path)
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



bool CreateRecursionDir(std::string path)
{
	if (path.length() == 0) return true;
	std::string sub;
	FixPath(path);

	std::string::size_type pos = path.find('/');
	while (pos != std::string::npos)
	{
		std::string cur = path.substr(0, pos-0);
		if (cur.length() > 0 && !IsDirectory(cur))
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

void GetProcessInfo(std::string &name, std::string &pid)
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
	CLog4zFile i;
	i.Open(buf, "r");
	if (!i.IsOpen())
	{
		return ;
	}
	if (i.ReadLine(buf, 259))
	{
		name = buf;
	}
	i.Close();

	std::string::size_type pos = name.rfind("/");
	if (pos != std::string::npos)
	{
		name = name.substr(pos+1, std::string::npos);
	}
	sprintf(buf, "%06d", id);
	pid = buf;
#endif
}



#ifdef WIN32
const static WORD cs_sColor[LOG_LEVEL_FATAL+1] = {
	0,
	0,
	FOREGROUND_BLUE|FOREGROUND_GREEN,
	FOREGROUND_GREEN|FOREGROUND_RED,
	FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_RED|FOREGROUND_BLUE};
#else

const static char cs_strColor[LOG_LEVEL_FATAL+1][50] = { 
	"\e[0m",
	"\e[0m",
	"\e[34m\e[1m",//hight blue
	"\e[33m", //yellow
	"\e[31m", //red
	"\e[32m", //green
	"\e[35m"};
#endif



//////////////////////////////////////////////////////////////////////////
// CLock
//////////////////////////////////////////////////////////////////////////
CLock::CLock()
{
#ifdef WIN32
	InitializeCriticalSection(&m_crit);
#else
	//m_crit = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_crit, &attr);
	pthread_mutexattr_destroy(&attr);
#endif
}
CLock::~CLock()
{
#ifdef WIN32
	DeleteCriticalSection(&m_crit);
#else
	pthread_mutex_destroy(&m_crit);
#endif
}

void CLock::Lock()
{
#ifdef WIN32
	EnterCriticalSection(&m_crit);
#else
	pthread_mutex_lock(&m_crit);
#endif
}
void CLock::UnLock()
{
#ifdef WIN32
	LeaveCriticalSection(&m_crit);
#else
	pthread_mutex_unlock(&m_crit);
#endif
}
//////////////////////////////////////////////////////////////////////////
// CSem
//////////////////////////////////////////////////////////////////////////
CSem::CSem()
{
#ifdef WIN32
	m_hSem = NULL;
#else
	m_bCreate = false;
#endif
}
CSem::~CSem()
{
#ifdef WIN32
	if (m_hSem != NULL)
	{
		CloseHandle(m_hSem);
		m_hSem = NULL;
	}
#else
	if (m_bCreate)
	{
		m_bCreate = false;
		sem_destroy(&m_semid);
	}
#endif
}

bool CSem::Create(int initcount)
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
	m_hSem = CreateSemaphore(NULL, initcount, 64, NULL);
	if (m_hSem == NULL)
	{
		return false;
	}
#else
	if (sem_init(&m_semid, 0, initcount) != 0)
	{
		return false;
	}
	m_bCreate = true;
#endif
	return true;
}
bool CSem::Wait(int timeout)
{
#ifdef WIN32
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	if (WaitForSingleObject(m_hSem, timeout) != WAIT_OBJECT_0)
	{
		return false;
	}
#else
	if (timeout <= 0)
	{
		return (sem_wait(&m_semid) == 0);
	}
	else
	{
		struct timeval tm;
		gettimeofday(&tm, NULL);
		long long endtime = tm.tv_sec *1000 + tm.tv_usec/1000 + timeout;
		do 
		{
			SleepMillisecond(50);
			int ret = sem_trywait(&m_semid);
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

bool CSem::Post()
{
#ifdef WIN32
	return ReleaseSemaphore(m_hSem, 1, NULL) ? true : false;
#else
	return (sem_post(&m_semid) == 0);
#endif
}

//////////////////////////////////////////////////////////////////////////
//! CThread
//////////////////////////////////////////////////////////////////////////
bool CThread::Start()
{
#ifdef WIN32
	unsigned long long ret = _beginthreadex(NULL, 0, ThreadProc, (void *) this, 0, NULL);

	if (ret == -1 || ret == 1  || ret == 0)
	{
		std::cout << "log4z: create log4z thread error! \r\n" <<std::endl;
		return false;
	}
	m_hThreadID = ret;
#else
	int ret = pthread_create(&m_phtreadID, NULL, ThreadProc, (void*)this);
	if (ret != 0)
	{
		std::cout <<"log4z: create log4z thread error! \r\n" << std::endl;
		return false;
	}
#endif
	return true;
}

bool CThread::Wait()
{
#ifdef WIN32
	if (WaitForSingleObject((HANDLE)m_hThreadID, INFINITE) != WAIT_OBJECT_0)
	{
		return false;
	}
#else
	if (pthread_join(m_phtreadID, NULL) != 0)
	{
		return false;
	}
#endif
	return true;
}

//////////////////////////////////////////////////////////////////////////
//! CLogerManager
//////////////////////////////////////////////////////////////////////////
CLogerManager::CLogerManager()
{
	m_bRuning = false;
	m_lastId = LOG4Z_MAIN_LOGGER_ID;
	GetProcessInfo(m_loggers[LOG4Z_MAIN_LOGGER_ID]._name, m_loggers[LOG4Z_MAIN_LOGGER_ID]._pid);
	m_ids[LOG4Z_MAIN_LOGGER_NAME] = LOG4Z_MAIN_LOGGER_ID;

	m_ullStatusTotalPushLog = 0;
	m_ullStatusTotalPopLog = 0;
	m_ullStatusTotalWriteFileCount = 0;
	m_ullStatusTotalWriteFileBytes = 0;
}
CLogerManager::~CLogerManager()
{
	Stop();
}

std::string CLogerManager::GetExampleConfig()
{
	return ""
		"[FileConfig]\n"
		"#path=./log/\n"
		"#level=DEBUG\n"
		"#display=true\n"
		"#monthdir=false\n"
		"#limit=100\n";
}


void CLogerManager::ShowColorText(const char *text, int level)
{
	if (level <= LOG_LEVEL_DEBUG || level > LOG_LEVEL_FATAL)
	{
		printf("%s", text);
		return;
	}
#ifndef WIN32
	printf("%s%s\e[0m", cs_strColor[level], text);
#else

	CAutoLock l(m_scLock);
	HANDLE hStd = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStd == INVALID_HANDLE_VALUE) return;
	CONSOLE_SCREEN_BUFFER_INFO oldInfo;
	if (!GetConsoleScreenBufferInfo(hStd, &oldInfo))
	{
		return;
	}
	else 
	{
		SetConsoleTextAttribute(hStd, cs_sColor[level]);
		printf("%s", text);
		SetConsoleTextAttribute(hStd, oldInfo.wAttributes);
	}
#endif
	return;
}


//! 读取配置文件并覆写
bool CLogerManager::Config(const char* strCfgPath)
{
	if (!m_configFile.empty())
	{
		std::cout << "log4z configure error: too many too call Config. the old config file=" << m_configFile << ", the new config file=" << strCfgPath << std::endl;
		return false;
	}
	m_configFile = strCfgPath;
	std::map<std::string, LoggerInfo> loggerMap;
	ParseConfig(strCfgPath, loggerMap);
	for (std::map<std::string, LoggerInfo>::iterator iter = loggerMap.begin(); iter != loggerMap.end(); ++iter)
	{
		CreateLogger(iter->second._name.c_str(), 
			iter->second._path.c_str(), 
			iter->second._level, 
			iter->second._display, 
			iter->second._monthdir,
			iter->second._limitsize);
	}
	return true;
}

//! 覆写式创建
LoggerId CLogerManager::CreateLogger(const char* strName, const char* strPath, int nLevel, bool display, bool monthdir, unsigned int limitsize)
{
	std::string _tmp;
	std::string _pid;
	GetProcessInfo(_tmp, _pid);
	std::string name = strName;
	std::string path = strPath;
	if (name.length() == 0)
	{
		ShowColorText("log4z: create logger error, name is empty ! \r\n", LOG_LEVEL_FATAL);
		return -1;
	}
	TrimLogConfig(path);
	FixPath(path);

	LoggerId newID = -1;
	{
		std::map<std::string, LoggerId>::iterator iter = m_ids.find(name);
		if (iter != m_ids.end())
		{
			newID = iter->second;
		}
	}
	if (newID == -1)
	{
		if (m_lastId +1 >= LOG4Z_LOGGER_MAX)
		{
			ShowColorText("log4z: CreateLogger can not create|writeover, because loggerid need < LOGGER_MAX! \r\n", LOG_LEVEL_FATAL);
			return -1;
		}
		newID = ++ m_lastId;
		m_ids[name] = newID;
	}

	if (!path.empty())
	{
		m_loggers[newID]._path = path;
	}

	if (newID > LOG4Z_MAIN_LOGGER_ID)
	{
		m_loggers[newID]._name = name;
	}
	m_loggers[newID]._pid = _pid;
	m_loggers[newID]._level = nLevel;
	m_loggers[newID]._enable = true;
	m_loggers[newID]._display = display;
	m_loggers[newID]._monthdir = monthdir;
	m_loggers[newID]._limitsize = limitsize;
	if (limitsize == 0)
	{
		m_loggers[newID]._limitsize = 4000;
	}

	return newID;
}


bool CLogerManager::Start()
{
	if (m_bRuning)
	{
		return false;
	}
	m_semaphore.Create(0);
	bool ret = CThread::Start();
	return ret && m_semaphore.Wait(3000);
}
bool CLogerManager::Stop()
{
	if (m_bRuning == true)
	{
		m_bRuning = false;
		Wait();
		return true;
	}
	return false;
}
bool CLogerManager::PrePushLog(LoggerId id, int level)
{
	if (id < 0 || id >= LOG4Z_LOGGER_MAX)
	{
		return false;
	}
	if (!m_bRuning || !m_loggers[id]._enable)
	{
		return false;
	}
	if (level < m_loggers[id]._level)
	{
		return false;
	}
	return true;
}
bool CLogerManager::PushLog(LoggerId id, int level, const char * log)
{
	if (id < 0 || id >= LOG4Z_LOGGER_MAX)
	{
		return false;
	}
	if (!m_bRuning || !m_loggers[id]._enable)
	{
		return false;
	}
	if (level < m_loggers[id]._level)
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
		now -=11644473600000000Ui64;
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
		tm tt = TimeToTm(pLog->_time);
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

	if (m_loggers[pLog->_id]._display && LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
		ShowColorText(pLog->_content, pLog->_level);
	}

	if (LOG4Z_ALL_DEBUGOUTPUT_DISPLAY && LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
#ifdef WIN32
		OutputDebugStringA(pLog->_content);
#endif
	}

	if (LOG4Z_ALL_WRITE_TO_FILE && LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
		CAutoLock l(m_lock);
		if (OpenLogger(pLog))
		{
			m_loggers[pLog->_id]._handle.Write(pLog->_content, pLog->_contentLen);
			CloseLogger(pLog->_id);
			m_ullStatusTotalWriteFileCount++;
			m_ullStatusTotalWriteFileBytes += pLog->_contentLen;
		}
	}

	if (LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
	{
		delete pLog;
		return true;
	}
	
	CAutoLock l(m_lock);
	m_logs.push_back(pLog);
	m_ullStatusTotalPushLog ++;
	return true;
}

//! 查找ID
LoggerId CLogerManager::FindLogger(const char * strName)
{
	std::map<std::string, LoggerId>::iterator iter;
	iter = m_ids.find(strName);
	if (iter != m_ids.end())
	{
		return iter->second;
	}
	return LOG4Z_INVALID_LOGGER_ID;
}

bool CLogerManager::SetLoggerLevel(LoggerId nLoggerID, int nLevel)
{
	if (nLoggerID <0 || nLoggerID >= LOG4Z_LOGGER_MAX || nLevel < LOG_LEVEL_TRACE || nLevel >LOG_LEVEL_FATAL) return false;
	m_loggers[nLoggerID]._level = nLevel;
	return true;
}
bool CLogerManager::SetLoggerDisplay(LoggerId nLoggerID, bool enable)
{
	if (nLoggerID <0 || nLoggerID >= LOG4Z_LOGGER_MAX) return false;
	m_loggers[nLoggerID]._display = enable;
	return true;
}
bool CLogerManager::SetLoggerMonthdir(LoggerId nLoggerID, bool use)
{
	if (nLoggerID <0 || nLoggerID >= LOG4Z_LOGGER_MAX) return false;
	m_loggers[nLoggerID]._monthdir = use;
	return true;
}
bool CLogerManager::SetLoggerLimitSize(LoggerId nLoggerID, unsigned int limitsize)
{
	if (nLoggerID <0 || nLoggerID >= LOG4Z_LOGGER_MAX) return false;
	if (limitsize == 0 ) {limitsize = (unsigned int)-1;}
	m_loggers[nLoggerID]._limitsize = limitsize;
	return true;
}
bool CLogerManager::UpdateConfig()
{
	if (m_configFile.empty())
	{
		return false;
	}
	std::map<std::string, LoggerInfo> loggerMap;
	ParseConfig(m_configFile, loggerMap);
	for (std::map<std::string, LoggerInfo>::iterator iter = loggerMap.begin(); iter != loggerMap.end(); ++iter)
	{
		LoggerId id = FindLogger(iter->first.c_str());
		if (id != LOG4Z_INVALID_LOGGER_ID)
		{
			SetLoggerDisplay(id, iter->second._display);
			SetLoggerLevel(id, iter->second._level);
			SetLoggerMonthdir(id, iter->second._monthdir);
			SetLoggerLimitSize(id, iter->second._limitsize);
		}
	}
	return true;
}

unsigned int CLogerManager::GetStatusActiveLoggers()
{
	unsigned int actives = 0;
	for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
	{
		if (m_loggers[i]._enable)
		{
			actives ++;
		}
	}
	return actives;
}


bool CLogerManager::OpenLogger(LogData * pLog)
{
	int id = pLog->_id;
	if (id < 0 || id >m_lastId)
	{
		ShowColorText("log4z: OpenLogger can not open, invalide logger id! \r\n", LOG_LEVEL_FATAL);
		return false;
	}

	LoggerInfo * pLogger = &m_loggers[id];
	if (!pLogger->_enable || pLog->_level < pLogger->_level)
	{
		return false;
	}

	bool sameday = IsSameDay(pLog->_time, pLogger->_curFileCreateTime);
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
		if (pLogger->_handle.IsOpen())
		{
			pLogger->_handle.Close();
		}
	}
	if (!pLogger->_handle.IsOpen())
	{
		
		tm t = TimeToTm(pLogger->_curFileCreateTime);
		std::string path = pLogger->_path;
		char buf[100] = { 0 };
		if (pLogger->_monthdir)
		{
			sprintf(buf, "%04d_%02d/", t.tm_year + 1900, t.tm_mon + 1);
			path += buf;
		}

		if (!IsDirectory(path))
		{
			CreateRecursionDir(path);
		}

		sprintf(buf, "%s_%04d%02d%02d%02d%02d_%s_%03d.log",
			pLogger->_name.c_str(), t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
			t.tm_hour, t.tm_min, pLogger->_pid.c_str(), pLogger->_curFileIndex);
		path += buf;
		pLogger->_handle.Open(path.c_str(), "ab");
		return pLogger->_handle.IsOpen();
	}
	return true;
}
bool CLogerManager::CloseLogger(LoggerId id)
{
	if (id < 0 || id >m_lastId)
	{
		ShowColorText("log4z: CloseLogger can not close, invalide logger id! \r\n", LOG_LEVEL_FATAL);
		return false;
	}
	LoggerInfo * pLogger = &m_loggers[id];
	if (pLogger->_handle.IsOpen())
	{
		pLogger->_handle.Close();
		return true;
	}
	return false;
}
bool CLogerManager::PopLog(LogData *& log)
{
	CAutoLock l(m_lock);
	if (m_logs.empty())
	{
		return false;
	}
	log = m_logs.front();
	m_logs.pop_front();
	return true;
}

void CLogerManager::Run()
{
	m_bRuning = true;
	m_loggers[LOG4Z_MAIN_LOGGER_ID]._enable = true;

	PushLog(0, LOG_LEVEL_ALARM, "-----------------  log4z thread started!   ----------------------------");
	for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
	{
		if (m_loggers[i]._enable)
		{
			std::stringstream ss;
			ss <<"logger id=" <<i 
				<<" path=" <<m_loggers[i]._path
				<<" name=" <<m_loggers[i]._name
				<<" level=" << m_loggers[i]._level
				<<" display=" << m_loggers[i]._display;
			PushLog(0, LOG_LEVEL_ALARM, ss.str().c_str());
		}
	}

	m_semaphore.Post();


	LogData * pLog = NULL;
	int needFlush[LOG4Z_LOGGER_MAX] = {0};
	while (true)
	{
		while(PopLog(pLog))
		{
			//
			m_ullStatusTotalPopLog ++;
			//discard
			LoggerInfo & curLogger = m_loggers[pLog->_id];
			if (!curLogger._enable || pLog->_level <curLogger._level  )
			{
				delete pLog;
				pLog = NULL;
				continue;
			}


			if (curLogger._display && !LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
				ShowColorText(pLog->_content, pLog->_level);
			}
			if (LOG4Z_ALL_DEBUGOUTPUT_DISPLAY && !LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
#ifdef WIN32
				OutputDebugStringA(pLog->_content);
#endif
			}


			if (LOG4Z_ALL_WRITE_TO_FILE && !LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
				if (!OpenLogger(pLog))
				{
					delete pLog;
					pLog = NULL;
					continue;
				}

				curLogger._handle.Write(pLog->_content, pLog->_contentLen);
				curLogger._curWriteLen += (unsigned int)pLog->_contentLen;
				needFlush[pLog->_id] ++;
				m_ullStatusTotalWriteFileCount++;
				m_ullStatusTotalWriteFileBytes += pLog->_contentLen;
			}
			else if (!LOG4Z_ALL_SYNCHRONOUS_OUTPUT)
			{
				m_ullStatusTotalWriteFileCount++;
				m_ullStatusTotalWriteFileBytes += pLog->_contentLen;
			}

			delete pLog;
			pLog = NULL;
		}

		for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
		{
			if (m_loggers[i]._enable && needFlush[i] > 0)
			{
				m_loggers[i]._handle.Flush();
				needFlush[i] = 0;
			}
		}

		//! delay. 
		SleepMillisecond(100);

		//! quit
		if (!m_bRuning && m_logs.empty())
		{
			break;
		}

	}

	for (int i=0; i<LOG4Z_LOGGER_MAX; i++)
	{
		if (m_loggers[i]._enable)
		{
			m_loggers[i]._enable = false;
			CloseLogger(i);
		}
	}

}

//////////////////////////////////////////////////////////////////////////
//ILog4zManager::GetInstance
//////////////////////////////////////////////////////////////////////////
ILog4zManager * ILog4zManager::GetInstance()
{
	static CLogerManager m;
	return &m;
}



_ZSUMMER_LOG4Z_END
_ZSUMMER_END

