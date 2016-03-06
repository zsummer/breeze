#include "user.h"
#include <ProtoChat.h>
User::User()
{
    setEntityName("User");
    slotting(ChatReq::GetProtoID(), std::bind(&User::onChatReq, this, _1, _2, _3));
}
User::~User() 
{
}

void User::onChatReq(TcpSessionPtr&, const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    //globalCall;
    ChatAck ack;
    //globalCall("client",_uID, ack);
}




