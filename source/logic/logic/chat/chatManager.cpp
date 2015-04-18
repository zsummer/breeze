#include "chatManager.h"
#include "../userManager.h"
#include "../dbManager.h"
using namespace zsummer::mysql;
#include <ProtoCommon.h>
#include <ProtoCommonSQL.h>
#include <ProtoChatSQL.h>
using namespace zsummer::mysql;
using namespace zsummer::network;

ChatManager::ChatManager()
{
}

bool ChatManager::init()
{
	auto build = ContactInfo_BUILD();
	if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
	{
		if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create table error. sql=" <<build[1]);
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
		auto sql = ContactInfo_LOAD(curID);
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
		auto mapInfo = ContactInfo_FETCH(result);
		_mapContact.insert(mapInfo.begin(), mapInfo.end());
		curID += mapInfo.size();
	} while (true);

	EventTrigger::getRef().watching(ETRIGGER_USER_LOGIN, std::bind(&ChatManager::onUserLogin, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
	EventTrigger::getRef().watching(ETRIGGER_USER_LOGOUT, std::bind(&ChatManager::onUserLogout, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
	return true;
}


void  ChatManager::onUserLogin(EventTriggerID tID, UserID uID, unsigned long long count, unsigned long long iconID, std::string nick)
{
	bool haveChange = false;
	auto founder = _mapContact.find(uID);
	if (founder == _mapContact.end())
	{
		ContactInfo info;
		info.uID = uID;
		haveChange = true;
		_mapContact[uID] = info;
		updateContact(info, true, false);
		founder = _mapContact.find(uID);
	}
	if (founder->second.nickName != nick)
	{
		founder->second.nickName = nick;
		haveChange = true;
	}
	if (founder->second.iconID != iconID)
	{
		founder->second.iconID = (short)iconID;
		haveChange = true;
	}
	updateContact(founder->second, haveChange, true);
}
void  ChatManager::onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string)
{
	auto founder = _mapContact.find(uID);
	if (founder != _mapContact.end())
	{
		founder->second.onlineFlag = false;
		updateContact(founder->second, false, true);
	}
}

void ChatManager::updateContact(const ContactInfo & info, bool writedb, bool broadcast)
{
	if (writedb)
	{
		auto sql = ContactInfo_UPDATE(info);
		if (!sql.empty())
		{
			DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::onUpdateContact, this, std::placeholders::_1));
		}
	}
	
	//broadcast
	if (broadcast)
	{
		WriteStream ws(ID_GetContactInfoAck);
		ws << EC_SUCCESS << info;
		for (auto &kv : info.friends)
		{
			if (kv.flag == FRIEND_ESTABLISHED)
			{
				auto ptr = UserManager::getRef().getInnerUserInfoByUID(kv.uid);
				if (ptr && ptr->sesionInfo.sID != InvalidSeesionID)
				{
					SessionManager::getRef().sendOrgSessionData(ptr->sesionInfo.sID, ws.getStream(), ws.getStreamLen());
				}
			}
		}
		auto ptr = UserManager::getRef().getInnerUserInfoByUID(info.uID);
		if (ptr && ptr->sesionInfo.sID != InvalidSeesionID)
		{
			SessionManager::getRef().sendOrgSessionData(ptr->sesionInfo.sID, ws.getStream(), ws.getStreamLen());
		}
	}
}



void ChatManager::onUpdateContact(zsummer::mysql::DBResultPtr result)
{
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("onUpdateContact error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
	}
}

void ChatManager::msg_onGetContactInfoReq(SessionID sID, ProtoID pID, ReadStream & rs)
{

}
void ChatManager::msg_onGetFriendListReq(SessionID sID, ProtoID pID, ReadStream & rs)
{

}
void ChatManager::msg_onFriendOperationReq(SessionID sID, ProtoID pID, ReadStream & rs)
{

}
void ChatManager::msg_onChatReq(SessionID sID, ProtoID pID, ReadStream & rs)
{

}