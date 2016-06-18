

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



#ifndef _DB_DICT_H_
#define _DB_DICT_H_


#include "defined.h"
#include "single.h"
#include "dbAsync.h"
#include "utls.h"
#include <ProtoDict.h>

template<class Packet>
bool fetchDict(DBHelperPtr helper, std::function<void(const Packet &)>);

template<class Packet>
bool buildDict(DBHelperPtr helper);

#define DefaultDefineDict(dict) public: 


class DBDict : public Singleton<DBDict>
{
private:
    DBHelperPtr _dictHelper;
    std::map<ui32, DictGlobal> _dictGlobal;
    std::map<ui32, DictRafflePool> _dictRafflePool;
    std::map<ui32, DictFightEffect> _dictFightEffect;
    std::map<ui32, DictItem> _dictItem;

public:
    bool initHelper();

    inline bool buildDictTable()
    {
        buildDict<DictGlobal>(_dictHelper);
        buildDict<DictRafflePool>(_dictHelper);
        buildDict<DictFightEffect>(_dictHelper);
        buildDict<DictItem>(_dictHelper);
        return true;
    }


public:
    inline bool DBDict::load()
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

};










template<class Packet>
bool fetchDict(DBHelperPtr helper, std::function<void(const Packet &)> cb)
{
    auto sql = Packet().getDBSelectPure();
    int cursor = 0;
    DBResultPtr result;
    do
    {
        result = helper->query(sql + " limit " + toString(cursor) + ", 100");
        if(!result)
        {
            LOGE("fetchDict error. dict name=" << Packet::getProtoName());
            return false;
        }
        if (result->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("fetchDict error. dict name=" << Packet::getProtoName() << ", error=" << result->getErrorMsg());
            return false;
        }
        if (!result->haveRow())
        {
            break;
        }
        Packet pkt;
        while(result->haveRow())
        {
            auto ret = pkt.fetchFromDBResult(*result);
            if (!ret)
            {
                LOGE("fetchDict errror when fetchFromDBResult to packet. dict name=" << Packet::getProtoName());
                return false;
            }
            cb(pkt);
        }
    }while(true);
    return true;
}

template<class Packet>
bool buildDict(DBHelperPtr helper)
{
    auto sqls = Packet().getDBBuild();
    for (auto sql : sqls)
    {
        helper->query(sql);
    }
    return true;
}























#endif