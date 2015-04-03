
#include "eventTrigger.h"
using namespace zsummer::mysql;

EventTrigger::EventTrigger()
{

}
EventTrigger::~EventTrigger()
{

}

bool EventTrigger::init()
{
	return true;
}
void EventTrigger::trigger(EventTriggerEnum triggerID, UserID uID, unsigned long long param1, unsigned long long param2, unsigned long long param3)
{
	SessionManager::getRef().post(std::bind(&EventTrigger::_trigger, this, triggerID, uID, param1, param2, param3));
}

void EventTrigger::watching(EventTriggerEnum triggerID, EventTrigger::TriggerHandler callback)
{
	_watchings[triggerID].push_back(callback);
}

void EventTrigger::_trigger(EventTriggerEnum triggerID, UserID uID, unsigned long long param1, unsigned long long param2, unsigned long long param3)
{
	for (auto & cb : _watchings[triggerID])
	{
		cb(uID, param1, param2, param3);
	}
}


