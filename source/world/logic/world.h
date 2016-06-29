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



#ifndef _WORLD_H_
#define _WORLD_H_
#include <common.h>
#include <ProtoDocker.h>


struct DockerSession
{
    DockerID dokerID = InvalidDockerID;
    SessionID sessionID = InvalidSessionID;
    int status; //0 invalid, 1 valid
};


class World : public Singleton<World>
{
public:
    World();
    bool init(const std::string & configName, DockerID configID);
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
    bool startDockerWideListen();




    

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
    std::map <DockerID, DockerSession> _dockerSession;
    AccepterID _widelisten = InvalidAccepterID;
    AccepterID _weblisten = InvalidAccepterID;
};





















#endif
