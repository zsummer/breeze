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


#include "performance.h"

static void hook_run_fn(lua_State *L, lua_Debug *ar);
using namespace zsummer::luaperf;
static int newindex(lua_State * L)
{
    lua_pushvalue(L, 1);
    lua_pushvalue(L, 2);
    lua_pushvalue(L, 3);
    lua_rawset(L, 4);
    lua_pop(L, 1);
    const char * key = luaL_checkstring(L, 2);
    const char * v = luaL_typename(L, 3);
    std::stringstream ss;
    ss << "catch one operation that it's set a global value. key=" << key << ", type(v)=" << v << ", is it correct ?";
    if (lua_getglobal(L, "summer") == LUA_TTABLE && lua_getfield(L, -1, "logw") == LUA_TFUNCTION)
    {
        lua_pushstring(L, ss.str().c_str());
        lua_pcall(L, 1, 0, 0);
    }
    else if (lua_getglobal(L, "print") == LUA_TFUNCTION)
    {
        lua_pushstring(L, ss.str().c_str());
        lua_pcall(L, 1, 0, 0);
    }
    lua_pop(L, lua_gettop(L) - 3);
    
    return 0;
}


zsummer::luaperf::Performence __perf;
void luaopen_performence(lua_State * L)
{
    //lua_Hook oldhook = lua_gethook(L);
    //int oldmask = lua_gethookmask(L);
    lua_sethook(L, &hook_run_fn, LUA_MASKCALL | LUA_MASKRET, 0);
    lua_getglobal(L, "_G");
    lua_newtable(L);
    lua_pushcclosure(L, newindex, 0);
    lua_setfield(L, -2, "__newindex");
    lua_setmetatable(L, -2);
}

void hook_run_fn(lua_State *L, lua_Debug *ar)
{
    auto & stack = __perf._stack.push();
    stack.len = 0;
    // 获取Lua调用信息
    lua_getinfo(L, "Sn", ar);
    if (!ar->name)
    {
        __perf._stack.pop();
        return;
    }
    if (ar->what)
    {
        size_t len = strlen(ar->what);
        if (len > 0 && len + stack.len < 300 - 4)
        {
            stack.buf[stack.len] = '(';
            stack.len += 1;
            memcpy(stack.buf + stack.len, ar->what, len);
            stack.len += len;
            stack.buf[stack.len] = ')';
            stack.buf[stack.len + 1] = ':';
            stack.buf[stack.len + 2] = ':';
            stack.len += 3;
        }
    }

    if (ar->namewhat)
    {
        size_t len = strlen(ar->namewhat);
        if (len > 0 && len + stack.len < 300 - 2)
        {
            memcpy(stack.buf + stack.len, ar->namewhat, len);
            stack.len += len + 2;
            stack.buf[stack.len - 2] = ':';
            stack.buf[stack.len - 1] = ':';
        }
    }

    if (ar->name)
    {
        size_t len = strlen(ar->name);
        if (len == 0)
        {
            __perf._stack.pop();
            return;
        }
        if (len > 0 && len + stack.len < 300)
        {
            memcpy(stack.buf + stack.len, ar->name, len);
            stack.len += len;
        }
    }

    if (300 - stack.len > 2)
    {
        stack.buf[stack.len] = ' ';
        stack.buf[stack.len+1] = '\t';
        stack.len += 2;
    }




    if (ar->source)
    {
        size_t len = strlen(ar->source);
        if (len > 0 && len + stack.len < 300)
        {
            memcpy(stack.buf + stack.len, ar->source, len);
            stack.len += len;
        }
    }





    if (stack.len == 0)
    {
        __perf._stack.pop();
        return;
    }
    if (PERF_MEM)
    {
        stack.mem = lua_gc(L, LUA_GCCOUNT, 0) /1024.0 + lua_gc(L, LUA_GCCOUNTB, 0)/1024.0/1024.0;
    }
    stack.hash = MurmurHash64A(stack.buf, stack.len, (uint64_t)0);
    stack.sec = getSteadyNow();
    if (ar->event == LUA_HOOKCALL)
    {
        
    }
    else if (ar->event == LUA_HOOKRET)
    {
        //lua_gc(L, LUA_GCCOLLECT, 0);
        for (size_t i = __perf._stack._offset - 1; i > 0; i--) //back is current.  
        {
            auto & param = __perf._stack._stack[i - 1];
            if (stack.hash != param.hash)
            {
                continue;
            }
            if (stack.len != param.len)
            {
                continue;
            }
            if (memcmp(stack.buf, param.buf, param.len) != 0)
            {
                continue;
            }
            stack.mem -= param.mem;
            stack.sec -= param.sec;
            __perf.call(stack);
            __perf._stack._offset = i; //not i-1 that next code will pop(1)
            break;
        }
        __perf._stack.pop(); //pop stack pop(1)

        if (__perf.expire(50))
        {
            __perf.dump(100);
        }
    }
}

