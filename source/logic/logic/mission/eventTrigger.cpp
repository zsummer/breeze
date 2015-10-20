
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

void EventTrigger::trigger(EventTriggerID tID, UserID uID, TupleParam param1, TupleParam param2, TupleParam param3)
{
    SessionManager::getRef().post(std::bind(&EventTrigger::_trigger, this, tID, uID, param1, param2, param3));
}

void EventTrigger::_trigger(EventTriggerID tID, UserID uID, TupleParam param1, TupleParam param2, TupleParam param3)
{
    for (auto & func : _watchings[tID])
    {
        func(tID, uID, param1, param2, param3);
    }
}

