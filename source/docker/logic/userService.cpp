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
    //globalCall;

    //globalCall("client",_uID, ack);
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

void UserService::globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
{
    if ((st == ServiceClient && svcID != getServiceID())
        || (st != ServiceUser && st != ServiceClient))
    {
        Service::globalCall(st, svcID, block, len, cb);
        return;
    }
    if (st == ServiceClient)
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
    LOGE("globalCall unknown flow");
}

void UserService::backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    if ((trace._fromService == ServiceClient && trace._fromServiceID != getServiceID())
        || (trace._fromService != ServiceUser && trace._fromService != ServiceClient))
    {
        Service::backCall(trace, block, len, cb);
        return;
    }
    if (trace._fromService == ServiceClient)
    {
        if (_clientID != InvalidSessionID)
        {
            SessionManager::getRef().sendSessionData(_clientID, block, len);
        }
        else
        {
            LOGW("backCall lose client. user ID=" << getServiceID());
        }
        return;
    }
    LOGE("unknown flow");
}