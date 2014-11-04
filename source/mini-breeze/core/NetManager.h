
/*
* mini-breeze License
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
*  file desc 
*  network manager
*/




#ifndef _NET_MANAGER_H_
#define _NET_MANAGER_H_
#include <ProtoDefine.h>
#include <ServerConfig.h>
#include "GlobalFacade.h"
#include <unordered_map>
#include <ProtoAuth.h>
#include <ProtoLogin.h>




class CNetManager
{
public:
	CNetManager();
	bool Start();
	bool Stop();

	//in this method don't add/or del m_mapSession,m_mapCharInfo.
	void CharLogin(std::shared_ptr<InnerCharInfo> iinfoPtr);
	void CharLogout(std::shared_ptr<InnerCharInfo> iinfoPtr);

	void event_OnSessionEstablished(SessionID);
	void event_OnSessionDisconnect(SessionID);

	void msg_SessionServerAuth(SessionID sID, ProtoID pID, ReadStreamPack &rs);


	void msg_AuthReq(SessionID sID, ProtoID pID, ReadStreamPack & rs);
	void msg_CharacterLoginReq(SessionID sID, ProtoID pID, ReadStreamPack &rs);
	void msg_CharacterCreateReq(SessionID sID, ProtoID pID, ReadStreamPack &rs);



	void event_OnSessionPulse(SessionID sID, unsigned int pulseInterval);
	void msg_OnClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs);

private:
	std::unordered_map<SessionID, std::shared_ptr<InnerCharInfo>> m_mapSession;
	std::unordered_map<CharacterID, std::shared_ptr<InnerCharInfo>> m_mapCharInfo;

	tagAcceptorConfigTraits m_configListen; //保存监听配置
	bool m_bListening = false;
	AccountID m_accepterID = InvalidAccepterID;
};




































#endif
