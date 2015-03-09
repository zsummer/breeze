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
	MessageDispatcher::getRef().registerOnSessionPulse(std::bind(&NetManager::event_onPulse, this, std::placeholders::_1, std::placeholders::_2));
	MessageDispatcher::getRef().registerSessionMessage(ID_X2X_ServerPulse,
		std::bind(&NetManager::msg_onServerPulse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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
		ConnectConfig tag;
		tag._remoteIP = con._remoteIP;
		tag._remotePort = con._remotePort;
		tag._reconnectMaxCount = 120;
		tag._reconnectInterval = 5000;
		if (true)
		{
			continue;
		}
		SessionID sID = SessionManager::getRef().addConnector(tag);

		if (sID == InvalidSeesionID)
		{
			LOGE("addConnector failed. ConnectConfig=" << tag);
			return false;
		}
		// save sID. do something after.
		// ...
	}

	_configListen._listenIP = ServerConfig::getRef().getConfigListen(LogicNode)._ip;
	_configListen._listenPort = ServerConfig::getRef().getConfigListen(LogicNode)._port;
	_configListen._maxSessions = 5000;

	// if have some connector need connect success. do open accept in event_onSessionEstablished when all connector is success.
	//other open acceoter in here.
	_accepterID = SessionManager::getRef().addAcceptor(_configListen);
	if (_accepterID == InvalidAccepterID)
	{
		LOGE("OPEN Accepter false. ListenConfig=" << _configListen);
		return false;
	}
	else
	{
		LOGI("OPEN Accepter true. ListenConfig=" << _configListen);
	}
	return true;
}
bool NetManager::stop()
{
	SessionManager::getRef().stop();
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




void NetManager::msg_onLoginReq(SessionID sID, ProtoID pID, ReadStream & rs)
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
		WriteStream ws(ID_LS2C_LoginAck);
		LS2C_LoginAck ack;
		ack.retCode = BEC_AUTH_LIMITE_COUNT;
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		return;
	}
	
	innerInfo->sesionInfo.user = req.user;
	innerInfo->sesionInfo.passwd = req.passwd;
	innerInfo->status = InnerUserInfo::IUIT_AUTHING;

	
	DBRequest dbreq("SELECT uid, passwd FROM `tb_auth` where user = ?");
	dbreq.add(req.user);
	auto & db = DBManager::getRef().getAuthDB();
	DBAsync::getRef().asyncQuery(db, dbreq.genSQL(), std::bind(&NetManager::db_onAuthSelect, this,
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
		WriteStream ws(ID_LS2C_LoginAck);
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
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
				SessionManager::getRef().kickSession(sID);
			}
			else
			{
				if (fder->second->sesionInfo.sID != InvalidSeesionID)
				{
					SessionManager::getRef().kickSession(fder->second->sesionInfo.sID);
					userLogout(fder->second);
					_mapUserSession.erase(fder->second->sesionInfo.sID);
					fder->second->sesionInfo.sID = InvalidSeesionID;
				}
				
				fder->second->sesionInfo = innerInfo->sesionInfo;
				innerInfo = fder->second;
				innerInfo->sesionInfo.lastLoginTime = time(NULL);
				ack.info = innerInfo->userInfo;
				WriteStream ws(ID_LS2C_LoginAck);
				ws << ack;
				SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());

				userLogin(innerInfo);


			}
			return;
		}
		
		_mapUserInfo.insert(std::make_pair(innerInfo->sesionInfo.uid, innerInfo));
		innerInfo->status = InnerUserInfo::IUIT_LOGINING;

		//! 
		auto & db = DBManager::getRef().getInfoDB();
		DBRequest dbreq;
		dbreq.init("select uid, nickname, iconID, `level`, diamond, giftDiamond,historyDiamond, UNIX_TIMESTAMP(joinTime) from tb_user where uid = ?");
		dbreq.add(innerInfo->sesionInfo.uid);
		DBAsync::getRef().asyncQuery(db, dbreq.genSQL(), std::bind(&NetManager::db_onUserSelect, this,
			std::placeholders::_1, sID, false));
	}
}

