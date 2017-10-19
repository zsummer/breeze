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
 * Copyright (C) 2010-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
 * AUTHORS:  YaweiZhang <yawei.zhang@foxmail.com>
 * VERSION:  3.5.0
 * PURPOSE:  A lightweight library for error reporting and logging to file and screen .
 * CREATION: 2010.10.4
 * LCHANGE:  2017.08.20
 * LICENSE:  Expat/MIT License, See Copyright Notice at the begin of this file.
 */


/*
 * contact me:
 * tencent qq group: 19811947
 * mail: yawei.zhang@foxmail.com
 */


/* 
 * UPDATES LOG
 * 
 * VERSION 0.1.0 <DATE: 2010.10.4>
 *     create the first project.  
 *     It support put log to screen and files, 
 *     support log level, support one day one log file.
 *     support multi-thread, cross-platform.
 * 
 * VERSION .... <DATE: ...>
 *     ...
 * 
 * VERSION 0.9.0 <DATE: 2012.12.24>
 *     support config files.
 *     support color text in screen.
 *     support multiple output to different files.
 * 
 * VERSION 1.0.0 <DATE: 2012.12.29>
 *     support comments in the config file.
 *     add a advanced demo in the ./project
 *     fix some details.
 * 
 * VERSION 1.0.1 <DATE: 2013.01.01>
 *     change and add some Comments in the log4z
 *     simplify the 'fast_test' demo projects.
 * 
 * VERSION 1.1.0 <DATE: 2013.01.24>
 *     the method Start will wait for the logger thread started.
 *     config and add method change. 
 *     namespace change.
 * 
 * VERSION 1.1.1 <DATE: 2013.02.23>
 *     add status info method.
 *     optimize. 
 *
 * VERSION 1.2.0 <DATE: 2013.04.05>
 *     add stress test demo
 *  rewrite Stream module,better performance. 
 * 
 * VERSION 1.2.1 <DATE: 2013.04.13>
 *     fixed type name 'long' stream format on 64/32 operation system.
 *  logger will not loss any log on process normal exit.
 *
 * VERSION 2.0.0 <DATE: 2013.04.25>
 *     new interface: 
 *      merge some Main interface and Dynamic interface
 *      add Change Logger Attribute method by thread-safe
 *     new config design.
 *     log file name append process id.
 *
 * VERSION 2.1 <DATE: 2013.05.22>
 *     support binary text output 
 *  rewrite write file module, support vs2005 open Chinese characters path
 *
 * VERSION 2.2 <DATE: 2013.07.08>
 *    optimized binary stream output view
 *     support wchar * string.
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
 * VERSION 2.6 <DATE: 2014.08.19>
 *  add PrePushLog 
 *  better performance when log is filter out.
 *  interface replace std::string because it's in shared library is unsafe.
 *  add log level 'trace'
 * 
 * VERSION 2.6.1 <DATE: 2014.08.22>
 *  fix bug from defined _MSC_VER 
 *
 * VERSION 2.7 <DATE: 2014.09.21>
 *  compatible mac machine,  now  log4z can working in linux/windows/mac.
 *
 * VERSION 2.8 <DATE: 2014.09.27>
 *  support synchronous written to file and thread-safe
 *  fix compatibility on MinGW. a constant value suffix.
 *  ignore utf-8 file BOM when load configure file
 *  use macro WIN32_LEAN_AND_MEAN replace head file winsock2.h
 *  new naming notations
 * 
 * VERSION 3.0 <DATE: 2014.12.19>
 *  new naming notations
 *  support for reading config from a string.
 *  remove all TLS code, used dispatch_semaphore in apple OS.
 *  support system: windows, linux, mac, iOS
 *
 * VERSION 3.1 <DATE: 2014.12.19>
 *  add method enable/disable logger by specific logger id
 *  add method enable/disable log suffix line number.
 *  add method enable/disable log output to file.
 *
 * VERSION 3.2 <DATE: 2014.12.19>
 *  add interface setLoggerName,setLoggerPath,setAutoUpdate
 *  support auto update from configure file
 *
 * VERSION 3.3 <DATE: 2014.12.19>
 *  support map vector list
 *  support continuum via travis.
 *  new hot change design, all change realize need via push log flow.
 *  support oem string convert.
 *  new method to read whole content of file.
 *  check configure's checksum when auto update it.
 *  some other optimize.
 * 
 * VERSION 3.5 <DATE: 2017.08.20>
 *  optimization
 *
 */


