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
    template<class Proto>
    void globalCall(const std::string & src, const UserID & srcID, const std::string & dst, const UserID & dstID, const Proto & proto);
protected:
protected:



protected:
    void event_onServiceLinked(TcpSessionPtr session);
    void event_onServiceClosed(TcpSessionPtr session);
    void event_onServiceMessage(TcpSessionPtr   session, const char * begin, unsigned int len);
    void initService();
    void checkServiceState();

    void event_onLinked(TcpSessionPtr session);
    void event_onClosed(TcpSessionPtr session);
    void event_onMessage(TcpSessionPtr   session, const char * begin, unsigned int len);





    void msg_onAttachLogicReq(TcpSessionPtr session, ReadStream & rs);

    bool on_preMessageProcess(TcpSessionPtr session, const char * blockBegin, zsummer::proto4z::Integer blockSize);

    void event_onSessionPulse(TcpSessionPtr session);
    void msg_onHeartbeatEcho(TcpSessionPtr session, ReadStream & rs);
private:
    std::unordered_map<std::string, EntitySession> _services;
    std::map<SessionID, int> _clusterState;
    bool _clusterNetWorking = false;
    bool _clusterServiceWorking = false;
    bool _clusterServiceInited = false;
    std::unordered_map<SessionID, UserInfoPtr> _mapSession;
    std::unordered_map<UserID, UserInfoPtr> _mapUserInfo;

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


template<class Proto>
void Application::globalCall(const std::string & src, const UserID & srcID, const std::string & dst, const UserID & dstID, const Proto & proto)
{
    Tracing trace;
    trace._fromService = src;
    trace._fromUID = srcID;
    trace._toService = dst;
    trace._toUID = dstID;
    WriteStream ws(Proto::GetProtoID());
    ws << trace << proto;
    auto founder = _services.find(dst);
    if (founder != _services.end())
    {
        SessionManager::getRef().sendSessionData(founder->second._sID, ws.getStream(), ws.getStreamLen());
    }
}




























#endif
