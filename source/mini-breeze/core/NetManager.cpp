#include "NetManager.h"


CNetManager::CNetManager()
{
	//认证逻辑 支持帐号多点认证
	CMessageDispatcher::getRef().RegisterSessionMessage(ID_C2AS_AuthReq,
		std::bind(&CNetManager::msg_AuthReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	
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
	}
}




void CNetManager::msg_AuthReq(SessionID sID, ProtoID pID, ReadStreamPack & rs)
{
	C2AS_AuthReq req;
	rs >> req;
	LOGD("ID_C2AS_AuthReq user=" << req.user << ", pwd=" << req.pwd);

	auto finditer = m_mapSession.find(sID);
	if (finditer != m_mapSession.end())
	{
		WriteStreamPack ws;
		AS2C_AuthAck ack;
		ack.retCode = BEC_AUTH_ING;
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




