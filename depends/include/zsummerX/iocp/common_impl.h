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
#pragma once

#ifndef _ZSUMMERX_COMMON_IMPL_H_
#define _ZSUMMERX_COMMON_IMPL_H_

#include "../common/common.h"




namespace zsummer
{
    namespace network
    {
        class TcpSocket;
        class TcpAccept;
        class UdpSocket;
        const int InvalidFD = -1;
        struct ExtendHandle 
        {
            OVERLAPPED     _overlapped;
            unsigned char _type;
            std::shared_ptr<TcpSocket> _tcpSocket;
            std::shared_ptr<TcpAccept> _tcpAccept;
            std::shared_ptr<UdpSocket> _udpSocket;
            enum HANDLE_TYPE
            {
                HANDLE_ACCEPT, 
                HANDLE_RECV, 
                HANDLE_SEND,
                HANDLE_CONNECT, 
                HANDLE_RECVFROM,
                HANDLE_SENDTO,
            };
        };
        template <class T>
        T & operator <<(T &t, const ExtendHandle & h)
        {
            t << (unsigned int)h._type;
            return t;
        }
        //! 完成键
        enum POST_COM_KEY
        {
            PCK_USER_DATA,
        };
#define HandlerFromOverlaped(ptr)  ((ExtendHandle*)((char*)ptr - (char*)&((ExtendHandle*)NULL)->_overlapped))
    }
}





















#endif











