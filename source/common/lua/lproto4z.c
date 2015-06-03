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


int luaopen_protoz_bit(lua_State *L);



static const unsigned short __gc_localEndianType = 1;
static bool islocalLittleEndian()
{
    if (*(const unsigned char *)&__gc_localEndianType == 1)
    {
        return true;
    }
    return false;
}

static unsigned long long reversalInteger(unsigned long long org)
{
    unsigned long long ret = 0;
    size_t len = sizeof(unsigned long long);

    unsigned char *dst = (unsigned char*)&ret;
    unsigned char *src = (unsigned char*)org + sizeof(unsigned long long);
    while (len > 0)
    {
        *dst++ = *--src;
        len--;
    }
    return ret;
}


static int checkIntegerBitTrue(lua_State *L)
{
    size_t len = 0;
    const char * stream;
    size_t pos;
    unsigned long long val;
    stream = luaL_checklstring(L, 1, &len);
    if (len != 8)
    {
        return 0;
    }
    val = *(unsigned long long *)stream;
    if (!islocalLittleEndian())
    {
        val = reversalInteger(val);
    }
    pos = luaL_checkinteger(L, 2);

    lua_settop(L, 0);
    
    if (val & (1ULL << pos))
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushnil(L);
    }
    return 1;
}

static int  sequenceToInteger(lua_State *L)
{
    size_t i, len = 0;
    const char * sequence = luaL_checklstring(L, 1, &len);
    unsigned long long num = 0;
    if (len > 64)
    {
        return 0;
    }
    
    for (i = 0; i < len; i++)
    {
        if (sequence[i] == '1')
        {
            num |= (1ULL << i);
        }
        else
        {
            num &= ~(unsigned long long)(1ULL << i);
        }
    }
    if (!islocalLittleEndian())
    {
        num = reversalInteger(num);
    }
    
    lua_pushlstring(L, (const char*)&num, 8);
    return 1;
}


static int streamToString(lua_State *L)
{
    const char * stream = luaL_checkstring(L, -1);
    unsigned long long integer = *(unsigned long long*) stream;
    char buf[50];
    lua_settop(L, 0);
#ifdef WIN32  
    sprintf(buf, "%I64u", integer);
#else
    sprintf(buf, "%llu", integer);
#endif
    lua_pushstring(L, buf);
    return 1;
}

static int stringToStream(lua_State *L)
{
    const char * stream = luaL_checkstring(L, -1);
    unsigned long long integer = 0;
#ifdef WIN32  
    sscanf(stream, "%I64u", &integer);
#else
    sscanf(stream, "%llu", &integer);
#endif
    lua_settop(L, 0);
    lua_pushlstring(L, (const char *)&integer, 8);
    return 1;
}


static luaL_Reg checkBit[] = {
    { "checkIntegerBitTrue", checkIntegerBitTrue },
    { "sequenceToInteger", sequenceToInteger },
    { "streamToString", streamToString },
    { "stringToStream", stringToStream },

    { NULL, NULL }
};


int luaopen_protoz_bit(lua_State *L)
{
    lua_getglobal(L, "Proto4z");
    if (lua_isnil(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, "Proto4z");
    }
    
    luaL_Reg *l;
    for (l = checkBit; l->name != NULL; l++) {
        lua_pushcclosure(L, l->func, 0);  /* closure with those upvalues */
        lua_setfield(L, -2, l->name);
    }
    lua_pop(L, 1);
    return 0;
}

