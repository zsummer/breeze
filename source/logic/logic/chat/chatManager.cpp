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
unsigned long long uID;
std::string nickName; //用户昵称 
short iconID; //头像 
char banned; //禁言 
unsigned int rankBlacks; //被拉黑次数 
unsigned int rankFriends; //好友个数 
unsigned char onlineFlag; //在线状态0离线,1在线 
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
		checkTable = DBManager::getRef().infoQuery(q.genSQL());
		if (checkTable->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create talbe tb_user error=" << checkTable->getLastError());
			return false;
		}
	}
	//版本升级自动alter add 新字段. 
	DBManager::getRef().infoQuery("alter table `tb_friend` add `nickName` varchar(255) NOT NULL DEFAULT ''");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `iconID` smallint(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `banned` tinyint(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `rankBlacks` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `rankFriends` int(10) NOT NULL DEFAULT '0'");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `friends` blob");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `blacks` blob");
	DBManager::getRef().infoQuery("alter table `tb_friend` add `request` blob");
	//加载所有用户数据
	UserID curID = 0;
	do
	{
		DBQuery q("select uID, nickName, iconID, banned, rankBlacks, rankFriends, friends, blacks, request from tb_friend where uID >? limit 1000;");
		q.add(curID);
		auto result = DBManager::getRef().infoQuery(q.genSQL());
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
			*result >> info.contact.rankBlacks;
			*result >> info.contact.rankFriends;
			info.contact.onlineFlag = false;
			std::string friends;
			std::string blacks;
			std::string request;
			friends.resize(1024);
			blacks.resize(1024);
			request.resize(1024);
			*result >> friends;
			*result >> blacks;
			*result >> request;
			try
			{
				ReadStream rs(friends.c_str(), (zsummer::proto4z::Integer)friends.length(), false);
					rs >> info.friends;
			}
			catch (std::runtime_error re)
			{
				LOGE("when load user friend find one error. uID=" << info.contact.uID << " error=" << re.what());
			}
			try
			{
				ReadStream rs(blacks.c_str(), (zsummer::proto4z::Integer)blacks.length(), false);
				rs >> info.blacks;
			}
			catch (std::runtime_error re)
			{
				LOGE("when load user friend find one error. uID=" << info.contact.uID << " error=" << re.what());
			}
			try
			{
				ReadStream rs(request.c_str(), (zsummer::proto4z::Integer)request.length(), false);
				rs >> info.request;
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
	auto founder = _mapContact.find(uID);
	if (founder == _mapContact.end())
	{
		InnerContactInfo info;
		info.contact.uID = uID;
		info.contact.banned = false;
		info.contact.iconID = (short)iconID;
		info.contact.nickName = nick;
		info.contact.rankBlacks = 0;
		info.contact.rankFriends = 0;
		_mapContact[uID] = info;
		
		updateContact(info);
		
		founder = _mapContact.find(uID);
	}
	founder->second.contact.onlineFlag = true;
	for (auto &kv : founder->second.friends)
	{
		//broadcast
	}
	

	
}
void  ChatManager::onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string)
{
	auto founder = _mapContact.find(uID);
	if (founder != _mapContact.end())
	{
		founder->second.contact.onlineFlag = false;
	}
}

void ChatManager::updateContact(const InnerContactInfo & info)
{
	try
	{
		WriteStream wsFriends(0);
		wsFriends << info.friends;
		WriteStream wsBlacks(0);
		wsBlacks << info.blacks;
		WriteStream wsRequest(0);
		wsRequest << info.request;

		DBQuery q("insert into tb_friend(uID, nickName, iconID, banned, rankBlacks, rankFriends, friends, blacks, request) "
			" values(?,?,?,?,?,?, ?, ?, ?) on duplicate key update banned=?, rankBlacks=?, rankFriends=?, friends=?, blacks=?, request=?;");
		q.add(info.contact.uID);
		q.add(info.contact.nickName);
		q.add(info.contact.iconID);
		q.add(info.contact.banned);
		q.add(info.contact.rankBlacks);
		q.add(info.contact.rankFriends);
		q.add(wsFriends.getStreamBody(), wsFriends.getStreamBodyLen());
		q.add(wsBlacks.getStreamBody(), wsBlacks.getStreamBodyLen());
		q.add(wsRequest.getStreamBody(), wsRequest.getStreamBodyLen());


		q.add(info.contact.banned);
		q.add(info.contact.rankBlacks);
		q.add(info.contact.rankFriends);
		q.add(wsFriends.getStreamBody(), wsFriends.getStreamBodyLen());
		q.add(wsBlacks.getStreamBody(), wsBlacks.getStreamBodyLen());
		q.add(wsRequest.getStreamBody(), wsRequest.getStreamBodyLen());

		DBManager::getRef().infoAsyncQuery(q.genSQL(), std::bind(&ChatManager::onUpdateContact, this, std::placeholders::_1));
	}
	catch (...)
	{
		LOGE("updateContact failed");
		return;
	}
}



void ChatManager::onUpdateContact(zsummer::mysql::DBResultPtr result)
{
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("onUpdateContact error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
	}
	
}

