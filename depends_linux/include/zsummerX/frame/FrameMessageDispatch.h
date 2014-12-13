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


class MessageDispatcher
{
private:
	MessageDispatcher(){}
	typedef std::unordered_map<ProtoID, std::vector<OnMessageFunction> > MapProtoDispatch;
public:
	static MessageDispatcher & getRef();
	inline static MessageDispatcher * getPtr(){ return &getRef(); }
	~MessageDispatcher(){};

	//message
	inline void registerSessionOrgMessage(const OnOrgMessageFunction & msgfun){ _vctOrgSessionDispatch.push_back(msgfun); }
	inline void registerSessionMessage(ProtoID protocolID, const OnMessageFunction & msgfun){ _mapSessionDispatch[protocolID].push_back(msgfun); }
	inline void registerSessionDefaultMessage(const OnMessageFunction & msgfun){ _vctDefaultSessionDispatch.push_back(msgfun); }

	//event. can use method isSessionID or isConnectID to resolution who is the sessionID
	inline void registerOnSessionEstablished(const OnSessionEstablished & fun){_vctOnSessionEstablished.push_back(fun); }
	inline void registerOnSessionDisconnect(const OnSessionDisconnect & fun){ _vctOnSessionDisconnect.push_back(fun); }

	//heartbeat
	inline void registerOnSessionPulse(const OnSessionPulseTimer & fun) { _vctOnSessionPulse.push_back(fun); }
	//http
	inline void registerOnSessionHTTPMessage(const OnHTTPMessageFunction & fun) { _vctSessionHTTPMessage.push_back(fun); }

public:
	inline bool dispatchOrgSessionMessage(SessionID sID, const char * blockBegin, FrameStreamTraits::Integer blockSize);
	inline void dispatchSessionMessage(SessionID sID, ProtoID pID, ReadStreamPack & msg);
	inline void dispatchOnSessionEstablished(SessionID sID);
	inline void dispatchOnSessionDisconnect(SessionID sID);
	inline void dispatchOnSessionPulse(SessionID sID, unsigned int pulseInterval);
	inline bool dispatchSessionHTTPMessage(SessionID sID, const zsummer::proto4z::PairString & commonLine, const zsummer::proto4z::HTTPHeadMap &head, const std::string & body);

	private:
		//!message
		MapProtoDispatch _mapSessionDispatch;
		std::vector<OnOrgMessageFunction> _vctOrgSessionDispatch;
		std::vector<OnMessageFunction> _vctDefaultSessionDispatch;

		//http
		std::vector<OnHTTPMessageFunction> _vctSessionHTTPMessage;

		//event
		std::vector<OnSessionEstablished> _vctOnSessionEstablished;
		std::vector<OnSessionDisconnect> _vctOnSessionDisconnect;

		std::vector<OnSessionPulseTimer> _vctOnSessionPulse;
};




