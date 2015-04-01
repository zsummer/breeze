#include "netManager.h"
#include "dbManager.h"

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
	if (!DBManager::getRef().start())
	{
		return false;
	}
	//////////////////////////////////////////////////////////////////////////

	{
		auto ret = DBManager::getRef().getInfoDB()->query("desc tb_user");
		if (ret->getErrorCode() != QEC_SUCCESS)
		{
			LOGI("create talbe tb_user ");
			DBQuery q("CREATE TABLE `tb_user` ( "
				"`uid` bigint(20) unsigned NOT NULL, "
				"PRIMARY KEY(`uid`) "
				") ENGINE = MyISAM DEFAULT CHARSET = utf8");
			ret = DBManager::getRef().getInfoDB()->query(q.genSQL());
			if (ret->getErrorCode() != QEC_SUCCESS)
			{
				LOGE("create talbe tb_user error=" << ret->getLastError());
				return false;
			}
		}
		//版本升级自动alter add 新字段. 
		DBManager::getRef().getInfoDB()->query("alter table `tb_user` add `nickname` varchar(255) NOT NULL DEFAULT ''");
		DBManager::getRef().getInfoDB()->query("alter table `tb_user` add `iconID` smallint(10) NOT NULL DEFAULT '0'");
		DBManager::getRef().getInfoDB()->query("alter table `tb_user` add `diamond` int(10) NOT NULL DEFAULT '0'");
		DBManager::getRef().getInfoDB()->query("alter table `tb_user` add `giftDiamond` int(10) NOT NULL DEFAULT '0'");
		DBManager::getRef().getInfoDB()->query("alter table `tb_user` add `historyDiamond` int(10) NOT NULL DEFAULT '0'");
		DBManager::getRef().getInfoDB()->query("alter table `tb_user` add `joinTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00'");

		//加载所有用户数据
		UserID curID = 0;
		do
		{
			DBQuery q("select uid, nickname, iconID, diamond, giftDiamond, historyDiamond, joinTime from tb_user where uid >? limit 1000;");
			q.add(curID);
			auto result = DBManager::getRef().getInfoDB()->query(q.genSQL());
			if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
			{
				LOGE("loadUserInfo error. begin uid is " << curID << ",  sql error=" << result->getLastError());
				return false;
			}
			if (!result->haveRow())
			{
				//all already loaded.
				LOGI("all tb_user is already loaded.");
				break;
			}
			while (result->haveRow())
			{
				UserInfo info;
				std::string friends;
				std::string bag;
				*result >> info.uid;
				*result >> info.nickName;
				*result >> info.iconID;
				*result >> info.diamond;
				*result >> info.giftDiamond;
				*result >> info.hisotryDiamond;
				*result >> info.joinTime;
				curID = info.uid;
				NetManager::getRef().loadUserInfo(info);
			}

		} while (true);

	}


	//push MessageHandler
	//.....
	//add other MessageHandler at here
	//.....
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
		LOGI("OPEN Accepter true. ListenConfig=" << _configListen);
	}
	return true;
}

bool NetManager::stop()
{
	SessionManager::getRef().stop();
	return true;
}


void NetManager::loadUserInfo(const UserInfo & info)
{
	if (info.uid == InvalidUserID)
	{
		LOGW("loadUserInfo found InvalidUserID");
		return;
	}
	auto founder = _mapUserInfo.find(info.uid);
	if (founder != _mapUserInfo.end())
	{
		LOGW("loadUserInfo  the user be aready loaded. uid=" << info.uid);
		return;
	}

	auto inner = std::make_shared<InnerUserInfo>();
	inner->userInfo = info;
	_mapUserInfo.insert(std::make_pair(info.uid, inner));
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

bool NetManager::on_preMessageProcess(SessionID sid, const char * blockBegin, zsummer::proto4z::Integer blockSize)
{
	return true;
}


void NetManager::msg_onLoginReq(SessionID sID, ProtoID pID, ReadStream & rs)
{
	LoginReq req;
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
		WriteStream ws(ID_LoginAck);
		LoginAck ack;
		ack.retCode = BEC_AUTH_LIMITE_COUNT;
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		return;
	}
	
	innerInfo->sesionInfo.user = req.user;
	innerInfo->sesionInfo.passwd = req.passwd;
	innerInfo->status = InnerUserInfo::IUIT_AUTHING;

	
	DBQuery q("SELECT uid, passwd FROM `tb_auth` where user = ?");
	q.add(req.user);
	auto & db = DBManager::getRef().getAuthDB();
	DBManager::getRef().getAsync()->asyncQuery(db, q.genSQL(), std::bind(&NetManager::db_onAuthSelect, this,
		std::placeholders::_1, sID));

}

