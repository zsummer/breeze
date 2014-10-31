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


/*
 * AUTHORS:  YaweiZhang <yawei_zhang@foxmail.com>
 * VERSION:  2.6.0
 * PURPOSE:  A lightweight library for error reporting and logging to file and screen .
 * CREATION: 2010.10.4
 * LCHANGE:  2014.07.03
 * LICENSE:  Expat/MIT License, See Copyright Notice at the begin of this file.
 */


/*
 *
 * QQ Group: 19811947
 * Web Site: www.zsummer.net
 * mail: yawei_zhang@foxmail.com
 */


/* 
 * UPDATES LOG
 * 
 * VERSION 0.1.0 <DATE: 2010.10.4>
 * 	create the first project.  
 * 	It support put log to screen and files, 
 * 	support log level, support one day one log file.
 * 	support multi-thread, cross-platform.
 * 
 * VERSION .... <DATE: ...>
 * 	...
 * 
 * VERSION 0.9.0 <DATE: 2012.12.24>
 * 	support config files.
 * 	support color text in screen.
 * 	support multiple output to different files.
 * 
 * VERSION 1.0.0 <DATE: 2012.12.29>
 * 	support comments in the config file.
 * 	add a advanced demo in the ./project
 * 	fix some details.
 * 
 * VERSION 1.0.1 <DATE: 2013.01.01>
 * 	change and add some Comments in the log4z
 * 	simplify the 'fast_test' demo projects.
 * 
 * VERSION 1.1.0 <DATE: 2013.01.24>
 * 	the method Start will wait for the logger thread started.
 * 	config and add method change. 
 * 	namespace change.
 * 
 * VERSION 1.1.1 <DATE: 2013.02.23>
 * 	add status info method.
 * 	optimize. 
 *
 * VERSION 1.2.0 <DATE: 2013.04.05>
 * 	add stress test demo
 *  rewrite Stream module,better performance. 
 * 
 * VERSION 1.2.1 <DATE: 2013.04.13>
 * 	fixed type name 'long' stream format on 64/32 operation system.
 *  logger will not loss any log on process normal exit.
 *
 * VERSION 2.0.0 <DATE: 2013.04.25>
 * 	new interface: 
 *      merge some Main interface and Dynamic interface
 *      add Change Logger Attribute method by thread-safe
 * 	new config design.
 * 	log file name append process id.
 *
 * VERSION 2.1 <DATE: 2013.05.22>
 * 	support binary text output 
 *  rewrite write file module, support vs2005 open Chinese characters path
 *
 * VERSION 2.2 <DATE: 2013.07.08>
 *	optimized binary stream output view
 * 	support wchar * string.
 *  
 * VERSION 2.3 <DATE: 2013.08.29>
 *  adjust output file named.
 *  support different month different directory.
 *  adjust some detail.
 * 
 * VERSION 2.4 <DATE: 2013.10.07>
 *  support rolling log file.
 *  support hot update configure
 *  used precision time in log.
 *  micro set default logger attribute
 *  fix tls bug in windows xp dll
 *
 * VERSION 2.5 <DATE: 2014.03.25>
 *  screen output can choice synchronous or not
 *  fix sometimes color will disorder on windows.
 *  eliminate some compiler warning
 *  fix sem_timewait in linux
 *  add format-style method at input log, cannot support vs2003 and VC6.
 *  fix WCHAR String cannot output
 *  optimize std::string, binary log input, and support std::wstring.
 *  clean code, better readability
 *  
 * VERSION 2.6 <DATE: 2014.07.03>
 *  add PrePushLog 
 *  better performance when log is filter out.
 *  interface replace std::string because it's in shared library is unsafe.
 *  add log level 'trace'
 *  
 */


#pragma once
#ifndef _ZSUMMER_LOG4Z_H_
#define _ZSUMMER_LOG4Z_H_

#include <string>
#include <sstream>
#include <errno.h>
#include <stdio.h>
#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

//! logger ID type. DO NOT TOUCH
typedef int LoggerId;

//! the invalid logger id. DO NOT TOUCH
const int LOG4Z_INVALID_LOGGER_ID = -1;

