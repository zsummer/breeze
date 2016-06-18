#include "docker.h"
#include "dbService.h"
#include <ProtoDBService.h>
#include <ProtoOffline.h>


DBService::DBService() 
{
    _dbAsync = std::make_shared<DBAsync>();
    slotting<RefreshServiceToMgrNotice>([](Tracing, ReadStream &rs) {});
    slotting<DBQueryReq>(std::bind(&DBService::onDBQueryReq, this, _1, _2)); //不需要shared_from_this
    slotting<DBQueryArrayReq>(std::bind(&DBService::onDBQueryArrayReq, this, _1, _2)); //不需要shared_from_this
}

DBService::~DBService()
{
    
}

void DBService::onTick()
{
    time_t now = getNowTime();
    if (now - _lastTime > 60)
    {
        _lastTime = now;
        LOGA("DBService [" << getServiceName() << "], finish count=" << _dbAsync->getFinalCount() << "post count=" << _dbAsync->getPostCount());
    }
}

void DBService::_checkSafeDestroy()
{
    auto service = Docker::getRef().peekService(STUserMgr, InvalidServiceID);
    if (!service)
    {
        _dbAsync->stop();
        if (_dbAsync->isStoped())
        {
            LOGA("_dbAsync finish count=" << _dbAsync->getFinalCount() << "post count=" << _dbAsync->getPostCount());
            _dbHelper->stop();
            finishUnload();
            return;
        }
    }
    SessionManager::getRef().createTimer(500, std::bind(&DBService::_checkSafeDestroy, this));
}

void DBService::onUnload()
{
    _checkSafeDestroy();
}

void DBService::onClientChange()
{
    return ;
}

bool DBService::onLoad()
{
    const auto & dbConfigs = ServerConfig::getRef().getDBConfig();
    auto founder = std::find_if(dbConfigs.begin(), dbConfigs.end(), [this](const DBConfig & dbc){return dbc._name == getServiceName(); });
    if (founder == dbConfigs.end())
    {
        LOGE("DBService::onLoad [" << getServiceName() << "] error. not found config");
        Docker::getRef().forceStop();
        return false;
    }
    const auto & dbConfig = *founder;
    _dbHelper = std::make_shared<DBHelper>();
    _dbHelper->init(dbConfig._ip, dbConfig._port, dbConfig._db, dbConfig._user, dbConfig._pwd, true);
    if (!_dbHelper->connect())
    {
        LOGE("DBService::onLoad [" << getServiceName() << "] connect error");
        Docker::getRef().forceStop();
        return false;
    }

    if (!_dbAsync->start())
    {
        LOGE("DBService::onLoad [" << getServiceName() << "] error. start db thread error");
        Docker::getRef().forceStop();
        return false;
    }


    if (onBuildDB())
    {
        finishLoad();
        return true;
    }
    Docker::getRef().forceStop();
    return false;
}




bool DBService::onBuildDB()
{
    if (getServiceType() == STInfoDBMgr)
    {
        if (!buildDB<UserBaseInfo>())
        {
            return false;
        }
        if (!buildDB<UserOffline>())
        {
            return false;
        }
    }
    return true;
}





zsummer::mysql::DBResultPtr DBService::query(const std::string &sql)
{
    return _dbHelper->query(sql);
}




void DBService::onDBQueryReq(Tracing trace, ReadStream &rs)
{
    DBQueryReq req;
    rs >> req;
    _dbAsync->asyncQuery(_dbHelper, req.sql, std::bind(&DBService::onAsyncDBQueryReq, std::static_pointer_cast<DBService>(shared_from_this()), _1, trace));
}
void DBService::onDBQueryArrayReq(Tracing trace, ReadStream &rs)
{
    DBQueryArrayReq req;
    rs >> req;
    _dbAsync->asyncQueryArray(_dbHelper, req.sqls, std::bind(&DBService::onAsyncDBQueryArrayReq, std::static_pointer_cast<DBService>(shared_from_this()), _1, _2, trace));
}
void DBService::onAsyncDBQueryReq(DBResultPtr result, Tracing trace)
{
    DBQueryResp resp;
    resp.retCode = EC_SUCCESS;
    resp.result.qc = result->getErrorCode();
    resp.result.errMsg = result->getErrorMsg();
    resp.result.sql = result->peekSQL();
    resp.result.affected = result->getAffectedRows();
    resp.result.fields = std::move(result->popResult());
    backToService(trace, resp, nullptr);
}
void DBService::onAsyncDBQueryArrayReq(bool ret, std::vector<DBResultPtr> results, Tracing trace)
{
    DBQueryArrayResp resp;
    resp.retCode = ret ? EC_SUCCESS : EC_DB_ERROR;
    for (auto &result : results)
    {
        DBDataResult ret;
        ret.qc = result->getErrorCode();
        ret.errMsg = result->getErrorMsg();
        ret.sql = result->peekSQL();
        ret.affected = result->getAffectedRows();
        ret.fields = std::move(result->popResult());
        resp.results.push_back(std::move(ret));
    }
    backToService(trace, resp, nullptr);
}
void DBService::onTest(ReadStream & rs)
{
    DBQueryResp resp;
    rs >> resp;
    DBResult result;
    LOGA("----------------------- onTest qc=" << resp.result.qc << ", errMSG=" << resp.result.errMsg << ", affected=" << resp.result.affected << ", fields=" << resp.result.fields.size());
    result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
}





