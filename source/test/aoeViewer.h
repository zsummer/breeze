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
#include <aoe/aoe.h>
using namespace zsummer::log4z;
using namespace zsummer::mysql;
#include <bcui/bcui.h>





struct Aoe
{
    std::tuple<double, double> org;
    std::tuple<double, double> vt;
    bool isRect;
    double value1;
    double value2;
    double value3;
    double clip;
};


inline void AoeViewer()
{
    BCUI bcui(screenX, screenY, BCUI_PIXEL_WHITE);
    bcui.init();
    bcui.reset(BCUI_PIXEL_WHITE);


    std::vector<Aoe> aoes;
    if (true)
    {
        Aoe aoe;
        std::get<0>(aoe.org) = screenX / 2.0;
        std::get<1>(aoe.org) = screenY / 2.0;
        aoe.value1 = screenY / 3.0;
        aoe.value2 = PI;
        aoe.value3 = 10;
        aoe.isRect = false;
        aoe.clip = 1;
        for (int i = 1; i <= 7; i++)
        {
            aoe.value2 = PI / 180.0 * 60.0 * i;
            for (int j = 0; j < 5; j++)
            {
                aoe.vt = getFarPoint(0, 0, PI * 2 / 4 * j, 1);
                for (int c = 0; c < 2; c++)
                {
                    aoe.clip = 6 * c;
                    aoes.push_back(aoe);
                }
            }
        }

        aoe.isRect = true;
        aoe.clip = 0;

        for (int j = 1; j <= 6; j++)
        {
            aoe.vt = getFarPoint(0, 0, PI * 2 / 5 * j, 1);
            aoe.value2 = aoe.value1;
            aoe.value3 = aoe.value1 / 3;
            aoes.push_back(aoe);
            aoe.value2 = aoe.value1 / 3;
            aoe.value3 = aoe.value1;
            aoes.push_back(aoe);
            aoe.value2 = aoe.value1 / 2;
            aoe.value3 = 10;
            aoes.push_back(aoe);
        }

        for (int i = 1; i <= 7; i++)
        {
            aoe.value2 = PI / 180.0 * 60.0 * i;

        }

    }


    for (auto aoe : aoes)
    {
        bcui.reset(BCUI_PIXEL_WHITE);
        bcui.setPos(0, 0, BCUI_PIXEL_WHITE);
        if (!aoe.isRect)
        {
            printf("AOE Circle  dist=%.2lf  angle=%.2lf  clip=%.2lf  face=%.2lf", aoe.value1, aoe.value2/PI*180, aoe.clip, getRadian(aoe.vt) / PI * 180);
        }


        AOECheck ac;
        if (ac.init(aoe.org, aoe.vt, aoe.isRect, aoe.value1, aoe.value2, aoe.value3, aoe.clip))
        {
            printf("  AOeCheck init success");
        }
        else
        {
            printf("  AOeCheck init error");
        }
        bcui.setPos((int)std::get<0>(aoe.org), (int)std::get<1>(aoe.org), BCUI_PIXEL_RED);
        for (int i = 0; i < screenX; i++)
        {
            for (int j = 0; j < screenY; j++)
            {
                auto ret = ac.check(std::make_tuple(i*1.0, j*1.0), 0);
                if (std::get<0>(ret))
                {
                    bcui.setPos(i, j, BCUI_PIXEL_BLUE);
                }
            }
        }
        bcui.setPos((int)std::get<0>(aoe.org), (int)std::get<1>(aoe.org), BCUI_PIXEL_RED);
        sleepMillisecond(500);
    }

    return;
}