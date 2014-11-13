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
 * Copyright (C) 2010-2014 YaweiZhang <yawei_zhang@foxmail.com>.
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




#ifndef ZSUMMER_MSG_MANAGER_H_
#define ZSUMMER_MSG_MANAGER_H_
#include <zsummerX/frame/FrameHeader.h>


class CMessageDispatcher
{
private:
	CMessageDispatcher(){}
	typedef std::unordered_map<ProtoID, std::vector<OnMessageFunction> > MapProtoDispatch;
public:
	static CMessageDispatcher & getRef();
	static CMessageDispatcher * getPtr(){ return &getRef(); }
	~CMessageDispatcher(){};

	//message
	inline void RegisterSessionOrgMessage(const OnOrgMessageFunction & msgfun){ m_vctOrgSessionDispatch.push_back(msgfun); }
	inline void RegisterSessionMessage(ProtoID protocolID, const OnMessageFunction & msgfun){ m_mapSessionDispatch[protocolID].push_back(msgfun); }
	inline void RegisterSessionDefaultMessage(const OnMessageFunction & msgfun){ m_vctDefaultSessionDispatch.push_back(msgfun); }

	//event. can use method IsSessionID or IsConnectID to resolution who is the sessionID
	inline void RegisterOnSessionEstablished(const OnSessionEstablished & fun){m_vctOnSessionEstablished.push_back(fun); }
	inline void RegisterOnSessionDisconnect(const OnSessionDisconnect & fun){ m_vctOnSessionDisconnect.push_back(fun); }

	//heartbeat
	inline void RegisterOnSessionPulse(const OnSessionPulseTimer & fun) { m_vctOnSessionPulse.push_back(fun); }
	//http
	inline void RegisterOnSessionHTTPMessage(const OnHTTPMessageFunction & fun) { m_vctSessionHTTPMessage.push_back(fun); }

public:
	inline bool DispatchOrgSessionMessage(SessionID sID, const char * blockBegin, FrameStreamTraits::Integer blockSize);
	inline void DispatchSessionMessage(SessionID sID, ProtoID pID, ReadStreamPack & msg);
	inline void DispatchOnSessionEstablished(SessionID sID);
	inline void DispatchOnSessionDisconnect(SessionID sID);
	inline void DispatchOnSessionPulse(SessionID sID, unsigned int pulseInterval);
	inline bool DispatchSessionHTTPMessage(SessionID sID, const zsummer::proto4z::PairString & commonLine, const zsummer::proto4z::HTTPHeadMap &head, const std::string & body);

	private:
		//!message
		MapProtoDispatch m_mapSessionDispatch;
		std::vector<OnOrgMessageFunction> m_vctOrgSessionDispatch;
		std::vector<OnMessageFunction> m_vctDefaultSessionDispatch;

		//http
		std::vector<OnHTTPMessageFunction> m_vctSessionHTTPMessage;

		//event
		std::vector<OnSessionEstablished> m_vctOnSessionEstablished;
		std::vector<OnSessionDisconnect> m_vctOnSessionDisconnect;

		std::vector<OnSessionPulseTimer> m_vctOnSessionPulse;
};




