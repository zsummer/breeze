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
		class CTimer
		{
		public:
			CTimer()
			{
				m_queSeq = 0;
				m_nextExpire = (unsigned int)-1;
			}
			~CTimer()
			{
			}
			//get current time tick. unit is millisecond.
			inline unsigned  int GetNowMilliTick()
			{
				return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			}

			//get next expire time  be used to set timeout when calling select / epoll_wait / GetQueuedCompletionStatus.
			inline unsigned int GetNextExpireTime()
			{
				unsigned int now = GetNowMilliTick();
				unsigned int dwDelayMs = m_nextExpire - now;
				if (dwDelayMs > 100)
				{
					dwDelayMs = 100;
				}
				return dwDelayMs;
			}

			inline TimerID CreateTimer(unsigned int delayms, const _OnTimerHandler &handle)
			{
				_OnTimerHandler *pfunc= new _OnTimerHandler(handle);
				unsigned int now = GetNowMilliTick();
				unsigned int expire = now+delayms;
				unsigned long long timerID = expire;
				timerID <<= 32;
				timerID |= m_queSeq++; //timerID is merge expire time and a sequence. sequence assure the ID is single.
				m_queTimer.insert(std::make_pair(timerID, pfunc));
				if (m_nextExpire > expire)
				{
					m_nextExpire = expire;
				}
				return timerID;
			}
			inline bool CancelTimer(TimerID timerID)
			{
				std::map<unsigned long long, _OnTimerHandler* >::iterator iter = m_queTimer.find(timerID);
				if (iter != m_queTimer.end())
				{
					delete iter->second;
					m_queTimer.erase(iter);
					return true;
				}
				return false;
			}
			// if have expired timer. the timer will trigger.
			inline void CheckTimer()
			{
				if (!m_queTimer.empty())
				{
					unsigned int now = GetNowMilliTick();
					if (m_nextExpire > now)
					{
						return;
					}

					while(1)
					{
						if (m_queTimer.empty())
						{
							m_nextExpire = (unsigned int)-1;
							break;
						}
						auto iter = m_queTimer.begin();
						unsigned long long timerID = iter->first;
						_OnTimerHandler * handler = iter->second;
						unsigned int nextexpire = timerID>>32;
						if (nextexpire > now)
						{
							m_nextExpire = nextexpire;
							break;
						}
						//erase the pointer from timer queue before call handler.
						m_queTimer.erase(iter);
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
			inline std::map<TimerID, _OnTimerHandler* >::size_type GetTimersCount(){ return m_queTimer.size(); }
		private:
			//! timer queue
			std::map<TimerID, _OnTimerHandler* > m_queTimer;
			unsigned int m_queSeq; //! single sequence . assure timer ID is global single.
			unsigned int m_nextExpire; //! cache the next expire time for check timer with   performance 
		};
	}
}







#endif











