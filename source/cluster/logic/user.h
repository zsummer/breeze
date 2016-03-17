
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





#ifndef _USER_H_
#define _USER_H_
#include <common.h>
#include "service.h"






class User : public Service
{
public:
    User();
    ~User();
public:
    void onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void process(const Tracing & trace, const char * block, unsigned int len) override final;
    virtual void globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb = nullptr)override final;
    virtual void backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb = nullptr)override final;
    
};



































#endif
