#include "application.h"
#include "dbService.h"
#include <ProtoDBService.h>



DBService::DBService() 
{
    _dbAsync = std::make_shared<DBAsync>();
    slotting<SQLQueryReq>(std::bind(&DBService::onSQLQueryReq, this, _1, _2)); //sloting都是同步调用 不需要shared_from_this
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
        LOGA("DBService [" << ServiceNames.at(getServiceType()) << "], finish count=" << _dbAsync->getFinalCount() << "post count=" << _dbAsync->getPostCount());
    }
}

void DBService::_checkSafeClosed()
{
    if (_dbAsync->isStoped())
    {
        setWorked(false);
        LOGA("_dbAsync finish count=" << _dbAsync->getFinalCount() << "post count=" << _dbAsync->getPostCount());
        return;
    }
    else
    {
        SessionManager::getRef().createTimer(500, std::bind(&DBService::_checkSafeClosed, this));
    }
}

void DBService::onStop()
{
    _dbAsync->stop();
    _checkSafeClosed();
}

bool DBService::onInit()
{
    const auto & dbConfigs = ServerConfig::getRef().getDBConfig();
    for (const auto & dbConfig : dbConfigs)
    {
        if (dbConfig._name != ServiceNames.at(getServiceType()))
        {
            continue;
        }
        _dbHelper = std::make_shared<DBHelper>();
        _dbHelper->init(dbConfig._ip, dbConfig._port, dbConfig._db, dbConfig._user, dbConfig._pwd);
       if (!_dbHelper->connect())
       {
           LOGE("DBService::onInit [" << ServiceNames.at(getServiceType()) << "] connect error");
           return false;
       }
       break;
    }
    if (!_dbHelper)
    {
        LOGE("DBService::onInit [" << ServiceNames.at(getServiceType()) << "] error. not found config");
        return false;
    }
    if (!_dbAsync->start())
    {
        LOGE("DBService::onInit [" << ServiceNames.at(getServiceType()) << "] error. start db thread error");
        return false;
    }

    setWorked(true);

    if (getServiceType() == ServiceInfoDBMgr)
    {
        WriteStream ws(SQLQueryReq::GetProtoID());
        SQLQueryReq req;
        req.sql = "select 1";
        ws << req;
        globalCall(ServiceDictDBMgr, InvalidServiceID, ws.getStream(), ws.getStreamLen(), std::bind(&DBService::onTest, std::static_pointer_cast<DBService>(shared_from_this()), _1));
    }
    

    return true;
}


static void defaultAsyncHandler(zsummer::mysql::DBResultPtr ptr)
{
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS)
    {
        LOGE("_defaultAsyncHandler error. msg=" << ptr->getErrorMsg() << ", org sql=" << ptr->peekSQL());
    }
}


void DBService::asyncQuery(const std::string &sql, const std::function<void(zsummer::mysql::DBResultPtr)> & handler)
{
    _dbAsync->asyncQuery(_dbHelper, sql, handler);
}
void DBService::asyncQuery(const std::string &sql)
{
    asyncQuery(sql, defaultAsyncHandler);
}
zsummer::mysql::DBResultPtr DBService::query(const std::string &sql)
{
    return _dbHelper->query(sql);
}




void DBService::onSQLQueryReq(Tracing trace, ReadStream &rs)
{
    SQLQueryReq req;
    rs >> req;
    asyncQuery(req.sql, std::bind(&DBService::onAsyncSQLQueryReq, std::static_pointer_cast<DBService>(shared_from_this()), _1, trace));

}

void DBService::onAsyncSQLQueryReq(DBResultPtr result, Tracing trace)
{
    SQLQueryResp resp;
    resp.retCode = EC_SUCCESS;
    resp.result.qc = result->getErrorCode();
    resp.result.errMsg = result->getErrorMsg();
    resp.result.sql = result->peekSQL();
    resp.result.affected = result->getAffectedRows();
    resp.result.fields = std::move(result->popResult());
    WriteStream ws(SQLQueryResp::GetProtoID());
    ws << resp;
    backCall(trace, ws.getStream(), ws.getStreamLen(), nullptr);
}

void DBService::onTest(ReadStream & rs)
{
    SQLQueryResp resp;
    rs >> resp;
    DBResult result;
    LOGD("onTest qc=" << resp.result.qc << ", errMSG=" << resp.result.errMsg << ", affected=" << resp.result.affected << ", fields=" << resp.result.fields.size());
    result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
}





