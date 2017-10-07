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
 * Copyright (C) 2010-2015 YaweiZhang <yawei.zhang@foxmail.com>.
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

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
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


#ifdef __APPLE__
#include <dispatch/dispatch.h>
#include <libproc.h>
#endif



void luaopen_performence(lua_State * L);

namespace zsummer
{
    class Timestamp
    {
    public:
        inline Timestamp(){_timpstamp = now();}
    public:
        //get lapse time. millisecond.
        inline double lapse(){return std::chrono::duration_cast<std::chrono::duration<double>>(now() - _timpstamp).count()*1000.0;}
        inline std::chrono::steady_clock::time_point now(){return std::chrono::steady_clock::now();}
        inline void flush(){_timpstamp = now();}
    private:
        std::chrono::steady_clock::time_point _timpstamp;
    };

    class LuaStack
    {
    public:
        using Param = std::tuple<std::string, std::chrono::steady_clock::time_point, double/* inc memory */>;
        using Stack = std::vector<Param>;
    public:
        void push(const std::string & func, double mem){ _stack.push_back(std::make_tuple(func, std::chrono::steady_clock::now(), mem)); }
        std::tuple<bool, double, double> pop(const std::string & func, double mem)
        {
            if (_stack.end() != std::find_if(_stack.begin(), _stack.end(), [&func](const Param & p){return std::get<0>(p) == func; }))
            {
                while (!_stack.empty())
                {
                    if (std::get<0>(_stack.back()) == func)
                    {
                        auto ret = std::make_tuple(true, 
                            std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - std::get<1>(_stack.back())).count()*1000.0,
                            mem - std::get<2>(_stack.back()));
                        _stack.pop_back();
                        return std::move(ret);
                    }
                    _stack.pop_back();
                }
            }
            return std::make_tuple(false, 0.0, 0.0);
        }
    private:
        Stack _stack;
    };



    class Performence
    {
    public:
        using Param = std::tuple<std::string, double, double, double, double>;
        inline void call(const std::string & func, double usetime, double mem)
        {
            auto founder = _perf.find(func);
            if (founder == _perf.end())
            {
                _perf[func] = std::make_tuple(func, usetime, 1.0, usetime, mem);
            }
            else
            {
                std::get<1>(founder->second) += usetime;
                std::get<2>(founder->second) += 1.0;
                if (std::get<3>(founder->second) < usetime)
                {
                    std::get<3>(founder->second) = usetime;
                }
                std::get<4>(founder->second) += mem;
            }
        }
        template<class T>
        inline std::string toString(const T & t)
        {
            std::stringstream ss;
            ss << t;
            std::string temp = std::move(ss.str());
            if (temp.length() < 15)
            {
                temp.append(15 - temp.length(), ' ');
            }
            return std::move(temp);
        }

        inline std::string getProcessName()
        {
            std::string name = "MainLog";
            char buf[260] = { 0 };
#ifdef WIN32
            if (GetModuleFileNameA(NULL, buf, 259) > 0)
            {
                name = buf;
            }
            std::string::size_type pos = name.rfind("\\");
            if (pos != std::string::npos)
            {
                name = name.substr(pos + 1, std::string::npos);
            }
            pos = name.rfind(".");
            if (pos != std::string::npos)
            {
                name = name.substr(0, pos - 0);
            }

#elif defined(__APPLE__)

            proc_name(getpid(), buf, 260);
            name = buf;
            return name;;
#else
            sprintf(buf, "/proc/%d/cmdline", (int)getpid());
            std::fstream f(buf, std::ios::in);
            if (f.is_open())
            {
                std::getline(f, name);
                f.close();
            }
            std::string::size_type pos = name.rfind("/");
            if (pos != std::string::npos)
            {
                name = name.substr(pos + 1, std::string::npos);
            }
            name.pop_back();
#endif
            return name;
        }

        inline void serialize(const std::list<Param> & l, const std::string & prefix, const std::string & head, int maxCount)
        {
            std::string filename;
            if (true)
            {
                char buf[100];
                time_t cur = time(NULL);
                struct tm *  t = localtime(&cur);
                sprintf(buf, "%04d%02d%02d_%02d%02d%02d_", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
                filename += buf;
            }
            filename += getProcessName();
            filename += "_";
            filename += prefix;
            filename += ".log";

            std::fstream f(filename, std::ios::out);
            if (!f.is_open())
            {
                return;
            }
            f.write(head.c_str(), head.length());
            std::string temp;
            for (const auto & o : l)
            {
                if (maxCount <= 0)
                {
                    break;
                }
                maxCount--;

                temp = std::get<0>(o);
                if (temp.length() < 70)
                {
                    temp.append(70 - temp.length(), ' ');
                }
                temp += "\t\t" + toString(std::get<1>(o)) + "\t\t" + toString(std::get<2>(o)) + "\t\t" + toString(std::get<3>(o)) + "\t\t" + toString(std::get<4>(o)) + "\n";
                f.write(temp.c_str(), temp.length());
            }
            f.close();
        }
        inline void dump(int maxCount)
        {
            std::string head = "total perf function size is[" + toString(_perf.size()) + "] \n";
            std::list<Param> orderList;
            for (auto & kv : _perf)
            {
                orderList.push_back(kv.second);
            }
            orderList.sort([](const Param & first, const Param & second){return std::get<1>(first) > std::get<1>(second); });
            serialize(orderList, "alltime", head, maxCount);
            orderList.sort([](const Param & first, const Param & second){return std::get<2>(first) > std::get<2>(second); });
            serialize(orderList, "allcount", head, maxCount);
            orderList.sort([](const Param & first, const Param & second){return std::get<1>(first) / std::get<2>(first) > std::get<1>(second) / std::get<2>(second); });
            serialize(orderList, "avetime", head, maxCount);
            orderList.sort([](const Param & first, const Param & second){return std::get<3>(first) > std::get<3>(second); });
            serialize(orderList, "maxtime", head, maxCount);
            orderList.sort([](const Param & first, const Param & second){return std::get<4>(first) > std::get<4>(second); });
            serialize(orderList, "allmem", head, maxCount);
        }
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
        std::map<std::string, Param > _perf;
        std::map<std::string, Param > _once;
        Timestamp _lastPerf;
    };


   


};











#endif


