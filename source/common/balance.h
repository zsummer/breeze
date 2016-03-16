

/*
* breeze License
* Copyright (C) 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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
 * 封装了一个负载均衡的处理类,提供两套*独立*的的负载均衡接口.
 * (启用节点)enbaleNode
 * (清理节点权重数据)cleanNode
 * (废弃节点)disableNode
 * (获取当前处理类的当前负载数据)getBalanceStatus
 * +手动控制权重接口
 *   -(获取当前所有有效节点的负载系数)getBalanceRate
 *   -(调整负载量)changeWeight
 *   -(根据当前负载量选择一个负载最小的节点)selectManual
 * +自动控制权重接口
 *   -(自动获取一个权重系数小的节点)selectAuto
 *
*/

#ifndef _BALANCE_H_
#define _BALANCE_H_
#include <defined.h>
class Balance
{
public:
    //server node, isAble, manual weight, auto weight, total select count
    using BalanceInfo = std::tuple<ClusterID, bool, float, float, float>;
    Balance(){}
    inline bool enableNode(ClusterID node);
    inline bool cleanNode(ClusterID node);
    inline bool disableNode(ClusterID node);
    inline bool changeWeight(ClusterID node, float weight);

    inline ClusterID selectAuto();
    inline ClusterID selectManual();
    inline float getBalanceRate();
    inline std::string getBalanceStatus();
private:
    std::vector<BalanceInfo> _balance;
};
inline bool Balance::enableNode(ClusterID node)
{
    if(node == InvalidClusterID)
    {
        return false;
    }
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt){return node == std::get<0>(bt);});
    if (founder != _balance.end())
    {
        std::get<1>(*founder) = true;
    }
    else
    {
        _balance.push_back(std::make_tuple(node, true, 0.0f, 0.0f, 0.0f));
    }
    return true;
}
inline bool Balance::cleanNode(ClusterID node)
{
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt){return node == std::get<0>(bt);});
    if (founder == _balance.end())
    {
        return false;
    }
    std::get<2>(*founder) = 0;
    std::get<3>(*founder) = 0;
    std::get<4>(*founder) = 0;
    return true;
}
inline bool Balance::disableNode(ClusterID node)
{
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt){return node == std::get<0>(bt);});
    if(founder == _balance.end())
    {
        return true;
    }
    std::get<1>(*founder) = false;
    return true;
}
inline bool Balance::changeWeight(ClusterID node, float weight)
{
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt){return node == std::get<0>(bt);});
    if (founder == _balance.end())
    {
        if (enableNode(node))
            return changeWeight(node, weight);
        else
            return false;
    }
    else
    {
        std::get<2>(*founder) += weight;
    }
    return true;
}

inline ClusterID Balance::selectAuto()
{
    size_t idx = (size_t)-1;
    float weight = (float)1E15;
    for (size_t i = 0; i < _balance.size(); ++i)
    {
        if(std::get<1>(_balance[i]) && std::get<3>(_balance[i]) < weight)
        {
            idx = i;
            weight = std::get<3>(_balance[i]);
        }
    }
    if (idx == (size_t)-1)
    {
        return InvalidClusterID;
    }
    std::get<3>(_balance[idx]) ++;
    std::get<4>(_balance[idx]) ++;
    return std::get<0>(_balance[idx]);
}
inline ClusterID Balance::selectManual()
{
    size_t idx = (size_t)-1;
    float weight = (float)1E15;
    for (size_t i = 0; i < _balance.size(); ++i)
    {
        if(std::get<1>(_balance[i]) && std::get<2>(_balance[i]) < weight)
        {
            idx = i;
            weight = std::get<2>(_balance[i]);
        }
    }
    if (idx == (size_t)-1)
    {
        return InvalidClusterID;
    }
    std::get<4>(_balance[idx]) ++;
    return std::get<0>(_balance[idx]);
}
inline float Balance::getBalanceRate()
{

    float light = 0.0;
    float weight = 0.0;
    float count = 0.0;
    for (size_t i = 0; i < _balance.size(); ++i)
    {
        if(!std::get<1>(_balance[i])) continue;
        if(std::get<2>(_balance[i]) < light)
        {
            light = std::get<2>(_balance[i]);
        }
        weight += std::get<2>(_balance[i]);
        count ++;
    }
    if (isZero(count, 1e-5) || isZero(weight, 1e-5))
    {
        return 1.0;
    }
    return light/(weight/count);
}
inline std::string Balance::getBalanceStatus()
{
    std::stringstream ss;
    for (size_t i= 0; i < _balance.size(); ++i)
    {
        ss << "[node=";
        ss << std::get<0>(_balance[i]);
        ss << ", isable=";
        ss << std::get<1>(_balance[i]);
        ss << ", manualweight=";
        ss << std::get<2>(_balance[i]);
        ss << ", autoweight=";
        ss << std::get<3>(_balance[i]);
        ss << ", selected=";
        ss << std::get<4>(_balance[i]);
        ss << "],";
    }
    return std::move(ss.str());
}



#endif
