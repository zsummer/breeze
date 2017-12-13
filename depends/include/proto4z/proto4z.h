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
 * Copyright (C) 2013-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
 * AUTHORS:  YaweiZhang <yawei.zhang@foxmail.com>
 * VERSION:  1.0
 * PURPOSE:  A lightweight library for process protocol .
 * CREATION: 2013.07.04
 * LCHANGE:  2017.09.18
 * LICENSE:  Expat/MIT License, See Copyright Notice at the begin of this file.
 */

/*
 * mail: yawei.zhang@foxmail.com
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
#include <sstream>
#include <algorithm>
#include <type_traits>
#ifndef WIN32
#include <stdexcept>
#include <unistd.h>
#include <execinfo.h>
#else
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#define WIN32_LEAN_AND_MEAN
#include <exception>
#include <windows.h>
#pragma warning(push)
#pragma warning(disable : 4091)
#include <DbgHelp.h>
#pragma warning(pop)
#pragma comment(lib, "Dbghelp")
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



inline std::string proto4z_traceback();

#define PROTO4Z_THROW(log)\
do{\
    std::stringstream ss; \
    ss << log << " throw by " << __FILE__ << ":" << __LINE__  << " ==> " << proto4z_traceback() << "\r\n"; \
    throw std::runtime_error(ss.str()); \
} while (0)



//////////////////////////////////////////////////////////////////////////
//! protocol traits instruction
//////////////////////////////////////////////////////////////////////////

// Memory layout
//|----------  header  ---------|-------  body  --------|
//|--packlen-|-reserve-protoID--|-------  body  --------|

//header
typedef unsigned int Integer;
typedef unsigned short ReserveInteger;
typedef unsigned short ProtoInteger;
//header end.


const static Integer MaxPackLen = (Integer)(-1) > 1024 * 1024 ? 1024 * 1024 : (Integer)-1;

//stream translate to Integer with endian type.
template<class BaseType>
typename std::enable_if<true, BaseType>::type streamToBaseType(const char stream[sizeof(BaseType)]);
template<class T>
void baseTypeToStream(char *stream, T v);



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

template<class T>
class TLSQueue
{
public:
    TLSQueue()
    {
    }
    ~TLSQueue()
    {
        while (!_que.empty())
        {
            T * ptr = _que.back();
            _que.pop_back();
            delete ptr;
        }
    }
    inline T * pop()
    {
        if (!_que.empty())
        {
            T * ptr = _que.back();
            _que.pop_back();
            return ptr;
        }
        return new T();
    }
    inline void push(T * ptr)
    {
        _que.push_back(ptr);
    }
protected:
private:
    std::vector<T*> _que;
};

//////////////////////////////////////////////////////////////////////////
//! class WriteStreamImpl: serializes the specified data to byte stream.
//////////////////////////////////////////////////////////////////////////
//StreamHeadTrait: User-Defined like DefaultStreamHeadTrait

template<class T = std::string>
class WriteStreamImpl
{
private:
    thread_local static TLSQueue<T> _tlsque;
public:
    //! testStream : if true then WriteStreamImpl will not do any write operation.
    //! attach : the existing memory.
    WriteStreamImpl(ProtoInteger pID);
    ~WriteStreamImpl();
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
    inline WriteStreamImpl & appendOriginalData(const void * data, Integer len);
    template<class U>
    inline WriteStreamImpl & fixOriginalData(Integer offset, U unit);
    inline WriteStreamImpl & fixOriginalData(Integer offset, const void * data, Integer len);


    inline WriteStreamImpl & setReserve(ReserveInteger n);

    template<class U>
    inline typename std::enable_if<std::is_arithmetic<U>::value, WriteStreamImpl>::type & operator << (U data)
    {
        checkMoveCursor(sizeof(U));
        _attach->append((const char*)&data, sizeof(U));
        _cursor += sizeof(U);
        baseTypeToStream(&(*_attach)[0], _cursor);
        return *this;
    }


protected:
    //! check move cursor is valid. if invalid then throw exception.
    inline void checkMoveCursor(Integer unit = (Integer)0);


private:

    T * _attach; //! If not attach any memory, class WriteStreamImpl will used this to managing memory.
    Integer _attachLen; //! can write max size
    Integer _cursor; //! current move cursor.
    ReserveInteger _reserve;
    ProtoInteger _pID; //! proto ID
    Integer _headLen;
};
//http://zh.cppreference.com/w/cpp/language/storage_duration 
template<class T>
thread_local  TLSQueue<T> WriteStreamImpl<T>::_tlsque;

//////////////////////////////////////////////////////////////////////////
//class ReadStream: De-serialization the specified data from byte stream.
//////////////////////////////////////////////////////////////////////////


class ReadStream
{
public:
    inline ReadStream(const char *attach, Integer attachLen, bool isHaveHeader = true);
    ~ReadStream(){}
public:
    //reset cursor
    inline void resetMoveCursor();
    //get protocol id
    inline ProtoInteger getProtoID(){ return _pID; }
    //get reserve id
    inline ReserveInteger getReserve(){ return _reserve; }
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

    template <class T>
    inline typename std::enable_if<std::is_arithmetic<T>::value, ReadStream>::type & 
        operator >> (T & data)
    {
        checkMoveCursor(sizeof(T));
        memcpy(&data, &_attach[_cursor], sizeof(T));
        _cursor += sizeof(T);
        return *this;
    }
   
protected:
    inline void checkMoveCursor(Integer unit);


private:
    const char * _attach;
    Integer _attachLen;
    Integer _cursor;
    ReserveInteger _reserve;
    ProtoInteger _pID; //! proto ID
    bool _isHaveHeader;
};


//////////////////////////////////////////////////////////////////////////
//! stl container
//////////////////////////////////////////////////////////////////////////

//write c-style string
template<class T>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const char *const data)
{
    Integer len = (Integer)strlen(data);
    ws << len;
    ws.appendOriginalData(data, len);
    return ws;
}

//write std::string
template<class T, class _Traits, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::basic_string<char, _Traits, _Alloc> & data)
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
template<class T, class U, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::vector<U, _Alloc> & vct)
{
    ws << (Integer)vct.size();
    for (typename std::vector<U, _Alloc>::const_iterator iter = vct.begin(); iter != vct.end(); ++iter)
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
        T t;
        vct.clear();
        vct.reserve(totalCount > 100 ? 100 : totalCount);
        for (Integer i = 0; i < totalCount; ++i)
        {
            rs >> t;
            vct.push_back(t);
        }
    }
    return rs;
}

//std::set
template<class T, class Key, class _Pr, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::set<Key, _Pr, _Alloc> & k)
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
    Key t;
    k.clear();
    for (Integer i = 0; i < totalCount; ++i)
    {
        rs >> t;
        k.insert(t);
    }
    return rs;
}

//std::multiset
template<class T, class Key, class _Pr, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::multiset<Key, _Pr, _Alloc> & k)
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
    Key t;
    k.clear();
    for (Integer i = 0; i < totalCount; ++i)
    {
        rs >> t;
        k.insert(t);
    }
    return rs;
}

//std::map
template<class T, class Key, class Value, class _Pr, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::map<Key, Value, _Pr, _Alloc> & kv)
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
    std::pair<Key, Value> pr;
    kv.clear();
    for (Integer i = 0; i < totalCount; ++i)
    {
        rs >> pr.first;
        rs >> pr.second;
        kv.insert(pr);
    }
    return rs;
}

//std::multimap
template<class T, class Key, class Value, class _Pr, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::multimap<Key, Value, _Pr, _Alloc> & kv)
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
    std::pair<Key, Value> pr;
    kv.clear();
    for (Integer i = 0; i < totalCount; ++i)
    {
        rs >> pr.first;
        rs >> pr.second;
        kv.insert(pr);
    }
    return rs;
}


//std::list
template<class T, class Value, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::list<Value, _Alloc> & l)
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
    Value t;
    l.clear();
    for (Integer i = 0; i < totalCount; ++i)
    {
        rs >> t;
        l.push_back(t);
    }
    return rs;
}
//std::deque
template<class T, class Value, class _Alloc>
inline WriteStreamImpl<T> & operator << (WriteStreamImpl<T> & ws, const std::deque<Value, _Alloc> & l)
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
    Value t;
    l.clear();
    for (Integer i = 0; i < totalCount; ++i)
    {
        rs >> t;
        l.push_back(t);
    }
    return rs;
}



//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////




template<class BaseType>
typename std::enable_if<true, BaseType>::type streamToBaseType(const char stream[sizeof(BaseType)])
{
    BaseType v = 0;
    memcpy(&v, stream, sizeof(BaseType));
    return v;
}

template<class T>
void baseTypeToStream(char *stream, T v)
{
    memcpy(stream, &v, sizeof(T));
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

    Integer packLen = streamToBaseType<Integer>(buff);
    if (packLen < headLen)
    {
        return std::make_pair(IRT_CORRUPTION, curBuffLen);
    }
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

template<class T>
WriteStreamImpl<T>::WriteStreamImpl(ProtoInteger pID)
{
    _reserve = 0;
    _pID = pID;
    _headLen = sizeof(Integer)+ sizeof(ReserveInteger) + sizeof(ProtoInteger);
    _cursor = _headLen;
    _attach = _tlsque.pop();
    _attach->reserve(1200);
    _attach->resize(_cursor, '\0');
    _attachLen = MaxPackLen;

    baseTypeToStream(&(*_attach)[0], _headLen);
    baseTypeToStream(&(*_attach)[0] + sizeof(Integer), _reserve);
    baseTypeToStream(&(*_attach)[0] + sizeof(Integer) + sizeof(ReserveInteger), pID);

}

template<class T>
WriteStreamImpl<T>::~WriteStreamImpl()
{
    _tlsque.push(_attach);
}


template<class T>
inline void WriteStreamImpl<T>::checkMoveCursor(Integer unit)
{
    if (_cursor > _attachLen)
    {
        PROTO4Z_THROW("bound over. cursor in end-of-data. _attachLen=" << _attachLen << ", _cursor=" << _cursor);
    }
    if (unit > _attachLen)
    {
        PROTO4Z_THROW("bound over. new unit be discarded. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", unit=" << unit);
    }
    if (_attachLen - _cursor < unit)
    {
        PROTO4Z_THROW("bound over. new unit be discarded. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", unit=" << unit);
    }
}


template<class T>
inline char* WriteStreamImpl<T>::getStream()
{
    return &(*_attach)[0];
}

template<class T>
inline char* WriteStreamImpl<T>::getStreamBody()
{
    return &(*_attach)[0] + _headLen;
}

template<class T>
inline WriteStreamImpl<T> & WriteStreamImpl<T>::appendOriginalData(const void * data, Integer len)
{
    checkMoveCursor(len);
    T & attach = *_attach;
    attach.append((const char*)data, len);
    _cursor += len;
    baseTypeToStream(&attach[0], _cursor);
    return *this;
}

template<class T>
template<class U>
inline WriteStreamImpl<T> & WriteStreamImpl<T>::fixOriginalData(Integer offset, U unit)
{
    if (offset + sizeof(unit) > _cursor)
    {
        PROTO4Z_THROW("fixOriginalData over stream. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", unit=" << unit << ", offset=" << offset);
    }
    baseTypeToStream(&(*_attach)[offset], unit);
    return *this;
}

template<class T>
inline WriteStreamImpl<T> & WriteStreamImpl<T>::fixOriginalData(Integer offset, const void * data, Integer len)
{
    if (offset + len > _cursor)
    {
        PROTO4Z_THROW("fixOriginalData over stream. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", data len=" << len << ", offset=" << offset);
    }
    memcpy(&(*_attach)[offset], data, len);
    return *this;
}

template<class T>
inline WriteStreamImpl<T> & WriteStreamImpl<T>::setReserve(ReserveInteger n)
{
    baseTypeToStream(&(*_attach)[sizeof(Integer)], n);
    return *this;
}








//////////////////////////////////////////////////////////////////////////
//! implement 
//////////////////////////////////////////////////////////////////////////

inline ReadStream::ReadStream(const char *attach, Integer attachLen, bool isHaveHeader)
{
    _attach = attach;
    _attachLen = attachLen;
    _isHaveHeader = isHaveHeader;
    if (_attachLen > MaxPackLen)
    {
        _attachLen = MaxPackLen;
    }


    if (_isHaveHeader)
    {
        if (_attachLen < sizeof(Integer) + sizeof(ReserveInteger) + sizeof(ProtoInteger))
        {
            PROTO4Z_THROW("ReadStream attach buff less then head len. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", _isHaveHeader=" << _isHaveHeader );
        }

        _cursor = sizeof(Integer) + sizeof(ReserveInteger) + sizeof(ProtoInteger);
        Integer len = streamToBaseType<Integer>(&_attach[0]);
        _reserve = streamToBaseType<ReserveInteger>(&_attach[sizeof(Integer)]);
        _pID = streamToBaseType<ProtoInteger>(&_attach[sizeof(Integer) + sizeof(ReserveInteger)]);
        if (len < _attachLen) // if stream invalid, ReadStream try read data as much as possible.
        {
            _attachLen = len;
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
        _cursor = sizeof(Integer) + sizeof(ReserveInteger) + sizeof(ProtoInteger);
    }
    else
    {
        _cursor = 0;
    }
}


inline void ReadStream::checkMoveCursor(Integer unit)
{
    if (_cursor > _attachLen)
    {
        PROTO4Z_THROW("bound over. cursor in end-of-data. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", _isHaveHeader=" << _isHaveHeader);
    }
    if (unit > _attachLen)
    {
        PROTO4Z_THROW("bound over. new unit be discarded. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", _isHaveHeader=" << _isHaveHeader);
    }
    if (_attachLen - _cursor < unit)
    {
        PROTO4Z_THROW("bound over. new unit be discarded. _attachLen=" << _attachLen << ", _cursor=" << _cursor << ", _isHaveHeader=" << _isHaveHeader);
    }
}



inline const char* ReadStream::getStream()
{
    return _attach;
}


inline Integer ReadStream::getStreamLen()
{
    return _attachLen;
}


inline const char* ReadStream::getStreamBody()
{
    if (_isHaveHeader)
    {
        return _attach + sizeof(Integer) + sizeof(ReserveInteger) + sizeof(ProtoInteger);
    }
    return _attach;
}


inline Integer ReadStream::getStreamBodyLen()
{
    if (_isHaveHeader)
    {
        return getStreamLen() - sizeof(Integer) - sizeof(ReserveInteger) - sizeof(ProtoInteger);
    }
    return getStreamLen();
}


inline const char* ReadStream::getStreamUnread()
{
    return &_attach[_cursor];
}


inline Integer ReadStream::getStreamUnreadLen()
{
    return getStreamLen()  - _cursor;
}



inline const char * ReadStream::peekOriginalData(Integer unit)
{
    checkMoveCursor(unit);
    return &_attach[_cursor];
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


inline std::pair<INTEGRITY_RET_TYPE, unsigned int> checkHTTPBuffIntegrity(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen,
                            bool & isChunked, std::string & method, std::string & line, std::map<std::string,std::string> & head, std::string & body);

std::string urlEncode(const std::string& orgString);
//"Content-Type" value is "application/x-www-form-urlencoded" means that your POST body will need to be URL encoded just like a GET parameter string.  
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
        if (_head.find("Connection") == _head.end())
        {
            _head.insert(std::make_pair("Connection", " keep-alive"));
        }
        if (_head.find("User-Agent") == _head.end())
        {
            _head.insert(std::make_pair("User-Agent", " Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) proto4z"));
        }
        writeGeneralHead();
        _buff.append(CRLF);
        _buff.append(content);
    }
    void get(std::string uri)
    {
        _head.insert(std::make_pair("Content-Length", "0"));
        _buff.append("GET " + uri + " HTTP/1.1" + CRLF);
        if (_head.find("Connection") == _head.end())
        {
            _head.insert(std::make_pair("Connection", " keep-alive"));
        }
        if (_head.find("User-Agent") == _head.end())
        {
            _head.insert(std::make_pair("User-Agent", " Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) proto4z"));
        }
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

        if (_head.find("Accept") == _head.end())
        {
            _head.insert(std::make_pair("Accept", " */*"));
        }

        if (_head.find("Accept-Languaget") == _head.end())
        {
            _head.insert(std::make_pair("Accept-Languaget", " zh-CN,zh;q=0.8"));
        }
        if (_head.find("Content-Type") == _head.end())
        {
            _head.insert(std::make_pair("Content-Type", " text/html; charset=utf-8"));
        }     

        for (auto iter = _head.begin(); iter != _head.end(); ++iter)
        {
            _buff.append(iter->first + ":" + iter->second + CRLF);
        }

    }
