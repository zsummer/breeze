#include "application.h"
#include "userMgr.h"
#include <ProtoDBService.h>



UserMgr::UserMgr()
{

}

UserMgr::~UserMgr()
{
    
}

void UserMgr::onTick()
{
    time_t now = getNowTime();
    if (now - _lastTime > 10)
    {
        _lastTime = now;
        LOGA("UserMgr::onTick");
    }
}

void UserMgr::onStop()
{
    setWorked(false);
}

bool UserMgr::onInit()
{
    setWorked(true);
    return true;
}



