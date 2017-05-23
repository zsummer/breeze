/*
* breeze License
* Copyright (C) 2017 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
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

#ifndef _AOE_H_
#define _AOE_H_

#include "../utls.h"
#include <tuple>





class AOECheck
{
public:
    AOECheck();
    ~AOECheck();
    bool init(std::tuple<double, double> org, std::tuple<double, double> vt, bool isRect, double value1, double value2, double value3, double clip);
    std::tuple<bool, double> check(std::tuple<double, double> pos, double collision);
private:
    std::tuple<double, double> _org;
    std::tuple<double, double> _orgc;
    std::tuple<double, double> _vt;
    bool _isRect;
    double _value1;
    double _value2;
    double _value3;
    double _clip;
    double _areaDistance = 0;
    std::vector<std::tuple<double, double>> _convexs;
    std::tuple<double, double> _fastBot;
    std::tuple<double, double> _fastTop;
protected:
private:
};





























#endif
