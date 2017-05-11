

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
        AOESearch aoe;
        aoe.isRect = 0;
        aoe.distance = 20;
        aoe.value = 2 * PI;
        aoe.limitEntitys = 1;
        aoe.filter = setBitFlag(aoe.filter, FILTER_ENEMY_CAMP);
        aoe.id = 1;
        _dictOneKeyAOESearch[1] = aoe;

        aoe.distance = 7;
        aoe.value = PI / 18*12;
        aoe.id = 2;
        aoe.limitEntitys = 1000;
        _dictOneKeyAOESearch[aoe.id] = aoe;

        aoe.distance = 12;
        aoe.value = PI / 18 * 12;
        aoe.id = 3;
        aoe.limitEntitys = 1000;
        _dictOneKeyAOESearch[aoe.id] = aoe;
        
    }
    if (true)
    {
        DictSkill skill;
        skill.id = 1;
        skill.stamp = 0;
        skill.stamp = setBitFlag(skill.stamp, SKILL_AUTO_USE, true);
        skill.stamp = setBitFlag(skill.stamp, SKILL_PHYSICAL, true);
        skill.stamp = setBitFlag(skill.stamp, SKILL_HIT, true);
        skill.interval = 3.0;
        skill.orgType = 1;
        skill.aoeID = 3;
        skill.searchID = 1;
        _dictOneKeyDictSkill[skill.id] = skill;
        skill.aoeID = 2;
        skill.id = 2;
        _dictOneKeyDictSkill[skill.id] = skill; //ai 
    }





    return true;
}


















