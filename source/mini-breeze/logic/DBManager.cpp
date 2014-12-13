#include "NetManager.h"
#include "DBManager.h"
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


	_authDB->init(ServerConfig::getRef().getAuthDBConfig());
	_infoDB->init(ServerConfig::getRef().getInfoDBConfig());
	_logDB->init(ServerConfig::getRef().getLogDBConfig());

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
void DBManager::charLogin(std::shared_ptr<InnerCharInfo> iinfoPtr)
{

}
void DBManager::charLogout(std::shared_ptr<InnerCharInfo> iinfoPtr)
{

}
