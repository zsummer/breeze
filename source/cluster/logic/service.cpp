
#include "service.h"
#include "application.h"
#include <ProtoCluster.h>



void Service::setWorked()
{
    if (!getShell())
    {
        ClusterServiceInited inited(getServiceType(), getServiceID());
        Application::getRef().broadcast(inited);
    }
    LOGI("Service worked service [" << ServiceNames.at(getServiceType()) << "][" << getServiceID() << "] ...");
    _worked = true;
}

void Service::call(const Tracing & trace, const char * block, unsigned int len)
{
    try
    {
        ReadStream rs(block, len);
        auto founder = _slots.find(rs.getProtoID());
        if (founder != _slots.end())
        {
            (founder->second)(trace, rs);
        }
    }
    catch (std::runtime_error e)
    {

    }
}





