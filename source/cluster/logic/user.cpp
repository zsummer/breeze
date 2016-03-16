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




