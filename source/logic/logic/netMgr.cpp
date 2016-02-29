#include "netMgr.h"
#include "dbMgr.h"
#include <ProtoCommon_SQL.h>
NetMgr::NetMgr()
{
    //平台登录  
    MessageDispatcher::getRef().addListener(PlatAuthReq::GetProtoID(), std::bind(&NetMgr::msg_onPlatAuthReq, this, _1, _2));
    MessageDispatcher::getRef().addListener(CreateUserReq::GetProtoID(), std::bind(&NetMgr::msg_onCreateUserReq, this, _1, _2));
    MessageDispatcher::getRef().addListener(SelectUserReq::GetProtoID(), std::bind(&NetMgr::msg_onSelectUserReq, this, _1, _2));

    //auth request process
    MessageDispatcher::getRef().addListener(AttachLogicReq::GetProtoID(),
        std::bind(&NetMgr::msg_onAttachLogicReq, this, _1, _2));


    MessageDispatcher::getRef().addListener(HeartbeatEcho::GetProtoID(),
        std::bind(&NetMgr::msg_onHeartbeatEcho, this, _1, _2));
}


bool NetMgr::init()
{
    _genID.initConfig(ServerConfig::getRef().getAreaID());
    return buildData() && loadData();
}


bool NetMgr::buildData()
{
    auto build = BaseInfo_BUILD();
    if (DBMgr::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
    {
        if (DBMgr::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("create table error. sql=" << build[1]);
            return false;
        }
    }
    for (size_t i = 2; i < build.size(); i++)
    {
        DBMgr::getRef().infoQuery(build[i]);
    }
    return true;
}

bool NetMgr::loadData()
{
    //加载所有用户数据
    unsigned long long curID = 0;
    do
    {
        auto sql = BaseInfo_LOAD(curID);
        auto result = DBMgr::getRef().infoQuery(sql);
        if (result->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("load contact error. curID:" << curID << ", err=" << result->getLastError());
            return false;
        }
        if (!result->haveRow())
        {
            break;
        }
        auto mapInfo = BaseInfo_FETCH(result);
        for (auto & kv : mapInfo)
        {
            if (kv.first > _genID.getCurID())
            {
                _genID.setCurID(kv.first);
            }
            createUser(kv.second);
        }
        curID += mapInfo.size();
    } while (true);
    return true;
}

bool NetMgr::start()
{
    auto connecters = ServerConfig::getRef().getConfigConnect(LogicServer);
    for (auto con : connecters)
    {
        SessionID cID = SessionManager::getRef().addConnecter(con._remoteIP, con._remotePort);
        SessionManager::getRef().getConnecterOptions(cID)._onSessionLinked = std::bind(&NetMgr::event_onLinked, this, _1);
        SessionManager::getRef().getConnecterOptions(cID)._onSessionClosed = std::bind(&NetMgr::event_onClosed, this, _1);
        SessionManager::getRef().getConnecterOptions(cID)._onBlockDispatch = [](TcpSessionPtr   session, const char * begin, unsigned int len)
        {
            ReadStream rs(begin, len);
            MessageDispatcher::getRef().dispatch(session, rs.getProtoID(), rs);
        };
        if (cID == InvalidSessionID)
        {
            LOGE("addConnecter error.");
            return false;
        }
        if (!SessionManager::getRef().openConnecter(cID))
        {
            LOGE("openConnecter error.");
            return false;
        }
    }

    _innerAID = SessionManager::getRef().addAccepter(ServerConfig::getRef().getConfigListen(LogicServer)._ip, ServerConfig::getRef().getConfigListen(LogicServer)._port);
    if (_innerAID == InvalidAccepterID)
    {
        LOGE("addAccepter error");
        return false;
    }
    SessionManager::getRef().getAccepterOptions(_innerAID)._whitelistIP = ServerConfig::getRef().getConfigListen(LogicServer)._whiteList;
    SessionManager::getRef().getAccepterOptions(_innerAID)._sessionOptions._onSessionLinked = std::bind(&NetMgr::event_onLinked, this, _1);
    SessionManager::getRef().getAccepterOptions(_innerAID)._sessionOptions._onSessionClosed = std::bind(&NetMgr::event_onClosed, this, _1);
    SessionManager::getRef().getAccepterOptions(_innerAID)._sessionOptions._onSessionPulse = std::bind(&NetMgr::event_onSessionPulse, this, _1);
    SessionManager::getRef().getAccepterOptions(_innerAID)._sessionOptions._onBlockDispatch = DispatchFunction;
    if (!SessionManager::getRef().openAccepter(_innerAID))
    {
        LOGE("openAccepter error");
        return false;
    }
    else
    {
        LOGI("openAccepter seccuss.");
    }
    if (ServerConfig::getRef().getConfigListen(LogicServer)._port != 0)
    {
        _wAID = SessionManager::getRef().addAccepter(ServerConfig::getRef().getConfigListen(LogicServer)._wip, ServerConfig::getRef().getConfigListen(LogicServer)._wport);
        if (_wAID != InvalidAccepterID)
        {
            SessionManager::getRef().getAccepterOptions(_wAID)._sessionOptions._onSessionLinked = std::bind(&NetMgr::event_onLinked, this, _1);
            SessionManager::getRef().getAccepterOptions(_wAID)._sessionOptions._onSessionClosed = std::bind(&NetMgr::event_onClosed, this, _1);
            SessionManager::getRef().getAccepterOptions(_wAID)._sessionOptions._onSessionPulse = std::bind(&NetMgr::event_onSessionPulse, this, _1);
            SessionManager::getRef().getAccepterOptions(_wAID)._sessionOptions._onBlockDispatch = DispatchFunction;
            SessionManager::getRef().openAccepter(_wAID);
        }
        
    }
    
    return true;
}

bool NetMgr::stop(std::function<void()> onSafeClosed)
{
    onSafeClosed();
    return true;
}

UserInfoPtr NetMgr::createUser(const BaseInfo & info)
{
    if (info.uID == InvalidUserID)
    {
        LOGE("NetMgr::createUser error. uID is invalid");
        return nullptr;
    }
    if (_mapUserInfo.find(info.uID) != _mapUserInfo.end())
    {
        LOGE("NetMgr::createUser error. user info already had. uid=" << info.uID);
        return nullptr;
    }
    auto data = std::make_shared<UserInfo>();
    data->sID = InvalidSessionID;
    data->base = info;
    data->token.uID = info.uID;
    auto ret = _mapUserInfo.insert(std::make_pair(data->base.uID, data));
    if (!ret.second)
    {
        return nullptr;
    }
    return ret.first->second;
}

UserInfoPtr NetMgr::getUserInfo(UserID uID)
{
    auto founder = _mapUserInfo.find(uID);
    if (founder != _mapUserInfo.end())
    {
        return founder->second;
    }
    return nullptr;
}

bool NetMgr::sendToUser(UserID uID, const char * block, unsigned int len)
{
    auto user = getUserInfo(uID);
    if (user && user->sID != InvalidSessionID)
    {
        SessionManager::getRef().sendSessionData(user->sID, block, len);
        return true;
    }
    return false;
}

bool NetMgr::sendToSession(SessionID sID, const char * block, unsigned int len)
{
    SessionManager::getRef().sendSessionData(sID, block, len);
    return true;
}



void NetMgr::msg_onAttachLogicReq(TcpSessionPtr session, ReadStream & rs)
{
    if (std::get<TupleParamNumber>(session->getUserParam(UPARAM_SESSION_STATUS)) != SSTATUS_UNKNOW)
    {
        return;
    }
    
    AttachLogicAck ack;
    ack.retCode = EC_SUCCESS;
    AttachLogicReq req;
    rs >> req;
    LOGD("enter msg_loginReq token=" << req.token << ", uID=" << req.uID);
    do 
    {
        auto info = getUserInfo(req.uID);
        if (!info)
        {
            ack.retCode = EC_TARGET_NOT_EXIST;
            break;
        }
        if (info->token.token != req.token)
        {
            ack.retCode = EC_PERMISSION_DENIED;
            break;
        }
        if (info->token.expire < time(NULL))
        {
            ack.retCode = EC_REQUEST_EXPIRE;
            break;
        }

        if (info->sID != InvalidSessionID)
        {
            event_onLogout(info);
            SessionManager::getRef().kickSession(info->sID);
            _mapSession.erase(info->sID);
        }

        info->sID = session->getSessionID();
        session->setUserParam(UPARAM_USER_ID, info->base.uID);
        session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_LOGINED);
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, time(NULL));
        session->setUserParam(UPARAM_LOGIN_TIME, time(NULL));
        _mapSession.insert(std::make_pair(session->getSessionID(), info));

        sendMessage(session, ack);
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, time(NULL));

        event_onLogin(info);
        
        return;
    } while (0);
    
    sendMessage(session, ack);
}



