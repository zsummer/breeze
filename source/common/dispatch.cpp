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

#include "dispatch.h"

using namespace zsummer::proto4z;
using namespace zsummer::network;

MessageDispatcher & MessageDispatcher::getRef()
{
    static MessageDispatcher _manager;
    return _manager;
}


void MessageDispatcher::dispatchSessionMessage(TcpSessionPtr  &session, ProtoID pID, zsummer::proto4z::ReadStream & msg)
{
    MapProtoDispatch::iterator iter = _mapSessionDispatch.find(pID);
    if (iter == _mapSessionDispatch.end() )
    {
        LCW("Entry dispatchSessionMessage[" << pID << "] Failed: UNKNOWN ProtoID.  SessionID=" << session->getSessionID() << ", ProtoID=" << pID);
        return;
    }
    try
    {
        if (iter != _mapSessionDispatch.end() && !iter->second.empty())
        {
            for (auto & fun : iter->second)
            {
                //LCT("Entry dispatchSessionMessage[" << pID << "]  SessionID=" << session->getSessionID());
                msg.resetMoveCursor();
                fun(session,  msg);
            }
        }
        //LCT("Leave dispatchSessionMessage[" << pID << "]  SessionID=" << session->getSessionID());
    }
    catch (std::runtime_error e)
    {
        LCE("Leave dispatchSessionMessage[" << pID << "] With Runtime Error: SessionID=" << session->getSessionID() << ", rsLen=" << msg.getStreamLen() << ", Error Message=\"" << e.what() << "\"");
    }
    catch (...)
    {
        LCE("Leave dispatchSessionMessage[" << pID << "] With Unknown Runtime Error: SessionID=" << session->getSessionID());
    }
}


