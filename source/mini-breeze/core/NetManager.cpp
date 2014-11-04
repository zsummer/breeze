#include "NetManager.h"


CNetManager::CNetManager()
{
	//认证逻辑 支持帐号多点认证
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2AS_AuthReq,
		std::bind(&CNetManager::msg_AuthReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2LS_CharacterCreateReq,
		std::bind(&CNetManager::msg_CharacterCreateReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2LS_CharacterLoginReq,
		std::bind(&CNetManager::msg_CharacterLoginReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	
	//注册事件
	CMessageDispatcher::getRef().RegisterOnSessionEstablished(std::bind(&CNetManager::event_OnSessionEstablished, this, std::placeholders::_1));
	CMessageDispatcher::getRef().RegisterOnSessionDisconnect(std::bind(&CNetManager::event_OnSessionDisconnect, this, std::placeholders::_1));

	//注册心跳
	CMessageDispatcher::getRef().RegisterOnSessionPulse(std::bind(&CNetManager::event_OnSessionPulse, this, std::placeholders::_1, std::placeholders::_2));
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2AS_ClientPulse,
		std::bind(&CNetManager::msg_OnClientPulse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool CNetManager::Start()
{
	auto connecters = GlobalFacade::getRef().getServerConfig().getConfigConnect(MiniBreezeNode);
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
		SessionID sID = CTcpSessionManager::getRef().AddConnector(tag);

		if (sID == InvalidSeesionID)
		{
			LOGE("AddConnector failed. remoteIP=" << tag.remoteIP << ", remotePort=" << tag.remotePort);
			return false;
		}
		// save sID. do something after.
		// ...
	}

	m_configListen.listenIP = GlobalFacade::getRef().getServerConfig().getConfigListen(MiniBreezeNode).ip;
	m_configListen.listenPort = GlobalFacade::getRef().getServerConfig().getConfigListen(MiniBreezeNode).port;
	m_configListen.maxSessions = 5000;
	// if have some connector need connect success. do open accept in event_OnSessionEstablished when all connector is success.
	//other open acceoter in here.
	m_accepterID = CTcpSessionManager::getRef().AddAcceptor(m_configListen);
	if (m_accepterID == InvalidAccepterID)
	{
		LOGE("OPEN Accepter false. ip=" << m_configListen.listenIP << ", port=" << m_configListen.listenPort);
		return false;
	}
	else
	{
		LOGI("OPEN Accepter true. ip=" << m_configListen.listenIP << ", port=" << m_configListen.listenPort);
	}
	return true;
}
bool CNetManager::Stop()
{
	CTcpSessionManager::getRef().Stop();
	return true;
}



void CNetManager::CharLogin(std::shared_ptr<InnerCharInfo> iinfoPtr)
{
	for (auto ptr : GlobalFacade::getRef().getAllHandler())
	{
		ptr->CharLogin(iinfoPtr);
	}
}
void CNetManager::CharLogout(std::shared_ptr<InnerCharInfo> iinfoPtr)
{
	for (auto ptr : GlobalFacade::getRef().getAllHandler())
	{
		ptr->CharLogout(iinfoPtr);
	}
}


void CNetManager::event_OnSessionEstablished(SessionID sID)
{
	if (IsConnectID(sID))
	{
		LOGT("CNetManager::event_OnSessionEstablished. SessionID=" << sID);
	}
	else
	{
		LOGT("CNetManager::event_OnSessionEstablished. SessionID=" << sID);
	}
}

void CNetManager::event_OnSessionDisconnect(SessionID sID)
{
	if (IsConnectID(sID))
	{
		LOGI("CNetManager::event_OnSessionDisconnect. sID=" << sID);
	}
	else
	{
		LOGI("CNetManager::event_OnSessionDisconnect. sID=" << sID);
		auto founder = m_mapSession.find(sID);
		if (founder == m_mapSession.end())
		{
			return;
		}
		auto iinfoPtr = founder->second;
		if (iinfoPtr->status == InnerCharInfo::ICIT_LOGINED)
		{
			CharLogin(iinfoPtr);
			m_mapCharInfo.erase(iinfoPtr->charInfo.charID);
		}
		m_mapSession.erase(sID);
	}
}




void CNetManager::msg_AuthReq(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	C2AS_AuthReq req;
	rs >> req;
	LOGD("ID_C2AS_AuthReq user=" << req.user << ", pwd=" << req.pwd);
	std::shared_ptr<InnerCharInfo> iinfoPtr;
	auto founder = m_mapSession.find(sID);
	if (founder != m_mapSession.end())
	{
		iinfoPtr = founder->second;
	}
	else
	{
		iinfoPtr = std::shared_ptr<InnerCharInfo>(new InnerCharInfo);
		iinfoPtr->sesionInfo.sID = sID;
		iinfoPtr->status = InnerCharInfo::ICIT_UNAUTH;
		m_mapSession.insert(std::make_pair(sID, iinfoPtr));
	}

	if (iinfoPtr->status != InnerCharInfo::ICIT_UNAUTH)
	{
		WriteStreamPack ws;
		AS2C_AuthAck ack;
		ack.retCode = BEC_AUTH_ING;
		ws << ID_AS2C_AuthAck << ack;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
		return;
	}
	
	iinfoPtr->status = InnerCharInfo::ICIT_AUTHING;


	//do someting with asynchronization
	//callback do something.

	{
		
		AS2C_AuthAck ack;
		ack.retCode = BEC_AUTH_NOT_FOUND_USER;

		do 
		{
			auto founder = m_mapSession.find(sID);
			if (founder == m_mapSession.end())
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
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
	}
}

void CNetManager::msg_CharacterCreateReq(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	C2LS_CharacterCreateReq req;
	rs >> req;

	auto fouder = m_mapSession.find(sID);
	if (fouder == m_mapSession.end())
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
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
	}
}

void CNetManager::msg_CharacterLoginReq(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	C2LS_CharacterLoginReq req;
	rs >> req;
	auto fouder = m_mapSession.find(sID);
	if (fouder == m_mapSession.end())
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

		auto foundOldChar = m_mapCharInfo.find(foundChar->charID);
		if (foundOldChar != m_mapCharInfo.end())
		{
			auto oldIInfoPtr = foundOldChar->second;
			CharLogout(oldIInfoPtr);
			CTcpSessionManager::getRef().KickSession(oldIInfoPtr->sesionInfo.sID);
			m_mapSession.erase(oldIInfoPtr->sesionInfo.sID);
			m_mapCharInfo.erase(oldIInfoPtr->charInfo.charID);
		}
		
		iinfo.charInfo = *foundChar;
		m_mapCharInfo.insert(std::make_pair(iinfo.charInfo.charID, iinfoPtr));
		CharLogin(iinfoPtr);

		LS2C_CharacterLoginAck ack;
		ack.retCode = BEC_SUCCESS;
		WriteStreamPack ws;
		ws << ID_LS2C_CharacterLoginAck << ack;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
	}
}

void CNetManager::event_OnSessionPulse(SessionID sID, unsigned int pulseInterval)
{
	if (IsConnectID(sID))
	{
	}
	else
	{
		auto founder = m_mapSession.find(sID);
		if (founder == m_mapSession.end())
		{
			CTcpSessionManager::getRef().KickSession(sID);
			LOGW("kick session because session not found in m_mapSession.  sID=" << sID);
			return;
		}
		if (founder->second->sesionInfo.lastActiveTime + pulseInterval * 2 / 1000 < time(NULL))
		{
			CTcpSessionManager::getRef().KickSession(sID);
			LOGW("kick session because session heartbeat timeout.  sID=" << sID << ", lastActiveTime=" << founder->second->sesionInfo.lastActiveTime);
			return;
		}
		WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
		AS2C_ClientPulseAck ack;
		ack.svrTimeStamp = time(NULL);
		ws << ID_AS2C_ClientPulseAck << ack;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
	}
}


void CNetManager::msg_OnClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	auto founder = m_mapSession.find(sID);
	if (founder != m_mapSession.end())
	{
		founder->second->sesionInfo.lastActiveTime = time(NULL);
		LOGD("msg_OnClientPulse lastActiveTime=" << founder->second->sesionInfo.lastActiveTime);
		return;
	}
}




