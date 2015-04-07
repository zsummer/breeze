
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



struct InnerContactInfo
{
	ContactInfo contact; //联系人卡片
	FriendInfoVct friends; //好友
	FriendInfoVct blacks; //黑名单
	FriendInfoVct request; //请求加好友
};

class ChatManager :public Singleton<ChatManager>
{
public:
	ChatManager();
	bool init();
	void updateContact(const InnerContactInfo & info);
	void onUpdateContact(zsummer::mysql::DBResultPtr);

public:
	void onUserLogin(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string);
	void onUserLogout(EventTriggerID tID, UserID uID, unsigned long long, unsigned long long, std::string);

	
private:
	std::unordered_map<UserID, InnerContactInfo> _mapContact;
};




































#endif
