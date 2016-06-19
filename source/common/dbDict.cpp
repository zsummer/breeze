

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



bool DBDict::buildDictTable()
{
    buildDict<DictGlobal>(_dictHelper);
    buildDict<DictRafflePool>(_dictHelper);
    buildDict<DictFightEffect>(_dictHelper);
    buildDict<DictItem>(_dictHelper);
    return true;
}


bool DBDict::initHelper()
{
    auto dbconfigs = ServerConfig::getRef().getDBConfig();
    auto founder = std::find_if(dbconfigs.begin(), dbconfigs.end(), [](const DBConfig & config) {return config._name == "STDictDBMgr"; });
    if (founder == dbconfigs.end())
    {
        LOGE("STDictDBMgr not found");
        return false;
    }
    _dictHelper = std::make_shared<DBHelper>();
    _dictHelper->init(founder->_ip, founder->_port, founder->_db, founder->_user, founder->_pwd, true);
    if (!_dictHelper->connect())
    {
        LOGE("can't connect mysql STDictDBMgr. config=" << *founder);
        return false;
    }
    return true;
}


bool DBDict::load()
{
    if (!fetchDict<DictGlobal>(_dictHelper, [this](const DictGlobal & dict)
    {
        _dictGlobal[dict.id] = dict;
    }))
    {
        LOGE("fetchDict DictGlobal error");
        return false;
    }


    if (!fetchDict<DictRafflePool>(_dictHelper, [this](const DictRafflePool & dict)
    {
        _dictRafflePool[dict.id] = dict;
        RaffleAward award;
        for (auto & tp : splitArrayString<unsigned int, unsigned int, double>(dict.poolString, ",", "|", " "))
        {
            award.id = std::get<0>(tp);
            award.weight = std::get<1>(tp);
            award.probability = std::get<2>(tp);
            _dictRafflePool[dict.id].pool.push_back(award);
        }
    }))
    {
        LOGE("fetchDict DictRafflePool error");
        return false;
    }


    if (!fetchDict<DictFightEffect>(_dictHelper, [this](const DictFightEffect & dict)
    {
        _dictFightEffect[dict.id] = dict;
    }))
    {
        LOGE("fetchDict DictFightEffect error");
        return false;
    }


    if (!fetchDict<DictItem>(_dictHelper, [this](const DictItem & dict)
    {
        _dictItem[dict.id] = dict;
    }))
    {
        LOGE("fetchDict DictItem error");
        return false;
    }

    return true;
}













