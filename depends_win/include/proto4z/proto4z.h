/*
 * proto4z License
 * -----------
 * 
 * proto4z is licensed under the terms of the MIT license reproduced below.
 * This means that proto4z is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2013-2014 YaweiZhang <yawei_zhang@foxmail.com>.
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


/*
 * AUTHORS:  YaweiZhang <yawei_zhang@foxmail.com>
 * VERSION:  1.0
 * PURPOSE:  A lightweight library for process protocol .
 * CREATION: 2013.07.04
 * LCHANGE:  2014.08.20
 * LICENSE:  Expat/MIT License, See Copyright Notice at the begin of this file.
 */

/*
 * Web Site: www.zsummer.net
 * mail: yawei_zhang@foxmail.com
 */

/* 
 * UPDATES LOG
 * 
 * VERSION 0.1.0 <DATE: 2013.07.4>
 * 	create the first project.  
 * 	support big-endian or little-endian
 * VERSION 0.3.0 <DATE: 2014.03.17>
 *  support user-defined header
 *  WriteStream support auto alloc memory or attach exist memory
 *  proto4z support stl container
 * VERSION 0.4.0 <DATE: 2014.05.16>
 *  Add some useful interface method
 * VERSION 0.5.0 <DATE: 2014.08.06>
 *  Add static buff for optimize
 *  Add genProto tools
 * VERSION 1.0.0 <DATE: 2014.08.20>
 *  Add HTTP proto
 * VERSION 1.1.0 <DATE: 2014.11.11>
 *  support http chunked header
 *  support http decode and encode method
 * 
 */
#pragma once
#ifndef _PROTO4Z_H_
#define _PROTO4Z_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <assert.h>
#ifndef WIN32
#include <stdexcept>
#else
#include <exception>
#endif
#ifndef _ZSUMMER_BEGIN
#define _ZSUMMER_BEGIN namespace zsummer {
#endif  
#ifndef _ZSUMMER_PROTO4Z_BEGIN
#define _ZSUMMER_PROTO4Z_BEGIN namespace proto4z {
#endif
_ZSUMMER_BEGIN
_ZSUMMER_PROTO4Z_BEGIN

#ifdef WIN32
#pragma warning(disable:4996)
#endif

enum ZSummer_EndianType
{
	BigEndian,
	LittleEndian,
};





//////////////////////////////////////////////////////////////////////////
//! protocol traits instruction
//////////////////////////////////////////////////////////////////////////

// Memory layout
//|-----------------pack header------------|-------pack body-------|
//|-[PreOffset]-[PackLenSize]-[PostOffset]-|-----------------------|

//PackLenIsContainHead effect
//|-----header len -----|-------body len--------|
//|---------------pack len----------------------| //true
//|---------------------|-------pack len--------| //false
//
struct DefaultStreamHeadTraits
{
	typedef unsigned short Integer; //User-Defined Integer Type must in [unsigned char, unsigned short, unsigned int, unsigned long long].
	const static Integer PreOffset = 0; //User-Defined 
	const static Integer PostOffset = 0; //User-Defined 
	const static Integer MaxPackLen = (Integer)-1; //User-Defined. example:  Integer = unsigned short(-1) ==>(65535)
	const static bool	 PackLenIsContainHead = true; //User-Defined 
	const static ZSummer_EndianType EndianType = LittleEndian;//User-Defined 
	const static Integer IntegerTypeSize = sizeof(Integer); // Don't Touch. PackLenSize and sizeof(Integer) must be equal. 
	const static Integer HeadLen = PreOffset + IntegerTypeSize + PostOffset; //Don't Touch. Head Length.
};

//protocol Traits example, User-Defined
struct TestBigStreamHeadTraits
{
	typedef unsigned int Integer;
	const static Integer PreOffset = 2; 
	const static Integer PostOffset = 4;
	const static Integer MaxPackLen = -1;
	const static bool PackLenIsContainHead = false;
	const static ZSummer_EndianType EndianType = BigEndian;
	const static Integer IntegerTypeSize = sizeof(Integer); // Don't Touch. PackLenSize and sizeof(Integer) must be equal. 
	const static Integer HeadLen = PreOffset + IntegerTypeSize + PostOffset; //Don't Touch.
};

//stream translate to Integer with endian type.
template<class Integer, class StreamHeadTrait>
Integer StreamToInteger(const char stream[sizeof(Integer)]);

//integer translate to stream with endian type.
template<class Integer, class StreamHeadTrait>
void IntegerToStream(Integer integer, char *stream);

//!get runtime local endian type. 
static const unsigned short __gc_localEndianType = 1;
inline ZSummer_EndianType __LocalEndianType();


//////////////////////////////////////////////////////////////////////////
//! get the residue length of packet  on the information received.
//////////////////////////////////////////////////////////////////////////


enum INTEGRITY_RET_TYPE
{
	IRT_SUCCESS = 0,
	IRT_SHORTAGE = 1,
	IRT_CORRUPTION = 2,
};
//! return value:
//! first: IRT_SUCCESS data integrity. second: current integrity data lenght.
//! first: IRT_SHORTAGE data not integrity. second: shortage lenght.
//! first: IRT_CORRUPTION data corruption. second: data lenght
template<class StreamHeadTrait>
inline std::pair<INTEGRITY_RET_TYPE, typename StreamHeadTrait::Integer>
CheckBuffIntegrity(const char * buff, typename StreamHeadTrait::Integer curBuffLen, 
typename StreamHeadTrait::Integer maxBuffLen /*= StreamHeadTrait::MaxPackLen*/);