void NetMgr::event_onSessionPulse(TcpSessionPtr session)
{
    if (isSessionID(session->getSessionID()))
    {
        if (time(NULL) - session->getUserParamNumber(UPARAM_LAST_ACTIVE_TIME) > session->getOptions()._sessionPulseInterval / 1000 * 2)
        {
            session->close();
            return;
        }
        Heartbeat hb;
        hb.timeStamp = (ui32)time(NULL);
        hb.timeTick = (unsigned int)getMSecTick();
        sendMessage(session, hb);
    }
}

void NetMgr::msg_onHeartbeatEcho(TcpSessionPtr session, ReadStream & rs)
{
    auto status = session->getUserParamNumber(UPARAM_SESSION_STATUS);
    if (status != SSTATUS_UNKNOW && status != SSTATUS_PLAT_LOGINING)
    {
        session->setUserParam(UPARAM_LAST_ACTIVE_TIME, time(NULL));
    }
}




void NetMgr::event_onLinked(TcpSessionPtr session)
{
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);
    LOGD("NetMgr::event_onLinked. SessionID=" << session->getSessionID() << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}

void NetMgr::event_onClosed(TcpSessionPtr session)
{
    LOGD("NetMgr::event_onClosed. SessionID=" << session->getSessionID() << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());

    if (isConnectID(session->getSessionID()))
    {
    }
    else
    {
        if (session->getUserParamNumber(UPARAM_SESSION_STATUS) == SSTATUS_LOGINED)
        {
            auto founder = _mapUserInfo.find(session->getUserParamNumber(UPARAM_USER_ID));
            if (founder == _mapUserInfo.end() || founder->second->sID != session->getSessionID())
            {
                _mapSession.erase(session->getSessionID());
                return;
            }
            
            event_onLogout(founder->second);
            founder->second->sID = InvalidSessionID;
        }
        _mapSession.erase(session->getSessionID());
    }

    if (_mapSession.size() == 0 && _onSafeClosed)
    {
        SessionManager::getRef().post(_onSafeClosed);
        _onSafeClosed = nullptr;
    }
}

