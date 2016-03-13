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
*  file desc 
*  network manager
*/




#ifndef _NET_MANAGER_H_
#define _NET_MANAGER_H_
#include <common.h>
#include "service.h"
#include <ProtoCluster.h>


class Application : public Singleton<Application>
{
public:
    Application();
    bool init(const std::string & config, ClusterIndex idx);
    bool start();
    bool run();
public:
    template<class Proto>
    void broadcast(const Proto & proto);
    void globalCall(Tracing trace, const char * block, unsigned int len);
    void globalBack(const Tracing & trace, const char * block, unsigned int len);
protected:

protected:
    void event_onServiceLinked(TcpSessionPtr session);
    void event_onServiceClosed(TcpSessionPtr session);
    void event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    ServicePtr createLocalService(ui16 st);
    void checkServiceState();

    void event_onClientLinked(TcpSessionPtr session);
    void event_onClientClosed(TcpSessionPtr session);
    void event_onClientMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void event_onClientPulse(TcpSessionPtr   session);

private:
    std::unordered_map<ui16, std::unordered_map<ServiceID, ServicePtr > > _services;

    std::map<SessionID, std::pair<ClusterIndex, int>> _clusterState;
    bool _clusterNetWorking = false;
    bool _clusterServiceWorking = false;
    bool _clusterServiceInited = false;



};






template<class Proto>
void Application::broadcast(const Proto & proto)
{
    WriteStream ws(Proto::GetProtoID());
    ws << proto;
    for (const auto &c: _clusterState)
    {
        SessionManager::getRef().sendSessionData(c.first, ws.getStream(), ws.getStreamLen());
    }
}
































#endif