//////////////////////////////////////////////////////////////////////////
//! class WriteStream: serializes the specified data to byte stream.
//////////////////////////////////////////////////////////////////////////
//StreamHeadTrait: User-Defined like DefaultStreamHeadTrait
//AllocType: inner allocate memory used this, default use std::allocator<char>

enum UserBuffType
{
	UBT_INVALIDE = 0,
	UBT_ATTACH, // attach exist buff.
	UBT_AUTO, //use std::string
	UBT_STATIC_AUTO, //use static std::string
};

template<class StreamHeadTrait/*=DefaultStreamHeadTraits*/, class _Alloc = std::allocator<char> >
class WriteStream
{
public:
	typedef typename StreamHeadTrait::Integer Integer;
	//! maxStreamLen : The maximum length can be written.
	//! bNoWrite : if true then WriteStream will not do any write operation.
	//! pAttachData : Attach to the existing memory.
	WriteStream(UserBuffType ubt = UBT_AUTO, Integer maxStreamLen = StreamHeadTrait::MaxPackLen);//Automatically allocate memory
	WriteStream(char * pAttachData, Integer maxStreamLen, bool bNoWrite = false);// attach exist memory
	~WriteStream(){}
public:
	//get head memory to packHead
	inline void GetStreamHead(char *streamHead/*[StreamHeadTrait::HeadLen]*/);
	//fill head memory from packHead
	inline void SetStreamHead(const char *streamHead/*[StreamHeadTrait::HeadLen]*/);

	//get total stream buff, the pointer must be used immediately.
	inline char* GetStream();
	//get total stream length.
	inline Integer GetStreamLen(){return m_cursor;}

	//get body stream buff, the pointer used by reflecting immediately.
	inline char* GetBodyStream();
	//get body stream length.
	inline Integer GetBodyStreamLen(){ return m_cursor - StreamHeadTrait::HeadLen; }

	//write original data.
	inline WriteStream<StreamHeadTrait> & AppendOriginalData(const void * data, Integer unit);


