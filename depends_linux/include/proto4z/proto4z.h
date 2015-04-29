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
 * Copyright (C) 2013-2015 YaweiZhang <yawei_zhang@foxmail.com>.
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
 * 
 * VERSION 0.3.0 <DATE: 2014.03.17>
 *  support user-defined header
 *  WriteStream support auto alloc memory or attach exist memory
 *  proto4z support stl container
 * 
 * VERSION 0.4.0 <DATE: 2014.05.16>
 *  Add some useful interface method
 * 
 * VERSION 0.5.0 <DATE: 2014.08.06>
 *  Add static buff for optimize
 *  Add genProto tools
 * 
 * VERSION 1.0.0 <DATE: 2014.08.20>
 *  Add HTTP protocol
 * 
 * VERSION 1.1.0 <DATE: 2014.11.11>
 *  support HTTP chunked header
 *  support HTTP decode and encode method
 *
 * VERSION 1.2.0 <DATE: 2014.12.19>
 *  new naming notations
 *  simplify traits
 *  
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
//|-----   header  -----|-------  body  --------|
//|--packlen-|-protoID--|-------  body  --------|


typedef unsigned int Integer;
typedef unsigned short ProtoInteger;

const static Integer MaxPackLen = 1024*1024;

//stream translate to Integer with endian type.
template<class Integer>
Integer streamToInteger(const char stream[sizeof(Integer)]);

//integer translate to stream with endian type.
template<class Integer>
void integerToStream(Integer integer, char *stream);

//!get runtime local endian type. 
static const unsigned short __gc_localEndianType = 1;
inline ZSummer_EndianType __localEndianType();


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
//! buff 缓冲区内容起始位置
//! curBuffLen 当前缓冲区内容大小
//! boundLen 当前缓冲区的边界大小, 如果对boundLen有疑惑 请填写和maxBuffLen一样的值
//! maxBuffLen 当前缓冲区实际最大大小
inline std::pair<INTEGRITY_RET_TYPE, Integer>
checkBuffIntegrity(const char * buff, Integer curBuffLen, Integer boundLen, Integer maxBuffLen);



//////////////////////////////////////////////////////////////////////////
//! class WriteStream: serializes the specified data to byte stream.
//////////////////////////////////////////////////////////////////////////
//StreamHeadTrait: User-Defined like DefaultStreamHeadTrait


class WriteStream
{
public:
	//! bNoWrite : if true then WriteStream will not do any write operation.
	//! attachData : Attach to the existing memory.
	inline WriteStream(ProtoInteger pID, char * attachData = NULL, Integer maxStreamLen = 0, bool bNoWrite = false);
	~WriteStream(){}
public:
	//get total stream buff, the pointer must be used immediately.
	inline char* getStream();
	//get total stream length.
	inline Integer getStreamLen(){return _cursor;}

	//get body stream buff, the pointer used by reflecting immediately.
	inline char* getStreamBody();
	//get body stream length.
	inline Integer getStreamBodyLen(){ return _cursor - _headLen; }

	//write original data.
	inline WriteStream & appendOriginalData(const void * data, Integer unit);
	inline WriteStream & fixOriginalData(Integer offset, Integer unit);

	inline WriteStream & operator << (bool data) { return writeSimpleData(data); }
	inline WriteStream & operator << (char data) { return writeSimpleData(data); }
	inline WriteStream & operator << (unsigned char data) { return writeSimpleData(data); }
	inline WriteStream & operator << (short data) { return writeIntegerData(data); }
	inline WriteStream & operator << (unsigned short data) { return writeIntegerData(data); }
	inline WriteStream & operator << (int data) { return writeIntegerData(data); }
	inline WriteStream & operator << (unsigned int data) { return writeIntegerData(data); }
	inline WriteStream & operator << (long data) { return writeIntegerData((long long)data); }
	inline WriteStream & operator << (unsigned long data) { return writeIntegerData((unsigned long long)data); }
	inline WriteStream & operator << (long long data) { return writeIntegerData(data); }
	inline WriteStream & operator << (unsigned long long data) { return writeIntegerData(data); }
	inline WriteStream & operator << (float data) { return writeIntegerData(data); }
	inline WriteStream & operator << (double data) { return writeIntegerData(data); }

protected:
	//! check move cursor is valid. if invalid then throw exception.
	inline void checkMoveCursor(Integer unit = (Integer)0);

