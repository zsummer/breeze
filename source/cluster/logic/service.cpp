
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

void Service::globalCall(ServiceType st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace._fromService = getServiceType();
    trace._fromServiceD = getServiceID();
    trace._traceBackID = 0;
    trace._traceID = ++_seqID;
    trace._toService = st;
    trace._toServiceID = svcID;
    if (cb)
    {
        _cbs.insert(std::make_pair(trace._traceID, cb));
    }
    Application::getRef().globalCall(trace, block, len);
}

void Service::backCall(const Tracing & trace, const char * block, unsigned int len)
{
    Tracing trc;
    trc._fromService = getServiceType();
    trc._fromServiceD = getServiceID();
    trc._traceBackID = trace._traceID;
    trc._traceID = ++_seqID;
    trc._toService = trace._fromService;
    trc._toServiceID = trace._fromServiceD;
    trc._fromLocal = trace._fromLocal;
    if (trc._fromLocal)
    {
        onBacking(trc, block, len);
    }
    else
    {
        Application::getRef().globalBack(trc, block, len);
    }
}

void Service::process(const Tracing & trace, const char * block, unsigned int len)
{
    try
    {
        ReadStream rs(block, len);
        auto founder = _slots.find(rs.getProtoID());
        if (founder != _slots.end())
        {
            founder->second(trace, rs);
        }
        else
        {
            LOGE("Service::process not found maping function. pID=" << rs.getProtoID());
        }
    }
    catch (std::runtime_error e)
    {
        LOGE("Service::process catch except. e=" << e.what());
    }
}

void Service::onBacking(const Tracing & trace, const char * block, unsigned int len)
{
    auto founder = _cbs.find(trace._traceBackID);
    if (founder != _cbs.end())
    {
        try
        {
            auto cb = std::move(founder->second);
            _cbs.erase(founder);
            ReadStream rs(block, len);
            cb(rs);
        }
        catch (std::runtime_error e)
        {
            LOGE("Service::onBacking catch except. e=" << e.what());
        }
    }
    else
    {
        LOGW("Service::onBacking not found callback. try call process...");
        try
        {
            ReadStream rs(block, len);
            auto fder = _slots.find(rs.getProtoID());
            if (fder != _slots.end())
            {
                fder->second(trace, rs);
            }
            else
            {
                LOGE("Service::onBacking try call process error. not found maping function. pID=" << rs.getProtoID());
            }
        }
        catch (std::runtime_error e)
        {
            LOGE("Service::onBacking try call process catch except. e=" << e.what());
        }
    }
}