void NetMgr::event_onLogin(UserInfoPtr)
{

}

void NetMgr::event_onLogout(UserInfoPtr)
{

}


//param is userID
//lparam is loginstatus
//rparam is lastactive time

bool NetMgr::on_preMessageProcess(TcpSessionPtr session, const char * blockBegin, zsummer::proto4z::Integer blockSize)
{
    ReadStream rs(blockBegin, blockSize);
    ProtoID pID = rs.getProtoID();
    if (pID >= 200)
    {
        if (session->getUserParamNumber(UPARAM_SESSION_STATUS) != SSTATUS_LOGINED)
        {
            LOGW("on_preMessageProcess check authorization failed. protoID=" << pID << ", session authorization status=" << session->getUserParamNumber(UPARAM_SESSION_STATUS));
            return false;
        }
    }
    return true;
}




void NetMgr::msg_onPlatAuthReq(TcpSessionPtr session, ReadStream & rs)
{
    if (session->getUserParamNumber(UPARAM_SESSION_STATUS) != SSTATUS_UNKNOW)
    {
        LOGE("NetMgr::msg_onPlatAuthReq. status error .session id=" << session->getSessionID() << ", status = " << session->getUserParamNumber(UPARAM_SESSION_STATUS));
        session->close();
        return;
    }
    PlatAuthReq req;
    rs >> req;
    session->setUserParam(UPARAM_ACCOUNT, req.account);

    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_PLAT_LOGINING);
    //goto plat auth
    //....
    //plat auth success.
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_PLAT_LOGINED);

    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_PLAT_LOADING);
    zsummer::mysql::DBQuery q(" select `uID`,`account`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime` from `tb_BaseInfo` where `account` = ? ");
    q << req.account;
    DBMgr::getRef().infoAsyncQuery(q.popSQL(), std::bind(&NetMgr::db_onFetchUsers, this, _1, session));
}

