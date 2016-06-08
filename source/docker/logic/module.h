/*
 * zsummerX License
 * -----------
 *
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 *
 *
 * ===============================================================================
 *
 * Copyright (C) 2010-2016 YaweiZhang <yawei.zhang@foxmail.com>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ===============================================================================
 *
 * (end of COPYRIGHT)
 */

#ifndef BREEZE_MODULE_H_
#define BREEZE_MODULE_H_
#include <common.h>
#include "service.h"
#include <ProtoDBService.h>


//ModuleData用于存储和管理必须存在并且唯一的数据.
//初始化必须携带key等数据, 该类会自动去数据库中select出对应数据,如果不存在则自动创建.
//比如玩家的基础数据,经验,等级,角色名,登录时间,钻石等
template<class DBData>
class ModuleData
{
public:
    ModuleData(){}
    virtual ~ModuleData(){};
public:
    //必须在default填充key内容, 否则无法自动创建或者自动加载  
    bool loadFromDB(ServicePtr service, const DBData & defaultData, std::function<void(bool)>);
    void writeToDB(std::function<void(bool)> cb = nullptr);
public:
    DBData _data;
private:
    void onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
    void onAffectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
private:
    ServiceWeakPtr _weakPtr;
};



//ModuleMultiData用于存储和管理一些数据集, 这些数据可以不存在,也可以存在多份.
//这类数据因为存在多key,或者只有一个通用的id为key, 因此无法智能筛选出用户的想要的数据, 也因此初始化时候要提供SQL语句.
//初始化的SQL语句可以通过工具生成的通用select语句追加自定义where语句来达到尽可能向后兼容的通用代码.
//比如属于玩家的道具,宠物,伙伴,英雄,任务,成就等
template<class DBData>
class ModuleMultiData
{
public:
    ModuleMultiData() {}
    virtual ~ModuleMultiData() {};
public:
    //sql通过协议工具生成的getDBSelectPure产生并手动追加where语句生成.
    bool loadFromDB(ServicePtr service, const std::string & sql, std::function<void(bool)>);
    //update和insert不会变更_data的数据,纯方法 
    void updateToDB(const DBData & data, std::function<void(bool, const DBData & data)> cb = nullptr);
    void insertToDB(const DBData & data, std::function<void(bool, const DBData & data)> cb = nullptr);
public:
    std::vector<DBData> _data;
private:
    void onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
    void onAffectFromDB(ReadStream & rs, ServicePtr service, const DBData & data, std::function<void(bool, const DBData & data)>);
private:
    ServiceWeakPtr _weakPtr;
};











template<class DBData>
bool ModuleData<DBData>::loadFromDB(ServicePtr service, const DBData & defaultData, std::function<void(bool)> cb)
{
    _weakPtr = service;
    _data = defaultData;
    SQLQueryReq req(_data.getDBSelect());
    service->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onSelectFromDB, this, _1, service, cb));
    return true;
}

template<class DBData>
void ModuleData<DBData>::writeToDB(std::function<void(bool)> cb)
{
    ServicePtr guard = _weakPtr;
    if (!guard)
    {
        return;
    }
    SQLQueryReq req(_data.getDBUpdate());
    guard->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onAffectFromDB, this, _1, guard, cb));
}

template<class DBData>
void ModuleData<DBData>::onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS)
    {
        LOGE("ModuleData<DBData>::onSelectFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc
            << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
        if (cb)
        {
            cb(false);
        }
        return;
    }
    DBResult result;
    result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
    if (result.haveRow())
    {
        if (!_data.fetchFromDBResult(result))
        {
            LOGE("ModuleData<DBData>::onSelectFromDB fetchFromDBResult error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc 
                << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg );
            if (cb)
            {
                cb(false);
            }
            return;
        }
        if (cb)
        {
            cb(true);
        }
    }
    else
    {
        SQLQueryReq req(_data.getDBInsert());
        service->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onAffectFromDB, this, _1, service, cb));
    }
}

template<class DBData>
void ModuleData<DBData>::onAffectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS )
    {
        LOGE("ModuleData<DBData>::onAffectFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc
            << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
        if (cb)
        {
            cb(false);
        }
        return;
    }
    if (resp.result.affected == 0)
    {
        LOGW("ModuleData<DBData>::onAffectFromDB warning. no affect. retCode=" << resp.retCode << ", querry code=" << resp.result.qc 
            << ", querry affect=" << resp.result.affected << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
    }
    if (resp.result.affected > 2)
    {
        LOGW("ModuleData<DBData>::onAffectFromDB warning.  more affect line . retCode=" << resp.retCode << ", querry code=" << resp.result.qc 
            << ", querry affect=" << resp.result.affected << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
    }
    if (cb)
    {
        cb(true);
    }
}



template<class DBData>
bool ModuleMultiData<DBData>::loadFromDB(ServicePtr service, const std::string & sql, std::function<void(bool)> cb)
{
    _weakPtr = service;
    SQLQueryReq req(sql);
    service->toService(ServiceInfoDBMgr, req, std::bind(&ModuleMultiData<DBData>::onSelectFromDB, this, _1, service, cb));
    return true;
}

template<class DBData>
void ModuleMultiData<DBData>::onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS)
    {
        LOGE("ModuleMultiData<DBData>::onSelectFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc
            << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
        if (cb)
        {
            cb(false);
        }
        return;
    }
    DBResult result;
    result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
    while (result.haveRow())
    {
        DBData data;
        if (!data.fetchFromDBResult(result))
        {
            LOGE("ModuleMultiData<DBData>::onSelectFromDB fetchFromDBResult error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc
                << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
            if (cb)
            {
                cb(false);
            }
            return;
        }
        _data.push_back(data);
    }
    if (cb)
    {
        cb(true);
    }
}

template<class DBData>
void ModuleMultiData<DBData>::updateToDB(const DBData & data, std::function<void(bool, const DBData & data)> cb)
{
    ServicePtr guard = _weakPtr;
    if (!guard)
    {
        return;
    }
    SQLQueryReq req(data.getDBUpdate());
    guard->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onAffectFromDB, this, _1, guard, data, cb));
}

template<class DBData>
void ModuleMultiData<DBData>::insertToDB(const DBData & data, std::function<void(bool, const DBData & data)> cb)
{
    ServicePtr guard = _weakPtr;
    if (!guard)
    {
        return;
    }
    SQLQueryReq req(data.getDBInsert());
    guard->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onAffectFromDB, this, _1, guard, data, cb));
}



template<class DBData>
void ModuleMultiData<DBData>::onAffectFromDB(ReadStream & rs, ServicePtr service, const DBData & data, std::function<void(bool, const DBData & data)>  cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS)
    {
        LOGE("ModuleMultiData<DBData>::onAffectFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc
            << ", sql=" << resp.result.sql << ", err msg=" << resp.result.errMsg);
        if (cb)
        {
            cb(false, data);
        }
        return;
    }
    if (cb)
    {
        cb(true, data);
    }
}





#endif


