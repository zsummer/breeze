

/*
* breeze License
* Copyright (C) 2016 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#pragma once
#ifndef _UTLS_IMPL_H_
#define _UTLS_IMPL_H_


inline void trimImpl(const char * buf, size_t len, const char ign, size_t & offset, size_t & outLen, int flag)
{
    const char * begin = buf;
    const char * end = begin + len;
    if (flag == 0 || flag == 1)
    {
        while (begin != end && *begin == ign) ++begin;
    }
    if (flag == 0 || flag == 2)
    {
        while (begin != end && *(end - 1) == ign) --end;
    }
    offset = begin - buf;
    outLen = end - begin;
}


template<class T>
typename std::enable_if<std::is_unsigned<T>::value && !std::is_floating_point<T>::value, T>::type
lutToString(char *buf, size_t len, size_t base, size_t fixed0, size_t &offset, size_t & outLen,  T t)
{
    const T tbase = (T)base;
    char * begin = buf;
    char * end = buf + len;
    *--end = '\0';
    do 
    {
        *--end = "0123456789abcdef"[t % tbase];
        t /= tbase;
        if (t == 0) break;
    } while (true);
    
    while (begin + len - 1 - end < (long long)fixed0)
    {
        *--end = '0';
    }

    offset = end - begin;
    outLen = begin + len - 1 - end;
    return t;
}


template<class T>
typename std::enable_if<std::is_signed<T>::value && ! std::is_floating_point<T>::value, T>::type
lutToString(char *buf, size_t len, size_t base, size_t fixed0, size_t &offset, size_t & outLen, T t)
{
    const T tbase = (T)base;
    char * begin = buf;
    char * end = buf + len;
    *--end = '\0';
    *--end = "0123456789abcdef"[abs(t % tbase)];
    
    if (t < (T)0)
    {
        t = -(t / tbase);

        while (t != 0)
        {
            *--end = "0123456789abcdef"[t % tbase];
            t /= tbase;
        } 
        while (begin + len - 1 - end < (long long)fixed0)
        {
            *--end = '0';
        }
        *--end = '-';
    }
    else
    {
        t = (t / tbase);
        while (t != 0)
        {
            *--end = "0123456789abcdef"[t % tbase];
            t /= tbase;
        }

        while (begin + len - 1 - end < (long long)fixed0)
        {
            *--end = '0';
        }
    }

    offset = end - begin;
    outLen = begin + len - 1 - end;
    return t;
}


inline void floatToString(char *buf, size_t len, size_t frac, size_t &offset, size_t & outLen, double t)
{

    switch (std::fpclassify(t)) 
    {
    case FP_INFINITE:
    {
        memcpy(buf, "inf", 4);
        offset = 0;
        outLen = 3;
        return ;
    }
    case FP_NAN:
    {
        memcpy(buf, "nan", 4);
        offset = 0;
        outLen = 3;
        return;
    }
    case FP_NORMAL:
        break;
    case FP_SUBNORMAL:
    case FP_ZERO:
    {
        buf[0] = '0';
        buf[1] = '\0';
        offset = 0;
        outLen = 1;
        return;
    }
    default:
        memcpy(buf, "undefined", sizeof("undefined"));
        offset = 0;
        outLen = sizeof("undefined") - 1;
        return;
    }


    double sign = std::fabs(t);
    if (sign > 0 && sign <= 0xFFFFFFFFFFFFF)
    {
        double f;
        double x;
        f = std::modf(t, &x);
        lutToString<long long>(buf, len / 2, 10, 0, offset, outLen, (long long)x);
        frac = frac > 16 ? 16 : frac;
        frac = frac > outLen ? frac - outLen : 0;
        if (frac > 0)
        {
            f = std::fabs(f);
            if (true)
            {
                size_t frac2 = frac;
                unsigned long long pw = 1;
                while (frac2 != 0)
                {
                    if (frac2 >= 10)
                    {
                        pw *= 10000000000;
                        frac2 -= 10;
                    }
                    else if (frac2 >= 5)
                    {
                        pw *= 100000;
                        frac2 -= 5;
                    }
                    else if (frac2 >= 2)
                    {
                        pw *= 100;
                        frac2 -= 2;
                    }
                    else
                    {
                        pw *= 10;
                        frac2 -= 1;
                    }
                }
                f *= pw;
            }
            long long llf = (long long)f;
            if (llf > 0)
            {
                char * begin = buf + offset;
                char * end = buf + offset + outLen;
                *end++ = '.';

                lutToString<long long>(end, len / 2 - 1, 10, frac, offset, outLen, llf);

                char * fbegin = end + offset;
                char * fend = fbegin + outLen;
                while (fbegin != fend && *(fend - 1) == '0')
                {
                    --fend;
                }

                memmove(end, fbegin, fend - fbegin);
                offset = begin - buf;
                outLen = (fend - fbegin) + end - begin;
            }

        }
    }
    else
    {
        char * ret = gcvt(t, (int)frac, buf);
        offset = ret - buf;
        outLen = strlen(ret);
        if (outLen > 0 && buf[offset + outLen - 1] == '.')
        {
            buf[offset + outLen - 1] = '\0';
            outLen--;
        }
    }
}




template<class T>
typename std::enable_if<std::is_same<T, bool>::value, std::string>::type
toString(const T &t)
{
    return t ? "1" : "0";
}

template<class T>
typename std::enable_if<std::is_same<T, char>::value, std::string>::type
toString(const T &t)
{
    return std::string(1, t);
}

template<class T>
typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value && !std::is_same<T, char>::value, std::string>::type
toString(const T &t)
{
    char buf[80];
    size_t offset = 0;
    size_t len = 0;
    lutToString<T>(buf, 80, 10, 0, offset, len, t);
    return std::string(buf+offset, len);
}


template<class T>
typename std::enable_if<std::is_floating_point<T>::value, std::string>::type 
toString(const T &t)
{
    char buf[80];
    size_t offset = 0;
    size_t outLen = 0;
    floatToString(buf, 80, sizeof(T) == 4 ? 6 : 15, offset, outLen, (double)t);
    return std::string(buf + offset, outLen);
}


template<class T>
typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type 
toString(const T & t)
{
    return t;
}

template<class T>
typename std::enable_if<std::is_same<T, char>::value, std::string>::type
toString(const T * t)
{
    return std::string(t);
}


template<class To>
typename std::enable_if<std::is_signed<To>::value && !std::is_same<To, bool>::value && !std::is_same<To, char>::value && !std::is_floating_point<To>::value, To > ::type
fromString(const char * buf, size_t len)
{
    const char * begin = buf;
    const char * end = buf + len;
    const char * next = begin;

    while (next != end &&
        ((*begin >= '0' && *begin <= '9') || (*begin == '-') || (*begin == '+')))
    {
        ++next;
    }

    if (begin == next)
    {
        return (To)0;
    }
    char buff[80];
    if (begin - next > 80 - 1)
    {
        next = begin + 80 - 1;
    }
    memcpy(buff, begin, next - begin);
    buff[next - begin] = '\0';

    
    return (To)strtoll(begin, NULL, 10);
}

template<class To>
typename std::enable_if<std::is_unsigned<To>::value && ! std::is_same<To, bool>::value, To > ::type 
fromString(const char * buf, size_t len)
{
    const char * begin = buf;
    const char * end = buf + len;
    const char * next = begin;
    while (next != end &&
        ((*begin >= '0' && *begin <= '9') || (*begin == '-') || (*begin == '+')))
    {
        ++next;
    }

    if (begin == next)
    {
        return (To)0;
    }
    char buff[80];
    if (begin - next > 80 - 1)
    {
        next = begin + 80 - 1;
    }
    memcpy(buff, begin, next - begin);
    buff[next - begin] = '\0';

    return (To)strtoull(begin, NULL, 10);
}

template<class To>
typename std::enable_if<std::is_floating_point<To>::value, To > ::type 
fromString(const char * buf, size_t len)
{
    size_t offset = 0;
    size_t outlen = 0;
    trim(buf, len, ' ', offset, outlen);
    const char * begin = buf + offset;
    const char * end = begin + outlen;


    if (end - begin >= 3)
    {
        if ((begin[0] == 'i' || begin[0] == 'I') && (begin[1] == 'n' || begin[1] == 'N') && (begin[2] == 'f' || begin[2] == 'F') )
        {
            return (To)(1e300*1e300);
        }
        if ((begin[0] == 'n' || begin[0] == 'N') && (begin[1] == 'a' || begin[1] == 'A') && (begin[2] == 'n' || begin[2] == 'N'))
        {
            return (To)(((To)(1e300*1e300))*0.0);
        }
    }

    const char * next = begin;
    while (next != end &&
        ((*begin >= '0' && *begin <= '9') || (*begin == 'e' || *begin == 'E') || (*begin == '.') || (*begin == '-') || (*begin == '+')))
    {
        ++next;
    }

    if (begin == next)
    {
        return (To)0;
    }
    char buff[80];
    if (begin - next > 80 -1)
    {
        next = begin + 80 - 1;
    }
    memcpy(buff, begin, next - begin);
    buff[next - begin] = '\0';

    return (To)strtod(buff, NULL);
}


template<class To>
typename std::enable_if<std::is_same<To, std::string>::value, To > ::type 
fromString(const char * buf, size_t len)
{
    return std::string(buf, len);
}

template<class To>
typename std::enable_if<std::is_same<To, char>::value, To > ::type
fromString(const char * buf, size_t len)
{
    return buf[0];
}
template<class To>
typename std::enable_if<std::is_same<To, bool>::value, To > ::type
fromString(const char * buf, size_t len)
{
    size_t offset = 0;
    size_t outlen = 0;
    trim(buf, len, ' ', offset, outlen);
    if (outlen == 0)
    {
        return false;
    }
    if ((outlen == 5 && memcmp(buf, "false", 5) == 0) || buf[0] == '0')
    {
        return false;
    }
    return true;
}













template<class To>
typename std::enable_if<std::is_signed<To>::value && !std::is_same<To, bool>::value && !std::is_same<To, char>::value && !std::is_floating_point<To>::value, To > ::type
fromString(const std::string & str)
{
    return fromString<To>(str.c_str(), str.length());
}

template<class To>
typename std::enable_if<std::is_unsigned<To>::value && ! std::is_same<To, bool>::value, To > ::type
fromString(const std::string & str)
{
    return fromString<To>(str.c_str(), str.length());
}

template<class To>
typename std::enable_if<std::is_floating_point<To>::value, To > ::type
fromString(const std::string & str)
{
    return fromString<To>(str.c_str(), str.length());
}


template<class To>
typename std::enable_if<std::is_same<To, std::string>::value, To > ::type
fromString(const std::string & str)
{
    return str;
}

template<class To>
typename std::enable_if<std::is_same<To, char>::value, To > ::type
fromString(const std::string & str)
{
    return fromString<To>(str.c_str(), str.length());
}
template<class To>
typename std::enable_if<std::is_same<To, bool>::value, To > ::type
fromString(const std::string & str)
{
    return fromString<To>(str.c_str(), str.length());
}





/*

template<class To>
typename std::enable_if<std::is_signed<To>::value && !std::is_same<To, bool>::value && !std::is_same<To, char>::value && !std::is_floating_point<To>::value, To > ::type
fromString(const char * str)
{
    return fromString<To>(str, strlen(str));
}

template<class To>
typename std::enable_if<std::is_unsigned<To>::value, To > ::type
fromString(const char * str)
{
    return fromString<To>(str, strlen(str));
}

template<class To>
typename std::enable_if<std::is_floating_point<To>::value, To > ::type
fromString(const char * str)
{
    return fromString<To>(str, strlen(str));
}


template<class To>
typename std::enable_if<std::is_same<To, std::string>::value, To > ::type
fromString(const char * str)
{
    return std::string(str);
}

template<class To>
typename std::enable_if<std::is_same<To, char>::value, To > ::type
fromString(const char * str)
{
    return fromString<To>(str, strlen(str));
}
template<class To>
typename std::enable_if<std::is_same<To, bool>::value, To > ::type
fromString(const char * str)
{
    return fromString<To>(str, strlen(str));
}
*/






