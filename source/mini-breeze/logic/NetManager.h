
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
#include <Common.h>
#include <unordered_map>
#include <ProtoAuth.h>
#include <ProtoLogin.h>
#include <DBHelper.h>
using namespace zsummer::mysql;



class NetManager :public Singleton<NetManager>
{
public:
	NetManager();
	bool start();
	bool stop();

	//in this method don't add/or del _mapSession,_mapCharInfo.
	void charLogin(std::shared_ptr<InnerCharInfo> iinfoPtr);
	void charLogout(std::shared_ptr<InnerCharInfo> iinfoPtr);

	void event_onSessionEstablished(SessionID);
	void event_onSessionDisconnect(SessionID);



	void msg_authReq(SessionID sID, ProtoID pID, ReadStreamPack & rs);
	void db_authSelect(DBResultPtr res, SessionID sID, C2AS_AuthReq req);
	void db_accountSelect(DBResultPtr res, SessionID sID, AccountID accID, C2AS_AuthReq req);



	void msg_characterLoginReq(SessionID sID, ProtoID pID, ReadStreamPack &rs);
	void msg_characterCreateReq(SessionID sID, ProtoID pID, ReadStreamPack &rs);



	void event_onSessionPulse(SessionID sID, unsigned int pulseInterval);
	void msg_onClientPulse(SessionID sID, ProtoID pID, ReadStreamPack & rs);

private:
	//
	std::vector<BaseHandler*> _handlers;

	//
	std::unordered_map<SessionID, std::shared_ptr<InnerCharInfo>> _mapSession;
	std::unordered_map<CharacterID, std::shared_ptr<InnerCharInfo>> _mapCharInfo;

	tagAcceptorConfigTraits _configListen; 
	bool _bListening = false;
	AccountID _accepterID = InvalidAccepterID;
};




































#endif
