#include "userManager.h"
#include "dbManager.h"
#include "mission/eventTrigger.h"
#include <ProtoCommon.h>
using namespace zsummer::mysql;
using namespace zsummer::network;

UserManager::UserManager()
{
}

bool UserManager::init()
{
	auto checkTable = DBManager::getRef().infoQuery("desc tb_user");
	if (checkTable->getErrorCode() != QEC_SUCCESS)
	{
		LOGI("create talbe tb_user ");
		DBQuery q("CREATE TABLE `tb_user` ( "
			"`uID` bigint(20) unsigned NOT NULL, "
			"PRIMARY KEY(`uID`) "
			") ENGINE = MyISAM DEFAULT CHARSET = utf8");
		checkTable = DBManager::getRef().infoQuery(q.genSQL());
		if (checkTable->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create talbe tb_user error=" << checkTable->getLastError());
			return false;
		}
	}
	//版本升级自动alter add 新字段. 
	DBManager::getRef().infoQuery("alter table `tb_user` add `nickname` varchar(255) NOT NULL DEFAULT ''");
	DBManager::getRef().infoQuery("alter table `tb_user` add `iconID` smallint(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_user` add `diamond` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_user` add `giftDiamond` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_user` add `historyDiamond` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_user` add `joinTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00'");

	//加载所有用户数据
	UserID curID = 0;
	do
	{
		DBQuery q("select uID, nickname, iconID, diamond, giftDiamond, historyDiamond, joinTime from tb_user where uID >? limit 1000;");
		q.add(curID);
		auto result = DBManager::getRef().infoQuery(q.genSQL());
		if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
		{
			LOGE("loadUserInfo error. begin uID is " << curID << ",  sql error=" << result->getLastError());
			return false;
		}
		if (!result->haveRow())
		{
			//all already loaded.
			LOGD("all tb_user is already loaded.");
			break;
		}
		while (result->haveRow())
		{
			UserInfo info;
			*result >> info.uID;
			*result >> info.nickName;
			*result >> info.iconID;
			*result >> info.diamond;
			*result >> info.giftDiamond;
			*result >> info.hisotryDiamond;
			*result >> info.joinTime;
			if (info.uID == InvalidUserID)
			{
				continue;
			}
			if (info.uID > curID)
			{
				curID = info.uID;
			}

			auto founder = _mapUser.find(info.uID);
			if (founder != _mapUser.end())
			{
				LOGE("loadUserInfo  the user be aready loaded. uID=" << info.uID);
				continue;
			}
			auto inner = std::make_shared<InnerUserInfo>();
			inner->userInfo = info;
			_mapUser.insert(std::make_pair(info.uID, inner));
			_mapNickName.insert(std::make_pair(info.nickName, inner));
		}

	} while (true);


	return true;
}


std::shared_ptr<InnerUserInfo> UserManager::getInnerUserInfoBySID(SessionID sid)
{
	auto founder = _mapSession.find(sid);
	if (founder != _mapSession.end())
	{
		return founder->second;
	}
	return std::shared_ptr<InnerUserInfo>();
}

std::shared_ptr<InnerUserInfo> UserManager::getInnerUserInfoByUID(UserID uID)
{
	auto founder = _mapUser.find(uID);
	if (founder != _mapUser.end())
	{
		return founder->second;
	}
	return std::shared_ptr<InnerUserInfo>();
}

std::shared_ptr<InnerUserInfo> UserManager::getInnerUserInfoByNickName(const std::string & nickName)
{
	auto founder = _mapNickName.find(nickName);
	if (founder != _mapNickName.end())
	{
		return founder->second;
	}
	return std::shared_ptr<InnerUserInfo>();
}


void UserManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo, bool newUser)
{
	_mapSession[innerInfo->sesionInfo.sID] = innerInfo;
	if (newUser)
	{
		_mapUser[innerInfo->userInfo.uID] = innerInfo;
		_mapNickName[innerInfo->userInfo.nickName] = innerInfo;
	}
    

    EventTrigger::getRef().trigger(ETRIGGER_USER_LOGIN, innerInfo->userInfo.uID, 1);
}

void UserManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{
	SessionManager::getRef().kickSession(innerInfo->sesionInfo.sID);
	_mapSession.erase(innerInfo->sesionInfo.sID);
	innerInfo->sesionInfo = SessionInfo();
}





