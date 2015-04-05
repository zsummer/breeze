
#include "dailyMission.h"


DailyMission::DailyMission()
{

}
DailyMission::~DailyMission()
{

}
bool DailyMission::init()
{
	EventTrigger::getRef().watching(ETRIGGER_USER_LOGIN,
		std::bind(&DailyMission::onUserLogin, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
	return true;
}

void DailyMission::onUserLogin(EventTriggerID tID, UserID uID, unsigned long long param1, unsigned long long param2, unsigned long long param3)
{

}