void NetManager::db_onAuthSelect(DBResultPtr res, SessionID sID)
{
	LOGD("enter db_authSelect. sID=" << sID);
	LoginAck ack;
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
		WriteStream ws(ID_LoginAck);
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
	}
	else
	{
		LOGD("user auth success. sID=" << sID << " req.user = " << innerInfo->sesionInfo.user << ", req.passwd = " << innerInfo->sesionInfo.passwd);
		innerInfo->sesionInfo.authTime = time(NULL);
		//检测用户状态 判断是否需要踢人, 重新拉取DB数据

		auto fder = _mapUserInfo.find(innerInfo->sesionInfo.uid);
		if (fder != _mapUserInfo.end())
		{

			//登录保护中
			if (fder->second->sesionInfo.sID != InvalidSeesionID 
				&& fder->second->status == InnerUserInfo::IUIT_LOGINING 
				&& time(NULL) - fder->second->sesionInfo.authTime < 300)
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
				innerInfo->sesionInfo.loginTime = time(NULL);
				innerInfo->sesionInfo.lastActiveTime = time(NULL);
				ack.info = innerInfo->userInfo;
				WriteStream ws(ID_LoginAck);
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
		DBQuery q;
		q.init("select uid, nickname, iconID, diamond, giftDiamond,historyDiamond, UNIX_TIMESTAMP(joinTime) from tb_user where uid = ?");
		q.add(innerInfo->sesionInfo.uid);
		DBManager::getRef().getAsync()->asyncQuery(db, q.genSQL(), std::bind(&NetManager::db_onUserSelect, this,
			std::placeholders::_1, sID, false));
	}
}

void NetManager::db_onUserSelect(DBResultPtr res, SessionID sID, bool isCreateUser)
{
	LOGD("enter db_onUserSelect. sID=" << sID);
	LoginAck ack;
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
		WriteStream ws(ID_LoginAck);
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
			WriteStream ws(ID_LoginAck);
			ack.info = innerInfo->userInfo;
			ws << ack;
			SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			if (ack.retCode != BEC_AUTH_ACCOUNT_INCORRECT)
			{
				innerInfo->status = InnerUserInfo::IUIT_LOGINED;
				innerInfo->sesionInfo.loginTime = time(NULL);
				userLogin(innerInfo);
			}
		}
	}
}


void NetManager::msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStream &rs)
{
	CreateUserReq req;
	rs >> req;
	auto fouder = _mapUserSession.find(sID);
	if (fouder == _mapUserSession.end() || fouder->second->status != InnerUserInfo::IUIT_LOGINING)
	{
		SessionManager::getRef().kickSession(sID);
		return;
	}
	fouder->second->userInfo.uid = fouder->second->sesionInfo.uid;
	fouder->second->userInfo.nickName = req.nickName;
	fouder->second->userInfo.iconID = req.iconID;

	auto & db = DBManager::getRef().getInfoDB();
	DBQuery q("insert into tb_user(uid, nickname, iconID, joinTime) values(?, ?, ?, now());");
	q.add(fouder->second->sesionInfo.uid);
	q.add(req.nickName);
	q.add(req.iconID);
	DBManager::getRef().getAsync()->asyncQuery(db, q.genSQL(), std::bind(&NetManager::db_onUserCreate, this,
		std::placeholders::_1, sID ));
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
	
	CreateUserAck ack;
	ack.retCode = BEC_DB_ERROR;


	if (res->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("db_onUserCreate error.  error msg=" << res->getLastError() << ",  sql=" << res->sqlString());
	}
	else
	{
		ack.retCode = BEC_SUCCESS;
	}


	if (ack.retCode == BEC_SUCCESS)
	{
		ack.info = innerInfo->userInfo;
		WriteStream ws(ID_CreateUserAck);
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		innerInfo->sesionInfo.loginTime = time(NULL);
		userLogin(innerInfo);

/*			//blob test
		DBQuery q;
		q.init("update tb_user set bag=? where uid=?");
		std::string apendBin;
		for (int i = 0; i < 256; i++)
		{
			apendBin.append(1, (char)i);
		}
		WriteStream wsdb(0);
		wsdb << ack.info;
		wsdb << apendBin;
		std::string blob(wsdb.getStreamBody(), wsdb.getStreamBodyLen());
		q.add(blob);
		q.add(ack.info.uid);
		auto & db = DBManager::getRef().getInfoDB();
		DBAsync::getRef().asyncQuery(db, q.genSQL(), std::bind(&NetManager::db_onTestBlog, this, std::placeholders::_1, false));
		q.init("select bag from tb_user where uid=?");
		q.add(ack.info.uid);
		DBAsync::getRef().asyncQuery(db, q.genSQL(), std::bind(&NetManager::db_onTestBlog, this, std::placeholders::_1, true));
		*/
	}
	else
	{
		WriteStream ws(ID_CreateUserAck);
		ws << ack;
		SessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
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
	auto founder = _mapUserSession.find(sID);
	if (founder != _mapUserSession.end())
	{
		ServerPulseEcho cp;
		rs >> cp;
		founder->second->sesionInfo.lastActiveTime = time(NULL);
		founder->second->sesionInfo.lastDelayTick = (getNowTick() - cp.timeTick + founder->second->sesionInfo.lastDelayTick) / 2; //延迟检测 阻尼衰减
		LOGD("msg_onServerPulseEcho lastActiveTime=" << founder->second->sesionInfo.lastActiveTime <<", lastDelayTick=" << founder->second->sesionInfo.lastDelayTick << "ms");
		return;
	}
}




