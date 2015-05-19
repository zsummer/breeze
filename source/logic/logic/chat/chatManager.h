
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


/*
*  file desc 
*  chat manager
*/




#ifndef _CHAT_MANAGER_H_
#define _CHAT_MANAGER_H_
#include <common.h>
#include <ProtoChat.h>
#include "../mission/eventTrigger.h"





class ChatManager :public Singleton<ChatManager>
{
public:
	ChatManager();
	bool init();
	//更新名片, 可选择更新到数据库还是更新给所有客户端
	void insertContact(const ContactInfo & info);
	void updateContact(const ContactInfo & info, bool writedb, bool broadcast);
	void db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc);

public:
	void onUserLogin(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string);
	void onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string);
public:
	void msg_onGetContactInfoReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);
	void msg_onFriendOperationReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);
	void msg_onChatReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);
	
private:
	std::unordered_map<UserID, ContactInfo> _mapContact; //存储所有好友/名片信息
	GenObjectID _genID; //生成消息ID
};




































#endif
