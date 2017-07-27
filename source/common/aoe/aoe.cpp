#include "aoe.h"
#include <algorithm>
#include <iostream>
#include <vector>



AOECheck::AOECheck()
{

}

AOECheck::~AOECheck()
{

}


bool AOECheck::init(std::tuple<double, double> org, std::tuple<double, double> vt, bool isRect, double value1, double value2, double value3, double clip)
{

    _org = org;
    _orgc = org + vt*clip;
    _vt = vt;
    _isRect = isRect;
    _value1 = value1;
    _value2 = value2;
    _value3 = value3;
    _clip = clip;
    _areaDistance = value1;
    if (isRect)
    {
        double v = std::max(value2, value3) / 2.0;
        _areaDistance = std::sqrt(v*v + value1*value1);
    }

    if (isRect)
    {
        std::tuple<double, double> rvt = rotateVertical(std::get<0>(vt), std::get<1>(vt), true);
        _convexs.reserve(4);
        _convexs.push_back(org + rvt*value3 / 2.0);
        _convexs.push_back(org + vt * value1 + rvt*value2 / 2.0);
        _convexs.push_back(org + vt * value1 - rvt*value2 / 2.0);
        _convexs.push_back(org - rvt*value3 / 2.0);
        _fastBot = _convexs.front();
        _fastTop = _convexs.back();
        for (size_t i = 0; i < _convexs.size(); i++)
        {
            std::get<0>(_fastBot) = std::min(std::get<0>(_fastBot), std::get<0>(_convexs[i]));
            std::get<1>(_fastBot) = std::min(std::get<1>(_fastBot), std::get<1>(_convexs[i]));
            std::get<0>(_fastTop) = std::max(std::get<0>(_fastTop), std::get<0>(_convexs[i]));
            std::get<1>(_fastTop) = std::max(std::get<1>(_fastTop), std::get<1>(_convexs[i]));
        }
    }
    return true;
}

std::tuple<bool, double> AOECheck::check(std::tuple<double, double> pos, double collision)
{
    double distance = getDistance(_org, pos) - collision;
    auto outRet = std::make_tuple(false, 0);
    auto inRet = std::make_tuple(true, distance);

    if (distance > _areaDistance)
    {
        return outRet;
    }

    //circle 
    if (!_isRect && _value2 > PI * 2.0 * 0.9)
    {
        //clip
        if (_clip != 0.0 && distance < _clip)
        {
            return outRet;
        }
        return inRet;
    }

    //radian 
    if (!_isRect)
    {
        //clip
        if (_clip != 0.0 && distance < _clip)
        {
            return outRet;
        }
        double r = getRadian(pos - _org, _vt);
        if (r < _value2 / 2.0)
        {
            return inRet;
        }
        return outRet;
    }

    if (_convexs.size() < 3)
    {
        return outRet;
    }
    //fast check
    if (std::get<0>(pos) < std::get<0>(_fastBot) 
        || std::get<1>(pos) < std::get<1>(_fastBot) 
        || std::get<0>(pos) > std::get<0>(_fastTop) 
        || std::get<1>(pos) > std::get<1>(_fastTop))
    {
        return outRet;
    }

    bool prime = false;
    for (int i = 0, j = (int)_convexs.size() - 1; i < (int)_convexs.size(); j = i++)
    {
        if (((std::get<1>(_convexs[i]) > std::get<1>(pos)) != (std::get<1>(_convexs[j]) > std::get<1>(pos)))
            &&
            (std::get<0>(pos) - std::get<0>(_convexs[i])
                < (std::get<0>(_convexs[j]) - std::get<0>(_convexs[i])) 
                * (std::get<1>(pos) - std::get<1>(_convexs[i])) 
                / (std::get<1>(_convexs[j]) - std::get<1>(_convexs[i]))))
        {
            prime = !prime;
        }
    }
    if (prime)
    {
        return inRet;
    }
    return outRet;
}









