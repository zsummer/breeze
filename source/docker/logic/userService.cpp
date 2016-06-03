#include "userService.h"



UserService::UserService()
{
    setServiceType(ServiceUser);
}

UserService::~UserService() 
{
}


void UserService::onTick()
{
    LOGE("UserService::onTick");
}



void UserService::onUninit()
{
    finishUninit();
}

bool UserService::onInit()
{
    _baseInfo.initFromDB(shared_from_this(), UserBaseInfo(getServiceID(), "", "", 0, 0), nullptr);
    return true;
}


void UserService::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    //toService;

    //toService("client",_uID, ack);
}

