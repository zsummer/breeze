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
class Module
{
public:
    Module(){}
    virtual ~Module(){};
public:
    bool initFromDB(ServicePtr service, std::function<void(bool)>);
    void writeToDB(std::function<void(bool)> callback = nullptr) {}
public:
    DBData _data;
private:
    void onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
//    void onInsertFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)>);
private:
    ServiceWeakPtr _weakPtr;
};


template<class DBData>
bool Module<DBData>::initFromDB(ServicePtr service, std::function<void(bool)> cb)
{
    _weakPtr = service;
    SQLQueryReq req(_data.getDBSelect());
    service->toService(ServiceInfoDBMgr, req, std::bind(&Module<DBData>::onSelectFromDB, this, _1, service, cb));
}

template<class DBData>
void Module<DBData>::onSelectFromDB(ReadStream & rs, ServicePtr service, std::function<void(bool)> cb)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS)
    {
        LOGE("Module<DBData>::onSelectFromDB error. retCode=" << resp.retCode << ", querry code=" << resp.result.qc);
        if (cb)
        {
            cb(false);
        }
        return;
    }
    DBResult result;
    result.buildResult(resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
/*    if (result.haveRow())
    {
        result >> _data;
    }
    else
    {

    }
    */
}





#endif


