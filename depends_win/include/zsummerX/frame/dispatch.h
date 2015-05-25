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




#ifndef ZSUMMER_MESSAGE_DISPATCHER_H_
#define ZSUMMER_MESSAGE_DISPATCHER_H_
#include "config.h"
#include "session.h"
namespace zsummer
{
	namespace network
	{
		/*
			MessageDispatcher 是一个协议消息派发器, 是一个单例singleton.
			消息派发分两种类型, 均需要使用者先调用对应的registerXXX系列接口进行注册.
			第一类是事件类型的通知, 即连接建立, 连接断开, 连接的定时检测回调.
			第二类为消息类型的处理通知,  消息处理通知分TCP和HTTP,  TCP有三种, 分别是预处理通知,具体协议处理和默认协议处理. HTTP只有一个消息处理回调. 
			 具体使用参见代码,注释和示例.
		*/
		class MessageDispatcher
		{
		private:
			MessageDispatcher(){}
			typedef std::unordered_map<ProtoID, std::vector<OnMessageFunction> > MapProtoDispatch;
		public:
			static MessageDispatcher & getRef();
			inline static MessageDispatcher * getPtr(){ return &getRef(); }
			~MessageDispatcher(){};

			//注册消息预处理handler, 收到网络消息后会把原始的数据包派发给这个handler,  如果handler的返回值为false, 则这个包会忽略掉, 不会被其他消息处理handler处理, 包括同级的其他PreMessage的handler.
			inline void registerSessionPreMessage(const OnPreMessageFunction & msgfun){ _vctPreSessionDispatch.push_back(msgfun); }
			//注册消息处理handler, 这个是针对消息ID进行注册, 回调参数是包含已经处理得到的协议ID以及attach好的ReadStream. 可以直接使用ReadStream流出对应的协议数据.
			inline void registerSessionMessage(ProtoID protoID, const OnMessageFunction & msgfun){ _mapSessionDispatch[protoID].push_back(msgfun); }
			//注册默认的消息处理handler, 如果一个协议找不到对应的协议处理handler, 则会交给默认的处理handler去处理.
			inline void registerSessionDefaultMessage(const OnDefaultMessageFunction & msgfun){ _vctDefaultSessionDispatch.push_back(msgfun); }

			//event. can use method isSessionID or isConnectID to resolution who is the sessionID
			//注册连接建立和断开的通知, 具体是连入的连接断开还是连出的连接断开 请使用isSessionID()和isConnectID()来判断.
			inline void registerOnSessionEstablished(const OnSessionEstablished & fun){ _vctOnSessionEstablished.push_back(fun); }
			inline void registerOnSessionDisconnect(const OnSessionDisconnect & fun){ _vctOnSessionDisconnect.push_back(fun); }

			//heartbeat
			//根据监听器或者连接器的配置中的_pulseInterval参数定时回调,  连接建立后的第一次调用在 建立时间+_pulseInterval 的时候.
			inline void registerOnSessionPulse(const OnSessionPulseTimer & fun) { _vctOnSessionPulse.push_back(fun); }
			//http

			//注册HTTP协议.
			//参数中. PairString是commondLine信息.  例如GET请求 http://127.0.0.1:8081/index.php?id=1,  commondLine.first="GET", second="/index.php?id=1"
			//commondLine分别有GET,POST,  如果是来自回复信息 则为first可能为HTTP/1.1, second是错误码. 200是成功.
			//body数据存储的是原始的HTTP的body数据, 支持chunked, 但需要自己根据情况选择是否调用urlencode函数进行编解码.
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
			std::vector<OnDefaultMessageFunction> _vctDefaultSessionDispatch;

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


