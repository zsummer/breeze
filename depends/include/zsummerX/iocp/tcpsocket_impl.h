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
#ifndef _ZSUMMERX_TCPSOCKET_IMPL_H_
#define _ZSUMMERX_TCPSOCKET_IMPL_H_

#include "common_impl.h"
#include "iocp_impl.h"
namespace zsummer
{
    namespace network
    {
        class TcpSocket : public std::enable_shared_from_this<TcpSocket>
        {
        public:

            TcpSocket();
            ~TcpSocket();
            //! initialize an attach socket to zsummer pump.
            //if the socket is used to connect,  It's need initialize before call doConnect 
            // if the socket is used to accept new socket, It's need initialize after OnAccept. 
            bool initialize(const EventLoopPtr& summer);
            bool setNoDelay();
            inline bool getPeerInfo(std::string& remoteIP, unsigned short &remotePort)
            {
                remoteIP = _remoteIP;
                remotePort = _remotePort;
                return true;
            }
            //! handle: void(zsummer::network::NetErrorCode);
            //! handle: NetErrorCode: 0 success. other code is failed  and can see error code in enum NetErrorCode 
            bool doConnect(const std::string& remoteIP, unsigned short remotePort, _OnConnectHandler && handler);
            //!handle:  void(NetErrorCode, int)
            //!handle:  NetErrorCode: 0 success. other code is failed  and can see error code in enum NetErrorCode 
            //!handle:  int: is transfer length. if not all data already transfer that you need call doSend transfer the remnant data.
            //! warning: when  handler is not callback ,  the function can not call repeat. if you have some question maybe you need read the test or implementation .
            //!          so,  when you want  repeat send data without care the callback , you need encapsulate the send operate via a send queue like the StressTest/FrameTest source code
            bool doSend(char * buf, unsigned int len, _OnSendHandler &&handler);
            //!handle:  void(NetErrorCode, int)
            //!handle:  NetErrorCode: 0 success. other code is failed  and can see error code in enum NetErrorCode 
            //!handle:  int: is received data  length. it maybe short than you want received data (len).
            //! buf: you recv buffer memory address . you would block the buffer still the handler callback .
            //! len: you want recv data for max bytes .
            //! warning: when  handler is not callback ,  the function can not call repeat. if you have some question maybe you need read the test or implementation .
            bool doRecv(char * buf, unsigned int len, _OnRecvHandler && handler);
            //close this socket.
            //warning : at a safe close method , if you have doConnect/doRecv/doSend request and not all callback. you need wait callback .  the callback will return with a error code.
            //         if you have not the operate and when you doClose the socket and immediate destroy this class object . in next do zsummerx's runOnce(), callback may be return and call operate in the bad memory . 
            bool doClose();
        public:
            bool attachSocket(SOCKET s, std::string remoteIP, unsigned short remotePort, bool isIPV6);
            void onIOCPMessage(BOOL bSuccess, DWORD dwTranceBytes, unsigned char cType);
            std::string logSection();
        public:
            //private
            EventLoopPtr  _summer;
            SOCKET        _socket = INVALID_SOCKET;
            std::string _remoteIP;
            unsigned short _remotePort = 0;
            bool _isIPV6 = false;
            //recv
            ExtendHandle _recvHandle;
            WSABUF         _recvWSABuf;
            _OnRecvHandler _onRecvHandler;


            //send
            ExtendHandle _sendHandle;
            WSABUF         _sendWsaBuf;
            _OnSendHandler _onSendHandler;


            //connect
            ExtendHandle _connectHandle;
            _OnConnectHandler _onConnectHandler;
            //status
            int _linkStatus = LS_UNINITIALIZE;
        };
        using TcpSocketPtr = std::shared_ptr<TcpSocket>;

    }
}
























#endif











