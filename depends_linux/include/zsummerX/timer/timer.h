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
#pragma once

#ifndef _ZSUMMERX_TIMER_H_
#define _ZSUMMERX_TIMER_H_
#include "../common/common.h"


// build a timmer system  based on red-black tree (std::map).
namespace zsummer
{
    namespace network
    {
        typedef unsigned long long TimerID;
        const unsigned long long   InvalidTimerID = 0;
        class Timer
        {
        public:
            Timer()
            {
                _queSeq = 0;
                _nextExpire = (unsigned int)-1;
            }
            ~Timer()
            {
            }
            //get current time tick. unit is millisecond.
            inline unsigned  int getNowMilliTick()
            {
                return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            }

            //get next expire time  be used to set timeout when calling select / epoll_wait / GetQueuedCompletionStatus.
            inline unsigned int getNextExpireTime()
            {
                unsigned int now = getNowMilliTick();
                unsigned int delay = _nextExpire - now;
                if (delay > 100)
                {
                    delay = 100;
                }
                return delay;
            }

            TimerID createTimer(unsigned int delayms, _OnTimerHandler &&handle);
            bool cancelTimer(TimerID timerID);
            // if have expired timer. the timer will trigger.
            void checkTimer();
            inline std::map<TimerID, _OnTimerHandler* >::size_type GetTimersCount(){ return _queTimer.size(); }
        private:
            //! timer queue
            std::map<TimerID, _OnTimerHandler* > _queTimer;
            unsigned int _queSeq; //! single sequence . assure timer ID is global single.
            unsigned int _nextExpire; //! cache the next expire time for check timer with   performance 
        };
    }
}







#endif











