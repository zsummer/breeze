/*
 * zsummerX License
 * -----------
 *
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 *
 *
 * ===============================================================================
 *
 * Copyright (C) 2010-2017 YaweiZhang <yawei.zhang@foxmail.com>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ===============================================================================
 *
 * (end of COPYRIGHT)
 */

#ifndef BREEZE_SERVICE_H_
#define BREEZE_SERVICE_H_
#include <common.h>


 /*
service是breeze引擎的核心结构, 通过包装对docker接口的再次包装, 实现了一切皆service的服务器架构.
通过简单的toService即可把数据发往另外一个service而不需要关心对方装载在本地还是另外一个docker上.
toService可以携带本地回调方法, 对方收到消息后通过backToService返回的消息可以直接在回调中处理. 
通过sloting方法可以注册当前service可接收的消息类型和对应的处理方法
 */


using Slot = std::function < void(const Tracing & trace, zsummer::proto4z::ReadStream &) >;
using ServiceCallback = std::function<void(zsummer::proto4z::ReadStream &)>;

struct RepeatTimerCounts 
{
    TimerID timerID = InvalidTimerID;
    ui32 delay = 0;
    ui32 interval = 0;
    ui32 repeat = 0;
    ui32 count = 0;
    bool withSysTime = false;
};
using RepeatTimerCB = std::function<void(TimerID tID, ui32 curRepeat, ui32 maxRepeat)>;
struct ReapeatTimerInfo
{
    RepeatTimerCounts counts;
    RepeatTimerCB  callback;
};
using ReapeatTimerInfoPtr = std::shared_ptr<ReapeatTimerInfo>;

class Docker;
class Service : public std::enable_shared_from_this<Service>
{
    friend Docker;
public:
    Service(){}
    virtual ~Service(){};

public:
    inline ui16 getServiceType(){ return _serviceType; }
    inline ServiceID getServiceID() { return _serviceID; }
    inline ServiceName getServiceName() { return _serviceName; }
    inline DockerID getServiceDockerID() { return _serviceDockerID; }
    inline DockerID getClientDockerID() { return _clientDockerID; }
    inline SessionID getClientSessionID() { return _clientSessionID; }
    inline ServiceInfo getServiceInfo() { return ServiceInfo(_serviceDockerID, _serviceType, _serviceID, _serviceName, _status, _clientDockerID, _clientSessionID); }
    inline ui16 getStatus() { return _status; }
    inline bool isShell() { return _shell; }
protected:
    inline void setServiceType(ServiceType serviceType) { _serviceType = serviceType; }
    inline void setServiceID(ServiceID serviceID) { _serviceID = serviceID; }
    inline void setServiceName(ServiceName serviceName) { _serviceName = serviceName; }
    inline void setServiceDockerID(DockerID dockerID) { _serviceDockerID = dockerID; }
    inline void setClientSessionID(SessionID clientSessionID) { _clientSessionID = clientSessionID; }
    inline void setClientDockerID(DockerID clientDockerID) { _clientDockerID = clientDockerID; }

    inline void setStatus(ui16 status) { _status = status; };
    inline void setShell(bool shell) { _shell = shell; }

public:
    using Slots = std::unordered_map<unsigned short, Slot>;
    template<class Proto>
    inline void slotting(const Slot & msgfun) { _slots[Proto::getProtoID()] = msgfun; _slotsName[Proto::getProtoID()] = Proto::getProtoName(); }

public: //与其他service进行交互,支持单例服务,多例服务,异构服务,客户端 
    bool canToService(ServiceType serviceType, ServiceID serviceID = InvalidServiceID);

