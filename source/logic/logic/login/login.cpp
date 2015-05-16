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
}

bool Login::init()
{
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
		return;
	}
	
	CreateUserReq req;
	rs >> req;
	UserInfo info;
	info.account = session->getUserParamString();
}

void Login::msg_onSelectUserReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs)
{

}