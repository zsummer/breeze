

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
template<class BalanceID>
class Balance
{
public:
    struct  BalanceInfo
    {
        BalanceInfo(BalanceID arg1, bool arg2, double arg3, double arg4):id(arg1),active(arg2),weight(arg3), count(arg4){}
        BalanceID id = 0;
        bool active = false;
        double weight = 0;
        double count = 0;
    };
    Balance(){}
    inline bool enableNode(BalanceID node);
    inline bool cleanNode(BalanceID node);
    inline bool disableNode(BalanceID node);
    inline size_t activeNodes();

    inline bool addWeight(BalanceID node, double weight);

    inline BalanceID pickNode(double step, double weight);
    inline double getBalanceDeviation();
    inline std::string getBalanceStatus();
private:
    std::vector<BalanceInfo> _balance;
    size_t _idx = -1;
};

template<class BalanceID>
inline bool Balance<BalanceID>::enableNode(BalanceID node)
{
    if(node == InvalidDockerID)
    {
        return false;
    }
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt) {return node == bt.id; });
    if (founder != _balance.end())
    {
        founder->active = true;
    }
    else
    {
        _balance.push_back(BalanceInfo(node, true, 0.0, 0.0));
    }
    return true;
}

template<class BalanceID>
inline bool Balance<BalanceID>::cleanNode(BalanceID node)
{
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt) {return node == bt.id; });
    if (founder == _balance.end())
    {
        return false;
    }
    founder->weight = 0.0;
    founder->count = 0.0;
    return true;
}

template<class BalanceID>
inline bool Balance<BalanceID>::disableNode(BalanceID node)
{
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt) {return node == bt.id; });
    if(founder == _balance.end())
    {
        return true;
    }
    founder->active = false;
    return true;
}
template<class BalanceID>
inline size_t Balance<BalanceID>::activeNodes()
{
    size_t ret = 0;
    for (auto & node : _balance)
    {
        if (node.active)
        {
            ret++;
        }
    }
    return ret;
}
template<class BalanceID>
inline bool Balance<BalanceID>::addWeight(BalanceID node, double weight)
{
    auto founder = std::find_if(_balance.begin(), _balance.end(), [node](const BalanceInfo & bt) {return node == bt.id; });
    if (founder == _balance.end())
    {
        if (enableNode(node))
            return addWeight(node, weight);
        else
            return false;
    }
    else
    {
        founder->weight += weight;
    }
    return true;
}

template<class BalanceID>
inline BalanceID Balance<BalanceID>::pickNode(double step, double autoAdd)
{
    if (_balance.empty())
    {
        return 0;
    }

    for (size_t i = 0; i < _balance.size(); ++i)
    {
        if (!_balance[i].active)
        {
            continue;
        }
        if (_idx >= _balance.size() || !_balance[_idx].active || _balance[_idx].weight - step > _balance[i].weight)
        {
            _idx = (int)i;
        }
    }
    if (_idx >= _balance.size() || !_balance[_idx].active)
    {
        return 0;
    }
    _balance[_idx].weight += autoAdd;
    _balance[_idx].count += 1;
    return _balance[_idx].id;
}

template<class BalanceID>
inline double Balance<BalanceID>::getBalanceDeviation()
{
    double light = 1E100;
    double weight = -1E100;
    for (size_t i = 0; i < _balance.size(); ++i)
    {
        if(!_balance[i].active) continue;
        if(_balance[i].weight < light)
        {
            light = _balance[i].weight;
        }
        if (_balance[i].weight > weight)
        {
            weight = _balance[i].weight;
        }
    }
    return weight - light;
}

template<class BalanceID>
inline std::string Balance<BalanceID>::getBalanceStatus()
{
    std::stringstream ss;
    ss << "[balaceDeviation:" << getBalanceDeviation() << "], node/active/weight/count";
    for (size_t i= 0; i < _balance.size(); ++i)
    {
        ss << "[";
        ss << _balance[i].id;
        ss << "/";
        ss << _balance[i].active;
        ss << "/";
        ss << _balance[i].weight;
        ss << "/";
        ss << _balance[i].count;
        ss << "],";
    }
    return ss.str();
}



#endif
