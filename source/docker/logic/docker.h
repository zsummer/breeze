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


/*
docker是用来托管service的专用vm. 
    负责底层的网络通讯,多节点的网络拓扑构建, docker的多节点对上层透明化.
    docker维护service和镜像service的创建,装载,卸载,销毁等管理操作. 
    上层只需关注docker所装载的service. 

docker的资源消耗:
    docker集群的socket数量开销= (docker个数的平方)*2
    docker集群的总端口占用数量开销=docker个数的平方
    操作系统的可用端口数量小于64k, 也就是docker无法突破的理论上限是252个docker进程.
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
    bool init(const std::string & configName, DockerID configID);
    bool start();
    void stop();
    void forceStop();
    void onShutdown();
    bool run();

    
public:
    //该分块下为网络通讯用接口,通过目标参数把数据通过网络发送出去  
    void sendViaSessionID(SessionID sessionID, const char * block, unsigned int len);
    template<class Proto>
    void sendViaSessionID(SessionID sessionID, const Proto & proto);

    void sendViaDockerID(DockerID dockerID, const char * block, unsigned int len);
    template<class Proto>
    void sendViaDockerID(DockerID dockerID, const Proto & proto);

    void sendViaServiceID(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len);
    template<class Proto>
    void sendViaServiceID(ServiceType serviceType, ServiceID serviceID, const Proto & proto);

    //如果目标是客户端, 会进行优化.
    void sendViaTracing(const Tracing & trace, const char * block, unsigned int len);
    template<class Proto>
    void sendViaTracing(const Tracing & trace, const Proto & proto);

    template<class Proto>
    void broadcastToDockers(const Proto & proto, bool withme);
    template<class Proto>
    void broadcastToDockers(const Proto & proto, const Tracing & trace, bool withme);

public:
    // toService根据tracing内容选择通过网络转发或者直接交给service进行处理 
    // 如果service在本地 则直接调用本地service的process方法 
    // 如果service在其他docker上, 则把数据转发给对应的docker.
    // 如果是客户端 则游戏通过oob其次通过routing数据找到对应的docker 然后通过该docker转发给客户端 
    // canForwardToOtherService 是属于错误止损用参数, 如果是来自其他docker的转发 但service并不在本地,在这种特殊情况下 可能会造成docker内部pingpong.   
    // needPost 是属于优化用参数, 填写true则不优化,但总是正确的. 
    void toService(Tracing trace, const char * block, unsigned int len, bool syncCall = true);
    template<class Proto>
    void toService(Tracing trace, Proto proto, bool syncCall = true);

public:
    bool isStopping();
    ServicePtr peekService(ServiceType serviceType, ServiceID serviceID);
    std::unordered_map<ServiceID, ServicePtr > & peekService(ServiceType serviceType);
    SessionID getDockerLinked(DockerID dockerID);
private:
    //内部接口 
    //打开监听端口,新连接 
    bool startDockerListen();
    bool startDockerConnect();
    bool startDockerWideListen();
    bool startDockerWebListen();

public:
    //内部接口 
    ServicePtr createService(const ServiceInfo& si, bool isShell, bool failExit);
    void destroyService(ServiceType serviceType, ServiceID serviceID);
public:
    //内部接口 
    void buildCluster();
    void destroyCluster();

    

private:
    //docker间通讯处理 
    void event_onServiceLinked(TcpSessionPtr session);
    void event_onServiceClosed(TcpSessionPtr session);
    void event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);

private:
    //客户端通讯处理 
    void event_onClientLinked(TcpSessionPtr session);
    void event_onClientPulse(TcpSessionPtr session);
    void event_onClientClosed(TcpSessionPtr session);
    void event_onClientMessage(TcpSessionPtr   session, const char * begin, unsigned int len);

private:
    //来自web客户端的请求
    void event_onWebClientRequestAPI(TcpSessionPtr session, const std::string & method, const std::string & methodLine,
        const std::map<std::string, std::string> &head, const std::string & body);
private:
    void event_onWebServerRequest(TcpSessionPtr session, ReadStream & rs);

private:
    void event_onLoadService(TcpSessionPtr session, ReadStream & rs);
    void event_onLoadServiceNotice(TcpSessionPtr session, ReadStream & rs);
    void event_onSwitchServiceClientNotice(TcpSessionPtr session, ReadStream & rs);
    void event_onKickRealClient(TcpSessionPtr session, ReadStream & rs);
    void event_onUnloadServiceInDocker(TcpSessionPtr session, ReadStream & rs);
    void event_onUnloadedServiceNotice(TcpSessionPtr session, ReadStream & rs);

    void event_onForwardToService(TcpSessionPtr session, ReadStream & rs);
    void event_onForwardToRealClient(TcpSessionPtr session, ReadStream & rs);

public://负载均衡 
    inline Balance & getUserBalance(){return _userBalance;}
    inline Balance & getWebBalance(){return _webBalance;}
private:
    Balance _userBalance;
    Balance _webBalance;

private:
    std::unordered_map<ui16, std::unordered_map<ServiceID, ServicePtr > > _services;
    std::unordered_map<ServiceID, ServicePtr > _invalidServices;
    std::map <DockerID, DockerSession> _dockerSession;
    bool _dockerNetWorking = false;
    bool _dockerServiceWorking = false;
    bool _dockerStopping = false;
    AccepterID _widelisten = InvalidAccepterID;
    AccepterID _weblisten = InvalidAccepterID;
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
                sendViaSessionID(c.second.sessionID, ws.getStream(), ws.getStreamLen());
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
                sendViaSessionID(c.second.sessionID, forward.getStream(), forward.getStreamLen());
            }
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::broadcast catch except error. e=" << e.what());
    }
}

template<class Proto>
void Docker::sendViaSessionID(SessionID sessionID, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        SessionManager::getRef().sendSessionData(sessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::sendViaSessionID catch except error. e=" << e.what());
    }
}

template<class Proto>
void Docker::sendViaTracing(const Tracing & trace, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        sendViaTracing(trace, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::sendViaTracing catch except error. e=" << e.what());
    }
}


template<class Proto>
void Docker::sendViaDockerID(DockerID dockerID, const Proto & proto)
{
    SessionID  sID = getDockerLinked(dockerID);
    if (sID != InvalidSessionID)
    {
        sendViaSessionID(sID, proto);
    }
    else
    {
        LOGE("Docker::sendViaDockerID not found docker. dockerID=" << dockerID);
    }
}


template<class Proto>
void Docker::sendViaServiceID(ServiceType serviceType, ServiceID serviceID, const Proto & proto)
{
    WriteStream ws(Proto::getProtoID());
    ws << proto;
    sendViaServiceID(serviceType, serviceID, ws.getStream(), ws.getStreamLen());
}

template<class Proto>
void Docker::toService(Tracing trace, Proto proto, bool syncCall)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(trace, ws.getStream(), ws.getStreamLen(), syncCall);
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::toService catch except error. e=" << e.what());
    }
}























#endif