inline const char * splitStringSearch(const char * begin, const char * end, char deli)
{
    while (begin != end && *begin != deli) ++begin;
    return begin;
}


template<class _Tuple>
void splitStringTupleImpl(_Tuple & ret, const char * begin, const char * end, char deli)
{
}

/*  
_Tuple is completion std::tuple<...T> .  
_This is current type.
    * if (std::is_arithmetic<_This>::value)  then  begin must had null-terminal char and this  deli not arithmetic value,   otherwise this impl will overwrid when call fromString .
    * when trans string to arithmetic will ignore bland char. 
*/
template<class _Tuple, class _This, class ... _Rest>
void splitStringTupleImpl(_Tuple & ret, const char * begin, const char * end, char deli)
{
    const char * next = end;
    do
    {
        while (begin != end && *begin == deli) ++begin; // merge and ignore the first, last deli multi-deli, and merge the mid multi-deli  
        if (begin == end) //empty
        {
            std::get< std::tuple_size<_Tuple>::value - 1 - sizeof ...(_Rest) >(ret) = _This();
            break;
        }
        next = splitStringSearch(begin, end, deli);
        std::get< std::tuple_size<_Tuple>::value - 1 - sizeof ...(_Rest) >(ret) = fromString<_This>(begin, next - begin);
        begin = next;
    } while (false);
    splitStringTupleImpl<_Tuple, _Rest ...>(ret, begin, end, deli);
}




