#include "netManager.h"
#include "dbManager.h"
#include "userManager.h"
#include <ProtoCommonSQL.h>
using namespace zsummer::mysql;

NetManager::NetManager()
{
	//auth request process
	MessageDispatcher::getRef().registerSessionMessage(ID_LoginReq,
		std::bind(&NetManager::msg_onLoginReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	MessageDispatcher::getRef().registerSessionMessage(ID_CreateUserReq,
		std::bind(&NetManager::msg_onCreateUserReq, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	MessageDispatcher::getRef().registerSessionOrgMessage(std::bind(&NetManager::on_preMessageProcess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	
	//register event
	MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(&NetManager::event_onSessionEstablished, this, std::placeholders::_1));
	MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(&NetManager::event_onSessionDisconnect, this, std::placeholders::_1));

	//
	MessageDispatcher::getRef().registerOnSessionPulse(std::bind(&NetManager::event_onPulse, this, std::placeholders::_1, std::placeholders::_2));
	MessageDispatcher::getRef().registerSessionMessage(ID_ServerPulseEcho,
		std::bind(&NetManager::msg_onServerPulseEcho, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool NetManager::start()
{
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

	//如果这个服务节点依赖需要和其他服务节点建立连接(分布式), 然后再开放端口的话, 下面的打开监听端口的代码应该放在所有connect成功后的回调函数中.
	// if have some connector need connect success. call addAcceptor in event_onSessionEstablished when all connector is success.

	_configListen._listenIP = ServerConfig::getRef().getConfigListen(LogicNode)._ip;
	_configListen._listenPort = ServerConfig::getRef().getConfigListen(LogicNode)._port;
	_configListen._maxSessions = 5000;

	_accepterID = SessionManager::getRef().addAcceptor(_configListen);
	if (_accepterID == InvalidAccepterID)
	{
		LOGE("OPEN Accepter false. ListenConfig=" << _configListen);
		return false;
	}
	else
	{
		LOGD("OPEN Accepter true. ListenConfig=" << _configListen);
	}
	return true;
}

bool NetManager::stop(std::function<void()> onSafeClosed)
{
	SessionManager::getRef().stopAccept();
	SessionManager::getRef().kickAllClients();
	SessionManager::getRef().kickAllConnect();

	if (UserManager::getRef().getAllOnlineUserCount() == 0)
	{
		SessionManager::getRef().post(onSafeClosed);
	}
	else
	{
		_onSafeClosed = onSafeClosed;
	}
	return true;
}



void NetManager::event_onSessionEstablished(SessionID sID)
{
	if (isConnectID(sID))
	{
		LOGT("NetManager::event_onSessionEstablished. SessionID=" << sID);
	}
	else
	{
		LOGT("NetManager::event_onSessionEstablished. SessionID=" << sID << ", all unlogins clients=" << _clients.size());
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
		
		auto founder = _clients.find(sID);
		if (founder != _clients.end())
		{
			_clients.erase(sID);
		}

		auto info = UserManager::getRef().getInnerUserInfoBySID(sID);
		if (info)
		{
			UserManager::getRef().userLogout(info);
		}
	}

	if (UserManager::getRef().getAllOnlineUserCount() == 0 && _onSafeClosed)
	{
		SessionManager::getRef().post(_onSafeClosed);
		_onSafeClosed = nullptr;
	}
}

bool NetManager::on_preMessageProcess(SessionID sID, const char * blockBegin, zsummer::proto4z::Integer blockSize)
{
	ReadStream rs(blockBegin, blockSize);
	auto founder = _clients.find(sID);
	if (founder == _clients.end())
	{
		SessionInfo info;
		info.sID = sID;
		_clients[sID] = info;
		founder = _clients.find(sID);
	}

	if (rs.getProtoID() >= 200 || rs.getProtoID() == ID_ServerPulseEcho)
	{
		if (founder->second.status == SS_LOGINED)
		{
			return true;
		}
		else
		{
			WriteStream ws(ID_LoginAck);
			LoginAck ack;
			ack.retCode = EC_PERMISSION_DENIED;
			ws << ack;
			SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			LOGW("on_preMessageProcess check authorization failed. protoID=" << rs.getProtoID() << ", session authorization status=" << founder->second.status);
			return false;
		}
	}

	if (rs.getProtoID() == ID_LoginReq  && founder->second.status == SS_UNAUTH)
	{
		return true;
	}
	if (rs.getProtoID() == ID_CreateUserReq && founder->second.status == SS_AUTHED)
	{
		return true;
	}
	
	
	WriteStream ws(ID_LoginAck);
	LoginAck ack;
	ack.retCode = EC_PERMISSION_DENIED;
	ws << ack;
	SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	LOGW("on_preMessageProcess check authorization failed. protoID=" << rs.getProtoID() << ", session authorization status=" << founder->second.status)
	return false;
}


void NetManager::msg_onLoginReq(SessionID sID, ProtoID pID, ReadStream & rs)
{
	LoginReq req;
	rs >> req;
	LOGD("enter msg_loginReq user=" << req.user << ", passwd=" << req.passwd);

	auto founder = _clients.find(sID);
	if (founder == _clients.end())
	{
		return;
	}
	founder->second.user = req.user;
	founder->second.passwd = req.passwd;
	founder->second.status = SS_AUTHING;

	DBQuery q("SELECT uID, passwd FROM `tb_auth` where user = ?");
	q.add(req.user);
	DBManager::getRef().authAsyncQuery(q.popSQL(), std::bind(&NetManager::db_onAuthSelect, this, std::placeholders::_1, sID));

}

void NetManager::db_onAuthSelect(DBResultPtr res, SessionID sID)
{
	LOGD("enter db_authSelect. sID=" << sID);
	LoginAck ack;
	ack.retCode = EC_DB_ERROR;
	ack.needCreate = 0;
	

	auto founder = _clients.find(sID);
	if (founder == _clients.end())
	{
		LOGW("db auth callback not found session. sID=" << sID);
		return;
	}

	if (res->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
	{
		LOGE("db_authSelect error.  db error, msg=" << res->getLastError() << ", req.user=" << founder->second.user << ", req.passwd=" << founder->second.passwd);
	}
	else if (!res->haveRow())
	{
		ack.retCode = EC_AUTH_USER_NOT_EXIST;
	}
	else
	{
		try
		{
			if (res->haveRow())
			{
				std::string passwd;
				UserID uID = InvalidUserID;
				*res >> uID;
				*res >> passwd;
				if (founder->second.passwd != passwd)
				{
					ack.retCode = EC_AUTH_PASSWD_INCORRECT;
				}
				else
				{
					ack.retCode = EC_SUCCESS;
					founder->second.uID = uID;
					founder->second.authTime = time(NULL);
					founder->second.status = SS_AUTHED;
				}

			}
		}
		catch (const std::string & err)
		{
			LOGE("db_onAuthSelect catch error. err=" << err << ", sql=" << res->sqlString());
			ack.retCode = EC_DB_ERROR;
		}
	}
	

	if (ack.retCode != EC_SUCCESS)
	{
		LOGD("user auth fail. sID=" << sID << " req.user = " << founder->second.user << ", req.passwd=" << founder->second.passwd);
		founder->second.status = SS_UNAUTH;
		WriteStream ws(ID_LoginAck);
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		return;
	}

	LOGD("user auth success. sID=" << sID << " req.user = " << founder->second.user << ", req.passwd=" << founder->second.passwd);
	auto inner = UserManager::getRef().getInnerUserInfoByUID(founder->second.uID);
	if (!inner)
	{
		WriteStream ws(ID_LoginAck);
		ack.retCode = EC_SUCCESS;
		ack.needCreate = 1;
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		return;
	}

	if (inner->sesionInfo.status == SS_LOGINED)
	{
		_clients.erase(inner->sesionInfo.sID);
		UserManager::getRef().userLogout(inner);
	}

	inner->sesionInfo = founder->second;
	inner->sesionInfo.lastActiveTime = time(NULL);
	inner->sesionInfo.loginTime = time(NULL);
	inner->sesionInfo.status = SS_LOGINED;



	UserManager::getRef().userLogin(inner);
	WriteStream ws(ID_LoginAck);
	ack.retCode = EC_SUCCESS;
	ack.info = inner->userInfo;
	ws << ack;
	SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
}


void NetManager::msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStream &rs)
{
	CreateUserReq req;
	rs >> req;

	auto founder = _clients.find(sID);
	if (founder == _clients.end())
	{
		return;
	}
	if (founder->second.status != SS_AUTHED || founder->second.uID == InvalidUserID)
	{
		return;
	}

	//如果是多个logic服务器, 那么创建角色的工作要先交给一个公共服务来进行互斥,而不是在这里进行互斥检测.
	auto inner = UserManager::getRef().getInnerUserInfoByNickName(req.nickName);
	if (inner)
	{
		LoginAck ack;
		WriteStream ws(ID_LoginAck);
		ack.retCode = EC_SUCCESS;
		ack.needCreate = 1;
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		LOGW("create user  warning. nick name incorect. nickName =" << req.nickName << ", cur uID=" << founder->second.uID << ", incorect uID= " << inner->userInfo.uID);
		return;
	}
	

	inner = UserManager::getRef().getInnerUserInfoByUID(founder->second.uID);
	if (inner)
	{
		return;
	}
	
	
	inner = std::make_shared<InnerUserInfo>();
	inner->userInfo.uID = founder->second.uID;
	inner->userInfo.nickName = req.nickName;
	inner->userInfo.iconID = req.iconID;

	inner->sesionInfo = founder->second;
	inner->sesionInfo.status = SS_LOGINED;
	inner->sesionInfo.loginTime = time(NULL);
	_clients.erase(sID);
	UserManager::getRef().userLogin(inner, true);
	DBManager::getRef().infoAsyncQuery(UserInfo_UPDATE(inner->userInfo), nullptr);
	DBManager::getRef().infoAsyncQuery(UserInfo_UPDATE(inner->userInfo), std::bind(&NetManager::db_onUserCreate, this, std::placeholders::_1, sID) );
}
void NetManager::db_onUserCreate(DBResultPtr res, SessionID sID)
{
	LOGD("enter db_onUserCreate. sID=" << sID);
	LoginAck ack;
	if (res->getErrorCode() == QEC_SUCCESS)
	{
		ack.retCode = EC_SUCCESS;
		ack.needCreate = 0;
		auto inner = UserManager::getRef().getInnerUserInfoBySID(sID);
		if (inner)
		{
			ack.info = inner->userInfo;
		}
		else
		{
			ack.retCode = EC_DB_ERROR;
		}
	}
	else
	{
		ack.retCode = EC_DB_ERROR;
		ack.needCreate = 0;
	}
	
	WriteStream ws(ID_LoginAck);
	ws << ack;
	SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());

}


void NetManager::event_onPulse(SessionID sID, unsigned int pulseInterval)
{
	if (isSessionID(sID))
	{
		auto inner = UserManager::getRef().getInnerUserInfoBySID(sID);
		if (!inner)
		{
			//如果第一个心跳检测之前没有登录 直接踢掉
			SessionManager::getRef().kickSession(sID);
			LOGW("kick session because session not found in _mapSession.  sID=" << sID);
			return;
		}
		if (time(NULL) - inner->sesionInfo.lastActiveTime > pulseInterval *2)
		{
			SessionManager::getRef().kickSession(sID);
			LOGW("kick session because session heartbeat timeout.  sID=" << sID << ", lastActiveTime=" << inner->sesionInfo.lastActiveTime);
			return;
		}

		WriteStream ws(ID_ServerPulse);
		ServerPulse sp;
		sp.timeStamp = (ui32)time(NULL);
		sp.timeTick = getNowTick();
		ws << sp;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
}


void NetManager::msg_onServerPulseEcho(SessionID sID, ProtoID pID, ReadStream & rs)
{
	auto inner = UserManager::getRef().getInnerUserInfoBySID(sID);
	if (!inner)
	{
		return;
	}
	ServerPulseEcho cp;
	rs >> cp;
	inner->sesionInfo.lastActiveTime = time(NULL);
	inner->sesionInfo.lastDelayTick = (getNowTick() - cp.timeTick + inner->sesionInfo.lastDelayTick) / 2; //延迟检测 阻尼衰减
	LOGD("msg_onServerPulseEcho lastActiveTime=" << inner->sesionInfo.lastActiveTime << ", lastDelayTick=" << inner->sesionInfo.lastDelayTick << "ms");
}