void NetManager::db_onUserSelect(DBResultPtr res, SessionID sID, bool isCreateUser)
{
	LOGD("enter db_onUserSelect. sID=" << sID);
	LS2C_LoginAck ack;
	ack.retCode = BEC_DB_ERROR;

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
		ack.retCode = BEC_AUTH_ACCOUNT_INCORRECT;
	}

	if (ack.retCode != BEC_SUCCESS && ack.retCode != BEC_AUTH_ACCOUNT_INCORRECT)
	{
		innerInfo->status = InnerUserInfo::IUIT_UNAUTH;
		WriteStream ws(ID_LS2C_LoginAck);
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
	else
	{
		LOGD("user auth success. sID=" << sID << " req.user = " << innerInfo->sesionInfo.user << ", req.passwd = " << innerInfo->sesionInfo.passwd);
		auto fder = _mapUserInfo.find(innerInfo->sesionInfo.uid);
		if (fder == _mapUserInfo.end())
		{
			SessionManager::getRef().kickSession(sID);
			return;
		}
		else
		{
			WriteStream ws(ID_LS2C_LoginAck);
			ack.info = innerInfo->userInfo;
			ws << ack;
			SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			if (ack.retCode != BEC_AUTH_ACCOUNT_INCORRECT)
			{
				innerInfo->status = InnerUserInfo::IUIT_LOGINED;
				innerInfo->sesionInfo.lastLoginTime = time(NULL);
				userLogin(innerInfo);
			}
		}
	}
}


void NetManager::msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStream &rs)
{
	C2LS_CreateUserReq req;
	rs >> req;
	auto fouder = _mapUserSession.find(sID);
	if (fouder == _mapUserSession.end() || fouder->second->status != InnerUserInfo::IUIT_LOGINING)
	{
		SessionManager::getRef().kickSession(sID);
		return;
	}

	auto & db = DBManager::getRef().getInfoDB();
	DBRequest dbreq("call CreateUser(?, ?, ?)");
	dbreq.add(fouder->second->sesionInfo.uid);
	dbreq.add(escapeString(req.nickName));
	dbreq.add(req.iconID);
	DBAsync::getRef().asyncQuery(db, dbreq.genSQL(), std::bind(&NetManager::db_onUserCreate, this,
		std::placeholders::_1, sID));
}
void NetManager::db_onUserCreate(DBResultPtr res, SessionID sID)
{
	LOGD("enter db_onUserCreate. sID=" << sID);
	auto fouder = _mapUserSession.find(sID);
	if (fouder == _mapUserSession.end() || fouder->second->status != InnerUserInfo::IUIT_LOGINING)
	{
		SessionManager::getRef().kickSession(sID);
		return;
	}
	auto & innerInfo = fouder->second;
	
	LS2C_CreateUserAck ack;
	ack.retCode = BEC_DB_ERROR;


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
		ack.retCode = BEC_AUTH_ACCOUNT_INCORRECT;
	}

	if (ack.retCode != BEC_SUCCESS && ack.retCode != BEC_AUTH_ACCOUNT_INCORRECT)
	{
		SessionManager::getRef().kickSession(sID);
	}
	else
	{
		if (ack.retCode == BEC_SUCCESS)
		{
			ack.info = innerInfo->userInfo;
			WriteStream ws(ID_LS2C_CreateUserAck);
			ws << ack;
			SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			innerInfo->sesionInfo.lastLoginTime = time(NULL);
			userLogin(innerInfo);

			//blob test
			DBRequest dbreq;
			dbreq.init("update tb_user set bag=? where uid=?");
			std::string apendBin;
			for (int i = 0; i < 256; i++)
			{
				apendBin.append(1, (char)i);
			}
			WriteStream wsdb(0);
			wsdb << ack.info;
			wsdb << apendBin;
			std::string blob(wsdb.getStreamBody(), wsdb.getStreamBodyLen());
			dbreq.add(blob);
			dbreq.add(ack.info.uid);
			auto & db = DBManager::getRef().getInfoDB();
			DBAsync::getRef().asyncQuery(db, dbreq.genSQL(), std::bind(&NetManager::db_onTestBlog, this, std::placeholders::_1, false));
			dbreq.init("select bag from tb_user where uid=?");
			dbreq.add(ack.info.uid);
			DBAsync::getRef().asyncQuery(db, dbreq.genSQL(), std::bind(&NetManager::db_onTestBlog, this, std::placeholders::_1, true));
		}
		else
		{
			WriteStream ws(ID_LS2C_CreateUserAck);
			ws << ack;
			SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		}
		
	}
}