template<class ... T>
typename std::enable_if<true, std::tuple<T ... >>::type splitStringTuple(const std::string & text, char deli)
{
    std::tuple<T ... > ret;
    splitStringTupleImpl<std::tuple<T ... >, T ...>(ret, text.c_str(), text.c_str()+text.length(), deli);
    return ret;
}



template<class ... T>
typename std::enable_if<true, std::vector<std::tuple<T ...> >>::type
splitStringTupleArray(const std::string & text, char deli, char subDeli)
{
    using Tuple = std::tuple<T ...>;
    std::vector<Tuple> ret;
    
    const char * begin = text.c_str();
    const char * end = text.c_str() + text.length();

    do
    {
        if (begin == end)
        {
            break;
        }
        Tuple one;
        const char * next = splitStringSearch(begin, end, deli);
        splitStringTupleImpl<Tuple, T ...>(one, begin, next, subDeli);
        ret.push_back(std::move(one));
        begin = next;
        if (begin != end)
        {
            ++begin; //ignore deli character
        }
    } while (true);
    return ret;
}

template<class _Value>
typename std::enable_if<true, std::vector<_Value>> ::type
splitStringSimpleArray(const std::string & text, char deli)
{
    using _Tuple = std::tuple<_Value>;
    std::vector<_Value> ret;
    
    const char * begin = text.c_str();
    const char * end = text.c_str() + text.length();

    do
    {
        if (begin == end)
        {
            break;
        }
        _Tuple one;
        const char * next = splitStringSearch(begin, end, deli);
        splitStringTupleImpl<_Tuple, _Value>(one, begin, next, deli);
        ret.push_back(std::move(std::get<0>(one)));
        begin = next;
        if (begin != end)
        {
            ++begin; //ignore deli character
        }
    } while (true);
    return ret;
}


