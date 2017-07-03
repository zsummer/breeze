/*
* breeze License
* Copyright (C) 2015 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
#include <ProtoSceneCommon.h>
#include <ProtoDocker.h>
#include <ProtoSceneClient.h>
#include <ProtoSceneServer.h>
#include <rvo2/RVO.h>

struct SceneDockerInfo
{
    SessionID sessionID = InvalidSessionID;
    unsigned long long areaID = InvalidAreaID;
    ServiceType serviceType = InvalidServiceID; //all is singleton
};
using SceneDockerInfoPtr = std::shared_ptr<SceneDockerInfo>;


struct SceneLineInfo
{
    SessionID sessionID = InvalidSessionID;
    SceneKnock knock;
};
using SceneLineInfoPtr = std::shared_ptr<SceneLineInfo>;

using SceneGroupInfoPtr = std::shared_ptr<SceneGroupInfo>;
using SceneGroupInfoPool = std::list<SceneGroupInfoPtr>;




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
    bool startDockerListen();
    bool startSceneListen();
public:
    void sendViaSessionID(SessionID sessionID, const char * block, unsigned int len);
    template<class Proto>
    void sendViaSessionID(SessionID sessionID, const Proto & proto);

    void toService(SessionID sessionID, const Tracing &trace, const char * block, unsigned int len);
    template<class Proto>
    void toService(SessionID sessionID, const Tracing &trace, const Proto & proto);

    template <class Proto>
    void toService(AreaID areaID, ServiceType indexServiceType, ServiceType dstServiceType, ServiceID dstServiceID, const Proto & proto); 


    template<class Proto>
    void backToService(SessionID sessionID, const Tracing &backTrace, const Proto & proto);


private:
    //docker间通讯处理 
    void event_onDockerLinked(TcpSessionPtr session);
    void event_onDockerClosed(TcpSessionPtr session);
    void event_onDockerMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void event_onServiceForwardMessage(TcpSessionPtr   session, const Tracing & trace, ReadStream & rs);

    void onChatReq(TcpSessionPtr session, const Tracing & trace, ChatReq & req);
    void onSceneGroupGetReq(TcpSessionPtr session, const Tracing & trace, SceneGroupGetReq & req);
    void onSceneGroupEnterReq(TcpSessionPtr session, const Tracing & trace, SceneGroupEnterReq & req);
    void onSceneGroupCancelReq(TcpSessionPtr session, const Tracing & trace, SceneGroupCancelReq & req);

    void onSceneServerJoinGroupIns(TcpSessionPtr session, const Tracing & trace, SceneServerJoinGroupIns & req);
    void onSceneGroupInviteReq(TcpSessionPtr session, const Tracing & trace, SceneGroupInviteReq & req);
    void onSceneGroupRejectReq(TcpSessionPtr session, const Tracing & trace, SceneGroupRejectReq & req);
    void onSceneGroupLeaveReq(TcpSessionPtr session, const Tracing & trace, SceneGroupLeaveReq & req);



private:
    //客户端通讯处理 
    void event_onSceneLinked(TcpSessionPtr session);
    void event_onScenePulse(TcpSessionPtr session);
    void event_onSceneClosed(TcpSessionPtr session);
    void event_onSceneMessage(TcpSessionPtr   session, const char * begin, unsigned int len);



public:
    SceneLineInfoPtr getLineInfo(LineID lineID);
    SceneLineInfoPtr pickFreeLineNode(double step, double autoAdd);
    SceneLineInfoPtr pickClosureLineNode(double step, double autoAdd);

private:
    std::map<AreaID, std::map<ServiceType, SceneDockerInfo> > _services; //只记录singleton的service   
    std::map<LineID, SceneLineInfoPtr> _lines;
    Balance<LineID> _freeBalance;
    Balance<LineID> _closureBalance;
    AccepterID _dockerListen = InvalidAccepterID;
    AccepterID _sceneListen = InvalidAccepterID;

public:
    SceneGroupInfoPtr getGroupInfoByAvatarID(ServiceID serviceID);
    SceneGroupInfoPtr getGroupInfo(GroupID groupID);
    void pushGroupInfoToClient(SceneGroupInfoPtr);
private:
    std::map<ServiceID, GroupID> _avatars;
    std::map<GroupID, SceneGroupInfoPtr> _groups;
    GroupID _lastGroupID = InvalidGroupID;

private:
    std::map<ui16, std::map<ui64, SceneGroupInfoPool> > _matchPools;
    TimerID _matchTimerID = InvalidTimerID;
    void onMatchTimer();
    void onMatchFreeTimer(ui16 sceneType, ui64 mapID);
    void onMatchArenaTimer();
};





template<class Proto>
void World::sendViaSessionID(SessionID sessionID, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        sendViaSessionID(sessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::sendViaSessionID catch except error. e=" << e.what());
    }
}

template<class Proto>
void World::toService(SessionID sessionID, const Tracing &trace, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(sessionID, trace, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::forwardViaSessionID catch except error. e=" << e.what());
    }
}

template<class Proto>
void World::backToService(SessionID sessionID, const Tracing &backTrace, const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;

        Tracing trace;
        trace.oob = backTrace.oob;
        trace.routing.toServiceType = backTrace.routing.fromServiceType;
        trace.routing.toServiceID = backTrace.routing.fromServiceID;
        trace.routing.fromServiceType = STWorldMgr;
        trace.routing.fromServiceID = InvalidServiceID;
        trace.routing.traceBackID = backTrace.routing.traceID;
        trace.routing.traceID = 0;
        toService(sessionID, trace, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Docker::forwardViaSessionID catch except error. e=" << e.what());
    }
}

template <class Proto>
void World::toService(AreaID areaID, ServiceType indexServiceType, ServiceType dstServiceType, ServiceID dstServiceID, const Proto & proto)
{
    auto areaMapIter = _services.find(areaID);
    if (areaMapIter == _services.end())
    {
        LOGE("not have areaID when to Service. areaID=" << areaID);
        return; 
    }
    auto founder = areaMapIter->second.find(indexServiceType);
    if (founder == areaMapIter->second.end())
    {
        LOGE("not have indexServiceType when to Service. areaID=" << areaID << ", indexServiceType=" << indexServiceType);
        return;
    }
    if (founder->second.sessionID == InvalidSessionID)
    {
        LOGW("the docker not linked when to Service. areaID=" << areaID << ", indexServiceType=" << indexServiceType);
        return;
    }
    Tracing trace;
    if (dstServiceType == STAvatar || dstServiceType == STClient)
    {
        trace.oob.clientAvatarID = dstServiceID;
    }
    trace.routing.fromServiceType = STWorldMgr;
    trace.routing.fromServiceID = InvalidServiceID;
    trace.routing.toServiceType = dstServiceType;
    trace.routing.toServiceID = dstServiceID;

    toService(founder->second.sessionID, trace, proto);
}











#endif
