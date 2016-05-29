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
    slotting<SelectUserPreviewsFromUserMgrReq>(std::bind(&UserMgrService::onSelectUserPreviewsFromUserMgrReq, this, _1, _2));
    slotting<CreateUserFromUserMgrReq>(std::bind(&UserMgrService::onCreateUserFromUserMgrReq, this, _1, _2));
    slotting<SelectUserFromUserMgrReq>(std::bind(&UserMgrService::onSelectUserFromUserMgrReq, this, _1, _2));
}



void UserMgrService::onSelectUserPreviewsFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    SelectUserPreviewsFromUserMgrReq req;
    rs >> req;

    SelectUserPreviewsFromUserMgrResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = EC_SUCCESS;


    if (req.account.empty() || req.token != req.token)
    {
        resp.retCode = EC_PERMISSION_DENIED;
        //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        Tracing backTrace;
        backTrace._toServiceType = trace._fromServiceType;
        backTrace._toServiceID = trace._fromServiceID;
        backTrace._fromServiceType = trace._toServiceType;
        backTrace._fromServiceID = trace._toServiceID;
        backTrace._traceID = trace._traceBackID;
        backTrace._traceBackID = trace._traceID;
        Docker::getRef().forwardToDocker(req.clientDockerID, backTrace, resp);
    }
    else
    {
        DBQuery q("select uID, account, nickName, iconID from tb_UserBaseInfo where account=?;");
        q << req.account;
        SQLQueryReq sql(q.pickSQL());
        toService(ServiceInfoDBMgr, sql, 
            std::bind(&UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, trace, req));
    }
}
void UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB(zsummer::proto4z::ReadStream &, const Tracing & trace, const SelectUserPreviewsFromUserMgrReq & req)
{
    LOGD("UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB");
}
void UserMgrService::onCreateUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{

}



void UserMgrService::onSelectUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{

}






