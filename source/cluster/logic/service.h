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
class Application;
class Service : public std::enable_shared_from_this<Service>
{
public:
    Service(){}
    virtual ~Service(){};
    using Slots = std::unordered_map<unsigned short, Slot>;

    inline ui16 getServiceType(){ return _st; }
    inline ServiceID getServiceID(){ return _serviceID; }
    inline SessionID getSessionID(){ return _sID; }
    inline bool getShell(){ return _sID != InvalidSessionID; }
    inline bool getInited(){ return _inited; }
    inline bool getWorked(){ return _worked; }

protected:
    template<class Proto>
    inline void slotting(const Slot & msgfun){ _slots[Proto::GetProtoID()] = msgfun; _slotsName[Proto::GetProtoID()] = Proto::GetProtoName(); }

protected:
    inline void setServiceType(ui16 st){ _st = st; }
    inline void setServiceID(ServiceID serviceID){ _serviceID = serviceID; }
    virtual bool onInit() = 0;
    void setWorked();
    //call 其他服务.
    void globalCall(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb);
    void backCall(const Tracing & trace, const char * block, unsigned int len);
private:
    friend Application;
    inline void setInited(){ _inited = true; }
    inline void setShell(SessionID sID){ _sID = sID; }
    //处理服务
    void process(const Tracing & trace, const char * block, unsigned int len);
    //壳子处理
    void onBacking(const Tracing & trace, const char * block, unsigned int len);


private:
    Slots _slots;
    std::map<ProtoID, std::string> _slotsName;
    ui16 _st = (ui16)ServiceInvalid;
    bool _inited = false;
    bool _worked = false;
    bool _shell = false;
    SessionID _sID = InvalidSessionID;
    ServiceID _serviceID = InvalidServiceID;
    ui32 _seqID = 0;
    std::map<ui32, std::pair<time_t,ServiceCallback> > _cbs;
    time_t _lastCheckCallback = 0;
};
using ServicePtr = std::shared_ptr<Service>;



#endif