//! the main logger id. DO NOT TOUCH
//! can use this id to set the main logger's attribute.
//! example:
//! ILog4zManager::GetInstance()->SetLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_WARN);
//! ILog4zManager::GetInstance()->SetLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, false);
const int LOG4Z_MAIN_LOGGER_ID = 0;

//! the main logger name. DO NOT TOUCH
const char*const LOG4Z_MAIN_LOGGER_NAME = "Main";

//! check VC VERSION. DO NOT TOUCH
//! format micro cannot support VC6 or VS2003, please use stream input log, like LOGI, LOGD, LOG_DEBUG, LOG_STREAM ...
#if _MSC_VER >= 1400 //MSVC >= VS2005
#define LOG4Z_FORMAT_INPUT_ENABLE
#endif

#ifndef WIN32
#define LOG4Z_FORMAT_INPUT_ENABLE
#endif

//! LOG Level
enum ENUM_LOG_LEVEL
{
	LOG_LEVEL_TRACE = 0,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_ALARM,
	LOG_LEVEL_FATAL,
};

//////////////////////////////////////////////////////////////////////////
//! -----------------default logger config, can change on this.-----------
//////////////////////////////////////////////////////////////////////////
//! the max logger count.
const int LOG4Z_LOGGER_MAX = 10;
//! the max log content length.
const int LOG4Z_LOG_BUF_SIZE = 2048;

//! all logger synchronous output or not
const bool LOG4Z_ALL_SYNCHRONOUS_OUTPUT = true;
//! all logger write log to file or not
const bool LOG4Z_ALL_WRITE_TO_FILE = false;
//! all logger synchronous display to the windows debug output
const bool LOG4Z_ALL_DEBUGOUTPUT_DISPLAY = false;

//! default logger output file.
const char* const LOG4Z_DEFAULT_PATH = "./log/";
//! default log filter level
const int LOG4Z_DEFAULT_LEVEL = LOG_LEVEL_DEBUG;
//! default logger display
const bool LOG4Z_DEFAULT_DISPLAY = true;
//! default logger month dir used status
const bool LOG4Z_DEFAULT_MONTHDIR = false;
//! default logger output file limit size, unit M byte.
const int LOG4Z_DEFAULT_LIMITSIZE = 100;

///////////////////////////////////////////////////////////////////////////
//! -----------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////





#ifndef _ZSUMMER_BEGIN
#define _ZSUMMER_BEGIN namespace zsummer {
#endif  
#ifndef _ZSUMMER_LOG4Z_BEGIN
#define _ZSUMMER_LOG4Z_BEGIN namespace log4z {
#endif
_ZSUMMER_BEGIN
_ZSUMMER_LOG4Z_BEGIN




//! log4z class
class ILog4zManager
{
public:
	ILog4zManager(){};
	virtual ~ILog4zManager(){};
	virtual std::string GetExampleConfig() = 0;

	//! Log4z Singleton
	static ILog4zManager * GetInstance();

	//! Config or overwrite configure
	//! Needs to be called before ILog4zManager::Start,, OR Do not call.
	virtual bool Config(const char * strCfgPath) = 0;

	//! Create or overwrite logger, Total count limited by LOG4Z_LOGGER_MAX.
	//! Needs to be called before ILog4zManager::Start, OR Do not call.
	virtual LoggerId CreateLogger(const char* strName, 
		const char* strPath = LOG4Z_DEFAULT_PATH,
		int nLevel = LOG4Z_DEFAULT_LEVEL,
		bool display = LOG4Z_DEFAULT_DISPLAY,
		bool monthdir = LOG4Z_DEFAULT_MONTHDIR,
		unsigned int limitsize = LOG4Z_DEFAULT_LIMITSIZE /*million byte, rolling file*/) = 0;

	//! Start Log Thread. This method can only be called once by one process.
	virtual bool Start() = 0;

	//! Default the method will be calling at process exit auto.
	//! Default no need to call and no recommended.
	virtual bool Stop() = 0;

	//! Find logger. thread safe.
	virtual LoggerId FindLogger(const char* strName) =0;

	//pre-check the log filter. if filter out return false. 
	virtual bool PrePushLog(LoggerId id, int level) = 0;
	//! Push log, thread safe.
	virtual bool PushLog(LoggerId id, int level, const char * log) = 0;

