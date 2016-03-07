
#include "service.h"





void Service::call(TcpSessionPtr  &session, const Tracing & trace, const char * block, unsigned int len)
{
    try
    {
        ReadStream rs(block, len);
        auto founder = _slots.find(rs.getProtoID());
        if (founder != _slots.end())
        {
            (founder->second)(session, trace, rs);
        }
    }
    catch (std::runtime_error e)
    {

    }
}




