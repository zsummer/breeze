
#include "service.h"
#include "application.h"
#include <ProtoCluster.h>


void Service::setInited()
{
    _inited = true;
}

void Service::setWorked(bool work)
{
    if (!isShell() && work)
    {
        LOGD("Service::setWorked broadcast. service=" << ServiceNames.at(getServiceType()) << ", id=" << getServiceID());
        ClusterServiceInited inited(getServiceType(), getServiceID());
        Application::getRef().broadcast(inited);
    }
    if (isShell())
    {
        if (work)
        {
            LOGI("remote service [" << ServiceNames.at(getServiceType()) << "] begin worked [" << getServiceID() << "] ...");
        }
        else
        {
            LOGW("remote service [" << ServiceNames.at(getServiceType()) << "] end work [" << getServiceID() << "] ...");
        }
    }
    else
    {
        if (work)
        {
            LOGI("local service [" << ServiceNames.at(getServiceType()) << "] begin worked [" << getServiceID() << "] ...");
        }
        else
        {
            LOGW("local service [" << ServiceNames.at(getServiceType()) << "] end work [" << getServiceID() << "] ...");
        }
    }

    _worked = work;
}

ui32 Service::makeCallback(const ServiceCallback &cb)
{
    ui32 cbid = ++_callbackSeq;
    _cbs.insert(std::make_pair(cbid, std::make_pair(getNowTime(), cb)));
    return cbid;
}
ServiceCallback Service::checkCallback(ui32 cbid)
{
    auto founder = _cbs.find(cbid);
    if (founder == _cbs.end())
    {
        return nullptr;
    }
    auto cb = std::move(founder->second.second);
    _cbs.erase(founder);
    return std::move(cb);
}
void Service::checkCallback()
{
    time_t now = getNowTime();
    if (now - _callbackCheck > 180)
    {
        _callbackCheck = now;
        for (auto iter = _cbs.begin(); iter != _cbs.end();)
        {
            if (now - iter->second.first > 600)
            {
                LOGW("Service::globalCall waiting callback timeout. cbid=" << iter->first << ", call time=" << iter->second.first);
                iter = _cbs.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}

void Service::globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace._fromService = getServiceType();
    trace._fromServiceD = getServiceID();
    trace._traceBackID = 0;
    trace._traceID = 0;
    trace._toService = st;
    trace._toServiceID = svcID;
    checkCallback();
    if (cb)
    {
        trace._traceID = makeCallback(cb);
    }
    
    Application::getRef().callOtherService(trace, block, len);
}

void Service::backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trc;
    trc._fromService = getServiceType();
    trc._fromServiceD = getServiceID();
    trc._traceBackID = trace._traceID;
    trc._traceID = 0;
    trc._toService = trace._fromService;
    trc._toServiceID = trace._fromServiceD;
    time_t now = getNowTime();
    if (cb)
    {
        trc._traceID = makeCallback(cb);
    }
    Application::getRef().callOtherService(trace, block, len);
}


void Service::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._traceBackID > 0)
    {
        auto cb = checkCallback(trace._traceBackID);
        if (!cb)
        {
            LOGE("Service::process callback timeout. cbid=" << trace._traceBackID);
            return;
        }
        try
        {
            ReadStream rs(block, len);
            cb(rs);
            return;
        }
        catch (std::runtime_error e)
        {
            LOGE("Service::process catch except error. e=" << e.what() << ", trace=" << trace);
            return;
        }
        return;
    }

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
            LOGE("Service::process call process error. not found maping function. pID=" << rs.getProtoID() << ", trace=" << trace);
        }
    }
    catch (std::runtime_error e)
    {
        LOGE("Service::process call process catch except error. e=" << e.what() << ", trace=" << trace);
    }
}








