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
 * Copyright (C) 2010-2016 YaweiZhang <yawei.zhang@foxmail.com>.
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

#ifndef BREEZE_SLOT_H_
#define BREEZE_SLOT_H_
#include "defined.h"


using Slot = std::function < void(zsummer::network::TcpSessionPtr&, const Tracing & trace, zsummer::proto4z::ReadStream &) >;


using ProtoID = zsummer::proto4z::ProtoInteger;
const ProtoID InvalidProtoID = -1;

class EntitySlot
{
public:
    EntitySlot(){}
    virtual ~EntitySlot(){};
    inline void setEntityName(const std::string &entity){ _entity = entity; }
    inline std::string getEntityName(){ return _entity; }
    inline void setEntityID(UserID uID){ _uID = uID; }
    inline UserID getEntityID(){ return _uID; }

    using Slots = std::unordered_map<unsigned short, Slot>;
    inline void slotting(ProtoID protoID,  const Slot & msgfun){ _slots[protoID]=msgfun; }
    inline void call(TcpSessionPtr  &session, const Tracing & trace, const char * block, unsigned int len);
protected:
    Slots _slots;
    std::string _entity;
    UserID _uID = InvalidUserID;
};


inline void EntitySlot::call(TcpSessionPtr  &session, const Tracing & trace, const char * block, unsigned int len)
{
    try
    {
        ReadStream rs(block, len);
        auto founder = _slots.find(rs.getProtoID());
        if (founder != _slots.end())
        {
            (founder->second)(session, trace, rs);
        }
    }
    catch (std::runtime_error e)
    {

    }
}

#endif


