#include "netMgr.h"
#include "dbMgr.h"




DBMgr::DBMgr()
{
    _infoDB = std::make_shared<DBHelper>();
    _logDB = std::make_shared<DBHelper>();
    _dbAsync = std::make_shared<DBAsync>();
    _dbLogAsync = std::make_shared<DBAsync>();
}
DBMgr::~DBMgr()
{
    
}

bool DBMgr::stop(std::function<void()> onSafeClosed)
{
    _onSafeClosed = onSafeClosed;
    if (_dbAsync->getFinalCount() != _dbAsync->getPostCount()
        || _dbLogAsync->getFinalCount() != _dbLogAsync->getPostCount())
    {
        SessionManager::getRef().createTimer(500, std::bind(&DBMgr::_checkSafeClosed, this));
    }
    else
    {
        SessionManager::getRef().post(std::bind(&DBMgr::_checkSafeClosed, this));
    }
    return true;
}

void DBMgr::_checkSafeClosed()
{
    if (_dbAsync->getFinalCount() != _dbAsync->getPostCount()
        || _dbLogAsync->getFinalCount() != _dbLogAsync->getPostCount())
    {
        SessionManager::getRef().createTimer(1000, std::bind(&DBMgr::_checkSafeClosed, this));
        LOGA("Waiting the db data to store. waiting count=" << _dbAsync->getPostCount() - _dbAsync->getFinalCount()
             << "  waiting write to log db:" <<  _dbLogAsync->getPostCount() - _dbLogAsync->getFinalCount());
        return;
    }
    
    LOGA("_dbAsync finish count=" << _dbAsync->getFinalCount() << "  _dbLogAsync finish count=:" << _dbLogAsync->getFinalCount());
    
    _infoDB->stop();
    _logDB->stop();
    _dbAsync->stop();
    _dbLogAsync->stop();
    
    if (_onSafeClosed)
    {
        _onSafeClosed();
        _onSafeClosed = nullptr;
    }
}

bool DBMgr::start()
{
    //启动db异步操作线程
    if (!_dbAsync->start())
    {
        return false;
    }
    LOGI("DBAsync started.  begin connect to db ...");
    
    //创建DBHelper
    //////////////////////////////////////////////////////////////////////////
/*    {
        const auto infoConfig = ServerConfig::getRef().getDBConfig(InfoDB);
        const auto logConfig = ServerConfig::getRef().getDBConfig(LogDB);
        _infoDB->init(infoConfig._ip, infoConfig._port, infoConfig._db, infoConfig._user, infoConfig._pwd);
        _logDB->init(logConfig._ip, logConfig._port, logConfig._db, logConfig._user, logConfig._pwd);

        if (!_infoDB->connect())
        {
            LOGE("connect Info DB false. db config=" << infoConfig);
            return false;
        }
        LOGI("connect Info DB success. db config=" << infoConfig);

        if (!_logDB->connect())
        {
            LOGE("connect Log DB false. db config=" << logConfig);
            return false;
        }
        LOGI("connect Log DB success. db config=" << logConfig);
    }
    */
    return true;
}