#pragma once
#ifndef _ZSUMMER_LOG4Z_H_
#define _ZSUMMER_LOG4Z_H_

#include <string>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <deque>


//! logger ID type. DO NOT TOUCH
typedef int LoggerId;

//! the invalid logger id. DO NOT TOUCH
const int LOG4Z_INVALID_LOGGER_ID = -1;

//! the main logger id. DO NOT TOUCH
//! can use this id to set the main logger's attribute.
//! example:
//! ILog4zManager::getPtr()->setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_WARN);
//! ILog4zManager::getPtr()->setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, false);
const int LOG4Z_MAIN_LOGGER_ID = 0;

//! the main logger name. DO NOT TOUCH
const char*const LOG4Z_MAIN_LOGGER_KEY = "Main";

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
const int LOG4Z_LOGGER_MAX = 20;
//! the max log content length.
const int LOG4Z_LOG_BUF_SIZE = 1024 * 8;
//! the max stl container depth.
const int LOG4Z_LOG_CONTAINER_DEPTH = 5;
//! the log queue length limit size.
const int LOG4Z_LOG_QUEUE_LIMIT_SIZE = 20000;

//! all logger synchronous output or not
const bool LOG4Z_ALL_SYNCHRONOUS_OUTPUT = false;
//! all logger synchronous display to the windows debug output
const bool LOG4Z_ALL_DEBUGOUTPUT_DISPLAY = false;

//! default logger output file.
const char* const LOG4Z_DEFAULT_PATH = "./log/";
//! default log filter level
const int LOG4Z_DEFAULT_LEVEL = LOG_LEVEL_DEBUG;
//! default logger display
const bool LOG4Z_DEFAULT_DISPLAY = true;
//! default logger output to file
const bool LOG4Z_DEFAULT_OUTFILE = true;
//! default logger month dir used status
const bool LOG4Z_DEFAULT_MONTHDIR = false;
//! default logger output file limit size, unit M byte.
const int LOG4Z_DEFAULT_LIMITSIZE = 100;
//! default logger show suffix (file name and line number) 
const bool LOG4Z_DEFAULT_SHOWSUFFIX = true;
//! support ANSI->OEM console conversion on Windows
#undef LOG4Z_OEM_CONSOLE
//! default logger force reserve log file count.
const size_t LOG4Z_FORCE_RESERVE_FILE_COUNT = 7;

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


struct LogData
{
    LoggerId _id;        //dest logger id
    int    _type;     //type.
    int    _typeval;
    int    _level;    //log level
    time_t _time;        //create time
    unsigned int _precise; //create time 
    unsigned int _threadID;
    int _contentLen;
    char _content[1]; //content
};

//! log4z class
class ILog4zManager
{
public:
    ILog4zManager(){};
    virtual ~ILog4zManager(){};

    //! Log4z Singleton
    
    static ILog4zManager * getInstance();
    inline static ILog4zManager & getRef(){return *getInstance();}
    inline static ILog4zManager * getPtr(){return getInstance();}

    //! Config or overwrite configure
    //! Needs to be called before ILog4zManager::Start,, OR Do not call.
    virtual bool config(const char * configPath) = 0;
    virtual bool configFromString(const char * configContent) = 0;

