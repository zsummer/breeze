
/*
* breeze License
* Copyright (C) 2015 YaweiZhang <yawei.zhang@foxmail.com>.
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


/*
 *  file desc
 */


#ifndef _ANY_H_
#define _ANY_H_
#include <defined.h>



// 仅支持基础类型哦
class Any
{
public:
    Any(unsigned long long ull)
    {
        _integer = ull;
    }
    Any(const std::string & str)
    {
        _str = str;
    }
    Any(const Any & a)
    {
        _integer = a._integer;
        _str = a._str;
    }
    Any(Any && a)
    {
        _integer = a._integer;
        _str = std::move(a._str);
    }
    std::string _str;
    unsigned long long _integer = 0;

};


template<class T>
T integerCast(const Any & a)
{
    return static_cast<T>(a._integer);
}


inline std::string stringCast(const Any & a)
{
    return a._str;
}






























#endif