template<size_t _Key, class ... T>
typename std::enable_if<true, std::map<typename std::tuple_element<_Key, std::tuple<T ...>>::type, std::tuple<T ...> >>::type
splitStringTupleDict(const std::string & text, char deli, char subDeli)
{
    using _Second = std::tuple<T ...>;
    using _First = typename std::tuple_element<_Key, std::tuple<T ...>>::type;
    std::map<_First, _Second> ret;
    
    const char * begin = text.c_str();
    const char * end = text.c_str() + text.length();

    do
    {
        if (begin == end)
        {
            break;
        }
        _First first;
        _Second one;
        const char * next = splitStringSearch(begin, end, deli);
        splitStringTupleImpl<_Second, T ...>(one, begin, next, subDeli);
        first = std::get<_Key>(one);
        ret.insert(std::make_pair(std::move(first), std::move(one)));
        begin = next;
        if (begin != end)
        {
            ++begin; //ignore deli character
        }
    } while (true);

    return ret;
}

template<class _Key, class _Value>
typename std::enable_if<true, std::map<_Key, _Value>>::type
splitStringSimpleDict(const std::string & text, char deli, char subDeli)
{
    using Second = std::tuple<_Key, _Value>;
    std::map<_Key, _Value> ret;
    
    const char * begin = text.c_str();
    const char * end = text.c_str() + text.length();

    do
    {
        if (begin == end)
        {
            break;
        }
        Second one;
        const char * next = splitStringSearch(begin, end, deli);
        splitStringTupleImpl<Second, _Key, _Value>(one, begin, next, subDeli);
        ret.insert(std::make_pair(std::move(std::get<0>(one)), std::move(std::get<1>(one))));
        begin = next;
        if (begin != end)
        {
            ++begin; //ignore deli character
        }
    } while (true);

    return ret;
}



