#include "netManager.h"
#include "dbManager.h"
#include "userManager.h"
#include <ProtoCommon_SQL.h>
#include "login/login.h"
NetManager::NetManager()
{
    //auth request process
    MessageDispatcher::getRef().registerSessionMessage(ID_LinkServerReq,
        std::bind(&NetManager::msg_onLinkServerReq, this, _1, _2));


    MessageDispatcher::getRef().registerSessionMessage(ID_HeartbeatEcho,
        std::bind(&NetManager::msg_onHeartbeatEcho, this, _1, _2));
}

bool NetManager::start()
{
    auto connecters = ServerConfig::getRef().getConfigConnect(LogicNode);
    for (auto con : connecters)
    {
        SessionID cID = SessionManager::getRef().addConnecter(con._remoteIP, con._remotePort);
        SessionManager::getRef().getConnecterOptions(cID)._onSessionLinked = std::bind(&NetManager::event_onSessionEstablished, this, _1);
        SessionManager::getRef().getConnecterOptions(cID)._onSessionClosed = std::bind(&NetManager::event_onSessionDisconnect, this, _1);
        if (cID == InvalidSeesionID)
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

    AccepterID _accepterID = SessionManager::getRef().addAccepter(ServerConfig::getRef().getConfigListen(LogicNode)._ip, ServerConfig::getRef().getConfigListen(LogicNode)._port);
    if (_accepterID == InvalidAccepterID)
    {
        LOGE("addAccepter error");
        return false;
    }
    
    SessionManager::getRef().getAccepterOptions(_accepterID)._sessionOptions._onSessionLinked = std::bind(&NetManager::event_onSessionEstablished, this, _1);
    SessionManager::getRef().getAccepterOptions(_accepterID)._sessionOptions._onSessionClosed = std::bind(&NetManager::event_onSessionDisconnect, this, _1);
    SessionManager::getRef().getAccepterOptions(_accepterID)._sessionOptions._onSessionPulse = std::bind(&NetManager::event_onSessionPulse, this, _1);
    if (!SessionManager::getRef().openAccepter(_accepterID))
    {
        LOGE("openAccepter error");
        return false;
    }
    else
    {
        LOGD("openAccepter seccuss.");
    }
    return true;
}

bool NetManager::stop(std::function<void()> onSafeClosed)
{
    onSafeClosed();
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

                session->setUserParam(USER_USER_ID, inner->userInfo.uID);
                session->setUserParam(USER_SESSION_STATUS, inner->userInfo.uID);
                session->setUserParam(USER_LAST_ACTIVE_TIME, time(NULL));

                WriteStream ws(ID_LinkServerAck);
                ws << ack;
                session->send(ws.getStream(), ws.getStreamLen());

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
    session->send(ws.getStream(), ws.getStreamLen());
}



void NetManager::event_onSessionPulse(TcpSessionPtr session)
{
    if (isSessionID(session->getSessionID()))
    {
        if (session->getUserParam(USER_SESSION_STATUS).getNumber() == SS_LOGINED 
            || time(NULL) - session->getUserParam(USER_LAST_ACTIVE_TIME).getNumber() > session->getOptions()._sessionPulseInterval*2)
        {
            session->close();
            return;
        }

        WriteStream ws(ID_Heartbeat);
        Heartbeat hb;
        hb.timeStamp = (ui32)time(NULL);
        hb.timeTick = getNowTick();
        ws << hb;
        session->send(ws.getStream(), ws.getStreamLen());
    }
}

void NetManager::msg_onHeartbeatEcho(TcpSessionPtr session, ReadStream & rs)
{
    session->setUserParam(USER_LAST_ACTIVE_TIME, time(NULL));
}




void NetManager::event_onSessionEstablished(TcpSessionPtr session)
{
    session->setUserParam(USER_SESSION_STATUS,SS_UNLOGIN);
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
        if (session->getUserParam(USER_SESSION_STATUS).getNumber() == SS_LOGINED)
        {
            auto info = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
            if (info)
            {
                UserManager::getRef().userLogout(info);
                info->sID = InvalidSeesionID;
            }
        }
        Login::getRef().event_onSessionDisconnect(session);

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
        if (session->getUserParam(USER_SESSION_STATUS).getNumber() != SS_LOGINED)
        {
            LOGW("on_preMessageProcess check authorization failed. protoID=" << pID << ", session authorization status=" << session->getUserParam(USER_SESSION_STATUS).getNumber());
            return false;
        }
    }
    return true;
}










