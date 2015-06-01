
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
*  event trigger
*/




#ifndef _EVENT_TRIGGER_H_
#define _EVENT_TRIGGER_H_
#include <common.h>
#include <any.h>



//事件触发器只为其他系统模块提供事件出发服务. 这些系统模块指的是 活动,任务,成就 等.
typedef unsigned short EventTriggerID;
typedef unsigned int MissionID;
class  EventTrigger :public Singleton<EventTrigger>
{
public:
	EventTrigger();
	~EventTrigger();
	bool init();

	
	void trigger(EventTriggerID tID, UserID uID, Any param1, Any param2, Any param3);

	typedef std::function<void(EventTriggerID, UserID, Any , Any , Any )> EventTriggerHandler;
	inline void watching(EventTriggerID tID, EventTriggerHandler handler){ _watchings[tID].push_back(handler); }

private:
	void _trigger(EventTriggerID tID, UserID uID, Any param1, Any param2, Any param3);
	std::map<EventTriggerID, std::vector<EventTriggerHandler>> _watchings;
};




































#endif
