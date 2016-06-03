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


template<class DBData>
class ModuleData
{
public:
    ModuleData(){}
    virtual ~ModuleData(){};
public:
    //必须在default填充key内容, 否则无法自动创建或者自动加载  
    bool initFromDB(ServicePtr service, const DBData & defaultData, std::function<void(bool)>);
    void writeToDB(std::function<void(bool)> cb = nullptr);
public:
    DBData _data;
private:
    void onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
    void onInsertFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
    void onUpdateFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
private:
    ServiceWeakPtr _weakPtr;
};

template<class DBData>
class ModuleMultiData
{
public:
    ModuleMultiData() {}
    virtual ~ModuleMultiData() {};
public:
    //sql必须和结构体对应 
    bool initFromDB(ServicePtr service, const std::string & sql, std::function<void(bool)>);
    //update和insert不会变更_data的数据,纯方法 
    void updateToDB(const DBData & data, std::function<void(bool, const DBData & data)> cb = nullptr);
    void insertToDB(const DBData & data, std::function<void(bool, const DBData & data)> cb = nullptr);
public:
    std::vector<DBData> _data;
private:
    void onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
    void onInsertFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
    void onUpdateFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
private:
    ServiceWeakPtr _weakPtr;
};










template<class DBData>
bool ModuleData<DBData>::initFromDB(ServicePtr service, const DBData & defaultData, std::function<void(bool)> cb)
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
    guard->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onUpdateFromDB, this, _1, guard, cb));
}

template<class DBData>
void ModuleData<DBData>::onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS)
    {
        LOGE("ModuleData<DBData>::onSelectFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc);
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
            LOGE("ModuleData<DBData>::onSelectFromDB fetchFromDBResult error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc);
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
        service->toService(ServiceInfoDBMgr, req, std::bind(&ModuleData<DBData>::onInsertFromDB, this, _1, service, cb));
    }
}

template<class DBData>
void ModuleData<DBData>::onInsertFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS || resp.result.affected != 1)
    {
        LOGE("ModuleData<DBData>::onInsertFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc);
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


template<class DBData>
void ModuleData<DBData>::onUpdateFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS || resp.result.affected != 1)
    {
        LOGE("ModuleData<DBData>::onUpdateFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc);
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


#endif


