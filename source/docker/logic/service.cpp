
#include "service.h"
#include "application.h"
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
        LOGE("Service::onTimer catch except error. e=" << e.what() << ", service=" << ServiceNames.at(getServiceType()) << ", service id=" << getServiceID());
    }
}

bool Service::finishInit()
{
    if (!isShell())
    {
        LOGD("local service finish init. service=" << ServiceNames.at(getServiceType()) << ", id=" << getServiceID());
        CreateServiceNotice notice(getServiceType(), getServiceID(), getDockerID(), getClientID());
        Application::getRef().broadcast(notice);
    }
    else
    {
        LOGD("remote service finish init. service=" << ServiceNames.at(getServiceType()) << ", id=" << getServiceID());
    }
    setStatus(SS_WORKING);
    return true;
}
bool Service::finishUninit()
{
    if (!isShell())
    {
        LOGD("local service finish uninit. service=" << ServiceNames.at(getServiceType()) << ", id=" << getServiceID());
        DestroyServiceNotice notice(getServiceType(), getServiceID());
        Application::getRef().broadcast(notice);
    }
    else
    {
        LOGD("remote service finish uninit. service=" << ServiceNames.at(getServiceType()) << ", id=" << getServiceID());
    }
    setStatus(SS_DESTROY);
    SessionManager::getRef().post(std::bind(&Application::destroyService, Application::getPtr(), getServiceType(), getServiceID()));
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

void Service::globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace._fromService = getServiceType();
    trace._fromServiceID = getServiceID();
    trace._traceBackID = 0;
    trace._traceID = 0;
    trace._toService = st;
    trace._toServiceID = svcID;
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
    trc._fromServiceID = getServiceID();
    trc._traceBackID = trace._traceID;
    trc._traceID = 0;
    trc._toService = trace._fromService;
    trc._toServiceID = trace._fromServiceID;
    if (cb)
    {
        trc._traceID = makeCallback(cb);
    }
    Application::getRef().callOtherService(trc, block, len);
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
            LOGE("Service::process call process error. not found maping function. pID=" << rs.getProtoID() << ", trace=" << trace);
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Service::process call process catch except error. e=" << e.what() << ", trace=" << trace);
    }
}








