
#include "service.h"
#include "docker.h"
#include <ProtoDocker.h>


TimerID Service::createTimer(ui32 delay, ui32 repeat, ui32 interval, bool withSysTime,
    const RepeatTimerCB& cb)
{
    ReapeatTimerInfoPtr rt = std::make_shared<ReapeatTimerInfo>();
    rt->counts.delay = delay;
    rt->counts.repeat = repeat;
    rt->counts.interval = interval;
    rt->counts.count = 0;
    rt->counts.withSysTime = withSysTime;
    rt->callback = cb;
    TimerID tID = SessionManager::getRef().createTimer(delay,
        std::bind(&Service::onTimer, shared_from_this(), rt), withSysTime);
    rt->counts.timerID = tID;
    _repeatTimers.insert(tID);
    return tID;
}
bool Service::cancelTimer(TimerID tID)
{
    SessionManager::getRef().cancelTimer(tID);
    _repeatTimers.erase(tID);
    return true;
}

void Service::onTimer(const ReapeatTimerInfoPtr & rt)
{
    auto founder = _repeatTimers.find(rt->counts.timerID);
    if (founder == _repeatTimers.end())
    {
        LOGE("Service::onTimer " << *this << " can't found repeat timerID");
        return;
    }

    (rt->callback)(rt->counts.timerID, rt->counts.count, rt->counts.repeat);

    founder = _repeatTimers.find(rt->counts.timerID);
    if (founder == _repeatTimers.end())
    {
        LOGE("Service::onTimer " << *this << " can't found repeat timerID. maybe it's cancel. timerID=" << rt->counts.timerID);
        return;
    }
    _repeatTimers.erase(founder);
    if (rt->counts.count == rt->counts.repeat)
    {
        return;
    }
    rt->counts.count++;
    TimerID tID = SessionManager::getRef().createTimer(rt->counts.interval,
        std::bind(&Service::onTimer, shared_from_this(), rt), rt->counts.withSysTime);
    rt->counts.timerID = tID;
    _repeatTimers.insert(tID);
}
bool Service::finishLoad()
{
    setStatus(SS_WORKING);
    if (!isShell())
    {
       if (true)
       {
           LoadServiceNotice notice;
           notice.shellServiceInfos.push_back(ServiceInfo(
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
            refreshNotice.shellServiceInfos.push_back(ServiceInfo(
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

        LOGI(*this << "local service finish load. service=" << getServiceName() << ", id=" << getServiceID());
    }
    else
    {
        LOGI(*this << "remote service finish load. service=" << getServiceName() << ", id=" << getServiceID());
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
            refreshNotice.shellServiceInfos.push_back(ServiceInfo(
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
        LOGI(*this << "local service finish unload. service=" << getServiceName() << ", id=" << getServiceID());
    }
    else
    {
        LOGI(*this << "remote service finish unload. service=" << getServiceName() << ", id=" << getServiceID());
    }
    for (auto tID : _repeatTimers)
    {
        SessionManager::getRef().cancelTimer(tID);
    }
    _repeatTimers.clear();
    return true;
}


ui64 Service::makeCallback(const ServiceCallback &cb)
{
    ui64 cbid = ++_callbackSeq;
    _cbs.insert(std::make_pair(cbid, std::make_pair(getNowTime(), cb)));
    return cbid;
}
ServiceCallback Service::checkoutCallback(ui64 cbid)
{
    cleanCallback();
    auto founder = _cbs.find(cbid);
    if (founder == _cbs.end())
    {
        return nullptr;
    }
    auto cb = std::move(founder->second.second);
    _cbs.erase(founder);
    return cb;
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
                LOGW("Service::cleanCallback  " << *this << " waiting callback timeout. cbid=" << iter->first << ", call time=" << iter->second.first);
                iter = _cbs.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}


bool Service::canToService(ServiceType serviceType, ServiceID serviceID)
{
    auto s = Docker::getRef().peekService(serviceType == STClient ? STAvatar : serviceType, serviceID);
    if (!s)
    {
        return false;
    }
    if (Docker::getRef().getDockerLinked(s->getServiceDockerID()) == InvalidSessionID)
    {
        return false;
    }
    if (serviceType == STClient && s->getClientSessionID() == InvalidSessionID)
    {
        return false;
    }
    return true;
}


void Service::toService(ServiceType serviceType, ServiceID serviceID, const OutOfBand &oob,  const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trace;
    trace.routing.fromServiceType = getServiceType();
    trace.routing.fromServiceID = getServiceID();
    trace.routing.traceBackID = 0;
    trace.routing.traceID = 0;
    trace.routing.toServiceType = serviceType;
    trace.routing.toServiceID = serviceID;
    trace.oob = oob;
    if (cb)
    {
        trace.routing.traceID = makeCallback(cb);
    }
    if (trace.routing.toServiceType == STClient && trace.routing.toServiceID == InvalidServiceID)
    {
        if ((trace.oob.clientDockerID == InvalidDockerID && trace.oob.clientSessionID != InvalidSessionID) 
            || (trace.oob.clientDockerID != InvalidDockerID && trace.oob.clientSessionID == InvalidSessionID))
        {
            LOGE("toService STClient via session ID but param had some wrong. the condition is clientDockerID and clientSessionID need all valid. trace=" << trace);
            return;
        }
        if (trace.oob.clientDockerID == InvalidDockerID && trace.oob.clientAvatarID == InvalidAvatarID && getServiceType() != STAvatar)
        {
            LOGE("toService STClient but can not get the avatar ID. trace=" << trace << ", this service=" << getServiceType());
            return;
        }
        if (trace.oob.clientDockerID == InvalidDockerID && trace.oob.clientAvatarID == InvalidAvatarID && getServiceType() == STAvatar)
        {
            trace.routing.toServiceID = getServiceID();
        }
        if (trace.oob.clientDockerID == InvalidDockerID && trace.oob.clientAvatarID != InvalidAvatarID)
        {
            trace.routing.toServiceID = trace.oob.clientAvatarID;
        }
    }
    else if (::getServiceTrait(trace.routing.toServiceType) == STrait_Multi && trace.routing.toServiceID == InvalidServiceID)
    {
        LOGE("toService STrait_Multi but can not get the toServiceID. trace=" << trace << ", this service=" << getServiceType());
        return;
    }
    Docker::getRef().toService(trace, block, len, false);
}



void Service::toService(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len, ServiceCallback cb)
{
    OutOfBand oob;
    if (getServiceType() == STAvatar)
    {
        oob.clientDockerID = getClientDockerID();
        oob.clientSessionID = getClientSessionID();
        oob.clientAvatarID = getServiceID();
    }
    toService(serviceType, serviceID, oob, block, len, cb);
}


void Service::toService(ServiceType serviceType, const OutOfBand &oob, const char * block, unsigned int len, ServiceCallback cb)
{
    toService(serviceType, InvalidServiceID, oob, block, len, cb);
}

void Service::toService(ServiceType serviceType, const char * block, unsigned int len, ServiceCallback cb)
{
    OutOfBand oob;
    if (getServiceType() == STAvatar)
    {
        oob.clientDockerID = getClientDockerID();
        oob.clientSessionID = getClientSessionID();
        oob.clientAvatarID = getServiceID();
    }
    toService(serviceType, InvalidServiceID, oob, block, len, cb);
}



void Service::backToService(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb)
{
    Tracing trc;
    trc.routing.fromServiceType = getServiceType();
    trc.routing.fromServiceID = getServiceID();
    trc.routing.traceID = 0;
    trc.routing.traceBackID = trace.routing.traceID;
    trc.routing.toServiceType = trace.routing.fromServiceType;
    trc.routing.toServiceID = trace.routing.fromServiceID;
    trc.oob = trace.oob;
    if (cb)
    {
        trc.routing.traceID = makeCallback(cb);
    }
    Docker::getRef().toService(trc, block, len, false);
}

void Service::directToRealClient(DockerID clientDockerID, SessionID clientSessionID, const char * block, unsigned int len)
{
    if (clientDockerID == ServerConfig::getRef().getDockerID())
    {
        Docker::getRef().sendViaSessionID(clientSessionID, block, len);
        return;
    }
    Tracing trc;
    trc.routing.fromServiceType = getServiceType();
    trc.routing.fromServiceID = getServiceID();
    trc.routing.traceID = 0;
    trc.routing.traceBackID = 0;
    trc.routing.toServiceType = STClient;
    trc.routing.toServiceID = InvalidServiceID;
    trc.oob.clientDockerID = clientDockerID;
    trc.oob.clientSessionID = clientSessionID;
    trc.oob.clientAvatarID = InvalidServiceID;
    Docker::getRef().forwardToRemoteService(trc, block, len);
}

void Service::toDocker(DockerID dockerID, const OutOfBand & oob, const char * block, unsigned int len)
{
    Tracing trc;
    trc.routing.fromServiceType = getServiceType();
    trc.routing.fromServiceID = getServiceID();
    trc.routing.traceID = 0;
    trc.routing.traceBackID = 0;
    trc.routing.toServiceType = STClient;
    trc.routing.toServiceID = InvalidServiceID;
    trc.oob = oob;
    WriteStream ws(ForwardToDocker::getProtoID());
    ws << trc;
    ws.appendOriginalData(block, len);
    Docker::getRef().sendViaDockerID(dockerID, ws.getStream(), ws.getStreamLen());
}
void Service::toDocker(DockerID dockerID, const char * block, unsigned int len)
{
    OutOfBand oob;
    if (getServiceType() == STAvatar)
    {
        oob.clientDockerID = getClientDockerID();
        oob.clientSessionID = getClientSessionID();
        oob.clientAvatarID = getServiceID();
    }
    toDocker(dockerID, oob, block, len);
}





void Service::process4bind(const Tracing & trace, const std::string & block)
{
    process(trace, block.c_str(), (unsigned int)block.length());
}

void Service::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace.routing.traceBackID > 0)
    {
        auto cb = checkoutCallback(trace.routing.traceBackID);
        if (!cb)
        {
            LOGE("Service::process  " << *this << " callback timeout. cbid=" << trace.routing.traceBackID);
            return;
        }
        try
        {
            ReadStream rs(block, len);
            LOGT("Service::process callback. " << *this << ", protoID=" << rs.getProtoID());
            cb(rs);
            return;
        }
        catch (const std::exception & e)
        {
            LOGE("Service::process  " << *this << " catch except error. e=" << e.what() << ", trace=" << trace);
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
            LOGT("Service::process sloting. " << *this << ", protoID=" << rs.getProtoID());
            fder->second(trace, rs);
        }
        else
        {
            LOGW("Service::process  " << *this << " call process warnning. not found maping function. pID=" << rs.getProtoID() << ", trace=" << trace);
        }
    }
    catch (const std::exception & e)
    {
        LOGE("Service::process  " << *this << " call process catch except error. e=" << e.what() << ", trace=" << trace);
    }
}






