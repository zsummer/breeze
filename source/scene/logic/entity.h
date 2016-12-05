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

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RVO::Vector2 & v){stm << "[" << v.x() << "," << v.y() << "]";return stm;}
inline EPosition operator + (const EPosition & dst, const EPosition & org){return EPosition(dst.x + org.x, dst.y + org.y);}
inline EPosition operator - (const EPosition & dst, const EPosition & org){return EPosition(dst.x - org.x, dst.y - org.y);}
inline EPosition operator * (const EPosition & dst, const EPosition & org){return EPosition(dst.x * org.x, dst.y * org.y);}
inline EPosition operator / (const EPosition & dst, const EPosition & org){return EPosition(dst.x / org.x, dst.y * org.y);}
inline EPosition operator + (const EPosition & dst, double val){return EPosition(dst.x + val, dst.y + val);}
inline EPosition operator - (const EPosition & dst, double val){return EPosition(dst.x - val, dst.y - val);}
inline EPosition operator * (const EPosition & dst, double val){return EPosition(dst.x * val, dst.y * val);}
inline EPosition operator / (const EPosition & dst, double val){return EPosition(dst.x / val, dst.y * val);}
inline EPosition normalize(const EPosition & dst){if (std::abs(dst.x) > std::abs(dst.y)){return EPosition(dst.x / dst.x, dst.y / dst.x);}return EPosition(dst.x / dst.y, dst.y / dst.y);}
inline RVO::Vector2 toRVOVector2(const EPosition & pos){return RVO::Vector2(pos.x, pos.y);}
inline EPosition toEPoint(const RVO::Vector2 & pos){return EPosition(pos.x(), pos.y());}
inline double getDistance(const EPosition& pos1, const EPosition & pos2){return getDistance(pos1.x, pos1.y, pos2.x, pos2.y);}
inline EntityProp operator + (const EntityProp & ep1, const EntityProp & ep2);
inline EntityProp operator * (const EntityProp & ep1, const EntityProp & ep2);
inline EntityProp operator * (const EntityProp & ep, double df);



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
    EntityProp _baseProps;
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
































inline EntityProp operator + (const EntityProp & ep1, const EntityProp & ep2)
{
    EntityProp ret;
    ret.hp = ep1.hp + ep2.hp;
    ret.hpRegen = ep1.hpRegen + ep2.hpRegen;
    ret.attack = ep1.attack + ep2.attack;
    ret.defense = ep1.defense + ep2.defense;
    ret.crit = ep1.crit + ep2.crit;
    ret.toughness = ep1.toughness + ep2.toughness;
    ret.moveSpeed = ep1.moveSpeed + ep2.moveSpeed;
    ret.attackSpeed = ep1.attackSpeed + ep2.attackSpeed;
    ret.vampirk = ep1.vampirk + ep2.vampirk;
    return ret;
}

inline EntityProp operator * (const EntityProp & ep1, const EntityProp & ep2)
{
    EntityProp ret;
    ret.hp = ep1.hp * ep2.hp;
    ret.hpRegen = ep1.hpRegen * ep2.hpRegen;
    ret.attack = ep1.attack * ep2.attack;
    ret.defense = ep1.defense * ep2.defense;
    ret.crit = ep1.crit * ep2.crit;
    ret.toughness = ep1.toughness * ep2.toughness;
    ret.moveSpeed = ep1.moveSpeed * ep2.moveSpeed;
    ret.attackSpeed = ep1.attackSpeed * ep2.attackSpeed;
    ret.vampirk = ep1.vampirk * ep2.vampirk;
    return ret;
}
inline EntityProp operator * (const EntityProp & ep, double df)
{
    EntityProp ret;
    ret.hp = ep.hp * df;
    ret.hpRegen = ep.hpRegen * df;
    ret.attack = ep.attack * df;
    ret.defense = ep.defense * df;
    ret.crit = ep.crit * df;
    ret.toughness = ep.toughness * df;
    ret.moveSpeed = ep.moveSpeed * df;
    ret.attackSpeed = ep.attackSpeed * df;
    ret.vampirk = ep.vampirk * df;
    return ret;
}



#endif
