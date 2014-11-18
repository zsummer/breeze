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

#ifndef _ZSUMMER_TCPSOCKET_IMPL_H_
#define _ZSUMMER_TCPSOCKET_IMPL_H_



#include "common_impl.h"
#include "epoll_impl.h"

namespace zsummer
{
	namespace network
	{

		class CTcpSocket : public std::enable_shared_from_this<CTcpSocket>
		{
		public:
			CTcpSocket();
			~CTcpSocket();
			bool Initialize(const ZSummerPtr& summer);
			inline bool GetPeerInfo(std::string& remoteIP, unsigned short &remotePort)
			{
				remoteIP = m_remoteIP;
				remotePort = m_remotePort;
				return true;
			}
			bool DoConnect(const std::string &remoteIP, unsigned short remotePort, _OnConnectHandler && handler);
			bool DoSend(char * buf, unsigned int len, _OnSendHandler && handler);
			bool DoRecv(char * buf, unsigned int len, _OnRecvHandler && handler);
			bool DoClose();

			
		public:
			void OnPostClose();
			void OnEPOLLMessage(int flag, bool err);
			bool AttachSocket(int s, const std::string& remoteIP, unsigned short remotePort);
		private:
			std::string SocketSection();
		private:
			ZSummerPtr m_summer;
			std::string m_remoteIP;
			unsigned short m_remotePort = 0;
			tagRegister m_register;
			
			_OnConnectHandler m_onConnectHandler;

			_OnRecvHandler m_onRecvHandler;
			unsigned int m_iRecvLen = 0;
			char	*	 m_pRecvBuf = NULL;

			_OnSendHandler m_onSendHandler;
			unsigned int m_iSendLen = 0;
			char *		 m_pSendBuf = NULL;
		};
		typedef std::shared_ptr<CTcpSocket> CTcpSocketPtr;
	}

}






















#endif











