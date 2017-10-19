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

#ifndef _ZSUMMER_UDPSOCKET_IMPL_H_
#define _ZSUMMER_UDPSOCKET_IMPL_H_



#include "common_impl.h"
#include "epoll_impl.h"

namespace zsummer
{
    namespace network
    {

        class UdpSocket : public std::enable_shared_from_this<UdpSocket>
        {
        public:
            // const char * remoteIP, unsigned short remotePort, nTranslate
            UdpSocket();
            ~UdpSocket();
            bool initialize(const EventLoopPtr &summer, const char *localIP, unsigned short localPort);
            bool doRecvFrom(char * buf, unsigned int len, _OnRecvFromHandler&& handler);
            bool doSendTo(char * buf, unsigned int len, const char *dstip, unsigned short dstport);
            bool onEPOLLMessage(uint32_t event);
        public:
            EventLoopPtr _summer;
            EventData _eventData;

            _OnRecvFromHandler _onRecvFromHandler;
            unsigned int _recvLen;
            char    *     _recvBuf;
        };
        using UdpSocketPtr = std::shared_ptr<UdpSocket>;
    }

}



#endif



