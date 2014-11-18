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
#ifndef _ZSUMMERX_TCPACCEPT_IMPL_H_
#define _ZSUMMERX_TCPACCEPT_IMPL_H_

#include "common_impl.h"
#include "iocp_impl.h"
#include "tcpsocket_impl.h"
namespace zsummer
{
	namespace network
	{
		class CTcpAccept : public std::enable_shared_from_this<CTcpAccept>
		{
		public:
			CTcpAccept();
			~CTcpAccept();
			bool Initialize(ZSummerPtr& summer);
			bool OpenAccept(const char * ip, unsigned short port);
			bool DoAccept(const CTcpSocketPtr& s, _OnAcceptHandler &&handler);
			bool OnIOCPMessage(BOOL bSuccess);

			//config
			ZSummerPtr m_summer;


			std::string		m_ip;
			unsigned short			m_port = 0;
			//listen
			SOCKET			m_server = INVALID_SOCKET;
			SOCKADDR_IN		m_addr;

			//client
			SOCKET m_socket = INVALID_SOCKET;
			char m_recvBuf[200];
			DWORD m_recvLen = 0;
			tagReqHandle m_handle;
			_OnAcceptHandler m_onAcceptHandler;
			CTcpSocketPtr m_client;

			//status
			int m_nLinkStatus;
		};
		typedef std::shared_ptr<CTcpAccept> CTcpAcceptPtr;

	}

}





















#endif











