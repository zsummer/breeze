/*
* breeze License
* Copyright (C) 2014-2017 YaweiZhang <yawei.zhang@foxmail.com>.
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


//! 测试

#include <common.h>
#include <utls.h>
#include <balance.h>
using namespace zsummer::log4z;
using namespace zsummer::mysql;


inline std::vector<std::string>  gray_code_rec(int cur)
{
    if (cur == 1)
    {
        return { "0", "1" };
    }
    std::vector<std::string> curLayer;
    auto floorLayer = gray_code_rec(cur - 1);
    std::for_each(floorLayer.begin(), floorLayer.end(), [&curLayer](auto & x) {curLayer.push_back("0" + x); });
    std::for_each(floorLayer.rbegin(), floorLayer.rend(), [&curLayer](auto & x) {curLayer.push_back("1" + x); });
    return curLayer;
}

inline std::vector<std::string>  gray_code_iter(int cur)
{
    std::vector<std::string> floorLayer;
    std::vector<std::string> curLayer = { "0", "1" };

    for (int i = 1; i < cur; i++)
    {
        floorLayer.swap(curLayer);
        curLayer.clear();
        std::for_each(floorLayer.begin(), floorLayer.end(), [&curLayer](auto & x) {curLayer.push_back("0" + x); });
        std::for_each(floorLayer.rbegin(), floorLayer.rend(), [&curLayer](auto & x) {curLayer.push_back("1" + x); });
    }
    return curLayer;
}


inline void arith_gray_code()
{
    LOGD(gray_code_rec(2));
    LOGD(gray_code_iter(2));

}
