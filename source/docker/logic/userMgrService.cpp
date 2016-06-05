#include "docker.h"
#include "userMgrService.h"
#include <ProtoCommon.h>
#include <ProtoDBService.h>
#include <ProtoUser.h>

UserMgrService::UserMgrService()
{
    slotting<SelectUserPreviewsFromUserMgrReq>(std::bind(&UserMgrService::onSelectUserPreviewsFromUserMgrReq, this, _1, _2));
    slotting<CreateUserFromUserMgrReq>(std::bind(&UserMgrService::onCreateUserFromUserMgrReq, this, _1, _2));
    slotting<AttachUserFromUserMgrReq>(std::bind(&UserMgrService::onAttachUserFromUserMgrReq, this, _1, _2));
    slotting<ClientDisconnectReq>(std::bind(&UserMgrService::onClientDisconnectReq, this, _1, _2));
}

UserMgrService::~UserMgrService()
{
    
}

void UserMgrService::onTick()
{
    time_t now = getNowTime();
    if (now - _lastTime > 10)
    {
        _lastTime = now;
        LOGD("UserMgrService::onTick");
        for (auto iter = _freeList.begin(); iter != _freeList.end();)
        {
            if (!iter->second)
            {
                iter = _freeList.erase(iter);
                continue;
            }
            else if (iter->second->_status == 2 && getNowTime() - iter->second->_lastChangeTime > 5*60)
            {
                iter->second->_status = 3;
                iter->second->_lastChangeTime = getNowTime();
                DestroyServiceInDocker destroy(ServiceUser, iter->second->_preview.serviceID);
                Docker::getRef().sendToDockerByService(ServiceUser, iter->second->_preview.serviceID, destroy);
            }
            else if (iter->second->_status = 3 && getNowTime() - iter->second->_lastChangeTime > 30)
            {
                if (!Docker::getRef().isHadService(ServiceUser, iter->second->_preview.serviceID))
                {
                    iter->second->_status = 0;
                    iter->second->_lastChangeTime = getNowTime();
                    iter = _freeList.erase(iter);
                    continue;
                }
                else
                {
                    LOGE("service not uninit finish. used time = " << getNowTime() - iter->second->_lastChangeTime << ", serviceID=" << iter->second->_preview.serviceID);
                }
            }
            iter++;
        }
    }
}

void UserMgrService::onUninit()
{
    finishUninit();
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

    SQLQueryReq sql("select max(serviceID) from tb_UserBaseInfo");
    toService(ServiceInfoDBMgr, sql,
        std::bind(&UserMgrService::onInitLastUIDFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1));
    return true;
}

void UserMgrService::onInitLastUIDFromDB(zsummer::proto4z::ReadStream & rs)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS)
    {
        LOGE("select max(serviceID) from tb_UserBaseInfo error.");
        return;
    }
    if (resp.result.qc != QEC_SUCCESS || resp.result.fields.empty())
    {
        LOGE("select max(serviceID) from tb_UserBaseInfo error. error sql msg=" << resp.result.errMsg);
        return;
    }
    _nextUserID = fromString<ui64>(resp.result.fields.front(), 0);
    if (_nextUserID < ServerConfig::getRef().getAreaID() * (ui64)pow(10,8))
    {
        _nextUserID = ServerConfig::getRef().getAreaID() * (ui64)pow(10, 8);
    }
    LOGD("onInitLastUIDFromDB _nextUserID=" << _nextUserID << ", areaID=" << ServerConfig::getRef().getAreaID() 
        << ", area begin uid=" << ServerConfig::getRef().getAreaID() * (ui64)pow(10, 8));
    finishInit();
}




void UserMgrService::updateUserPreview(const UserPreview & pre)
{
    UserStatusPtr usp;
    if (true)
    {
        auto founder = _userStatusByID.find(pre.serviceID);
        if (founder == _userStatusByID.end())
        {
            usp = std::make_shared<UserStatus>();
            usp->_status = 0;
            usp->_preview = pre;
            _userStatusByID[pre.serviceID] = usp;
            _userStatusByName[pre.serviceName] = usp;
        }
        else
        {
            usp = founder->second;
            usp->_preview = pre;
        }
        _userStatusByName[pre.serviceName] = usp;
    }
    if (true)
    {
        auto &acs = _accountStatus[pre.account];
        acs._users[pre.serviceID] = usp;
    }
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
        DBQuery q("select serviceID, account, serviceName, iconID from tb_UserBaseInfo where account=?;");
        q << req.account;
        SQLQueryReq sql(q.pickSQL());
        toService(ServiceInfoDBMgr, sql, 
            std::bind(&UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, trace, req));
    }
}
void UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB(zsummer::proto4z::ReadStream & rs, const Tracing & trace, const SelectUserPreviewsFromUserMgrReq & req)
{
    LOGD("UserMgrService::onSelectUserPreviewsFromUserMgrReqFromDB");
    DBResult dbResult;
    SQLQueryResp sqlResp;
    rs >> sqlResp;
    if (sqlResp.retCode == EC_SUCCESS)
    {
        dbResult.buildResult((QueryErrorCode)sqlResp.result.qc, sqlResp.result.errMsg, sqlResp.result.sql, sqlResp.result.affected, sqlResp.result.fields);
    }

    SelectUserPreviewsFromUserMgrResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;
    resp.retCode = sqlResp.retCode != EC_SUCCESS ? sqlResp.retCode : (dbResult.getErrorCode() != QEC_SUCCESS ? EC_DB_ERROR : EC_SUCCESS);
    while (sqlResp.retCode == EC_SUCCESS && dbResult.getErrorCode() == QEC_SUCCESS && dbResult.haveRow())
    {
        UserPreview pre;
        dbResult >> pre.serviceID;
        dbResult >> pre.account;
        dbResult >> pre.serviceName;
        dbResult >> pre.iconID;
        resp.previews.push_back(pre);
        updateUserPreview(pre);
    }
    Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
}

