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
#include <math.h>

// one timmer system  based on red-black tree (std::map).
namespace zsummer
{
    namespace network
    {
        using TimerID = unsigned long long;
        const unsigned long long   InvalidTimerID = 0;



        class Timer
        {
        public:
            Timer();
            ~Timer();
            //get current time tick. unit is millisecond.
            unsigned long long getSteadyTick();
            unsigned long long getSystemTick();
            TimerID makeTimeID(bool useSystemTick, unsigned int delayTick);
            std::pair<bool, unsigned long long> resolveTimeID(TimerID timerID);
            //get next expire time  be used to set timeout when calling select / epoll_wait / GetQueuedCompletionStatus.
            unsigned int getNextExpireTime();

            TimerID createTimer(unsigned int delayTick, _OnTimerHandler &&handle, bool useSysTime = true);
            TimerID createTimer(unsigned int delayTick,const _OnTimerHandler &handle, bool useSysTime = true);
            bool cancelTimer(TimerID timerID);
            // if have expired timer. the timer will trigger.
            void checkTimer();
            inline std::map<TimerID, _OnTimerHandler* >::size_type getTimersCount(){ return _sysQue.size() + _steadyQue.size(); }
        private:
            //! timer queue
            std::map<TimerID, _OnTimerHandler* > _sysQue;
            std::map<TimerID, _OnTimerHandler* > _steadyQue;
            unsigned long long _queSeq = 0; //! single sequence . assure timer ID is global single.

            const unsigned long long _startSystemTime = getSystemTick();
            const unsigned long long _startSteadyTime = getSteadyTick();

            const unsigned long long   SequenceBit = 15;
            const unsigned long long   SequenceMask = (unsigned long long)pow(2, SequenceBit) - 1;
            const unsigned long long   TimeSeqMask = (unsigned long long)pow(2, 51) - 1;
            const unsigned long long   UsedSysMask = 1ULL << 51;
        };
    }
}







#endif











