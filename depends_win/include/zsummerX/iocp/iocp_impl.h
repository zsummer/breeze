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



#ifndef _ZSUMMERX_IOCP_IMPL_H_
#define _ZSUMMERX_IOCP_IMPL_H_


#include "common_impl.h"
#include "../timer/timer.h"

namespace zsummer
{
	namespace network
	{
		//! ioserver, message loop.
		class ZSummer :public std::enable_shared_from_this<ZSummer>
		{
		public:
			ZSummer(){m_io = NULL;}
			~ZSummer(){}

			inline bool Initialize();
			void RunOnce();
			//handle: std::function<void()>
			//switch initiative, in the multi-thread it's switch call thread simultaneously.
			inline void Post(_OnPostHandler &&h){ PostMsg(PCK_USER_DATA, std::move(h)); }
			inline unsigned long long CreateTimer(unsigned int delayms, _OnTimerHandler &&handle){return m_timer.CreateTimer(delayms, std::move(handle));}
			inline bool CancelTimer(unsigned long long timerID){return m_timer.CancelTimer(timerID);}
		private:
			inline void PostMsg(POST_COM_KEY pck, _OnPostHandler &&handle)
			{
				_OnPostHandler *ptr = new _OnPostHandler(std::move(handle));
				PostQueuedCompletionStatus(m_io, 0, pck, (LPOVERLAPPED)(ptr));
			}
			inline std::string ZSummerSection()
			{
				std::stringstream os;
				os << " ZSummerSection: m_iocp=" << (void*)m_io << ", current total timer=" << m_timer.GetTimersCount();
				return os.str();
			}
		public:
			HANDLE m_io;
			CTimer m_timer;
		};

		typedef std::shared_ptr<ZSummer> ZSummerPtr;
		inline bool ZSummer::Initialize()
		{
			if (m_io != NULL)
			{
				LCF("ZSummer::RunOnce[this0x" << this << "] iocp is craeted !" << ZSummerSection());
				return false;
			}
			m_io = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 1);
			if (!m_io)
			{
				LCF("ZSummer::RunOnce[this0x" << this << "] CreateIoCompletionPort False!" << ZSummerSection());
				return false;
			}
			return true;
		}









	}

}





















#endif











