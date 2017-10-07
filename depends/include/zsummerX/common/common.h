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
#pragma once

#ifndef _ZSUMMERX_COMMON_H_
#define _ZSUMMERX_COMMON_H_

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#pragma comment(lib, "ws2_32")
#else
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#endif

#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <utility>

#include <memory>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <algorithm>
#include <log4z/log4z.h>
#include <rc4/rc4_encryption.h>
#include <atomic>

namespace zsummer
{
    namespace network
    {
        //! NetErrorCode
        enum NetErrorCode
        {
            NEC_SUCCESS = 0,
            NEC_ERROR,
            NEC_REMOTE_CLOSED,
        };

        class TcpSocket;
        using TcpSocketPtr = std::shared_ptr<TcpSocket>;

        //! post callback
        using _OnPostHandler = std::function<void()>;
        //timer callback
        using _OnTimerHandler = std::function<void()>;
        //accept callback
        using _OnAcceptHandler = std::function<void(NetErrorCode, TcpSocketPtr)>;
        //connect callback
        using _OnConnectHandler = std::function<void(NetErrorCode)>;
        //send or recv callback  @int : translate bytes.
        using _OnSendHandler = std::function<void(NetErrorCode, int)>;
        //return the offset that the first call doRecv with param daemon mod.
        using _OnRecvHandler = std::function<unsigned int(NetErrorCode, int)>;

        //udp callback
        //! @const char *: remote ip
        //! @unsigned short: remote port
        //! @int : translate bytes
        using _OnRecvFromHandler = std::function<void(NetErrorCode, const char*, unsigned short, int)>;


        enum LINK_STATUS
        {
            LS_UNINITIALIZE, //socket default status
            LS_WAITLINK, // socket status after init and will to connect.
            LS_ATTACHED, // socket attached will to initialize.
            LS_ESTABLISHED, //socket status is established
            LS_CLOSED, // socket is closed. don't use it again.
        };

        class ZSummerEnvironment
        {
        public:
            ZSummerEnvironment();
            ~ZSummerEnvironment();
            inline void addCreatedSocketCount(){ _totalCreatedCTcpSocketObjs++; }
            inline void addClosedSocketCount(){ _totalClosedCTcpSocketObjs++; }
            inline unsigned int getCreatedSocketCount(){ return _totalCreatedCTcpSocketObjs; }
            inline unsigned int getClosedSocketCount(){ return _totalClosedCTcpSocketObjs; }
            inline LoggerId getNetCoreLogger(){ return _netLoggerID; }
        private:
            std::atomic_uint _totalCreatedCTcpSocketObjs;
            std::atomic_uint _totalClosedCTcpSocketObjs;
            LoggerId _netLoggerID = 0;
        };

        extern ZSummerEnvironment g_appEnvironment;

        std::string getHostByName(const std::string & name);
        std::string getPureHostName(const std::string & host);
#ifndef WIN32
        inline bool setNonBlock(int fd) {return fcntl((fd), F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK) == 0;}
        inline bool setNoDelay(int fd){int bTrue = true?1:0; return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&bTrue, sizeof(bTrue)) == 0;}
        inline bool setReuse(int fd){int bReuse = 1;return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &bReuse, sizeof(bReuse)) == 0;}
        inline bool setIPV6Only(int fd, bool only){int ipv6only = only ? 1 : 0;return setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &ipv6only, sizeof(ipv6only)) == 0;}
#else
        inline bool setNonBlock(SOCKET s) {unsigned long val = 1;return ioctlsocket(s, FIONBIO, &val) == NO_ERROR;}
        inline bool setNoDelay(SOCKET s){BOOL bTrue = TRUE;return setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)&bTrue, sizeof(bTrue)) == 0;}
        inline bool setReuse(SOCKET s){BOOL bReUseAddr = TRUE;return setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&bReUseAddr, sizeof(BOOL)) == 0;}
        inline bool setIPV6Only(SOCKET s, bool only){DWORD ipv6only = only ? 1: 0;return setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, (char*)&ipv6only, sizeof(ipv6only)) == 0;}
#endif
    }
}



#define LCT( log ) LOG_TRACE( zsummer::network::g_appEnvironment.getNetCoreLogger(), log )
#define LCD( log ) LOG_DEBUG( zsummer::network::g_appEnvironment.getNetCoreLogger(), log )
#define LCI( log ) LOG_INFO( zsummer::network::g_appEnvironment.getNetCoreLogger(),  log )
#define LCW( log ) LOG_WARN( zsummer::network::g_appEnvironment.getNetCoreLogger(),  log )
#define LCE( log ) LOG_ERROR( zsummer::network::g_appEnvironment.getNetCoreLogger(), log )
#define LCA( log ) LOG_ALARM( zsummer::network::g_appEnvironment.getNetCoreLogger(), log )
#define LCF( log ) LOG_FATAL( zsummer::network::g_appEnvironment.getNetCoreLogger(), log )




















#endif











