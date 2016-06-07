
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

/*
*  file desc
*  asynchronous operate db via multi-thread.
*  利用线程异步化DB操作。
*  
*/


#ifndef _DB_ASNYNC_H_
#define _DB_ASNYNC_H_
#include <defined.h>
#include <single.h>
#include <config.h>
#include <proto4z/dbHelper.h>
#include <zsummerX/zsummerX.h>

class DBAsync
{
public:
    DBAsync();
    ~DBAsync();
    bool start();
    bool stop();
    bool isStoped();
public:

    //无论mysql遇到任何错误, 在当前服务节点关闭时, Post出去的请求数量肯定和Final的完成数量相等.
    inline unsigned long long getPostCount(){ return _uPostCount.load(); }
    inline unsigned long long getFinalCount(){ return _uFinalCount.load(); }
public:
    //调用该接口把sql语句的执行丢进另外一个线程中执行.
    //执行完毕后会在主线程中执行回调函数.
    void asyncQuery(DBHelperPtr &dbhelper, const std::string &sql,
        const std::function<void(DBResultPtr)> & handler);
    void asyncQueryArray(DBHelperPtr &dbhelper, const std::vector<std::string> &sqls,
        const std::function<void(bool, std::vector<DBResultPtr>)> & handler);

protected:
    void _asyncQuery(DBHelperPtr &dbhelper, const std::string &sql,
        const std::function<void(DBResultPtr)> & handler);
    void _asyncQueryArray(DBHelperPtr &dbhelper, const std::vector<std::string> &sqls,
        const std::function<void(bool, std::vector<DBResultPtr>)> & handler);
    inline void run();
private:
    std::shared_ptr<std::thread> _thread;
    zsummer::network::EventLoopPtr _event;
    bool _bRuning = false;
    bool _bClosed = false;
    std::atomic_ullong _uPostCount;
    std::atomic_ullong _uFinalCount;
};
typedef std::shared_ptr<DBAsync> DBAsyncPtr;





template<class Org, class MapOrg, class PageKey>
class StorageHelper
{
public:
    inline MapOrg & getMapOrg(){ return _alldata; }
    inline bool hadMapOrg(){ return _hadAlldata; }
    inline Org & getOrg(){ return _data; }    
    inline bool hadOrg(){ return _hadData; }

public:
    std::function<MapOrg(DBResultPtr)> _fetchAllFunction;
    std::function<bool (DBResultPtr, Org & info)> _fetchFunction;
    std::function<PageKey(const MapOrg & curMap, PageKey lastKey)> _fetchNextKeyFunction;
private:
    MapOrg _alldata;
    bool _hadAlldata = false;
    Org _data;
    bool _hadData = false;
    std::vector<std::string> _buildSql; //0 desc, 1 create, 2,3,4, alter
    std::string _loadSql;
    std::string _selectSql;
    std::string _updateSql;
    std::string _insertSql;

    PageKey _lastKey;
    bool _needInsert = true;
    bool _dirty = false; //set diry  when need insert or need update when inserting or updating.
};










#endif
