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




inline std::tuple<double, double> randPos(int maxX, int maxY)
{
    int x = rand() % maxX;
    int y = rand() % maxY;
    return make_tuple((double)x, (double)y);
}

inline void setPos(BCUI& bcui, std::tuple<double, double> vt, BCUI_PIXEL bp)
{
    bcui.setPos((int)std::get<0>(vt), (int)std::get<1>(vt), bp);
}

inline void vectorViewer()
{
    BCUI bcui(screenX, screenY, BCUI_PIXEL_WHITE);
    bcui.init();
    bcui.reset(BCUI_PIXEL_WHITE);


    double ret = det( std::make_tuple(-12, -17), std::make_tuple(-6, 15));
    for (int i=0; i< 100; i++)
    {
        bcui.reset(BCUI_PIXEL_WHITE);
        auto org = randPos(bcui.getX(), bcui.getY());

        auto dst = randPos(bcui.getX(), bcui.getY());

        auto one = randPos(bcui.getX(), bcui.getY());

        setPos(bcui, org, BCUI_PIXEL_BLACK);
        setPos(bcui, dst, BCUI_PIXEL_RED);
        setPos(bcui, one, BCUI_PIXEL_BLUE);
        setPos(bcui, std::make_tuple(2,0), BCUI_PIXEL_WHITE);
//        printf("dot:%0.2lf, det:%0.2lf ----------------", dot(dst - org, org - one) / dot(dst - org, dst - org) / dot(one - org, one - org),
//            det(dst - org, org - one));

        auto a = dst - org;
        auto b = one - org;



        printf("AB=[%.2lf, %.2lf], CA=[%.2lf,%.2lf],  det=%.2lf  distLine=%.2lf----------------", std::get<0>(a), std::get<1>(a),
            std::get<0>(b), std::get<1>(b), det(a, b), distLine(org, dst, one));
        sleepMillisecond(7000);
    }


    

    return ;
}