inline double getFloatNowTime()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch()).count();
}
inline double getFloatSteadyNowTime()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline long long getNowTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline long long getNowSteadyTick()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline time_t getUTCTime()
{
    return time(NULL);
}
inline time_t getTZZoneOffset()
{
    time_t fixday = 7 * 24 * 3600;
    tm tm = gettm(fixday);
    return ((tm.tm_mday - 1) * 24 + tm.tm_hour) * 3600 - fixday;
}
inline time_t getDaySecond(time_t t)
{
    return (t + getTZZoneOffset()) % (24 * 3600);
}

//safe method for get tm from unix timestamp
// 
// struct tm {
//             int tm_sec;    /* Seconds (0-60) */
//             int tm_min;    /* Minutes (0-59) */
//             int tm_hour;   /* Hours (0-23) */
//             int tm_mday;   /* Day of the month (1-31) */
//             int tm_mon;    /* Month (0-11) */
//             int tm_year;   /* Year - 1900 */
//             int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
//             int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
//             int tm_isdst;  /* Daylight saving time */
//            };
// 
inline tm gettm(time_t ts)
{
    tm * tstm = localtime(&ts);
    if (!tstm)
    {
        ts = 0;
        tstm = localtime(&ts);
    }
    return *tstm;
}

inline std::string formatDateString(time_t ts)
{
    tm tstm = gettm(ts);
    char buff[50];
    sprintf(buff, "%04d-%02d-%02d", tstm.tm_year + 1900, tstm.tm_mon + 1, tstm.tm_mday);
    return buff;
}
inline std::string formatTimeString(time_t ts)
{
    tm tstm = gettm(ts);
    char buff[50];
    sprintf(buff, "%02d:%02d:%02d", tstm.tm_hour, tstm.tm_min, tstm.tm_sec);
    return buff;
}
inline std::string formatDateTimeString(time_t ts)
{
    tm tstm = gettm(ts);
    char buff[50];
    sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d",
        tstm.tm_year + 1900, tstm.tm_mon + 1, tstm.tm_mday,
        tstm.tm_hour, tstm.tm_min, tstm.tm_sec);
    return buff;
}

