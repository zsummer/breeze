#include "userService.h"
#include <ProtoUserMgr.h>
#include <ProtoUser.h>


UserService::UserService()
{
    slotting<UserChatReq>(std::bind(&UserService::onChatReq, this, _1, _2));
}

UserService::~UserService() 
{
}


void UserService::onTick()
{
    LOGE("UserService::onTick");
}



void UserService::onUninit()
{
    finishUninit();
}

bool UserService::onInit()
{
    _baseInfo.initFromDB(shared_from_this(), UserBaseInfo(getServiceID(), "", "", 0, 0), nullptr);
    return true;
}

bool UserService::onModuleInit(bool success)
{
    if (success)
    {
        _curInitedModuleCount++;
    }
    else 
    { 
        Docker::getRef().stop(); 
        return false; 
    }
    if (_curInitedModuleCount == _totalInitedModuleCount)
    {
        finishInit();
        AttachUserFromUserMgrResp resp(EC_SUCCESS, getClientDockerID(), getClientSessionID(), getServiceID());
        Docker::getRef().sendToDocker(getClientDockerID(), resp);
    }
    return true;
}

void UserService::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserChatReq req;
    rs >> req;
    UserChatResp resp;
    resp.fromServiceID = getServiceID();
    resp.msg = req.msg;
    toService(ServiceClient, req.toServiceID, resp);
}

