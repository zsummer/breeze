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
 * Copyright (C) 2010-2016 YaweiZhang <yawei.zhang@foxmail.com>.
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


using Slot = std::function < void(const Tracing & trace, zsummer::proto4z::ReadStream &) >;
using ServiceCallback = std::function<void(zsummer::proto4z::ReadStream &)>;

using ProtoID = zsummer::proto4z::ProtoInteger;
const ProtoID InvalidProtoID = -1;

enum ServiceStatus
{
    SS_CREATED,
    SS_INITING,
    SS_WORKING,
    SS_UNINITING,
    SS_DESTROY,
};



class Docker;
class Service : public std::enable_shared_from_this<Service>
{
    friend Docker;
public:
    Service(){}
    virtual ~Service(){};

public:
    inline ui16 getServiceType(){ return _serviceType; }
    inline ServiceID getServiceID(){ return _serviceID; }
    inline DockerID getDockerID() { return _dockerID; }
    inline SessionID getClientSessionID() { return _clientSessionID; }
    inline DockerID getClientDockerID() { return _clientDockerID; }

    inline ui16 getStatus() { return _status; }
    inline bool isShell() { return _shell; }
protected:
    inline void setServiceType(ui16 serviceType) { _serviceType = serviceType; }
    inline void setServiceID(ServiceID serviceID) { _serviceID = serviceID; }
    inline void setDockerID(DockerID dockerID) { _dockerID = dockerID; }
    inline void setClientSessionID(SessionID clientSessionID) { _clientSessionID = clientSessionID; }
    inline void setClientDockerID(SessionID clientDockerID) { _clientDockerID = clientDockerID; }

    inline void setStatus(ui16 status) { _status = status; };
    inline void setShell(bool shell) { _shell = shell; }

private:
    void beginTimer();
    void onTimer();
protected:
    virtual void onTick() = 0; //仅限单例模式并且非shell的service才会调用这个 

    virtual bool onInit() = 0; //service初始化好之后要调用finishInit 
    bool finishInit();
    virtual void onUninit() = 0;//service卸载好之后要调用finishUninit 
    bool finishUninit();

protected:
    using Slots = std::unordered_map<unsigned short, Slot>;
    template<class Proto>
    inline void slotting(const Slot & msgfun) { _slots[Proto::getProtoID()] = msgfun; _slotsName[Proto::getProtoID()] = Proto::getProtoName(); }
    
    virtual void process(const Tracing & trace, const char * block, unsigned int len);
    virtual void process4bind(const Tracing & trace, const std::string & block);

public:
    void toService(ui16 serviceType, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    void toService(ui16 serviceType, ServiceID serviceID, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ui16 serviceType, Proto proto, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ui16 serviceType, ServiceID serviceID, Proto proto, ServiceCallback cb = nullptr);

    void backToService(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    template<class Proto>
    void backToService(const Tracing & trace, Proto proto, ServiceCallback cb = nullptr);

private:
    ui32 makeCallback(const ServiceCallback &cb);
    void cleanCallback();
    ServiceCallback checkoutCallback(ui32 cbid);

private:
    Slots _slots;
    std::map<ProtoID, std::string> _slotsName;

    TimerID _timer = InvalidTimerID;

private:
    ui16 _serviceType = (ui16)ServiceInvalid;
    ServiceID _serviceID = InvalidServiceID;
    DockerID _dockerID = InvalidDockerID; //实际所在的docker
    SessionID _clientSessionID = InvalidSessionID; //如果存在关联的客户端,则该ID代表在实际所在docker中的sessionID. 目前仅限UserService使用
    DockerID _clientDockerID = InvalidDockerID; //如果存在关联的客户端,则该ID代表在_clientSessionID所在dockerID. 目前仅限UserService使用

    short _status = 0;
    bool _shell = false;
    

private:
    ui32 _callbackSeq = 0;
    time_t _callbackCleanTS = 0;
    std::map<ui32, std::pair<time_t,ServiceCallback> > _cbs;

};
using ServicePtr = std::shared_ptr<Service>;
using ServiceWeakPtr = std::shared_ptr<Service>;

template<class Proto>
void Service::toService(ui16 serviceType, Proto proto, ServiceCallback cb)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(serviceType, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toService catch except error. e=" << e.what());
    }
}
template<class Proto>
void Service::toService(ui16 serviceType, ServiceID serviceID, Proto proto, ServiceCallback cb)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(serviceType, serviceID, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toService catch except error. e=" << e.what());
    }
}

template<class Proto>
void Service::backToService(const Tracing & trace, Proto proto, ServiceCallback cb)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        backToService(trace, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::backToService catch except error. e=" << e.what());
    }
}












#endif


