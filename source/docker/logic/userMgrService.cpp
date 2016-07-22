#include "docker.h"
#include "userMgrService.h"
#include <ProtoCommon.h>
#include <ProtoUser.h>

UserMgrService::UserMgrService()
{
    slotting<RefreshServiceToMgrNotice>(std::bind(&UserMgrService::onRefreshServiceToMgrNotice, this, _1, _2));
    slotting<RealClientClosedNotice>(std::bind(&UserMgrService::onRealClientClosedNotice, this, _1, _2));
    slotting<ClientAuthReq>(std::bind(&UserMgrService::onClientAuthReq, this, _1, _2));
    slotting<CreateUserReq>(std::bind(&UserMgrService::onCreateUserReq, this, _1, _2));
    slotting<AttachUserReq>(std::bind(&UserMgrService::onAttachUserReq, this, _1, _2));
}

UserMgrService::~UserMgrService()
{
    
}

void UserMgrService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    time_t now = getNowTime();
    if (now - _lastTime > 10)
    {
        _lastTime = now;


        LOGI("UserMgrService::onTick balance=" << Docker::getRef().getUserBalance().getBalanceStatus());


        for (auto iter = _freeList.begin(); iter != _freeList.end();)
        {
            if (iter->second->_status == SS_WORKING && getNowTime() - iter->second->_lastChangeTime > 30)
            {
                auto service = Docker::getRef().peekService(STUser, iter->second->_preview.userID);
                if (service)
                {
                    UnloadServiceInDocker unload(service->getServiceType(), service->getServiceID());
                    Docker::getRef().sendViaDockerID(service->getServiceDockerID(), unload);
                }
                else
                {
                    LOGE("service not unload finish. used time = " << getNowTime() - iter->second->_lastChangeTime << ", serviceID=" << iter->second->_preview.userID);
                }
                iter = _freeList.erase(iter);
                continue;
            }
            iter++;
        }
    }
}

void UserMgrService::onUnload()
{
    finishUnload();
}

void UserMgrService::onClientChange()
{
    return ;
}


bool UserMgrService::onLoad()
{
    _nextUserID = ServerConfig::getRef().getMinServiceID()+1;

    std::string sql = trim(UserPreview().getDBSelectPure(), " ");
    sql = subStringWithoutBack(sql, " ");
    sql += " `tb_UserBaseInfo` ";
    int curLimit = 0;
    DBQueryReq req(sql + "limit 0, 100");
    toService(STInfoDBMgr, req,
        std::bind(&UserMgrService::onLoadUserPreviewsFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, curLimit, sql));
    return true;
}

void UserMgrService::onLoadUserPreviewsFromDB(zsummer::proto4z::ReadStream & rs, int curLimit, const std::string &sql)
{
    DBQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS)
    {
        LOGE("onLoadUserPreviewsFromDB error. errCode=" << resp.retCode 
            << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() <<  ", sql=" << sql);
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.qc != QEC_SUCCESS )
    {
        LOGE("onLoadUserPreviewsFromDB error. errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
            << ", sql msg=" << resp.result.errMsg
            << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() << ", sql=" << sql);
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.fields.empty())
    {
        LOGA("onLoadUserPreviewsFromDB success. errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
            << ", sql msg=" << resp.result.errMsg
            << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() << ", sql=" << sql);

        LOGD("onLoadLastUIDFromDB _nextUserID=" << _nextUserID << ", areaID=" << ServerConfig::getRef().getAreaID()
            << ", area begin uid=" << ServerConfig::getRef().getMinServiceID());
        finishLoad();
        return;
    }
    DBResult result;
    result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
    while (result.haveRow())
    {
        UserPreview up;
        up.fetchFromDBResult(result);

        if (_userStatusByID.find(up.userID) != _userStatusByID.end()
            || _userStatusByName.find(up.userName) != _userStatusByName.end())
        {
            LOGA("onLoadUserPreviewsFromDB . errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
                << ", sql msg=" << resp.result.errMsg
                << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() << ", sql=" << sql);
            LOGE("User ID or Name conflict. " << up);
            return;
        }
        updateUserPreview(up);
        if (_nextUserID < up.userID)
        {
            _nextUserID = up.userID;
        }
    }
    DBQueryReq req(sql + "limit " + toString(curLimit+100) + ", 100");
    toService(STInfoDBMgr, req,
        std::bind(&UserMgrService::onLoadUserPreviewsFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, curLimit+100, sql));

}




