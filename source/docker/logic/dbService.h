
/*
* breeze License
* Copyright (C) 2016 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
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





#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_
#include <common.h>
#include "service.h"




class DBService : public Service
{
public:
    DBService();
    ~DBService();
    bool onLoad() override final;
    void onClientChange() override final;
    void onUnload() override final;
    void onTick(TimerID tID, ui32 count, ui32 repeat) override final;
    bool onBuildDB();
public:
    void onDBQueryReq(Tracing trace, ReadStream &rs);
    void onAsyncDBQueryReq(DBResultPtr result, Tracing trace);
    void onDBQueryArrayReq(Tracing trace, ReadStream &rs);
    void onAsyncDBQueryArrayReq(bool ret, std::vector<DBResultPtr> results, Tracing trace);

    void onTest(ReadStream & rs);
    template<class T>
    bool buildDB();
public:
    zsummer::mysql::DBResultPtr query(const std::string &sql);
public:

private:
    std::string _db;
    DBHelperPtr _dbHelper;
    DBAsyncPtr _dbAsync;
    time_t _lastTime = getNowTime();
private:
    void _checkSafeDestroy();
};





template<class T>
bool DBService::buildDB()
{
    DBResultPtr ret;
    const auto & builds = T().getDBBuild();

    for (auto iter = builds.begin(); iter != builds.end(); iter++)
    {
        ret = _dbHelper->query(*iter);
        if (ret->getErrorCode() != QEC_SUCCESS)
        {
            if (iter == builds.begin())
            {
                LOGE("create table error. error=" << ret->getErrorMsg() << ", sql=" << ret->peekSQL());
                return false;
            }
            else if (ret->getErrorMsg().find("1060") == std::string::npos)
            {
                LOGE("alter filed error. error=" << ret->getErrorMsg() << ", sql=" << ret->peekSQL());
                return false;
            }
        }
    }
    return true;
}































#endif
