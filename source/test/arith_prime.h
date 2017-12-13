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


inline void arith_prime()
{
    const unsigned long long dataSize = 1 * 100 * 1000;
    const unsigned long long sqrtSize = (unsigned long long)sqrt(dataSize);
    bool *data = new bool[dataSize + 1];// is comp
    memset(data, 0, sizeof(bool)*(dataSize + 1));

    std::vector<unsigned long long> prime;

    double now = getFloatSteadyNowTime();

    for (unsigned long long i = 2; i <= dataSize; i++)
    {
        if (!data[i])
        {
            for (size_t j = i + i; j <= dataSize; j += i)
            {
                data[j] = true;
            }
            prime.push_back(i);
        }
    }

    LOGD("normal  sieve used time " << getFloatSteadyNowTime() - now << ", " << prime);



    prime.clear();
    memset(data, 0, sizeof(bool)*(dataSize + 1));
    now = getFloatSteadyNowTime();
    for (unsigned long long i = 2; i <= sqrtSize; i++)
    {
        if (!data[i])
        {
            for (size_t j = i + i; j <= dataSize; j += i)
            {
                data[j] = true;
            }
            prime.push_back(i);
        }
    }
    for (size_t i = sqrtSize; i < dataSize; i++)
    {
        if (!data[i])
        {
            prime.push_back(i);
        }
    }

    LOGD("normal optimize sieve used time " << getFloatSteadyNowTime() - now << ", " << prime);

    prime.clear();
    memset(data, 0, sizeof(bool)*(dataSize + 1));
    now = getFloatSteadyNowTime();
    for (unsigned long long i = 2; i <= dataSize; i++)
    {
        if (!data[i])
        {
            prime.push_back(i);
        }
        for (auto x : prime)
        {
            long long m = i*x;
            if (m> dataSize)
            {
                break;
            }
            data[m] = true;
            if (i%x == 0)
            {
                break;
            }
        }

    }
    LOGD("liner sieve used time " << getFloatSteadyNowTime() - now << ", " << prime);



    prime.clear();
    memset(data, 0, sizeof(bool)*(dataSize + 1));
    now = getFloatSteadyNowTime();
    for (unsigned long long i = 2; i <= dataSize; i++)
    {
        bool canComb = false;
        for (auto x : prime)
        {
            if (x > sqrtSize)
            {
                break;
            }
            if (i%x == 0)
            {
                canComb = true;
                break;
            }
        }
        if (canComb)
        {
            continue;
        }
        prime.push_back(i);
    }
    LOGD("mod optimize prime used time " << getFloatSteadyNowTime() - now << ", " << prime);






    prime.clear();
    memset(data, 0, sizeof(bool)*(dataSize + 1));
    now = getFloatSteadyNowTime();
    for (unsigned long long i = 2; i <= dataSize; i++)
    {
        bool canComb = false;
        for (auto x : prime)
        {
            if (i%x == 0)
            {
                canComb = true;
                break;
            }
        }
        if (canComb)
        {
            continue;
        }
        prime.push_back(i);
    }
    LOGD("mod prime used time " << getFloatSteadyNowTime() - now << ", " << prime);


    delete[]data;

}
