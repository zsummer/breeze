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






#ifndef _NET_MANAGER_H_
#define _NET_MANAGER_H_
#include <common.h>
#include "service.h"
#include <ProtoDocker.h>


class Application : public Singleton<Application>
{
public:
    Application();
    bool init(const std::string & config, DockerID idx);
    bool start();
    void stop();
    bool run();
public:
    template<class Proto>
    void broadcast(const Proto & proto, bool withme);
    template<class Proto>
    void broadcast(const Proto & proto, const Tracing & trace, bool withme);

    template<class Proto>
    void sendToSession(SessionID sessionID, const Proto & proto);
    template<class Proto>
    void sendToSession(SessionID sessionID, const Tracing & trace, const Proto & proto);

    template<class Proto>
    void sendToDocker(DockerID dockerID, const Proto & proto);
    template<class Proto>
    void sendToDocker(DockerID dockerID, const Tracing & trace, const Proto & proto);
    void sendToDocker(DockerID dockerID, const char * block, unsigned int len);

    void callOtherService(Tracing trace, const char * block, unsigned int len);
    bool isStoping();

private:
    bool startDockerListen();
    bool startDockerConnect();
    bool startWideListen();

public:
    ServicePtr createService(ui16 serviceType, ServiceID serviceID, DockerID dockerID, SessionID clientID, bool isShell, bool failExit);
    bool destroyService(ui16 serviceType, ServiceID serviceID);
    void checkServiceState();
    void onCheckSafeExit();


private:
    void event_onServiceLinked(TcpSessionPtr session);
    void event_onServiceClosed(TcpSessionPtr session);

    void event_onCreateServiceInDocker(TcpSessionPtr session, ReadStream & rs);
    void event_onCreateServiceNotice(TcpSessionPtr session, ReadStream & rs);
    void event_onDestroyServiceInDocker(TcpSessionPtr session, ReadStream & rs);
    void event_onDestroyServiceNotice(TcpSessionPtr session, ReadStream & rs);

    void event_onRemoteShellForward(TcpSessionPtr session, ReadStream & rs);
    void event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);


    void event_onClientLinked(TcpSessionPtr session);
    void event_onClientClosed(TcpSessionPtr session);
    void event_onClientMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void event_onClientPulse(TcpSessionPtr   session);
private:
    std::unordered_map<ui16, std::unordered_map<ServiceID, ServicePtr > > _services;

    std::map < DockerID, std::pair<SessionID, int>> _dockerSession;
    bool _dockerNetWorking = false;
    bool _dockerServiceWorking = false;
    AccepterID _wlisten = InvalidAccepterID;
    

};






template<class Proto>
void Application::broadcast(const Proto & proto, bool withme)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        for (const auto &c : _dockerSession)
        {
            if (c.second.first == InvalidSessionID)
            {
                LOGF("Application::broadcast fatal error. dockerID not have session. dockerID=" << c.first << ", proto id=" << Proto::getProtoID());
                continue;
            }
            if (c.second.second == 0)
            {
                LOGW("Application::broadcast warning error. session try connecting. dockerID=" << c.first << ", client session ID=" << c.second.first);
            }
            if (withme || ServerConfig::getRef().getDockerID() != c.first)
            {
                SessionManager::getRef().sendSessionData(c.second.first, ws.getStream(), ws.getStreamLen());
            }
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Application::broadcast catch except error. e=" << e.what());
    }
}

template<class Proto>
void Application::broadcast(const Proto & proto, const Tracing & trace, bool withme)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << trace << proto;
        for (const auto &c : _dockerSession)
        {
            if (c.second.first == InvalidSessionID)
            {
                LOGF("Application::broadcast fatal error. dockerID not have session. dockerID=" << c.first << ", proto id=" << Proto::getProtoID());
                continue;
            }
            if (c.second.second == 0)
            {
                LOGW("Application::broadcast warning error. session try connecting. dockerID=" << c.first << ", client session ID=" << c.second.first);
            }
            if (withme || ServerConfig::getRef().getDockerID() != c.first)
            {
                SessionManager::getRef().sendSessionData(c.second.first, ws.getStream(), ws.getStreamLen());
            }
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Application::broadcast catch except error. e=" << e.what());
    }
}

template<class Proto>
void Application::sendToSession(SessionID sessionID, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        SessionManager::getRef().sendSessionData(sessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Application::sendToSession catch except error. e=" << e.what());
    }
}
template<class Proto>
void Application::sendToSession(SessionID sessionID, const Tracing & trace, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << trace << proto;
        SessionManager::getRef().sendSessionData(sessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Application::sendToSession catch except error. e=" << e.what());
    }
}

template<class Proto>
void Application::sendToDocker(DockerID dockerID, const Proto & proto)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.first != InvalidSessionID && founder->second.second != 0)
    {
        sendToSession(founder->second.first, proto);
    }
    else
    {
        LOGE("Application::sendToDocker not found docker. dockerID=" << dockerID);
    }
}

template<class Proto>
void Application::sendToDocker(DockerID dockerID, const Tracing & trace, const Proto & proto)
{
    auto founder = _dockerSession.find(dockerID);
    if (founder != _dockerSession.end() && founder->second.first != InvalidSessionID && founder->second.second != 0)
    {
        sendToSession(founder->second.first, trace, proto);
    }
    else
    {
        LOGE("Application::sendToDocker not found docker. dockerID=" << dockerID);
    }
}




























#endif
