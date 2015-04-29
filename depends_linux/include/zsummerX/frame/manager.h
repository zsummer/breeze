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
 * Copyright (C) 2010-2014 YaweiZhang <yawei_zhang@foxmail.com>.
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


#ifndef ZSUMMER_TCPSESSION_MANAGER_H_
#define ZSUMMER_TCPSESSION_MANAGER_H_

#include "config.h"
namespace zsummer
{
	namespace network
	{

		class TcpSession;
		typedef  std::shared_ptr<TcpSession> TcpSessionPtr;

		class SessionManager
		{
		private:
			SessionManager();

		public://!get the single and global object pointer   
			static SessionManager & getRef();
			inline static SessionManager * getPtr(){ return &getRef(); };
		public:
			bool start();
			void stopAccept();
			void kickAllClients();
			void kickAllConnect();
			void stop();
			void run();
			void runOnce(bool isImmediately = false);

			//handle: std::function<void()>
			//switch initiative, in the multi-thread it's switch call thread simultaneously.
			template<class H>
			void post(H &&h){ _summer->post(std::move(h)); }

			template <class H>
			zsummer::network::TimerID createTimer(unsigned int delayms, H &&h){ return _summer->createTimer(delayms, std::move(h)); }
			bool cancelTimer(unsigned long long timerID){ return _summer->cancelTimer(timerID); }


			//! add acceptor under the configure.
			AccepterID addAcceptor(const ListenConfig &traits);
			AccepterID getAccepterID(SessionID sID);

			//! add connector under the configure.
			SessionID addConnector(const ConnectConfig & traits);


			//send original data. can repeat call because it's used send queue in internal implementation.
			void sendOrgSessionData(SessionID sID, const char * orgData, unsigned int orgDataLen);
			//send LCIc data with protocol id 
			void sendSessionData(SessionID sID, ProtoID pID, const char * userData, unsigned int userDataLen);

			//close session socket.
			void kickSession(SessionID sID);

		public://statistical information
			std::string getRemoteIP(SessionID sID);
			unsigned short getRemotePort(SessionID sID);
			unsigned long long _totalConnectCount = 0;
			unsigned long long _totalAcceptCount = 0;
			unsigned long long _totalConnectClosedCount = 0;
			unsigned long long _totalAcceptClosedCount = 0;
			unsigned long long _totalSendMessages = 0;
			unsigned long long _totalSendBytes = 0;

			unsigned long long _totalRecvCount = 0;
			unsigned long long _totalRecvBytes = 0;
			unsigned long long _totalRecvMessages = 0;
			unsigned long long _totalRecvHTTPCount = 0;
			time_t _openTime = 0;

		private:
			friend class TcpSession;
			// socket(from accept) on close 
			void onSessionClose(AccepterID aID, SessionID sID, const TcpSessionPtr &session);
			// socket(from connect) on close 
			void onConnect(SessionID cID, bool bConnected, const TcpSessionPtr &session);
			void onAcceptNewClient(zsummer::network::NetErrorCode ec, const TcpSocketPtr & s, const TcpAcceptPtr & accepter, AccepterID aID);
		private:
			EventLoopPtr _summer;
			bool  _running = true;
			bool _openAccept = true;

			SessionID _lastAcceptID = 0; //accept ID sequence. range  [0 - -1)
			SessionID _lastSessionID = 0;//session ID sequence. range  [0 - __MIDDLE_SEGMENT_VALUE)
			SessionID _lastConnectID = 0;//connect ID sequence. range  [__MIDDLE_SEGMENT_VALUE - -1)

			std::unordered_map<AccepterID, TcpAcceptPtr> _mapAccepterPtr;
			std::unordered_map<SessionID, TcpSessionPtr> _mapTcpSessionPtr;

			std::unordered_map<SessionID, std::pair<ConnectConfig, ConnectInfo> > _mapConnectorConfig;
			std::unordered_map<AccepterID, std::pair<ListenConfig, ListenInfo> > _mapAccepterConfig;
		public:
		};



	}
}


#endif