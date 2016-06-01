/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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






#ifndef _DOCKER_H_
#define _DOCKER_H_
#include <common.h>
#include "service.h"
#include <ProtoDocker.h>

struct DockerSession
{
    DockerID dokerID = InvalidDockerID;
    SessionID sessionID = InvalidSessionID;
    int status; //0 invalid, 1 valid
};


class Docker : public Singleton<Docker>
{
public:
    Docker();
    bool init(const std::string & config, DockerID idx);
    bool start();
    void stop();
    bool run();
public:
    template<class Proto>
    void sendToSession(SessionID sessionID, const Proto & proto);
    void sendToSession(SessionID sessionID, const char * block, unsigned int len);

    void forwardToSession(SessionID sessionID, const Tracing & trace, const char * block, unsigned int len);
    template<class Proto>
    void forwardToSession(SessionID sessionID, const Tracing & trace, const Proto & proto);

    template<class Proto>
    void sendToDocker(DockerID dockerID, const Proto & proto);
    void sendToDocker(DockerID dockerID, const char * block, unsigned int len);

    template<class Proto>
    void forwardToDocker(DockerID dockerID, const Tracing & trace, const Proto & proto);
    void forwardToDocker(DockerID dockerID, const Tracing & trace, const char * block, unsigned int len);

    template<class Proto>
    void broadcastToDockers(const Proto & proto, bool withme);
    template<class Proto>
    void broadcastToDockers(const Proto & proto, const Tracing & trace, bool withme);

public:


    //canForwardToOtherService 如果是来自其他docker的转发 不应该再转发出去.  
    //needPost 如果是来自本地到本地的服务, 需要进行post解耦, 不应该直接调用process. 
    void toService(Tracing trace, const char * block, unsigned int len, bool canForwardToOtherService, bool needPost);
    template<class Proto>
    void toService(Tracing trace, Proto proto, bool canForwardToOtherService, bool needPost);
public:
    bool isStoping();

private:
    bool startDockerListen();
    bool startDockerConnect();
    bool startDockerWideListen();

public:
    ServicePtr createService(ui16 serviceType, ServiceID serviceID, DockerID dockerID, DockerID clientDockerID, SessionID clientSession, bool isShell, bool failExit);
    void destroyService(ui16 serviceType, ServiceID serviceID);
public:
    void checkServiceState();
    void onCheckSafeExit();


private:
    void event_onServiceLinked(TcpSessionPtr session);
    void event_onServiceClosed(TcpSessionPtr session);
    void event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void event_onClientLinked(TcpSessionPtr session);
    void event_onClientClosed(TcpSessionPtr session);
    void event_onClientMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void event_onClientPulse(TcpSessionPtr   session);
private:
    void event_onCreateServiceInDocker(TcpSessionPtr session, ReadStream & rs);
    void event_onChangeServiceClientID(TcpSessionPtr session, ReadStream & rs);
    void event_onCreateOrRefreshServiceNotice(TcpSessionPtr session, ReadStream & rs);
    void event_onDestroyServiceInDocker(TcpSessionPtr session, ReadStream & rs);
    void event_onDestroyServiceNotice(TcpSessionPtr session, ReadStream & rs);

    void event_onForwardToService(TcpSessionPtr session, ReadStream & rs);


private:
    std::unordered_map<ui16, std::unordered_map<ServiceID, ServicePtr > > _services;
    std::map <DockerID, DockerSession> _dockerSession;
    bool _dockerNetWorking = false;
    bool _dockerServiceWorking = false;
    AccepterID _wlisten = InvalidAccepterID;
private:
    //std::map<SessionID, ServiceID> _clientToService; //store in session
};






template<class Proto>
void Docker::broadcastToDockers(const Proto & proto, bool withme)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        for (const auto &c : _dockerSession)
        {
            if (c.second.sessionID == InvalidSessionID)
            {
                LOGF("Docker::broadcastToDockers fatal error. dockerID not have session. dockerID=" << c.first << ", proto id=" << Proto::getProtoID());
                continue;
            }
            if (c.second.status == 0)
            {
                LOGW("Docker::broadcastToDockers warning error. session try connecting. dockerID=" << c.first << ", client session ID=" << c.second.sessionID);
            }
            if (withme || ServerConfig::getRef().getDockerID() != c.first)
            {
                sendToSession(c.second.sessionID, ws.getStream(), ws.getStreamLen());
            }
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::broadcast catch except error. e=" << e.what());
    }
}

template<class Proto>
void Docker::broadcastToDockers(const Proto & proto, const Tracing & trace, bool withme)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        WriteStream forward(ForwardToService::getProtoID());
        forward << trace;
        forward.appendOriginalData(ws.getStream(), ws.getStreamLen());
        for (const auto &c : _dockerSession)
        {
            if (c.second.sessionID == InvalidSessionID)
            {
                LOGF("Docker::broadcastToDockers fatal error. dockerID not have session. dockerID=" << c.first << ", proto id=" << Proto::getProtoID());
                continue;
            }
            if (c.second.status == 0)
            {
                LOGW("Docker::broadcastToDockers warning error. session try connecting. dockerID=" << c.first << ", client session ID=" << c.second.sessionID);
            }
            if (withme || ServerConfig::getRef().getDockerID() != c.first)
            {
                sendToSession(c.second.sessionID, forward.getStream(), forward.getStreamLen());
            }
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::broadcast catch except error. e=" << e.what());
    }
}

template<class Proto>
void Docker::sendToSession(SessionID sessionID, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        SessionManager::getRef().sendSessionData(sessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::sendToSession catch except error. e=" << e.what());
    }
}



template<class Proto>
void Docker::forwardToSession(SessionID sessionID, const Tracing & trace, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        forwardToSession(sessionID, trace, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::forwardToSession catch except error. e=" << e.what());
    }
}

template<class Proto>
void Docker::sendToDocker(DockerID dockerID, const Proto & proto)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.sessionID != InvalidSessionID && founder->second.status != 0)
    {
        sendToSession(founder->second.sessionID, proto);
    }
    else
    {
        LOGE("Docker::sendToDocker not found docker. dockerID=" << dockerID);
    }
}

template<class Proto>
void Docker::forwardToDocker(DockerID dockerID, const Tracing & trace, const Proto & proto)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.sessionID != InvalidSessionID && founder->second.status != 0)
    {
        forwardToSession(founder->second.sessionID, trace, proto);
    }
    else
    {
        LOGE("Docker::forwardToDocker not found docker. dockerID=" << dockerID);
    }
}





template<class Proto>
void Docker::toService(Tracing trace, Proto proto, bool canForwardToOtherService, bool needPost)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(trace, ws.getStream(), ws.getStreamLen(), canForwardToOtherService, needPost);
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::toService catch except error. e=" << e.what());
    }
}























#endif
