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
	std::string _listenIP = "0.0.0.0";
	unsigned short _listenPort = 81;
	ProtoType _protoType = PT_TCP;
	std::string _rc4TcpEncryption = ""; //empty is not encryption
	bool _openFlashPolicy = false;
	unsigned int _pulseInterval = 30000;
	unsigned int _maxSessions = 5000;
	std::vector<std::string> _whitelistIP;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const tagAcceptorConfigTraits & config)
{
	std::string whitelist;
	for (auto str : config._whitelistIP)
	{
		whitelist += str + ",";
	}
	
	os << "[_listenIP=" << config._listenIP << ", _listenPort=" << config._listenPort << ", _protoType=" << (config._protoType == PT_TCP ? "PT_TCP" : "PT_HTTP") 
		<< ", _rc4TcpEncryption=" << config._rc4TcpEncryption << ", _openFlashPolicy=" << config._openFlashPolicy << ", _pulseInterval=" << config._pulseInterval 
		<< ", _maxSessions=" << config._maxSessions << ", _whitelistIP=" << whitelist << "]";
	return os;
}

struct tagAcceptorInfo
{
	//limit max session.
	AccepterID _aID = InvalidAccepterID;
	unsigned long long _totalAcceptCount = 0; 
	unsigned long long _currentLinked = 0; 
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const tagAcceptorInfo & info)
{
	os << "[_aID=" << info._aID << ", _totalAcceptCount=" << info._totalAcceptCount << ", _currentLinked=" << info._currentLinked << "]";
	return os;
}


struct tagConnctorConfigTraits
{
	std::string _remoteIP = "127.0.0.1";
	unsigned short _remotePort = 81;
	ProtoType _protoType = PT_TCP;
	std::string _rc4TcpEncryption = ""; //empty is not encryption
	unsigned int _pulseInterval = 30000;
	unsigned int _reconnectMaxCount = 0; // try reconnect max count
	unsigned int _reconnectInterval = 5000; //million seconds;
	bool         _reconnectCleanAllData = true;//clean all data when reconnect;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const tagConnctorConfigTraits & config)
{
	os << "[_remoteIP=" << config._remoteIP << ", _remotePort=" << config._remotePort << ", _protoType=" << (config._protoType == PT_TCP ? "PT_TCP" : "PT_HTTP")
		<< ", _rc4TcpEncryption=" << config._rc4TcpEncryption << ", _pulseInterval=" << config._pulseInterval << ", _reconnectMaxCount=" << config._reconnectMaxCount
		<< ", _reconnectInterval=" << config._reconnectInterval << ", _reconnectCleanAllData=" << config._reconnectCleanAllData << "]";
	return os;
}

struct tagConnctorInfo
{
	//implementation reconnect 
	SessionID _cID = InvalidSeesionID;
	unsigned long long _totalConnectCount = 0;
	unsigned long long _curReconnectCount = 0;
};
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const tagConnctorInfo & info)
{
	os << "[_cID=" << info._cID << ", _totalConnectCount=" << info._totalConnectCount << ", _curReconnectCount=" << info._curReconnectCount << "]";
	return os;
}




//----------------------------------------
class TcpSession;
typedef std::shared_ptr<zsummer::network::TcpSocket> TcpSocketPtr;
typedef std::shared_ptr<zsummer::network::TcpAccept> TcpAcceptPtr;
typedef std::shared_ptr<zsummer::network::ZSummer> ZSummerPtr;
typedef std::shared_ptr<TcpSession> CTcpSessionPtr;


//receive buffer length  and send buffer length 
const unsigned int SEND_RECV_CHUNK_SIZE = 1024 * 1024 - 1;


typedef zsummer::proto4z::ReadStream ReadStreamPack;
typedef zsummer::proto4z::WriteStream WriteStreamPack;


//!register message with original net pack, if return false other register will not receive this message.
typedef std::function < bool(SessionID, const char * /*blockBegin*/, typename zsummer::proto4z::Integer /*blockSize*/) > OnOrgMessageFunction;

//!register message 
typedef std::function < void(SessionID, ProtoID, ReadStreamPack &) > OnMessageFunction;

//!register event 
typedef std::function < void(SessionID) > OnSessionEstablished;
typedef std::function < void(SessionID) > OnSessionDisconnect;

//register http proto message 
typedef std::function < void (SessionID, const zsummer::proto4z::PairString &, const zsummer::proto4z::HTTPHeadMap& /*head*/, const std::string & /*body*/) > OnHTTPMessageFunction;

//register pulse timer .  you can register this to implement heartbeat . 
typedef std::function < void(SessionID, unsigned int/*pulse interval*/) > OnSessionPulseTimer;



#endif

