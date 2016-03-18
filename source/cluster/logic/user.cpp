#include "user.h"

User::User()
{
    setServiceType(ServiceUser);

}

User::~User() 
{
}

void User::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    //globalCall;

    //globalCall("client",_uID, ack);
}

void  User::process2(const Tracing & trace, const std::string & block)
{
    Service::process2(trace, block);
}

void  User::process(const Tracing & trace, const char * block, unsigned int len)
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
    
    LOGF("User::process trace=" << trace);
}

void User::globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
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

void User::backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
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