	//! fix pack len.
	inline void fixPackLen();

	//! write integer data with endian type.
	template <class T>
	inline WriteStream & writeIntegerData(T t);

	//! write some types of data with out endian type. It's relative to writeIntegerData method.
	template <class T>
	inline WriteStream & writeSimpleData(T t);
private:

	std::string _data; //! If not attach any memory, class WriteStream will used this to managing memory.
	char * _attachData;//! attach memory pointer
	Integer _maxStreamLen; //! can write max size
	Integer _cursor; //! current move cursor.
	ProtoInteger _pID; //! proto ID
	Integer _headLen;
	bool  _isNoWrite; //! if true then WriteStream will not do any write operation.
};

//////////////////////////////////////////////////////////////////////////
//class ReadStream: De-serialization the specified data from byte stream.
//////////////////////////////////////////////////////////////////////////


class ReadStream
{
public:
	inline ReadStream(const char *attachData, Integer attachDataLen, bool isHaveHeader = true);
	~ReadStream(){}
public:
	//reset cursor
	inline void resetMoveCursor();
	//get protocol id
	inline ProtoInteger getProtoID(){return _pID;}
	//get attach data buff
	inline const char* getStream();
	//get pack length in stream
	inline Integer getStreamLen();

	//get body stream buff, the pointer used by reflecting immediately.
	inline const char* getStreamBody();
	//get body stream length.
	inline Integer getStreamBodyLen();

	//get current unread stream buff, the pointer used by reflecting immediately.
	inline const char* getStreamUnread();
	//get current unread stream buff length
	inline Integer getStreamUnreadLen();


	inline const char * peekOriginalData(Integer unit);
	inline void skipOriginalData(Integer unit);


	inline ReadStream & operator >> (bool & data) { return readSimpleData(data); }
	inline ReadStream & operator >> (char & data) { return readSimpleData(data); }
	inline ReadStream & operator >> (unsigned char & data) { return readSimpleData(data); }
	inline ReadStream & operator >> (short & data) { return readIntegerData(data); }
	inline ReadStream & operator >> (unsigned short & data) { return readIntegerData(data); }
	inline ReadStream & operator >> (int & data) { return readIntegerData(data); }
	inline ReadStream & operator >> (unsigned int & data) { return readIntegerData(data); }
	inline ReadStream & operator >> (long & data){ long long tmp = 0;ReadStream & ret = readIntegerData(tmp);data =(long) tmp;return ret;}
	inline ReadStream & operator >> (unsigned long & data){ unsigned long long tmp = 0;ReadStream & ret = readIntegerData(tmp);data = (unsigned long)tmp;return ret;}
	inline ReadStream & operator >> (long long & data) { return readIntegerData(data); }
	inline ReadStream & operator >> (unsigned long long & data) { return readIntegerData(data); }
	inline ReadStream & operator >> (float & data) { return readIntegerData(data); } 
	inline ReadStream & operator >> (double & data) { return readIntegerData(data); }
protected:
	inline void checkMoveCursor(Integer unit);
	template <class T>
	inline ReadStream & readIntegerData(T & t);
	template <class T>
	inline ReadStream & readSimpleData(T & t);

private:
	const char * _attachData;
	Integer _maxDataLen;
	Integer _cursor;
	ProtoInteger _pID; //! proto ID
	bool _isHaveHeader;
};


//////////////////////////////////////////////////////////////////////////
//! stl container
//////////////////////////////////////////////////////////////////////////

//write c-style string

inline WriteStream & operator << (WriteStream & ws, const char *const data)
{
	Integer len = (Integer)strlen(data);
	ws << len;
	ws.appendOriginalData(data, len);
	return ws;
}