    void toService(ServiceType serviceType, ServiceID serviceID, const OutOfBand &oob, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    void toService(ServiceType serviceType, ServiceID serviceID, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    void toService(ServiceType serviceType, const OutOfBand &oob, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    void toService(ServiceType serviceType, const char * block, unsigned int len, ServiceCallback cb = nullptr);

    template<class Proto>
    void toService(ServiceType serviceType, ServiceID serviceID, const OutOfBand &oob, Proto proto, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ServiceType serviceType, const OutOfBand &oob, Proto proto, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ServiceType serviceType, ServiceID serviceID, Proto proto, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ServiceType serviceType, Proto proto, ServiceCallback cb = nullptr);

    //根据trace信息直接把数据丢给来源service. 
    void backToService(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    template<class Proto>
    void backToService(const Tracing & trace, Proto proto, ServiceCallback cb = nullptr);

    //直接发送给客户端 
    void directToRealClient(DockerID clientDockerID, SessionID clientSessionID, const char * block, unsigned int len);
    template<class Proto>
    void directToRealClient(DockerID clientDockerID, SessionID clientSessionID, Proto proto);

    //发送给docker
    void toDocker(DockerID dockerID, const char * block, unsigned int len);
    void toDocker(DockerID dockerID, const OutOfBand & oob, const char * block, unsigned int len);
    template<class Proto>
    void toDocker(DockerID dockerID, Proto proto);
    template<class Proto>
    void toDocker(DockerID dockerID, const OutOfBand & oob, Proto proto);


public:
    //该定时器并不需要维护定时器ID 除非有需要cancel的情况. 
    //对于repeat类型的定时器, 在service完成卸载后 会由该父类进行全部取消与清除操作, 无需担心定时器造成的引用计数问题. 
    TimerID createTimer(ui32 delay, ui32 repeat, ui32 interval, bool withSysTime,
        const RepeatTimerCB& cb);
    //repeat类型的定时器, 取消时以最后一次回调中的tID为准. 每次repeat定时器ID都会换一次. 这里要注意. 
    bool cancelTimer(TimerID tID);

protected:
    virtual void onTick(TimerID tID, ui32 count, ui32 repeat) = 0; //仅限STrait_Single 特性且非shell的service才会调用该回调.  

    virtual bool onLoad() = 0; //service初始化好之后要调用finishLoad 
    bool finishLoad();

    virtual void onClientChange() = 0;
    virtual void onUnload() = 0;//service卸载好之后要调用finishUnload 
    bool finishUnload();


protected:

    
    virtual void process(const Tracing & trace, const char * block, unsigned int len);
    virtual void process4bind(const Tracing & trace, const std::string & block);
private:
    void onTimer(const ReapeatTimerInfoPtr & rt);


private:
    ui64 makeCallback(const ServiceCallback &cb);
    void cleanCallback();
    ServiceCallback checkoutCallback(ui64 cbid);

private:
    Slots _slots;
    std::map<ProtoID, std::string> _slotsName;
    std::set<TimerID> _repeatTimers;
private:
    ServiceType _serviceType = InvalidServiceType;
    ServiceID _serviceID = InvalidServiceID;
    ServiceName _serviceName = InvalidServiceName;
    DockerID _serviceDockerID = InvalidDockerID; //实际所在的docker
    SessionID _clientSessionID = InvalidSessionID; //如果存在关联的客户端,则该ID代表在实际所在docker中的sessionID. 目前仅限AvatarService使用
    DockerID _clientDockerID = InvalidDockerID; //如果存在关联的客户端,则该ID代表在_clientSessionID所在dockerID. 目前仅限AvatarService使用

    ui16 _status = SS_CREATED;
    bool _shell = false;
    

private:
    ui64 _callbackSeq = 0;
    time_t _callbackCleanTS = 0;
    std::map<ui64, std::pair<time_t,ServiceCallback> > _cbs;

};
using ServicePtr = std::shared_ptr<Service>;
using ServiceWeakPtr = std::shared_ptr<Service>;

inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & os, Service & svc)
{
    os << " --[ " << svc.getServiceDockerID() << ":" << svc.getServiceName() << ":" << svc.getServiceID()
        << ":" << svc.getStatus()
        << " client=" << svc.getClientDockerID() << ":"
        << svc.getClientSessionID() << " ]--  ";
    return os;
}

template<class Proto>
void Service::toService(ServiceType serviceType, const OutOfBand &oob, Proto proto, ServiceCallback cb)
{
    try
    {
        LOGT("Service::toService" << *this << ", dstType=" << ::getServiceName(serviceType) << ", protoName=" << Proto::getProtoName());
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(serviceType, oob, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toDocker catch except error. service=" << getServiceInfo() << ", protoID=" << Proto::getProtoID() << ", e=" << e.what());
    }
}
template<class Proto>
void Service::toService(ServiceType serviceType, ServiceID serviceID, const OutOfBand &oob, Proto proto, ServiceCallback cb)
{
    try
    {
        LOGT("Service::toService" << *this << ", dstType=" << ::getServiceName(serviceType) <<", dstID=" << serviceID
            << ", protoName=" << Proto::getProtoName());
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(serviceType, serviceID, oob, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toDocker catch except error. service=" << getServiceInfo() << ", protoID=" << Proto::getProtoID() << ", e=" << e.what());
    }
}
template<class Proto>
void Service::toService(ServiceType serviceType, ServiceID serviceID, Proto proto, ServiceCallback cb )
{
    toService(serviceType, serviceID, OutOfBand(), proto, cb);
}
template<class Proto>
void Service::toService(ServiceType serviceType, Proto proto, ServiceCallback cb)
{
    toService(serviceType, InvalidServiceID, OutOfBand(), proto, cb);
}
template<class Proto>
void Service::backToService(const Tracing & trace, Proto proto, ServiceCallback cb)
{
    try
    {
        LOGT("Service::backToService" << *this << ", dstType=" << ::getServiceName(trace.routing.fromServiceType) 
            << ", dstID=" << trace.routing.fromServiceID << ", protoName=" << Proto::getProtoName());
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        backToService(trace, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toDocker catch except error. service=" << getServiceInfo() << ", protoID=" << Proto::getProtoID() << ", e=" << e.what());
    }
}

template<class Proto>
void Service::directToRealClient(DockerID clientDockerID, SessionID clientSessionID, Proto proto)
{
    try
    {
        LOGT("Service::directToRealClient" << *this << ", dstDockerID=" << clientDockerID
            << ", dstSessionID=" << clientSessionID << ", protoName=" << Proto::getProtoName());
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        directToRealClient(clientDockerID, clientSessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toDocker catch except error. service=" << getServiceInfo() << ", protoID=" << Proto::getProtoID() << ", e=" << e.what());
    }
}

template<class Proto>
void Service::toDocker(DockerID dockerID, Proto proto)
{
    try
    {
        LOGT("Service::toDocker" << *this << ", dstDockerID=" << dockerID << ", protoName=" << Proto::getProtoName());
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toDocker(dockerID, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toDocker catch except error. service=" << getServiceInfo() << ", protoID=" << Proto::getProtoID() << ", e=" << e.what());
    }
}
template<class Proto>
void Service::toDocker(DockerID dockerID, const OutOfBand & oob, Proto proto)
{
    try
    {
        LOGT("Service::toDocker" << *this << ", dstDockerID=" << dockerID << ", protoName=" << Proto::getProtoName());
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toDocker(dockerID, oob, ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toDocker catch except error. service=" << getServiceInfo() << ", protoID=" << Proto::getProtoID() << ", e=" << e.what());
    }
}








#endif


