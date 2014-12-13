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

#ifndef _ZSUMMER_TCPACCEPT_IMPL_H_
#define _ZSUMMER_TCPACCEPT_IMPL_H_

#include "common_impl.h"
#include "select_impl.h"
#include "tcpsocket_impl.h"
/*
*	TcpAcceptImpl: EPOLL LT EPOLLONESHOT模式 每次MOD accept一次 以尽量保持和IOCP的PROACTOR设计的一致性
*/

namespace zsummer
{
	namespace network
	{
		class TcpAcceptImpl :public std::enable_shared_from_this<TcpAcceptImpl>
		{
		public:
			TcpAcceptImpl();
			~TcpAcceptImpl();
			bool initialize(const ZSummerPtr &summer);
			bool openAccept(const std::string& listenIP, unsigned short listenPort);
			bool doAccept(const TcpSocketPtr &s, _OnAcceptHandler && handle);
			void onSelectMessage();
			bool close();

		private:
			std::string AcceptSection();
		private:
			ZSummerPtr 		_summer;
			std::string		_listenIP;
			short			_listenPort = 0;

			sockaddr_in		_addr;

			tagRegister _register; //! epoll 注册事件
			_OnAcceptHandler _onAcceptHandler;
			TcpSocketPtr  _client;
		};
		typedef std::shared_ptr<TcpAcceptImpl> TcpAcceptPtr;
	}
}






















#endif











