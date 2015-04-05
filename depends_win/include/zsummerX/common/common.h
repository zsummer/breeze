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
* Copyright (C) 2013-2014 YaweiZhang <yawei_zhang@foxmail.com>.
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

#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
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

#endif

#include <assert.h>
#include <string>
#include <iostream>
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
			NEC_REMOTE_HANGUP,
		};

		
		//! post callback
		typedef std::function<void()> _OnPostHandler;
		//timer callback
		typedef std::function<void()> _OnTimerHandler;

		//accept callback
		class TcpSocket;
		typedef std::function<void(NetErrorCode, std::shared_ptr<TcpSocket>)> _OnAcceptHandler;
		//connect callback
		typedef std::function<void(NetErrorCode)> _OnConnectHandler;

		//send or recv callback
		//! type int : translate bytes already.
		typedef std::function<void(NetErrorCode, int)> _OnSendHandler;
		typedef _OnSendHandler _OnRecvHandler;

		//udp callback
		//! const char *: remote ip
		//! unsigned short: remote port
		//! int : translate bytes
		typedef std::function<void (NetErrorCode, const char*, unsigned short, int)> _OnRecvFromHandler;


		enum LINK_STATUS
		{
			LS_UNINITIALIZE, //socket default status
			LS_WAITLINK, // socket status after init and will to connect.
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

			inline void addCreatedSessionCount(){ _totalCreatedCTcpSessionObjs++; }
			inline void addClosedSessionCount(){ _totalClosedCTcpSessionObjs++; }
			inline unsigned int getCreatedSessionCount(){ return _totalCreatedCTcpSessionObjs; }
			inline unsigned int getClosedSessionCount(){ return _totalClosedCTcpSessionObjs; }

			inline LoggerId getNetCoreLogger(){ return _netLoggerID; }
		private:
			std::atomic_uint _totalCreatedCTcpSocketObjs;
			std::atomic_uint _totalClosedCTcpSocketObjs;
			std::atomic_uint _totalCreatedCTcpSessionObjs;
			std::atomic_uint _totalClosedCTcpSessionObjs;
			LoggerId _netLoggerID = 0;
		};

		extern ZSummerEnvironment g_appEnvironment;
#ifndef WIN32
		inline bool setNonBlock(int fd) 
		{
			return fcntl((fd), F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK) == 0;
		}
		inline bool setNoDelay(int fd)
		{
			int bTrue = true?1:0;
			return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&bTrue, sizeof(bTrue)) == 0;
		}
#else
		inline bool setNonBlock(SOCKET s) 
		{		
			unsigned long val = 1;
			int nb = ioctlsocket(s, FIONBIO, &val);
			if (nb != NO_ERROR)
			{
				return false;
			}
			return true;
		}
		inline bool setNoDelay(SOCKET s)
		{
			BOOL bTrue = TRUE;
			if (setsockopt(s,IPPROTO_TCP, TCP_NODELAY, (char*)&bTrue, sizeof(bTrue)) != 0)
			{
				return false;
			}
			return true;
		}
#endif
	}
}


#define LCT( log ) LOG_TRACE( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCD( log ) LOG_DEBUG( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ <<": "<< log )
#define LCI( log ) LOG_INFO( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ <<": "<<  log )
#define LCW( log ) LOG_WARN( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCE( log ) LOG_ERROR( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCA( log ) LOG_ALARM( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCF( log ) LOG_FATAL( zsummer::network::g_appEnvironment.getNetCoreLogger(), __FUNCTION__ << ": "<< log )





















#endif