inline bool MessageDispatcher::dispatchOrgSessionMessage(SessionID sID, const char * blockBegin, FrameStreamTraits::Integer blockSize)
{
	if (_vctOrgSessionDispatch.empty())
	{
		return true;
	}

	try
	{
		for (auto & fun : _vctOrgSessionDispatch)
		{
			LCT("Entry dispatchOrgSessionMessage  SessionID=" << sID << ", blockSize=" << blockSize);
			if (!fun(sID, blockBegin, blockSize))
			{
				return false;
			}
		}
	}
	catch (std::runtime_error e)
	{
		LCE("Leave dispatchOrgSessionMessage With Runtime Error:  SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		return false;
	}
	catch (...)
	{
		LCE("Leave dispatchOrgSessionMessage With Unknown Runtime Error: SessionID=" << sID);
		return false;
	}
	return true;
}

inline void MessageDispatcher::dispatchSessionMessage(SessionID sID, ProtoID pID, ReadStreamPack & msg)
{
	MapProtoDispatch::iterator iter = _mapSessionDispatch.find(pID);
	if ((iter == _mapSessionDispatch.end() || iter->second.empty()) && _vctDefaultSessionDispatch.empty())
	{
		LCE("Entry dispatchSessionMessage[" << pID << "] Failed: UNKNOWN ProtoID.  SessionID=" << sID << ", ProtoID=" << pID);
		return;
	}
	try
	{
		if (iter != _mapSessionDispatch.end() && !iter->second.empty())
		{
			for (auto & fun : iter->second)
			{
				LCT("Entry dispatchSessionMessage[" << pID << "]  SessionID=" << sID);
				msg.resetMoveCursor();
				msg >> pID;
				fun(sID, pID, msg);
			}	
		}
		else
		{
			for (auto & fun : _vctDefaultSessionDispatch)
			{
				msg.resetMoveCursor();
				msg >> pID;
				fun(sID, pID, msg);
			}
		}
		LCT("Leave dispatchSessionMessage[" << pID << "]  SessionID=" << sID);
	}
	catch (std::runtime_error e)
	{
		LCE("Leave dispatchSessionMessage[" << pID << "] With Runtime Error: SessionID=" << sID << ", rsLen=" << msg.getStreamLen() << ", Error Message=\"" << e.what() << "\"");
	}
	catch (...)
	{
		LCE("Leave dispatchSessionMessage[" << pID << "] With Unknown Runtime Error: SessionID=" << sID);
	}
}


inline void MessageDispatcher::dispatchOnSessionEstablished(SessionID sID)
{
	if (_vctOnSessionEstablished.empty())
	{
		return;
	}
	for (auto &fun : _vctOnSessionEstablished)
	{
		try
		{
			LCT("Entry dispatchOnSessionEstablished SessionID=" << sID);
			fun(sID);
			LCT("Leave dispatchOnSessionEstablished SessionID=" << sID);
		}

		catch (std::runtime_error e)
		{
			LCE("Leave dispatchOnSessionEstablished Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		}
		catch (...)
		{
			LCE("Leave dispatchOnSessionEstablished Unknown Runtime Error: SessionID=" << sID);
		}
	}


}
inline void MessageDispatcher::dispatchOnSessionDisconnect(SessionID sID)
{
	if (_vctOnSessionDisconnect.empty())
	{
		return;
	}
	for (auto & fun : _vctOnSessionDisconnect)
	{
		try
		{
			LCT("Entry dispatchOnSessionDisconnect SessionID=" << sID);
			fun(sID);
			LCT("Leave dispatchOnSessionDisconnect SessionID=" << sID);
		}
		catch (std::runtime_error e)
		{
			LCE("Leave dispatchOnSessionDisconnect Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		}
		catch (...)
		{
			LCE("Leave dispatchOnSessionDisconnect Unknown Runtime Error: SessionID=" << sID);
		}
	}
}


inline void MessageDispatcher::dispatchOnSessionPulse(SessionID sID, unsigned int pulseInterval)
{
	if (_vctOnSessionPulse.empty())
	{
		return;
	}
	for (auto & fun : _vctOnSessionPulse)
	{
		try
		{
			LCT("Entry dispatchOnSessionPulse SessionID=" << sID);
			fun(sID, pulseInterval);
			LCT("Leave dispatchOnSessionPulse SessionID=" << sID);
		}
		catch (std::runtime_error e)
		{
			LCE("Leave dispatchOnSessionPulse Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
		}
		catch (...)
		{
			LCE("Leave dispatchOnSessionPulse Unknown Runtime Error: SessionID=" << sID);
		}
	}
}


inline bool  MessageDispatcher::dispatchSessionHTTPMessage(SessionID sID, const zsummer::proto4z::PairString & commonLine, const zsummer::proto4z::HTTPHeadMap &head, const std::string & body)
{
	try
	{
		for (auto & fun : _vctSessionHTTPMessage)
		{
			LCT("Entry dispatchSessionHTTPMessage  SessionID=" << sID << ", commond=" << commonLine.first << ", commondValue=" << commonLine.second
				<< ", head count=" << head.size() << ", bodySize=" << body.length());
			fun(sID, commonLine, head, body);
			LCT("Leave dispatchSessionHTTPMessage  SessionID=" << sID);
		}
		return true;
	}
	catch (std::runtime_error e)
	{
		LCE("Leave dispatchSessionHTTPMessage With Runtime Error: SessionID=" << sID << ", Error Message=\"" << e.what() << "\"");
	}
	catch (...)
	{
		LCE("Leave dispatchSessionHTTPMessage With Unknown Runtime Error: SessionID=" << sID);
	}
	return false;
}



#endif


