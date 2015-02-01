
/*
* mini-breeze License
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
 *  BaseHandler provide a unified way to manager message handler.
 */


#ifndef _BASE_MESSAGE_HANDLER_H_
#define _BASE_MESSAGE_HANDLER_H_
#include <innerDefined.h>


class MessageHandler
{
public:
	MessageHandler(){}
	virtual ~MessageHandler(){};
	virtual bool init() = 0;
	virtual void userLogin(std::shared_ptr<InnerUserInfo> innerInfo) = 0;
	virtual void userLogout(std::shared_ptr<InnerUserInfo> innerInfo) = 0;
};



































#endif
