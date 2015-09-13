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
#pragma warning(disable:4503)
#pragma warning(disable:4200)
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
        //! define network type
        using SessionID = unsigned int;
        const SessionID InvalidSessionID = -1;
        using AccepterID = unsigned int;
        const AccepterID InvalidAccepterID = -1;


        //! define session id range.
        const unsigned int __MIDDLE_SEGMENT_VALUE = 300 * 1000 * 1000;
        inline bool isSessionID(unsigned int unknowID){ return unknowID < __MIDDLE_SEGMENT_VALUE ? true : false; }
        inline bool isConnectID(unsigned int unknowID){ return unknowID != InvalidSessionID && !isSessionID(unknowID); }
        inline unsigned int nextSessionID(unsigned int curSessionID){ return (curSessionID + 1) % __MIDDLE_SEGMENT_VALUE; }
        inline unsigned int nextConnectID(unsigned int curSessionID){ return (curSessionID + 1 < __MIDDLE_SEGMENT_VALUE || curSessionID + 1 == InvalidSessionID) ? __MIDDLE_SEGMENT_VALUE : curSessionID + 1; }


        const unsigned int SESSION_BLOCK_SIZE = 10 * 1024;

        enum ProtoType
        {
            PT_TCP,
            PT_HTTP,
        };

        enum BLOCK_CHECK_TYPE
        {
            BCT_SUCCESS = 0, //成功, 返回当前block大小
            BCT_SHORTAGE = 1, //不足, 返回当前block还需要的大小
            BCT_CORRUPTION = 2, //错误, 需要关闭socket
        };

        enum StatType
        {
            STAT_STARTTIME,
            STAT_SESSION_CREATED,
            STAT_SESSION_DESTROYED,
            STAT_SESSION_LINKED,
            STAT_SESSION_CLOSED,
            STAT_FREE_BLOCKS,
            STAT_EXIST_BLOCKS,
            STAT_SEND_COUNT,
            STAT_SEND_PACKS,
            STAT_SEND_BYTES,
            STAT_SEND_QUES,
            STAT_RECV_COUNT,
            STAT_RECV_PACKS,
            STAT_RECV_BYTES,
            
            STAT_SIZE,
        };

        class TcpSession;
        using TcpSessionPtr = std::shared_ptr<TcpSession>;

        struct SessionBlock 
        {
            unsigned int len = 0;
            unsigned int bound = 0;
            char begin[0];
        };
        

        using CreateBlock = std::function<SessionBlock * ()>;

        using FreeBlock = std::function<void(SessionBlock *)>;
        
        using OnBlockCheckResult = std::pair<BLOCK_CHECK_TYPE, unsigned int>;

        //检查当前缓冲块内是否能读出一个完整的block
        using OnBlockCheck = std::function<OnBlockCheckResult(const char * /*begin*/, unsigned int /*len*/, unsigned int /*bound*/, unsigned int /*blockLimit*/)>;

        //!每读出一个block就调用这个方法dispatch出去
        using OnBlockDispatch = std::function<void(TcpSessionPtr   /*session*/, const char * /*begin*/, unsigned int /*len*/)>;

        //!连接建立, 关闭, 定时器
        using OnSessionEvent = std::function<void(TcpSessionPtr   /*session*/)>;

        using PairString = std::pair<std::string, std::string>;
        using MapString = std::map<std::string, std::string>;
        //!HTTP解包,hadHeader 区别chunked的后续小包, commonLine 指的是GET, POST RESPONSE. 
        using OnHTTPBlockCheck = std::function<OnBlockCheckResult(const char * /*begin*/, unsigned int /*len*/, unsigned int /*bound*/,
            bool /*hadHeader*/, bool & /*isChunked*/, PairString& /*commonLine*/, MapString & /*head*/, std::string & /*body*/)>;
        //!HTTP派发
        using OnHTTPBlockDispatch = std::function<
            void(TcpSessionPtr /*session*/, const PairString & /*commonLine*/, const MapString &/*head*/, const std::string & /*body*/)>;
        


        struct SessionOptions 
        {

            ProtoType       _protoType = PT_TCP;
            std::string     _rc4TcpEncryption = ""; //empty is not encryption
            bool            _openFlashPolicy = false; //检测falsh客户端
            bool            _setNoDelay = true; 
            bool            _joinSmallBlock = true; //发送时合并小包一起发送
            unsigned int    _sessionPulseInterval = 30000; //session pulse间隔
            unsigned int    _connectPulseInterval = 5000; //connect pulse间隔
            unsigned int    _reconnects = 0; // 重连次数
            bool            _reconnectClean = true;//重连时清除未发送的队列.

            OnBlockCheck _onBlockCheck;
            OnBlockDispatch _onBlockDispatch;
            OnHTTPBlockCheck _onHTTPBlockCheck;
            OnHTTPBlockDispatch _onHTTPBlockDispatch;
            OnSessionEvent _onSessionClosed;
            OnSessionEvent _onSessionLinked;
            OnSessionEvent _onSessionPulse;

            CreateBlock _createBlock ;
            FreeBlock _freeBlock;

        };

        struct AccepterOptions
        {
            AccepterID _aID = InvalidAccepterID;
            TcpAcceptPtr _accepter;
            std::string        _listenIP;
            unsigned short    _listenPort = 0;
            unsigned int    _maxSessions = 5000;
            std::vector<std::string> _whitelistIP;
            unsigned long long _totalAcceptCount = 0;
            unsigned long long _currentLinked = 0;
            SessionOptions _sessionOptions;
        };


        class Any
        {
        public:
            Any()
            {

            }
            Any(unsigned long long n)
            {
                _number = n;
            }
            Any(const std::string & str)
            {
                _string = str;
            }
            Any(void * p)
            {
                _pointer = p;
            }
        public:
            inline unsigned long long getNumber() const { return _number; }
            inline std::string getString() const { return _string; }
            inline void * getPtr() const { return _pointer; }
        private:
            unsigned long long _number = 0;
            std::string _string;
            void * _pointer = nullptr;
        };


        template<class Number>
        Number numberCast(const Any & any)
        {
            return (Number)any.getNumber();
        }

        inline std::string  stringCast(const Any & any)
        {
            return any.getString();
        }
        template<class Pointer>
        Pointer * pointerCast(const Any & any)
        {
            return (Pointer *)any.getPtr();
        }



        inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const SessionOptions & traits)
        {
            os << "{ " << "_protoType=" << traits._protoType
                << ", _rc4TcpEncryption=" << traits._rc4TcpEncryption
                << ", _openFlashPolicy=" << traits._openFlashPolicy
                << ", _setNoDelay=" << traits._setNoDelay
                << ", _sessionPulseInterval=" << traits._sessionPulseInterval
                << ", _connectPulseInterval=" << traits._connectPulseInterval
                << ", _reconnects=" << traits._reconnects
                << ", _reconnectClean=" << traits._reconnectClean
                << "}";
            return os;
        }


        inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream &os, const AccepterOptions & extend)
        {
            os << "{"
                << "_aID=" << extend._aID
                << ", _listenIP=" << extend._listenIP
                << ", _listenPort=" << extend._listenPort
                << ", _maxSessions=" << extend._maxSessions
                << ",_totalAcceptCount=" << extend._totalAcceptCount
                << ", _currentLinked=" << extend._currentLinked
                << ",_whitelistIP={";

            for (auto str : extend._whitelistIP)
            {
                os << str << ",";
            }
            os << "}";
            os << ", SessionOptions=" << extend._sessionOptions;
            os << "}";
            return os;
        }
    }
}





#endif

