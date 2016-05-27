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
            LOGF("UserMgrService found the user/client id, but user shell store service id not user id or docker id invalid. trace=" << trace
                <<", shell.uID=" << shell._uID << ", shell.dockerID=" << shell._dockerID);
            return;
        }
        
        try
        {
            WriteStream ws(ClientForward::getProtoID());
            ws << trace;
            ws.appendOriginalData(block, len);
            Application::getRef().sendToDocker(shell._dockerID, ws.getStream(), ws.getStreamLen());
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
    const auto  & config = ServerConfig::getRef().getDockerConfig();
    for (const auto & docker : config)
    {
        if (!docker._wideIP.empty() && docker._widePort != 0)
        {
            _balance.enableNode(docker._docker);
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
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = EC_SUCCESS;

    auto founder = _accountCache.find(req.account);
    if (founder == _accountCache.end())
    {
        return;
    }

    
    
    WriteStream ws(UserAuthResp::getProtoID());
    ws << resp;

    WriteStream wsf(ClientForward::getProtoID());
    wsf << trace;
    wsf.appendOriginalData(ws.getStream(), ws.getStreamLen());
    Application::getRef().sendToDocker(resp.clientDockerID, wsf.getStream(), wsf.getStreamLen());
}

