

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
        _dictOneKeyDictProp[prop.id] = prop; // hp regen buff prop

        prop = DictProp();
        prop.id = 4;
        prop.attack = 500;
        _dictOneKeyDictProp[prop.id] = prop; // attack buff prop 
    }
    if (true)
    {

    }

    if (true)
    {
        DictSkill skill;
        skill.id = 1;
        skill.stamp = 0;
        skill.stamp = setBitFlag(skill.stamp, SKILL_AUTO_USE, true);
        skill.stamp = setBitFlag(skill.stamp, SKILL_PHYSICAL, true);
        skill.cd = 0;
        _dictOneKeyDictSkill[skill.id] = skill;

        skill.stamp = setBitFlag(skill.stamp, SKILL_AUTO_USE, false);

        skill.id = 2;
        _dictOneKeyDictSkill[skill.id] = skill;

        skill.id = 3;
        _dictOneKeyDictSkill[skill.id] = skill;

    }





    return true;
}


















