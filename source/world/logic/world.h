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
    SessionID getDockerLinked(DockerID dockerID);
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

private:
    //客户端通讯处理 
    void event_onSpaceLinked(TcpSessionPtr session);
    void event_onSpacePulse(TcpSessionPtr session);
    void event_onSpaceClosed(TcpSessionPtr session);
    void event_onSpaceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);

private:


private:
    Balance _spaceBalance;

private:
    AccepterID _widelisten = InvalidAccepterID;
    AccepterID _weblisten = InvalidAccepterID;
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















#endif