private:
    std::map<std::string, std::string> _head;
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
                    readStatus ++;
                    cursor++;
                    continue;
                }
            }
            else // ! isCommondLine
            {
                if (buff[cursor] == SEGM)
                {
                    readStatus ++;
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

inline std::pair<INTEGRITY_RET_TYPE, unsigned int> checkHTTPBuffIntegrity(const char * buff, unsigned int curBuffLen, unsigned int maxBuffLen,
    bool & isChunked, std::string & method, std::string & line, std::map<std::string, std::string> & head, std::string & body)
{
    if (head.empty())
    {
        isChunked = false;
    }
    int bodyLenght = -1;
    unsigned int usedCount = 0;


    //extract head
    if (!isChunked)
    {

        //extract common line
        try
        {
            usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, true, true, method, line);
        }
        catch (INTEGRITY_RET_TYPE t)
        {
            return std::make_pair(t, usedCount);
        }

        //extract head line
        head.clear();
        try
        {
            std::string tmpMethod;
            std::string tmpLine;
            do
            {
                tmpMethod.clear();
                tmpLine.clear();
                usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, true, false, tmpMethod, tmpLine);
                if (tmpMethod.empty() && tmpLine.empty())
                {
                    break;
                }
                if (tmpMethod == "Content-Length")
                {
                    bodyLenght = atoi(tmpLine.c_str());
                }
                else if (tmpMethod == "Transfer-Encoding")
                {
                    isChunked = true;
                }
                head.insert(std::make_pair(std::move(tmpMethod), std::move(tmpLine)));
            } while (true);
        }
        catch (INTEGRITY_RET_TYPE t)
        {
            return std::make_pair(t, 0);
        }
    }
    


    //read chunked header
    if (isChunked)
    {
        try
        {
            std::string tmpMethod;
            std::string tmpLine;
            usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, false, false, tmpMethod, tmpLine);
            //chunked end. need closed.
            if (tmpMethod.empty())
            {
                return std::make_pair(IRT_CORRUPTION, 0);
            }
            sscanf(tmpMethod.c_str(), "%x", &bodyLenght);
            if (bodyLenght == 0)
            {
                //http socket end.
                return std::make_pair(IRT_CORRUPTION, 0);
            }
            
        }
        catch (INTEGRITY_RET_TYPE t)
        {
            return std::make_pair(t, 0);
        }
    }
    else if (head.empty())
    {
        return std::make_pair(IRT_SHORTAGE, 0);
    }
    else if (method == "GET")
    {
        return std::make_pair(IRT_SUCCESS, usedCount);
    }
    
    if (bodyLenght == -1 || usedCount + bodyLenght > maxBuffLen)
    {
        return std::make_pair(IRT_CORRUPTION, 0);
    }
    if (bodyLenght + usedCount > curBuffLen)
    {
        return std::make_pair(IRT_SHORTAGE, 0);
    }
    body.assign(buff + usedCount, bodyLenght);
    usedCount += bodyLenght;

    if (isChunked)//clean chunked end CRLF
    {
        try
        {
            std::string tmpMethod;
            std::string tmpLine;
            usedCount += InnerReadLine(buff + usedCount, curBuffLen - usedCount, maxBuffLen - usedCount, false, false, tmpMethod, tmpLine);
            //chunked end. need closed.
            if (!tmpMethod.empty())
            {
                return std::make_pair(IRT_CORRUPTION, 0);
            }
        }
        catch (INTEGRITY_RET_TYPE t)
        {
            return std::make_pair(t, 0);
        }
    }
    

    return std::make_pair(IRT_SUCCESS, usedCount);
}