void UserMgrService::onCreateUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    CreateUserFromUserMgrReq req;
    rs >> req;
    CreateUserFromUserMgrResp resp;
    resp.retCode = EC_SUCCESS;
    resp.previews.clear();
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;

    auto founder = _accountStatus.find(req.account);
    if (founder == _accountStatus.end() || founder->second._users.size() > 4 || getNowTime() - founder->second._lastCreateTime < 60)
    {
        resp.retCode = EC_ERROR;
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }

    if (_userStatusByName.find(req.serviceName) != _userStatusByName.end())
    {
        resp.retCode = EC_ERROR;
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    founder->second._lastCreateTime = getNowTime();
    UserBaseInfo userBaseInfo;
    userBaseInfo.account = req.account;
    userBaseInfo.serviceID = ++_nextUserID;
    userBaseInfo.serviceName = req.serviceName;
    userBaseInfo.level = 1;
    userBaseInfo.iconID = 0;

    SQLQueryReq sql(userBaseInfo.getDBInsert());
    toService(ServiceInfoDBMgr, sql,
        std::bind(&UserMgrService::onCreateUserFromUserMgrReqFromDB, std::static_pointer_cast<UserMgrService>(shared_from_this()), _1, userBaseInfo, req));
}

void UserMgrService::onCreateUserFromUserMgrReqFromDB(zsummer::proto4z::ReadStream & rs, const UserBaseInfo & ubi, const CreateUserFromUserMgrReq &req)
{
    LOGD("UserMgrService::onCreateUserFromUserMgrReqFromDB");
    SQLQueryResp sqlResp;
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
        UserPreview up(ubi.serviceID, ubi.serviceName, ubi.iconID, ubi.account);
        updateUserPreview(up);
        for (const auto & kv : _accountStatus[ubi.account]._users)
        {
            resp.previews.push_back(kv.second->_preview);
        }
    }

    Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
}

void UserMgrService::onAttachUserFromUserMgrReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    AttachUserFromUserMgrReq req;
    rs >> req;
    AttachUserFromUserMgrResp resp;
    resp.retCode = EC_SUCCESS;
    resp.serviceID = req.serviceID;
    resp.clientDockerID = req.clientDockerID;
    resp.clientSessionID = req.clientSessionID;

    auto founder = _userStatusByID.find(req.serviceID);
    if (founder == _userStatusByID.end() || founder->second->_preview.account != req.account)
    {
        resp.retCode = EC_ERROR;
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    auto & status = *founder->second;
    if (status._status == 1 || status._status == 3 )
    {
        resp.retCode = EC_ERROR;
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
    status._lastChangeTime = getNowTime();
    _freeList.erase(req.serviceID);
    if (status._status == 0)
    {
        DockerID dockerID = _balance.selectAuto();
        if (dockerID == InvalidDockerID)
        {
            resp.retCode = EC_ERROR;
            Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
            return;
        }
        status._status = 1;
        CreateServiceInDocker notice(ServiceUser, req.serviceID, req.clientDockerID, req.clientSessionID);
        Docker::getRef().sendToDocker(dockerID, notice);
    }
    else if(status._status == 2)
    {
        ChangeServiceClient change(ServiceUser, req.serviceID, req.clientDockerID, req.clientSessionID);
        Docker::getRef().sendToDockerByService(ServiceUser, req.serviceID, change);
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
    }
    else
    {
        resp.retCode = EC_ERROR; 
        Docker::getRef().sendToDocker(req.clientDockerID, resp); //这个是认证协议, 对应的UserService并不存在 所以不能通过toService和backToService等接口发出去.
        return;
    }
}


void UserMgrService::onClientDisconnectReq(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    ClientDisconnectReq req;
    rs >> req;
    auto founder = _userStatusByID.find(req.serviceID);
    if (founder == _userStatusByID.end())
    {
        LOGE("onClientDisconnectReq not found service id.  " << req.serviceID);
        return;
    }
    founder->second->_status = 2;
    founder->second->_lastChangeTime = getNowTime();
    _freeList[req.serviceID] = founder->second;
    ChangeServiceClient change(ServiceUser, req.serviceID, InvalidDockerID, InvalidSessionID);
    Docker::getRef().sendToDockerByService(ServiceUser, req.serviceID, change);
}



