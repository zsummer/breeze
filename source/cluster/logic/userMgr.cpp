#include "application.h"
#include "userMgr.h"
#include <ProtoDBService.h>
#include <ProtoUser.h>



UserMgr::~UserMgr()
{
    
}

void UserMgr::onTick()
{
    time_t now = getNowTime();
    if (now - _lastTime > 10)
    {
        _lastTime = now;
        LOGA("UserMgr::onTick");
    }
}
void  UserMgr::process(const Tracing & trace, const char * block, unsigned int len)
{
    if (trace._toService == ServiceUserMgr)
    {
        Service::process(trace, block, len);
        return;
    }
    if (trace._toService != ServiceUser)
    {
        LOGE("unknown ");
        return;
    }
    globalCall(trace._toService, trace._toServiceID, block, len, nullptr);
}
void UserMgr::onStop()
{
    setWorked(false);
}

bool UserMgr::onInit()
{
    setWorked(true);
    return true;
}

UserMgr::UserMgr()
{
    slotting<AuthReq>(std::bind(&UserMgr::onAuthReq, this, _1, _2));
}



void UserMgr::onAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{
    AuthResp resp;
    WriteStream ws(AuthResp::GetProtoID());
    ws << resp;
    backCall(trace, ws.getStream(), ws.getStreamLen(), nullptr);
}

