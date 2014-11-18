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




#ifndef ZSUMMER_TCP_SESSION_H_
#define ZSUMMER_TCP_SESSION_H_
#include "FrameHeader.h"
#include <rc4/rc4_encryption.h>

struct MessagePack
{
	char buff[FrameStreamTraits::MaxPackLen];
	unsigned int bufflen = 0;
};

struct MessageChunk
{
	char buff[SEND_RECV_CHUNK_SIZE];
	unsigned int bufflen = 0;
};

struct rc4_state;

class CTcpSession : public std::enable_shared_from_this<CTcpSession>
{
public:
	CTcpSession();
	~CTcpSession();
	bool BindTcpSocketPrt(const CTcpSocketPtr &sockptr, AccepterID aID, SessionID sID, const tagAcceptorConfigTraits &traits);
	void BindTcpConnectorPtr(const CTcpSocketPtr &sockptr, const std::pair<tagConnctorConfigTraits, tagConnctorInfo> & config);
	void DoSend(const char *buf, unsigned int len);
	void Close();
	SessionID GetAcceptID(){ return m_acceptID; }
private:
	void CleanSession(bool isCleanAllData, const std::string &rc4TcpEncryption);

	bool DoRecv();

	void OnConnected(zsummer::network::ErrorCode ec, const std::pair<tagConnctorConfigTraits, tagConnctorInfo> & config);

	void OnRecv(zsummer::network::ErrorCode ec, int nRecvedLen);
	
	void OnSend(zsummer::network::ErrorCode ec, int nSentLen);

	void OnPulseTimer();
	
	void OnClose();

private:
	CTcpSocketPtr  m_sockptr;
	SessionID m_sessionID = InvalidSeesionID; 
	AccepterID m_acceptID = InvalidAccepterID;
	ProtoType m_protoType = PT_TCP;
	unsigned int m_pulseInterval = 0;
	zsummer::network::TimerID m_pulseTimerID = zsummer::network::InvalidTimerID;

	enum SessionStatus
	{
		SS_UNINITILIZE,
		SS_ESTABLISHED,
		SS_CLOSED,
	};
	
	//! 
	MessageChunk m_recving;
	MessageChunk m_sending;
	unsigned int m_sendingCurIndex = 0;

	//! send data queue
	std::queue<MessagePack *> m_sendque;
	std::queue<MessagePack *> m_freeCache;

	//! rc encrypt
	std::string m_rc4Encrypt;
	CRC4Encryption m_rc4StateRead;
	CRC4Encryption m_rc4StateWrite;

	//! flash policy 
	bool m_bFirstRecvData = true;
	bool m_bOpenFlashPolicy = false;

	//! http status data
	bool m_httpHadHeader = false;
	bool m_httpIsChunked = false;
	zsummer::proto4z::PairString  m_httpCommonLine;
	zsummer::proto4z::HTTPHeadMap m_httpHeader;
};

#endif


