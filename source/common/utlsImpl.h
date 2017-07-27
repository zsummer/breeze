

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



#ifndef _UTLS_IMPL_H_
#define _UTLS_IMPL_H_


//string
template<class T>
std::string toString(const T &t)
{
    std::stringstream os;
    os.precision(16);
    os << t;
    return os.str();
}




template<class To>
typename std::enable_if<std::is_floating_point<To>::value, To>::type fromString(const std::string & t, To def)
{
    if (t.empty()) return def;
    return (To)atof(t.c_str());
}
template<class To>
typename std::enable_if<std::is_floating_point<To>::value, To>::type fromString(const std::string & t)
{
    return (To)atof(t.c_str());
}

template<class To>
typename std::enable_if<std::is_integral<To>::value, To>::type fromString(const std::string & t, To def)
{
    if (t.empty()) return def;
    if (t.length()>= 19)
    {
        if (typeid(To) == typeid(unsigned long long))
        {
            char *cursor = nullptr;
            return (To)strtoull(t.c_str(), &cursor, 10);
        }
    }
    return (To)atoll(t.c_str());
}

template<class To>
typename std::enable_if<std::is_integral<To>::value, To>::type fromString(const std::string & t)
{
    if (t.length() >= 19)
    {
        if (typeid(To) == typeid(unsigned long long))
        {
            char *cursor = nullptr;
            return (To)strtoull(t.c_str(), &cursor, 10);
        }
    }
    return (To)atoll(t.c_str());
}

template<class To>
typename std::enable_if<std::is_pointer<To>::value, To>::type fromString(const std::string & t, To def)
{
    if (t.empty()) return def;
    return t.c_str();
}
template<class To>
typename std::enable_if<std::is_pointer<To>::value, To>::type fromString(const std::string & t)
{
    return t.c_str();
}

template<class To>
typename std::enable_if<std::is_class<To>::value, To>::type fromString(const std::string & t, To def)
{
    if (t.empty()) return def;
    return t;
}
template<class To>
typename std::enable_if<std::is_class<To>::value, To>::type fromString(const std::string & t)
{
    return t;
}

template<class To>
typename std::enable_if<std::is_class<To>::value, To>::type fromString(std::string && t, To def)
{
    if (t.empty()) return def;
    return std::move(t);
}
template<class To>
typename std::enable_if<std::is_class<To>::value, To>::type fromString(std::string && t)
{
    return std::move(t);
}


template<class _Tuple>
void splitTupleStringImpl(_Tuple & ret, const std::string & text, const std::string & deli, const std::string & ign)
{
}

template<class _Tuple, class _This, class ... _Rest>
void splitTupleStringImpl(_Tuple & ret, const std::string & text, const std::string & deli, const std::string & ign)
{
    std::size_t which = std::tuple_size<_Tuple>::value - 1 - sizeof ...(_Rest);
    std::size_t firstCursor = 0;
    std::size_t secondCursor = 0;
    std::size_t curFinder = 0;
    while (curFinder <= which)
    {
        auto pos = text.find(deli, firstCursor);
        if (curFinder < which &&  pos == std::string::npos)
        {
            // not found
            return;
        }
        else if (curFinder < which)
        {
            curFinder++;
            firstCursor = pos + deli.size();
        }
        else
        {
            secondCursor = pos;
            break;
        }
    }
    std::get< std::tuple_size<_Tuple>::value - 1 - sizeof ...(_Rest) >(ret) = fromString<_This>(trim(text.substr(firstCursor, secondCursor - firstCursor), ign));
    splitTupleStringImpl<_Tuple, _Rest ...>(ret, text, deli, ign);
}




template<class ... T>
typename std::enable_if<std::is_integral<int>::value, std::tuple<T ... >>::type splitTupleString(const std::string & text, const std::string & deli, const std::string & ign)
{
    std::tuple<T ... > ret;
    splitTupleStringImpl<std::tuple<T ... >, T ...>(ret, text, deli, ign);
    return ret;
}

template<class First, class Second>
typename std::enable_if<std::is_integral<int>::value, std::pair<First, Second>>::type splitPairString(const std::string & str, const std::string & delimiter)
{
    auto tp = splitTupleString<First, Second>(str, delimiter, "");
    return std::make_pair(std::get<0>(tp), std::get<1>(tp));
}


