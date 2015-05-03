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
#ifndef WIN32
#include <sys/epoll.h>
#endif
namespace zsummer
{
	namespace network
	{

#ifdef WIN32

		enum EPOLL_CTL_ENUM
		{
			EPOLL_CTL_ADD,
			EPOLL_CTL_MOD,
			EPOLL_CTL_DEL,
		};

		typedef union epoll_data {
			void    *ptr;
			int      fd;
			uint32_t u32;
			uint64_t u64;
		} epoll_data_t;

		struct epoll_event {
			uint32_t     events;//    Epoll events 
			epoll_data_t data;//      User data variable 
		};
#endif
		class TcpSocket;
		class TcpAccept;
		class UdpSocket;
		const int InvalideFD = -1;
		struct tagRegister
		{
			enum REG_TYPE
			{
				REG_INVALID,
				REG_ZSUMMER,
				REG_TCP_SOCKET,
				REG_TCP_ACCEPT,
				REG_UDP_SOCKET
			};

			epoll_event   _event; //event, auto set
			unsigned char _type = REG_INVALID; //register type
			unsigned char _linkstat = LS_UNINITIALIZE;
			int			  _fd = InvalideFD;   //file descriptor
			std::shared_ptr<TcpSocket> _tcpSocketSendPtr;
			std::shared_ptr<TcpSocket> _tcpSocketRecvPtr;
			std::shared_ptr<TcpSocket> _tcpSocketConnectPtr;
			std::shared_ptr<TcpAccept> _tcpacceptPtr;
			std::shared_ptr<UdpSocket> _udpsocketPtr;
		};

		template <class T>
		T& operator <<(T &t, const tagRegister & reg)
		{
			t << "registerEvent Info: epoll_event.events[" << reg._event.events
				<< "] _type[" << (int)reg._type << "] _linkstat[" << (int)reg._linkstat
				<< "] _fd[" << reg._fd << "]  Notes: REG_INVALID[" << tagRegister::REG_INVALID << "] REG_ZSUMMER[" << tagRegister::REG_ZSUMMER
				<< "] REG_TCP_SOCKET[" << tagRegister::REG_TCP_SOCKET << "] REG_TCP_ACCEPT[" << tagRegister::REG_TCP_ACCEPT
				<< "] REG_UDP_SOCKET[" << tagRegister::REG_UDP_SOCKET
				<< "] EPOLL_CTL_ADD[" << EPOLL_CTL_ADD << "] EPOLL_CTL_MOD[" << EPOLL_CTL_MOD << "] EPOLL_CTL_DEL[" << EPOLL_CTL_DEL
				<< "];   EPOLLIN[" << EPOLLIN << "] EPOLLOUT[" << EPOLLOUT << "] EPOLLERR[" << EPOLLERR << "] EPOLLHUP[" << EPOLLHUP;
			return t;
		}
	}
}





















#endif











