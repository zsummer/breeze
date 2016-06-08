#include "userService.h"
#include <ProtoUserMgr.h>
#include <ProtoUser.h>


UserService::UserService()
{
    slotting<UserChatReq>(std::bind(&UserService::onChatReq, this, _1, _2));
    slotting<UserPingPongReq>(std::bind(&UserService::onUserPingPongReq, this, _1, _2));
}

UserService::~UserService() 
{
}


void UserService::onTick()
{
    LOGE("UserService::onTick");
}



void UserService::onUnload()
{
    finishUnload();
}

void UserService::onClientChange()
{
    if (getClientDockerID() != InvalidDockerID && getClientSessionID() != InvalidSessionID)
    {
        AttachUserFromUserMgrResp resp(EC_SUCCESS, getClientDockerID(), getClientSessionID(), getServiceID());
        Docker::getRef().sendToDocker(getClientDockerID(), resp);
    }
}

bool UserService::onLoad()
{
    _baseInfo.loadFromDB(shared_from_this(), UserBaseInfo(getServiceID(), getServiceName(), "", 0, 0), std::bind(&UserService::onModuleLoad, std::static_pointer_cast<UserService>(shared_from_this()), _1));
    return true;
}

void UserService::onModuleLoad(bool success)
{
    if (success)
    {
        _curLoadModuleCount++;
    }
    else 
    { 
        LOGE(" UserService::onModuleLoad false");
        return ; 
    }
    if (_curLoadModuleCount == _totalModuleCount)
    {
        finishLoad();
        AttachUserFromUserMgrResp resp(EC_SUCCESS, getClientDockerID(), getClientSessionID(), getServiceID());
        Docker::getRef().sendToDocker(getClientDockerID(), resp);
    }
    return ;
}


void UserService::onModuleUnload(bool success)
{
    if (success)
    {
        _curUnloadModuleCount++;
    }
    else
    {
        LOGE(" UserService::onModuleUnload false");
        return;
    }
    if (_curLoadModuleCount == _totalModuleCount)
    {
        finishUnload();
    }
    return;
}


void UserService::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserChatReq req;
    rs >> req;

    _baseInfo._data.level++;
    _baseInfo.writeToDB();

    UserChatResp resp;
    resp.fromServiceID = getServiceID();
    resp.msg = req.msg;
    toService(ServiceClient, req.toServiceID, resp);
}

void UserService::onUserPingPongReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserPingPongReq req;
    rs >> req;
    UserPingPongResp resp;
    resp.msg = req.msg;
    toService(ServiceClient, getServiceID(), resp);
    static int testCount = 0;
    testCount++;
    if (testCount %10000 == 0)
    {
        LOGA("onUserPingPongReq count=" << testCount);
    }
}

