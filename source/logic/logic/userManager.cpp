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
	auto tb = UserInfo_BUILD();
	for (auto & m : tb)
	{
		DBManager::getRef().infoQuery(m);
	}
	
	//加载所有用户数据
	unsigned long long curIndex = 0;
	do
	{
		auto result = DBManager::getRef().infoQuery(UserInfo_LOAD(curIndex));
		curIndex += 1000;
		if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
		{
			LOGE("loadUserInfo error. begin curIndex is " << curIndex << ",  sql error=" << result->getLastError());
			return false;
		}
		if (!result->haveRow())
		{
			//all already loaded.
			LOGD("all tb_UserInfo is already loaded.");
			break;
		}

		auto ret = UserInfo_FETCH(result);
		for (auto & kv : ret)
		{
			auto inner = std::make_shared<InnerUserInfo>();
			inner->userInfo = kv.second;
			_mapUser.insert(std::make_pair(kv.first, inner));
			_mapNickName.insert(std::make_pair(kv.second.nickName, inner));
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
	EventTrigger::getRef().trigger(ETRIGGER_USER_LOGOUT, innerInfo->userInfo.uID, 1, innerInfo->userInfo.iconID, innerInfo->userInfo.nickName);
}