	inline WriteStream<StreamHeadTrait> & operator << (bool data) { return WriteSimpleData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (char data) { return WriteSimpleData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (unsigned char data) { return WriteSimpleData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (short data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (unsigned short data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (int data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (unsigned int data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (long data) { return WriteIntegerData((long long)data); }
	inline WriteStream<StreamHeadTrait> & operator << (unsigned long data) { return WriteIntegerData((unsigned long long)data); }
	inline WriteStream<StreamHeadTrait> & operator << (long long data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (unsigned long long data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (float data) { return WriteIntegerData(data); }
	inline WriteStream<StreamHeadTrait> & operator << (double data) { return WriteIntegerData(data); }

protected:
	//! check move cursor is valid. if invalid then throw exception.
	inline void CheckMoveCursor(Integer unit = (Integer)0);

	//! fix pack len.
	inline void FixPackLen();

	//! write integer data with endian type.
	template <class T>
	inline WriteStream<StreamHeadTrait> & WriteIntegerData(T t);

	//! write some types of data with out endian type. It's relative to WriteIntegerData method.
	template <class T>
	inline WriteStream<StreamHeadTrait> & WriteSimpleData(T t);
private:

	UserBuffType m_useBuffType;
	std::basic_string<char, std::char_traits<char>, _Alloc > m_data; //! If not attach any memory, class WriteStream will used this to managing memory.
	static std::basic_string<char, std::char_traits<char>, _Alloc > m_staticData; //! warning: single-thread, static buff.
	char * m_pAttachData;//! attach memory pointer
	Integer m_maxStreamLen; //! can write max size
	Integer m_cursor; //! current move cursor.
	bool  m_bNoWrite; //! if true then WriteStream will not do any write operation.
};
template<class StreamHeadTrait/*=DefaultStreamHeadTraits*/, class _Alloc>
std::basic_string<char, std::char_traits<char>, _Alloc > WriteStream<StreamHeadTrait, _Alloc>::m_staticData;
//////////////////////////////////////////////////////////////////////////
//class ReadStream: De-serialization the specified data from byte stream.
//////////////////////////////////////////////////////////////////////////

//StreamHeadTrait: User-Defined like DefaultStreamHeadTrait
template<class StreamHeadTrait/*=DefaultStreamHeadTraits*/>
class ReadStream
{
public:
	typedef typename StreamHeadTrait::Integer Integer;
	ReadStream(const char *pAttachData, Integer attachDataLen);
	~ReadStream(){}
public:

	inline void ResetMoveCursor(){ m_cursor = StreamHeadTrait::HeadLen;}
	//get head memory to packHead
	inline void GetStreamHead(char *streamHead/*[StreamHeadTrait::HeadLen]*/);
	inline Integer GetStreamHeadLen(){ return StreamHeadTrait::HeadLen; };

	//get attach data buff
	inline const char* GetStream();
	//get pack length in stream
	inline Integer GetStreamLen();

	//get body stream buff, the pointer used by reflecting immediately.
	inline const char* GetStreamBody();
	//get body stream length.
	inline Integer GetStreamBodyLen();

	//get current unread stream buff, the pointer used by reflecting immediately.
	inline const char* GetStreamUnread();
	//get current unread stream buff length
	inline Integer GetStreamUnreadLen();


	inline const char * PeekOriginalData(Integer unit);
	inline void SkipOriginalData(Integer unit);


	inline ReadStream<StreamHeadTrait> & operator >> (bool & data) { return ReadSimpleData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (char & data) { return ReadSimpleData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (unsigned char & data) { return ReadSimpleData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (short & data) { return ReadIntegerData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (unsigned short & data) { return ReadIntegerData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (int & data) { return ReadIntegerData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (unsigned int & data) { return ReadIntegerData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (long & data){ long long tmp = 0;ReadStream & ret = ReadIntegerData(tmp);data =(long) tmp;return ret;}
	inline ReadStream<StreamHeadTrait> & operator >> (unsigned long & data){ unsigned long long tmp = 0;ReadStream & ret = ReadIntegerData(tmp);data = (unsigned long)tmp;return ret;}
	inline ReadStream<StreamHeadTrait> & operator >> (long long & data) { return ReadIntegerData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (unsigned long long & data) { return ReadIntegerData(data); }
	inline ReadStream<StreamHeadTrait> & operator >> (float & data) { return ReadIntegerData(data); } 
	inline ReadStream<StreamHeadTrait> & operator >> (double & data) { return ReadIntegerData(data); }
protected:
	inline void CheckMoveCursor(Integer unit);
	template <class T>
	inline ReadStream<StreamHeadTrait> & ReadIntegerData(T & t);
	template <class T>
	inline ReadStream<StreamHeadTrait> & ReadSimpleData(T & t);

private:
	const char * m_pAttachData;
	Integer m_maxDataLen;
	Integer m_cursor;
};


//////////////////////////////////////////////////////////////////////////
//! stl container
//////////////////////////////////////////////////////////////////////////

//write c-style string
template<class StreamHeadTrait>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const char *const data)
{
	typename StreamHeadTrait::Integer len = (typename StreamHeadTrait::Integer)strlen(data);
	ws << len;
	ws.AppendOriginalData(data, len);
	return ws;
}

//write std::string
template<class StreamHeadTrait, class _Traits, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::basic_string<char, _Traits, _Alloc> & data)
{
	typename StreamHeadTrait::Integer len = (typename StreamHeadTrait::Integer)data.length();
	ws << len;
	ws.AppendOriginalData(data.c_str(), len);
	return ws;
}
//read std::string
template<class StreamHeadTrait, class _Traits, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::basic_string<char, _Traits, _Alloc> & data)
{
	typename StreamHeadTrait::Integer len = 0;
	rs >> len;
	data.assign(rs.PeekOriginalData(len), len);
	rs.SkipOriginalData(len);
	return rs;
}


//std::vector
template<class StreamHeadTrait, class T, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::vector<T, _Alloc> & vct)
{
	ws << (typename StreamHeadTrait::Integer)vct.size();
	for (typename std::vector<T, _Alloc>::const_iterator iter = vct.begin(); iter != vct.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class StreamHeadTrait, typename T, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::vector<T, _Alloc> & vct)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		T t;
		rs >> t;
		vct.push_back(t);
	}
	return rs;
}

//std::set
template<class StreamHeadTrait, class Key, class _Pr, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::set<Key, _Pr, _Alloc> & k)
{
	ws << (typename StreamHeadTrait::Integer)k.size();
	for (typename std::set<Key, _Pr, _Alloc>::const_iterator iter = k.begin(); iter != k.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class StreamHeadTrait, class Key, class _Pr, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::set<Key, _Pr, _Alloc> & k)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		Key t;
		rs >> t;
		k.insert(t);
	}
	return rs;
}

//std::multiset
template<class StreamHeadTrait, class Key, class _Pr, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::multiset<Key, _Pr, _Alloc> & k)
{
	ws << (typename StreamHeadTrait::Integer)k.size();
	for (typename std::multiset<Key, _Pr, _Alloc>::const_iterator iter = k.begin(); iter != k.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class StreamHeadTrait, class Key, class _Pr, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::multiset<Key, _Pr, _Alloc> & k)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		Key t;
		rs >> t;
		k.insert(t);
	}
	return rs;
}

//std::map
template<class StreamHeadTrait, class Key, class Value, class _Pr, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::map<Key, Value, _Pr, _Alloc> & kv)
{
	ws << (typename StreamHeadTrait::Integer)kv.size();
	for (typename std::map<Key, Value, _Pr, _Alloc>::const_iterator iter = kv.begin(); iter != kv.end(); ++iter)
	{
		ws << iter->first;
		ws << iter->second;
	}
	return ws;
}

template<class StreamHeadTrait, class Key, class Value, class _Pr, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::map<Key, Value, _Pr, _Alloc> & kv)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		std::pair<Key, Value> pr;
		rs >> pr.first;
		rs >> pr.second;
		kv.insert(pr);
	}
	return rs;
}

//std::multimap
template<class StreamHeadTrait, class Key, class Value, class _Pr, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::multimap<Key, Value, _Pr, _Alloc> & kv)
{
	ws << (typename StreamHeadTrait::Integer)kv.size();
	for (typename std::multimap<Key, Value, _Pr, _Alloc>::const_iterator iter = kv.begin(); iter != kv.end(); ++iter)
	{
		ws << iter->first;
		ws << iter->second;
	}
	return ws;
}

template<class StreamHeadTrait, class Key, class Value, class _Pr, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::multimap<Key, Value, _Pr, _Alloc> & kv)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		std::pair<Key, Value> pr;
		rs >> pr.first;
		rs >> pr.second;
		kv.insert(pr);
	}
	return rs;
}


