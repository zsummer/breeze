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
#ifndef _ZSUMMERX_UDPSOCKET_IMPL_H_
#define _ZSUMMERX_UDPSOCKET_IMPL_H_

#include "common_impl.h"
#include "iocp_impl.h"

namespace zsummer
{
    namespace network
    {
        class UdpSocket : public std::enable_shared_from_this<UdpSocket>
        {
        public:
            UdpSocket();
            ~UdpSocket();
            bool initialize(const EventLoopPtr &summer, const char *localIP, unsigned short localPort);
            bool doSendTo(char * buf, unsigned int len, const char *dstip, unsigned short dstport);
            bool onIOCPMessage(BOOL bSuccess, DWORD dwTranceBytes, unsigned char cType);
            bool doRecvFrom(char * buf, unsigned int len, _OnRecvFromHandler &&handler);
        public:
            //private
            EventLoopPtr _summer;
            
            SOCKET        _socket;
            SOCKADDR_IN    _addr;

            //recv
            ExtendHandle _recvHandle;
            WSABUF         _recvWSABuf;
            sockaddr_in  _recvFrom;
            int             _recvFromLen;
            _OnRecvFromHandler _onRecvHander;
            LINK_STATUS _linkStatus;
        };
        using UdpSocketPtr = std::shared_ptr<UdpSocket>;
    }
}
























#endif











