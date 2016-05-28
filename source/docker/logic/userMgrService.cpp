#include "docker.h"
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
            _balance.enableNode(docker._dockerID);
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

//     WriteStream wsf(ClientForward::getProtoID());
//     wsf << trace;
//     wsf.appendOriginalData(ws.getStream(), ws.getStreamLen());
//     Docker::getRef().sendToDocker(resp.clientDockerID, wsf.getStream(), wsf.getStreamLen());
}