    //! Create or overwrite logger.
    //! Needs to be called before ILog4zManager::Start, OR Do not call.
    virtual LoggerId createLogger(const char* key) = 0;

    //! Start Log Thread. This method can only be called once by one process.
    virtual bool start() = 0;

    //! Default the method will be calling at process exit auto.
    //! Default no need to call and no recommended.
    virtual bool stop() = 0;

    //! Find logger. thread safe.
    virtual LoggerId findLogger(const char* key) =0;

    //pre-check the log filter. if filter out return false. 
    virtual bool prePushLog(LoggerId id, int level) = 0;
    //! Push log, thread safe.
    virtual bool pushLog(LogData * pLog, const char * file = NULL, int line = 0) = 0;

    //! set logger's attribute, thread safe.
    virtual bool enableLogger(LoggerId id, bool enable) = 0; // immediately when enable, and queue up when disable. 
    virtual bool setLoggerName(LoggerId id, const char * name) = 0;
    virtual bool setLoggerPath(LoggerId id, const char * path) = 0;
    virtual bool setLoggerLevel(LoggerId id, int nLevel) = 0; // immediately when enable, and queue up when disable. 
    virtual bool setLoggerFileLine(LoggerId id, bool enable) = 0;
    virtual bool setLoggerDisplay(LoggerId id, bool enable) = 0;
    virtual bool setLoggerOutFile(LoggerId id, bool enable) = 0;
    virtual bool setLoggerLimitsize(LoggerId id, unsigned int limitsize) = 0;
	virtual bool setLoggerMonthdir(LoggerId id, bool enable) = 0;
	virtual bool setLoggerReserveTime(LoggerId id, time_t sec) = 0;


    //! Update logger's attribute from config file, thread safe.
    virtual bool setAutoUpdate(int interval/*per second, 0 is disable auto update*/) = 0;
    virtual bool updateConfig() = 0;

    //! Log4z status statistics, thread safe.
    virtual bool isLoggerEnable(LoggerId id) = 0;
    virtual unsigned long long getStatusTotalWriteCount() = 0;
    virtual unsigned long long getStatusTotalWriteBytes() = 0;
    virtual unsigned long long getStatusTotalPushQueue() = 0;
    virtual unsigned long long getStatusTotalPopQueue() = 0;
    virtual unsigned int getStatusActiveLoggers() = 0;

    virtual LogData * makeLogData(LoggerId id, int level) = 0;
    virtual void freeLogData(LogData * log) = 0;
};

class Log4zStream;
class Log4zBinary;

#ifndef _ZSUMMER_END
#define _ZSUMMER_END }
#endif  
#ifndef _ZSUMMER_LOG4Z_END
#define _ZSUMMER_LOG4Z_END }
#endif

_ZSUMMER_LOG4Z_END
_ZSUMMER_END



//! base macro.
#define LOG_STREAM(id, level, file, line, log)\
do{\
    if (zsummer::log4z::ILog4zManager::getPtr()->prePushLog(id,level)) \
    {\
        zsummer::log4z::LogData * __pLog = zsummer::log4z::ILog4zManager::getPtr()->makeLogData(id, level); \
        zsummer::log4z::Log4zStream __ss(__pLog->_content + __pLog->_contentLen, LOG4Z_LOG_BUF_SIZE - __pLog->_contentLen);\
        __ss << log;\
        __pLog->_contentLen += __ss.getCurrentLen(); \
        zsummer::log4z::ILog4zManager::getPtr()->pushLog(__pLog, file, line);\
    }\
} while (0)


