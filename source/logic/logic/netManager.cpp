#include "netManager.h"
#include "dbManager.h"
using namespace zsummer::mysql;

NetManager::NetManager()
{
	//auth request process
	MessageDispatcher::getRef().registerSessionMessage(ID_C2LS_LoginReq,
		std::bind(&NetManager::msg_onLoginReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	MessageDispatcher::getRef().registerSessionMessage(ID_C2LS_CreateUserReq,
		std::bind(&NetManager::msg_onCreateUserReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	
	//register event
	MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(&NetManager::event_onSessionEstablished, this, std::placeholders::_1));
	MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(&NetManager::event_onSessionDisconnect, this, std::placeholders::_1));

	//
	MessageDispatcher::getRef().registerOnSessionPulse(std::bind(&NetManager::event_onSessionPulse, this, std::placeholders::_1, std::placeholders::_2));
	MessageDispatcher::getRef().registerSessionMessage(ID_C2AS_ClientPulse,
		std::bind(&NetManager::msg_onClientPulse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool NetManager::start()
{
	//init
	_handlers.push_back(DBManager::instantiate());
	for (auto ptr : _handlers)
	{
		if (!ptr->init())
		{
			LOGW("init handler false");
			return false;
		}
	}
	LOGI("init handler all Success. handler size=" << _handlers.size());
	//end
	auto connecters = ServerConfig::getRef().getConfigConnect(LogicNode);
	for (auto con : connecters)
	{
		tagConnctorConfigTraits tag;
		tag.remoteIP = con._remoteIP;
		tag.remotePort = con._remotePort;
		tag.reconnectMaxCount = 120;
		tag.reconnectInterval = 5000;
		if (true)
		{
			continue;
		}
		SessionID sID = TcpSessionManager::getRef().addConnector(tag);

		if (sID == InvalidSeesionID)
		{
			LOGE("addConnector failed. remoteIP=" << tag.remoteIP << ", remotePort=" << tag.remotePort);
			return false;
		}
		// save sID. do something after.
		// ...
	}

	_configListen.listenIP = ServerConfig::getRef().getConfigListen(LogicNode)._ip;
	_configListen.listenPort = ServerConfig::getRef().getConfigListen(LogicNode)._port;
	_configListen.maxSessions = 5000;

	// if have some connector need connect success. do open accept in event_onSessionEstablished when all connector is success.
	//other open acceoter in here.
	_accepterID = TcpSessionManager::getRef().addAcceptor(_configListen);
	if (_accepterID == InvalidAccepterID)
	{
		LOGE("OPEN Accepter false. ip=" << _configListen.listenIP << ", port=" << _configListen.listenPort);
		return false;
	}
	else
	{
		LOGI("OPEN Accepter true. ip=" << _configListen.listenIP << ", port=" << _configListen.listenPort);
	}
	return true;
}
bool NetManager::stop()
{
	TcpSessionManager::getRef().stop();
	return true;
}



void NetManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo)
{
	for (auto ptr : _handlers)
	{
		ptr->userLogin(innerInfo);
	}
}
void NetManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{
	for (auto ptr : _handlers)
	{
		ptr->userLogout(innerInfo);
	}
}


void NetManager::event_onSessionEstablished(SessionID sID)
{
	if (isConnectID(sID))
	{
		LOGT("NetManager::event_onSessionEstablished. SessionID=" << sID);
	}
	else
	{
		LOGT("NetManager::event_onSessionEstablished. SessionID=" << sID);
	}
}

void NetManager::event_onSessionDisconnect(SessionID sID)
{
	if (isConnectID(sID))
	{
		LOGI("NetManager::event_onSessionDisconnect. sID=" << sID);
	}
	else
	{
		LOGI("NetManager::event_onSessionDisconnect. sID=" << sID);
		auto founder = _mapUserSession.find(sID);
		if (founder == _mapUserSession.end())
		{
			return;
		}
		auto innerInfo = founder->second;
		_mapUserSession.erase(sID);

		if (innerInfo->status == InnerUserInfo::IUIT_LOGINED)
		{
			userLogin(innerInfo);
		}
		if (innerInfo->status == InnerUserInfo::IUIT_LOGINING)
		{
			_mapUserInfo.erase(innerInfo->sesionInfo.uid);
		}
		innerInfo->sesionInfo.sID = InvalidSeesionID;
	}
}




void NetManager::msg_onLoginReq(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	C2LS_LoginReq req;
	rs >> req;
	LOGD("enter msg_loginReq user=" << req.user << ", passwd=" << req.passwd);
	std::shared_ptr<InnerUserInfo> innerInfo;
	auto founder = _mapUserSession.find(sID);
	if (founder != _mapUserSession.end())
	{
		innerInfo = founder->second;
	}
	else
	{
		innerInfo = std::shared_ptr<InnerUserInfo>(new InnerUserInfo);
		innerInfo->sesionInfo.sID = sID;
		innerInfo->status = InnerUserInfo::IUIT_UNAUTH;
		_mapUserSession.insert(std::make_pair(sID, innerInfo));
	}

	if (innerInfo->status != InnerUserInfo::IUIT_UNAUTH)
	{
		WriteStreamPack ws(ID_LS2C_LoginAck);
		LS2C_LoginAck ack;
		ack.retCode = BEC_AUTH_LIMITE_COUNT;
		ws << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		return;
	}
	
	innerInfo->sesionInfo.user = req.user;
	innerInfo->sesionInfo.passwd = req.passwd;
	innerInfo->status = InnerUserInfo::IUIT_AUTHING;

	

	std::string auth_sql = "SELECT uid, passwd FROM `tb_auth` where user = '";
	auth_sql += escapeString(req.user);
	auth_sql += "'";

	auto & db = DBManager::getRef().getAuthDB();
	DBAsync::getRef().asyncQuery(db, auth_sql, std::bind(&NetManager::db_onAuthSelect, this,
		std::placeholders::_1, sID));

}

void NetManager::db_onAuthSelect(DBResultPtr res, SessionID sID)
{
	LOGD("enter db_authSelect. sID=" << sID);
	LS2C_LoginAck ack;
	ack.retCode = BEC_DB_ERROR;

	auto founder = _mapUserSession.find(sID);
	if (founder == _mapUserSession.end())
	{
		LOGE("db auth callback not found session. sID=" << sID);
		return;
	}
	auto & innerInfo = founder->second;
	if (!innerInfo)
	{
		LOGE("db auth callback found session but InnerInfo is NULL . sID=" << sID);
		return;
	}
	
	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_authSelect error.  db error, msg=" << res->getLastError() << ", req.user=" << innerInfo->sesionInfo.user << ", req.passwd=" << innerInfo->sesionInfo.passwd);
	}
	else if (!res->haveRow())
	{
		ack.retCode = BEC_AUTH_USER_NOT_EXIST;
	}
	else
	{
		try
		{
			if (res->haveRow())
			{
				UserID uid = 0;
				std::string passwd;
				*res >> uid;
				*res >> passwd;
				if (innerInfo->sesionInfo.passwd != passwd)
				{
					ack.retCode = BEC_AUTH_PASSWD_INCORRECT;
				}
				else
				{
					ack.retCode = BEC_SUCCESS;
					innerInfo->sesionInfo.uid = uid;
				}

			}
		}
		catch (const std::string & err)
		{
			LOGE("db_onAuthSelect catch error. err=" << err << ", sql=" << res->sqlString());
			ack.retCode = BEC_DB_ERROR;
		}
	}
	

	if (ack.retCode != BEC_SUCCESS)
	{
		LOGD("user auth fail. sID=" << sID << " req.user = " << innerInfo->sesionInfo.user << ", req.passwd = " << innerInfo->sesionInfo.passwd );
		innerInfo->status = InnerUserInfo::IUIT_UNAUTH;
		WriteStreamPack ws(ID_LS2C_LoginAck);
		ws << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
	else
	{
		LOGD("user auth success. sID=" << sID << " req.user = " << innerInfo->sesionInfo.user << ", req.passwd = " << innerInfo->sesionInfo.passwd);
		//检测用户状态 判断是否需要踢人, 重新拉取DB数据

		auto fder = _mapUserInfo.find(innerInfo->sesionInfo.uid);
		if (fder != _mapUserInfo.end())
		{
			if (fder->second->status != InnerUserInfo::IUIT_LOGINED)
			{
				TcpSessionManager::getRef().kickSession(sID);
			}
			else
			{
				if (fder->second->sesionInfo.sID != InvalidSeesionID)
				{
					TcpSessionManager::getRef().kickSession(fder->second->sesionInfo.sID);
					userLogout(fder->second);
					_mapUserSession.erase(fder->second->sesionInfo.sID);
					fder->second->sesionInfo.sID = InvalidSeesionID;
				}
				
				fder->second->sesionInfo = innerInfo->sesionInfo;
				innerInfo = fder->second;
				innerInfo->sesionInfo.lastLoginTime = time(NULL);
				ack.needCreateUser = false;
				ack.info = innerInfo->userInfo;
				WriteStreamPack ws(ID_LS2C_LoginAck);
				ws << ack;
				TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());

				userLogin(innerInfo);


			}
			return;
		}
		
		_mapUserInfo.insert(std::make_pair(innerInfo->sesionInfo.uid, innerInfo));
		innerInfo->status = InnerUserInfo::IUIT_LOGINING;
		auto & db = DBManager::getRef().getInfoDB();
		std::string selectUserInfo_sql = "select uid, nickname, iconID, `level`, diamond, giftDiamond,historyDiamond, UNIX_TIMESTAMP(joinTime) from tb_user where uid = ";
		selectUserInfo_sql += toString(innerInfo->sesionInfo.uid);
		DBAsync::getRef().asyncQuery(db, selectUserInfo_sql, std::bind(&NetManager::db_onUserSelect, this,
			std::placeholders::_1, sID, false));
	}
}

void NetManager::db_onUserSelect(DBResultPtr res, SessionID sID, bool isCreateUser)
{
	LOGD("enter db_onUserSelect. sID=" << sID);
	LS2C_LoginAck ack;
	ack.retCode = BEC_DB_ERROR;
	ack.needCreateUser = false;

	auto founder = _mapUserSession.find(sID);
	if (founder == _mapUserSession.end())
	{
		LOGE("db_onUserSelect callback not found session. sID=" << sID);
		return;
	}
	auto & innerInfo = founder->second;
	if (!innerInfo)
	{
		LOGE("db_onUserSelect callback found session but InnerInfo is NULL . sID=" << sID);
		return;
	}
	

	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_onUserSelect error.  error msg=" << res->getLastError() << ", req.user=" << innerInfo->sesionInfo.user << ", req.passwd=" << innerInfo->sesionInfo.passwd);
	}
	else if (res->haveRow())
	{
		try
		{
			while (res->haveRow())
			{
				*res >> innerInfo->userInfo.uid;
				*res >> innerInfo->userInfo.nickName;
				*res >> innerInfo->userInfo.iconID;
				*res >> innerInfo->userInfo.level;
				*res >> innerInfo->userInfo.diamond;
				*res >> innerInfo->userInfo.giftDiamond;
				*res >> innerInfo->userInfo.hisotryDiamond;
				*res >> innerInfo->userInfo.joinTime;
				ack.info = innerInfo->userInfo;
				ack.retCode = BEC_SUCCESS;
				ack.needCreateUser = false;
				break;
			}
		}
		catch (const std::string & err)
		{
			LOGE("db_onUserSelect catch error. err=" << err << ", sql=" << res->sqlString());
		}
	}
	else
	{
		ack.retCode = BEC_SUCCESS;
		ack.needCreateUser = true;
	}

	if (ack.retCode != BEC_SUCCESS)
	{
		innerInfo->status = InnerUserInfo::IUIT_UNAUTH;
		WriteStreamPack ws(ID_LS2C_LoginAck);
		ws << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
	else
	{
		LOGD("user auth success. sID=" << sID << " req.user = " << innerInfo->sesionInfo.user << ", req.passwd = " << innerInfo->sesionInfo.passwd);
		auto fder = _mapUserInfo.find(innerInfo->sesionInfo.uid);
		if (fder == _mapUserInfo.end())
		{
			TcpSessionManager::getRef().kickSession(sID);
			return;
		}
		else
		{
			WriteStreamPack ws(ID_LS2C_LoginAck);
			ack.info = innerInfo->userInfo;
			ws << ack;
			TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			if (!ack.needCreateUser)
			{
				innerInfo->status = InnerUserInfo::IUIT_LOGINED;
				innerInfo->sesionInfo.lastLoginTime = time(NULL);
				userLogin(innerInfo);
			}
		}
	}
}


void NetManager::msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	C2LS_CreateUserReq req;
	rs >> req;
	auto fouder = _mapUserSession.find(sID);
	if (fouder == _mapUserSession.end() || fouder->second->status != InnerUserInfo::IUIT_LOGINING)
	{
		TcpSessionManager::getRef().kickSession(sID);
		return;
	}

	auto & db = DBManager::getRef().getInfoDB();
	std::string sql = "call CreateUser(";
	sql += toString(fouder->second->sesionInfo.uid);
	sql += ", \"";
	sql += zsummer::mysql::escapeString(req.nickName);
	sql += "\", ";
	sql += toString(req.iconID);
	sql += ")";
	DBAsync::getRef().asyncQuery(db, sql, std::bind(&NetManager::db_onUserCreate, this,
		std::placeholders::_1, sID));
}
void NetManager::db_onUserCreate(DBResultPtr res, SessionID sID)
{
	LOGD("enter db_onUserCreate. sID=" << sID);
	auto fouder = _mapUserSession.find(sID);
	if (fouder == _mapUserSession.end() || fouder->second->status != InnerUserInfo::IUIT_LOGINING)
	{
		TcpSessionManager::getRef().kickSession(sID);
		return;
	}
	auto & innerInfo = fouder->second;
	
	LS2C_CreateUserAck ack;
	ack.retCode = BEC_DB_ERROR;
	ack.needCreateUser = false;

	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_onUserCreate error.  error msg=" << res->getLastError() << ",  sql=" << res->sqlString());
	}
	else if (res->haveRow())
	{
		try
		{
			while (res->haveRow())
			{
				*res >> innerInfo->userInfo.uid;
				*res >> innerInfo->userInfo.nickName;
				*res >> innerInfo->userInfo.iconID;
				*res >> innerInfo->userInfo.level;
				*res >> innerInfo->userInfo.diamond;
				*res >> innerInfo->userInfo.giftDiamond;
				*res >> innerInfo->userInfo.hisotryDiamond;
				*res >> innerInfo->userInfo.joinTime;
				ack.info = innerInfo->userInfo;
				ack.retCode = BEC_SUCCESS;
				ack.needCreateUser = false;
				break;
			}
		}
		catch (const std::string & err)
		{
			LOGE("db_onUserCreate catch error. err=" << err << ", sql=" << res->sqlString());
		}
	}
	else
	{
		ack.retCode = BEC_SUCCESS;
		ack.needCreateUser = true;
	}

	if (ack.retCode != BEC_SUCCESS)
	{
		TcpSessionManager::getRef().kickSession(sID);
	}
	else
	{
		if (!ack.needCreateUser)
		{
			ack.info = innerInfo->userInfo;
			WriteStreamPack ws(ID_LS2C_CreateUserAck);
			ws << ack;
			TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			innerInfo->sesionInfo.lastLoginTime = time(NULL);
			userLogin(innerInfo);

		}
		else
		{
			WriteStreamPack ws(ID_LS2C_CreateUserAck);
			ws << ack;
			TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		}
		
	}
}



void NetManager::event_onSessionPulse(SessionID sID, unsigned int pulseInterval)
{
	if (isSessionID(sID))
	{
		auto founder = _mapUserSession.find(sID);
		if (founder == _mapUserSession.end())
		{
			TcpSessionManager::getRef().kickSession(sID);
			LOGW("kick session because session not found in _mapSession.  sID=" << sID);
			return;
		}
		if (founder->second->sesionInfo.lastActiveTime + pulseInterval * 2 / 1000 < time(NULL))
		{
			TcpSessionManager::getRef().kickSession(sID);
			LOGW("kick session because session heartbeat timeout.  sID=" << sID << ", lastActiveTime=" << founder->second->sesionInfo.lastActiveTime);
			return;
		}
		WriteStreamPack ws(ID_AS2C_ServerPulse);
		AS2C_ServerPulse sp;
		sp.timeStamp = (ui32)time(NULL);
		sp.timeTick = 0;
		ws << sp;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}


void NetManager::msg_onClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	auto founder = _mapUserSession.find(sID);
	if (founder != _mapUserSession.end())
	{
		founder->second->sesionInfo.lastActiveTime = time(NULL);
		LOGD("msg_onClientPulse lastActiveTime=" << founder->second->sesionInfo.lastActiveTime);
		return;
	}
}




