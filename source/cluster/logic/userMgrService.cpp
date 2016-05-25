#include "application.h"
#include "userMgrService.h"
#include <ProtoCommon.h>
#include <ProtoDBService.h>
#include <ProtoUser.h>



UserMgrService::~UserMgrService()
{
    
}

void UserMgrService::onTick()
{
    time_t now = getNowTime();
    if (now - _lastTime > 10)
    {
        _lastTime = now;
        LOGA("UserMgrService::onTick");
    }
}

void  UserMgrService::process(const Tracing & trace, const char * block, unsigned int len)
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
            LOGE("UserMgrService not found the user/client id trace=" << trace);
            return;
        }
        const ServiceUserShell & shell = founder->second;
        if (shell._uID != trace._toServiceID)
        {
            LOGF("UserMgrService found the user/client id, but user shell store service id not user id or cluster id invalid. trace=" << trace
                <<", shell.uID=" << shell._uID << ", shell.cltID=" << shell._cltID);
            return;
        }
        
        try
        {
            WriteStream ws(ClusterClientForward::getProtoID());
            ws << trace;
            ws.appendOriginalData(block, len);
            Application::getRef().callOtherCluster(shell._cltID, ws.getStream(), ws.getStreamLen());
        }
        catch (const std::exception & e)
        {
            LOGE("UserMgrService::process catch except error. e=" << e.what());
        }
        return;
    }
    LOGF("UserMgrService::process trace=" << trace);
}
void UserMgrService::onUninit()
{
    finishUninit();
}


bool UserMgrService::onInit()
{
    const auto  & config = ServerConfig::getRef().getClusterConfig();
    for (const auto & cluster : config)
    {
        if (!cluster._wideIP.empty() && cluster._widePort != 0)
        {
            _balance.enableNode(cluster._cluster);
        }
    }
    finishInit();
    return true;
}

UserMgrService::UserMgrService()
{
    slotting<UserAuthReq>(std::bind(&UserMgrService::onUserAuthReq, this, _1, _2));
}



void UserMgrService::onUserAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserAuthReq req;
    rs >> req;
    UserAuthResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.clientClusterID = req.clientClusterID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = EC_SUCCESS;

    auto founder = _accountCache.find(req.account);
    if (founder == _accountCache.end())
    {
        return;
    }

    
    
    WriteStream ws(UserAuthResp::getProtoID());
    ws << resp;

    WriteStream wsf(ClusterClientForward::getProtoID());
    wsf << trace;
    wsf.appendOriginalData(ws.getStream(), ws.getStreamLen());
    Application::getRef().callOtherCluster(resp.clientClusterID, wsf.getStream(), wsf.getStreamLen());
}

