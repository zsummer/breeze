#include "chatManager.h"
#include "../userManager.h"
#include "../dbManager.h"
#include <ProtoCommon.h>
#include <ProtoCommonSQL.h>
#include <ProtoChatSQL.h>


ChatManager::ChatManager()
{
	MessageDispatcher::getRef().registerSessionMessage(ID_GetContactInfoReq, std::bind(&ChatManager::msg_onGetContactInfoReq, this, _1, _2, _3));
	MessageDispatcher::getRef().registerSessionMessage(ID_FriendOperationReq, std::bind(&ChatManager::msg_onFriendOperationReq, this, _1, _2, _3));
	MessageDispatcher::getRef().registerSessionMessage(ID_ChatReq, std::bind(&ChatManager::msg_onChatReq, this, _1, _2, _3));
}

bool ChatManager::init()
{
	//! 先desc一下ContactInfo表, 不存在则创建
	auto build = ContactInfo_BUILD();
	if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
	{
		if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create table error. sql=" <<build[1]);
			return false;
		}
	}
	//! 无论ContactInfo表的字段是否有增删 都alter一遍. 
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

	//获取当前最大消息ID
	_genID.initConfig(ServerConfig::getRef().getPlatID(), ServerConfig::getRef().getAreaID());
	DBQuery q("select id from tb_ChatInfo where id >= ? and id < ?  order by id desc limit 1;");
	q << _genID.getMinObjID();
	q << _genID.getMaxObjID();
	auto result = DBManager::getRef().infoQuery(q.popSQL());
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("ChatManager::init() init error.  can't get current tb_ChatInfo id.  error=" << result->getLastError() << ", sql=" << result->sqlString());
		return false;
	}
	if (result->haveRow())
	{
		try
		{
			UserID lastChatID = 0;
			*result >> lastChatID;
			_genID.setCurObjID(lastChatID);
		}
		catch (...)
		{
			LOGE("ChatManager::init() catch error.  can't get current tb_ChatInfo .  error=" << result->getLastError() << ", sql=" << result->sqlString());
			return false;
		}
	}

	//监控玩家登录和退出, 用来更新玩家在线状态, 如果之后独立为一个进程后, 该通知以消息通知的形式获得.
	EventTrigger::getRef().watching(ETRIGGER_USER_LOGIN, std::bind(&ChatManager::onUserLogin, this, _1, _2, _3, _4, _5));
	EventTrigger::getRef().watching(ETRIGGER_USER_LOGOUT, std::bind(&ChatManager::onUserLogout, this, _1, _2, _3, _4, _5));
	return true;
}


void  ChatManager::onUserLogin(EventTriggerID tID, UserID uID, unsigned long long count, unsigned long long iconID, std::string nick)
{
	
	auto founder = _mapContact.find(uID);
	if (founder == _mapContact.end())
	{
		ContactInfo info;
		info.uID = uID;
		info.iconID = (short)iconID;
		info.nickName = nick;
		_mapContact[uID] = info;
		insertContact(info);
		return;
	}
	bool haveChange = false;
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

void ChatManager::insertContact(const ContactInfo & info)
{
	auto sql = ContactInfo_INSERT(info);
	if (!sql.empty())
	{
		DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "insertContact"));
	}
}
void ChatManager::updateContact(const ContactInfo & info, bool writedb, bool broadcast)
{
	if (writedb)
	{
		auto sql = ContactInfo_UPDATE(info);
		if (!sql.empty())
		{
			DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "updateContact"));
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
				auto ptr = UserManager::getRef().getInnerUserInfo(kv.uid);
				if (ptr && ptr->sID != InvalidSeesionID)
				{
					SessionManager::getRef().sendSessionData(ptr->sID, ws.getStream(), ws.getStreamLen());
				}
			}
		}
		auto ptr = UserManager::getRef().getInnerUserInfo(info.uID);
		if (ptr && ptr->sID != InvalidSeesionID)
		{
			SessionManager::getRef().sendSessionData(ptr->sID, ws.getStream(), ws.getStreamLen());
		}
	}
}



void ChatManager::db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc)
{
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE(desc << " error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
	}
}

void ChatManager::msg_onGetContactInfoReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	GetContactInfoReq req;
	rs >> req;
	GetContactInfoAck ack;
	ack.retCode = EC_SUCCESS;
	auto founder = _mapContact.find(req.uid);
	if (founder == _mapContact.end())
	{
		ack.retCode = EC_NO_USER;
	}
	else
	{
		ack.retCode = EC_SUCCESS;
		ack.contact = founder->second;
	}
	WriteStream ws(ID_GetContactInfoAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}

void ChatManager::msg_onFriendOperationReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	FriendOperationReq req;
	rs >> req;

	auto inner = UserManager::getRef().getInnerUserInfo(session->getSessionID());
	if (!inner)
	{
		//.
		return;
	}

	auto src = _mapContact.find(inner->userInfo.uID);
	if (src == _mapContact.end())
	{
		return;
	}

	auto dst = _mapContact.find(req.uid);
	if (dst == _mapContact.end())
	{
		return;
	}

	


}


void ChatManager::msg_onChatReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	ChatReq req;
	rs >> req;
	auto inner = UserManager::getRef().getInnerUserInfo(session->getSessionID());
	if (!inner)
	{
		//.
		return;
	}
	ChatInfo info;
	info.chlType = req.chlType;
	info.dstid = req.dstid;
	info.id = _genID.genNewObjID();
	info.msg = req.msg;
	info.sendTime = time(NULL);
	info.srcIcon = inner->userInfo.iconID;
	info.srcid = inner->userInfo.uID;
	info.srcName = inner->userInfo.nickName;

	if (info.chlType == CHANNEL_PRIVATE)
	{
		auto dstinner = UserManager::getRef().getInnerUserInfo(req.dstid);
		if (!dstinner)
		{
			return;
		}
		info.dstIcon = dstinner->userInfo.iconID;
		info.dstName = dstinner->userInfo.nickName;
		if (dstinner->sID != InvalidSeesionID)
		{
			WriteStream ws(ID_ChatNotice);
			ChatNotice notice;
			notice.msgs.push_back(info);
			ws << notice;
			SessionManager::getRef().sendSessionData(dstinner->sID, ws.getStream(), ws.getStreamLen());
		}
	}
	else if (info.chlType == CHANNEL_GROUP || info.chlType == CHANNEL_WORLD)
	{
// 		for ()
// 		{
// 			WriteStream ws(ID_ChatNotice);
// 			ChatNotice notice;
// 			notice.msgs.push_back(info);
// 			SessionManager::getRef().sendOrgSessionData(dstinner->sesionInfo.sID, ws.getStream(), ws.getStreamLen());
// 		}
	}

	auto chatsql = ChatInfo_INSERT(info);
	DBManager::getRef().infoAsyncQuery(chatsql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "ChatInfo_INSERT"));

	WriteStream ws(ID_ChatAck);
	ChatAck ack;
	ack.chlType = info.chlType;
	ack.dstid = info.dstid;
	ack.msgid = info.id;
	ack.retCode = EC_SUCCESS;
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}