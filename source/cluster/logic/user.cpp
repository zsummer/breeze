#include "user.h"
#include <ProtoChat.h>
User::User()
{
    setServiceType(ServiceUser);
    slotting<ChatReq>(std::bind(&User::onChatReq, this, _1, _2));
}
User::~User() 
{
}

void User::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    //globalCall;
    ChatAck ack;
    //globalCall("client",_uID, ack);
}




