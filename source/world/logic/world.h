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





#ifndef _WORLD_H_
#define _WORLD_H_
#include <common.h>
#include <ProtoCommon.h>
#include <ProtoDocker.h>
#include <ProtoSpaceCommon.h>
#include <ProtoSpaceClient.h>


struct WorldServiceSession
{
    AreaID areaID = InvalidAreaID;
    ServiceType serviceType = InvalidServiceID; //all is singleton 
    SessionID sessionID = InvalidSessionID;
};

class World : public Singleton<World>
{
public:
    World();
    bool init(const std::string & configName);
    bool start();
    void stop();
    void forceStop();
    void onShutdown();
    bool run();

    
public:
    bool isStopping();
private:
    SessionID getDockerLinked(AreaID areaID, ServiceType serviceType);
    template <class Proto>
    void directToService(SessionID sessionID, ServiceType serviceType, const Proto & proto);

    template <class Proto>
    void toService(AreaID areaID, ServiceType serviceType, const Proto & proto);

private:
    //内部接口 
    //打开监听端口,新连接 
    bool startDockerListen();
    bool startSpaceListen();



public:
    void sendToSession(SessionID sessionID, const char * block, unsigned int len);
    template<class Proto>
    void sendToSession(SessionID sessionID, const Proto & proto);
    

private:
    //docker间通讯处理 
    void event_onDockerLinked(TcpSessionPtr session);
    void event_onDockerClosed(TcpSessionPtr session);
    void event_onDockerMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void event_onServiceForwardMessage(TcpSessionPtr   session, ServiceType serviceType, ReadStream & rs);

private:
    //客户端通讯处理 
    void event_onSpaceLinked(TcpSessionPtr session);
    void event_onSpacePulse(TcpSessionPtr session);
    void event_onSpaceClosed(TcpSessionPtr session);
    void event_onSpaceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);



private:
    Balance _spaceBalance;
private:
    std::map<AreaID, std::map<ServiceType, WorldServiceSession> > _services;
    AccepterID _dockerListen = InvalidAccepterID;
    AccepterID _spaceListen = InvalidAccepterID;
};





template<class Proto>
void World::sendToSession(SessionID sessionID, const Proto & proto)
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

template <class Proto>
void World::directToService(SessionID sessionID, ServiceType serviceType, const Proto & proto)
{
    Tracing trace;
    trace.toServiceType = serviceType;
    trace.toServiceID = InvalidServiceID;
    trace.fromServiceType = STWorldMgr;
    trace.fromServiceID = InvalidServiceID;

    WriteStream fd(ForwardToService::getProtoID());
    WriteStream ws(Proto::getProtoID());
    ws << proto;
    fd << trace;
    fd.appendOriginalData(ws.getStream(), ws.getStreamLen());
    SessionManager::getRef().sendSessionData(sessionID, fd.getStream(), fd.getStreamLen());
}

template <class Proto>
void World::toService(AreaID areaID, ServiceType serviceType, const Proto & proto)
{

    SessionID sID = getDockerLinked(areaID, serviceType);
    if (sID == InvalidSessionID)
    {
        LOGE("docker not linked.  areaID=" << areaID << ", serviceType=" << getServiceName(serviceType) 
            << ", protoID=" << Proto::getProtoID());
        return;
    }
    directToService(sID, serviceType, proto);
}











#endif
