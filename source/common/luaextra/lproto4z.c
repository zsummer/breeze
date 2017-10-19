/*
 * proto4z License
 * -----------
 * 
 * proto4z is licensed under the terms of the MIT license reproduced below.
 * This means that proto4z is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2013-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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




#include "lua.h"
#include "lauxlib.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <time.h>
#include <sys/time.h>
#endif // WIN32

#ifdef __APPLE__
#include<mach/mach_time.h>
#endif // __APPLE__

int luaopen_proto4z_util(lua_State *L);



static int newTag(lua_State * L)
{
    unsigned long long tag = 0;
    lua_pushlstring(L, (const char*)&tag, sizeof(tag));
    return 1;
}

static int setTag(lua_State * L)
{
    unsigned long long tag = 0;
    const char * luaTag = luaL_checkstring(L, 1);
    int n = (int)luaL_checkinteger(L, 2);
    memcpy(&tag, luaTag, sizeof(tag));
    tag |= (unsigned long long)1 << (n - 1);
    lua_pushlstring(L, (const char*)&tag, sizeof(tag));
    return 1;
}

static int unsetTag(lua_State * L)
{
    unsigned long long tag = 0;
    const char * luaTag = luaL_checkstring(L, 1);
    int n = (int)luaL_checkinteger(L, 2);
    memcpy(&tag, luaTag, sizeof(tag));
    tag &= ~((unsigned long long)1 << (n - 1));
    lua_pushlstring(L, (const char*)&tag, sizeof(tag));
    return 1;
}

static int testTag(lua_State * L)
{
    unsigned long long tag = 0;
    const char * luaTag = luaL_checkstring(L, 1);
    int n = (int)luaL_checkinteger(L, 2);
    memcpy(&tag, luaTag, sizeof(tag));
    int ret = tag & ((unsigned long long)1 << (n - 1));
    lua_pushboolean(L, ret);
    return 1;
}



static void printPackError(lua_State * L, const char *tp, const char * desc)
{
    char buf[200] = { 0 };
    lua_getglobal(L, "print");
    sprintf(buf, "pack warning. the value is nil when pack [%s].[%s]. it's will replace by default value.", desc, tp);
    lua_pushstring(L, buf);
    lua_pcall(L, 1, 0, 0);
}



static int pack(lua_State * L)
{
    const char * tp = luaL_checkstring(L, 2);
    const char * desc = luaL_optstring(L, 3, "");



    while (*tp == ' ') tp++;

    if (tp[0] == 'i')
    {
        if (tp[1] == '8' && tp[2] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            char v = (char)luaL_optinteger(L, 1, 0);
            lua_pushlstring(L, &v, 1);
        }
        else if (tp[1] == '1' && tp[2] == '6' && tp[3] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            short v = (short)luaL_optinteger(L, 1, 0);
            lua_pushlstring(L, (const char *)&v, 2);
        }
        else if (tp[1] == '3' && tp[2] == '2' && tp[3] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            int v = (int)luaL_optinteger(L, 1, 0);
            lua_pushlstring(L, (const char *)&v, 4);
        }
        else if (tp[1] == '6' && tp[2] == '4' && tp[3] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            long long v = 0;
            if (lua_isinteger(L, 1))
            {
                v = (long long)luaL_optinteger(L, 1, 0);
            }
            else
            {
                v = (long long)luaL_optnumber(L, 1, 0);
            }
            lua_pushlstring(L, (char*)&v, 8);
        }
    }
    else if (tp[0] == 'u' && tp[1] == 'i' )
    {

        if (tp[2] == '8' && tp[3] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            unsigned char v = (unsigned char)(unsigned long long)luaL_optinteger(L, 1, 0);
            lua_pushlstring(L, (const char *)&v, 1);
        }
        else if (tp[2] == '1' && tp[3] == '6' && tp[4] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            unsigned short v = (unsigned short)(unsigned long long)luaL_optinteger(L, 1, 0);
            lua_pushlstring(L, (const char *)&v, 2);
        }
        else if (tp[2] == '3' && tp[3] == '2' && tp[4] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            unsigned int v = (unsigned int)(unsigned long long)luaL_optinteger(L, 1, 0);
            lua_pushlstring(L, (const char *)&v, 4);
        }
        else if (tp[2] == '6' && tp[3] == '4' && tp[4] == 0)
        {
            if (lua_isnil(L, 1)) printPackError(L, tp, desc);
            unsigned long long v = 0;
            if (lua_isinteger(L, 1))
            {
                v = (unsigned long long)luaL_optinteger(L, 1, 0);
            }
            else
            {
                v = (unsigned long long)luaL_optnumber(L, 1, 0);
            }
            lua_pushlstring(L, (char*)&v, 8);
        }
    }
    else if (tp[0] == 'f' && strcmp(tp, "float") == 0)
    {
        if (lua_isnil(L, 1)) printPackError(L, tp, desc);
        float v = (float)luaL_optnumber(L, 1, 0.0f);
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (tp[0] == 'd' && strcmp(tp, "double") == 0)
    {
        if (lua_isnil(L, 1)) printPackError(L, tp, desc);
        double v = (double)luaL_optnumber(L, 1, 0.0f);
        lua_pushlstring(L, (const char *)&v, 8);
    }
    else 
    {
        printPackError(L, tp, desc);
        return 0;
    }
    return 1;
}

static void printUnpackError(lua_State * L, size_t pos, size_t dataLen, const char *tp)
{
    char buf[200] = { 0 };
    lua_getglobal(L, "print");
    sprintf(buf, "unpack error. the current pos is invalid. cur pos=%u, type=%s, blockSize=%u", (unsigned int)pos, tp, (unsigned int)dataLen);
    lua_pushstring(L, buf);
    lua_pcall(L, 1, 0, 0);
}
static int unpack(lua_State * L)
{
    size_t dataLen = 0;
    const char * data = luaL_checklstring(L, 1, &dataLen);
    size_t pos = (size_t)luaL_checkinteger(L, 2);
    const char * tp = luaL_checkstring(L, 3);
    if (pos < 1 || (size_t)pos > dataLen)
    {
        printUnpackError(L, pos, dataLen, "any");
        return 0;
    }


    while (*tp == ' ') tp++;


    if (tp[0] == 'i')
    {
        if (tp[1] == '8' && tp[2] == 0)
        {
            if (pos - 1 + 1 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "i8");
                return 0;
            }
            char ch = (char)data[pos - 1];
            lua_pushinteger(L, ch);
            lua_pushinteger(L, pos + 1);
        }
        else if (tp[1] == '1' && tp[2] == '6' && tp[3] == 0)
        {
            if (pos - 1 + 2 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "i16");
                return 0;
            }
            short v = 0;
            memcpy(&v, &data[pos - 1], 2);

            lua_pushinteger(L, v);
            lua_pushinteger(L, pos + 2);
        }
        else if (tp[1] == '3' && tp[2] == '2' && tp[3] == 0)
        {
            if (pos - 1 + 4 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "i32");
                return 0;
            }
            int v = 0;
            memcpy(&v, &data[pos - 1], 4);

            lua_pushinteger(L, v);
            lua_pushinteger(L, pos + 4);
        }
        else if (tp[1] == '6' && tp[2] == '4' && tp[3] == 0)
        {
            if (pos - 1 + 8 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "i64");
                return 0;
            }

            long long v = 0;
            memcpy(&v, &data[pos - 1], 8);

            if (sizeof(lua_Integer) >=8)
            {
                lua_pushinteger(L, v);
            }
            else
            {
                lua_pushnumber(L, (double)v);
            }

            lua_pushinteger(L, pos + 8);
        }
    }
    else if (tp[0] == 'u' && tp[1] == 'i')
    {
        if (tp[2] == '8' && tp[3] == 0)
        {
            if (pos - 1 + 1 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "ui8");
                return 0;
            }
            unsigned char ch = (unsigned char)data[pos - 1];
            lua_pushinteger(L, ch);
            lua_pushinteger(L, pos + 1);
        }
        else if (tp[2] == '1' && tp[3] == '6' && tp[4] == 0)
        {
            if (pos - 1 + 2 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "ui16");
                return 0;
            }
            unsigned short v = 0;
            memcpy(&v, &data[pos - 1], 2);

            lua_pushinteger(L, v);
            lua_pushinteger(L, pos + 2);
        }
        else if (tp[2] == '3' && tp[3] == '2' && tp[4] == 0)
        {
            if (pos - 1 + 4 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "ui32");
                return 0;
            }
            unsigned int v = 0;
            memcpy(&v, &data[pos - 1], 4);

            lua_pushinteger(L, v);
            lua_pushinteger(L, pos + 4);
        }
        else if (tp[2] == '6' && tp[3] == '4' && tp[4] == 0)
        {
            if (pos - 1 + 8 > dataLen)
            {
                printUnpackError(L, pos, dataLen, "ui64");
                return 0;
            }

            unsigned long long v = 0;
            memcpy(&v, &data[pos - 1], 8);

            if (sizeof(lua_Integer) >= 8)
            {
                lua_pushinteger(L, (long long)v);
            }
            else
            {
                lua_pushnumber(L, (double)v);
            }
            lua_pushinteger(L, pos + 8);
        }
    }
    else if (tp[0] == 'f' && strcmp(tp, "float") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            printUnpackError(L, pos, dataLen, "float");
            return 0;
        }
        float v = 0;
        memcpy(&v, &data[pos - 1], 4);
        lua_pushnumber(L, v);
        lua_pushinteger(L, pos + 4);
    }
    else if (tp[0] == 'd' && strcmp(tp, "double") == 0)
    {
        if (pos - 1 + 8 > dataLen)
        {
            printUnpackError(L, pos, dataLen, "double");
            return 0;
        }
        double v = 0;
        memcpy(&v, &data[pos - 1], 8);
        lua_pushnumber(L, v);
        lua_pushinteger(L, pos + 8);
    }
    else if (tp[0] == 's' && strcmp(tp, "string") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            printUnpackError(L, pos, dataLen, "string/head");
            return 0;
        }
        unsigned int strLen = 0;
        memcpy(&strLen, &data[pos - 1], 4);
        pos += 4;
        if (pos - 1 + strLen > dataLen)
        {
            printUnpackError(L, pos, dataLen, "string/body");
            return 0;
        }
        lua_pushlstring(L, &data[pos - 1], strLen);
        lua_pushinteger(L, pos + strLen);
    }
    else
    {
        lua_pushnil(L);
        lua_pushinteger(L, pos);
        return 2;
    }
    return 2;
}

static int steadyTime(lua_State * L)
{
    unsigned int ret = 0;
#ifdef WIN32
    ret = GetTickCount();
#elif defined(__APPLE__)
    const int64_t kOneMillion = 1000 * 1000;
    mach_timebase_info_data_t timebase_info;
    mach_timebase_info(&timebase_info);
    ret = (unsigned int)((mach_absolute_time() * timebase_info.numer) / (kOneMillion * timebase_info.denom));
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts) != 0)
        ret = 0;
    ret = ts.tv_sec * 1000 + (ts.tv_nsec / 1000 / 1000);
#endif
    lua_pushinteger(L, ret);
    return 1;
}


static luaL_Reg tagReg[] = {

    //一个空的8字节tag 
    { "newTag", newTag }, 

    //设置第N位为1,  N的起始坐标是1.  
    //example: local newTag = setTag(oldTag, 1)
    { "setTag", setTag },

    //设置第N位为0, N的起始坐标是1  
    //example: local newTag = unsetTag(oldTag, 1)
    { "unsetTag", unsetTag }, 

    //检查第N位是否为1.  
    //example: local isSet = testTag(tag, 1)
    { "testTag", testTag },

    //把一个lua数据按照类型说明序列化成一段二进制流.
    //支持i8,ui8, i16, ui16, i32, ui32, i64, ui64, float, double, string. 
    //example: local block = pack(obj, "ui32", "desc")
    { "pack", pack }, 

    //从二进制流中流出一个元素 并返回下一个元素开始的下标位置. 
    //example: local len , pos unpck(block, pos, "ui32")  
    { "unpack", unpack }, 

    //获取一个稳定的tick计数 毫秒级. 
    //example: local nowTick = steadyTime()
    { "now", steadyTime }, 

    { NULL, NULL }
};


int luaopen_proto4z_util(lua_State *L)
{
    lua_newtable(L);
    luaL_Reg *l;
    for (l = tagReg; l->name != NULL; l++) 
    {
        lua_pushcclosure(L, l->func, 0);
        lua_setfield(L, -2, l->name);
    }
    lua_setglobal(L, "Proto4zUtil");
    return 0;
}