void NetManager::db_onTestBlog(DBResultPtr res, bool isRead)
{
	LOGD("enter db_onTestBlog. isRead=" << isRead);
	
	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_onTestBlog error.  error msg=" << res->getLastError() << ",  sql=" << res->sqlString());
	}
	else if (isRead)
	{
		if (res->haveRow())
		{
			try
			{
				std::string blob;
				*res >> blob;
				if (blob.length() > 0)
				{
					ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false);
					UserInfo info;
					rs >> info;
					std::string appendBin;
					rs >> appendBin;
					if (appendBin.length() != 256)
					{
						LOGE("test blog read error. appendBin length not is 256");
					}
					else
					{
						for (unsigned int i = 0; i < 256; i++)
						{
							if ((unsigned int)(unsigned char)appendBin.at(i) != i )
							{
								LOGE("test blog read error. appendBin have error. the character is " << i);
								break;
							}
						}		
					}
					
					int a = 0;
					a++;
				}
			}
			catch (const std::runtime_error & e)
			{
				LOGE("test blog read error. catch:" << e.what());
			}
			catch (...)
			{
				LOGE("test blog read error. catch:other.");
			}
		}
		else
		{
			LOGE("test blog read error");
		}
	}
	else
	{
		if (res->getAffectedRows() == 0)
		{
			LOGE("test blog write error");
		}
	}
}

void NetManager::event_onPulse(SessionID sID, unsigned int pulseInterval)
{
	if (isSessionID(sID))
	{
		auto founder = _mapUserSession.find(sID);
		if (founder == _mapUserSession.end())
		{
			SessionManager::getRef().kickSession(sID);
			LOGW("kick session because session not found in _mapSession.  sID=" << sID);
			return;
		}
		if (founder->second->sesionInfo.lastActiveTime + pulseInterval * 2 / 1000 < time(NULL))
		{
			SessionManager::getRef().kickSession(sID);
			LOGW("kick session because session heartbeat timeout.  sID=" << sID << ", lastActiveTime=" << founder->second->sesionInfo.lastActiveTime);
			return;
		}
		WriteStream ws(ID_X2X_ServerPulse);
		X2X_ServerPulse sp;
		sp.timeStamp = (ui32)time(NULL);
		sp.timeTick = getNowTick();
		ws << sp;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}


void NetManager::msg_onServerPulse(SessionID sID, ProtoID pID, ReadStream & rs)
{
	auto founder = _mapUserSession.find(sID);
	if (founder != _mapUserSession.end())
	{
		X2X_ServerPulse cp;
		rs >> cp;
		founder->second->sesionInfo.lastActiveTime = time(NULL);
		founder->second->sesionInfo.lastDelayTick = (getNowTick() - cp.timeTick + founder->second->sesionInfo.lastDelayTick) / 2; //延迟检测 阻尼衰减
		LOGD("msg_onServerPulse lastActiveTime=" << founder->second->sesionInfo.lastActiveTime <<", lastDelayTick=" << founder->second->sesionInfo.lastDelayTick << "ms");
		return;
	}
}




