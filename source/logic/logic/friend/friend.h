
/*
* breeze License
* Copyright (C) 2015 YaweiZhang <yawei.zhang@foxmail.com>.
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
*  friend 
*/




#ifndef _FRIEND_H_
#define _FRIEND_H_
#include <common.h>
#include <ProtoFriend.h>
#include "../mission/eventTrigger.h"
#include <multimod_matching_tree/match_tree.h>





class Friend :public Singleton<Friend>
{
public:
    Friend();
    ~Friend();
    bool init();
    bool initFriends();

    //存储好友关系
    void insertFriend(const FriendInfo & info);
    void updateFriend(const FriendInfo & info);


    void db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc);
public:
    void onUserLogin(EventTriggerID tID, UserID uID, Any , Any , Any );
    void onUserLogout(EventTriggerID tID, UserID uID, Any , Any , Any );
public:
    void msg_onFriendOperationReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onGetSomeStrangersReq(TcpSessionPtr session, ReadStream & rs);
    
private:
    std::map<UserID, std::map<UserID, FriendInfo> > _friends;
};




































#endif
