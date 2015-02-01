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
		LOGE("DBManager start false. ");
		return false;
	}
	LOGI("DBManager start success. ");

	const auto authConfig = ServerConfig::getRef().getAuthDBConfig();
	const auto infoConfig = ServerConfig::getRef().getInfoDBConfig();
	const auto logConfig = ServerConfig::getRef().getLogDBConfig();
	_authDB->init(authConfig._ip, authConfig._port, authConfig._db, authConfig._user, authConfig._pwd);
	_infoDB->init(infoConfig._ip, infoConfig._port, infoConfig._db, infoConfig._user, infoConfig._pwd);
	_logDB->init(logConfig._ip, logConfig._port, logConfig._db, logConfig._user, logConfig._pwd);

	if (!_authDB->connect())
	{
		LOGE("connect Auth DB false. db config=" << ServerConfig::getRef().getAuthDBConfig());
		return false;
	}
	LOGI("connect Auth DB success. db config=" << ServerConfig::getRef().getAuthDBConfig());

	if (!_infoDB->connect())
	{
		LOGE("connect Info DB false. db config=" << ServerConfig::getRef().getInfoDBConfig());
		return false;
	}
	LOGI("connect Info DB success. db config=" << ServerConfig::getRef().getInfoDBConfig());

	if (!_logDB->connect())
	{
		LOGE("connect Log DB false. db config=" << ServerConfig::getRef().getLogDBConfig());
		return false;
	}
	LOGI("connect Log DB success. db config=" << ServerConfig::getRef().getLogDBConfig());
	return true;
}
void DBManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo)
{

}
void DBManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{

}
