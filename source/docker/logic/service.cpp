
#include "service.h"
#include "docker.h"
#include <ProtoDocker.h>


void Service::beginTimer()
{
    if (_timer == InvalidTimerID)
    {
        _timer = SessionManager::getRef().createTimer(5000, std::bind(&Service::onTimer, shared_from_this()));
    }
}
void Service::onTimer()
{
    if (_timer == InvalidTimerID)
    {
        return;
    }
    _timer = SessionManager::getRef().createTimer(5000, std::bind(&Service::onTimer, shared_from_this()));
    try
    {
        onTick();
    }
    catch (const std::exception & e)
    {
        LOGE("Service::onTimer catch except error. e=" << e.what() << ", service=" << getServiceName() << ", service id=" << getServiceID());
    }
}

bool Service::finishLoad()
{
    setStatus(SS_WORKING);
    if (!isShell())
    {
       if (true)
       {
           LoadServiceNotice notice;
           notice.shellServiceInfos.push_back(ShellServiceInfo(
               getServiceDockerID(),
               getServiceType(),
               getServiceID(),
               getServiceName(),
               getStatus(),
               getClientDockerID(),
               getClientSessionID()));
           Docker::getRef().broadcastToDockers(notice, false);
       }

        if (getServiceTrait(getServiceType()) == STrait_Multi)
        {
            RefreshServiceToMgrNotice refreshNotice;
            refreshNotice.shellServiceInfos.push_back(ShellServiceInfo(
                getServiceDockerID(),
                getServiceType(),
                getServiceID(),
                getServiceName(),
                getStatus(),
                getClientDockerID(),
                getClientSessionID()));

            for (auto sd : ServiceDepends)
            {
                if (getServiceTrait(sd.first) == STrait_Single )
                {
                    toService(sd.first, refreshNotice, nullptr);
                }
            }
        }

        LOGI("local service finish load. service=" << getServiceName() << ", id=" << getServiceID());
    }
    else
    {
        LOGI("remote service finish load. service=" << getServiceName() << ", id=" << getServiceID());
    }
    
    return true;
}
bool Service::finishUnload()
{
    setStatus(SS_DESTROY);
    if (!isShell())
    {
        if (getServiceTrait(getServiceType()) == STrait_Multi)
        {
            RefreshServiceToMgrNotice refreshNotice;
            refreshNotice.shellServiceInfos.push_back(ShellServiceInfo(
                getServiceDockerID(),
                getServiceType(),
                getServiceID(),
                getServiceName(),
                getStatus(),
                getClientDockerID(),
                getClientSessionID()));
            for (auto sd : ServiceDepends)
            {
                if (getServiceTrait(sd.first) == STrait_Single)
                {
                    toService(sd.first, refreshNotice, nullptr);
                }
            }
        }

        UnloadedServiceNotice notice(getServiceType(), getServiceID());
        Docker::getRef().broadcastToDockers(notice, true);
        LOGI("local service finish unload. service=" << getServiceName() << ", id=" << getServiceID());
    }
    else
    {
        LOGI("remote service finish unload. service=" << getServiceName() << ", id=" << getServiceID());
    }
    
    return true;
}


ui32 Service::makeCallback(const ServiceCallback &cb)
{
    ui32 cbid = ++_callbackSeq;
    _cbs.insert(std::make_pair(cbid, std::make_pair(getNowTime(), cb)));
    return cbid;
}
ServiceCallback Service::checkoutCallback(ui32 cbid)
{
    cleanCallback();
    auto founder = _cbs.find(cbid);
    if (founder == _cbs.end())
    {
        return nullptr;
    }
    auto cb = std::move(founder->second.second);
    _cbs.erase(founder);
    return std::move(cb);
}

void Service::cleanCallback()
{
    time_t now = getNowTime();
    if (now - _callbackCleanTS > 180)
    {
        _callbackCleanTS = now;
        for (auto iter = _cbs.begin(); iter != _cbs.end();)
        {
            if (now - iter->second.first > 600)
            {
                LOGW("Service::cleanCallback waiting callback timeout. cbid=" << iter->first << ", call time=" << iter->second.first);
                iter = _cbs.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}

void Service::toService(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace.fromServiceType = getServiceType();
    trace.fromServiceID = getServiceID();
    trace.fromDockerID = getServiceDockerID();
    trace.traceBackID = 0;
    trace.traceID = 0;
    trace.toServiceType = serviceType;
    trace.toServiceID = serviceID;
    if (cb)
    {
        trace.traceID = makeCallback(cb);
    }
    Docker::getRef().toService(trace, block, len, true, true);
}

void Service::toService(ServiceType serviceType, const char * block, unsigned int len, ServiceCallback cb)
{
    toService(serviceType, InvalidServiceID, block, len, cb);
}

void Service::backToService(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trc;
    trc.fromDockerID = getServiceDockerID();
    trc.fromServiceType = getServiceType();
    trc.fromServiceID = getServiceID();
    trc.traceBackID = trace.traceID;
    trc.traceID = 0;
    trc.toServiceType = trace.fromServiceType;
    trc.toServiceID = trace.fromServiceID;
    trc.toDockerID = trace.fromDockerID;
    if (cb)
    {
        trc.traceID = makeCallback(cb);
    }
    Docker::getRef().toService(trc, block, len, true, true);
}

void Service::process4bind(const Tracing & trace, const std::string & block)
{
    process(trace, block.c_str(), (unsigned int)block.length());
}

void Service::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace.traceBackID > 0)
    {
        auto cb = checkoutCallback(trace.traceBackID);
        if (!cb)
        {
            LOGE("Service::process callback timeout. cbid=" << trace.traceBackID);
            return;
        }
        try
        {
            ReadStream rs(block, len);
            cb(rs);
            return;
        }
        catch (const std::exception & e)
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
            LOGW("Service::process call process warnning. not found maping function. pID=" << rs.getProtoID() << ", trace=" << trace);
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Service::process call process catch except error. e=" << e.what() << ", trace=" << trace);
    }
}








