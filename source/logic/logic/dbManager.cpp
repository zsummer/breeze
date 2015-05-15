#include "netManager.h"
#include "dbManager.h"




DBManager::DBManager()
{
	_authDB = std::make_shared<DBHelper>();
	_infoDB = std::make_shared<DBHelper>();
	_logDB = std::make_shared<DBHelper>();
	_dbAsync = std::make_shared<DBAsync>();
    _dbLogAsync = std::make_shared<DBAsync>();
}
DBManager::~DBManager()
{
	
}

bool DBManager::stop(std::function<void()> onSafeClosed)
{
    _onSafeClosed = onSafeClosed;
    if (_dbAsync->getFinalCount() != _dbAsync->getPostCount()
        || _dbLogAsync->getFinalCount() != _dbLogAsync->getPostCount())
    {
        SessionManager::getRef().createTimer(500, std::bind(&DBManager::_checkSafeClosed, this));
    }
    else
    {
        SessionManager::getRef().post(std::bind(&DBManager::_checkSafeClosed, this));
    }
	return true;
}

void DBManager::_checkSafeClosed()
{
    if (_dbAsync->getFinalCount() != _dbAsync->getPostCount()
        || _dbLogAsync->getFinalCount() != _dbLogAsync->getPostCount())
    {
        SessionManager::getRef().createTimer(1000, std::bind(&DBManager::_checkSafeClosed, this));
        LOGA("Waiting the db data to store. waiting count=" << _dbAsync->getPostCount() - _dbAsync->getFinalCount()
             << "  waiting write to log db:" <<  _dbLogAsync->getPostCount() - _dbLogAsync->getFinalCount());
        return;
    }
    
    LOGA("_dbAsync finish count=" << _dbAsync->getFinalCount() << "  _dbLogAsync finish count=:" << _dbLogAsync->getFinalCount());
    
    _authDB->stop();
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

bool DBManager::start()
{
	//启动db异步操作线程
	if (!_dbAsync->start())
	{
		return false;
	}
	LOGD("DBAsync start success.  begin connect to db ...");
	
	//创建DBHelper
	//////////////////////////////////////////////////////////////////////////
	{
		const auto authConfig = ServerConfig::getRef().getDBConfig(AuthDB);
		const auto infoConfig = ServerConfig::getRef().getDBConfig(InfoDB);
		const auto logConfig = ServerConfig::getRef().getDBConfig(LogDB);
		_authDB->init(authConfig._ip, authConfig._port, authConfig._db, authConfig._user, authConfig._pwd);
		_infoDB->init(infoConfig._ip, infoConfig._port, infoConfig._db, infoConfig._user, infoConfig._pwd);
		_logDB->init(logConfig._ip, logConfig._port, logConfig._db, logConfig._user, logConfig._pwd);

		if (!_authDB->connect())
		{
			LOGE("connect Auth DB false. db config=" << authConfig);
			return false;
		}
		LOGD("connect Auth DB success. db config=" << authConfig);

		if (!_infoDB->connect())
		{
			LOGE("connect Info DB false. db config=" << infoConfig);
			return false;
		}
		LOGD("connect Info DB success. db config=" << infoConfig);

		if (!_logDB->connect())
		{
			LOGE("connect Log DB false. db config=" << logConfig);
			return false;
		}
		LOGD("connect Log DB success. db config=" << logConfig);
	}

	return true;
}

