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
    if (trace._toService == ServiceUser || trace._toService == ServiceClient)
    {
        auto founder = _userShells.find(trace._toServiceID);
        if (founder == _userShells.end())
        {
            LOGE("UserMgr not found the user/client id trace=" << trace);
            return;
        }
        const ServiceUserShell & shell = founder->second;
        if (shell._uID != trace._toServiceID)
        {
            LOGF("UserMgr found the user/client id, but user shell store service id not user id or cluster id invalid. trace=" << trace
                <<", shell.uID=" << shell._uID << ", shell.cltID=" << shell._cltID);
            return;
        }
        
        try
        {
            WriteStream ws(ClusterClientForward::GetProtoID());
            ws << trace;
            ws.appendOriginalData(block, len);
            Application::getRef().callOtherCluster(shell._cltID, ws.getStream(), ws.getStreamLen());
        }
        catch (std::runtime_error e)
        {
            LOGE("UserMgr::process catch except error. e=" << e.what());
        }
        return;
    }
    LOGF("UserMgr::process trace=" << trace);
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
    slotting<UserAuthReq>(std::bind(&UserMgr::onAuthReq, this, _1, _2));
}



void UserMgr::onAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{

}

