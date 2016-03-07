
#include "service.h"



bool Service::init()
{
    _inited = true;
    return true;
}

bool Service::start()
{
    _worked = true;
    return true;
}

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





