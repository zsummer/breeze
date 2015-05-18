#include "login.h"
#include "../userManager.h"
#include "../dbManager.h"
#include <ProtoCommon.h>
#include <ProtoCommonSQL.h>
#include <ProtoLogin.h>
#include <ProtoLoginSQL.h>

Login::Login()
{
	MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(&Login::event_onSessionDisconnect, this, _1));
	MessageDispatcher::getRef().registerSessionMessage(ID_PlatAuthReq, std::bind(&Login::msg_onPlatAuthReq, this, _1, _2, _3));
	MessageDispatcher::getRef().registerSessionMessage(ID_CreateUserReq, std::bind(&Login::msg_onCreateUserReq, this, _1, _2, _3));
	MessageDispatcher::getRef().registerSessionMessage(ID_SelectUserReq, std::bind(&Login::msg_onSelectUserReq, this, _1, _2, _3));
}

bool Login::init()
{
	_genID.initConfig(ServerConfig::getRef().getPlatID(), ServerConfig::getRef().getAreaID());
	DBQuery q("select uID from tb_UserInfo where uID >= ? and uID < ?  order by uID desc limit 1;");
	q << _genID.getMinObjID();
	q << _genID.getMaxObjID();
	auto result = DBManager::getRef().infoQuery(q.popSQL());
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("Login::init() init error.  can't get current users info.  error=" << result->getLastError() << ", sql=" << result->sqlString());
		return false;
	}
	if (result->haveRow())
	{
		try
		{
			UserID lastUserID = InvalidUserID;
			*result >> lastUserID;
			_genID.setCurObjID(lastUserID);
		}
		catch (...)
		{
			LOGE("Login::init() catch error.  can't get current users info.  error=" << result->getLastError() << ", sql=" << result->sqlString());
			return false;
		}
	}
	return true;
}

void Login::event_onSessionDisconnect(TcpSessionPtr session)
{
	_cache.erase(session->getSessionID());
}

void Login::msg_onPlatAuthReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	PlatAuthReq req; 
	rs >> req;
	//goto plat auth
	//....
	//plat auth success.

	session->setUserParamString(req.account);
	zsummer::mysql::DBQuery q(" select `uID`,`account`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime` from `tb_UserInfo` where `account` = ? ");
	q << req.account;
	DBManager::getRef().infoAsyncQuery(q.popSQL(), std::bind(&Login::db_onFetchUsers, this, _1, session));
}

void Login::db_onFetchUsers(DBResultPtr result, TcpSessionPtr session)
{
	PlatAuthAck ack;
	ack.retCode = EC_DB_ERROR;
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("Login::db_onFetchUsers have db error. error=" << result->getLastError() << ", sql=" << result->sqlString());
	}
	else
	{
		ack.retCode = EC_SUCCESS;
		try
		{
			UserInfo info;
			while (result->haveRow())
			{
				*result >> info.uID;
				*result >> info.account;
				*result >> info.nickName;
				*result >> info.iconID;
				*result >> info.diamond;
				*result >> info.hisotryDiamond;
				*result >> info.giftDiamond;
				*result >> info.joinTime;
				ack.users.push_back(info);
			}
			
		}
		catch (std::runtime_error e)
		{
			ack.retCode = EC_DB_ERROR;
			LOGE("Login::db_onFetchUsers catch one exception. e=" << e.what() << ", sql=" << result->sqlString());
		}
	}
	if (ack.retCode == EC_SUCCESS)
	{
		_cache[session->getSessionID()] = ack.users;
	}
	WriteStream ws(ID_PlatAuthAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}

void Login::msg_onCreateUserReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	auto founder = _cache.find(session->getSessionID());
	if (founder == _cache.end())
	{
		LOGW("Login::msg_onCreateUserReq session have no auth. sID=" << session->getSessionID());
		return;
	}
	
	CreateUserReq req;
	rs >> req;
	UserInfo info;
	info.uID = _genID.genNewObjID();
	if (info.uID >= _genID.getMaxObjID() || info.uID < _genID.getMinObjID())
	{
		LOGE("gen UserID over the max user ID. cur ID=" << info.uID);
		return;
	}
	
	info.account = session->getUserParamString();
	info.nickName = req.nickName;
	info.iconID = req.iconID;
	std::string sql = UserInfo_INSERT(info);
	DBManager::getRef().infoAsyncQuery(sql, std::bind(&Login::db_onCreateUser, this, _1, session, info));
}

void Login::db_onCreateUser(DBResultPtr result, TcpSessionPtr session, const UserInfo & info)
{
	CreateUserAck ack;
	ack.retCode = EC_SUCCESS;
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		ack.retCode = EC_DB_ERROR;
	}
	else
	{
		//!跨服务节点不能这么写
		UserManager::getRef().addUser(info);
		//end

		auto founder = _cache.find(session->getSessionID());
		if (founder == _cache.end())
		{
			return;
		}
		else
		{
			founder->second.push_back(info);
			ack.users = founder->second;
		}
	}
	WriteStream ws(ID_CreateUserAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}



void Login::msg_onSelectUserReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{
	SelectUserReq req;
	rs >> req;
	
	auto founder = _cache.find(session->getSessionID());
	if (founder == _cache.end())
	{
		return;
	}
	auto foundUser = std::find_if(founder->second.begin(), founder->second.end(), [&req](const UserInfo & info) { return info.uID == req.uID; });
	if (foundUser == founder->second.end())
	{
		return;
	}
	MD5Data data;
	data.append(foundUser->account);
	data.append(foundUser->nickName);

	char buf[100];
	sprintf(buf, "%d%d", rand() % 10000, (unsigned int)time(NULL));
	data.append(buf);

	SelectUserAck ack;
	ack.retCode = EC_SUCCESS;
	ack.uID = req.uID;
	ack.token = data.genMD5();

	//!跨服务节点不能这么写
	UserManager::getRef().setUserToken(ack.uID, ack.token, time(NULL) + 100000);

	WriteStream ws(ID_SelectUserAck);
	ws << ack;
	session->doSend(ws.getStream(), ws.getStreamLen());
}