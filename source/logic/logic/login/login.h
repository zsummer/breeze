
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
    void event_onClosed(TcpSessionPtr session);
    //! ---- 令牌验证 --------------------------------------------
    void msg_onPlatAuthReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onCreateUserReq(TcpSessionPtr session, ReadStream & rs);
    void msg_onSelectUserReq(TcpSessionPtr session, ReadStream & rs);

    void db_onFetchUsers(DBResultPtr result, TcpSessionPtr session);
    void db_onCreateUser(DBResultPtr result, TcpSessionPtr session, const UserInfo &info);
private:
    //走数据库, 这里只是保存下认证/创建用户/选择用户这些流程时候的一些状态.
    //玩家进入游戏后应该选择一个合适的时机清除掉.
    //也可以后续放进redis中存储.
    std::map<SessionID, UserInfoArray> _cache;

    //负责分配一个支持SQL合服的64位ID.  [plat+ared+uniqueID]
    GenObjectID _genID;


};




































#endif
