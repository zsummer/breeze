

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

bool DBDict::finish()
{
    if (true)
    {
        AOESearch aoe;
        aoe.isRect = 0;
        aoe.value1 = 10;
        aoe.value2 = PI * 2;
        aoe.value3 = 0;
        aoe.clip = 0;
        aoe.compensate = 0;
        aoe.limitEntitys = 1;
        aoe.etype = ENTITY_NONE;
        aoe.filter = setBitFlag(setBitFlag(aoe.filter, FILTER_ENEMY_CAMP), FILTER_NEUTRAL_CAMP);
        aoe.id = 1; //player aos
        _dictOneKeyAOESearch[aoe.id] = aoe;

        aoe.value1 = 8;
        aoe.value2 = PI / 2;
        aoe.compensate = -3;
        aoe.clip = 2;
        aoe.limitEntitys = 1000;
        aoe.id = 2; //player aoe
        _dictOneKeyAOESearch[aoe.id] = aoe;



        aoe.isRect = 0;
        aoe.value1 = 10;
        aoe.value2 = PI * 2;
        aoe.value3 = 0;
        aoe.clip = 0;
        aoe.compensate = 0;
        aoe.limitEntitys = 1;
        aoe.etype = ENTITY_NONE;
        aoe.filter = setBitFlag(aoe.filter, FILTER_ENEMY_CAMP);
        aoe.id = 3; //walker aos
        _dictOneKeyAOESearch[aoe.id] = aoe;

        aoe.value1 = 6;
        aoe.value2 = PI / 2;
        aoe.compensate = -2;
        aoe.clip = 1.5;
        aoe.limitEntitys = 1000;
        aoe.id = 4; //walker aoe
        _dictOneKeyAOESearch[aoe.id] = aoe;


        aoe.isRect = 0;
        aoe.value1 = 10;
        aoe.value2 = PI * 2;
        aoe.value3 = 0;
        aoe.clip = 0;
        aoe.compensate = 0;
        aoe.limitEntitys = 1;
        aoe.etype = ENTITY_PLAYER;
        aoe.filter = setBitFlag(aoe.filter, FILTER_ENEMY_CAMP);
        aoe.id = 5; //monster aos
        _dictOneKeyAOESearch[aoe.id] = aoe;

        aoe.value1 = 6;
        aoe.value2 = PI / 2;
        aoe.compensate = -2;
        aoe.clip = 1.5;
        aoe.limitEntitys = 1000;
        aoe.id = 6; //monster aoe
        _dictOneKeyAOESearch[aoe.id] = aoe;
    }


    if (true)
    {
        DictSkill skill;
        skill.id = 1;
        skill.stamp = 0;
        skill.stamp = setBitFlag(skill.stamp, SKILL_NORMAL, true);
        skill.stamp = setBitFlag(skill.stamp, SKILL_PHYSICAL, true);
        skill.stamp = setBitFlag(skill.stamp, SKILL_HARM, true);
        skill.interval = 3.0;
        skill.aosType = 3;
        skill.aosID = 1;
        skill.aoeID = 2;
        _dictOneKeyDictSkill[skill.id] = skill;

        skill.aosID = 3;
        skill.aoeID = 4;
        skill.id = 3;
        _dictOneKeyDictSkill[skill.id] = skill; //walker  

        skill.aosID = 5;
        skill.aoeID = 6;
        skill.id = 5;
        _dictOneKeyDictSkill[skill.id] = skill; //monster  
    }



    for(auto &kv : _dictOneKeyDictSkill)
    {
        if  (kv.second.aosID != InvalidDictID)
        {
            auto  aos = getOneKeyAOESearch(kv.second.aosID);
            if (!aos.first)
            {
                LOGE("DBDict finish dict check error. not found aos dict. skillID=" << kv.second.aosID);
                return false;
            }
            kv.second.aosDict = aos.second;
        }
        if  (kv.second.aoeID != InvalidDictID)
        {
            auto  aoe = getOneKeyAOESearch(kv.second.aoeID);
            if (!aoe.first)
            {
                LOGE("DBDict finish dict check error. not found aoe dict. skillID=" << kv.second.aosID);
                return false;
            }
            kv.second.aoeDict = aoe.second;
        }

    }
    return true;
}


















