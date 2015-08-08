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
static int isEndianType()
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
        if (!isEndianType())
        {
            byteRevese((char*)&v, 2);
        }
        lua_pushlstring(L, (const char *)&v, 2);
    }
    else if (strcmp(tp, "ui16") == 0)
    {
        unsigned short v = (unsigned short)luaL_checkinteger(L, 1);
        if (!isEndianType())
        {
            byteRevese((char*)&v, 2);
        }
        lua_pushlstring(L, (const char *)&v, 2);
    }
    else if (strcmp(tp, "i32") == 0)
    {
        int v = (int)luaL_checkinteger(L, 1);
        if (!isEndianType())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (strcmp(tp, "ui32") == 0)
    {
        unsigned int v = (unsigned int)luaL_checkinteger(L, 1);
        if (!isEndianType())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (strcmp(tp, "i64") == 0 || strcmp(tp, "ui64") == 0)
    {
        lua_pushvalue(L, 1);
    }
    else if (strcmp(tp, "float") == 0)
    {
        float v = (float)luaL_checknumber(L, 1);
        if (!isEndianType())
        {
            byteRevese((char*)&v, 4);
        }
        lua_pushlstring(L, (const char *)&v, 4);
    }
    else if (strcmp(tp, "double") == 0)
    {
        double v = (double)luaL_checknumber(L, 1);
        if (!isEndianType())
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


static int unpack(lua_State * L)
{
    size_t dataLen = 0;
    const char * data = luaL_checklstring(L, 1, &dataLen);
    int pos = (int)luaL_checkinteger(L, 2);
    const char * tp = luaL_checkstring(L, 3);
    if (pos < 1 || (size_t)pos > dataLen)
    {
        return 0;
    }
    
    if (strcmp(tp, "i8") == 0)
    {
        if (pos - 1 + 1 > dataLen)
        {
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
            return 0;
        }
        short v = 0;
        memcpy(&v, &data[pos - 1], 2);
        if (!isEndianType())
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
            return 0;
        }
        unsigned short v = 0;
        memcpy(&v, &data[pos - 1], 2);
        if (!isEndianType())
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
            return 0;
        }
        int v = 0;
        memcpy(&v, &data[pos - 1], 4);
        if (!isEndianType())
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
            return 0;
        }
        unsigned int v = 0;
        memcpy(&v, &data[pos - 1], 4);
        if (!isEndianType())
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
            return 0;
        }
        lua_pushlstring(L, &data[pos - 1], 8);
        lua_pushinteger(L, pos + 8);
    }
    else if (strcmp(tp, "float") == 0)
    {
        if (pos - 1 + 4 > dataLen)
        {
            return 0;
        }
        float v = 0;
        memcpy(&v, &data[pos - 1], 4);
        if (!isEndianType())
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
            return 0;
        }
        double v = 0;
        memcpy(&v, &data[pos - 1], 8);
        if (!isEndianType())
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
            return 0;
        }
        unsigned int strLen = 0;
        memcpy(&strLen, &data[pos - 1], 4);
        if (!isEndianType())
        {
            byteRevese((char*)&strLen, 4);
        }
        pos += 4;
        if (pos - 1 + strLen > dataLen)
        {
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

static int checkULL(lua_State * L)
{
    unsigned long long num = 0;
    size_t strLen = 0;
    const char * str = luaL_checklstring(L, 1, &strLen);
    int isULL = false;
    int i = 0;
    if (strLen == 8)
    {
        for (i = 0; i < 8; i++)
        {
            if (str[i] >126 || str[i] < 32)
            {
                isULL = true;
                break;
            }
        }
    }
    char buf[50];
    if (isULL)
    {
        memcpy(&num, str, 8);
#ifdef WIN32  
        sprintf(buf, "%I64d", num);
#else
        sprintf(buf,"%lld", num);
#endif
    }
    else
    {
        sprintf(buf, "\"%s\"", str);
    }
    lua_pushstring(L, buf);
    return 1;
}

static luaL_Reg tagReg[] = {
    { "newTag", newTag },
    { "setTag", setTag },
    { "unsetTag", unsetTag },
    { "testTag", testTag },
    { "pack", pack },
    { "unpack", unpack },
    { "now", steadyTime },
    { "checkULL",checkULL },
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

