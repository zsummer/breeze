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
* Copyright (C) 2013 YaweiZhang <yawei_zhang@foxmail.com>.
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
#ifndef WIN32
		typedef int SOCKET;
		inline void closesocket(SOCKET s)
		{
			::close(s);
		}
#define IS_PENDING (errno == EINPROGRESS)
#define IS_EINTR (errno == EINTR)
#define IS_WOULDBLOCK (errno == EAGAIN || errno == EWOULDBLOCK)
#define OSTREAM_GET_LASTERROR  "errno=" << errno << ", errMSG=" << strerror(errno)
#else
		const int SHUT_RD = SD_RECEIVE;
		const int SHUT_WR = SD_SEND;
		const int SHUT_RDWR = SD_BOTH;
		typedef int socklen_t;
#define IS_PENDING (WSAGetLastError() == ERROR_IO_PENDING)
#define IS_EINTR (WSAGetLastError() == WSAEINTR)
#define IS_WOULDBLOCK (WSAGetLastError() == WSAEWOULDBLOCK )
#define OSTREAM_GET_LASTERROR  "WSAGetLastError()=" << WSAGetLastError()

#endif
		class TcpSocketImpl;
		class TcpAcceptImpl;
		class UdpSocketImpl;
		const int InvalideFD = -1;
		struct tagRegister
		{
			enum REG_TYPE
			{
				REG_INVALID,
				REG_TCP_SOCKET,
				REG_TCP_ACCEPT,
				REG_UDP_SOCKET
			};
			unsigned short _type = REG_INVALID;
			unsigned char _linkstat = LS_UNINITIALIZE;
			bool _rd = false;
			bool _wt = false;
			SOCKET _fd = InvalideFD;
			std::shared_ptr<TcpSocketImpl> _tcpSocketSendPtr;
			std::shared_ptr<TcpSocketImpl> _tcpSocketRecvPtr;
			std::shared_ptr<TcpSocketImpl> _tcpSocketConnectPtr;
			std::shared_ptr<TcpAcceptImpl> _tcpacceptPtr;
			std::shared_ptr<UdpSocketImpl> _udpsocketPtr;
		};
		typedef std::vector<tagRegister> PoolReggister;

		template <class T>
		T& operator <<(T &t, const tagRegister & reg)
		{
			t << "registerEvent Info: register._fd[" << reg._fd << "] _rd[" << reg._rd
				<< "] _wt[" << reg._wt << "] _linkstat[" << (int)reg._linkstat << "], _type=[" << reg._type << "]";
				
			return t;
		}
	}
}





















#endif











