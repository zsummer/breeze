/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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


#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <common.h>
#include <utls.h>
#include <ProtoCommon.h>
#include <ProtoClient.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneServer.h>
#include <ProtoSceneClient.h>
#include <rvo2/RVO.h>

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RVO::Vector2 & v)
{
    stm << "[" << v.x() << "," << v.y() << "]";
    return stm;
}


inline EPosition operator + (const EPosition & dst, const EPosition & org)
{
    return EPosition(dst.x + org.x, dst.y + org.y);
}
inline EPosition operator - (const EPosition & dst, const EPosition & org)
{
    return EPosition(dst.x - org.x, dst.y - org.y);
}
inline EPosition operator * (const EPosition & dst, const EPosition & org)
{
    return EPosition(dst.x * org.x, dst.y * org.y);
}
inline EPosition operator / (const EPosition & dst, const EPosition & org)
{
    return EPosition(dst.x / org.x, dst.y * org.y);
}
inline EPosition operator + (const EPosition & dst, double val)
{
    return EPosition(dst.x + val, dst.y + val);
}
inline EPosition operator - (const EPosition & dst, double val)
{
    return EPosition(dst.x - val, dst.y - val);
}
inline EPosition operator * (const EPosition & dst, double val)
{
    return EPosition(dst.x * val, dst.y * val);
}
inline EPosition operator / (const EPosition & dst, double val)
{
    return EPosition(dst.x / val, dst.y * val);
}
inline EPosition normalize(const EPosition & dst)
{
    if (std::abs(dst.x) > std::abs(dst.y))
    {
        return EPosition(dst.x / dst.x, dst.y / dst.x);
    }
    return EPosition(dst.x / dst.y, dst.y / dst.y);
}



inline RVO::Vector2 toRVOVector2(const EPosition & pos)
{
    return RVO::Vector2(pos.x, pos.y);
}
inline EPosition toEPoint(const RVO::Vector2 & pos)
{
    return EPosition(pos.x(), pos.y());
}
inline double getDistance(const EPosition& pos1, const EPosition & pos2)
{
    return getDistance(pos1.x, pos1.y, pos2.x, pos2.y);
}
struct EntityControl //EntityControl  
{
    unsigned long long eid = InvalidEntityID;
    unsigned long long agentNo = -1; //agentNo. -1为无效  
    double stateChageTime = 0.0;
    EPosition spawnpoint; //出生点
    SkillInfoArray skills; //技能数据  
    BuffInfoArray buffs; //BUFF数据, 小标ID对应bufftype  
    double diedTime = 1E128; //实体死亡时间点 仅飞行道具类有效  
    ui64 hitTimes = -1; //实体碰撞, 仅飞行道具类有效  
    double blockMoveCount = 0; //移动被阻次数 
    EPosition lastClientPos; //最后一次客户端提交的坐标
};

inline EntityProp processPropGrow(const EntityProp & fixedProps, const EntityProp & growProps, const EntityProp & growth, double level)
{
    EntityProp ret;
    ret.hp = fixedProps.hp + growProps.hp * pow(level, growth.hp);
    ret.hpRegen = fixedProps.hpRegen + growProps.hpRegen * pow(level, growth.hpRegen);
    ret.attack = fixedProps.attack + growProps.attack * pow(level, growth.attack);
    ret.defense = fixedProps.defense + growProps.defense * pow(level, growth.defense);
    ret.crit = fixedProps.crit + growProps.crit * pow(level, growth.crit);
    ret.toughness = fixedProps.toughness + growProps.toughness * pow(level, growth.toughness);
    ret.moveSpeed = fixedProps.moveSpeed + growProps.moveSpeed * pow(level, growth.moveSpeed);
    ret.attackSpeed = fixedProps.attackSpeed + growProps.attackSpeed * pow(level, growth.attackSpeed);
    ret.vampirk = fixedProps.vampirk + growProps.vampirk * pow(level, growth.vampirk);
    return ret;
}
inline EntityProp addPropGrow(const EntityProp & props1, const EntityProp & props2)
{
    EntityProp ret;
    ret.hp = props1.hp + props2.hp;
    ret.hpRegen = props1.hpRegen + props2.hpRegen;
    ret.attack = props1.attack + props2.attack;
    ret.defense = props1.defense + props2.defense;
    ret.crit = props1.crit + props2.crit;
    ret.toughness = props1.toughness + props2.toughness;
    ret.moveSpeed = props1.moveSpeed + props2.moveSpeed;
    ret.attackSpeed = props1.attackSpeed + props2.attackSpeed;
    ret.vampirk = props1.vampirk + props2.vampirk;
    return ret;
}

class Entity
{
public:
    Entity();
    ~Entity();
    double getSpeed();
    double getSuckBlood();
    double getAttack();
    EntityFullData getFullData();
    EntityBase _baseInfo;
    EntityProp _fixedProps;
    EntityProp _growProps;
    EntityProp _growth;
    EntityProp _props;
    EntityInfo  _entityInfo;
    EntityMove  _entityMove;
    EntityControl _control;
    EntityReport _report;
    SessionID _clientSessionID = InvalidSessionID;
    bool _isInfoDirty = false;
    bool _isMoveDirty = false;
};

using EntityPtr = std::shared_ptr<Entity>;


































#endif