	//! Set logger's attribute, thread safe.
	virtual bool SetLoggerLevel(LoggerId nLoggerID, int nLevel) = 0;
	virtual bool SetLoggerDisplay(LoggerId nLoggerID, bool enable) = 0;
	virtual bool SetLoggerMonthdir(LoggerId nLoggerID, bool use) = 0;
	virtual bool SetLoggerLimitSize(LoggerId nLoggerID, unsigned int limitsize) = 0;
	//! Update logger's attribute from config file, thread safe.
	virtual bool UpdateConfig() = 0;

	//! Log4z status statistics, thread safe.
	virtual unsigned long long GetStatusTotalWriteCount() = 0;
	virtual unsigned long long GetStatusTotalWriteBytes() = 0;
	virtual unsigned long long GetStatusWaitingCount() = 0;
	virtual unsigned int GetStatusActiveLoggers() = 0;

};

#ifndef _ZSUMMER_END
#define _ZSUMMER_END }
#endif  
#ifndef _ZSUMMER_LOG4Z_END
#define _ZSUMMER_LOG4Z_END }
#endif

_ZSUMMER_LOG4Z_END
_ZSUMMER_END

class CStringStream;

//! optimize by TLS
#ifndef WIN32
extern __thread char g_log4zstreambuf[LOG4Z_LOG_BUF_SIZE];
#endif

//! base micro.
#ifdef  WIN32
#define LOG_STREAM(id, level, log)\
{\
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		char logbuf[LOG4Z_LOG_BUF_SIZE];\
		zsummer::log4z::CStringStream ss(logbuf, LOG4Z_LOG_BUF_SIZE);\
		ss << log;\
		ss << " ( " << __FILE__ << " ) : "  << __LINE__;\
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, logbuf);\
	}\
}
#else
#define LOG_STREAM(id, level, log)\
{\
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		zsummer::log4z::CStringStream ss(g_log4zstreambuf, LOG4Z_LOG_BUF_SIZE);\
		ss << log;\
		ss << " ( " << __FILE__ << " ) : "  << __LINE__;\
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, g_log4zstreambuf);\
	}\
}
#endif

//! fast micro
#define LOG_TRACE(id, log) LOG_STREAM(id, LOG_LEVEL_TRACE, log)
#define LOG_DEBUG(id, log) LOG_STREAM(id, LOG_LEVEL_DEBUG, log)
#define LOG_INFO(id, log)  LOG_STREAM(id, LOG_LEVEL_INFO, log)
#define LOG_WARN(id, log)  LOG_STREAM(id, LOG_LEVEL_WARN, log)
#define LOG_ERROR(id, log) LOG_STREAM(id, LOG_LEVEL_ERROR, log)
#define LOG_ALARM(id, log) LOG_STREAM(id, LOG_LEVEL_ALARM, log)
#define LOG_FATAL(id, log) LOG_STREAM(id, LOG_LEVEL_FATAL, log)

//! super micro.
#define LOGT( log ) LOG_TRACE(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGD( log ) LOG_DEBUG(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGI( log ) LOG_INFO(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGW( log ) LOG_WARN(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGE( log ) LOG_ERROR(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGA( log ) LOG_ALARM(LOG4Z_MAIN_LOGGER_ID, log )
#define LOGF( log ) LOG_FATAL(LOG4Z_MAIN_LOGGER_ID, log )


//! format input log.
#ifdef LOG4Z_FORMAT_INPUT_ENABLE
#ifdef WIN32
#define LOG_FORMAT(id, level, logformat, ...) \
{ \
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		char logbuf[LOG4Z_LOG_BUF_SIZE]; \
		int ret = _snprintf_s(logbuf, LOG4Z_LOG_BUF_SIZE, _TRUNCATE, logformat, ##__VA_ARGS__); \
		if (ret >= 0 && ret<LOG4Z_LOG_BUF_SIZE-1) \
				{\
		_snprintf_s(logbuf + ret, LOG4Z_LOG_BUF_SIZE - ret, _TRUNCATE, " (%s) : %d", __FILE__, __LINE__);\
				}\
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, logbuf); \
	}\
 }