uint64_t MurmurHash64A(const void * key, uint64_t len, uint64_t seed)
{
    const uint64_t m = 0xc6a4a7935bd1e995;
    const uint64_t r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len / 8);

    while (data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch (len & 7)
    {
    case 7: h ^= uint64_t(data2[6]) << 48;
    case 6: h ^= uint64_t(data2[5]) << 40;
    case 5: h ^= uint64_t(data2[4]) << 32;
    case 4: h ^= uint64_t(data2[3]) << 24;
    case 3: h ^= uint64_t(data2[2]) << 16;
    case 2: h ^= uint64_t(data2[1]) << 8;
    case 1: h ^= uint64_t(data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

inline void zsummer::luaperf::Performence::call(const LuaStack::Layer & param)
{
    auto founder = _collected.find(param.hash);
    if (founder == _collected.end())
    {
        Collect pi;
        memcpy(pi.buf, param.buf, param.len);
        pi.len = param.len;
        pi.hash = param.hash;
        pi.maxsec = param.sec;
        pi.count = 1;
        pi.mem = param.mem;
        _collected[param.hash] = pi;
    }
    else
    {
        Collect & pi = founder->second;
        if (pi.len != param.len || memcmp(pi.buf, param.buf, pi.len) != 0)
        {
            return;
        }
        pi.count++;
        pi.maxsec = pi.maxsec > param.sec ? pi.maxsec : param.sec;
        pi.mem += param.mem;
        pi.sec += param.sec;
    }
}



std::string zsummer::luaperf::Performence::getProcessID()
{
    std::string pid = "0";
    char buf[260] = { 0 };
#ifdef WIN32
    DWORD winPID = GetCurrentProcessId();
    sprintf(buf, "%06u", winPID);
    pid = buf;
#else
    sprintf(buf, "%06d", getpid());
    pid = buf;
#endif
    return pid;
}




std::string zsummer::luaperf::Performence::getProcessName()
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



void zsummer::luaperf::Performence::serialize(const std::vector<std::unordered_map<uint64_t, Collect>::iterator> & l, const std::string & prefix, const std::string & head, int maxCount)
{
    std::string filename = "./perf";
#ifdef WIN32
    mkdir(filename.c_str());
#else
    mkdir(filename.c_str(),   600);
#endif
    if (true)
    {
        char buf[100];
        time_t cur = time(NULL);
        struct tm *  t = localtime(&cur);
        sprintf(buf, "/%04d%02d%02d_%02d%02d%02d_", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        filename += buf;
    }
    if (_processID.empty() && _processName.empty())
    {
        _processID = getProcessID();
        _processID = _processID.c_str();
        _processName = getProcessName();
        _processName = _processName.c_str();
    }
    filename += _processName;
    filename += "_";
    filename += _processID;
    filename += "_";
    filename += prefix;
    filename += ".md";

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
        temp.assign(o->second.buf, o->second.len);
        temp.append("|");
        if (temp.length() < 70)
        {
            temp.append(70 - temp.length(), ' ');
        }
        temp += "\t\t\t" + toString(o->second.count) + "\t\t|\t\t" + toString(o->second.maxsec) + "\t\t|\t\t" + toString(o->second.avgsec);

        temp += "\t\t|\t\t" + toString(o->second.sec) + "\t\t|\t\t" + toString(o->second.mem) + "\n";

        f.write(temp.c_str(), temp.length());
    }
    f.close();
    _historyFile.push_back(filename);
    while (_historyFile.size() > 10)
    {
        ::remove(_historyFile.front().c_str());
        _historyFile.pop_front();
    }
}



void zsummer::luaperf::Performence::dump(int maxCount)
{
    std::string head = "function name |  call count |  max second | avg second |  total second |  function memory (M)  \n" 
                        "-- | -- | -- | -- | -- | --  \n";
    using PerfIter = std::unordered_map<uint64_t, Collect>::iterator;
    std::vector<PerfIter> orderList;
    for (auto iter = _collected.begin(); iter != _collected.end(); iter++)
    {
        iter->second.avgsec = iter->second.sec / iter->second.count;
        orderList.push_back(iter);
    }

    std::sort(orderList.begin(), orderList.end(), [](const PerfIter & first, const PerfIter & second) {return first->second.sec > second->second.sec; });
    serialize(orderList, "top_total_sec", head, maxCount);


    std::sort(orderList.begin(), orderList.end(), [](const PerfIter & first, const PerfIter & second) {return first->second.maxsec > second->second.maxsec; });
    serialize(orderList, "top_max_sec", head, maxCount);

    std::sort(orderList.begin(), orderList.end(), [](const PerfIter & first, const PerfIter & second) {return first->second.avgsec > second->second.avgsec; });
    serialize(orderList, "top_avg_sec", head, maxCount);


    std::sort(orderList.begin(), orderList.end(), [](const PerfIter & first, const PerfIter & second) {return first->second.count > second->second.count; });
    serialize(orderList, "top_total_ccount", head, maxCount);

    if (PERF_MEM)
    {
        std::sort(orderList.begin(), orderList.end(), [](const PerfIter & first, const PerfIter & second) {return first->second.mem > second->second.mem; });
        serialize(orderList, "top_total_mem", head, maxCount);
    }


}