//write std::string
template<class _Traits, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::basic_string<char, _Traits, _Alloc> & data)
{
	Integer len = (Integer)data.length();
	ws << len;
	ws.appendOriginalData(data.c_str(), len);
	return ws;
}
//read std::string
template<class _Traits, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::basic_string<char, _Traits, _Alloc> & data)
{
	Integer len = 0;
	rs >> len;
	data.assign(rs.peekOriginalData(len), len);
	rs.skipOriginalData(len);
	return rs;
}


//std::vector
template<class T, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::vector<T, _Alloc> & vct)
{
	ws << (Integer)vct.size();
	for (typename std::vector<T, _Alloc>::const_iterator iter = vct.begin(); iter != vct.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<typename T, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::vector<T, _Alloc> & vct)
{
	Integer totalCount = 0;
	rs >> totalCount;
	if (totalCount > 0)
	{
		vct.reserve(totalCount);
		for (Integer i = 0; i < totalCount; ++i)
		{
			T t;
			rs >> t;
			vct.push_back(t);
		}
	}
	return rs;
}

//std::set
template<class Key, class _Pr, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::set<Key, _Pr, _Alloc> & k)
{
	ws << (Integer)k.size();
	for (typename std::set<Key, _Pr, _Alloc>::const_iterator iter = k.begin(); iter != k.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class Key, class _Pr, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::set<Key, _Pr, _Alloc> & k)
{
	Integer totalCount = 0;
	rs >> totalCount;
	for (Integer i = 0; i < totalCount; ++i)
	{
		Key t;
		rs >> t;
		k.insert(t);
	}
	return rs;
}

//std::multiset
template<class Key, class _Pr, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::multiset<Key, _Pr, _Alloc> & k)
{
	ws << (Integer)k.size();
	for (typename std::multiset<Key, _Pr, _Alloc>::const_iterator iter = k.begin(); iter != k.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class Key, class _Pr, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::multiset<Key, _Pr, _Alloc> & k)
{
	Integer totalCount = 0;
	rs >> totalCount;
	for (Integer i = 0; i < totalCount; ++i)
	{
		Key t;
		rs >> t;
		k.insert(t);
	}
	return rs;
}

//std::map
template<class Key, class Value, class _Pr, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::map<Key, Value, _Pr, _Alloc> & kv)
{
	ws << (Integer)kv.size();
	for (typename std::map<Key, Value, _Pr, _Alloc>::const_iterator iter = kv.begin(); iter != kv.end(); ++iter)
	{
		ws << iter->first;
		ws << iter->second;
	}
	return ws;
}

template<class Key, class Value, class _Pr, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::map<Key, Value, _Pr, _Alloc> & kv)
{
	Integer totalCount = 0;
	rs >> totalCount;
	for (Integer i = 0; i < totalCount; ++i)
	{
		std::pair<Key, Value> pr;
		rs >> pr.first;
		rs >> pr.second;
		kv.insert(pr);
	}
	return rs;
}

//std::multimap
template<class Key, class Value, class _Pr, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::multimap<Key, Value, _Pr, _Alloc> & kv)
{
	ws << (Integer)kv.size();
	for (typename std::multimap<Key, Value, _Pr, _Alloc>::const_iterator iter = kv.begin(); iter != kv.end(); ++iter)
	{
		ws << iter->first;
		ws << iter->second;
	}
	return ws;
}

template<class Key, class Value, class _Pr, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::multimap<Key, Value, _Pr, _Alloc> & kv)
{
	Integer totalCount = 0;
	rs >> totalCount;
	for (Integer i = 0; i < totalCount; ++i)
	{
		std::pair<Key, Value> pr;
		rs >> pr.first;
		rs >> pr.second;
		kv.insert(pr);
	}
	return rs;
}


