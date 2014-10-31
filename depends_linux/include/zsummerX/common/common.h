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
		//! ErrorCode
		enum ErrorCode
		{
			EC_SUCCESS = 0,
			EC_ERROR,
			EC_REMOTE_CLOSED,
			EC_REMOTE_HANGUP,
		};

		
		//! post callback
		typedef std::function<void()> _OnPostHandler;
		//timer callback
		typedef std::function<void()> _OnTimerHandler;

		//accept callback
		class CTcpSocket;
		typedef std::function<void(ErrorCode, std::shared_ptr<CTcpSocket>)> _OnAcceptHandler;
		//connect callback
		typedef std::function<void(ErrorCode)> _OnConnectHandler;

		//send or recv callback
		//! type int : translate bytes already.
		typedef std::function<void(ErrorCode, int)> _OnSendHandler;
		typedef _OnSendHandler _OnRecvHandler;

		//udp callback
		//! const char *: remote ip
		//! unsigned short: remote port
		//! int : translate bytes
		typedef std::function<void (ErrorCode, const char*, unsigned short, int)> _OnRecvFromHandler;


		enum LINK_STATUS
		{
			LS_UNINITIALIZE, //socket default status
			LS_WAITLINK, // socket status after init and will to connect.
			LS_ESTABLISHED, //socket status is established
			LS_CLOSED, // socket is closed. don't use it again.
		};

		class CEnvironment
		{
		public:
			CEnvironment();
			~CEnvironment();
			inline void AddCreatedSocketCount(){ m_totalCreatedCTcpSocketObjs++; }
			inline void AddClosedSocketCount(){ m_totalClosedCTcpSocketObjs++; }
			inline unsigned int GetCreatedSocketCount(){ return m_totalCreatedCTcpSocketObjs; }
			inline unsigned int GetClosedSocketCount(){ return m_totalClosedCTcpSocketObjs; }
			inline LoggerId GetNetCoreLogger(){ return m_netLoggerID; }
		private:
			std::atomic_uint m_totalCreatedCTcpSocketObjs;
			std::atomic_uint m_totalClosedCTcpSocketObjs;
			LoggerId m_netLoggerID = 0;
		};

		extern CEnvironment g_appEnvironment;
#ifndef WIN32
		inline bool SetNonBlock(int fd) 
		{
			return fcntl((fd), F_SETFL, fcntl(fd, F_GETFL)|O_NONBLOCK) == 0;
		}
		inline bool SetNoDelay(int fd)
		{
			int bTrue = true?1:0;
			return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&bTrue, sizeof(bTrue)) == 0;
		}
#else
		inline bool SetNonBlock(SOCKET s) 
		{		
			unsigned long val = 1;
			int nb = ioctlsocket(s, FIONBIO, &val);
			if (nb != NO_ERROR)
			{
				return false;
			}
			return true;
		}
		inline bool SetNoDelay(SOCKET s)
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


#define LCT( log ) LOG_TRACE( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCD( log ) LOG_DEBUG( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ <<": "<< log )
#define LCI( log ) LOG_INFO( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ <<": "<<  log )
#define LCW( log ) LOG_WARN( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCE( log ) LOG_ERROR( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCA( log ) LOG_ALARM( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ << ": "<< log )
#define LCF( log ) LOG_FATAL( zsummer::network::g_appEnvironment.GetNetCoreLogger(), __FUNCTION__ << ": "<< log )





















#endif











