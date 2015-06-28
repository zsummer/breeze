#include "netManager.h"
#include "dbManager.h"
#include "userManager.h"
#include <ProtoCommon_SQL.h>

NetManager::NetManager()
{
    //auth request process
    MessageDispatcher::getRef().registerSessionMessage(ID_LinkServerReq,
        std::bind(&NetManager::msg_onLinkServerReq, this, _1, _2));



    MessageDispatcher::getRef().registerSessionPreMessage(std::bind(&NetManager::on_preMessageProcess, this, _1, _2, _3));
    
    //register event
    MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(&NetManager::event_onSessionEstablished, this, _1));
    MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(&NetManager::event_onSessionDisconnect, this, _1));

    //
    MessageDispatcher::getRef().registerOnSessionPulse(std::bind(&NetManager::event_onSessionPulse, this, _1, _2));

    MessageDispatcher::getRef().registerSessionMessage(ID_HeartbeatEcho,
        std::bind(&NetManager::msg_onHeartbeatEcho, this, _1, _2));
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
//     SessionManager::getRef().stopAccept();
//     SessionManager::getRef().kickAllClients();
//     SessionManager::getRef().kickAllConnect();
// 
//     if (UserManager::getRef().getAllOnlineUserCount() == 0)
//     {
//         SessionManager::getRef().post(onSafeClosed);
//     }
//     else
//     {
//         _onSafeClosed = onSafeClosed;
//     }
    return true;
}






void NetManager::msg_onLinkServerReq(TcpSessionPtr session, ReadStream & rs)
{
    LinkServerReq req;
    rs >> req;
    LOGD("enter msg_loginReq token=" << req.token << ", uID=" << req.uID);
    LinkServerAck ack;
    ack.retCode = EC_SUCCESS;

    auto inner = UserManager::getRef().getInnerUserInfo(req.uID);
    if (inner)
    {
        if (inner->token.token == req.token)
        {
            if (inner->token.tokenExpire > time(NULL))
            {
                ack.retCode = EC_SUCCESS;
                if (inner->sID != InvalidSeesionID)
                {
                    UserManager::getRef().userLogout(inner);
                }

                inner->loginTime = time(NULL);
                inner->sID = session->getSessionID();

                session->setUserParam(inner->userInfo.uID);
                session->setUserLParam(SS_LOGINED);
                session->setUserRParam(time(NULL));
                WriteStream ws(ID_LinkServerAck);
                ws << ack;
                session->doSend(ws.getStream(), ws.getStreamLen());

                UserManager::getRef().userLogin(inner);
                return;
            }
            else
            {
                ack.retCode = EC_TOKEN_EXPIRE;
            }
        }
        else
        {
            ack.retCode = EC_USER_NOT_FOUND;
        }
        
    }
    else
    {
        ack.retCode = EC_USER_NOT_FOUND;
    }
    
    WriteStream ws(ID_LinkServerAck);
    ws << ack;
    session->doSend(ws.getStream(), ws.getStreamLen());
}



void NetManager::event_onSessionPulse(TcpSessionPtr session, unsigned int pulseInterval)
{
    if (isSessionID(session->getSessionID()))
    {
        if (session->getUserLParam() == SS_LOGINED || time(NULL) - session->getUserRParam() > pulseInterval * 2)
        {
            session->close();
            return;
        }

        WriteStream ws(ID_Heartbeat);
        Heartbeat hb;
        hb.timeStamp = (ui32)time(NULL);
        hb.timeTick = getNowTick();
        ws << hb;
        session->doSend(ws.getStream(), ws.getStreamLen());
    }
}

void NetManager::msg_onHeartbeatEcho(TcpSessionPtr session, ReadStream & rs)
{
    session->setUserLParam(time(NULL));
}




void NetManager::event_onSessionEstablished(TcpSessionPtr session)
{
    session->setUserLParam(SS_UNLOGIN);
    LOGT("NetManager::event_onSessionEstablished. SessionID=" << session->getSessionID() << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());
}

void NetManager::event_onSessionDisconnect(TcpSessionPtr session)
{
    LOGT("NetManager::event_onSessionDisconnect. SessionID=" << session->getSessionID() << ", remoteIP=" << session->getRemoteIP() << ", remotePort=" << session->getRemotePort());

    if (isConnectID(session->getSessionID()))
    {
    }
    else
    {
        if (session->getUserParam() == SS_LOGINED)
        {
            auto info = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
            if (info)
            {
                UserManager::getRef().userLogout(info);
                info->sID = InvalidSeesionID;
            }
        }

    }

    if (UserManager::getRef().getAllOnlineUserCount() == 0 && _onSafeClosed)
    {
        SessionManager::getRef().post(_onSafeClosed);
        _onSafeClosed = nullptr;
    }
}


//param is userID
//lparam is loginstatus
//rparam is lastactive time

bool NetManager::on_preMessageProcess(TcpSessionPtr session, const char * blockBegin, zsummer::proto4z::Integer blockSize)
{
    ReadStream rs(blockBegin, blockSize);
    ProtoID pID = rs.getProtoID();
    if (pID >= 200)
    {
        if (session->getUserLParam() != SS_LOGINED)
        {
            LOGW("on_preMessageProcess check authorization failed. protoID=" << pID << ", session authorization status=" << session->getUserParam());
            return false;
        }
    }
    return true;
}