void UserMgrService::updateUserPreview(const UserPreview & pre)
{
    UserStatusPtr usp;
    if (true)
    {
        auto founder = _userStatusByID.find(pre.userID);
        if (founder == _userStatusByID.end())
        {
            usp = std::make_shared<UserStatus>();
            usp->_status = SS_NONE;
            usp->_preview = pre;
            _userStatusByID[pre.userID] = usp;
            _userStatusByName[pre.userName] = usp;
        }
        else
        {
            usp = founder->second;
            usp->_preview = pre;
        }
        _userStatusByName[pre.userName] = usp;
    }
    if (true)
    {
        auto &acs = _accountStatus[pre.account];
        acs._users[pre.userID] = usp;
    }
}

void UserMgrService::onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    LoadServiceNotice notice;
    rs >> notice;
    for (const auto & si : notice.shellServiceInfos)
    {
        if (si.serviceType == STUser)
        {
            auto founder = _userStatusByID.find(si.serviceID);
            if (founder == _userStatusByID.end())
            {
                LOGE("error");
                return;
            }
            founder->second->_status = si.status;
            founder->second->_lastChangeTime = getNowTime();
        }
    }

}




void UserMgrService::onClientAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    ClientAuthReq req;
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
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
    }
    else
    {
        std::string sql = trim(UserPreview().getDBSelectPure(), " ");
        sql = subStringWithoutBack(sql, " ");
        sql += " `tb_UserBaseInfo` where account=?;";
 
        DBQuery q(sql);
        q << req.account;
        DBQueryReq sqlReq(q.pickSQL());
        toService(STInfoDBMgr, sqlReq,
            std::bind(&UserMgrService::onClientAuthReqFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, trace, req));
    }
}
void UserMgrService::onClientAuthReqFromDB(zsummer::proto4z::ReadStream & rs, const Tracing & trace, const SelectUserPreviewsFromUserMgrReq & req)
{
    LOGD("UserMgrService::onClientAuthReqFromDB");
    DBResult dbResult;
    DBQueryResp sqlResp;
    rs >> sqlResp;
    dbResult.buildResult((QueryErrorCode)sqlResp.result.qc, sqlResp.result.errMsg, sqlResp.result.sql, sqlResp.result.affected, sqlResp.result.fields);


    SelectUserPreviewsFromUserMgrResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = sqlResp.retCode != EC_SUCCESS ? sqlResp.retCode : (dbResult.getErrorCode() != QEC_SUCCESS ? EC_DB_ERROR : EC_SUCCESS);
    if (sqlResp.retCode == EC_SUCCESS && dbResult.getErrorCode() == QEC_SUCCESS )
    {
        _accountStatus[resp.account];
        while (dbResult.haveRow())
        {
            UserPreview pre;
            pre.fetchFromDBResult(dbResult);
            resp.previews.push_back(pre);
            updateUserPreview(pre);
        }
    }
    Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
}

