
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
        LOGE("Service::onTimer catch except error. e=" << e.what() << ", service=" << ServiceTypeNames.at(getServiceType()) << ", service id=" << getServiceID());
    }
}

bool Service::finishInit()
{
    setStatus(SS_WORKING);
    if (!isShell())
    {
        LOGI("local service finish init. service=" << ServiceTypeNames.at(getServiceType()) << ", id=" << getServiceID());
        CreateOrRefreshServiceNotice notice(
            getServiceDockerID(), 
            getServiceType(), 
            getServiceID(), 
            getServiceName(), 
            getStatus(),  
            getClientDockerID(), 
            getClientSessionID());
        Docker::getRef().broadcastToDockers(notice, false);
        for (ui16 i= ServiceInvalid+1; i < ServiceMulti; i++)
        {
            toService(i, notice, nullptr);
        }
    }
    else
    {
        LOGI("remote service finish init. service=" << ServiceTypeNames.at(getServiceType()) << ", id=" << getServiceID());
    }
    
    return true;
}
bool Service::finishUninit()
{
    setStatus(SS_DESTROY);
    if (!isShell())
    {
        LOGI("local service finish uninit. service=" << ServiceTypeNames.at(getServiceType()) << ", id=" << getServiceID());
        CreateOrRefreshServiceNotice refreshNotice(
            getServiceDockerID(),
            getServiceType(),
            getServiceID(),
            getServiceName(),
            getStatus(),
            getClientDockerID(),
            getClientSessionID());
        Docker::getRef().broadcastToDockers(refreshNotice, false);
        for (ui16 i = ServiceInvalid + 1; i < ServiceMulti; i++)
        {
            toService(i, refreshNotice, nullptr);
        }

        LOGI("local service finish uninit. service=" << ServiceTypeNames.at(getServiceType()) << ", id=" << getServiceID());
        DestroyServiceNotice notice(getServiceType(), getServiceID());
        Docker::getRef().broadcastToDockers(notice, true);
    }
    else
    {
        LOGI("remote service finish uninit. service=" << ServiceTypeNames.at(getServiceType()) << ", id=" << getServiceID());
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

void Service::toService(ui16 serviceType, ServiceID serviceID, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace._fromServiceType = getServiceType();
    trace._fromServiceID = getServiceID();
    trace._fromDockerID = getServiceDockerID();
    trace._traceBackID = 0;
    trace._traceID = 0;
    trace._toServiceType = serviceType;
    trace._toServiceID = serviceID;
    if (cb)
    {
        trace._traceID = makeCallback(cb);
    }
    Docker::getRef().toService(trace, block, len, true, true);
}

void Service::toService(ui16 serviceType, const char * block, unsigned int len, ServiceCallback cb)
{
    toService(serviceType, InvalidServiceID, block, len, cb);
}

void Service::backToService(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trc;
    trc._fromDockerID = getServiceDockerID();
    trc._fromServiceType = getServiceType();
    trc._fromServiceID = getServiceID();
    trc._traceBackID = trace._traceID;
    trc._traceID = 0;
    trc._toServiceType = trace._fromServiceType;
    trc._toServiceID = trace._fromServiceID;
    trc._toDockerID = trace._fromDockerID;
    if (cb)
    {
        trc._traceID = makeCallback(cb);
    }
    Docker::getRef().toService(trc, block, len, true, true);
}

void Service::process4bind(const Tracing & trace, const std::string & block)
{
    process(trace, block.c_str(), (unsigned int)block.length());
}

void Service::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._traceBackID > 0)
    {
        auto cb = checkoutCallback(trace._traceBackID);
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








