#include "chatManager.h"
#include "../userManager.h"
#include "../dbManager.h"
#include <ProtoCommon.h>
#include <ProtoCommonSQL.h>
#include <ProtoChatSQL.h>


ChatManager::ChatManager()
{
	MessageDispatcher::getRef().registerSessionMessage(ID_GetContactInfoReq, std::bind(&ChatManager::msg_onGetContactInfoReq, this, _1, _2));
	MessageDispatcher::getRef().registerSessionMessage(ID_FriendOperationReq, std::bind(&ChatManager::msg_onFriendOperationReq, this, _1, _2));
	MessageDispatcher::getRef().registerSessionMessage(ID_ChatReq, std::bind(&ChatManager::msg_onChatReq, this, _1, _2));
	MessageDispatcher::getRef().registerSessionMessage(ID_GetSomeStrangersReq, std::bind(&ChatManager::msg_onGetSomeStrangersReq, this, _1, _2));
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
	if (!initFilter())
	{
		return false;
	}
	if (!initContact())
	{
		return false;
	}
	if (!initFriends())
	{
		return false;
	}

	//监控玩家登录和退出, 用来更新玩家在线状态, 如果之后独立为一个进程后, 该通知以消息通知的形式获得.
	EventTrigger::getRef().watching(ETRIGGER_USER_LOGIN, std::bind(&ChatManager::onUserLogin, this, _1, _2, _3, _4, _5));
	EventTrigger::getRef().watching(ETRIGGER_USER_LOGOUT, std::bind(&ChatManager::onUserLogout, this, _1, _2, _3, _4, _5));
	return true;
}

bool ChatManager::initFilter()
{
	_filter = match_tree_init_from_file("../filter.txt", ".....", 5);
	if (_filter == nullptr)
	{
		LOGE("match_tree_init_from_file error");
		return false;
	}
	LOGI("init filter configure success. filter patterns=" << _filter->_tree_pattern_count << ", min pattern="
		<< _filter->_tree_pattern_minimum_len << ", max pattern=" << _filter->_tree_pattern_maximum_len << ", used memory=" << _filter->_tree_memory_used / 1024 << "KB");
	return true;
}
bool ChatManager::initContact()
{
	//! 先desc一下ContactInfo表, 不存在则创建
	auto build = ContactInfo_BUILD();
	if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
	{
		if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create table error. sql=" << build[1]);
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
		auto mapInfo = ContactInfo_FETCH(result);
		if (mapInfo.empty())
		{
			break;
		}
		for (auto kv : mapInfo)
		{
			Contact info;
			info.info = kv.second;
			_contacts.insert(std::make_pair(info.info.uID, info));
		}
		curID += mapInfo.size();
	} while (true);

	return true;
}
bool ChatManager::initFriends()
{
	//! 先desc一下FriendInfo表, 不存在则创建
	auto build = FriendInfo_BUILD();
	if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
	{
		if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create table error. sql=" << build[1]);
			return false;
		}
	}
	//! 无论FriendInfo表的字段是否有增删 都alter一遍. 
	for (size_t i = 2; i < build.size(); i++)
	{
		DBManager::getRef().infoQuery(build[i]);
	}

	//加载所有好友关系
	unsigned long long curID = 0;
	do
	{
		auto sql = FriendInfo_LOAD(curID);
		auto result = DBManager::getRef().infoQuery(sql);
		if (result->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("load FriendInfo error. curID:" << curID << ", err=" << result->getLastError());
			return false;
		}
		auto mapInfo = FriendInfo_FETCH(result);
		if (mapInfo.empty())
		{
			break;
		}
		for (auto kv : mapInfo)
		{
			auto founder = _contacts.find(kv.first);
			if (founder == _contacts.end())
			{
				LOGW("can not found the user ID when load friends info. uID=" << kv.first);
				continue;
			}
			founder->second.friends.insert(kv.second.begin(), kv.second.end());
		}
		curID += mapInfo.size();
	} while (true);
	return true;
}

bool ChatManager::initMessage()
{
	//! 先desc一下ChatInfo表, 不存在则创建
	auto build = ChatInfo_BUILD();
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
	return true;
}

void  ChatManager::onUserLogin(EventTriggerID tID, UserID uID, unsigned long long count, unsigned long long iconID, std::string nick)
{
	auto founder = _contacts.find(uID);
	if (founder == _contacts.end())
	{
		Contact contact;
		contact.info.uID = uID;
		contact.info.iconID = (short)iconID;
		contact.info.nickName = nick;
		_contacts[uID] = contact;
		insertContact(contact.info);
	}
	founder = _contacts.find(uID);
	if (founder == _contacts.end())
	{
		return;
	}
	bool haveChange = false;
	if (founder->second.info.nickName != nick)
	{
		founder->second.info.nickName = nick;
		haveChange = true;
	}
	if (founder->second.info.iconID != iconID)
	{
		founder->second.info.iconID = (short)iconID;
		haveChange = true;
	}
	if (haveChange)
	{
		updateContact(founder->second.info);
	}
	founder->second.info.onlineFlag = true;
}

void  ChatManager::onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string)
{
	auto founder = _contacts.find(uID);
	if (founder != _contacts.end())
	{
		founder->second.info.onlineFlag = false;
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

void ChatManager::updateContact(const ContactInfo & info)
{
	auto sql = ContactInfo_UPDATE(info);
	if (!sql.empty())
	{
		DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "updateContact"));
	}
}

