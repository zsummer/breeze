/*
* breeze License
* Copyright (C) 2015 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


/*
*  file desc 
*  network manager
*/




#ifndef _NET_MANAGER_H_
#define _NET_MANAGER_H_
#include <common.h>
#include <ProtoLogin.h>


class NetMgr :public Singleton<NetMgr>
{
public:
    NetMgr();
    bool init();
    bool start();
    bool stop(std::function<void()> onSafeClosed);
    bool buildData();
    bool loadData();
public:
    UserInfoPtr getUserInfo(UserID uID);
    bool sendToUser(UserID uID, const char * block, unsigned int len);
    bool sendToSession(SessionID sID, const char * block, unsigned int len);
    template<typename Proto>
    void broadcast(Proto & data, const UIDS &ids);
    template<typename Proto>
    void broadcast(Proto & data);
protected:
protected:
    UserInfoPtr createUser(const BaseInfo & info);


protected: //平台登录  
    void msg_onPlatAuthReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onCreateUserReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onSelectUserReq(TcpSessionPtr session, ReadStream & rs);
    void db_onFetchUsers(DBResultPtr result, TcpSessionPtr session);
    void db_onCreateUser(DBResultPtr result, TcpSessionPtr session, const BaseInfo &info);
protected:
    void event_onLinked(TcpSessionPtr session);
    void event_onClosed(TcpSessionPtr session);
    void event_onLogin(UserInfoPtr);
    void event_onLogout(UserInfoPtr);



    void msg_onAttachLogicReq(TcpSessionPtr session, ReadStream & rs);



    bool on_preMessageProcess(TcpSessionPtr session, const char * blockBegin, zsummer::proto4z::Integer blockSize);

    void event_onSessionPulse(TcpSessionPtr session);
    void msg_onHeartbeatEcho(TcpSessionPtr session, ReadStream & rs);
private:
    std::unordered_map<SessionID, UserInfoPtr> _mapSession;
    std::unordered_map<UserID, UserInfoPtr> _mapUserInfo;
    

    //login server
    GenObjectID _genID;
    std::unordered_map<std::string, std::map<UserID, BaseInfo>> _mapAccounts;
    //login server end.
private:
    AccepterID _innerAID = InvalidAccepterID;
    AccepterID _wAID = InvalidAccepterID;
    std::function<void()> _onSafeClosed;
};


template<typename Proto>
void NetMgr::broadcast(Proto & data, const UIDS &ids)
{
    if (!ids.empty())
    {
        WriteStream ws(Proto::GetProtoID());
        ws << data;
        for (auto id : ids)
        {
            NetMgr::getRef().sendToUser(id, ws.getStream(), ws.getStreamLen());
        }
    }
}

template<typename Proto>
void NetMgr::broadcast(Proto & data)
{
    WriteStream ws(Proto::GetProtoID());
    ws << data;
    for (auto pr : _mapSession)
    {
        if (pr.second && pr.second->sID != InvalidSessionID)
        {
            NetMgr::getRef().sendToSession(pr.second->sID, ws.getStream(), ws.getStreamLen());
        }
    }
}




































#endif