//std::list
template<class Value, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::list<Value, _Alloc> & l)
{
	ws << (Integer)l.size();
	for (typename std::list<Value,_Alloc>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class Value, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::list<Value, _Alloc> & l)
{
	Integer totalCount = 0;
	rs >> totalCount;
	for (Integer i = 0; i < totalCount; ++i)
	{
		Value t;
		rs >> t;
		l.push_back(t);
	}
	return rs;
}
//std::deque
template<class Value, class _Alloc>
inline WriteStream & operator << (WriteStream & ws, const std::deque<Value, _Alloc> & l)
{
	ws << (Integer)l.size();
	for (typename std::deque<Value,_Alloc>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
	{
		ws << *iter;
	}
	return ws;
}

template<class Value, class _Alloc>
inline ReadStream & operator >> (ReadStream & rs, std::deque<Value, _Alloc> & l)
{
	Integer totalCount = 0;
	rs >> totalCount;
	for (Integer i = 0; i < totalCount; ++i)
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

inline ZSummer_EndianType __localEndianType()
{
	if (*(const unsigned char *)&__gc_localEndianType == 1)
	{
		return LittleEndian;
	}
	return BigEndian;
}

template<class Integer>
Integer streamToInteger(const char stream[sizeof(Integer)])
{
	if (stream == NULL)
	{
		throw std::runtime_error("streamToInteger stream is NULL");
	}
	
	unsigned short integerLen = sizeof(Integer);
	Integer integer = 0 ;
	if (integerLen == 1)
	{
		integer = (Integer)stream[0];
	}
	else
	{
		if (LittleEndian != __localEndianType())
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

template<class Integer>
void integerToStream(Integer integer, char *stream)
{
	unsigned short integerLen = sizeof(Integer);
	if (integerLen == 1)
	{
		stream[0] = (char)integer;
	}
	else
	{
		if (LittleEndian != __localEndianType())
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



inline std::pair<INTEGRITY_RET_TYPE, Integer> checkBuffIntegrity(const char * buff, Integer curBuffLen, Integer boundLen, Integer maxBuffLen)
{
	if (boundLen < curBuffLen || maxBuffLen < boundLen)
	{
		return std::make_pair(IRT_CORRUPTION, curBuffLen);
	}

	unsigned short headLen = (unsigned short)sizeof(Integer) + (unsigned short)sizeof(ProtoInteger);
	if (curBuffLen < headLen)
	{
		return std::make_pair(IRT_SHORTAGE, headLen - curBuffLen);
	}

	Integer packLen = streamToInteger<Integer>(buff);

	if (packLen > boundLen)
	{
		if (packLen > maxBuffLen)
		{
			return std::make_pair(IRT_CORRUPTION, curBuffLen);
		}
		else
		{
			return std::make_pair(IRT_SHORTAGE, packLen - curBuffLen);
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


inline WriteStream::WriteStream(ProtoInteger pID, char * attachData, Integer maxStreamLen, bool bNoWrite)
{
	_pID = pID;
	_attachData = attachData;
	_maxStreamLen = maxStreamLen;
	_headLen = sizeof(Integer) + sizeof(ProtoInteger);
	_cursor = _headLen;
	_isNoWrite = bNoWrite;
	if (_attachData == NULL || _maxStreamLen < _headLen)
	{
		_attachData = NULL;
		_data.reserve(1200);
		_data.resize(_cursor, '\0');
	}
	if (_maxStreamLen < _headLen || _maxStreamLen > MaxPackLen)
	{
		_maxStreamLen = MaxPackLen;
	}

	//write header
	Integer packLen = _headLen;
	if (_attachData)
	{
		integerToStream<Integer>(packLen, &_attachData[0]);
		integerToStream<ProtoInteger>(pID, &_attachData[sizeof(Integer)]);
	}
	else
	{
		integerToStream<Integer>(packLen, &_data[0]);
		integerToStream<ProtoInteger>(pID, &_data[sizeof(Integer)]);
	}
}



inline void WriteStream::checkMoveCursor(Integer unit)
{
	if (_maxStreamLen < _headLen)
	{
		throw std::runtime_error("construction param error. attach memory size less than mini size.");
	}
	if (_cursor > _maxStreamLen)
	{
		throw std::runtime_error("bound over. cursor in end-of-data.");
	}
	if (unit > _maxStreamLen)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
	if (_maxStreamLen - _cursor < unit)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
}


inline void WriteStream::fixPackLen()
{
	if (_isNoWrite)
	{
		return;
	}
	Integer packLen = _cursor;
	if (_attachData)
	{
		integerToStream<Integer>(packLen, &_attachData[0]);
	}
	else
	{
		integerToStream<Integer>(packLen, &_data[0]);
	}
}




inline char* WriteStream::getStream()
{
	if (_isNoWrite)
	{
		return NULL;
	}
	if (_attachData)
	{
		return _attachData;
	}
	else
	{
		return &_data[0];
	}
	return NULL;
}


inline char* WriteStream::getStreamBody()
{
	if (_isNoWrite)
	{
		return NULL;
	}
	if (_attachData)
	{
		return _attachData + _headLen;
	}
	else
	{
		return &_data[0] + _headLen;
	}
	return NULL;
}


inline WriteStream & WriteStream::appendOriginalData(const void * data, Integer unit)
{
	checkMoveCursor(unit);
	if (!_isNoWrite)
	{
		if (_attachData)
		{
			memcpy(&_attachData[_cursor], data, unit);
		}
		else
		{
			_data.append((const char*)data, unit);
		}
	}
	_cursor += unit;
	fixPackLen();
	return *this;
}
inline WriteStream & WriteStream::fixOriginalData(Integer offset, Integer unit)
{
	if (offset + sizeof(Integer) > _cursor)
	{
		throw std::runtime_error("fixOriginalData over stream.");
	}
	if (_attachData)
	{
		integerToStream<Integer>(unit, &_attachData[offset]);
	}
	else
	{
		integerToStream<Integer>(unit, &_data[offset]);
	}
	return *this;
}
 template <class T> 
inline WriteStream & WriteStream::writeIntegerData(T t)
{
	Integer unit = sizeof(T);
	checkMoveCursor(unit);
	if (!_isNoWrite)
	{
		if (_attachData)
		{
			integerToStream<T>(t, &_attachData[_cursor]);
		}
		else
		{
			_data.append((const char*)&t, unit);
			if (LittleEndian != __localEndianType())
			{
				integerToStream<T>(t, &_data[_cursor]);
			}
		}
	}
	_cursor += unit;
	fixPackLen();
	return * this;
}


 template <class T>
inline WriteStream & WriteStream::writeSimpleData(T t)
{
	Integer unit = sizeof(T);
	checkMoveCursor(unit);
	if (!_isNoWrite)
	{
		if (_attachData)
		{
			memcpy(&_attachData[_cursor], &t, unit);
		}
		else
		{
			_data.append((const char*)&t, unit);
		}
	}

	_cursor += unit;
	fixPackLen();
	return * this;
}






//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////

inline ReadStream::ReadStream(const char *attachData, Integer attachDataLen, bool isHaveHeader)
{
	_attachData = attachData;
	_maxDataLen = attachDataLen;
	_isHaveHeader = isHaveHeader;
	if (_maxDataLen > MaxPackLen)
	{
		_maxDataLen = MaxPackLen;
	}


	if (_isHaveHeader)
	{
		if (_maxDataLen < sizeof(Integer)+sizeof(ProtoInteger))
		{
			_attachData = NULL; //assert
		}

		_cursor = sizeof(Integer) + sizeof(ProtoInteger);
		_pID = streamToInteger<ProtoInteger>(&_attachData[sizeof(Integer)]);
		Integer len = streamToInteger<Integer>(&_attachData[0]);
		if (len < _maxDataLen) // if stream invalid, ReadStream try read data as much as possible.
		{
			_maxDataLen = len;
		}
	}
	else
	{
		_cursor = 0;
		_pID = 0;
	}


	
}

inline void ReadStream::resetMoveCursor()
{
	if (_isHaveHeader)
	{
		_cursor = sizeof(Integer) + sizeof(ProtoInteger);
	}
	else
	{
		_cursor = 0;
	}
}


inline void ReadStream::checkMoveCursor(Integer unit)
{
	if (_cursor > _maxDataLen)
	{
		throw std::runtime_error("bound over. cursor in end-of-data.");
	}
	if (unit > _maxDataLen)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
	if (_maxDataLen - _cursor < unit)
	{
		throw std::runtime_error("bound over. new unit be discarded.");
	}
}



inline const char* ReadStream::getStream()
{
	return _attachData;
}


inline Integer ReadStream::getStreamLen()
{
	return _maxDataLen;
}


inline const char* ReadStream::getStreamBody()
{
	if (_isHaveHeader)
	{
		return _attachData + sizeof(Integer) + sizeof(ProtoInteger);
	}
	return _attachData;
}


inline Integer ReadStream::getStreamBodyLen()
{
	if (_isHaveHeader)
	{
		return getStreamLen() - sizeof(Integer) - sizeof(ProtoInteger);
	}
	return getStreamLen();
}


inline const char* ReadStream::getStreamUnread()
{
	return &_attachData[_cursor];
}


inline Integer ReadStream::getStreamUnreadLen()
{
	return getStreamLen()  - _cursor;
}

 template <class T>
inline ReadStream & ReadStream::readIntegerData(T & t)
{
	Integer unit = sizeof(T);
	checkMoveCursor(unit);
	t = streamToInteger<T>(&_attachData[_cursor]);
	_cursor += unit;
	return * this;
}
 template <class T>
inline ReadStream & ReadStream::readSimpleData(T & t)
{
	Integer unit = sizeof(T);
	checkMoveCursor(unit);
	memcpy(&t, &_attachData[_cursor], unit);
	_cursor += unit;
	return * this;
}

inline const char * ReadStream::peekOriginalData(Integer unit)
{
	checkMoveCursor(unit);
	return &_attachData[_cursor];
}

inline void ReadStream::skipOriginalData(Integer unit)
{
	checkMoveCursor(unit);
	_cursor += unit;
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

inline INTEGRITY_RET_TYPE checkHTTPBuffIntegrity(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen, 
							bool hadHeader, bool & isChunked, PairString& commonLine, HTTPHeadMap & head, std::string & body, unsigned int &usedCount);

std::string urlEncode(const std::string& orgString);
std::string urlDecode(const std::string& orgString);
class WriteHTTP
{
public:
	const char * getStream(){ return _buff.c_str();}
	unsigned int getStreamLen() { return (unsigned int)_buff.length();}
	void addHead(std::string key, std::string val)
	{
		_head.insert(std::make_pair(key, val));
	}
	void post(std::string uri, std::string content)
	{
		char buf[100];
		sprintf(buf, "%u", (unsigned int)content.length());
		_head.insert(std::make_pair("Content-Length", buf));
		_buff.append("POST " + uri + " HTTP/1.1" + CRLF);
		writeGeneralHead();
		_buff.append(CRLF);
		_buff.append(content);
	}
	void get(std::string uri)
	{
		_head.insert(std::make_pair("Content-Length", "0"));
		_buff.append("GET " + uri + " HTTP/1.1" + CRLF);
		writeGeneralHead();
		_buff.append(CRLF);
	}
	void response(std::string statusCode, std::string content)
	{
		char buf[100];
		sprintf(buf, "%u", (unsigned int)content.length());
		_head.insert(std::make_pair("Content-Length", buf));
		_buff.append("HTTP/1.1 " + statusCode + " ^o^" + CRLF);
		writeGeneralHead();
		_buff.append(CRLF);
		_buff.append(content);
	}
protected:
	void writeGeneralHead()
	{
		for (HTTPHeadMap::iterator iter = _head.begin(); iter != _head.end(); ++iter)
		{
			_buff.append(iter->first + ":" + iter->second + CRLF);
		}
	}
private:
	HTTPHeadMap _head;
	std::string _buff;
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

inline INTEGRITY_RET_TYPE checkHTTPBuffIntegrity(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen,
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
