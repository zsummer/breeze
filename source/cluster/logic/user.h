
/*
* breeze License
* Copyright (C) 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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




#ifndef _USER_H_
#define _USER_H_
#include <common.h>
#include <ProtoChat.h>





class User : public EntitySlot, public std::enable_shared_from_this<User>
{
public:
    User();
    ~User();
public:
    void onChatReq(TcpSessionPtr&, const Tracing & trace, zsummer::proto4z::ReadStream &);
    
};



































#endif