void NetMgr::db_onFetchUsers(DBResultPtr result, TcpSessionPtr session)
{
    //loading guard over.
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_PLAT_LOGINED);

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
            BaseInfo info;
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
                _mapAccounts[session->getUserParamString(UPARAM_ACCOUNT)][info.uID] = info;
            }

        }
        catch (std::runtime_error e)
        {
            ack.retCode = EC_DB_ERROR;
            LOGE("Login::db_onFetchUsers catch one exception. e=" << e.what() << ", sql=" << result->sqlString());
        }
    }
    sendMessage(session, ack);
}

void NetMgr::msg_onCreateUserReq(TcpSessionPtr session, ReadStream & rs)
{
    if (session->getUserParamNumber(UPARAM_SESSION_STATUS) != SSTATUS_PLAT_LOGINED)
    {
        LOGE("NetMgr::msg_onCreateUserReq. status error. session id=" << session->getSessionID() << ", status = " << session->getUserParamNumber(UPARAM_SESSION_STATUS));
        session->close();
        return;
    }

    auto founder = _mapAccounts.find(session->getUserParamString(UPARAM_ACCOUNT));
    if (founder != _mapAccounts.end() && founder->second.size() > MAX_ACCOUNT_USERS)
    {
        LOGW("Login::msg_onCreateUserReq  too many users. sID=" << session->getSessionID());
        return;
    }

    

    CreateUserReq req;
    rs >> req;
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_PLAT_CREATING);
    BaseInfo info;
    info.uID = _genID.genNewObjID();
    info.account = session->getUserParamString(UPARAM_ACCOUNT);
    info.nickName = req.nickName;
    info.iconID = req.iconID;
    info.joinTime = (ui32)time(NULL);
    _mapAccounts[session->getUserParamString(UPARAM_ACCOUNT)][info.uID] = info;

    std::string sql = BaseInfo_INSERT(info);
    DBMgr::getRef().infoAsyncQuery(sql, std::bind(&NetMgr::db_onCreateUser, this, _1, session, info));
}

void NetMgr::db_onCreateUser(DBResultPtr result, TcpSessionPtr session, const BaseInfo & info)
{
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_PLAT_LOGINED);
    CreateUserAck ack;
    ack.retCode = EC_SUCCESS;
    if (result->getErrorCode() != QEC_SUCCESS)
    {
        ack.retCode = EC_DB_ERROR;
        _mapAccounts[info.account].erase(info.uID);
    }
    else
    {
        //!模拟 通知logic服务器添加新的用户
        createUser(info);
        ack.users.push_back(info);
        //end
    }
    sendMessage(session, ack);
}



void NetMgr::msg_onSelectUserReq(TcpSessionPtr session, ReadStream & rs)
{
    if (session->getUserParamNumber(UPARAM_SESSION_STATUS) != SSTATUS_PLAT_LOGINED)
    {
        LOGE("NetMgr::msg_onSelectUserReq. status error. session id=" << session->getSessionID() << ", status = " << session->getUserParamNumber(UPARAM_SESSION_STATUS));
        session->close();
        return;
    }

    auto founder = _mapAccounts.find(session->getUserParamString(UPARAM_ACCOUNT));
    if (founder == _mapAccounts.end())
    {
        LOGW("Login::msg_onSelectUserReq session have no account info. sID=" << session->getSessionID());
        return;
    }

    SelectUserReq req;
    rs >> req;

    auto base = founder->second.find(req.uID);
    if (base == founder->second.end())
    {
        LOGW("Login::msg_onSelectUserReq session have no user info. sID=" << session->getSessionID());
        return;
    }


    MD5Data data;
    data.append(base->second.account);
    data.append(base->second.nickName);
    data.append(toString(rand()));

    //模拟通知logic刷新token
    auto ptr = getUserInfo(req.uID);
    if (!ptr)
    {
        return;
    }
    ptr->token.uID = req.uID;
    ptr->token.token = data.genMD5();
    ptr->token.expire = (unsigned int)time(NULL) + 600;

    //模拟断开连接
    session->setUserParam(UPARAM_SESSION_STATUS, SSTATUS_UNKNOW);


    SelectUserAck ack;
    ack.retCode = EC_SUCCESS;
    ack.uID = req.uID;
    ack.token = data.genMD5();
    ack.ip = ServerConfig::getRef().getConfigListen(LogicServer)._wip;
    ack.port = ServerConfig::getRef().getConfigListen(LogicServer)._wport;

    sendMessage(session, ack);
}