inline bool isSameYear(time_t first, time_t second, time_t offset)
{
    return gettm(first + offset).tm_year == gettm(second + offset).tm_year;
}
inline bool isSameMonth(time_t first, time_t second, time_t offset)
{
    tm ftm = gettm(first + offset);
    tm stm = gettm(second + offset);
    return ftm.tm_year == stm.tm_year && ftm.tm_mon == stm.tm_mon;
}
inline bool isSameWeak(time_t first, time_t second, time_t offset)
{
    tm ftm = gettm(first + offset);
    time_t begin = first + offset - (ftm.tm_wday * 24 * 3600) - ftm.tm_hour * 3600 - ftm.tm_min * 60 - ftm.tm_sec;
    return second + offset >= begin && second + offset < begin + 7 * 24 * 3600;
}
// example: if 03:00::00 is the day bound you can set offset = -3*3600
inline bool isSameDay(time_t first, time_t second, time_t offset)
{
    tm ftm = gettm(first + offset);
    tm stm = gettm(second + offset);
    return ftm.tm_year == stm.tm_year && ftm.tm_yday == stm.tm_yday;
}

inline int distanceDays(time_t first, time_t second)
{
    return (int)std::abs((long long)(second - getDaySecond(second)) - (long long)(first - getDaySecond(first))) / 3600 / 24;
}





inline std::tuple<double, double> operator + (const std::tuple<double, double> & self, const std::tuple<double, double> & val) 
{ 
    return std::tuple<double, double>(std::get<0>(self) + std::get<0>(val), std::get<1>(self) + std::get<1>(val)); 
}
inline std::tuple<double, double> operator - (const std::tuple<double, double> & self, const std::tuple<double, double> & val) 
{ 
    return std::tuple<double, double>(std::get<0>(self) - std::get<0>(val), std::get<1>(self) - std::get<1>(val)); 
}
inline std::tuple<double, double> operator * (const std::tuple<double, double> & self, const std::tuple<double, double> & val) 
{ 
    return std::tuple<double, double>(std::get<0>(self) * std::get<0>(val), std::get<1>(self) * std::get<1>(val)); 
}
inline std::tuple<double, double> operator / (const std::tuple<double, double> & self, const std::tuple<double, double> & val) 
{ 
    return std::tuple<double, double>(std::get<0>(self) / std::get<0>(val), std::get<1>(self) / std::get<1>(val)); 
}

inline std::tuple<double, double> operator + (const std::tuple<double, double> & self, double val)
{
    return std::tuple<double, double>(std::get<0>(self) + val, std::get<1>(self) + val);
}
inline std::tuple<double, double> operator - (const std::tuple<double, double> & self, double val)
{
    return std::tuple<double, double>(std::get<0>(self) - val, std::get<1>(self) - val);
}
inline std::tuple<double, double> operator * (const std::tuple<double, double> & self, double val)
{
    return std::tuple<double, double>(std::get<0>(self) * val, std::get<1>(self) * val);
}
inline std::tuple<double, double> operator / (const std::tuple<double, double> & self, double val)
{
    return std::tuple<double, double>(std::get<0>(self) / val, std::get<1>(self) / val);
}






inline bool isZero(double f, double acc)
{
    return fabs(f) < acc;
}


inline bool isEqual(double f1, double f2, double acc)
{
    return fabs(f1 - f2) <= std::max(fabs(f1), fabs(f2)) * acc;
}


inline double getDistance(double org, double dst)
{
    return fabs(org - dst);
}

inline double getDistance(double posx1, double posy1, double posx2, double posy2)
{
    return sqrt((posx1 - posx2)*(posx1 - posx2) +(posy1 - posy2)*(posy1-posy2));
}
inline double getDistance(const std::tuple<double, double> & pos1, const std::tuple<double, double> & pos2)
{
    return getDistance(std::get<0>(pos1), std::get<1>(pos1), std::get<0>(pos2), std::get<1>(pos2));
}

inline double getRadian(double vx, double vy)
{
    double r = getRadian(1, 0, vx, vy);
    if (vy < 0)
    {
        return PI * 2.0 - r;
    }
    return r;
}

