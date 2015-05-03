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




#ifndef ZSUMMER_TCP_SESSION_H_
#define ZSUMMER_TCP_SESSION_H_
#include "config.h"
#include <rc4/rc4_encryption.h>

namespace zsummer
{
	namespace network
	{


		struct MessageSendPack
		{
			char buff[MAX_SEND_PACK_SIZE];
			unsigned int bufflen = 0;
		};

		struct MessageBuffChunk
		{
			char buff[MAX_BUFF_SIZE];
			unsigned int bufflen = 0;
		};

		struct rc4_state;

		class TcpSession : public std::enable_shared_from_this<TcpSession>
		{
		public:
			void doSend(const char *buf, unsigned int len);
			void close();
			inline SessionID getAcceptID(){ return _acceptID; }
            inline SessionID getSessionID(){ return _sessionID; }
			inline const std::string & getRemoteIP(){ return _remoteIP; }
			inline unsigned short getRemotePort(){ return _remotePort; }
            
            inline void setUserParam(unsigned long long param) { _param = param;}
            inline void setUserLParam(unsigned long long param) { _lparam = param;}
            inline void setUserRParam(unsigned long long param) { _rparam = param;}
            inline unsigned long long getUserParam(){ return _param;}
            inline unsigned long long getUserLParam(){ return _lparam;}
            inline unsigned long long getUserRParam(){ return _rparam;}
            inline void setUserParamString(const std::string param){ _paramstring = param;}
            inline const std::string getUserParamString(){ return _paramstring;}
        public:
            TcpSession();
            ~TcpSession();
            bool bindTcpSocketPrt(const TcpSocketPtr &sockptr, AccepterID aID, SessionID sID, const ListenConfig &traits);
            void bindTcpConnectorPtr(const TcpSocketPtr &sockptr, const std::pair<ConnectConfig, ConnectInfo> & config);
            
		private:
			void cleanSession(bool isCleanAllData, const std::string &rc4TcpEncryption);

			bool doRecv();

			void onConnected(zsummer::network::NetErrorCode ec, const std::pair<ConnectConfig, ConnectInfo> & config);

			void onRecv(zsummer::network::NetErrorCode ec, int nRecvedLen);

			void onSend(zsummer::network::NetErrorCode ec, int nSentLen);

			void onPulseTimer();

			void onClose();


		private:
			TcpSocketPtr  _sockptr;
			std::string _remoteIP;
			unsigned short _remotePort = 0;
			//
			SessionID _sessionID = InvalidSeesionID;
			AccepterID _acceptID = InvalidAccepterID;
			ProtoType _protoType = PT_TCP;
			unsigned int _pulseInterval = 0;
			zsummer::network::TimerID _pulseTimerID = zsummer::network::InvalidTimerID;

			enum SessionStatus
			{
				SS_UNINITILIZE,
				SS_ESTABLISHED,
				SS_CLOSED,
			};

			//! 
			MessageBuffChunk _recving;
			MessageBuffChunk _sending;
			unsigned int _sendingCurIndex = 0;

			//! send data queue
			std::queue<MessageSendPack *> _sendque;
			std::queue<MessageSendPack *> _freeCache;

			//! rc encrypt
			std::string _rc4Encrypt;
			RC4Encryption _rc4StateRead;
			RC4Encryption _rc4StateWrite;

			//! flash policy 
			bool _bFirstRecvData = true;
			bool _bOpenFlashPolicy = false;

			//! http status data
			bool _httpHadHeader = false;
			bool _httpIsChunked = false;
			zsummer::proto4z::PairString  _httpCommonLine;
			zsummer::proto4z::HTTPHeadMap _httpHeader;
            
            //! user param
            unsigned long long _param = 0;
            unsigned long long _lparam = 0;
            unsigned long long _rparam = 0;
            std::string _paramstring;
		};


	}
}


#endif