template<class ... T>
typename std::enable_if<std::is_integral<int>::value, std::vector<std::tuple<T ...> >>::type
splitArrayString(const std::string & text, const std::string & deli, const std::string & deliMeta, const std::string & ign)
{
    std::vector<std::tuple<T ...> > ret;
    size_t beginPos = 0;
    std::string matched;
    for (size_t i = 0; i < text.length(); i++)
    {
        if ((matched.empty() && text[i] == deli[0]) || !matched.empty())
        {
            matched.push_back(text[i]);
        }
        if (matched == deli)
        {
            auto one = trim(text.substr(beginPos, i + 1 - deli.length() - beginPos), ign);
            if (!one.empty())
            {
                ret.push_back(splitTupleString<T...>(one, deliMeta, ign));
            }
            beginPos = i + 1;
            matched.clear();
        }
    }
    auto one = trim(text.substr(beginPos, text.length() - beginPos), ign);
    if (!one.empty())
    {
        ret.push_back(splitTupleString<T...>(std::move(one), deliMeta, ign));
    }
    return std::move(ret);
}


template<class Key, class ... T>
typename std::enable_if<std::is_integral<int>::value, std::map<Key, std::tuple<Key, T ...> >>::type
splitDictString(const std::string & text, const std::string & deli, const std::string & deliMeta, const std::string & ign)
{
    std::map<Key, std::tuple<Key, T ...> > ret;
    size_t beginPos = 0;
    std::string matched;
    for (size_t i = 0; i < text.length(); i++)
    {
        if ((matched.empty() && text[i] == deli[0]) || !matched.empty())
        {
            matched.push_back(text[i]);
        }
        if (matched == deli)
        {
            auto one = trim(text.substr(beginPos, i + 1 - deli.length() - beginPos), ign);
            if (!one.empty())
            {
                auto tp = splitTupleString<Key, T...>(one, deliMeta, ign);
                auto k = std::get<0>(tp);
                auto founder = ret.find(k);
                if (founder == ret.end())
                {
                    ret.insert(std::make_pair(k, std::move(tp)));
                }
                else
                {
                    founder->second = std::move(tp);
                }
            }
            beginPos = i + 1;
            matched.clear();
        }
    }
    auto one = trim(text.substr(beginPos, text.length() - beginPos), ign);
    if (!one.empty())
    {
        auto tp = splitTupleString<Key, T...>(one, deliMeta, ign);
        auto k = std::get<0>(tp);
        ret[k] = std::move(tp);
    }
    return std::move(ret);
}



template<class Value>
typename std::enable_if<std::is_integral<int>::value, std::vector<Value>>::type
splitString(std::string text, const std::string & deli, const std::string & ign)
{
    std::vector<Value> ret;
    size_t beginPos = 0;
    std::string matched;
    for (size_t i = 0; i < text.length(); i++)
    {
        if ((matched.empty() && text[i] == deli[0]) || !matched.empty())
        {
            matched.push_back(text[i]);
        }
        if (matched == deli)
        {
            ret.push_back(fromString<Value>(trim(text.substr(beginPos, i + 1 - deli.length() - beginPos), ign)));
            beginPos = i + 1;
            matched.clear();
        }
    }
    ret.push_back(fromString<Value>(trim(text.substr(beginPos, text.length() - beginPos), ign)));
    return std::move(ret);
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
    return std::move(ret);
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
    return std::move(ret);
}

inline double calcELORatingUpper(double ownerScore, double dstScore, int winFlag)
{
    double base = winFlag == 0 ? 0.5 : (winFlag > 0 ? 1.0 : 0);
    double winRate = 1.0 / (1.0 + pow(10.0, (dstScore - ownerScore) / 400.0));
    return 32.0 * (base - winRate);
}



template<class Container>
std::string mergeToString(const Container & contariner, const std::string& deli)
{
    std::string ret;
    for (const auto &t : contariner)
    {
        ret += toString(t);
        ret += deli;
    }
    if (!deli.empty())
    {
        for (size_t i = 0; i < deli.size(); i++)
        {
            ret.pop_back();
        }
    }
    return ret;
}

template<class T>  //example: Container = std::vector<int>
void mergeToString(std::string & dstString, const std::string& deli, const T & t)
{
    if (!dstString.empty())
    {
        dstString += deli;
    }
    dstString += toString(t);
}

#endif
