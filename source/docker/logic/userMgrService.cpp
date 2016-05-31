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

void UserMgrService::onInitDB(zsummer::proto4z::ReadStream & rs, int cur, int total)
{
    SQLQueryResp resp;
    rs >> resp;
    if (cur == 1 &&(resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS))
    {
        LOGE("UserMgrService::onInitDB error");
        return;
    }
    else if (cur == total)
    {
        finishInit();
    }
    else
    {
        auto sqls = UserBaseInfo().getDBBuild();
        SQLQueryReq req(sqls.at(cur));
        toService(ServiceInfoDBMgr, req, std::bind(&UserMgrService::onInitDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, cur+1, (int)sqls.size()));
    }
    return;

}
bool UserMgrService::onInit()
{
    const auto  & config = ServerConfig::getRef().getServiceTypeConfig().at(ServiceUser);
    for (auto dockerID : config)
    {
        _balance.enableNode(dockerID);
    }
    if (config.empty())
    {
        LOGE("at least have one docker contain ServiceUser service ");
        return false;
    }
    if (true)
    {
        auto sqls = UserBaseInfo().getDBBuild();
        SQLQueryReq req(sqls.at(0));
        toService(ServiceInfoDBMgr, req, std::bind(&UserMgrService::onInitDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, 1, (int)sqls.size()));
    }
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

    if (req.account.empty() || req.token != req.token)
    {
        SelectUserPreviewsFromUserMgrResp resp;
        resp.account = req.account;
        resp.token = req.token;
        resp.previews.clear();
        resp.clientDockerID = req.clientDockerID;
        resp.clientSessionID = req.clientSessionID;
        resp.retCode = EC_PERMISSION_DENIED;
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.

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
void UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB(zsummer::proto4z::ReadStream & rs, const Tracing & trace, const SelectUserPreviewsFromUserMgrReq & req)
{
    LOGD("UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB");
    SQLResult result;
    rs >> result;
    DBResult dbResult;
    dbResult.buildResult((QueryErrorCode)result.qc, result.errMsg, result.sql, result.affected, result.fields);
    SelectUserPreviewsFromUserMgrResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = dbResult.getErrorCode() == QEC_SUCCESS ? EC_SUCCESS : EC_DB_ERROR;
    while (dbResult.getErrorCode() == QEC_SUCCESS && dbResult.haveRow())
    {
        UserPreview pre;
        dbResult >> pre.uID;
        dbResult >> pre.account;
        dbResult >> pre.uName;
        dbResult >> pre.iconID;
        resp.previews.push_back(pre);
    }
    _accountPreviews[resp.account] = resp.previews;
    Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
}

void UserMgrService::onCreateUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    CreateUserFromUserMgrReq req;
    rs >> req;

 
}



void UserMgrService::onSelectUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &)
{

}






