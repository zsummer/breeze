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
 * Copyright (C) 2013-2015 YaweiZhang <yawei.zhang@foxmail.com>.
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

static const unsigned short __gc_localEndianType = 1;
static int isLittleEndian()
{
    if (*(const unsigned char *)&__gc_localEndianType == 1)
    {
        return 1;
    }
    return 0;
}

void byteRevese(char * buf, unsigned int bytes)
{
    char tmp = 0;
    char *dst = buf;
    char *src = buf + bytes;
    bytes /= 2;
    while (bytes > 0)
    {
        tmp = *dst;
        *dst++ = *--src;
        *src = tmp;
        bytes--;
    }
    return;
}


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

static int pack(lua_State * L)
{
    const char * tp = luaL_checkstring(L, 2);

    if (strcmp(tp, "i8") == 0)
    {
        char v = (char)luaL_checkinteger(L, 1);
        lua_pushlstring(L, &v, 1);
    }
    else if (strcmp(tp, "ui8") == 0)
    {
        unsigned char v = (unsigned char)luaL_checkinteger(L, 1);
        lua_pushlstring(L, (const char *)&v, 1);
    }
    else if (strcmp(tp, "i16") == 0)
    {
        short v = (short)luaL_checkinteger(L, 1);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 2);
        }
        lua_pushlstring(L, (const char *)&v, 2);
    }
    else if (strcmp(tp, "ui16") == 0)
    {
        unsigned short v = (unsigned short)luaL_checkinteger(L, 1);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 2);
        }
        lua_pushlstring(L, (const char *)&v, 2);
    }
    else if (strcmp(tp, "i32") == 0)
    {
        int v = (int)luaL_checkinteger(L, 1);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (strcmp(tp, "ui32") == 0)
    {
        unsigned int v = (unsigned int)luaL_checkinteger(L, 1);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (strcmp(tp, "i64") == 0 || strcmp(tp, "ui64") == 0)
    {
        if (lua_isstring(L, 1))
        {
            size_t len = 0;
            const char * str = luaL_checklstring(L, 1, &len);
            if (len < 50)
            {
                if (strcmp(tp, "i64") == 0)
                {
                    long long v = 0;
#ifdef WIN32  
                    sscanf(str, "%I64d", &v);
#else
                    sscanf(str, "%lld", &v);
#endif
                    if (!isLittleEndian())
                    {
                        byteRevese((char*)&v, 8);
                    }
                    lua_pushlstring(L, (char*)&v, 8);

                }
                else
                {
                    unsigned long long v = 0;
#ifdef WIN32  
                    sscanf(str, "%I64u", &v);
#else
                    sscanf(str, "%llu", &v);
#endif
                    if (!isLittleEndian())
                    {
                        byteRevese((char*)&v, 8);
                    }
                    lua_pushlstring(L, (char*)&v, 8);
                }
            }

        }
        else
        {
            unsigned long long v = (unsigned long long)luaL_checkinteger(L, 1);
            if (!isLittleEndian())
            {
                byteRevese((char*)&v, 8);
            }
            lua_pushlstring(L, (char*)&v, 8);
        }
    }
    else if (strcmp(tp, "float") == 0)
    {
        float v = (float)luaL_checknumber(L, 1);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (strcmp(tp, "double") == 0)
    {
        double v = (double)luaL_checknumber(L, 1);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 8);
        }
        lua_pushlstring(L, (const char *)&v, 8);
    }
    else
    {
        return 0;
    }
    return 1;
}

