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
* Copyright (C) 2010-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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

#ifndef _ZSUMMER_SELECT_IMPL_H_
#define _ZSUMMER_SELECT_IMPL_H_
#include "common_impl.h"
#include "../timer/timer.h"
#include "tcpaccept_impl.h"
#include "udpsocket_impl.h"

namespace zsummer
{
    namespace network
    {
        class TcpSocket;
        class UdpSocket;
        class TcpAccept;
        using TcpSocketPtr = std::shared_ptr<TcpSocket>;
        using TcpAcceptPtr = std::shared_ptr<TcpAccept>;
        using UdpSocketPtr = std::shared_ptr<UdpSocket>;


        using ArrayTcpSocket = std::vector<TcpSocketPtr>;
        using ArrayTcpAccept = std::vector<TcpAcceptPtr>;
        using ArrayUdpSocket = std::vector<UdpSocketPtr>;

        class EventLoop : public std::enable_shared_from_this<EventLoop>
        {
        public:
            using MessageStack = std::vector<void*> ;
            EventLoop(){}
            ~EventLoop(){}
            bool initialize();
            void runOnce(bool isImmediately = false);

            template <typename handle>
            inline void post(handle &&h)
            {
                PostMessage(std::move(h));
            }
            inline unsigned long long createTimer(unsigned int delayms, _OnTimerHandler &&handle, bool useSystemTime = true)
            {
                return _timer.createTimer(delayms, std::move(handle), useSystemTime);
            }
            inline unsigned long long createTimer(unsigned int delayms, const _OnTimerHandler &handle, bool useSystemTime = true)
            {
                return _timer.createTimer(delayms, handle, useSystemTime);
            }
            inline bool cancelTimer(unsigned long long timerID)
            {
                return _timer.cancelTimer(timerID);
            }

        public:
            void setEvent(int fd, int op /*0 read, 1 write, 2 error*/);
            void unsetEvent(int fd, int op /*0 read, 1 write, 2 error*/);
            void addTcpAccept(int fd, TcpAcceptPtr s);
            void addTcpSocket(int fd, TcpSocketPtr s);
            void addUdpSocket(int fd, UdpSocketPtr s);
            void clearSocket(int fd);

            void PostMessage(_OnPostHandler &&handle);
        private:
            std::string logSection();
        private:
            //线程消息
            int        _sockpair[2];
            fd_set _fdreads;
            fd_set _fdwrites;
            fd_set _fderrors;
            int _maxfd = 0;
            ArrayTcpSocket _arrayTcpSocket;
            ArrayTcpAccept _arrayTcpAccept;
            ArrayUdpSocket _arrayUdpSocket;
            MessageStack _postQueue;
            std::mutex     _postQueueLock;
            //! timmer
            Timer _timer;
        };
        using EventLoopPtr = std::shared_ptr<EventLoop> ;
    }

}





















#endif











