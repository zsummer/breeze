
/*
* breeze License
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
#include <common.h>
#include <dbAsync.h>
#include <unordered_map>
#include <ProtoLogin.h>
using namespace zsummer::mysql;



class NetManager :public Singleton<NetManager>
{
public:
	NetManager();
	bool start();
	bool stop();

	//in this method don't add/or del _mapSession,_mapCharInfo.
	void userLogin(std::shared_ptr<InnerUserInfo> innerInfo);
	void userLogout(std::shared_ptr<InnerUserInfo> innerInfo);

	void event_onSessionEstablished(SessionID);
	void event_onSessionDisconnect(SessionID);



	void msg_onLoginReq(SessionID sID, ProtoID pID, ReadStream & rs);
	void db_onAuthSelect(DBResultPtr res, SessionID sID);
	void db_onUserSelect(DBResultPtr res, SessionID sID, bool isCreateUser);

	void db_updateUserInfo(const UserInfo & ui);


	void msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStream &rs);
	void db_onUserCreate(DBResultPtr res, SessionID sID);
	void db_onTestBlog(DBResultPtr res, bool isRead);


	void event_onPulse(SessionID sID, unsigned int pulseInterval);
	void msg_onServerPulse(SessionID sID, ProtoID pID, ReadStream & rs);

private:
	//
	std::vector<MessageHandler*> _handlers;

	//
	std::unordered_map<SessionID, std::shared_ptr<InnerUserInfo>> _mapUserSession;
	std::unordered_map<UserID, std::shared_ptr<InnerUserInfo>> _mapUserInfo;

	zsummer::network::ListenConfig _configListen; 
	bool _bListening = false;
	AccepterID _accepterID = InvalidAccepterID;
};




































#endif
