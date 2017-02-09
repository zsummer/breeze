

/*
* breeze License
* Copyright (C) 2014-2016 YaweiZhang <yawei.zhang@foxmail.com>.
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

#include "dbDict.h"
#include "config.h"
#include "utls.h"



DBHelperPtr buildHelper(const std::string & db)
{
    auto dbconfigs = ServerConfig::getRef().getDBConfig();
    auto founder = std::find_if(dbconfigs.begin(), dbconfigs.end(), [db](const DBConfig & config) {return config._name == db; });
    if (founder == dbconfigs.end())
    {
        LOGE(db << " not found");
        return nullptr;
    }
    auto helper = std::make_shared<DBHelper>();
    helper->init(founder->_ip, founder->_port, founder->_db, founder->_user, founder->_pwd, true);
    if (!helper->connect())
    {
        LOGE("can't connect mysql " << db << ",  config=" << *founder);
        return nullptr;
    }
    return helper;
}

bool DBDict::fakeTestData()
{
    if (true)
    {
        DictProp prop;
        prop.id = 1;
        prop.attack = 200;
        prop.hp = 10000;
        prop.hpRegen = 20;
        prop.moveSpeed = 6.0;
        prop.attackSpeed = 2;
        _dictOneKeyDictProp[prop.id] = prop; // player base prop 

        prop.id = 2;
        prop.hp /= 2.0;
        prop.attackSpeed /= 2.0;
        prop.moveSpeed = 4.0;
        prop.attackSpeed = 3.0;
        _dictOneKeyDictProp[prop.id] = prop; // ai base prop


        prop = DictProp();
        prop.id = 3;
        prop.hp = 2000;
        prop.hpRegen = 200;
        _dictOneKeyDictProp[prop.id] = prop; // hp regen buff prop

        prop = DictProp();
        prop.id = 4;
        prop.attack = 500;
        _dictOneKeyDictProp[prop.id] = prop; // attack buff prop 
    }
    if (true)
    {
        AOESearch s;
        s.id = 1; 
        s.etype = ENTITY_NONE; // all type
        s.camp = 0;
        s.camp = setBitFlag(s.camp, 2, 1); //敌方
        s.camp = setBitFlag(s.camp, 3, 1); //包括中立
        s.distance = 10.0;
        s.radian = PI*2.0; 
        s.isRect = 0; //radian
        s.limitEntitys = 1;
        s.offsetX = 0.0;
        s.offsetY = 0.0;
        _dictOneKeyAOESearch[s.id] = s; // 360度索敌

        s.id = 2; 
        s.distance = 5.0;
        s.radian = PI/2.0;
        s.limitEntitys = 100;
        s.offsetY = -1.0;
        s.offsetX = -1.0;
        s.distance += 1;
        _dictOneKeyAOESearch[s.id] = s; //90度扇形伤害

        s.id = 3; 
        s.limitEntitys = 1;
        _dictOneKeyAOESearch[s.id] = s;//90度扇形伤害 限制一个敌人 


        s.id = 4; 
        s.distance = 5.0;
        s.radian = 2.0;
        s.limitEntitys = 10;
        s.offsetY = -1.0;
        s.offsetX = -1.0;
        s.distance += 1;
        _dictOneKeyAOESearch[s.id] = s;//长5,宽2, 修正长+1  长方形伤害 

        s.id = 5; 
        s.limitEntitys = 1;
        _dictOneKeyAOESearch[s.id] = s;//长5,宽2, 修正长+1  长方形伤害 限制1个敌人 
    }
    if (true)
    {
        DictSkillBehaviour bhr;
        bhr.id = 1;
        bhr.isHit = true;
        bhr.propID = 4;
        _dictOneKeyDictSkillBehaviour[bhr.id] = bhr;  //攻击, 携带额外属性

        bhr.id = 2;
        bhr.isHit = false;
        bhr.propID = 0;
        bhr.buffs.push_back(1);
        _dictOneKeyDictSkillBehaviour[bhr.id] = bhr; //攻击, 触发buff

        bhr.id = 3;
        bhr.buffs.clear();
        bhr.buffs.push_back(2);
        _dictOneKeyDictSkillBehaviour[bhr.id] = bhr;//攻击 触发双buff
    }
    if (true)
    {
        DictSkill skill;
        skill.id = 1;
        skill.stamp = 0;
        skill.stamp = setBitFlag(skill.stamp, SKILL_AUTO_USE, true);
        skill.stamp = setBitFlag(skill.stamp, SKILL_PHYSICAL, true);
        skill.cd = 0;
        skill.effects.push_back(DictPairValue(200, 1));
        _dictOneKeyDictSkill[skill.id] = skill;

        skill.stamp = setBitFlag(skill.stamp, SKILL_AUTO_USE, false);

        skill.id = 2;
        skill.effects.clear();
        skill.effects.push_back(DictPairValue(0, 2));
        _dictOneKeyDictSkill[skill.id] = skill;

        skill.id = 3;
        skill.effects.clear();
        skill.effects.push_back(DictPairValue(0,3));
        _dictOneKeyDictSkill[skill.id] = skill;

    }
    if (true)
    {
        DictBuffEffect effect;
        effect.id = 1;
        effect.propID = 2; //move
        _dictOneKeyDictBuffEffect[effect.id] = effect;
        effect.id = 1;
        effect.propID = 3; //hp
        _dictOneKeyDictBuffEffect[effect.id] = effect;
    }
    if (true)
    {
        DictBuff buff;
        buff.id = 1;
        buff.effects.push_back(1);
        buff.keepTime = 10;
        buff.limitStackTime = 20;
        buff.stamp = 0;
        buff.stamp = setBitFlag(buff.stamp, BUFF_BUFF, true);
        _dictOneKeyDictBuff[buff.id] = buff;

        buff.id = 2;
        buff.effects.push_back(2); // 1&2
        buff.keepTime = 10;
        buff.limitStackTime = 20;
        buff.stamp = 0;
        buff.stamp = setBitFlag(buff.stamp, BUFF_BUFF, true);
        _dictOneKeyDictBuff[buff.id] = buff;

    }

    if (true)
    {
        DictModel model;
        model.modelID = 1;
        model.modelName = "avatar";
        model.initCamp = 0;
        model.initLevel = 1;
        model.modelRedius = 1.0;
        model.initState = ENTITY_STATE_ACTIVE;
        _dictOneKeyDictModel[model.modelID] = model;

        model.modelID = 2;
        model.modelName = "野";
        model.initCamp = 0;
        model.initLevel = 1;
        model.initState = ENTITY_STATE_ACTIVE;
        _dictOneKeyDictModel[model.modelID] = model;
    }
    if (true)
    {
        DictModelLevel level;
        level.levelID = 1;
        level.modelID = 1;
        level.needExp = 1000;
        level.propID = 1;
        level.skills.push_back(1);
        level.skills.push_back(2);
        level.skills.push_back(3);
        level.skills.push_back(4);
        _dictTwoKeyDictModelLevel[level.modelID][level.levelID] = level;

        level.modelID = 2;
        level.propID = 3;
        level.skills.clear();
        level.skills.push_back(1);
        _dictTwoKeyDictModelLevel[level.modelID][level.levelID] = level;
    }
    return true;
}


















