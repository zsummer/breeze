
/*
* breeze License
* Copyright (C) 2015 YaweiZhang <yawei_zhang@foxmail.com>.
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



#ifndef _LOGIN_H_
#define _LOGIN_H_
#include <common.h>
#include <ProtoLogin.h>






class Login :public Singleton<Login>
{
public:
	Login();
	bool init();
public:
	void event_onSessionDisconnect(TcpSessionPtr session);
	//! ---- 令牌验证 --------------------------------------------
	void msg_onPlatAuthReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);
	void msg_onCreateUserReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);
	void msg_onSelectUserReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);

	void db_onFetchUsers(DBResultPtr result, TcpSessionPtr session);
private:
	//是加载到内存 还是全都走数据库, 还有UID的产生机制.
	std::map<SessionID, UserInfoArray> _cache;
	std::map<UserID, UserInfo> _user;
};




































#endif