inline double getRadian(double vx1, double vy1, double vx2, double vy2)
{
    return acos(dot(vx1,vy1, vx2, vy2) / sqrt( dot(vx1, vy1, vx1,vy1)*dot(vx2, vy2, vx2, vy2)));
}

inline double getRadian(const std::tuple<double, double> & v)
{
    return getRadian(std::get<0>(v), std::get<1>(v));
}
inline double getRadian(const std::tuple<double, double> & v1, const std::tuple<double, double> & v2)
{
    return getRadian(std::get<0>(v1), std::get<1>(v1), std::get<0>(v2), std::get<1>(v2));
}

inline std::tuple<double, double> getFarPoint(double orgx, double orgy, double radian, double distance)
{
    return std::make_tuple(orgx + cos(radian) * distance, orgy + sin(radian) * distance);
}






inline std::tuple<double, double> rotateVertical(std::tuple<double, double> vt, bool isClockwise) { return rotateVertical(std::get<0>(vt), std::get<1>(vt), isClockwise); }
inline std::tuple<double, double> rotateVertical(double vx, double vy, bool isClockwise)
{
    if (isClockwise)
    {
        return std::make_tuple(vy, vx*-1);
    }
    return std::make_tuple(vy*-1, vx);
}

inline std::tuple<double, double> normalize(std::tuple<double, double> vt) { return normalize(std::get<0>(vt), std::get<1>(vt)); }
inline std::tuple<double, double> normalize(double vx, double vy)
{
    double mode = std::sqrt(vx*vx + vy*vy);
    return std::make_tuple(vx / mode, vy / mode);
}

inline double dot(std::tuple<double, double> vt1, std::tuple<double, double> vt2)
{
    return dot(std::get<0>(vt1),  std::get<0>(vt1),  std::get<0>(vt2), std::get<1>(vt2));
}
inline double det(std::tuple<double, double> vt1, std::tuple<double, double> vt2)
{
    return det(std::get<0>(vt1), std::get<1>(vt1), std::get<0>(vt2),  std::get<1>(vt2));
}

inline double dot(double vx1, double vy1, double vx2, double vy2)
{
    return vx1 * vx2 + vy1 * vy2;
}
inline double det(double vx1, double vy1, double vx2, double vy2)
{
    return vx1 * vy2 - vx2 * vy1;
}
inline double distLine(double linex1, double liney1, double linex2, double liney2, double cx, double cy)
{
    double vx1 = linex2 - linex1;
    double vy1 = liney2 - liney1;
    double vx2 = cx - linex1;
    double vy2 = cy - liney1;
    return det(vx1, vy1, vx2, vy2) / std::sqrt(vx1*vx1 + vy1*vy1);
}
inline double distLine(std::tuple<double, double> line1, std::tuple<double, double> line2, std::tuple<double, double> pos)
{
    return distLine(std::get<0>(line1), std::get<1>(line1), std::get<0>(line2), std::get<1>(line2), std::get<0>(pos), std::get<1>(pos));
}
inline std::tuple<double, double> shortestLine(double linex1, double liney1, double linex2, double liney2, double cx, double cy)
{
    return shortestLine(std::tuple<double, double>(linex1, liney1), std::tuple<double, double>(linex2, liney2), std::tuple<double, double>(cx, cy));
}

inline std::tuple<double, double> shortestLine(std::tuple<double, double> line1, std::tuple<double, double> line2, std::tuple<double, double> pos)
{
    const double prec = 0.001;
    std::tuple<double, double> ret;
    double distl1 = getDistance(line1, pos);
    double distl2 = getDistance(line2, pos);
    if (distl1 < prec)
    {
        return line1;
    }
    if (distl2 < prec)
    {
        return line2;
    }

    double x1 = dot(line2 - line1, pos - line1); 
    if (std::abs(x1) < prec)
    {
        return line1;
    }
    double x2 = dot(line1 - line2, pos - line2);
    if (std::abs(x2) < prec)
    {
        return line2;
    }
    if (x2 > 0.0 && x1 > 0.0)
    {
        double distL = distLine(line1, line2, pos);
        double distL1 = getDistance(line1, pos);
        double dist = std::sqrt(distL1*distL1 - distL*distL);
        return line1 + normalize(line2 - line1)*dist;
    }
    if (x1 < 0)
    {
        return line1;
    }
    return line2;
}




