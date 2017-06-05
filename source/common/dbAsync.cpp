
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


#include "dbAsync.h"
using namespace zsummer::mysql;
using namespace zsummer::network;




DBAsync::DBAsync()
{
    _event = std::make_shared<zsummer::network::EventLoop>();
    _uFinalCount = 0;
    _uPostCount = 0;
}

DBAsync::~DBAsync()
{
    stop();
}

bool DBAsync::start()
{
    bool ret = _event->initialize();
    if (!ret)
    {
        return false;
    }
    if (_thread)
    {
        return false;
    }
    _bRuning = true;
    _uPostCount.store(0);
    _uFinalCount.store(0);
    _thread = std::shared_ptr<std::thread>(new std::thread(std::bind(&DBAsync::run, this)));
    return true;
}
bool DBAsync::stop()
{
    _bRuning = false;
    if (!_thread)
    {
        _bClosed = true;
    }
    return true;
}
bool DBAsync::isStoped() 
{
    if (!_bClosed)
    {
        return false;
    }
    _thread->join();
    return true;
}

void DBAsync::asyncQuery(DBHelperPtr &dbhelper, const std::string &sql,
    const std::function<void(DBResultPtr)> & handler)
{
    _uPostCount++;
    _event->post(std::bind(&DBAsync::_asyncQuery, this, dbhelper, sql, handler));
}
void DBAsync::asyncQueryArray(DBHelperPtr &dbhelper, const std::vector<std::string> &sqls,
    const std::function<void(bool, std::vector<DBResultPtr>)> & handler)
{
    _uPostCount++;
    _event->post(std::bind(&DBAsync::_asyncQueryArray, this, dbhelper, sqls, handler));
}

void DBAsync::_asyncQuery(DBHelperPtr &dbhelper, const std::string &sql,
    const std::function<void(DBResultPtr)> & handler)
{
    DBResultPtr ret = dbhelper->query(sql);
    _uFinalCount++;
    if (ret->getErrorCode() != QEC_SUCCESS)
    {
        LOGE("_asyncQuery MYSQL ERROR. sql=" << ret->peekSQL() << " $$$$  error msg=" << ret->getErrorMsg());
    }
    if (handler)
    {
        SessionManager::getRef().post(std::bind(handler, ret));
    }
}
void DBAsync::_asyncQueryArray(DBHelperPtr &dbhelper, const std::vector<std::string> &sqls,
    const std::function<void(bool, std::vector<DBResultPtr>)> & handler)
{
    bool isSuccess = true;
    std::vector<DBResultPtr> results;
    for (size_t i = 0; i < sqls.size(); i++)
    {
        DBResultPtr ret = std::make_shared<DBResult>();
        ret = dbhelper->query(sqls.at(i));
        if (ret->getErrorCode() != QEC_SUCCESS)
        {
            if (ret->getErrorCode() != QEC_SUCCESS)
            {
                LOGE("_asyncQueryArray MYSQL ERROR. sql=" << ret->peekSQL() << " $$$$  error msg=" << ret->getErrorMsg());
            }
            isSuccess = false;
        }
        results.push_back(ret);
    }
    _uFinalCount++;
    if (handler)
    {
        SessionManager::getRef().post(std::bind(handler, isSuccess, results));
    }
}

void DBAsync::run()
{
    do
    {
        if (!_bRuning && _uPostCount == _uFinalCount)
        {
            break;
        }
        try
        {
            _event->runOnce();
        }
        catch (const std::exception & e)
        {
            std::cout << "DBAsync::run error. e=" << e.what() << std::endl;
        }

    } while (true);
    _bClosed = true;
}















