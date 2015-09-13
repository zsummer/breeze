
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
*  chat manager
*/




#ifndef _CHAT_MANAGER_H_
#define _CHAT_MANAGER_H_
#include <common.h>
#include <ProtoChat.h>
#include "../mission/eventTrigger.h"
#include <multimod_matching_tree/match_tree.h>




class Chat :public Singleton<Chat>
{
public:
    Chat();
    ~Chat();
    bool init();

    bool loadFilter();
    bool buildMessage();
    bool initGenerator();
    bool loadMessage();


    //存储聊天消息
    void insertMessage(const ChatInfo & info);
    void updateMessage(const ChatInfo & info);

    //广播消息给客户端
    //uIDs为空则广播给所有在线用户
    void broadcast(WriteStream & ws, const UIDS &ids);
    void broadcastFriends(WriteStream & ws, UserID uID);

    void db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc);

public:
    void msg_onChatReq(TcpSessionPtr session, ReadStream & rs);
    
private:

    //频道
    std::map<unsigned long long, UIDS> _channels;

    //过滤词库
    match_tree_head * _filter = nullptr;

    //负责分配一个支持SQL合服的64位ID.  [plat+ared+uniqueID]
    GenObjectID _genID; //生成消息ID
};




































#endif
