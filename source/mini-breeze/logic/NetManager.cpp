#include "NetManager.h"
#include "DBManager.h"
using namespace zsummer::mysql;

NetManager::NetManager()
{
	//auth request process
	MessageDispatcher::getRef().registerSessionMessage(ID_C2AS_AuthReq,
		std::bind(&NetManager::msg_authReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	MessageDispatcher::getRef().registerSessionMessage(ID_C2LS_CharacterCreateReq,
		std::bind(&NetManager::msg_characterCreateReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	MessageDispatcher::getRef().registerSessionMessage(ID_C2LS_CharacterLoginReq,
		std::bind(&NetManager::msg_characterLoginReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	
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
	auto connecters = ServerConfig::getRef().getConfigConnect(MiniBreezeNode);
	for (auto con : connecters)
	{
		tagConnctorConfigTraits tag;
		tag.remoteIP = con.remoteIP;
		tag.remotePort = con.remotePort;
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

	_configListen.listenIP = ServerConfig::getRef().getConfigListen(MiniBreezeNode).ip;
	_configListen.listenPort = ServerConfig::getRef().getConfigListen(MiniBreezeNode).port;
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



void NetManager::charLogin(std::shared_ptr<InnerCharInfo> iinfoPtr)
{
	for (auto ptr : _handlers)
	{
		ptr->charLogin(iinfoPtr);
	}
}
void NetManager::charLogout(std::shared_ptr<InnerCharInfo> iinfoPtr)
{
	for (auto ptr : _handlers)
	{
		ptr->charLogout(iinfoPtr);
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
		auto founder = _mapSession.find(sID);
		if (founder == _mapSession.end())
		{
			return;
		}
		auto iinfoPtr = founder->second;
		if (iinfoPtr->status == InnerCharInfo::ICIT_LOGINED)
		{
			charLogin(iinfoPtr);
			_mapCharInfo.erase(iinfoPtr->charInfo.charID);
		}
		_mapSession.erase(sID);
	}
}




void NetManager::msg_authReq(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	C2AS_AuthReq req;
	rs >> req;
	LOGD("ID_C2AS_AuthReq user=" << req.user << ", pwd=" << req.pwd);
	std::shared_ptr<InnerCharInfo> iinfoPtr;
	auto founder = _mapSession.find(sID);
	if (founder != _mapSession.end())
	{
		iinfoPtr = founder->second;
	}
	else
	{
		iinfoPtr = std::shared_ptr<InnerCharInfo>(new InnerCharInfo);
		iinfoPtr->sesionInfo.sID = sID;
		iinfoPtr->status = InnerCharInfo::ICIT_UNAUTH;
		_mapSession.insert(std::make_pair(sID, iinfoPtr));
	}

	if (iinfoPtr->status != InnerCharInfo::ICIT_UNAUTH)
	{
		WriteStreamPack ws;
		AS2C_AuthAck ack;
		ack.retCode = BEC_AUTH_ING;
		ws << ID_AS2C_AuthAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		return;
	}
	
	iinfoPtr->status = InnerCharInfo::ICIT_AUTHING;

	
	//
	{

		std::string auth_sql = "SELECT accID, pwd FROM `tb_auth` where account = '";
		auto & db = DBManager::getRef().getAuthDB();
		auth_sql += escapeString(req.user);
		auth_sql += "'";


		DBAsync::getRef().asyncQuery(db, auth_sql, std::bind(&NetManager::db_authSelect, this,
			std::placeholders::_1,sID, req));
		return;
	}

	//do someting with asynchronization
	//callback do something.

	{
		
		AS2C_AuthAck ack;
		ack.retCode = BEC_AUTH_NOT_FOUND_USER;

		do 
		{
			auto founder = _mapSession.find(sID);
			if (founder == _mapSession.end())
			{
				break;
			}
			auto & iinfo = *founder->second;
			if (iinfo.status != InnerCharInfo::ICIT_AUTHING)
			{
				ack.retCode = BEC_AUTH_AREADY_AUTH;
				break;
			}
			if (true)
			{
				iinfo.status = InnerCharInfo::ICIT_AUTHED;
				iinfo.accInfo.accID = InvalidAccountID;
				iinfo.accInfo.accName = "default";
				iinfo.accInfo.diamond = 0;
				iinfo.accInfo.giftDmd = 0;
				iinfo.accInfo.hisDiamond = 0;
				iinfo.accInfo.hisGiftDmd = 0;

				ack.retCode = BEC_SUCCESS;
				ack.info = iinfo.accInfo;
			}
			else
			{
				iinfo.status = InnerCharInfo::ICIT_UNAUTH;
				ack.retCode = BEC_AUTH_PWD_INCORRECT;
			}
		} while (0);

		WriteStreamPack ws;
		ws << ID_AS2C_AuthAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}

void NetManager::db_authSelect(DBResultPtr res, SessionID sID, C2AS_AuthReq req)
{
	//error
	AS2C_AuthAck ack;
	ack.retCode = BEC_DB_ERROR;
	AccountID accID = InvalidAccountID;

	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_authSelect error.  error msg=" << res->getLastError() << ", req.user=" << req.user << ", req.pwd=" << req.pwd);
	}
	else if (!res->haveRow())
	{
		ack.retCode = BEC_AUTH_NOT_FOUND_USER;
	}
	else
	{
		try
		{
			if (res->haveRow())
			{
				std::string pwd;
				*res >> accID;
				*res >> pwd;
				if (req.pwd != pwd)
				{
					ack.retCode = BEC_AUTH_PWD_INCORRECT;
				}
				else
				{
					ack.retCode = BEC_SUCCESS;
				}

			}
		}
		catch (const std::string & err)
		{
			LOGE("db_authSelect catch error.  req.user=" << req.user << ", req.pwd=" << req.pwd << ", error=" << err);
			ack.retCode = BEC_AUTH_NOT_FOUND_USER;
		}
	}
	

	if (ack.retCode != BEC_SUCCESS)
	{
		auto founder = _mapSession.find(sID);
		if (founder != _mapSession.end() && founder->second)
		{
			founder->second->status = InnerCharInfo::ICIT_UNAUTH;
		}

		WriteStreamPack ws;
		ws << ID_AS2C_AuthAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
	else
	{
		{
			auto & db = DBManager::getRef().getInfoDB();
			std::string selectAccountInfo_sql = "call AutoSelectAccount(";
			selectAccountInfo_sql += toString(accID);
			selectAccountInfo_sql += ")";
			DBAsync::getRef().asyncQuery(db, selectAccountInfo_sql, std::bind(&NetManager::db_accountSelect, this,
				std::placeholders::_1,sID, accID, req));
		}
	}
}

void NetManager::db_accountSelect(DBResultPtr res, SessionID sID, AccountID accID, C2AS_AuthReq req)
{
	//error
	AS2C_AuthAck ack;
	ack.retCode = BEC_DB_ERROR;
	

	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_authSelect error.  error msg=" << res->getLastError() << ", req.user=" << req.user << ", req.pwd=" << req.pwd);
	}
	else if (!res->haveRow())
	{
		ack.retCode = BEC_AUTH_NOT_FOUND_USER;
	}
	else
	{
		try
		{
			while (res->haveRow())
			{
				ack.retCode = BEC_SUCCESS;
				break;
			}
		}
		catch (const std::string & err)
		{
			LOGE("db_authSelect catch error.  req.user=" << req.user << ", req.pwd=" << req.pwd << ", error=" << err);
			ack.retCode = BEC_AUTH_NOT_FOUND_USER;
		}
	}



	if (ack.retCode != BEC_SUCCESS)
	{
		auto founder = _mapSession.find(sID);
		if (founder != _mapSession.end() && founder->second)
		{
			founder->second->status = InnerCharInfo::ICIT_UNAUTH;
		}
		WriteStreamPack ws;
		ws << ID_AS2C_AuthAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
	else
	{
		WriteStreamPack ws;
		ws << ID_AS2C_AuthAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}

void NetManager::msg_characterCreateReq(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	C2LS_CharacterCreateReq req;
	rs >> req;

	auto fouder = _mapSession.find(sID);
	if (fouder == _mapSession.end())
	{
		return;
	}
	auto iinfoPtr = fouder->second;
	auto & iinfo = *iinfoPtr;
	if (iinfo.status != InnerCharInfo::ICIT_AUTHED)
	{
		return;
	}
	//do someting with asynchronization
	//callback do something.
	
	{
		LS2C_CharacterCreateAck ack;
		ack.retCode = BEC_DB_ERROR;
		do 
		{
			if (true)
			{
				CharacterInfo info;
				info.accID = iinfo.accInfo.accID;
				info.charID = 100;
				info.charName = req.charName;
				info.iconID = 100;
				info.level = 1;
				iinfo.accInfo.charInfos.push_back(info);

				ack.info = info;
				ack.retCode = BEC_SUCCESS;
			}
		} while (0);
		
		WriteStreamPack ws;
		ws << ID_LS2C_CharacterCreateAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}

void NetManager::msg_characterLoginReq(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	C2LS_CharacterLoginReq req;
	rs >> req;
	auto fouder = _mapSession.find(sID);
	if (fouder == _mapSession.end())
	{
		return;
	}
	auto iinfoPtr = fouder->second;
	auto & iinfo = *iinfoPtr;
	if (iinfo.status != InnerCharInfo::ICIT_AUTHED)
	{
		return;
	}
	
	{
		auto foundChar = std::find_if(iinfo.accInfo.charInfos.begin(), iinfo.accInfo.charInfos.end(),
			[&req](const CharacterInfo & charInfo){return charInfo.charID == req.charID; });
		if (foundChar == iinfo.accInfo.charInfos.end())
		{
			return;
		}

		auto foundOldChar = _mapCharInfo.find(foundChar->charID);
		if (foundOldChar != _mapCharInfo.end())
		{
			auto oldIInfoPtr = foundOldChar->second;
			charLogout(oldIInfoPtr);
			TcpSessionManager::getRef().kickSession(oldIInfoPtr->sesionInfo.sID);
			_mapSession.erase(oldIInfoPtr->sesionInfo.sID);
			_mapCharInfo.erase(oldIInfoPtr->charInfo.charID);
		}
		
		iinfo.charInfo = *foundChar;
		_mapCharInfo.insert(std::make_pair(iinfo.charInfo.charID, iinfoPtr));
		charLogin(iinfoPtr);

		LS2C_CharacterLoginAck ack;
		ack.retCode = BEC_SUCCESS;
		WriteStreamPack ws;
		ws << ID_LS2C_CharacterLoginAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}

void NetManager::event_onSessionPulse(SessionID sID, unsigned int pulseInterval)
{
	if (isConnectID(sID))
	{
	}
	else
	{
		auto founder = _mapSession.find(sID);
		if (founder == _mapSession.end())
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
		WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
		AS2C_ClientPulseAck ack;
		ack.svrTimeStamp = time(NULL);
		ws << ID_AS2C_ClientPulseAck << ack;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}


void NetManager::msg_onClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	auto founder = _mapSession.find(sID);
	if (founder != _mapSession.end())
	{
		founder->second->sesionInfo.lastActiveTime = time(NULL);
		LOGD("msg_onClientPulse lastActiveTime=" << founder->second->sesionInfo.lastActiveTime);
		return;
	}
}