//std::list
template<class StreamHeadTrait, class Value, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::list<Value, _Alloc> & l)
{
	ws << (typename StreamHeadTrait::Integer)l.size();
	for (typename std::list<Value,_Alloc>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class StreamHeadTrait, class Value, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::list<Value, _Alloc> & l)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		Value t;
		rs >> t;
		l.push_back(t);
	}
	return rs;
}
//std::deque
template<class StreamHeadTrait, class Value, class _Alloc>
inline WriteStream<StreamHeadTrait> & operator << (WriteStream<StreamHeadTrait> & ws, const std::deque<Value, _Alloc> & l)
{
	ws << (typename StreamHeadTrait::Integer)l.size();
	for (typename std::deque<Value,_Alloc>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class StreamHeadTrait, class Value, class _Alloc>
inline ReadStream<StreamHeadTrait> & operator >> (ReadStream<StreamHeadTrait> & rs, std::deque<Value, _Alloc> & l)
{
	typename StreamHeadTrait::Integer totalCount = 0;
	rs >> totalCount;
	for (typename StreamHeadTrait::Integer i = 0; i < totalCount; ++i)
	{
		Value t;
		rs >> t;
		l.push_back(t);
	}
	return rs;
}



//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////

inline ZSummer_EndianType __LocalEndianType()
{
	if (*(const unsigned char *)&__gc_localEndianType == 1)
	{
		return LittleEndian;
	}
	return BigEndian;
}

template<class Integer, class StreamHeadTrait>
Integer StreamToInteger(const char stream[sizeof(Integer)])
{
	unsigned short integerLen = sizeof(Integer);
	Integer integer = 0 ;
	if (integerLen == 1)
	{
		integer = (Integer)stream[0];
	}
	else
	{
		if (StreamHeadTrait::EndianType != __LocalEndianType())
		{
			unsigned char *dst = (unsigned char*)&integer;
			unsigned char *src = (unsigned char*)stream + integerLen;
			while (integerLen > 0)
			{
				*dst++ = *--src;
				integerLen --;
			}
		}
		else
		{
			memcpy(&integer, stream, integerLen);
		}
	}
	return integer;
}

template<class Integer, class StreamHeadTrait>
void IntegerToStream(Integer integer, char *stream)
{
	unsigned short integerLen = sizeof(Integer);
	if (integerLen == 1)
	{
		stream[0] = (char)integer;
	}
	else
	{
		if (StreamHeadTrait::EndianType != __LocalEndianType())
		{
			unsigned char *src = (unsigned char*)&integer + integerLen;
			unsigned char *dst = (unsigned char*)stream;
			while (integerLen > 0)
			{
				*dst++ = *--src;
				integerLen --;
			}
		}
		else
		{
			memcpy(stream, &integer, integerLen);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////


template<class StreamHeadTrait>
inline std::pair<INTEGRITY_RET_TYPE, typename StreamHeadTrait::Integer> CheckBuffIntegrity(const char * buff, typename StreamHeadTrait::Integer curBuffLen, typename StreamHeadTrait::Integer maxBuffLen)
{
	//! 检查包头是否完整
	if (curBuffLen < StreamHeadTrait::HeadLen)
	{
		return std::make_pair(IRT_SHORTAGE, StreamHeadTrait::HeadLen - curBuffLen);
	}

	//! 获取包长度
	typename StreamHeadTrait::Integer packLen = StreamToInteger<typename StreamHeadTrait::Integer, StreamHeadTrait>(buff+StreamHeadTrait::PreOffset);
	if (!StreamHeadTrait::PackLenIsContainHead)
	{
		typename StreamHeadTrait::Integer oldInteger = packLen;
		packLen += StreamHeadTrait::HeadLen;
		if (packLen < oldInteger) //over range
		{
			return std::make_pair(IRT_CORRUPTION, curBuffLen);
		}
	}

	//! check
	if (packLen > maxBuffLen)
	{
		return std::make_pair(IRT_CORRUPTION, curBuffLen);
	}
	if (packLen == curBuffLen)
	{
		return std::make_pair(IRT_SUCCESS, packLen);
	}
	if (packLen < curBuffLen)
	{
		return std::make_pair(IRT_SUCCESS, packLen);
	}
	return std::make_pair(IRT_SHORTAGE, packLen - curBuffLen);
}



//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////

template<class StreamHeadTrait, class AllocType>
WriteStream<StreamHeadTrait, AllocType>::WriteStream(UserBuffType ubt, Integer maxStreamLen)
{
	m_useBuffType = ubt;
	m_pAttachData = NULL;
	m_bNoWrite = false;
	m_maxStreamLen = maxStreamLen;
	m_cursor = StreamHeadTrait::HeadLen;
	Integer reserveSize = sizeof(Integer) == 1 ? 255 : 1200;
	if (reserveSize < StreamHeadTrait::HeadLen)
	{
		reserveSize = StreamHeadTrait::HeadLen;
	}
	if (m_useBuffType == UBT_AUTO)
	{
		m_data.reserve(reserveSize);
		m_data.resize((size_t)StreamHeadTrait::HeadLen, '\0');
	}
	else if (m_useBuffType == UBT_STATIC_AUTO)
	{
		if (m_staticData.capacity() < (size_t)StreamHeadTrait::HeadLen)
		{
			m_staticData.reserve((size_t)StreamHeadTrait::HeadLen);
		}
		m_staticData.resize((size_t)StreamHeadTrait::HeadLen, '\0');
	}
}


template<class StreamHeadTrait, class AllocType>
WriteStream<StreamHeadTrait, AllocType>::WriteStream(char * pAttachData, Integer maxStreamLen, bool bNoWrite)
{
	m_useBuffType = UBT_ATTACH;
	m_pAttachData = pAttachData;
	m_maxStreamLen = maxStreamLen;
	m_cursor = StreamHeadTrait::HeadLen;
	m_bNoWrite = bNoWrite;
}

template<class StreamHeadTrait, class AllocType>
inline void WriteStream<StreamHeadTrait, AllocType>::CheckMoveCursor(Integer unit)
{
	if (m_maxStreamLen < StreamHeadTrait::HeadLen)
	{
		throw std::runtime_error("construction param error. attach memory size less than StreamHeadTrait::HeadLen.");
	}
	if (m_cursor > m_maxStreamLen)
	{
		throw std::runtime_error("bound over. cursor in end-of-data.");
	}
	if (unit > m_maxStreamLen)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
	if (m_maxStreamLen - m_cursor < unit)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
}

template<class StreamHeadTrait, class AllocType>
inline void WriteStream<StreamHeadTrait, AllocType>::FixPackLen()
{
	if (m_bNoWrite)
	{
		return;
	}
	Integer packLen = m_cursor;
	if (!StreamHeadTrait::PackLenIsContainHead)
	{
		packLen -= StreamHeadTrait::HeadLen;
	}
	if (m_useBuffType == UBT_ATTACH)
	{
		IntegerToStream<Integer, StreamHeadTrait>(packLen, &m_pAttachData[StreamHeadTrait::PreOffset]);
	}
	else if (m_useBuffType == UBT_AUTO)
	{
		IntegerToStream<Integer, StreamHeadTrait>(packLen, &m_data[StreamHeadTrait::PreOffset]);
	}
	else if (m_useBuffType == UBT_STATIC_AUTO)
	{
		IntegerToStream<Integer, StreamHeadTrait>(packLen, &m_staticData[StreamHeadTrait::PreOffset]);
	}
	
}
template<class StreamHeadTrait, class AllocType>
inline void WriteStream<StreamHeadTrait, AllocType>::GetStreamHead(char *streamHead)
{
	if (m_bNoWrite)
	{
		return;
	}
	if (m_useBuffType == UBT_ATTACH)
	{
		memcpy(streamHead, m_pAttachData, StreamHeadTrait::HeadLen);
	}
	else if (m_useBuffType == UBT_AUTO)
	{
		memcpy(streamHead, &m_data[0], StreamHeadTrait::HeadLen);
	}
	else if (m_useBuffType == UBT_STATIC_AUTO)
	{
		memcpy(streamHead, &m_staticData[0], StreamHeadTrait::HeadLen);
	}
}
template<class StreamHeadTrait, class AllocType>
inline void WriteStream<StreamHeadTrait, AllocType>::SetStreamHead(const char *streamHead)
{
	if (m_bNoWrite)
	{
		return;
	}
	if (m_useBuffType == UBT_ATTACH)
	{
		memcpy(m_pAttachData, streamHead, StreamHeadTrait::HeadLen);
	}
	else if (m_useBuffType == UBT_AUTO)
	{
		memcpy(&m_data[0], streamHead, StreamHeadTrait::HeadLen);
	}
	else if (m_useBuffType == UBT_STATIC_AUTO)
	{
		memcpy(&m_staticData[0], streamHead, StreamHeadTrait::HeadLen);
	}
	FixPackLen();
}

template<class StreamHeadTrait, class AllocType>
inline char* WriteStream<StreamHeadTrait, AllocType>::GetStream()
{
	if (m_bNoWrite)
	{
		return NULL;
	}
	if (m_useBuffType == UBT_ATTACH)
	{
		return m_pAttachData;
	}
	else if (m_useBuffType == UBT_AUTO)
	{
		return &m_data[0];
	}
	else if (m_useBuffType == UBT_STATIC_AUTO)
	{
		return &m_staticData[0];
	}
	return NULL;
}

template<class StreamHeadTrait, class AllocType>
inline char* WriteStream<StreamHeadTrait, AllocType>::GetBodyStream()
{
	if (m_bNoWrite)
	{
		return NULL;
	}
	if (m_useBuffType == UBT_ATTACH)
	{
		return m_pAttachData + StreamHeadTrait::HeadLen;
	}
	else if (m_useBuffType == UBT_AUTO)
	{
		return &m_data[0] + StreamHeadTrait::HeadLen;
	}
	else if (m_useBuffType == UBT_STATIC_AUTO)
	{
		return &m_staticData[0] + StreamHeadTrait::HeadLen;
	}
	return NULL;
}

template<class StreamHeadTrait, class AllocType>
inline WriteStream<StreamHeadTrait> & WriteStream<StreamHeadTrait, AllocType>::AppendOriginalData(const void * data, Integer unit)
{
	CheckMoveCursor(unit);
	if (!m_bNoWrite)
	{
		if (m_useBuffType == UBT_ATTACH)
		{
			memcpy(&m_pAttachData[m_cursor], data, unit);
		}
		else if (m_useBuffType == UBT_AUTO)
		{
			m_data.append((const char*)data, unit);
		}
		else if (m_useBuffType == UBT_STATIC_AUTO)
		{
			m_staticData.append((const char*)data, unit);
		}
	}
	m_cursor += unit;
	FixPackLen();
	return *this;
}

template<class StreamHeadTrait, class AllocType> template <class T> 
inline WriteStream<StreamHeadTrait> & WriteStream<StreamHeadTrait, AllocType>::WriteIntegerData(T t)
{
	Integer unit = sizeof(T);
	CheckMoveCursor(unit);
	if (!m_bNoWrite)
	{
		if (m_useBuffType == UBT_ATTACH)
		{
			IntegerToStream<T, StreamHeadTrait>(t, &m_pAttachData[m_cursor]);
		}
		else if (m_useBuffType == UBT_AUTO)
		{
			m_data.append((const char*)&t, unit);
			if (StreamHeadTrait::EndianType != __LocalEndianType())
			{
				IntegerToStream<T, StreamHeadTrait>(t, &m_data[m_cursor]);
			}
		}
		else if (m_useBuffType == UBT_STATIC_AUTO)
		{
			m_staticData.append((const char*)&t, unit);
			if (StreamHeadTrait::EndianType != __LocalEndianType())
			{
				IntegerToStream<T, StreamHeadTrait>(t, &m_staticData[m_cursor]);
			}
		}
	}
	m_cursor += unit;
	FixPackLen();
	return * this;
}


template<class StreamHeadTrait, class AllocType> template <class T>
inline WriteStream<StreamHeadTrait> & WriteStream<StreamHeadTrait, AllocType>::WriteSimpleData(T t)
{
	Integer unit = sizeof(T);
	CheckMoveCursor(unit);
	if (!m_bNoWrite)
	{
		if (m_useBuffType == UBT_ATTACH)
		{
			memcpy(&m_pAttachData[m_cursor], &t, unit);
		}
		else if (m_useBuffType == UBT_AUTO)
		{
			m_data.append((const char*)&t, unit);
		}
		else if (m_useBuffType == UBT_STATIC_AUTO)
		{
			m_staticData.append((const char*)&t, unit);
		}
	}

	m_cursor += unit;
	FixPackLen();
	return * this;
}






//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////
template<class StreamHeadTrait>
ReadStream<StreamHeadTrait>::ReadStream(const char *pAttachData, Integer attachDataLen)
{
	m_pAttachData = pAttachData;
	m_maxDataLen = attachDataLen;
	m_cursor = StreamHeadTrait::HeadLen;
	if (m_maxDataLen > StreamHeadTrait::MaxPackLen)
	{
		m_maxDataLen = StreamHeadTrait::MaxPackLen;
	}
	if (m_maxDataLen < StreamHeadTrait::HeadLen)
	{
		m_pAttachData = NULL;
	}
}


template<class StreamHeadTrait>
inline void ReadStream<StreamHeadTrait>::CheckMoveCursor(Integer unit)
{
	if (m_cursor > m_maxDataLen)
	{
		throw std::runtime_error("bound over. cursor in end-of-data.");
	}
	if (unit > m_maxDataLen)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
	if (m_maxDataLen - m_cursor < unit)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
}
template<class StreamHeadTrait>
inline void ReadStream<StreamHeadTrait>::GetStreamHead(char *streamHead)
{
	memcpy(streamHead, m_pAttachData, StreamHeadTrait::HeadLen);
}

template<class StreamHeadTrait>
inline const char* ReadStream<StreamHeadTrait>::GetStream()
{
	return m_pAttachData;
}

template<class StreamHeadTrait>
inline typename ReadStream<StreamHeadTrait>::Integer ReadStream<StreamHeadTrait>::GetStreamLen()
{
	Integer packLen = StreamToInteger<Integer, StreamHeadTrait>(&m_pAttachData[StreamHeadTrait::PreOffset]);
	if (!StreamHeadTrait::PackLenIsContainHead)
	{
		return packLen + StreamHeadTrait::HeadLen;
	}
	if (packLen > m_maxDataLen)
	{
		return 0;
	}
	return packLen;
}

template<class StreamHeadTrait>
inline const char* ReadStream<StreamHeadTrait>::GetStreamBody()
{
	return &m_pAttachData[StreamHeadTrait::HeadLen];
}

template<class StreamHeadTrait>
inline typename ReadStream<StreamHeadTrait>::Integer ReadStream<StreamHeadTrait>::GetStreamBodyLen()
{
	return GetStreamLen() - StreamHeadTrait::HeadLen;
}

template<class StreamHeadTrait>
inline const char* ReadStream<StreamHeadTrait>::GetStreamUnread()
{
	return &m_pAttachData[m_cursor];
}

template<class StreamHeadTrait>
typename ReadStream<StreamHeadTrait>::Integer ReadStream<StreamHeadTrait>::GetStreamUnreadLen()
{
	return GetStreamBodyLen() + StreamHeadTrait::HeadLen - m_cursor;
}

template<class StreamHeadTrait> template <class T>
inline ReadStream<StreamHeadTrait> & ReadStream<StreamHeadTrait>::ReadIntegerData(T & t)
{
	Integer unit = sizeof(T);
	CheckMoveCursor(unit);
	t = StreamToInteger<T, StreamHeadTrait>(&m_pAttachData[m_cursor]);
	m_cursor += unit;
	return * this;
}
template<class StreamHeadTrait> template <class T>
inline ReadStream<StreamHeadTrait> & ReadStream<StreamHeadTrait>::ReadSimpleData(T & t)
{
	Integer unit = sizeof(T);
	CheckMoveCursor(unit);
	memcpy(&t, &m_pAttachData[m_cursor], unit);
	m_cursor += unit;
	return * this;
}
template<class StreamHeadTrait>
inline const char * ReadStream<StreamHeadTrait>::PeekOriginalData(Integer unit)
{
	CheckMoveCursor(unit);
	return &m_pAttachData[m_cursor];
}
template<class StreamHeadTrait>
inline void ReadStream<StreamHeadTrait>::SkipOriginalData(Integer unit)
{
	CheckMoveCursor(unit);
	m_cursor += unit;
}








/////////////////////////
//http proto 
/////////////////////////
const char *const CRLF = "\r\n";
const char CR = '\r'; //CRLF
const char LF = '\n';
const char SEGM = ':';
const char BLANK = ' ';
typedef std::pair<std::string, std::string> PairString;
typedef std::map<std::string, std::string> HTTPHeadMap;

inline INTEGRITY_RET_TYPE CheckHTTPBuffIntegrity(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen, 
							bool hadHeader, bool & isChunked, PairString& commonLine, HTTPHeadMap & head, std::string & body, unsigned int &usedCount);

std::string urlEncode(const std::string& orgString);
std::string urlDecode(const std::string& orgString);
class WriteHTTP
{
public:
	const char * GetStream(){ return m_buff.c_str();}
	unsigned int GetStreamLen() { return (unsigned int)m_buff.length();}
	void AddHead(std::string key, std::string val)
	{
		m_head.insert(std::make_pair(key, val));
	}
	void Post(std::string uri, std::string content)
	{
		char buf[100];
		sprintf(buf, "%u", (unsigned int)content.length());
		m_head.insert(std::make_pair("Content-Length", buf));
		m_buff.append("POST " + uri + " HTTP/1.1" + CRLF);
		WriteGeneralHead();
		m_buff.append(CRLF);
		m_buff.append(content);
	}
	void Get(std::string uri)
	{
		m_head.insert(std::make_pair("Content-Length", "0"));
		m_buff.append("GET " + uri + " HTTP/1.1" + CRLF);
		WriteGeneralHead();
		m_buff.append(CRLF);
	}
	void Response(std::string statusCode, std::string content)
	{
		char buf[100];
		sprintf(buf, "%u", (unsigned int)content.length());
		m_head.insert(std::make_pair("Content-Length", buf));
		m_buff.append("HTTP/1.1 " + statusCode + " ^o^" + CRLF);
		WriteGeneralHead();
		m_buff.append(CRLF);
		m_buff.append(content);
	}
protected:
	void WriteGeneralHead()
	{
		for (HTTPHeadMap::iterator iter = m_head.begin(); iter != m_head.end(); ++iter)
		{
			m_buff.append(iter->first + ":" + iter->second + CRLF);
		}
	}
private:
	HTTPHeadMap m_head;
	std::string m_buff;
};


inline std::string urlEncode(const std::string & orgString)
{
	std::string ret;
	for (int i = 0; i < (int)orgString.length(); ++i)
	{
		char ch = orgString[i];
		if (ch == '\0')
		{
			break;
		}
		if ((ch >= 'A' && ch <= 'Z')
			|| (ch >= 'a' && ch <= 'z')
			|| (ch >= '0' && ch <= '9')
			|| ch == '-' || ch == '_' || ch == '.' || ch == '~')
		{
			ret += ch;
		}
		else if (ch == ' ')
		{
			ret += '+';
		}
		else
		{
			ret += '%';
			unsigned char tmp = ch / 16;
			ret += tmp > 9 ? tmp + 55 : tmp + 48;
			tmp = ch % 16;
			ret += tmp > 9 ? tmp + 55 : tmp + 48;
		}
	}
	return ret;
}
inline std::string urlDecode(const std::string & orgString)
{
	std::string ret;
	unsigned int count = (unsigned int)orgString.length();
	unsigned int cursor = 0;
	while (cursor < count)
	{
		char ch = orgString[cursor];
		if (ch == '\0')
		{
			break;
		}
		if (ch == '+')
		{
			ret += ' ';
			cursor++;
			continue;
		}
		if (ch == '%')
		{
			if (count - cursor < 2)
			{
				break; //error
			}
			unsigned char och;
			unsigned char x = orgString[cursor + 1];
			if (x >= 'A' && x <= 'Z') x = x - 'A' + 10;
			else if (x >= 'a' && x <= 'z') x = x - 'a' + 10;
			else if (x >= '0' && x <= '9') x = x - '0';
			och = x * 16;
			x = orgString[cursor + 2];
			if (x >= 'A' && x <= 'Z') x = x - 'A' + 10;
			else if (x >= 'a' && x <= 'z') x = x - 'a' + 10;
			else if (x >= '0' && x <= '9') x = x - '0';
			och += x;
			ret += och;
			cursor += 3;
			continue;
		}
		ret += ch;
		cursor++;
	}
	return ret;
}


inline unsigned int InnerReadLine(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen,  bool isKV, bool isCommondLine,
	std::string & outStringKey, std::string &outStringValue)
{
	if (curBuffLen == 0)
	{
		return IRT_CORRUPTION;
	}
	
	unsigned int cursor = 0;
	short readStatus = 0;
	INTEGRITY_RET_TYPE isIntegrityData = IRT_SHORTAGE;

	outStringKey.clear();
	outStringValue.clear();

	while (cursor < curBuffLen)
	{
		if (cursor >= maxBuffLen)
		{
			isIntegrityData = IRT_CORRUPTION;
			break;
		}
		if (buff[cursor] == CR)
		{
			cursor++;
			continue;
		}
		if (buff[cursor] == LF)
		{
			cursor++;
			isIntegrityData = IRT_SUCCESS;
			break;
		}
		if (!isKV)
		{
			outStringKey.push_back(buff[cursor]);
			cursor++;
			continue;
		}
		else
		{
			if (isCommondLine)
			{
				if (buff[cursor] == BLANK)
				{
					readStatus++;
					cursor++;
					continue;
				}
			}
			else // ! isCommondLine
			{
				if (buff[cursor] == SEGM)
				{
					readStatus++;
					cursor++;
					continue;
				}
				if (buff[cursor] == BLANK && readStatus == 0)
				{
					cursor++;
					continue;
				}
				if (buff[cursor] == BLANK && readStatus == 1 && outStringValue.empty())
				{
					cursor++;
					continue;
				}
			}//end. !isCommondLine
			if (readStatus == 0)
			{
				outStringKey.push_back(buff[cursor]);
			}
			else if (readStatus == 1)
			{
				outStringValue.push_back(buff[cursor]);
			}
			cursor++;
			continue;
		}//end. isKV
	}//extract character loop

	if (isIntegrityData != IRT_SUCCESS)
	{
		throw isIntegrityData;
	}
	return cursor;
}

inline INTEGRITY_RET_TYPE CheckHTTPBuffIntegrity(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen,
	bool hadHeader, bool &isChunked, PairString& commonLine, HTTPHeadMap & head, std::string & body, unsigned int &usedCount)
{
	if (!hadHeader)
	{
		isChunked = false;
	}
	int bodyLenght = -1;
	usedCount = 0;
	PairString keyValue;

	//extract head
	if (!hadHeader)
	{

		//extract common line
		try
		{
			usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, true, true, commonLine.first, commonLine.second);
		}
		catch (INTEGRITY_RET_TYPE t)
		{
			return t;
		}

		//extract head line
		head.clear();
		try
		{
			do
			{
				keyValue.first.clear();
				keyValue.second.clear();
				usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, true, false, keyValue.first, keyValue.second);
				if (keyValue.first.empty() && keyValue.second.empty())
				{
					break;
				}
				if (keyValue.first == "Content-Length")
				{
					bodyLenght = atoi(keyValue.second.c_str());
				}
				else if (keyValue.first == "Transfer-Encoding")
				{
					isChunked = true;
				}
				head.insert(keyValue);
			} while (true);
		}
		catch (INTEGRITY_RET_TYPE t)
		{
			return t;
		}
	}
	


	//read chunked header
	if (isChunked)
	{
		try
		{
			keyValue.first.clear();
			keyValue.second.clear();
			usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, false, false, keyValue.first, keyValue.second);
			//chunked end. need closed.
			if (keyValue.first.empty())
			{
				return IRT_CORRUPTION;
			}
			sscanf(keyValue.first.c_str(), "%x", &bodyLenght);
			if (bodyLenght == 0)
			{
				//http socket end.
				return IRT_CORRUPTION;
			}
			
		}
		catch (INTEGRITY_RET_TYPE t)
		{
			return t;
		}
	}
	else if (hadHeader)
	{
		return IRT_SHORTAGE;
	}
	else if (commonLine.first == "GET")
	{
		return IRT_SUCCESS;
	}
	
	if (bodyLenght == -1 || usedCount + bodyLenght > maxBuffLen)
	{
		return IRT_CORRUPTION;
	}
	if (bodyLenght + usedCount > curBuffLen)
	{
		return IRT_SHORTAGE;
	}
	body.assign(buff + usedCount, bodyLenght);
	usedCount += bodyLenght;

	if (isChunked)//clean chunked end CRLF
	{
		try
		{
			keyValue.first.clear();
			keyValue.second.clear();
			usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, false, false, keyValue.first, keyValue.second);
			//chunked end. need closed.
			if (!keyValue.first.empty())
			{
				return IRT_CORRUPTION;
			}
		}
		catch (INTEGRITY_RET_TYPE t)
		{
			return t;
		}
	}
	

	return IRT_SUCCESS;
}









#ifndef _ZSUMMER_END
#define _ZSUMMER_END }
#endif  
#ifndef _ZSUMMER_PROTO4Z_END
#define _ZSUMMER_PROTO4Z_END }
#endif

_ZSUMMER_PROTO4Z_END
_ZSUMMER_END

#endif
