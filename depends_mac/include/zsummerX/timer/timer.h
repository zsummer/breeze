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
* Copyright (C) 2013 YaweiZhang <yawei_zhang@foxmail.com>.
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
				unsigned int dwDelayMs = _nextExpire - now;
				if (dwDelayMs > 100)
				{
					dwDelayMs = 100;
				}
				return dwDelayMs;
			}

			inline TimerID createTimer(unsigned int delayms, _OnTimerHandler &&handle)
			{
				_OnTimerHandler *pfunc= new _OnTimerHandler(std::move(handle));
				unsigned int now = getNowMilliTick();
				unsigned int expire = now+delayms;
				unsigned long long timerID = expire;
				timerID <<= 32;
				timerID |= _queSeq++; //timerID is merge expire time and a sequence. sequence assure the ID is single.
				_queTimer.insert(std::make_pair(timerID, pfunc));
				if (_nextExpire > expire)
				{
					_nextExpire = expire;
				}
				return timerID;
			}
			inline bool cancelTimer(TimerID timerID)
			{
				std::map<unsigned long long, _OnTimerHandler* >::iterator iter = _queTimer.find(timerID);
				if (iter != _queTimer.end())
				{
					delete iter->second;
					_queTimer.erase(iter);
					return true;
				}
				return false;
			}
			// if have expired timer. the timer will trigger.
			inline void checkTimer()
			{
				if (!_queTimer.empty())
				{
					unsigned int now = getNowMilliTick();
					if (_nextExpire > now)
					{
						return;
					}

					while(1)
					{
						if (_queTimer.empty())
						{
							_nextExpire = (unsigned int)-1;
							break;
						}
						auto iter = _queTimer.begin();
						unsigned long long timerID = iter->first;
						_OnTimerHandler * handler = iter->second;
						unsigned int nextexpire = timerID>>32;
						if (nextexpire > now)
						{
							_nextExpire = nextexpire;
							break;
						}
						//erase the pointer from timer queue before call handler.
						_queTimer.erase(iter);
						try
						{
							(*handler)();
						}
						catch (std::runtime_error e)
						{
							LCW("OnTimerHandler have runtime_error exception. err=" << e.what());
						}
						catch (...)
						{
							LCW("OnTimerHandler have unknown exception.");
						}
						delete handler;
					}
					
				}
			}
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











