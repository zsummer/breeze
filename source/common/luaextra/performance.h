/*
 * zsummerX License
 * -----------
 * 
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
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


#ifndef _SUMMER_PERFORMANCE_H_
#define _SUMMER_PERFORMANCE_H_

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <deque>
#include <array>
#include <unordered_map>
#include <cmath>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#include <direct.h>
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


#ifdef __APPLE__
#include <dispatch/dispatch.h>
#include <libproc.h>
#endif


uint64_t MurmurHash64A(const void * key, uint64_t len, uint64_t seed);
void luaopen_performence(lua_State * L);

namespace zsummer
{
    namespace luaperf
    {
        inline double getSteadyNow()
        {
            return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        class Timestamp
        {
        public:
            inline Timestamp() { _last = getSteadyNow(); }
        public:
            //get lapse time. millisecond.
            inline double lapse() { return getSteadyNow() - _last; }
            inline void flush() { _last = getSteadyNow(); }
        private:
            double _last;
        };

        const size_t LUA_STACK_DEPTH = 10000;
        const bool PERF_MEM = true;
        class LuaStack
        {
        public:
            
            struct Layer
            {
                char buf[300];
                size_t len = 0;
                uint64_t hash = 0;
                double mem = 0;
                double sec = 0;
            };
            std::array<Layer, LUA_STACK_DEPTH> _stack;
            size_t _offset = 0;

        public:
            inline bool empty() { return _offset == 0; }
            inline Layer & back() 
            {
                if (_offset == 0)
                {
                    throw std::runtime_error("LuaStack stack no any Layer");
                }
                return _stack[_offset - 1]; 
            }
            inline Layer & push() 
            {
                if (_offset >= LUA_STACK_DEPTH)
                {
                    throw std::runtime_error("LuaStack stack overflow");
                }
                return _stack[_offset++];
            }
            inline void pop()
            {
                if (_offset <= 0)
                {
                    throw std::runtime_error("LuaStack stack empty can't pop");
                }
                _offset--;
            }
        };



        class Performence
        {
        public:
            struct Collect
            {
                char buf[300];
                size_t len = 0;
                uint64_t hash = 0;

                double count = 0;
                double sec = 0;
                double maxsec = 0;
                double avgsec = 0;
                double mem = 0;
            };

            void call(const LuaStack::Layer & param);

            inline void toString(char *buf, unsigned long long &len, unsigned long long t,  bool minus, 
                unsigned long long deci, unsigned long long fill0)
            {
                const char * dec = "0123456789abcdef";

                char * end = buf + len;
                *--end = '\0';
                char * cur = end;
                do 
                {
                    *--cur = dec[t % deci];
                    t /= deci;
                    if (t == 0)
                    {
                        break;
                    }
                } while (true);
                while ((unsigned long long)(end - cur) < fill0)
                {
                    *--cur = '0';
                }
                if (minus)
                {
                    *--cur = '-';
                }
                memmove(buf, cur, end - cur + 1);
                len = end - cur;
            }

            inline std::string toString(double t)
            {
#if __cplusplus >= 201103L
                using std::isnan;
                using std::isinf;
#endif
                if (isnan(t))
                {
                    return "nan";
                }
                else if (isinf(t))
                {
                    return "inf";
                }

                double fabst = fabs(t);
                char buf[80];
                if (fabst < 0.000001 ||  fabst >= 4503599627370495ULL)
                {
                    gcvt(t, 12, buf);
                    return std::string(buf);
                }
                else 
                {
                    unsigned long long integ = (unsigned long long)fabst;
                    unsigned long long len = 80;
                    toString(buf, len, (unsigned long long)fabst, t < 0, 10, 0);

                    unsigned long long fn = (unsigned long long)(( fabst - integ*1.0) * 1000000.0);
                    if (fn > 0)
                    {
                        buf[len] = '.';
                        len++;
                        unsigned long long nlen = 20;
                        toString(buf + len, nlen, fn, false, 10, 6);
                        len += nlen;
                    }
                    return std::string(buf, len);
 
                }
            }

            std::string getProcessID();
            std::string getProcessName();

            void serialize(const std::vector<std::unordered_map<uint64_t, Collect>::iterator> & l, 
                const std::string & prefix, const std::string & head, int maxCount);
            void dump(int maxCount);
            inline bool expire(double interval)
            {
                if (_lastPerf.lapse() > interval)
                {
                    _lastPerf.flush();
                    return true;
                }
                return false;
            }
        public:
            LuaStack _stack;
        private:
            std::unordered_map<uint64_t, Collect> _collected;
            std::string _processID;
            std::string _processName;
            std::deque<std::string> _historyFile;
            Timestamp _lastPerf;
        };
    };
    

};











#endif


