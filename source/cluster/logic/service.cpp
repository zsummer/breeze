
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

void Service::globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace._fromService = getServiceType();
    trace._fromServiceD = getServiceID();
    trace._traceBackID = 0;
    trace._traceID = ++_seqID;
    trace._toService = st;
    trace._toServiceID = svcID;
    time_t now = getNowTime();
    if (cb)
    {
        LOGD("Service::globalCall make callback. cbid=" << trace._traceID << ", call time=" << now);
        _cbs.insert(std::make_pair(trace._traceID, std::make_pair(now, cb)));
    }
    
    if (now - _lastCheckCallback > 180)
    {
        _lastCheckCallback = now;
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
    
    Application::getRef().globalCall(trace, block, len);
}

void Service::backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trc;
    trc._fromService = getServiceType();
    trc._fromServiceD = getServiceID();
    trc._traceBackID = trace._traceID;
    trc._traceID = ++_seqID;
    trc._toService = trace._fromService;
    trc._toServiceID = trace._fromServiceD;
    time_t now = getNowTime();
    if (cb)
    {
        LOGD("Service::backCall make callback. cbid=" << trace._traceID << ", call time=" << now);
        _cbs.insert(std::make_pair(trace._traceID, std::make_pair(now, cb)));
    }
    Application::getRef().globalCall(trc, block, len);
}


void Service::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._traceBackID > 0)
    {
        auto founder = _cbs.find(trace._traceBackID);
        if (founder != _cbs.end())
        {
            try
            {
                auto cb = std::move(founder->second.second);
                _cbs.erase(founder);
                ReadStream rs(block, len);
                cb(rs);
                return;
            }
            catch (std::runtime_error e)
            {
                LOGE("Service::process catch except. e=" << e.what() << ", trace=" << trace);
                return;
            }
        }
        else
        {
            LOGE("Service::process not found callback function. try to find slot. trace=" << trace);
        }
        //return;
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
        LOGE("Service::process call process catch except. e=" << e.what() << ", trace=" << trace);
    }
}