void UserMgrService::onCreateUserReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    CreateUserFromUserMgrReq req;
    rs >> req;
    CreateUserFromUserMgrResp resp;
    resp.retCode = EC_SUCCESS;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;

    auto founder = _accountStatus.find(req.account);
    if (founder == _accountStatus.end())
    {
        resp.retCode = EC_USER_NOT_FOUND;
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    if (founder->second._users.size() > 4 )
    {
        resp.retCode = EC_USER_COUNT_LIMITE;
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    if ( getNowTime() - founder->second._lastCreateTime < 60)
    {
        resp.retCode = EC_USER_FREQ_LIMITE;
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }

    if (_userStatusByName.find(req.userName) != _userStatusByName.end())
    {
        resp.retCode = EC_USER_NAME_CONFLICT;
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    founder->second._lastCreateTime = getNowTime();
    UserBaseInfo userBaseInfo;
    userBaseInfo.account = req.account;
    userBaseInfo.userID = ++_nextUserID;
    userBaseInfo.userName = req.userName;
    userBaseInfo.level = 1;
    userBaseInfo.iconID = 0;

    DBQueryReq sql(userBaseInfo.getDBInsert());
    toService(STInfoDBMgr, sql,
        std::bind(&UserMgrService::onCreateUserFromUserMgrReqFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, userBaseInfo, req));
}

void UserMgrService::onCreateUserFromUserMgrReqFromDB(zsummer::proto4z::ReadStream & rs, const UserBaseInfo & ubi, const CreateUserFromUserMgrReq &req)
{
    LOGD("UserMgrService::onCreateUserFromUserMgrReqFromDB");
    DBQueryResp sqlResp;
    rs >> sqlResp;

    CreateUserFromUserMgrResp resp;
    resp.retCode = EC_SUCCESS;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = sqlResp.retCode;
    
    if (sqlResp.result.qc != QEC_SUCCESS || sqlResp.result.affected == 0)
    {
        resp.retCode = EC_DB_ERROR;
    }
    if (resp.retCode == EC_SUCCESS)
    {
        UserPreview up(ubi.userID, ubi.userName, ubi.account, ubi.iconID, ubi.level);
        updateUserPreview(up);
        for (const auto & kv : _accountStatus[ubi.account]._users)
        {
            resp.previews.push_back(kv.second->_preview);
        }
    }

    Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
}

void UserMgrService::onAttachUserReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    AttachUserReq req;
    rs >> req;
    AttachUserResp resp;
    resp.retCode = EC_SUCCESS;

    auto founder = _userStatusByID.find(req.userID);
    if (founder == _userStatusByID.end() || founder->second->_preview.account != req.account)
    {
        resp.retCode = EC_ERROR;
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    auto & status = *founder->second;
    if (status._status == SS_UNLOADING || status._status == SS_INITING )
    {
        resp.retCode = EC_ERROR;
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    status._lastChangeTime = getNowTime();
    _freeList.erase(req.userID);
    if (status._status == SS_NONE || status._status == SS_DESTROY)
    {
        DockerID dockerID = Docker::getRef().getUserBalance().selectAuto();
        if (dockerID == InvalidDockerID)
        {
            resp.retCode = EC_ERROR;
            Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
            return;
        }
        status._status = SS_INITING;
        status._clientDockerID = req.clientDockerID;
        status._clientSessionID = req.clientSessionID;
        LoadService notice(STUser, req.userID, status._preview.userName, req.clientDockerID, req.clientSessionID);
        Docker::getRef().sendViaDockerID(dockerID, notice);
    }
    else if(status._status == SS_WORKING)
    {
        status._clientDockerID = req.clientDockerID;
        status._clientSessionID = req.clientSessionID;
        SwitchServiceClientNotice change(STUser, req.userID, req.clientDockerID, req.clientSessionID);
        Docker::getRef().broadcastToDockers(change, true);
        //Docker::getRef().sendViaDockerID(STUser, req.serviceID, change);
    }
    else
    {
        resp.retCode = EC_ERROR; 
        Docker::getRef().sendViaDockerID(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
}


void UserMgrService::onRealClientClosedNotice(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    RealClientClosedNotice notice;
    rs >> notice;
    auto founder = _userStatusByID.find(notice.serviceID);
    if (founder == _userStatusByID.end())
    {
        LOGE("onRealClientClosedNotice not found service id.  " << notice.serviceID);
        return;
    }
    if (founder->second->_clientDockerID == notice.clientDockerID
        && founder->second->_clientSessionID == notice.clientSessionID
        && founder->second->_status == SS_WORKING)
    {
        SwitchServiceClientNotice change(STUser, notice.serviceID, InvalidDockerID, InvalidSessionID);
        Docker::getRef().sendViaServiceID(STUser, notice.serviceID, change);
        founder->second->_lastChangeTime = getNowTime();
        _freeList[notice.serviceID] = founder->second;
    }

}



