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


#ifndef ZSUMMER_TCPSESSION_MANAGER_H_
#define ZSUMMER_TCPSESSION_MANAGER_H_

#include "config.h"
#include "session.h"
namespace zsummer
{
    namespace network
    {


        inline SessionBlock * DefaultCreateBlock();
        inline void DefaultFreeBlock(SessionBlock *sb);

        inline OnBlockCheckResult DefaulBlockCheck(const char * begin, unsigned int len, unsigned int bound, unsigned int blockLimit)
        {
            auto ret = zsummer::proto4z::checkBuffIntegrity(begin, len, bound, blockLimit);
            return std::make_pair((BLOCK_CHECK_TYPE)ret.first, (unsigned int)ret.second);
        }
        inline void DefaultBlockDispatch(TcpSessionPtr session, const char * begin, unsigned int len)
        {
            LCW("DefaultBlockDispatch empty. ");
        }

        inline OnBlockCheckResult DefaultHTTPBlockCheck(const char * begin, unsigned int len, unsigned int bound,
                bool & isChunked, std::string& method, std::string & line, std::map<std::string,std::string> & head, std::string & body)
        {
            auto ret = zsummer::proto4z::checkHTTPBuffIntegrity(begin, len, bound, isChunked, method, line, head, body);
            return std::make_pair((BLOCK_CHECK_TYPE)ret.first, ret.second);
        }

        inline void DefaultHTTPBlockDispatch(TcpSessionPtr session, const std::string & mthoed, const std::string &methodLine, 
            const std::map<std::string, std::string> &head, const std::string & body)
        {
            LCW("DefaultHTTPBlockDispatch empty.");
        }


        /*
            SessionManager是一个单例singleton, 是一个对zsummerX底层接口的高级封装, 如果需要自己封装 则可以参考frame的做法或者example中的例子进行封装或使用.
            这个单例提供了所有网络的高级的可操作接口, 比如启动网络模块单例, 开启网络循环, 依次关闭部分网络功能 最后退出网络循环,  添加多个监听接口, 添加多个连出, 发送数据,
                跨线程的通知机制post, 创建取消定时器, 获取连接信息, 设置定时检测, 设置断线重莲次数和间隔, 设置是否支持flash Policy, 设置最大可连入的连接数, 设置协议是二进制的TCP协议(proto4z协议流), 
                设置协议是HTTP(可做WEB服务器和客户端使用, 很方便的做一些SDK认证和平台接入).
        */
        class SessionManager
        {
        private:
            SessionManager();

        public://!get the single and global object pointer   
            static SessionManager & getRef();
            inline static SessionManager * getPtr(){ return &getRef(); };
        public:
            //要使用SessionManager必须先调用start来启动服务.
            bool start();

            //退出消息循环.
            void stop();
            

            //阻塞当前线程并开始消息循环. 默认选用这个比较好. 当希望有更细力度的控制run的时候推荐使用runOnce
            bool run();
            inline bool isRunning(){ return _running; }

            //执行一次消息处理, 如果isImmediately为true, 则无论当前处理有无数据 都需要立即返回, 可以嵌入到任意一个线程中灵活使用
            //默认为false,  如果没有网络消息和事件消息 则会阻塞一小段时间, 有消息通知会立刻被唤醒.
            bool runOnce(bool isImmediately = false);

            //handle: std::function<void()>
            //switch initiative, in the multi-thread it's switch call thread simultaneously.
            //投递一个handler到SessionManager的线程中去处理, 线程安全.
            template<class H>
            void post(H &&h){ _summer->post(std::move(h)); }

            //it's blocking call. support ipv6 & ipv4 .
            inline std::string getHostByName(const std::string & name) { return zsummer::network::getHostByName(name); }
            //创建定时器 单位是毫秒 非线程安全.
            template <class H>
            zsummer::network::TimerID createTimer(unsigned int delayms, H &&h, bool useSystemTime = true)
            { return _summer->createTimer(delayms, std::move(h), useSystemTime); }
            template <class H>
            zsummer::network::TimerID createTimer(unsigned int delayms, const H &h, bool useSystemTime = true)
            {
                return _summer->createTimer(delayms, h, useSystemTime);
            }
            //取消定时器.  注意, 如果在定时器的回调handler中取消当前定时器 会失败的.
            bool cancelTimer(unsigned long long timerID){ return _summer->cancelTimer(timerID); }



            AccepterID addAccepter(const std::string& listenIP, unsigned short listenPort);
            AccepterOptions & getAccepterOptions(AccepterID aID);
            bool openAccepter(AccepterID aID);
            AccepterID getAccepterID(SessionID sID);


            SessionID addConnecter(const std::string& remoteHost, unsigned short remotePort);
            SessionOptions & getConnecterOptions(SessionID cID);
            bool openConnecter(SessionID cID);
            TcpSessionPtr getTcpSession(SessionID sID);

            std::string getRemoteIP(SessionID sID);
            unsigned short getRemotePort(SessionID sID);

            //send data.
            void sendSessionData(SessionID sID, const char * orgData, unsigned int orgDataLen);

            void fakeSessionData(SessionID sID, const char * orgData, unsigned int orgDataLen);

            //close session socket.
            void kickSession(SessionID sID);
            void kickClientSession(AccepterID aID = InvalidAccepterID);
            void kickConnect(SessionID cID = InvalidSessionID);
            void stopAccept(AccepterID aID = InvalidAccepterID);
        public:
            //statistical information
            inline unsigned long long getStatInfo(int stat){ return _statInfo[stat]; }
            alignas(unsigned long long) unsigned long long _statInfo[STAT_SIZE];

        public:
            SessionBlock * CreateBlock();
            void FreeBlock(SessionBlock * sb);
        private:
            std::deque<SessionBlock*> _freeBlock;
        private:
            friend class TcpSession;
            // 一个established状态的session已经关闭. 
            void removeSession(TcpSessionPtr session);

            //accept到新连接.
            void onAcceptNewClient(zsummer::network::NetErrorCode ec, const TcpSocketPtr & s, const TcpAcceptPtr & accepter, AccepterID aID);
        private:

            //消息循环
            EventLoopPtr _summer;

            //! 以下一组参数均为控制消息循环的开启和关闭用的
            bool  _running = true;  //默认是开启, 否则会在合适的时候退出消息循环.

            //!以下一组ID用于生成对应的unique ID. 
            AccepterID _lastAcceptID = InvalidAccepterID; //accept ID sequence. range  (0 - power(2,32))
            SessionID _lastSessionID = InvalidSessionID;//session ID sequence. range  (0 - __MIDDLE_SEGMENT_VALUE)
            SessionID _lastConnectID = InvalidSessionID;//connect ID sequence. range  (__MIDDLE_SEGMENT_VALUE - power(2,32))

            //!存储当前的连入连出的session信息和accept监听器信息.
            std::unordered_map<SessionID, TcpSessionPtr> _mapTcpSessionPtr;
            std::unordered_map<AccepterID, AccepterOptions > _mapAccepterOptions;
        };




        inline SessionBlock * DefaultCreateBlock()
        {
            return SessionManager::getRef().CreateBlock();
        }

        inline void DefaultFreeBlock(SessionBlock *sb)
        {
            SessionManager::getRef().FreeBlock(sb);
        }


    }
}


#endif
