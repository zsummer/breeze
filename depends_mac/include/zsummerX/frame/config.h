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

#ifndef ZSUMMER_CONFIG_H_
#define ZSUMMER_CONFIG_H_

#include <iostream>
#include <queue>
#include <iomanip>
#include <string.h>
#include <signal.h>
#include <unordered_map>
#include <log4z/log4z.h>
#include <proto4z/proto4z.h>

#ifdef WIN32
#include "../iocp/iocp_impl.h"
#include "../iocp/tcpsocket_impl.h"
#include "../iocp/udpsocket_impl.h"
#include "../iocp/tcpaccept_impl.h"
#elif defined(__APPLE__) || defined(__SELECT__)
#include "../select/select_impl.h"
#include "../select/udpsocket_impl.h"
#include "../select/tcpsocket_impl.h"
#include "../select/tcpaccept_impl.h"
#else
#include "../epoll/epoll_impl.h"
#include "../epoll/tcpsocket_impl.h"
#include "../epoll/udpsocket_impl.h"
#include "../epoll/tcpaccept_impl.h"
#endif


namespace zsummer
{
	namespace network
	{

		typedef unsigned int SessionID;
		const SessionID InvalidSeesionID = -1;
		typedef unsigned int AccepterID;
		const AccepterID InvalidAccepterID = -1;
		typedef unsigned short ProtoID;
		const ProtoID InvalidProtoID = -1;


		// const unsigned int __MIDDLE_SEGMENT_VALUE = ((unsigned int)-1) / (unsigned int)2;
		const unsigned int __MIDDLE_SEGMENT_VALUE = 300 * 1000 * 1000;
		inline bool isSessionID(unsigned int unknowID){ return unknowID < __MIDDLE_SEGMENT_VALUE ? true : false; }
		inline bool isConnectID(unsigned int unknowID){ return unknowID != InvalidSeesionID && !isSessionID(unknowID); }
		inline unsigned int nextSessionID(unsigned int curSessionID){ return (curSessionID + 1) % __MIDDLE_SEGMENT_VALUE; }
		inline unsigned int nextConnectID(unsigned int curSessionID){ return (curSessionID + 1 < __MIDDLE_SEGMENT_VALUE || curSessionID + 1 == InvalidSeesionID) ? __MIDDLE_SEGMENT_VALUE : curSessionID + 1; }



		enum ProtoType
		{
			PT_TCP,
			PT_HTTP,
		};


		struct ListenConfig
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


		struct ListenInfo
		{
			//limit max session.
			AccepterID _aID = InvalidAccepterID;
			unsigned long long _totalAcceptCount = 0;
			unsigned long long _currentLinked = 0;
		};


		struct ConnectConfig
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



		struct ConnectInfo
		{
			//implementation reconnect 
			SessionID _cID = InvalidSeesionID;
			unsigned long long _totalConnectCount = 0;
			unsigned long long _curReconnectCount = 0;
		};



		//----------------------------------------

		//receive buffer length  and send buffer length 
		const unsigned int MAX_BUFF_SIZE = 100 * 1024;
		const unsigned int MAX_SEND_PACK_SIZE = 10 * 1024;

		//!register message with original net pack, if return false other register will not receive this message.
		typedef std::function < bool(SessionID, const char * /*blockBegin*/, typename zsummer::proto4z::Integer /*blockSize*/) > OnPreMessageFunction;

		//!register message 
		typedef std::function < void(SessionID, ProtoID, zsummer::proto4z::ReadStream &) > OnMessageFunction;

		//!register event 
		typedef std::function < void(SessionID, const std::string & /*remoteIP*/, unsigned short /*remotePort*/) > OnSessionEstablished;
		typedef std::function < void(SessionID, const std::string & /*remoteIP*/, unsigned short /*remotePort*/) > OnSessionDisconnect;

		//register http proto message 
		typedef std::function < void(SessionID, const zsummer::proto4z::PairString &, const zsummer::proto4z::HTTPHeadMap& /*head*/, const std::string & /*body*/) > OnHTTPMessageFunction;

		//register pulse timer .  you can register this to implement heartbeat . 
		typedef std::function < void(SessionID, unsigned int/*pulse interval*/) > OnSessionPulseTimer;






		inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ListenConfig & config)
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


		inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ListenInfo & info)
		{
			os << "[_aID=" << info._aID << ", _totalAcceptCount=" << info._totalAcceptCount << ", _currentLinked=" << info._currentLinked << "]";
			return os;
		}



		inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ConnectConfig & config)
		{
			os << "[_remoteIP=" << config._remoteIP << ", _remotePort=" << config._remotePort << ", _protoType=" << (config._protoType == PT_TCP ? "PT_TCP" : "PT_HTTP")
				<< ", _rc4TcpEncryption=" << config._rc4TcpEncryption << ", _pulseInterval=" << config._pulseInterval << ", _reconnectMaxCount=" << config._reconnectMaxCount
				<< ", _reconnectInterval=" << config._reconnectInterval << ", _reconnectCleanAllData=" << config._reconnectCleanAllData << "]";
			return os;
		}


		inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const ConnectInfo & info)
		{
			os << "[_cID=" << info._cID << ", _totalConnectCount=" << info._totalConnectCount << ", _curReconnectCount=" << info._curReconnectCount << "]";
			return os;
		}


	}
}





#endif

