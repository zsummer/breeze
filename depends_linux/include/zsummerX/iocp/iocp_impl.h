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



#ifndef _ZSUMMERX_IOCP_IMPL_H_
#define _ZSUMMERX_IOCP_IMPL_H_


#include "common_impl.h"
#include "../timer/timer.h"

namespace zsummer
{
    namespace network
    {
        //! ioserver, message loop.
        class EventLoop :public std::enable_shared_from_this<EventLoop>
        {
        public:
            EventLoop(){_io = NULL;}
            ~EventLoop(){}

            inline bool initialize();
            void runOnce(bool isImmediately = false);
            //handle: std::function<void()>
            //switch initiative, in the multi-thread it's switch call thread simultaneously.
            inline void post(_OnPostHandler &&h){ postMsg(PCK_USER_DATA, std::move(h)); }
            inline unsigned long long createTimer(unsigned int delayms, _OnTimerHandler &&handle){return _timer.createTimer(delayms, std::move(handle));}
            inline bool cancelTimer(unsigned long long timerID){return _timer.cancelTimer(timerID);}
        private:
            inline void postMsg(POST_COM_KEY pck, _OnPostHandler &&handle)
            {
                _OnPostHandler *ptr = new _OnPostHandler(std::move(handle));
                PostQueuedCompletionStatus(_io, 0, pck, (LPOVERLAPPED)(ptr));
            }
            inline std::string logSection()
            {
                std::stringstream os;
                os << " logSection: _iocp=" << (void*)_io << ", current total timer=" << _timer.GetTimersCount();
                return os.str();
            }
        public:
            HANDLE _io;
            Timer _timer;
        };

        typedef std::shared_ptr<EventLoop> EventLoopPtr;
        inline bool EventLoop::initialize()
        {
            if (_io != NULL)
            {
                LCF("EventLoop::runOnce[this0x" << this << "] iocp is craeted !" << logSection());
                return false;
            }
            _io = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 1);
            if (!_io)
            {
                LCF("EventLoop::runOnce[this0x" << this << "] CreateIoCompletionPort False!" << logSection());
                return false;
            }
            return true;
        }









    }

}





















#endif











