
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




#ifndef _FOLLOW_H_
#define _FOLLOW_H_
#include <common.h>
#include <ProtoFollow.h>
#include "../mission/eventTrigger.h"




//关注 
class Follow :public Singleton<Follow>
{
public:
    Follow();
    ~Follow();
    bool init();
    bool buildFollow();
    bool loadFollow();


    void updateFollowingInfo(FollowingInfo & info);
    void db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc);

public:
    void msg_onGetFollowingReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onGetFollowerReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onPokeReq(TcpSessionPtr session, ReadStream & rs);

private:
    //<follower, <following, info>>
    std::map<UserID, std::map<UserID, FollowingInfo>> _following;
    
    //<following, <follower, info>>
    std::map<UserID, std::map<UserID, FollowingInfo>> _follower;
};




































#endif
