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

#ifndef _ZSUMMER_TCPSOCKET_IMPL_H_
#define _ZSUMMER_TCPSOCKET_IMPL_H_



#include "common_impl.h"
#include "epoll_impl.h"

namespace zsummer
{
    namespace network
    {

        class TcpSocket : public std::enable_shared_from_this<TcpSocket>
        {
        public:
            TcpSocket();
            ~TcpSocket();
            bool setNoDelay();
            inline void setFloodSendOptimize(bool enable){_floodSendOptimize = enable;}
            bool initialize(const EventLoopPtr& summer);
            inline bool getPeerInfo(std::string& remoteIP, unsigned short &remotePort)
            {
                remoteIP = _remoteIP;
                remotePort = _remotePort;
                return true;
            }
            bool doConnect(const std::string &remoteIP, unsigned short remotePort, _OnConnectHandler && handler);
            bool doSend(char * buf, unsigned int len, _OnSendHandler && handler);
            bool doRecv(char * buf, unsigned int len, _OnRecvHandler && handler, bool daemonRecv = false);
            bool doClose();

            
        public:
            void OnPostClose();
            void onEPOLLMessage(uint32_t event);
            bool attachSocket(int fd, const std::string& remoteIP, unsigned short remotePort, bool isIPV6);
        private:
            std::string logSection();
        private:
            EventLoopPtr _summer;
            std::string _remoteIP;
            unsigned short _remotePort = 0;
            bool _isIPV6 = false;
            bool _daemonRecv = false;
            bool _floodSendOptimize = true;
            EventData _eventData;
            
            _OnConnectHandler _onConnectHandler;

            _OnRecvHandler _onRecvHandler;
            unsigned int _recvLen = 0;
            char    *     _recvBuf = NULL;
            unsigned int _recvOffset = 0;

            _OnSendHandler _onSendHandler;
            unsigned int _sendLen = 0;
            char *         _sendBuf = NULL;
        };
        using TcpSocketPtr = std::shared_ptr<TcpSocket>;
    }

}


#endif


