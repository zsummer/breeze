
/*
* mini-mini-breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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
*  文件说明
*  网络管理类
*  提供服务节点的网络模块配置启动,维护网络的连接/断开,心跳脉冲, 节点注册, 默认消息处理等.
*  提供所有人较原始的网络访问接口.
*/




#ifndef _NET_MANAGER_H_
#define _NET_MANAGER_H_
#include <ServerConfig.h>
#include <ProtoDefine.h>
#include <ProtoAuth.h>
#include "GlobalFacade.h"
#include <unordered_map>


/*
*  文件说明
*  网络管理类
*  提供服务节点的网络模块配置启动,维护网络的连接/断开,心跳脉冲, 节点注册, 默认消息处理等.
*  提供较原始的网络访问接口.
*/




class CNetManager
{
public:
	CNetManager();
	//连接所有认证服务和中央服务
	bool Start();
	bool Stop();

	void event_OnSessionEstablished(SessionID);
	void event_OnSessionDisconnect(SessionID);

	void msg_SessionServerAuth(SessionID sID, ProtoID pID, ReadStreamPack &rs);

	void msg_DefaultSessionReq(SessionID sID, ProtoID pID, ReadStreamPack & rs);


	void msg_AuthReq(SessionID sID, ProtoID pID, ReadStreamPack & rs);
	void msg_AuthAck(SessionID cID, ProtoID pID, ReadStreamPack &rs);
	void msg_CharacterLogin(SessionID cID, ProtoID pID, ReadStreamPack &rs);

	void event_OnSessionPulse(SessionID sID, unsigned int pulseInterval);
	void event_OnConnectorPulse(SessionID cID, unsigned int pulseInterval);
	void msg_OnDirectServerPulse(SessionID cID, ProtoID pID, ReadStreamPack &rs);
	void msg_OnClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs);

private:
	std::unordered_map<SessionID, std::shared_ptr<AgentSessionInfo>> m_mapSession;
	std::unordered_map<CharacterID, std::shared_ptr<AgentSessionInfo>> m_mapChar;

	tagAcceptorConfigTraits m_configListen; //保存监听配置
	bool m_bListening = false;

	std::unordered_map<SessionID, tagConnctorConfigTraits> m_configCenter;  //cID 对应的连接配置
	std::vector<ServerAuthSession> m_onlineCenter;
};




































#endif
