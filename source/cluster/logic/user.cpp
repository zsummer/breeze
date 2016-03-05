#include "user.h"
#include <ProtoChat.h>
User::User(const std::string &entity, UserID uID) : MessageSlot(entity, uID)
{
    slotting(ChatReq::GetProtoID(), std::bind(&User::call, this, _1, _2, _3, _4, _5));
}

void User::onChatReq(TcpSocketPtr&, const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    //globalCall;
    ChatAck ack;
    //globalCall("client",_uID, ack);
}




