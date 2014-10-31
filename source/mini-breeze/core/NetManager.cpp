#include "NetManager.h"


CNetManager::CNetManager()
{
	//注册来自客户端的默认协议处理逻辑
	CMessageDispatcher::getRef().RegisterSessionDefaultMessage(
		std::bind(&CNetManager::msg_DefaultSessionReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//认证逻辑 支持帐号多点认证
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2AS_AuthReq,
		std::bind(&CNetManager::msg_AuthReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_AS2C_AuthAck,
		std::bind(&CNetManager::msg_AuthAck, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_LS2AS_CharacterLogin,
		std::bind(&CNetManager::msg_CharacterLogin, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//注册事件
	CMessageDispatcher::getRef().RegisterOnSessionEstablished(std::bind(&CNetManager::event_OnSessionEstablished, this, std::placeholders::_1));
	CMessageDispatcher::getRef().RegisterOnSessionDisconnect(std::bind(&CNetManager::event_OnSessionDisconnect, this, std::placeholders::_1));

	//注册心跳
	CMessageDispatcher::getRef().RegisterOnSessionPulse(std::bind(&CNetManager::event_OnSessionPulse, this, std::placeholders::_1, std::placeholders::_2));
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2AS_ClientPulse,
		std::bind(&CNetManager::msg_OnClientPulse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_DT2OS_DirectServerPulse,
		std::bind(&CNetManager::msg_OnDirectServerPulse, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool CNetManager::Start()
{
	auto connecters = GlobalFacade::getRef().getServerConfig().getConfigConnect(AgentNode);
	for (auto con : connecters)
	{
		tagConnctorConfigTraits tag;
		tag.remoteIP = con.remoteIP;
		tag.remotePort = con.remotePort;
		tag.reconnectMaxCount = 120;
		tag.reconnectInterval = 5000;
		if (con.dstNode != CenterNode)
		{
			continue;
			
		}
		SessionID sID = CTcpSessionManager::getRef().AddConnector(tag);

		if (sID == InvalidSeesionID)
		{
			LOGE("AddConnector failed. remoteIP=" << tag.remoteIP << ", remotePort=" << tag.remotePort);
			return false;
		}
		m_configCenter.insert(std::make_pair(sID, tag));
	}

	m_configListen.listenIP = GlobalFacade::getRef().getServerConfig().getConfigListen(AgentNode).ip;
	m_configListen.listenPort = GlobalFacade::getRef().getServerConfig().getConfigListen(AgentNode).port;
	m_configListen.maxSessions = 5000;
	LOGI("CNetManager Init Success.");
	return true;
}
bool CNetManager::Stop()
{
	CTcpSessionManager::getRef().Stop();
	return true;
}

void CNetManager::event_OnSessionEstablished(SessionID sID)
{
	if (IsConnectID(sID))
	{
		//auth
		WriteStreamPack ws;
		DT2OS_DirectServerAuth auth;
		auth.srcNode = GlobalFacade::getRef().getServerConfig().getOwnServerNode();
		auth.srcIndex = GlobalFacade::getRef().getServerConfig().getOwnNodeIndex();
		ws << ID_DT2OS_DirectServerAuth << auth;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
		LOGI("send DT2OS_DirectServerAuth sID=" << sID << ", node=" << auth.srcNode << ", index=" << auth.srcIndex)
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
		auto founder = m_configCenter.find(sID);
		if (founder != m_configCenter.end())
		{
			LOGW("event_OnDisconnect Center Server. sID=" << sID << ", listenIP=" << founder->second.remoteIP << ", listenPort=" << founder->second.remotePort);
		}
		{
			auto finder = std::find_if(m_onlineCenter.begin(), m_onlineCenter.end(),
				[sID](const ServerAuthSession & sas){ return sas.sID == sID; });
			if (finder != m_onlineCenter.end())
			{
				m_onlineCenter.erase(finder);
				LOGW("event_OnDisconnect Center Server erase. sID=" << sID << ", current online Center count=" << m_onlineCenter.size());
			}
		}
	}
	else
	{
		auto founder = m_mapSession.find(sID);
		if (founder == m_mapSession.end())
		{
			return;
		}
		if (founder->second->sInfo.charID != InvalidCharacterID)
		{
			LOGI("CNetManager::event_OnSessionDisconnect. send ID_AS2LS_CharacterLogout. info=" << *founder->second);
			{
				RT2OS_RouteToOtherServer route;
				route.dstNode = LogicNode;
				route.routerType = RT_BROADCAST;
				route.dstIndex = 0;
				WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
				ws << ID_RT2OS_RouteToOtherServer << route << ID_AS2LS_CharacterLogout << founder->second->sInfo;
				CTcpSessionManager::getRef().SendOrgSessionData(m_onlineCenter.at(0).sID, ws.GetStream(), ws.GetStreamLen());
			}
			m_mapChar.erase(founder->second->sInfo.charID);
		}
		founder->second->sInfo.sID = InvalidSeesionID;
		m_mapSession.erase(founder);
	}
}

void CNetManager::msg_SessionServerAuth(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	DT2OS_DirectServerAuth auth;
	rs >> auth;
	LOGI("msg_ConnectServerAuth. sID=" << sID << ", Node=" << auth.srcNode << ", index=" << auth.srcIndex);

	auto founder = std::find_if(m_onlineCenter.begin(), m_onlineCenter.end(),
		[auth](const ServerAuthSession & sas){ return sas.index == auth.srcIndex; });
	if (founder != m_onlineCenter.end())
	{
		CTcpSessionManager::getRef().KickSession(founder->sID);
		m_onlineCenter.erase(founder);
	}
	ServerAuthSession sas;
	sas.node = auth.srcNode;
	sas.index = auth.srcIndex;
	sas.sID = sID;
	m_onlineCenter.push_back(sas);


	if (m_bListening || m_configCenter.size() !=  m_onlineCenter.size())
	{
		return;
	}

	//所有connector已经建立连接成功 并且是程序启动时的第一次 此时打开客户端监听端口
	if (CTcpSessionManager::getRef().AddAcceptor(m_configListen) == InvalidAccepterID)
	{
		LOGE("AddAcceptor Failed. listenIP=" << m_configListen.listenIP << ", listenPort=" << m_configListen.listenPort);
		return;
	}
	m_bListening = true;
	LOGI("AddAcceptor Success. listenIP=" << m_configListen.listenIP << ", listenPort=" << m_configListen.listenPort);
}



void CNetManager::msg_AuthReq(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	C2AS_AuthReq req;
	rs >> req;
	LOGD("ID_C2AS_AuthReq user=" << req.info.user << ", pwd=" << req.info.pwd);
	if (m_onlineCenter.empty())
	{
		WriteStreamPack ws;
		AS2C_AuthAck ack;
		ack.retCode = EC_SERVER_ERROR;
		ws << ID_AS2C_AuthAck << ack;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
		return;
	}

	auto finditer = m_mapSession.find(sID);
	if (finditer != m_mapSession.end())
	{
		WriteStreamPack ws;
		AS2C_AuthAck ack;
		ack.retCode = EC_AUTH_ING;
		ws << ID_AS2C_AuthAck << ack;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
		return;
	}

	std::shared_ptr<AgentSessionInfo> sinfo(new AgentSessionInfo);
	sinfo->sInfo.agentIndex = GlobalFacade::getRef().getServerConfig().getOwnNodeIndex();
	sinfo->sInfo.srcNode = AgentNode;
	sinfo->sInfo.srcIndex = sinfo->sInfo.agentIndex;
	sinfo->sInfo.sID = sID;
	m_mapSession.insert(std::make_pair(sID, sinfo));

	//route
	ProtoID inProtoID = ID_RT2OS_RouteToOtherServer;
	RT2OS_RouteToOtherServer route;
	route.dstNode = AuthNode;
	route.routerType = RT_ANY;
	route.dstIndex = 0;
	WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
	ws << inProtoID << route << ID_C2AS_AuthReq << sinfo->sInfo << req;
	CTcpSessionManager::getRef().SendOrgSessionData(m_onlineCenter.at(0).sID, ws.GetStream(), ws.GetStreamLen());
}

void CNetManager::msg_AuthAck(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	SessionInfo info;
	AS2C_AuthAck ack;
	rs >> info;
	rs >> ack;



	if (ack.retCode == EC_SUCCESS)
	{
		auto founder = m_mapSession.find(info.sID);
		if (founder == m_mapSession.end())
		{
			LOGE("msg_AuthAck can not found session ID.  sID=" << info.sID);
			return;
		}
		founder->second->sInfo.accID = ack.accountID;
	}

	WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
	ws << ID_AS2C_AuthAck << ack;
	CTcpSessionManager::getRef().SendOrgSessionData(info.sID, ws.GetStream(), ws.GetStreamLen());
}

//踢掉其他登录的到该节点的角色.
void CNetManager::msg_CharacterLogin(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	SessionInfo info;
	rs >> info;
	LOGT("CNetManager::msg_CharacterLogin.info=" << info);
	//静默方式踢掉原先的角色Session
	auto founder = m_mapChar.find(info.charID);
	if (founder != m_mapChar.end())
	{
		SessionInfo & si = founder->second->sInfo;
		CTcpSessionManager::getRef().KickSession(si.sID);
		LOGI("CNetManager::msg_CharacterLogin. send ID_AS2LS_CharacterLogout. info=" << *founder->second);
		m_mapSession.erase(si.sID);
		si.sID = InvalidSeesionID;
		si.charID = InvalidCharacterID;
		m_mapChar.erase(founder);
	}

	//保存新的角色索引和记录
	auto iter = m_mapSession.find(info.sID);
	if (iter != m_mapSession.end())
	{
		SessionInfo & si = iter->second->sInfo;
		si.charID = info.charID;
		si.loginTime = info.loginTime;
		m_mapChar.insert(std::make_pair(info.charID, iter->second));
		LOGI("CNetManager::msg_CharacterLogin Character On login. info=" << si);
	}
}

void CNetManager::event_OnSessionPulse(SessionID sID, unsigned int pulseInterval)
{
	if (IsConnectID(sID))
	{
		auto founder = std::find_if(m_onlineCenter.begin(), m_onlineCenter.end(), [sID](const ServerAuthSession & sas) {return sas.sID == sID; });
		if (founder == m_onlineCenter.end())
		{
			CTcpSessionManager::getRef().KickSession(sID);
			LOGW("break connector because the connector not founder in online center. sID=" << sID);
			return;
		}
		if (founder->lastActiveTime + pulseInterval * 10 / 1000 < time(NULL))
		{
			CTcpSessionManager::getRef().KickSession(sID);
			LOGW("break connector because the connector heartbeat timeout. sID=" << sID << ", lastActiveTime=" << founder->lastActiveTime);
			return;
		}
		WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
		DT2OS_DirectServerPulse pulse;
		pulse.srcNode = GlobalFacade::getRef().getServerConfig().getOwnServerNode();
		pulse.srcIndex = GlobalFacade::getRef().getServerConfig().getOwnNodeIndex();
		ws << ID_DT2OS_DirectServerPulse << pulse;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
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
		if (founder->second->lastActiveTime + pulseInterval * 10 / 1000 < time(NULL))
		{
			CTcpSessionManager::getRef().KickSession(sID);
			LOGW("kick session because session heartbeat timeout.  sID=" << sID << ", lastActiveTime=" << founder->second->lastActiveTime);
			return;
		}
		WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
		AS2C_ClientPulseAck ack;
		ack.svrTimeStamp = time(NULL);
		ws << ID_AS2C_ClientPulseAck << ack;
		CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
	}
}

void CNetManager::msg_OnDirectServerPulse(SessionID sID, ProtoID pID, ReadStreamPack &rs)
{
	auto founder = std::find_if(m_onlineCenter.begin(), m_onlineCenter.end(), [sID](const ServerAuthSession & sas) {return sas.sID == sID; });
	if (founder != m_onlineCenter.end())
	{
		LOGD("msg_OnDirectServerPulse lastActiveTime=" << founder->lastActiveTime);
		founder->lastActiveTime = time(NULL);
		return;
	}
}
void CNetManager::msg_OnClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	auto founder = m_mapSession.find(sID);
	if (founder != m_mapSession.end())
	{
		founder->second->lastActiveTime = time(NULL);
		LOGD("msg_OnClientPulse lastActiveTime=" << founder->second->lastActiveTime);
		return;
	}
}


void CNetManager::msg_DefaultSessionReq(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	if (IsConnectID(sID))
	{
		SessionInfo info;
		rs >> info;
		if (info.sID != InvalidSeesionID)
		{
			WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
			ws << pID;
			ws.AppendOriginalData(rs.GetStreamUnread(), rs.GetStreamUnreadLen());
			CTcpSessionManager::getRef().SendOrgSessionData(info.sID, ws.GetStream(), ws.GetStreamLen());
		}
	}
	else
	{
		auto finditer = m_mapSession.find(sID);
		if (finditer == m_mapSession.end() || finditer->second->sInfo.accID == InvalidAccountID)
		{
			AS2C_AuthAck ack;
			ack.retCode = EC_AUTH_NOT_FOUND_USER;
			ack.accountID = InvalidAccountID;
			WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
			ws << ID_AS2C_AuthAck << ack;
			CTcpSessionManager::getRef().SendOrgSessionData(sID, ws.GetStream(), ws.GetStreamLen());
		}
		else
		{
			ProtoID inProtoID = InvalidProtoID;
			if (isNeedAuthClientPROTO(pID) && !m_onlineCenter.empty())
			{
				inProtoID = ID_RT2OS_RouteToOtherServer;
				RT2OS_RouteToOtherServer route;
				route.dstNode = LogicNode;
				route.routerType = RT_ANY;
				route.dstIndex = 0;

				WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
				ws << inProtoID << route << pID << finditer->second->sInfo;
				ws.AppendOriginalData(rs.GetStreamUnread(), rs.GetStreamUnreadLen());
				CTcpSessionManager::getRef().SendOrgSessionData(m_onlineCenter.at(0).sID, ws.GetStream(), ws.GetStreamLen());
				return;
			}
		}

	}
};


