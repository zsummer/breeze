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


private:
    Balance _userBalance;
    Balance _webBalance;

private:
    AccepterID _widelisten = InvalidAccepterID;
    AccepterID _weblisten = InvalidAccepterID;
};





















#endif
