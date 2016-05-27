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
    finishInit();
    return true;
}


void UserService::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    //toService;

    //toService("client",_uID, ack);
}

void  UserService::process4bind(const Tracing & trace, const std::string & block)
{
    Service::process4bind(trace, block);
}

void  UserService::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._toService == ServiceUser && trace._toServiceID == getServiceID())
    {
        Service::process(trace, block, len);
        return;
    }
    if (trace._toService == ServiceClient && trace._toServiceID == getServiceID())
    {
        if (_clientID != InvalidSessionID)
        {
            SessionManager::getRef().sendSessionData(_clientID, block, len);
        }
        else
        {
            LOGW("lose client. user ID=" << getServiceID());
        }
        return;
    }
    
    LOGF("UserService::process trace=" << trace);
}
