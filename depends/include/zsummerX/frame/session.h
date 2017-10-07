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
        class TcpSession : public std::enable_shared_from_this<TcpSession>
        {
        public:
            TcpSession();
            ~TcpSession();
            inline SessionOptions & getOptions(){ return _options; }
            void connect();
            void reconnect();
            bool attatch(const TcpSocketPtr &sockptr, AccepterID aID, SessionID sID);
            void send(const char *buf, unsigned int len);
            void close();
            
        private:

            bool doRecv();
            unsigned int onRecv(zsummer::network::NetErrorCode ec, int received);
            void onSend(zsummer::network::NetErrorCode ec, int sent);
            void onConnected(zsummer::network::NetErrorCode ec);
            void onPulse();

        public:
            inline void setEventLoop(EventLoopPtr el){ _eventLoop = el; }
            inline SessionID getAcceptID(){ return _acceptID; }
            inline SessionID getSessionID(){ return _sessionID; }
            inline void setSessionID(SessionID sID){ _sessionID = sID; }
            inline bool isInvalidSession(){ return !_sockptr; }
            inline const std::string & getRemoteIP(){ return _remoteIP; }
            inline void setRemoteIP(const std::string &remoteIP){ _remoteIP = remoteIP; }
            inline unsigned short getRemotePort(){ return _remotePort; }
            inline void setRemotePort(unsigned short remotePort){ _remotePort = remotePort; }
            inline std::size_t getSendQueSize(){ return _sendque.size(); }
            inline zsummer::network::NetErrorCode getLastError(){ return _lastRecvError; }

            inline const TupleParam& getUserParam(size_t index) { return peekTupleParamImpl(index); }
            inline void setUserParam(size_t index, const TupleParam &tp) { autoTupleParamImpl(index) = tp; }
            inline bool isUserParamInited(size_t index) { return std::get<TupleParamInited>(peekTupleParamImpl(index)); }
            inline double getUserParamNumber(size_t index) { return std::get<TupleParamNumber>(peekTupleParamImpl(index)); }
            inline void setUserParamNumber(size_t index, double f) { std::get<TupleParamNumber>(autoTupleParamImpl(index)) = f; }
            inline unsigned long long getUserParamInteger(size_t index) { return std::get<TupleParamInteger>(peekTupleParamImpl(index)); }
            inline void setUserParamInteger(size_t index, unsigned long long ull) { std::get<TupleParamInteger>(autoTupleParamImpl(index)) = ull; }
            inline const std::string & getUserParamString(size_t index) { return std::get<TupleParamString>(peekTupleParamImpl(index)); }
            inline void setUserParamString(size_t index, const std::string & str) { std::get<TupleParamString>(autoTupleParamImpl(index)) = str; }

        private:
            SessionOptions _options;
            EventLoopPtr _eventLoop;
            TcpSocketPtr  _sockptr;
            std::string _remoteIP;
            unsigned short _remotePort = 0;
            int _status = 0; //0 uninit, 1 connecting, 2 session established, 3  died
   
            //
            SessionID _sessionID = InvalidSessionID;
            AccepterID _acceptID = InvalidAccepterID;
            zsummer::network::TimerID _pulseTimerID = zsummer::network::InvalidTimerID;

            //! 
            SessionBlock* _recving = nullptr;
            SessionBlock* _sending = nullptr;
            unsigned int _sendingLen = 0;

            //! send data queue
            std::deque<SessionBlock *> _sendque;
            unsigned long long _reconnects = 0;

            //! rc encrypt
            RC4Encryption _rc4StateRead;
            RC4Encryption _rc4StateWrite;

            //!
            bool _bFirstRecvData = true;

            //!last recv error code
            zsummer::network::NetErrorCode _lastRecvError = NEC_SUCCESS;

            //! http status data
            bool _httpIsChunked = false;
            std::string _httpMethod;
            std::string _httpMethodLine;
            std::map<std::string, std::string> _httpHeader;

            
            //! user param
            std::vector<TupleParam> _param;
            TupleParam & autoTupleParamImpl(size_t index);
            const TupleParam & peekTupleParamImpl(size_t index) const;

        };
        using TcpSessionPtr = std::shared_ptr<TcpSession>;
    }
}


#endif