static void printError(lua_State * L, size_t pos, size_t dataLen, const char *tp)
{
    char buf[100] = { 0 };
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
        printError(L, pos, dataLen, "any");
        return 0;
    }
    
    if (strcmp(tp, "i8") == 0)
    {
        if (pos - 1 + 1 > dataLen)
        {
            printError(L, pos, dataLen, "i8");
            return 0;
        }
        char ch = (char)data[pos - 1];
        lua_pushinteger(L, ch);
        lua_pushinteger(L, pos + 1);
    }
    else if (strcmp(tp, "ui8") == 0)
    {
        if (pos - 1 + 1 > dataLen)
        {
            printError(L, pos, dataLen, "ui8");
            return 0;
        }
        unsigned char ch = (unsigned char)data[pos - 1];
        lua_pushinteger(L, ch);
        lua_pushinteger(L, pos + 1);
    }
    else if (strcmp(tp, "i16") == 0)
    {
        if (pos - 1 + 2 > dataLen)
        {
            printError(L, pos, dataLen, "i16");
            return 0;
        }
        short v = 0;
        memcpy(&v, &data[pos - 1], 2);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 2);
        }
        lua_pushinteger(L, v);
        lua_pushinteger(L, pos + 2);
    }
    else if (strcmp(tp, "ui16") == 0)
    {
        if (pos - 1 + 2 > dataLen)
        {
            printError(L, pos, dataLen, "ui16");
            return 0;
        }
        unsigned short v = 0;
        memcpy(&v, &data[pos - 1], 2);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 2);
        }
        lua_pushinteger(L, v);
        lua_pushinteger(L, pos + 2);
    }
    else if (strcmp(tp, "i32") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            printError(L, pos, dataLen, "i32");
            return 0;
        }
        int v = 0;
        memcpy(&v, &data[pos - 1], 4);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushinteger(L, v);
        lua_pushinteger(L, pos + 4);
    }
    else if (strcmp(tp, "ui32") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            printError(L, pos, dataLen, "ui32");
            return 0;
        }
        unsigned int v = 0;
        memcpy(&v, &data[pos - 1], 4);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushinteger(L, v);
        lua_pushinteger(L, pos + 4);
    }
    else if (strcmp(tp, "i64") == 0 || strcmp(tp, "ui64") == 0)
    {
        if (pos - 1 + 8 > dataLen)
        {
            printError(L, pos, dataLen, "i64/ui64");
            return 0;
        }
/*        {
            lua_pushlstring(L, &data[pos - 1], 8);
            lua_pushinteger(L, pos + 8);
        } */

        {
            unsigned long long v = 0;
            memcpy(&v, &data[pos - 1], 8);
            if (!isLittleEndian())
            {
                byteRevese((char*)&v, 8);
            }

            char buf[50] = { 0 };
            if (strcmp(tp, "i64") == 0)
            {
#ifdef WIN32  
                sprintf(buf, "%I64d", (long long)v);
#else
                sprintf(buf, "%lld", (long long)v);
#endif
            }
            else
            {
#ifdef WIN32  
                sprintf(buf, "%I64u", v);
#else
                sprintf(buf, "%llu", v);
#endif
            }
            lua_pushstring(L, buf);
            lua_pushinteger(L, pos + 8);
        }
    }
    else if (strcmp(tp, "float") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            printError(L, pos, dataLen, "float");
            return 0;
        }
        float v = 0;
        memcpy(&v, &data[pos - 1], 4);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushnumber(L, v);
        lua_pushinteger(L, pos + 4);
    }
    else if (strcmp(tp, "double") == 0)
    {
        if (pos - 1 + 8 > dataLen)
        {
            printError(L, pos, dataLen, "double");
            return 0;
        }
        double v = 0;
        memcpy(&v, &data[pos - 1], 8);
        if (!isLittleEndian())
        {
            byteRevese((char*)&v, 8);
        }
        lua_pushnumber(L, v);
        lua_pushinteger(L, pos + 8);
    }
    else if (strcmp(tp, "string") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            printError(L, pos, dataLen, "string/head");
            return 0;
        }
        unsigned int strLen = 0;
        memcpy(&strLen, &data[pos - 1], 4);
        if (!isLittleEndian())
        {
            byteRevese((char*)&strLen, 4);
        }
        pos += 4;
        if (pos - 1 + strLen > dataLen)
        {
            printError(L, pos, dataLen, "string/body");
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
    //example: local block = pack(obj, "ui32")
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

