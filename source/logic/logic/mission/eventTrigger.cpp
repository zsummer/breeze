
#include "eventTrigger.h"


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

void EventTrigger::trigger(EventTriggerID tID, UserID uID, unsigned long long param1, unsigned long long param2, std::string param3)
{
	SessionManager::getRef().post(std::bind(&EventTrigger::_trigger, this, tID, uID, param1, param2, param3));
}

void EventTrigger::_trigger(EventTriggerID tID, UserID uID, unsigned long long param1, unsigned long long param2, std::string param3)
{
	for (auto & func : _watchings[tID])
	{
		func(tID, uID, param1, param2, param3);
	}
}

