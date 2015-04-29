#include "userManager.h"
#include "dbManager.h"
#include "mission/eventTrigger.h"
#include <ProtoCommon.h>
#include <ProtoCommonSQL.h>

using namespace zsummer::mysql;
using namespace zsummer::network;


UserManager::UserManager()
{
}

bool UserManager::init()
{
	auto build = UserInfo_BUILD();
	if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
	{
		if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create table error. sql=" << build[1]);
			return false;
		}
	}

	for (size_t i = 2; i < build.size(); i++)
	{
		DBManager::getRef().infoQuery(build[i]);
	}

	
	
	//加载所有用户数据
	unsigned long long curID = 0;
	do
	{
		auto sql = UserInfo_LOAD(curID);
		auto result = DBManager::getRef().infoQuery(sql);
		if (result->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("load contact error. curID:" << curID << ", err=" << result->getLastError());
			return false;
		}
		if (!result->haveRow())
		{
			break;
		}
		auto mapInfo = UserInfo_FETCH(result);
		for (auto & kv : mapInfo)
		{
			auto inner = std::make_shared<InnerUserInfo>();
			inner->userInfo = kv.second;
			_mapUser.insert(std::make_pair(kv.first, inner));
			_mapNickName.insert(std::make_pair(kv.second.nickName, inner));
		}
		curID += mapInfo.size();
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

void UserManager::addUser(std::shared_ptr<InnerUserInfo> innerInfo)
{
	_mapSession[innerInfo->sesionInfo.sID] = innerInfo;
	_mapUser[innerInfo->userInfo.uID] = innerInfo;
	_mapNickName[innerInfo->userInfo.nickName] = innerInfo;
}
void UserManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo)
{
    EventTrigger::getRef().trigger(ETRIGGER_USER_LOGIN, innerInfo->userInfo.uID, 1, innerInfo->userInfo.iconID, innerInfo->userInfo.nickName);
}

void UserManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{
	SessionManager::getRef().kickSession(innerInfo->sesionInfo.sID);
	_mapSession.erase(innerInfo->sesionInfo.sID);
	innerInfo->sesionInfo = SessionInfo();
	EventTrigger::getRef().trigger(ETRIGGER_USER_LOGOUT, innerInfo->userInfo.uID, 1, innerInfo->userInfo.iconID, innerInfo->userInfo.nickName);
}





