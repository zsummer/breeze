#include "netManager.h"
#include "dbManager.h"
using namespace zsummer::mysql;

DBManager::DBManager()
{
	_authDB = std::make_shared<DBHelper>();
	_infoDB = std::make_shared<DBHelper>();
	_logDB = std::make_shared<DBHelper>();
	_dbAsync = std::make_shared<DBAsync>();
}
DBManager::~DBManager()
{
	
}

bool DBManager::stop()
{
	// 	_authDB->stop();
	// 	_infoDB->stop();
	// 	_logDB->stop();
	while (_dbAsync->getFinalCount() != _dbAsync->getPostCount())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	_authDB->stop();
	_infoDB->stop();
	_logDB->stop();
	_dbAsync->stop();
	return true;
}
bool DBManager::start()
{
	//启动db异步操作线程
	if (!_dbAsync->start())
	{
		return false;
	}
	
	//创建DBHelper
	//////////////////////////////////////////////////////////////////////////
	LOGI("DBAsync start success.  begin connect to db ...");
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
		LOGI("connect Auth DB success. db config=" << authConfig);

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

	

	return true;
}