inline bool CMessageDispatcher::DispatchOrgSessionMessage(SessionID sID, const char * blockBegin, FrameStreamTraits::Integer blockSize)
{
	if (m_vctOrgSessionDispatch.empty())
	{
		return true;
	}

	try
	{
		for (auto & fun : m_vctOrgSessionDispatch)
		{
			LCT("Entry DispatchOrgSessionMessage  SessionID=" << sID << ", blockSize=" << blockSize);
			if (!fun(sID, blockBegin, blockSize))
			{
				return false;
			}
		}
	}
	catch (std::runtime_error e)
	{
		LCE("Leave DispatchOrgSessionMessage With Runtime Error:  SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		return false;
	}
	catch (...)
	{
		LCE("Leave DispatchOrgSessionMessage With Unknown Runtime Error: SessionID=" << sID);
		return false;
	}
	return true;
}

inline void CMessageDispatcher::DispatchSessionMessage(SessionID sID, ProtoID pID, ReadStreamPack & msg)
{
	MapProtoDispatch::iterator iter = m_mapSessionDispatch.find(pID);
	if ((iter == m_mapSessionDispatch.end() || iter->second.empty()) && m_vctDefaultSessionDispatch.empty())
	{
		LCE("Entry DispatchSessionMessage[" << pID << "] Failed: UNKNOWN ProtoID.  SessionID=" << sID << ", ProtoID=" << pID);
		return;
	}
	try
	{
		if (iter != m_mapSessionDispatch.end() && !iter->second.empty())
		{
			for (auto & fun : iter->second)
			{
				LCT("Entry DispatchSessionMessage[" << pID << "]  SessionID=" << sID);
				msg.ResetMoveCursor();
				msg >> pID;
				fun(sID, pID, msg);
			}	
		}
		else
		{
			for (auto & fun : m_vctDefaultSessionDispatch)
			{
				msg.ResetMoveCursor();
				msg >> pID;
				fun(sID, pID, msg);
			}
		}
		LCT("Leave DispatchSessionMessage[" << pID << "]  SessionID=" << sID);
	}
	catch (std::runtime_error e)
	{
		LCE("Leave DispatchSessionMessage[" << pID << "] With Runtime Error: SessionID=" << sID << ", rsLen=" << msg.GetStreamLen() << ", Error Message=\"" << e.what() << "\"");
	}
	catch (...)
	{
		LCE("Leave DispatchSessionMessage[" << pID << "] With Unknown Runtime Error: SessionID=" << sID);
	}
}


inline void CMessageDispatcher::DispatchOnSessionEstablished(SessionID sID)
{
	if (m_vctOnSessionEstablished.empty())
	{
		return;
	}
	for (auto &fun : m_vctOnSessionEstablished)
	{
		try
		{
			LCT("Entry DispatchOnSessionEstablished SessionID=" << sID);
			fun(sID);
			LCT("Leave DispatchOnSessionEstablished SessionID=" << sID);
		}

		catch (std::runtime_error e)
		{
			LCE("Leave DispatchOnSessionEstablished Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		}
		catch (...)
		{
			LCE("Leave DispatchOnSessionEstablished Unknown Runtime Error: SessionID=" << sID);
		}
	}


}
inline void CMessageDispatcher::DispatchOnSessionDisconnect(SessionID sID)
{
	if (m_vctOnSessionDisconnect.empty())
	{
		return;
	}
	for (auto & fun : m_vctOnSessionDisconnect)
	{
		try
		{
			LCT("Entry DispatchOnSessionDisconnect SessionID=" << sID);
			fun(sID);
			LCT("Leave DispatchOnSessionDisconnect SessionID=" << sID);
		}
		catch (std::runtime_error e)
		{
			LCE("Leave DispatchOnSessionDisconnect Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		}
		catch (...)
		{
			LCE("Leave DispatchOnSessionDisconnect Unknown Runtime Error: SessionID=" << sID);
		}
	}
}


inline void CMessageDispatcher::DispatchOnSessionPulse(SessionID sID, unsigned int pulseInterval)
{
	if (m_vctOnSessionPulse.empty())
	{
		return;
	}
	for (auto & fun : m_vctOnSessionPulse)
	{
		try
		{
			LCT("Entry DispatchOnSessionPulse SessionID=" << sID);
			fun(sID, pulseInterval);
			LCT("Leave DispatchOnSessionPulse SessionID=" << sID);
		}
		catch (std::runtime_error e)
		{
			LCE("Leave DispatchOnSessionPulse Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		}
		catch (...)
		{
			LCE("Leave DispatchOnSessionPulse Unknown Runtime Error: SessionID=" << sID);
		}
	}
}


inline bool  CMessageDispatcher::DispatchSessionHTTPMessage(SessionID sID, const zsummer::proto4z::PairString & commonLine, const zsummer::proto4z::HTTPHeadMap &head, const std::string & body)
{
	try
	{
		for (auto & fun : m_vctSessionHTTPMessage)
		{
			LCT("Entry DispatchSessionHTTPMessage  SessionID=" << sID << ", commond=" << commonLine.first << ", commondValue=" << commonLine.second
				<< ", head count=" << head.size() << ", bodySize=" << body.length());
			fun(sID, commonLine, head, body);
			LCT("Leave DispatchSessionHTTPMessage  SessionID=" << sID);
		}
		return true;
	}
	catch (std::runtime_error e)
	{
		LCE("Leave DispatchSessionHTTPMessage With Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
	}
	catch (...)
	{
		LCE("Leave DispatchSessionHTTPMessage With Unknown Runtime Error: SessionID=" << sID);
	}
	return false;
}



#endif