#else
#define LOG_FORMAT(id, level, logformat, ...) \
{ \
	if (zsummer::log4z::ILog4zManager::GetInstance()->PrePushLog(id,level)) \
	{\
		int ret = snprintf(g_log4zstreambuf, LOG4Z_LOG_BUF_SIZE,logformat, ##__VA_ARGS__); \
		if (ret >= 0 && ret < LOG4Z_LOG_BUF_SIZE - 1) \
				{\
		snprintf(g_log4zstreambuf + ret, LOG4Z_LOG_BUF_SIZE - ret, " (%s) : %d", __FILE__, __LINE__); \
				}\
		zsummer::log4z::ILog4zManager::GetInstance()->PushLog(id, level, g_log4zstreambuf); \
	} \
}
#endif
//!format string
#define LOGFMT_TRACE(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_TRACE, fmt, ##__VA_ARGS__)
#define LOGFMT_DEBUG(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define LOGFMT_INFO(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOGFMT_WARN(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOGFMT_ERROR(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define LOGFMT_ALARM(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_ALARM, fmt, ##__VA_ARGS__)
#define LOGFMT_FATAL(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)
#define LOGFMTT( fmt, ...) LOGFMT_TRACE(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#define LOGFMTD( fmt, ...) LOGFMT_DEBUG(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#define LOGFMTI( fmt, ...) LOGFMT_INFO(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#define LOGFMTW( fmt, ...) LOGFMT_WARN(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#define LOGFMTE( fmt, ...) LOGFMT_ERROR(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#define LOGFMTA( fmt, ...) LOGFMT_ALARM(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#define LOGFMTF( fmt, ...) LOGFMT_FATAL(LOG4Z_MAIN_LOGGER_ID, fmt,  ##__VA_ARGS__)
#else
inline void empty_log_format_function1(LoggerId id, const char*, ...){}
inline void empty_log_format_function2(const char*, ...){}
#define LOGFMT_TRACE empty_log_format_function1
#define LOGFMT_DEBUG LOGFMT_TRACE
#define LOGFMT_INFO LOGFMT_TRACE
#define LOGFMT_WARN LOGFMT_TRACE
#define LOGFMT_ERROR LOGFMT_TRACE
#define LOGFMT_ALARM LOGFMT_TRACE
#define LOGFMT_FATAL LOGFMT_TRACE
#define LOGFMTT empty_log_format_function2
#define LOGFMTD LOGFMTT
#define LOGFMTI LOGFMTT
#define LOGFMTW LOGFMTT
#define LOGFMTE LOGFMTT
#define LOGFMTA LOGFMTT
#define LOGFMTF LOGFMTT
#endif


_ZSUMMER_BEGIN
_ZSUMMER_LOG4Z_BEGIN

//! optimze from std::stringstream to CStringStream
#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4996)
#endif
struct BinaryBlock
{
	BinaryBlock(const char * buf, int len)
	{
		_buf = buf;
		_len = len;
	}
	const char * _buf;
	int  _len;
};
class CStringStream
{
public:
	inline CStringStream(char * buf, int len);
private:
	template<class T>
	inline CStringStream & WriteData(const char * ft, T t);
	inline CStringStream & WriteLongLong(long long t);
	inline CStringStream & WriteULongLong(unsigned long long t);
	inline CStringStream & WritePointer(const void * t);
	inline CStringStream & WriteString(const wchar_t* t){ return WriteData("%s", t); }
	inline CStringStream & WriteWString(const wchar_t* t);
	inline CStringStream & WriteBinary(const BinaryBlock & t);
public:
	inline CStringStream & operator <<(const void * t){ return  WritePointer(t); }

	inline CStringStream & operator <<(const char * t){return WriteData("%s", t);}
#ifdef WIN32
	inline CStringStream & operator <<(const wchar_t * t){ return WriteWString(t);}
#endif
	inline CStringStream & operator <<(bool t){ return (t ? WriteData("%s", "true") : WriteData("%s", "false"));}

	inline CStringStream & operator <<(char t){return WriteData("%c", t);}

	inline CStringStream & operator <<(unsigned char t){return WriteData("%u",(unsigned int)t);}

	inline CStringStream & operator <<(short t){ return WriteData("%d", (int)t); }

	inline CStringStream & operator <<(unsigned short t){ return WriteData("%u", (unsigned int)t); }

	inline CStringStream & operator <<(int t){return WriteData("%d", t);}

	inline CStringStream & operator <<(unsigned int t){return WriteData("%u", t);}

	inline CStringStream & operator <<(long t) { return WriteLongLong(t); }

	inline CStringStream & operator <<(unsigned long t){ return WriteULongLong(t); }

	inline CStringStream & operator <<(long long t) { return WriteLongLong(t); }

	inline CStringStream & operator <<(unsigned long long t){ return WriteULongLong(t); }

	inline CStringStream & operator <<(float t){return WriteData("%.4f", t);}

	inline CStringStream & operator <<(double t){return WriteData("%.4lf", t);}

	template<class _Elem,class _Traits,class _Alloc> //support std::string, std::wstring
	inline CStringStream & operator <<(const std::basic_string<_Elem, _Traits, _Alloc> & t){ return *this << t.c_str(); }

	inline CStringStream & operator << (const zsummer::log4z::BinaryBlock & binary){ return WriteBinary(binary); }

private:
	CStringStream(){}
	CStringStream(CStringStream &){}
	char *  m_pBegin;
	char *  m_pEnd;
	char *  m_pCur;
};

inline CStringStream::CStringStream(char * buf, int len)
{
	m_pBegin = buf;
	m_pEnd = buf + len;
	m_pCur = m_pBegin;
}

template<class T>
inline CStringStream& CStringStream::WriteData(const char * ft, T t)
{
	if (m_pCur < m_pEnd)
	{
		int len = 0;
		int count = (int)(m_pEnd - m_pCur);
#ifdef WIN32
		len = _snprintf(m_pCur, count, ft, t);
		if (len == count || (len == -1 && errno == ERANGE))
		{
			len = count;
			*(m_pEnd - 1) = '\0';
		}
		else if (len < 0)
		{
			*m_pCur = '\0';
			len = 0;
		}
#else
		len = snprintf(m_pCur, count, ft, t);
		if (len < 0)
		{
			*m_pCur = '\0';
			len = 0;
		}
		else if (len >= count)
		{
			len = count;
			*(m_pEnd - 1) = '\0';
		}
#endif
		m_pCur += len;
	}
	return *this;
}

inline CStringStream & CStringStream::WriteLongLong(long long t)
{
#ifdef WIN32  
	WriteData("%I64d", t);
#else
	WriteData("%lld", t);
#endif
	return *this;
}

inline CStringStream & CStringStream::WriteULongLong(unsigned long long t)
{
#ifdef WIN32  
	WriteData("%I64u", t);
#else
	WriteData("%llu", t);
#endif
	return *this;
}

inline CStringStream & CStringStream::WritePointer(const void * t)
{
#ifdef WIN32
	sizeof(t) == 8 ? WriteData("%016I64x", (unsigned long long)t) : WriteData("%08I64x", (unsigned long long)t);
#else
	sizeof(t) == 8 ? WriteData("%016llx", (unsigned long long)t) : WriteData("%08llx", (unsigned long long)t);
#endif
	return *this;
}

inline CStringStream & CStringStream::WriteBinary(const BinaryBlock & t)
{
	WriteData("%s", "\r\n\t[");
	for (int i = 0; i < t._len; i++)
	{
		if (i % 16 == 0)
		{
			WriteData("%s", "\r\n\t");
			*this << (void*)(t._buf + i);
			WriteData("%s", ": ");
		}
		WriteData("%02x ", (unsigned char)t._buf[i]);
	}
	WriteData("%s", "\r\n\t]\r\n\t");
	return *this;
}

inline zsummer::log4z::CStringStream & zsummer::log4z::CStringStream::WriteWString(const wchar_t* t)
{
#ifdef WIN32
	DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, t, -1, NULL, 0, NULL, NULL);
	if (dwLen < LOG4Z_LOG_BUF_SIZE)
	{
		std::string str;
		str.resize(dwLen, '\0');
		dwLen = WideCharToMultiByte(CP_ACP, 0, t, -1, &str[0], dwLen, NULL, NULL);
		if (dwLen > 0)
		{
			WriteData("%s", str.c_str());
		}
	}
#else
	//not support
#endif
	return *this;
}


#ifdef WIN32
#pragma warning(pop)
#endif

_ZSUMMER_LOG4Z_END
_ZSUMMER_END

#endif





