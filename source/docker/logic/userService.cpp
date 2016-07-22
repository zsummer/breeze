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


void UserService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    LOGI("UserService::onTick");
}




void UserService::onClientChange()
{
    if (getClientDockerID() != InvalidDockerID && getClientSessionID() != InvalidSessionID)
    {
        AttachUserFromUserMgrResp resp(EC_SUCCESS, getClientDockerID(), getClientSessionID(), getServiceID());
        Docker::getRef().sendViaDockerID(getClientDockerID(), resp);
    }
}

bool UserService::onLoad()
{
    UserBaseInfo ubi;
    ubi.userID = getServiceID();
    ubi.userName = getServiceName();
    _baseInfo.loadFromDB(shared_from_this(), ubi, std::bind(&UserService::onModuleLoad, std::static_pointer_cast<UserService>(shared_from_this()), _1, _2));
    return true;
}

void UserService::onUnload()
{
    _baseInfo.writeToDB(std::bind(&UserService::onModuleUnload, std::static_pointer_cast<UserService>(shared_from_this()), _1, _2));
}


void UserService::onModuleLoad(bool success, const std::string & moduleName)
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
        Docker::getRef().sendViaDockerID(getClientDockerID(), resp);
    }
    return ;
}


void UserService::onModuleUnload(bool success, const std::string & moduleName)
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
    LOGI("onChatReq" << req << ", self serviceID=" << getServiceID());
    _baseInfo._data.level++;
    _baseInfo.writeToDB();

    UserChatResp resp;
    resp.fromUserID = getServiceID();
    resp.msg = req.msg;
    toService(STClient, req.userID, resp);
}

void UserService::onUserPingPongReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserPingPongReq req;
    rs >> req;
    UserPingPongResp resp;
    resp.msg = req.msg;
    toService(STClient, getServiceID(), resp);
    static int testCount = 0;
    testCount++;
    if (testCount %10000 == 0)
    {
        LOGA("onUserPingPongReq count=" << testCount);
    }
}

