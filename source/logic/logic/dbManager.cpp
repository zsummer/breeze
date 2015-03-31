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

	//////////////////////////////////////////////////////////////////////////
	
	{
		auto ret = DBManager::getRef().getInfoDB()->query("desc tb_user");
		if (ret->getErrorCode() != QEC_SUCCESS)
		{
			LOGI("create talbe tb_user ");
			DBQuery q("CREATE TABLE `tb_user` ( "
				"`uid` bigint(20) unsigned NOT NULL, "
				"`nickname` varchar(255) NOT NULL DEFAULT '', "
				"`iconID` smallint(10) NOT NULL DEFAULT '0', "
				"`diamond` int(10) NOT NULL DEFAULT '0', "
				"`giftDiamond` int(10) NOT NULL DEFAULT '0', "
				"`historyDiamond` int(10) NOT NULL DEFAULT '0', "
				"`joinTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00', "
				"PRIMARY KEY(`uid`) "
				") ENGINE = MyISAM DEFAULT CHARSET = utf8");
			ret = DBManager::getRef().getInfoDB()->query(q.genSQL());
			if (ret->getErrorCode() != QEC_SUCCESS)
			{
				LOGE("create talbe tb_user error=" << ret->getLastError());
				return false;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	
	{
		//加载所有用户数据
		UserID curID = 0;
		do
		{
			DBQuery q("select uid, nickname, iconID, diamond, giftDiamond, historyDiamond, joinTime from tb_user where uid >? limit 1000;");
			q.add(curID);
			auto result = _infoDB->query(q.genSQL());
			if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
			{
				LOGE("loadUserInfo error. begin uid is " << curID << ",  sql error=" << result->getLastError());
				return false;
			}
			if (!result->haveRow())
			{
				//all already loaded.
				break;
			}
			while (result->haveRow())
			{
				UserInfo info;
				std::string friends;
				std::string bag;
				*result >> info.uid;
				*result >> info.nickName;
				*result >> info.iconID;
				*result >> info.diamond;
				*result >> info.giftDiamond;
				*result >> info.hisotryDiamond;
				*result >> info.joinTime;
				curID = info.uid;
				NetManager::getRef().loadUserInfo(info);
			}

		} while (true);

	}
	

	return true;
}
void DBManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo)
{

}
void DBManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{

}