template<class Integer, class Pos>
inline bool getBitFlag(Integer bin, Pos pos)
{
    return (bin & ((Integer)1 << (pos - 1))) != 0;
}

template<class Integer, class Pos>
inline Integer setBitFlag(Integer bin, Pos pos, bool flag)
{
    if (flag)
    {
        return bin | ((Integer)1 << (pos - 1));
    }
    return bin & ~((Integer)1 << (pos - 1));
}




//integer
//==========================================================================
//return value is [min, max]
template<class T>
inline T pruning(T v, T min, T max)
{
    return v < min ? min : (v > max ? max : v);
}


template<class RandIt>
inline void randomShuffle(RandIt first, RandIt end)
{
    std::random_shuffle(first, end);
}





template<class RandIt, class GetWeightFunc> 
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount, bool uniqueTake, GetWeightFunc getWeight)
{
    std::vector<std::pair<RandIt, int> > temp;
    std::vector<RandIt> ret;
    ret.reserve(takeCount);
    temp.reserve(128);
    int sumWeight = 0;
    if (true)
    {
        auto cur = first;
        while (cur != end)
        {
            int curWeight = getWeight(cur);
            if (curWeight > 0)
            {
                sumWeight += curWeight;
                temp.push_back(std::make_pair(cur, curWeight));
            }
            cur++;
        }
    }
    
    size_t curTakeCount = 0;
    while (sumWeight > 0 && temp.size() > 0 && curTakeCount < (size_t)takeCount)
    {
        curTakeCount++;
        int rd = realRand() % (sumWeight);
        int curWeight = 0;
        for (auto iter = temp.begin(); iter != temp.end();)
        {
            auto & v = *iter;
            curWeight += v.second;
            if (rd < curWeight)
            {
                ret.push_back(v.first);
                if (uniqueTake)
                {
                    sumWeight -= v.second;
                    temp.erase(iter);
                }
                break;
            }
            iter++;
        }
    }
    return ret;
}

template<class RandIt, class GetProbabilityFunc> // func example  [](RandIt iter){return iter->probability;}
inline std::vector<RandIt> raffle(RandIt first, RandIt end, int takeCount, GetProbabilityFunc getProbability)
{
    std::vector<RandIt> ret;
    ret.reserve(takeCount);
    auto cur = first;
    while (cur != end)
    {
        double prob = getProbability(cur);
        for (int i=0; i<takeCount; i++)
        {
            double rd = realRandF();
            if (rd < prob)
            {
                ret.push_back(cur);
            }
        }
        cur++;
    }
    return ret;
}

inline double calcELORatingUpper(double ownerScore, double dstScore, int winFlag)
{
    double base = winFlag == 0 ? 0.5 : (winFlag > 0 ? 1.0 : 0);
    double winRate = 1.0 / (1.0 + pow(10.0, (dstScore - ownerScore) / 400.0));
    return 32.0 * (base - winRate);
}



template<class Container>
std::string mergeToString(const Container & contariner, char deli)
{
    std::string ret;
    for (const auto &t : contariner)
    {
        ret += toString(t);
        ret += deli;
    }
    if (!ret.empty())
    {
        ret.pop_back();
    }
    return ret;
}

template<class T>  //example: Container = std::vector<int>
void mergeToString(std::string & dstString, char deli, const T & t)
{
    if (!dstString.empty() && dstString.back() != deli)
    {
        dstString += deli;
    }
    dstString += toString(t);
}

#endif
