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




#ifndef ZSUMMER_MSG_MANAGER_H_
#define ZSUMMER_MSG_MANAGER_H_
#include "config.h"
#include "session.h"
namespace zsummer
{
	namespace network
	{
		class MessageDispatcher
		{
		private:
			MessageDispatcher(){}
			typedef std::unordered_map<ProtoID, std::vector<OnMessageFunction> > MapProtoDispatch;
		public:
			static MessageDispatcher & getRef();
			inline static MessageDispatcher * getPtr(){ return &getRef(); }
			~MessageDispatcher(){};

			//message
			inline void registerSessionPreMessage(const OnPreMessageFunction & msgfun){ _vctPreSessionDispatch.push_back(msgfun); }
			inline void registerSessionMessage(ProtoID protoID, const OnMessageFunction & msgfun){ _mapSessionDispatch[protoID].push_back(msgfun); }
			inline void registerSessionDefaultMessage(const OnMessageFunction & msgfun){ _vctDefaultSessionDispatch.push_back(msgfun); }

			//event. can use method isSessionID or isConnectID to resolution who is the sessionID
			inline void registerOnSessionEstablished(const OnSessionEstablished & fun){ _vctOnSessionEstablished.push_back(fun); }
			inline void registerOnSessionDisconnect(const OnSessionDisconnect & fun){ _vctOnSessionDisconnect.push_back(fun); }

			//heartbeat
			inline void registerOnSessionPulse(const OnSessionPulseTimer & fun) { _vctOnSessionPulse.push_back(fun); }
			//http
			inline void registerOnSessionHTTPMessage(const OnHTTPMessageFunction & fun) { _vctSessionHTTPMessage.push_back(fun); }

		public:
            bool dispatchPreSessionMessage(TcpSessionPtr  session, const char * blockBegin, zsummer::proto4z::Integer blockSize);
			void dispatchSessionMessage(TcpSessionPtr  session, ProtoID pID, zsummer::proto4z::ReadStream & msg);
			void dispatchOnSessionEstablished(TcpSessionPtr  session);
			void dispatchOnSessionDisconnect(TcpSessionPtr  session);
			void dispatchOnSessionPulse(TcpSessionPtr  session, unsigned int pulseInterval);
            bool dispatchSessionHTTPMessage(TcpSessionPtr session, const zsummer::proto4z::PairString & commonLine, const zsummer::proto4z::HTTPHeadMap &head, const std::string & body);
		private:
			//!message
			MapProtoDispatch _mapSessionDispatch;
			std::vector<OnPreMessageFunction> _vctPreSessionDispatch;
			std::vector<OnMessageFunction> _vctDefaultSessionDispatch;

			//http
			std::vector<OnHTTPMessageFunction> _vctSessionHTTPMessage;

			//event
			std::vector<OnSessionEstablished> _vctOnSessionEstablished;
			std::vector<OnSessionDisconnect> _vctOnSessionDisconnect;

			std::vector<OnSessionPulseTimer> _vctOnSessionPulse;
		};





	}
}

#endif


