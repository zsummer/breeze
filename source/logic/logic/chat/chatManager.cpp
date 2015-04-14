#include "chatManager.h"
#include "../userManager.h"
#include "../dbManager.h"
using namespace zsummer::mysql;
#include <ProtoCommon.h>

using namespace zsummer::mysql;
using namespace zsummer::network;

ChatManager::ChatManager()
{
}

bool ChatManager::init()
{
	auto checkTable = DBManager::getRef().infoQuery("desc tb_friend");
	if (checkTable->getErrorCode() != QEC_SUCCESS)
	{
		LOGI("create talbe tb_friend ");
		DBQuery q("CREATE TABLE `tb_friend` ( "
			"`uID` bigint(20) unsigned NOT NULL, "
			"PRIMARY KEY(`uID`) "
			") ENGINE = MyISAM DEFAULT CHARSET = utf8");
		checkTable = DBManager::getRef().infoQuery(q.popSQL());
		if (checkTable->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create talbe tb_friend error=" << checkTable->getLastError());
			return false;
		}
	}
	//版本升级自动alter add 新字段. 
	DBManager::getRef().infoQuery("alter table `tb_friend` add `nickName` varchar(255) NOT NULL DEFAULT ''");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `iconID` smallint(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `banned` tinyint(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `totalBlacks` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `totalFriends` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `friends` blob");
	//加载所有用户数据
	UserID curID = 0;
	do
	{
		DBQuery q("select uID, nickName, iconID, banned, totalBlacks, totalFriends, friends from tb_friend where uID >? limit 1000;");
		q.add(curID);
		auto result = DBManager::getRef().infoQuery(q.popSQL());
		if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
		{
			LOGE("load friend error. begin uID is " << curID << ",  sql error=" << result->getLastError());
			return false;
		}
		if (!result->haveRow())
		{
			//all already loaded.
			LOGD("all tb_friend is already loaded.");
			break;
		}
		while (result->haveRow())
		{
			InnerContactInfo info;
			*result >> info.contact.uID;
			*result >> info.contact.nickName;
			*result >> info.contact.iconID;
			*result >> info.contact.banned;
			*result >> info.contact.totalBlacks;
			*result >> info.contact.totalFriends;
			info.contact.onlineFlag = false;
			std::string friends;
			friends.resize(1024);
			*result >> friends;

			try
			{
				if (!friends.empty())
				{

					ReadStream rs(friends.c_str(), (zsummer::proto4z::Integer)friends.length(), false);
					rs >> info.friends;
				}
			}
			catch (std::runtime_error re)
			{
				LOGE("when load user friend find one error. uID=" << info.contact.uID << " error=" << re.what());
			}

			_mapContact[info.contact.uID] = info;
			if (info.contact.uID > curID)
			{
				curID = info.contact.uID;
			}
			
		}

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
		InnerContactInfo info;
		info.contact.uID = uID;
		haveChange = true;
		_mapContact[uID] = info;
		updateContact(info, true, false);
		founder = _mapContact.find(uID);
	}
	if (founder->second.contact.nickName != nick)
	{
		founder->second.contact.nickName = nick;
		haveChange = true;
	}
	if (founder->second.contact.iconID != iconID)
	{
		founder->second.contact.iconID = (short)iconID;
		haveChange = true;
	}
	if (haveChange)
	{
		updateContact(founder->second, true, true);
	}
	else
	{
		updateContact(founder->second, false, true);
	}
}
void  ChatManager::onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string)
{
	auto founder = _mapContact.find(uID);
	if (founder != _mapContact.end())
	{
		founder->second.contact.onlineFlag = false;
		updateContact(founder->second, false, true);
	}
}

void ChatManager::updateContact(const InnerContactInfo & info, bool writedb, bool broadcast)
{
	if (writedb)
	{
		try
		{
			WriteStream wsFriends(0);
			wsFriends << info.friends;
			DBQuery q("insert into tb_friend(uID) values(?) on duplicate key update nickName=?, iconID=?, banned=?,  totalBlacks=?, totalFriends=?, friends=?;");
			q.add(info.contact.uID);
			q.add(info.contact.nickName);
			q.add(info.contact.iconID);
			q.add(info.contact.banned);
			q.add(info.contact.totalBlacks);
			q.add(info.contact.totalFriends);
			q.add(wsFriends.getStreamBody(), wsFriends.getStreamBodyLen());

			DBManager::getRef().infoAsyncQuery(q.popSQL(), std::bind(&ChatManager::onUpdateContact, this, std::placeholders::_1));
		}
		catch (...)
		{
			LOGE("updateContact failed");
			return;
		}
	}
	


	//broadcast
	if (broadcast)
	{
		WriteStream ws(ID_GetContactInfoAck);
		ws << EC_SUCCESS << info.contact;
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
		auto ptr = UserManager::getRef().getInnerUserInfoByUID(info.contact.uID);
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