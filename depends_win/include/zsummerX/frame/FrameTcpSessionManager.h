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

#include "FrameHeader.h"
class CTcpSession;
typedef  std::shared_ptr<CTcpSession> CTcpSessionPtr;

class CTcpSessionManager
{
private:
	CTcpSessionManager();

public://!get the single and global object pointer   
	static CTcpSessionManager & getRef();
	static CTcpSessionManager * getPtr(){ return &getRef(); };
public:
	bool Start();
	void Stop();
	void Run();

public:
	//handle: std::function<void()>
	//switch initiative, in the multi-thread it's switch call thread simultaneously.
	template<class H>
	void Post(const H &h){ m_summer->Post(h); }

public:
	template <class H>
	zsummer::network::TimerID CreateTimer(unsigned int delayms, const H &h){ return m_summer->CreateTimer(delayms, h); }
	bool CancelTimer(unsigned long long timerID){ return m_summer->CancelTimer(timerID); }

public:
	//! add acceptor under the configure.
	AccepterID AddAcceptor(const tagAcceptorConfigTraits &traits);
	AccepterID GetAccepterID(SessionID sID);

	//! add connector under the configure.
	SessionID AddConnector(const tagConnctorConfigTraits & traits);

public:
	//send original data. can repeat call because it's used send queue in internal implementation.
	void SendOrgSessionData(SessionID sID, const char * orgData, unsigned int orgDataLen);
	//send LCIc data with protocol id 
	void SendSessionData(SessionID sID, ProtoID pID, const char * userData, unsigned int userDataLen);

	//close session socket.
	void KickSession(SessionID sID);



private:
	void SafeStop();
	friend class CTcpSession;
	// socket(from accept) on close 
	void OnSessionClose(AccepterID aID, SessionID sID);
	// socket(from connect) on close 
	void OnConnect(SessionID cID, bool bConnected, CTcpSessionPtr session);
	void OnAcceptNewClient(zsummer::network::ErrorCode ec, CTcpSocketPtr s, CTcpAcceptPtr accepter, AccepterID aID);
private:
	ZSummerPtr m_summer;
	bool  m_bRunning = true;
	unsigned int  m_onlineConnectCounts = 0;//counts online connect when zsummerx will exit

	SessionID m_lastAcceptID = 0; //accept ID sequence. range  [0 - -1)
	SessionID m_lastSessionID = 0;//session ID sequence. range  [0 - __MIDDLE_SEGMENT_VALUE)
	SessionID m_lastConnectID = 0;//connect ID sequence. range  [__MIDDLE_SEGMENT_VALUE - -1)

	std::unordered_map<AccepterID, CTcpAcceptPtr> m_mapAccepterPtr;
	std::unordered_map<SessionID, CTcpSessionPtr> m_mapTcpSessionPtr;

	std::unordered_map<SessionID, std::pair<tagConnctorConfigTraits, tagConnctorInfo> > m_mapConnectorConfig;
	std::unordered_map<AccepterID, std::pair<tagAcceptorConfigTraits, tagAcceptorInfo> > m_mapAccepterConfig;
public:
};

#endif