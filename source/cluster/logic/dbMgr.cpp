#include "application.h"
#include "dbMgr.h"




DBBase::DBBase() 
{
    _dbAsync = std::make_shared<DBAsync>();
}

DBBase::~DBBase()
{
    
}
bool DBBase::init(const std::string & db)
{
    _db = db;
    const auto & dbConfigs = ServerConfig::getRef().getDBConfig();
    for (const auto & dbConfig : dbConfigs)
    {
        if (dbConfig._name != db)
        {
            continue;
        }
        _dbHelper = std::make_shared<DBHelper>();
        _dbHelper->init(dbConfig._ip, dbConfig._port, dbConfig._db, dbConfig._user, dbConfig._pwd);
       if (!_dbHelper->connect())
       {
           return false;
       }
       break;
    }
    if (!_dbHelper)
    {
        return false;
    }
    return true;
}
bool DBBase::start()
{
    if (!_dbHelper)
    {
        return false;
    }
    if (!_dbAsync->start())
    {
        return false;
    }
    ClusterServiceInited inited(getEntityName());
    Application::getRef().broadcast(inited);
    return true;
}


bool DBBase::stop(std::function<void()> onSafeClosed)
{
    _onSafeClosed = onSafeClosed;
    SessionManager::getRef().createTimer(500, std::bind(&DBBase::_checkSafeClosed, this));
    return true;
}

void DBBase::_checkSafeClosed()
{
    if (_dbAsync->getFinalCount() != _dbAsync->getPostCount())
    {
        SessionManager::getRef().createTimer(600, std::bind(&DBBase::_checkSafeClosed, this));
        LOGA("Waiting the db data to store. waiting count=" << _dbAsync->getPostCount() - _dbAsync->getFinalCount());
        return;
    }
    LOGA("_dbAsync finish count=" << _dbAsync->getFinalCount() );
    
    _dbAsync->stop();

    if (_onSafeClosed)
    {
        _onSafeClosed();
        _onSafeClosed = nullptr;
    }
}


static void defaultAsyncHandler(zsummer::mysql::DBResultPtr ptr)
{
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS)
    {
        LOGE("_defaultAsyncHandler error. msg=" << ptr->getLastError() << ", org sql=" << ptr->sqlString());
    }
}
void DBBase::asyncQuery(const std::string &sql, const std::function<void(zsummer::mysql::DBResultPtr)> & handler)
{
    _dbAsync->asyncQuery(_dbHelper, sql, handler);
}
void DBBase::asyncQuery(const std::string &sql)
{
    asyncQuery(sql, defaultAsyncHandler);
}
zsummer::mysql::DBResultPtr DBBase::query(const std::string &sql)
{
    return _dbHelper->query(sql);
}



