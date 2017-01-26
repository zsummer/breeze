

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
        _dictOneKeyDictProp[prop.id] = prop;

        prop.id = 2;
        prop.hp /= 2.0;
        prop.attackSpeed /= 2.0;
        prop.moveSpeed = 4.0;
        prop.attackSpeed = 3.0;
        _dictOneKeyDictProp[prop.id] = prop;


        prop = DictProp();
        prop.id = 3;
        prop.hp = 2000;
        prop.hpRegen = 200;
        _dictOneKeyDictProp[prop.id] = prop;

        prop = DictProp();
        prop.id = 4;
        prop.attack = 500;
        _dictOneKeyDictProp[prop.id] = prop;
    }
    if (true)
    {
        AOESearch s;
        s.id = 1; //锁敌
        s.etype = ENTITY_NONE; // all type
        s.camp = 0;
        s.camp = setBitFlag(s.camp, 2, 1); //敌方
        s.camp = setBitFlag(s.camp, 3, 1); //包括中立
        s.distance = 10.0;
        s.radian = PI*2.0; //360度锁敌
        s.isRect = false; //radian
        s.limitEntitys = 1;
        s.offsetX = 0.0;
        s.offsetY = 0.0;
        _dictOneKeyAOESearch[s.id] = s;

        s.id = 2; //90度扇形伤害
        s.distance = 5.0;
        s.radian = PI/2.0;
        s.limitEntitys = 10;
        s.offsetY = -1.0;
        s.offsetX = -1.0;
        s.distance += 1;
        _dictOneKeyAOESearch[s.id] = s;

        s.id = 3; //90度扇形伤害 限制一个敌人
        s.limitEntitys = 1;
        _dictOneKeyAOESearch[s.id] = s;


        s.id = 4; //长5,宽2, 修正长+1  长方形伤害
        s.distance = 5.0;
        s.radian = 2.0;
        s.limitEntitys = 10;
        s.offsetY = -1.0;
        s.offsetX = -1.0;
        s.distance += 1;
        _dictOneKeyAOESearch[s.id] = s;

        s.id = 5; //长5,宽2, 修正长+1  长方形伤害 限制1个敌人
        s.limitEntitys = 1;
        _dictOneKeyAOESearch[s.id] = s;
    }
    if (true)
    {
        DictBuffEffect effect;
        effect.id = 1;
        effect.areaTrigger = 0.0;
        effect.autoUnloadBuff = 0.0;
        effect.intervalLimit = 0.0;

    }



}


















