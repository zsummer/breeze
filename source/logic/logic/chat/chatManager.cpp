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
	MessageDispatcher::getRef().registerSessionMessage(ID_GetSomeStrangersReq, std::bind(&ChatManager::msg_onGetSomeStrangersReq, this, _1, _2, _3));
}

ChatManager::~ChatManager()
{
	if (_filter)
	{
		match_tree_free(_filter);
		_filter = nullptr;
	}
}

bool ChatManager::init()
{
	//加载过滤词库
	_filter = match_tree_init_from_file("../filter.txt", ".....", 5);
	if (_filter == nullptr)
	{
		LOGE("match_tree_init_from_file error");
		return false;
	}
	LOGI("init filter configure success. filter patterns=" << _filter->_tree_pattern_count << ", min pattern=" 
		<< _filter->_tree_pattern_minimum_len << ", max pattern=" << _filter->_tree_pattern_maximum_len << ", used memory=" << _filter->_tree_memory_used / 1024 << "KB");
	
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
	
	//! 先desc一下ChatInfo表, 不存在则创建
	build = ChatInfo_BUILD();
	if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
	{
		if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create table error. sql=" << build[1]);
			return false;
		}
	}
	//! 无论ChatInfo表的字段是否有增删 都alter一遍. 
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
		_contacts.insert(mapInfo.begin(), mapInfo.end());
		curID += mapInfo.size();
	} while (true);

	//获取当前最大消息ID
	_genID.initConfig(ServerConfig::getRef().getPlatID(), ServerConfig::getRef().getAreaID());
	DBQuery q("select mID from tb_ChatInfo where mID >= ? and mID < ?  order by mID desc limit 1;");
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
	
	auto founder = _contacts.find(uID);
	if (founder == _contacts.end())
	{
		ContactInfo info;
		info.uID = uID;
		info.iconID = (short)iconID;
		info.nickName = nick;
		_contacts[uID] = info;
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
	updateContact(founder->second, haveChange, false);
}
void  ChatManager::onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string)
{
	auto founder = _contacts.find(uID);
	if (founder != _contacts.end())
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
		GetContactInfoAck ack;
		ack.retCode = EC_SUCCESS;
		ack.contact = info;
		ws << ack;
		for (auto &kv : info.friends)
		{
			if (kv.flag == FRIEND_ESTABLISHED)
			{
				auto ptr = UserManager::getRef().getInnerUserInfo(kv.uID);
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
	auto founder = _contacts.find(req.uID);
	if (founder == _contacts.end())
	{
		ack.retCode = EC_INVALIDE_USER;
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
	FriendOperationAck ack;
	ack.retCode = EC_SUCCESS;
	ack.srcFlag = req.oFlag;
	ack.dstUID = req.uID;
	auto inner = UserManager::getRef().getInnerUserInfo(session->getSessionID());
	if (!inner)
	{
		ack.retCode = EC_PERMISSION_DENIED;
		return;
	}
	ack.srcUID = inner->userInfo.uID;


	auto src = _contacts.find(inner->userInfo.uID);
	if (src == _contacts.end())
	{
		ack.retCode = EC_PARAM_DENIED;
		return;
	}
	auto srcStatus = std::find_if(src->second.friends.begin(), src->second.friends.end(), [&req](const FriendInfo& info){return info.uID == req.uID; });


	auto dst = _contacts.find(req.uID);
	if (dst == _contacts.end())
	{
		ack.retCode = EC_PARAM_DENIED;
		return;
	}
	auto dstStatus = std::find_if(dst->second.friends.begin(), dst->second.friends.end(), [&inner](const FriendInfo& info){return info.uID == inner->userInfo.uID; });


	if (req.oFlag == FRIEND_ADDFRIEND)
	{
		if (dstStatus == dst->second.friends.end() || dstStatus->flag == FRIEND_REQUESTING)
		{
			if (dstStatus != dst->second.friends.end())
			{
				dst->second.friends.erase(dstStatus);
			}
			FriendInfo info;
			info.flag = FRIEND_REQUESTING;
			info.makeTime = (unsigned int)time(NULL);
			info.uID = src->second.uID;
			dst->second.friends.push_back(info);
			if (srcStatus == src->second.friends.end() || srcStatus->flag == FRIEND_WAITING)
			{
				if (srcStatus != src->second.friends.end())
				{
					src->second.friends.erase(srcStatus);
				}
				info.flag = FRIEND_WAITING;
				info.uID = req.uID;
				src->second.friends.push_back(info);
			}
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
		
	}
	else if (req.oFlag == FRIEND_ADDBLACK)
	{
		src->second.friends.erase(srcStatus);
		FriendInfo info;
		info.flag = FRIEND_BLACKLIST;
		info.makeTime = (unsigned int)time(NULL);
		info.uID = req.uID;
		src->second.friends.push_back(info);
		if (dstStatus != dst->second.friends.end() && dstStatus->flag != FRIEND_BLACKLIST)
		{
			dst->second.friends.erase(dstStatus);
		}
	}
	else if (req.oFlag == FRIEND_REMOVEBLACK)
	{
		if (srcStatus != src->second.friends.end() && srcStatus->flag == FRIEND_BLACKLIST)
		{
			src->second.friends.erase(srcStatus);
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
	}
	else if (req.oFlag == FRIEND_REMOVEFRIEND)
	{
		if (srcStatus != src->second.friends.end() && srcStatus->flag != FRIEND_BLACKLIST)
		{
			src->second.friends.erase(srcStatus);
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
	}
	else if (req.oFlag == FRIEND_ALLOW)
	{
		if (srcStatus != src->second.friends.end() && srcStatus->flag == FRIEND_REQUESTING)
		{
			srcStatus->flag = FRIEND_ESTABLISHED;
			srcStatus->makeTime = (unsigned int)time(NULL);
			dst->second.friends.erase(dstStatus);

			FriendInfo info;
			info.uID = inner->userInfo.uID;
			info.makeTime = (unsigned int)time(NULL);
			info.flag = FRIEND_ESTABLISHED;
			src->second.friends.push_back(info);
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
	}
	else if (req.oFlag == FRIEND_REJECT)
	{
		if (srcStatus != src->second.friends.end() && srcStatus->flag == FRIEND_REQUESTING)
		{
			src->second.friends.erase(srcStatus);
			if (dstStatus != dst->second.friends.end() && dstStatus->flag == FRIEND_WAITING)
			{
				dst->second.friends.erase(dstStatus);
			}
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
	}
	else if (req.oFlag == FRIEND_IGNORE)
	{
		if (srcStatus != src->second.friends.end() && srcStatus->flag == FRIEND_REQUESTING)
		{
			src->second.friends.erase(srcStatus);
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
	}
	else 
	{
		ack.retCode = EC_PARAM_DENIED;
	}
	
	
	WriteStream ws(ID_FriendOperationAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}

void ChatManager::msg_onGetSomeStrangersReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	GetSomeStrangersReq req;
	rs >> req;
	auto inner = UserManager::getRef().getInnerUserInfo(session->getSessionID());
	if (!inner)
	{
		//.
		return;
	}

	GetSomeStrangersAck ack;
	ack.retCode = EC_SUCCESS;
	for (auto & c : _contacts)
	{
		if (c.second.onlineFlag != 0)
		{
			ack.uIDs.push_back(c.first);
		}
		if (ack.uIDs.size() > 10)
		{
			break;
		}
	}

	WriteStream ws(ID_GetSomeStrangersAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
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
	info.dstID = req.dstID;
	info.mID = _genID.genNewObjID();
	info.msg = req.msg;
	info.sendTime = (unsigned int)time(NULL);
	info.srcIcon = inner->userInfo.iconID;
	info.srcID = inner->userInfo.uID;
	info.srcName = inner->userInfo.nickName;
	//塞进数据库原诗的聊天内容
	auto chatsql = ChatInfo_INSERT(info);
	DBManager::getRef().infoAsyncQuery(chatsql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "ChatInfo_INSERT"));

	//过滤掉脏字
	match_tree_translate(_filter, &info.msg[0], (unsigned int)info.msg.length(), 1, '*');

	//通知下去
	if (info.chlType == CHANNEL_PRIVATE)
	{
		auto dstinner = UserManager::getRef().getInnerUserInfo(req.dstID);
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
		WriteStream ws(ID_ChatNotice);
		ChatNotice notice;
		notice.msgs.push_back(info);
		ws << notice;

		if (info.chlType == CHANNEL_GROUP)
		{
			auto founder = _channels.find(info.dstID);
			if (founder != _channels.end())
			{
				for (auto id : founder->second)
				{
					auto dstinner = UserManager::getRef().getInnerUserInfo(id);
					if (!dstinner || dstinner->sID == InvalidSeesionID)
					{
						continue;;
					}
					SessionManager::getRef().sendSessionData(dstinner->sID, ws.getStream(), ws.getStreamLen());
				}
				
			}
		}
		else
		{
			for (auto &c : _contacts)
			{
				auto dstinner = UserManager::getRef().getInnerUserInfo(c.first);
				if (!dstinner || dstinner->sID == InvalidSeesionID)
				{
					continue;;
				}
				SessionManager::getRef().sendSessionData(dstinner->sID, ws.getStream(), ws.getStreamLen());
			}
			
		}
		
	}



	WriteStream ws(ID_ChatAck);
	ChatAck ack;
	ack.chlType = info.chlType;
	ack.dstID = info.dstID;
	ack.msgID = info.mID;
	ack.retCode = EC_SUCCESS;
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}