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



void  User::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._toService == ServiceUser)
    {
        Service::process(trace, block, len);
        return;
    }
    if (trace._toService == ServiceClient)
    {
        //session manager
    }
    
    LOGF("User::process trace=" << trace);
}

void User::globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
{
    if (st == ServiceUser || st == ServiceInvalid)
    {
        return;
    }
    if (st != ServiceClient)
    {
        Service::globalCall(st, svcID, block, len, cb);
        return;
    }

    
    //session manager
}
void User::backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    if (trace._fromService != ServiceClient)
    {
        Service::backCall(trace, block, len, cb);
        return;
    }
    //session manager
}