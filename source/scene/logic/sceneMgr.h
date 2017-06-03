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





#ifndef _SceneMgr_H_
#define _SceneMgr_H_
#include <common.h>
#include <ProtoCommon.h>
#include <ProtoDocker.h>
#include <ProtoSceneCommon.h>
#include <ProtoSceneClient.h>
#include <rvo2/RVO.h>
#include "scene.h"



class SceneMgr : public Singleton<SceneMgr>
{
public:
    SceneMgr();
    bool init(const std::string & configName, ui32 serverID);
    bool start();
    void stop();
    void forceStop();
    void onShutdown();
    bool run();

    
public:
    bool isStopping();
public:
    void sendViaSessionID(SessionID sessionID, const char * block, unsigned int len);
    template<class Proto>
    void sendViaSessionID(SessionID sessionID, const Proto & proto);

    void sendToWorld(const char * block, unsigned int len);
    void sendToWorld(const Tracing &trace, const char * block, unsigned int len);
    template<class Proto>
    void sendToWorld(const Proto & proto);
    template<class Proto>
    void sendToWorld(const Tracing &trace, const Proto & proto);
private:
    //内部接口 
    //打开监听端口,新连接 
    bool startClientListen();
    bool startWorldConnect();
    bool loadScenes();
    void onTimer();
public:
    ScenePtr getScene(SceneID);
    ScenePtr getActiveScene(SceneID sceneID);
private:
    //docker间通讯处理 
    void event_onWorldLinked(TcpSessionPtr session);
    void event_onWorldClosed(TcpSessionPtr session);
    void event_onWorldMessage(TcpSessionPtr session, const char * begin, unsigned int len);
    void onSceneGroupAvatarInfo(TcpSessionPtr session, SceneGroupAvatarInfo & info);
    void onSceneServerEnterSceneIns(TcpSessionPtr session, SceneServerEnterSceneIns & ins);
    void onSceneServerCancelSceneIns(TcpSessionPtr session, SceneServerCancelSceneIns & ins);
    void onForwardToService(TcpSessionPtr session, Tracing & trace, ReadStream & rs);
private:
    //客户端通讯处理 
    void event_onClientLinked(TcpSessionPtr session);
    void event_onClientPulse(TcpSessionPtr session);
    void event_onClientClosed(TcpSessionPtr session);
    void event_onClientMessage(TcpSessionPtr   session, const char * begin, unsigned int len);


private:


    std::map<SceneID, ScenePtr> _actives;
    std::queue<ScenePtr> _frees; //队列
    std::map<SceneID, ScenePtr> _scenes;
    
    std::map<ServiceID, std::pair<std::string, SceneID>> _tokens;
    std::map<ServiceID, time_t> _forbids;
    time_t _forbidAll = 0;

    SessionID _worldSessionID = InvalidSessionID;
    AccepterID _clientListen = InvalidAccepterID;

    SceneID _lastSceneID = InvalidSceneID;
};
























template<class Proto>
void SceneMgr::sendViaSessionID(SessionID sessionID, const Proto & proto)
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
void SceneMgr::sendToWorld(const Proto & proto)
{
    if (_worldSessionID != InvalidSessionID)
    {
        sendViaSessionID(_worldSessionID, proto);
    }
}



template<class Proto>
void SceneMgr::sendToWorld(const Tracing &trace, const Proto & proto)
{
    WriteStream ws(Proto::getProtoID());
    ws << proto;
    sendToWorld(trace, ws.getStream(), ws.getStreamLen());
}




#endif