//存储好友关系
void ChatManager::insertFriend(const FriendInfo & info)
{
	auto sql = FriendInfo_INSERT(info);
	if (!sql.empty())
	{
		DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "insertFriend"));
	}
}
void ChatManager::updateFriend(const FriendInfo & info)
{
	auto sql = FriendInfo_UPDATE(info);
	if (!sql.empty())
	{
		DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "updateFriend"));
	}
}

//存储聊天消息
void ChatManager::insertMessage(const ChatInfo & info)
{
	auto sql = ChatInfo_INSERT(info);
	if (!sql.empty())
	{
		DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "insertMessage"));
	}
}
void ChatManager::updateMessage(const ChatInfo & info)
{
	auto sql = ChatInfo_UPDATE(info);
	if (!sql.empty())
	{
		DBManager::getRef().infoAsyncQuery(sql, std::bind(&ChatManager::db_onDefaultUpdate, this, _1, "updateMessage"));
	}
}


void ChatManager::broadcast(WriteStream & ws, const UserIDArray uIDs)
{
	UserManager::getRef().broadcast(ws, uIDs);
}

void ChatManager::broadcastFriends(WriteStream & ws, UserID uID)
{
	auto founder = _contacts.find(uID);
	if (founder == _contacts.end())
	{
		return;
	}
	UserIDArray ids;
	for (auto kv : founder->second.friends)
	{
		if (kv.second.fID == FRIEND_ESTABLISHED)
		{
			auto fr = _contacts.find(kv.second.fID);
			if (fr == _contacts.end())
			{
				continue;
			}
			if (fr->second.info.onlineFlag)
			{
				ids.push_back(kv.first);
			}
		}
	}
	broadcast(ws, ids);
}

void ChatManager::db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc)
{
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE(desc << " error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
	}
}

void ChatManager::msg_onGetContactInfoReq(TcpSessionPtr session, ReadStream & rs)
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
		ack.contact = founder->second.info;
	}
	WriteStream ws(ID_GetContactInfoAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}

void ChatManager::msg_onFriendOperationReq(TcpSessionPtr session, ReadStream & rs)
{
	FriendOperationReq req;
	rs >> req;
	FriendOperationAck ack;
	ack.retCode = EC_SUCCESS;
	ack.srcFlag = req.oFlag;
	ack.dstUID = req.uID;
	auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
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
	auto srcStatus = src->second.friends.find(req.uID);


	auto dst = _contacts.find(req.uID);
	if (dst == _contacts.end())
	{
		ack.retCode = EC_PARAM_DENIED;
		return;
	}
	auto dstStatus = dst->second.friends.find(inner->userInfo.uID);


	if (req.oFlag == FRIEND_ADDFRIEND)
	{
		if (dstStatus == dst->second.friends.end() || dstStatus->second.flag == FRIEND_REQUESTING)
		{
			FriendInfo info;
			info.flag = FRIEND_REQUESTING;
			info.makeTime = (unsigned int)time(NULL);
			info.fID = src->second.info.uID;
			info.ownID = dst->second.info.uID;

			if (dstStatus == dst->second.friends.end())
			{
				dst->second.friends[info.fID] = info;
				insertFriend(info);
			}
			else
			{
				dstStatus->second = info;
				updateFriend(info);
			}

			info.flag = FRIEND_WAITING;
			info.fID = dst->second.info.uID;
			info.ownID = src->second.info.uID;
			if (srcStatus == src->second.friends.end())
			{
				src->second.friends[info.fID] = info;
				insertFriend(info);
			}
			else if (srcStatus->second.flag == FRIEND_WAITING)
			{
				srcStatus->second = info;
				updateFriend(info);
			}
			
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
		
	}
	else if (req.oFlag == FRIEND_ADDBLACK)
	{

	}
	else if (req.oFlag == FRIEND_REMOVEBLACK)
	{

	}
	else if (req.oFlag == FRIEND_REMOVEFRIEND)
	{

	}
	else if (req.oFlag == FRIEND_ALLOW)
	{
		if (srcStatus != src->second.friends.end() && srcStatus->second.flag == FRIEND_REQUESTING)
		{
			srcStatus->second.flag = FRIEND_ESTABLISHED;
			srcStatus->second.makeTime = (unsigned int)time(NULL);
			updateFriend(srcStatus->second);

			if (dstStatus != dst->second.friends.end())
			{
				dstStatus->second.flag = FRIEND_ESTABLISHED;
				dstStatus->second.makeTime = (unsigned int)time(NULL);
				updateFriend(dstStatus->second);
			}
		}
		else
		{
			ack.retCode = EC_PARAM_DENIED;
		}
	}
	else if (req.oFlag == FRIEND_REJECT)
	{
	
	}
	else if (req.oFlag == FRIEND_IGNORE)
	{

	}
	else 
	{
		ack.retCode = EC_PARAM_DENIED;
	}
	
	
	WriteStream ws(ID_FriendOperationAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}

void ChatManager::msg_onGetSomeStrangersReq(TcpSessionPtr session, ReadStream & rs)
{
	GetSomeStrangersReq req;
	rs >> req;
	auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
	if (!inner)
	{
		//.
		return;
	}

	GetSomeStrangersAck ack;
	ack.retCode = EC_SUCCESS;
	for (auto & c : _contacts)
	{
		if (ack.uIDs.size() > 10)
		{
			break;
		}
		if (c.first == session->getUserParam())
		{
			continue;
		}
// 		if (c.second.onlineFlag != 0)
// 		{
 			ack.uIDs.push_back(c.first);
// 		}
	}

	WriteStream ws(ID_GetSomeStrangersAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}

void ChatManager::msg_onChatReq(TcpSessionPtr session, ReadStream & rs)
{
	ChatReq req;
	rs >> req;
	auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
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