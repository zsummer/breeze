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


//! common header 

#ifndef ZSUMMER_HEADER_H_
#define ZSUMMER_HEADER_H_

#include <zsummerX/zsummerX.h>


#include <iostream>
#include <queue>
#include <iomanip>
#include <string.h>
#include <signal.h>
#include <unordered_map>
#include <log4z/log4z.h>
#include <proto4z/proto4z.h>
using namespace std;




typedef unsigned int SessionID;
const SessionID InvalidSeesionID = -1;
typedef unsigned int AccepterID;
const AccepterID InvalidAccepterID = -1;
typedef unsigned short ProtoID;
const ProtoID InvalidProtoID = -1;


// const unsigned int __MIDDLE_SEGMENT_VALUE = ((unsigned int)-1) / (unsigned int)2;
const unsigned int __MIDDLE_SEGMENT_VALUE = 300*1000*1000;
inline bool isSessionID(unsigned int unknowID){ return unknowID < __MIDDLE_SEGMENT_VALUE ? true : false; }
inline bool isConnectID(unsigned int unknowID){ return unknowID != InvalidSeesionID && !isSessionID(unknowID); }
inline unsigned int nextSessionID(unsigned int curSessionID){ return (curSessionID + 1) % __MIDDLE_SEGMENT_VALUE; }
inline unsigned int nextConnectID(unsigned int curSessionID){ return (curSessionID + 1 < __MIDDLE_SEGMENT_VALUE || curSessionID + 1 == InvalidSeesionID) ? __MIDDLE_SEGMENT_VALUE : curSessionID + 1; }



enum ProtoType
{
	PT_TCP,
	PT_HTTP,
};


struct tagAcceptorConfigTraits
{
	std::string listenIP = "0.0.0.0";
	unsigned short listenPort = 81;
	ProtoType protoType = PT_TCP;
	std::string rc4TcpEncryption = ""; //empty is not encryption
	bool openFlashPolicy = false;
	unsigned int pulseInterval = 30000;
	unsigned int maxSessions = 5000;
	std::vector<std::string> whitelistIP;
};

struct tagAcceptorInfo
{
	//limit max session.
	AccepterID aID = InvalidAccepterID;
	unsigned long long totalAcceptCount = 0; 
	unsigned long long currentLinked = 0; 
};



struct tagConnctorConfigTraits
{
	std::string remoteIP = "127.0.0.1";
	unsigned short remotePort = 81;
	ProtoType protoType = PT_TCP;
	std::string rc4TcpEncryption = ""; //empty is not encryption
	unsigned int pulseInterval = 30000;
	unsigned int reconnectMaxCount = 0; // try reconnect max count
	unsigned int reconnectInterval =5000; //million seconds;
	bool         reconnectCleanAllData = true ;//clean all data when reconnect;
};

struct tagConnctorInfo
{
	//implementation reconnect 
	SessionID cID = InvalidSeesionID;
	unsigned long long totalConnectCount = 0; 
	unsigned long long curReconnectCount = 0; 
};





//----------------------------------------
class TcpSession;
typedef std::shared_ptr<zsummer::network::TcpSocket> TcpSocketPtr;
typedef std::shared_ptr<zsummer::network::TcpAccept> TcpAcceptPtr;
typedef std::shared_ptr<zsummer::network::ZSummer> ZSummerPtr;
typedef std::shared_ptr<TcpSession> CTcpSessionPtr;



//receive buffer length  and send buffer length 
const unsigned int SEND_RECV_CHUNK_SIZE = 64 * 1024 -1;
//proto traits 
struct FrameStreamTraits
{
	typedef unsigned short Integer;
	typedef unsigned short ProtoInteger;
	const static Integer MaxPackLen = (Integer)48 * 1024;
	const static bool	 PackLenIsContainHead = true; 
	const static zsummer::proto4z::ZSummer_EndianType EndianType = zsummer::proto4z::LittleEndian;
};


typedef zsummer::proto4z::ReadStream ReadStreamPack;
typedef zsummer::proto4z::WriteStream WriteStreamPack;


//!register message with original net pack, if return false other register will not receive this message.
typedef std::function < bool(SessionID, const char * /*blockBegin*/, typename FrameStreamTraits::Integer /*blockSize*/) > OnOrgMessageFunction;

//!register message 
typedef std::function < void(SessionID, ProtoID, ReadStreamPack &) > OnMessageFunction;

//!register event 
typedef std::function < void(SessionID) > OnSessionEstablished;
typedef std::function < void(SessionID) > OnSessionDisconnect;

//register http proto message 
typedef std::function < void (SessionID, const zsummer::proto4z::PairString &, const zsummer::proto4z::HTTPHeadMap& /*head*/, const std::string & /*body*/) > OnHTTPMessageFunction;

//register pulse timer .  you can register this to implement heartbeat . 
typedef std::function < void(SessionID, unsigned int/*pulse interval*/) > OnSessionPulseTimer;

//! print log
template<class OS>
OS & operator <<(OS & os, const tagAcceptorConfigTraits & traits)
{
	os << "[listenIP=" << traits.listenIP << "; listenPort=" << traits.listenPort
		<< "; maxSessions=" << traits.maxSessions << "; whitelistIP=";
	for (auto x : traits.whitelistIP)
	{
		os << x << ",";
	}
	os << "]";
	return os;
}

//! print log
template<class OS>
OS & operator <<(OS & os, const tagConnctorConfigTraits & traits)
{
	os << "[remoteIP=" << traits.remoteIP << "; remotePort=" << traits.remotePort
		<< "; reconnectMaxCount=" << traits.reconnectMaxCount << "; reconnectInterval=" << traits.reconnectInterval;
	return os;
}

#endif