//! fast macro
#define LOG_TRACE(id, log) LOG_STREAM(id, LOG_LEVEL_TRACE, __FILE__, __LINE__, log)
#define LOG_DEBUG(id, log) LOG_STREAM(id, LOG_LEVEL_DEBUG, __FILE__, __LINE__, log)
#define LOG_INFO(id, log)  LOG_STREAM(id, LOG_LEVEL_INFO, __FILE__, __LINE__, log)
#define LOG_WARN(id, log)  LOG_STREAM(id, LOG_LEVEL_WARN, __FILE__, __LINE__, log)
#define LOG_ERROR(id, log) LOG_STREAM(id, LOG_LEVEL_ERROR, __FILE__, __LINE__, log)
#define LOG_ALARM(id, log) LOG_STREAM(id, LOG_LEVEL_ALARM, __FILE__, __LINE__, log)
#define LOG_FATAL(id, log) LOG_STREAM(id, LOG_LEVEL_FATAL, __FILE__, __LINE__, log)

//! super macro.
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
#define LOG_FORMAT(id, level, file, line, logformat, ...) \
do{ \
    if (zsummer::log4z::ILog4zManager::getPtr()->prePushLog(id,level)) \
    {\
        zsummer::log4z::LogData * __pLog = zsummer::log4z::ILog4zManager::getPtr()->makeLogData(id, level); \
        int __logLen = _snprintf_s(__pLog->_content + __pLog->_contentLen, LOG4Z_LOG_BUF_SIZE - __pLog->_contentLen, _TRUNCATE, logformat, ##__VA_ARGS__); \
        if (__logLen < 0) __logLen = LOG4Z_LOG_BUF_SIZE - __pLog->_contentLen; \
        __pLog->_contentLen += __logLen; \
        zsummer::log4z::ILog4zManager::getPtr()->pushLog(__pLog, file, line); \
    }\
} while (0)
#else
#define LOG_FORMAT(id, level, file, line, logformat, ...) \
do{ \
    if (zsummer::log4z::ILog4zManager::getPtr()->prePushLog(id,level)) \
    {\
        zsummer::log4z::LogData * __pLog = zsummer::log4z::ILog4zManager::getPtr()->makeLogData(id, level); \
        int __logLen = snprintf(__pLog->_content + __pLog->_contentLen, LOG4Z_LOG_BUF_SIZE - __pLog->_contentLen,logformat, ##__VA_ARGS__); \
        if (__logLen < 0) __logLen = 0; \
        if (__logLen > LOG4Z_LOG_BUF_SIZE - __pLog->_contentLen) __logLen = LOG4Z_LOG_BUF_SIZE - __pLog->_contentLen; \
        __pLog->_contentLen += __logLen; \
        zsummer::log4z::ILog4zManager::getPtr()->pushLog(__pLog, file, line); \
    } \
}while(0)
#endif
//!format string
#define LOGFMT_TRACE(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGFMT_DEBUG(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGFMT_INFO(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGFMT_WARN(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGFMT_ERROR(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGFMT_ALARM(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_ALARM, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGFMT_FATAL(id, fmt, ...)  LOG_FORMAT(id, LOG_LEVEL_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
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

//! optimze from std::stringstream to Log4zStream
#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4996)
#endif
class Log4zBinary
{
public:
    Log4zBinary(const void * buf, size_t len)
    {
        this->buf = (const char *)buf;
        this->len = len;
    }
    const char * buf;
    size_t  len;
};

class Log4zString
{
public:
    Log4zString(const char * buf, size_t len)
    {
        this->buf = (const char *)buf;
        this->len = len;
    }
    const char * buf;
    size_t  len;
};

class Log4zStream
{
public:
    inline Log4zStream(char * buf, int len);
    inline int getCurrentLen(){return (int)(_cur - _begin);}
public:
    inline Log4zStream & writeLongLong(long long t, int width = 0, int dec = 10);
    inline Log4zStream & writeULongLong(unsigned long long t, int width = 0, int dec = 10);
    inline Log4zStream & writeDouble(double t, bool isSimple);
    inline Log4zStream & writePointer(const void * t);
    inline Log4zStream & writeString(const char * t) { return writeString(t, strlen(t)); };
    inline Log4zStream & writeString(const char * t, size_t len);
    inline Log4zStream & writeChar(char ch);
    inline Log4zStream & writeBinary(const Log4zBinary & t);
public:
    inline Log4zStream & operator <<(const void * t){ return  writePointer(t); }

    inline Log4zStream & operator <<(const char * t){return writeString(t);}

    inline Log4zStream & operator <<(bool t){ return (t ? writeString("true", 4) : writeString("false", 5));}

    inline Log4zStream & operator <<(char t){return writeChar(t);}

    inline Log4zStream & operator <<(unsigned char t){return writeULongLong(t);}

    inline Log4zStream & operator <<(short t){ return writeLongLong(t); }

    inline Log4zStream & operator <<(unsigned short t){ return writeULongLong(t); }

    inline Log4zStream & operator <<(int t){return writeLongLong(t);}

    inline Log4zStream & operator <<(unsigned int t){return writeULongLong(t);}

    inline Log4zStream & operator <<(long t) { return writeLongLong(t); }

    inline Log4zStream & operator <<(unsigned long t){ return writeULongLong(t); }

    inline Log4zStream & operator <<(long long t) { return writeLongLong(t); }

    inline Log4zStream & operator <<(unsigned long long t){ return writeULongLong(t); }

    inline Log4zStream & operator <<(float t){return writeDouble(t, true);}

    inline Log4zStream & operator <<(double t){return writeDouble(t, false);}

    template<class _Elem,class _Traits,class _Alloc> //support std::string, std::wstring
    inline Log4zStream & operator <<(const std::basic_string<_Elem, _Traits, _Alloc> & t){ return writeString(t.c_str(), t.length()); }

    inline Log4zStream & operator << (const zsummer::log4z::Log4zBinary & binary) { return writeBinary(binary); }

    inline Log4zStream & operator << (const zsummer::log4z::Log4zString & str) { return writeString(str.buf, str.len); }

    template<class _Ty1, class _Ty2>
    inline Log4zStream & operator <<(const std::pair<_Ty1, _Ty2> & t){ return *this << "pair(" << t.first << ":" << t.second << ")"; }

    template<class _Elem, class _Alloc>
    inline Log4zStream & operator <<(const std::vector<_Elem, _Alloc> & t)
    { 
        *this << "vector(" << t.size() << ")[";
        int inputCount = 0;
        for (typename std::vector<_Elem, _Alloc>::const_iterator iter = t.begin(); iter != t.end(); iter++)
        {
            inputCount++;
            if (inputCount > LOG4Z_LOG_CONTAINER_DEPTH)
            {
                *this << "..., ";
                break;
            }
            *this << *iter << ", ";
        }
        if (!t.empty())
        {
            _cur -= 2;
        }
        return *this << "]";
    }
    template<class _Elem, class _Alloc>
    inline Log4zStream & operator <<(const std::list<_Elem, _Alloc> & t)
    { 
        *this << "list(" << t.size() << ")[";
        int inputCount = 0;
        for (typename std::list<_Elem, _Alloc>::const_iterator iter = t.begin(); iter != t.end(); iter++)
        {
            inputCount++;
            if (inputCount > LOG4Z_LOG_CONTAINER_DEPTH)
            {
                *this << "..., ";
                break;
            }
            *this << *iter << ", ";
        }
        if (!t.empty())
        {
            _cur -= 2;
        }
        return *this << "]";
    }
    template<class _Elem, class _Alloc>
    inline Log4zStream & operator <<(const std::deque<_Elem, _Alloc> & t)
    {
        *this << "deque(" << t.size() << ")[";
        int inputCount = 0;
        for (typename std::deque<_Elem, _Alloc>::const_iterator iter = t.begin(); iter != t.end(); iter++)
        {
            inputCount++;
            if (inputCount > LOG4Z_LOG_CONTAINER_DEPTH)
            {
                *this << "..., ";
                break;
            }
            *this << *iter << ", ";
        }
        if (!t.empty())
        {
            _cur -= 2;
        }
        return *this << "]";
    }
    template<class _Elem, class _Alloc>
    inline Log4zStream & operator <<(const std::queue<_Elem, _Alloc> & t)
    {
        *this << "queue(" << t.size() << ")[";
        int inputCount = 0;
        for (typename std::queue<_Elem, _Alloc>::const_iterator iter = t.begin(); iter != t.end(); iter++)
        {
            inputCount++;
            if (inputCount > LOG4Z_LOG_CONTAINER_DEPTH)
            {
                *this << "..., ";
                break;
            }
            *this << *iter << ", ";
        }
        if (!t.empty())
        {
            _cur -= 2;
        }
        return *this << "]";
    }
    template<class _K, class _V, class _Pr, class _Alloc>
    inline Log4zStream & operator <<(const std::map<_K, _V, _Pr, _Alloc> & t)
    {
        *this << "map(" << t.size() << ")[";
        int inputCount = 0;
        for (typename std::map < _K, _V, _Pr, _Alloc>::const_iterator iter = t.begin(); iter != t.end(); iter++)
        {
            inputCount++;
            if (inputCount > LOG4Z_LOG_CONTAINER_DEPTH)
            {
                *this << "..., ";
                break;
            }
            *this << *iter << ", ";
        }
        if (!t.empty())
        {
            _cur -= 2;
        }
        return *this << "]";
    }

private:
    Log4zStream(){}
    Log4zStream(Log4zStream &){}
    char *  _begin;
    char *  _end;
    char *  _cur;
};

inline Log4zStream::Log4zStream(char * buf, int len)
{
    _begin = buf;
    _end = buf + len;
    _cur = _begin;
}



inline Log4zStream & Log4zStream::writeLongLong(long long t, int width, int dec)
{
    if (t < 0 )
    {
        t = -t;
        writeChar('-');
    }
    writeULongLong((unsigned long long)t, width, dec);
    return *this;
}

inline Log4zStream & Log4zStream::writeULongLong(unsigned long long t, int width, int dec)
{
    static const char * lut = 
        "0123456789abcdef";

    static const char *lutDec = 
        "00010203040506070809"
        "10111213141516171819"
        "20212223242526272829"
        "30313233343536373839"
        "40414243444546474849"
        "50515253545556575859"
        "60616263646566676869"
        "70717273747576777879"
        "80818283848586878889"
        "90919293949596979899";

    static const char *lutHex = 
        "000102030405060708090A0B0C0D0E0F"
        "101112131415161718191A1B1C1D1E1F"
        "202122232425262728292A2B2C2D2E2F"
        "303132333435363738393A3B3C3D3E3F"
        "404142434445464748494A4B4C4D4E4F"
        "505152535455565758595A5B5C5D5E5F"
        "606162636465666768696A6B6C6D6E6F"
        "707172737475767778797A7B7C7D7E7F"
        "808182838485868788898A8B8C8D8E8F"
        "909192939495969798999A9B9C9D9E9F"
        "A0A1A2A3A4A5A6A7A8A9AAABACADAEAF"
        "B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
        "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF"
        "D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
        "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF"
        "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";

    const unsigned long long cacheSize = 64;

    if ((unsigned long long)(_end - _cur) > cacheSize)
    {
        char buf[cacheSize];
        unsigned long long val = t;
        unsigned long long i = cacheSize;
        unsigned long long digit = 0;



        if (dec == 10)
        {
            do
            {
                const unsigned long long m2 = (unsigned long long)((val % 100) * 2);
                *(buf + i - 1) = lutDec[m2 + 1];
                *(buf + i - 2) = lutDec[m2];
                i -= 2;
                val /= 100;
                digit += 2;
            } while (val && i >= 2);
            if (digit >= 2 && buf[cacheSize - digit] == '0')
            {
                digit--;
            }
        }
        else if (dec == 16)
        {
            do
            {
                const unsigned long long m2 = (unsigned long long)((val % 256) * 2);
                *(buf + i - 1) = lutHex[m2 + 1];
                *(buf + i - 2) = lutHex[m2];
                i -= 2;
                val /= 256;
                digit += 2;
            } while (val && i >= 2);
            if (digit >= 2 && buf[cacheSize - digit] == '0')
            {
                digit--;
            }
        }
        else
        {
            do
            {
                buf[--i] = lut[val % dec];
                val /= dec;
                digit++;
            } while (val && i > 0);
        }

        while (digit < (unsigned long long)width)
        {
            digit++;
            buf[cacheSize - digit] = '0';
        }

        writeString(buf + (cacheSize - digit), (size_t)digit);
    }
    return *this;
}
inline Log4zStream & Log4zStream::writeDouble(double t, bool isSimple)
{

#if __cplusplus >= 201103L
                using std::isnan;
                using std::isinf;
#endif
    if (isnan(t))
    {
        writeString("nan", 3);
        return *this;
    }
    else if (isinf(t))
    {
        writeString("inf", 3);
        return *this;
    }



    size_t count = _end - _cur;
    double fabst = fabs(t);
    if (count > 30)
    {
        if ( fabst < 0.0001 || (!isSimple && fabst > 4503599627370495ULL) || (isSimple && fabst > 8388607))
        {
            gcvt(t, isSimple ? 7 : 16, _cur);
            size_t len = strlen(_cur);
            if (len > count) len = count;
            _cur += len;
            return *this;
        }
        else
        {
            if (t < 0.0)
            {
                writeChar('-');
            }
            double intpart = 0;
            unsigned long long fractpart = (unsigned long long)(modf(fabst, &intpart) * 10000);
            writeULongLong((unsigned long long)intpart);
            if (fractpart > 0)
            {
                writeChar('.');
                writeULongLong(fractpart, 4);
            }
        }
    }

    return *this;
}

inline Log4zStream & Log4zStream::writePointer(const void * t)
{
    sizeof(t) == 8 ?  writeULongLong((unsigned long long)t, 16, 16): writeULongLong((unsigned long long)t, 8, 16);
    return *this;
}

inline Log4zStream & Log4zStream::writeBinary(const Log4zBinary & t)
{
    writeString("\r\n\t[");
    for (size_t i=0; i<(t.len / 32)+1; i++)
    {
        writeString("\r\n\t");
        *this << (void*)(t.buf + i*32);
        writeString(": ");
        for (size_t j = i * 32; j < (i + 1) * 32 && j < t.len; j++)
        {
            if (isprint((unsigned char)t.buf[j]))
            {
                writeChar(' ');
                writeChar(t.buf[j]);
                writeChar(' ');
            }
            else
            {
                *this << " . ";
            }
        }
        writeString("\r\n\t");
        *this << (void*)(t.buf + i * 32);
        writeString(": ");
        for (size_t j = i * 32; j < (i + 1) * 32 && j < t.len; j++)
        {
            writeULongLong((unsigned long long)(unsigned char)t.buf[j], 2, 16);
            writeChar(' ');
        }
    }

    writeString("\r\n\t]\r\n\t");
    return *this;
}
inline Log4zStream & zsummer::log4z::Log4zStream::writeChar(char ch)
{
    if (_end - _cur > 1)
    {
        _cur[0] = ch;
        _cur++;
    }
    return *this;
}

inline Log4zStream & zsummer::log4z::Log4zStream::writeString(const char * t, size_t len)
{
    size_t count = _end - _cur;
    if (len > count)
    {
        len = count;
    }
    if (len > 0)
    {
        memcpy(_cur, t, len);
        _cur += len;
    }
    
    return *this;
}




#ifdef WIN32
#pragma warning(pop)
#endif

_ZSUMMER_LOG4Z_END
_ZSUMMER_END

#endif