inline std::string proto4z_traceback()
{
    std::stringstream ss;
#ifdef WIN32
    ss << "\r\n";
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
	SymInitialize(GetCurrentProcess(), NULL, TRUE);

    //     typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
    //     CaptureStackBackTraceType capture = (CaptureStackBackTraceType)(GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlCaptureStackBackTrace"));
    //     if (capture == NULL) return;
    const int stackMax = 128;
    void* trace[stackMax];
    //    int count = (capture)(0, stackMax, trace, NULL);
    int count = (CaptureStackBackTrace)(0, stackMax, trace, NULL);
    for (int i = 1; i < count; i++)
    {
        ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
        PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
        pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymbol->MaxNameLen = MAX_SYM_NAME;
        DWORD64 dwDisplacement = 0;
        if (SymFromAddr(GetCurrentProcess(), (DWORD64)trace[i], &dwDisplacement, pSymbol))
        {
            ss << "bt[" << i - 1 << "]       --[ " << pSymbol->Name << " ]--              from     ";
        }
        else
        {
            ss << "bt[" << i - 1 << "]   " << "error[" << GetLastError() << "]              from     ";
        }

        IMAGEHLP_LINE64 lineInfo = { sizeof(IMAGEHLP_LINE64) };
        DWORD dwLineDisplacement;
        if (SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)trace[i], &dwLineDisplacement, &lineInfo))
        {
            std::string pathfile = lineInfo.FileName;
            if (pathfile.empty())
            {
                ss << "\r\n";
                continue;
            }
            std::for_each(pathfile.begin(), pathfile.end(), [](char &ch) { if (ch == '/') ch = '\\'; });
            auto pos = pathfile.find_last_of('\\');
            if (pos != std::string::npos) pathfile[pos] = '/';
            pos = pathfile.find_last_of('\\');
            if (pos != std::string::npos) pathfile[pos] = '/'; else pos = -1;
            ss << pathfile.substr(pos + 1) << ":" << lineInfo.LineNumber;
        }
        else
        {
            ss << "------:0";
        }
        ss << "\r\n";
        if (strcmp(pSymbol->Name, "main") == 0) break;
    }
#else
    void *stack[200];
    size_t size = backtrace(stack, 200);
    char **stackSymbol = backtrace_symbols(stack, size);
    ss << "backtrace: ";
    for (size_t i = 1; i < size; i++)
    {
        ss << stack[i] << "  ";
    }
    ss << "\r\n";
    for (size_t i = 1; i < size && stackSymbol ; i++)
    {
        if (stackSymbol[i] && strlen(stackSymbol[i]) > 0)
        {
            ss << "bt[" << i - 1 << "] " << stackSymbol[i] << "\r\n";
        }
    }
    free(stackSymbol);
#endif
    return ss.str();
}


using WriteStream = WriteStreamImpl<std::string>;




#ifndef _ZSUMMER_END
#define _ZSUMMER_END }
#endif  
#ifndef _ZSUMMER_PROTO4Z_END
#define _ZSUMMER_PROTO4Z_END }
#endif

_ZSUMMER_PROTO4Z_END
_ZSUMMER_END

#endif
