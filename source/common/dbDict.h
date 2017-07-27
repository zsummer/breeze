

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



#ifndef _DB_DICT_H_
#define _DB_DICT_H_


#include "defined.h"
#include "single.h"
#include "dbAsync.h"
#include "utls.h"
#include <DictCommon.h>
#include <DictScene.h>
#include <ProtoCommon.h>
#include <ProtoSceneCommon.h>
#include <ProtoClient.h>
#include <ProtoDocker.h>
#include <LogCommon.h>

/*
服务器引擎的配置走数据库
该字典类提供方法自动化的, 同步方式的, 在起服时候从数据库拉取所有配置并进行构建.
所有service都可以直接通过单例直接查找配置并进行使用. 
*/



DBHelperPtr buildHelper(const std::string & db);
template<class Packet>
bool fetchDict(DBHelperPtr helper, std::function<void(const Packet &)>);
template<class Packet>
bool buildTable(DBHelperPtr helper);

#define LOAD_ONE_KEY_DICT(dt) if(!loadOneKey##dt()) return false; 

#define MAKE_ONE_KEY_DICT(dt, keytype, key) public: \
inline bool loadOneKey##dt() \
{ \
    if (!fetchDict<dt>(_dictHelper, [this](const dt & dict) \
    { \
        _dictOneKey##dt[dict.key] = dict; \
    })) \
    { \
        LOGE("fetchDict" #dt " error"); \
        return false; \
    } \
    return true; \
} \
inline const dt & getOneKey##dt##WithException(keytype k) \
{ \
    auto founder =  _dictOneKey##dt.find(k); \
    if (founder == _dictOneKey##dt.end()) \
        throw std::runtime_error("had exception when get" #dt "WithException not found key[" + toString(k) + "]"); \
    return founder->second; \
} \
inline std::pair<bool, dt>  getOneKey##dt(keytype k) \
{ \
    auto founder =  _dictOneKey##dt.find(k); \
    if (founder == _dictOneKey##dt.end()) \
        return std::make_pair(false, dt()); \
    return std::make_pair(true, founder->second); \
} \
inline const std::map<keytype, dt> &  peekOneKey##dt() \
{ \
    return  _dictOneKey##dt; \
} \
private: \
std::map<keytype, dt> _dictOneKey##dt 


#define LOAD_TWO_KEY_DICT(dt) if(!loadTwoKey##dt()) return false; 

#define MAKE_TWO_KEY_DICT(dt, keytype1, key1, keytype2, key2) public: \
inline bool loadTwoKey##dt() \
{ \
    if (!fetchDict<dt>(_dictHelper, [this](const dt & dict) \
    { \
        _dictTwoKey##dt[dict.key1][dict.key2] = dict; \
    })) \
    { \
        LOGE("fetchDict" #dt " error"); \
        return false; \
    } \
    return true; \
} \
inline const dt & getTwoKey##dt##WithException(keytype1 k1, keytype2 k2) \
{ \
    auto founder1 =  _dictTwoKey##dt.find(k1); \
    if (founder1 == _dictTwoKey##dt.end()) \
        throw std::runtime_error("had exception when get" #dt "WithException not found key1[" + toString(k1) + "][" + toString(k2) + "]"); \
    auto founder2 =  founder1->second.find(k2); \
    if (founder2 == founder1->second.end()) \
        throw std::runtime_error("had exception when get" #dt "WithException not found key2[" + toString(k1) + "][" + toString(k2) + "]"); \
    return founder2->second; \
} \
inline std::pair<bool, dt>  getTwoKey##dt(keytype1 k1, keytype2 k2) \
{ \
    auto founder1 =  _dictTwoKey##dt.find(k1); \
    if (founder1 == _dictTwoKey##dt.end()) \
        return std::make_pair(false, dt()); \
    auto founder2 =  founder1->second.find(k2); \
    if (founder2 == founder1->second.end()) \
        return std::make_pair(false, dt()); \
    return std::make_pair(true, founder2->second); \
} \
inline const std::map<keytype1, std::map<keytype2, dt> > &  peekTwoKey##dt() \
{ \
    return  _dictTwoKey##dt; \
} \
private: \
std::map<keytype1, std::map<keytype2, dt> > _dictTwoKey##dt 



class DBDict : public Singleton<DBDict>
{
public:
    inline bool buildDictTable()
    {
        auto helper = buildHelper("STDictDBMgr");
        if (!helper) return false;
        buildTable<DictGlobal>(helper);
        buildTable<DictDrop>(helper);
        buildTable<DictItem>(helper);
        buildTable<DictProp>(helper);
        buildTable<AOESearch>(helper);
        buildTable<DictBuff>(helper);
        buildTable<DictSkill>(helper);
        return true;
    }
    inline bool buildInfoTable()
    {
        auto helper = buildHelper("STInfoDBMgr");
        if (!helper) return false;
        buildTable<AvatarBaseInfo>(helper);
        buildTable<AvatarOffline>(helper);
        return true;
    }
    inline bool buildLogTable()
    {
        auto helper = buildHelper("STLogDBMgr");
        if (!helper) return false;
        buildTable<LogChat>(helper);
        buildTable<LogQuit>(helper);
        buildTable<LogLogin>(helper);
        return true;
    }

public:
    inline bool initHelper()
    {
        _dictHelper = buildHelper("STDictDBMgr");
        return !!_dictHelper;
    }
    inline bool load()
    {
        LOAD_ONE_KEY_DICT(DictGlobal);
        LOAD_ONE_KEY_DICT(DictDrop);
        LOAD_ONE_KEY_DICT(DictItem);
        LOAD_ONE_KEY_DICT(DictProp);

        LOAD_ONE_KEY_DICT(AOESearch);
        LOAD_ONE_KEY_DICT(DictBuff);
        LOAD_ONE_KEY_DICT(DictSkill);
        return finish();
    }
    bool finish();
    
    MAKE_ONE_KEY_DICT(DictGlobal, ui64, id);
    MAKE_ONE_KEY_DICT(DictDrop, ui64, id);
    MAKE_ONE_KEY_DICT(DictItem, ui64, id);
    MAKE_ONE_KEY_DICT(DictProp, ui64, id);
    MAKE_ONE_KEY_DICT(AOESearch, ui64, id);
    MAKE_ONE_KEY_DICT(DictBuff, ui64, id);
    MAKE_ONE_KEY_DICT(DictSkill, ui64, id);



private:
    DBHelperPtr _dictHelper;
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
        cursor+=100;
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
bool buildTable(DBHelperPtr helper)
{
    auto sqls = Packet().getDBBuild();
    for (auto sql : sqls)
    {
        helper->query(sql);
    }
    return true;
}























#endif