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
    SS_INITED = 1,
    SS_WORKED = 2,
    SS_IS_SHELL= 3,
    SS_STOP = 4,
};



class Application;
class Service : public std::enable_shared_from_this<Service>
{
    friend Application;
public:
    Service(){}
    virtual ~Service(){};
    using Slots = std::unordered_map<unsigned short, Slot>;

    inline ui16 getServiceType(){ return _type; }
    inline ServiceID getServiceID(){ return _serviceID; }
    inline ClusterID getClusterID(){ return _cltID; }
    inline bool isShell(){ return _cltID != InvalidClusterID; }
    inline bool isInited(){ return getBitFlag(_status, SS_INITED); }
    inline bool isWorked(){ return getBitFlag(_status, SS_WORKED) && !getBitFlag(_status, SS_STOP); }
protected:
    inline void setServiceType(ui16 st) { _type = st; }
    inline void setServiceID(ServiceID serviceID) { _serviceID = serviceID; }
    void setWorked(bool work);
private:
    void setInited();
    inline void setShell(ClusterID cltID) { _cltID = cltID; }
    void onTimer();
protected:
    virtual bool onInit() = 0; //user must setWorked(true) when init finish & success. 
    virtual void onTick() = 0; //
    virtual void onStop() = 0; //user must setWorked(false) when stop finish & success. 
protected:
    template<class Proto>
    inline void slotting(const Slot & msgfun) { _slots[Proto::getProtoID()] = msgfun; _slotsName[Proto::getProtoID()] = Proto::getProtoName(); }
    
    virtual void process(const Tracing & trace, const char * block, unsigned int len);
    virtual void process4bind(const Tracing & trace, const std::string & block);

    virtual void globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    virtual void backCall(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb = nullptr);

    ui32 makeCallback(const ServiceCallback &cb);
    void cleanCallback();
    ServiceCallback checkoutCallback(ui32 cbid);

private:
    Slots _slots;
    std::map<ProtoID, std::string> _slotsName;
    ui16 _type = (ui16)ServiceInvalid;
    short _status = 0;
    ClusterID _cltID = InvalidClusterID;
    ServiceID _serviceID = InvalidServiceID;
    TimerID _timer = InvalidTimerID;
private:
    ui32 _callbackSeq = 0;
    time_t _callbackCleanTS = 0;
    std::map<ui32, std::pair<time_t,ServiceCallback> > _cbs;

};
using ServicePtr = std::shared_ptr<Service>;



#endif


