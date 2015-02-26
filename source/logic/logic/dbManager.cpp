#include "netManager.h"
#include "dbManager.h"
using namespace zsummer::mysql;

DBManager::DBManager()
{
	_authDB = std::make_shared<DBHelper>();
	_infoDB = std::make_shared<DBHelper>();
	_logDB = std::make_shared<DBHelper>();
}
DBManager::~DBManager()
{
	DBAsync::getRef().stop();
	_authDB->stop();
	_infoDB->stop();
	_logDB->stop();
}

bool DBManager::init()
{

	if (!DBAsync::instantiate()->start())
	{
		LOGE("DBAsync start false. ");
		return false;
	}
	LOGI("DBAsync start success.  begin connect to db ...");

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
	return true;
}
void DBManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo)
{

}
void DBManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{

}
