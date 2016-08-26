#include "docker.h"
#include "avatarMgrService.h"
#include <ProtoCommon.h>
#include <ProtoClient.h>

AvatarMgrService::AvatarMgrService()
{
    slotting<RefreshServiceToMgrNotice>(std::bind(&AvatarMgrService::onRefreshServiceToMgrNotice, this, _1, _2));
    slotting<RealClientClosedNotice>(std::bind(&AvatarMgrService::onRealClientClosedNotice, this, _1, _2));
    slotting<ClientAuthReq>(std::bind(&AvatarMgrService::onClientAuthReq, this, _1, _2));
    slotting<CreateAvatarReq>(std::bind(&AvatarMgrService::onCreateAvatarReq, this, _1, _2));
    slotting<AttachAvatarReq>(std::bind(&AvatarMgrService::onAttachAvatarReq, this, _1, _2));

    slotting<GetSceneTokenInfoResp>(std::bind(&AvatarMgrService::onGetSceneTokenInfoResp, this, _1, _2));
    slotting<JoinSceneResp>(std::bind(&AvatarMgrService::onJoinSceneResp, this, _1, _2));
    slotting<JoinSceneNotice>(std::bind(&AvatarMgrService::onJoinSceneNotice, this, _1, _2));
    slotting<LeaveSceneResp>(std::bind(&AvatarMgrService::onLeaveSceneResp, this, _1, _2));
}

AvatarMgrService::~AvatarMgrService()
{
    
}

void AvatarMgrService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    checkFreeList();
    systemAutoChat();
}

void AvatarMgrService::systemAutoChat()
{
    if (getFloatNowTime() - _lastSystemChat < 30.0)
    {
        return;
    }
    _lastSystemChat = getFloatNowTime();

    auto avatars = Docker::getRef().peekService(STAvatar);
    ChatResp resp;
    resp.channelID = CC_SYSTEM;
    for (auto kv : avatars)
    {
        resp.msg.clear();
        switch (rand()%6+94)
        {
        case 0:
        {
            resp.msg = "Why don't you tell me a story ?";
        }
        break;
        case 1:
        {
            resp.msg = "Is anybody in here? ";
        }
        break;
        case 2:
        {
            resp.msg = "Welcome to the wild star. here nothing.";
        }
        break;
        case 3:
        {
            resp.msg = "Ladies And Gentlemen We Are Floating In Space.";
        }
        break;
        case 4:
        {
            resp.msg = "How long, How long until I see you ? ";
        }
        break;
        case 5:
        {
            resp.msg = "For summer being done, Can spring be far behind ? ";
        }
        break;

        default:
            break;
        }

        if (resp.msg.empty())
        {
            continue;
        }
        toService(STClient,kv.second->getServiceID(), resp);
    }
}
void AvatarMgrService::checkFreeList()
{
    
    if (getFloatNowTime() - _lastCheckFreeList < 10.0)
    {
        return;
    }
    _lastCheckFreeList = getFloatNowTime();


    LOGI("AvatarMgrService::onTick balance=" << Docker::getRef().getAvatarBalance().getBalanceStatus());


    for (auto iter = _freeList.begin(); iter != _freeList.end();)
    {
        if (iter->second->_status == SS_WORKING && getNowTime() - iter->second->_lastChangeTime > 30)
        {
            auto service = Docker::getRef().peekService(STAvatar, iter->second->_preview.avatarID);
            if (service)
            {
                UnloadServiceInDocker unload(service->getServiceType(), service->getServiceID());
                Docker::getRef().sendViaDockerID(service->getServiceDockerID(), unload);
            }
            else
            {
                LOGE("service not unload finish. used time = " << getNowTime() - iter->second->_lastChangeTime << ", serviceID=" << iter->second->_preview.avatarID);
            }
            iter = _freeList.erase(iter);
            continue;
        }
        iter++;
    }
}

void AvatarMgrService::onUnload()
{
    finishUnload();
}

void AvatarMgrService::onClientChange()
{
    return ;
}


bool AvatarMgrService::onLoad()
{
    _nextAvatarID = ServerConfig::getRef().getMinServiceID()+1;

    std::string sql = trim(AvatarPreview().getDBSelectPure(), " ");
    sql = subStringWithoutBack(sql, " ");
    sql += " `tb_AvatarBaseInfo` ";
    int curLimit = 0;
    DBQueryReq req(sql + "limit 0, 100");
    toService(STInfoDBMgr, req,
        std::bind(&AvatarMgrService::onLoadAvatarPreviewsFromDB, std::static_pointer_cast<AvatarMgrService>(shared_from_this()), _1, curLimit, sql));
    return true;
}

void AvatarMgrService::onLoadAvatarPreviewsFromDB(zsummer::proto4z::ReadStream & rs, int curLimit, const std::string &sql)
{
    DBQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS)
    {
        LOGE("onLoadAvatarPreviewsFromDB error. errCode=" << resp.retCode 
            << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() <<  ", sql=" << sql);
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.qc != QEC_SUCCESS )
    {
        LOGE("onLoadAvatarPreviewsFromDB error. errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
            << ", sql msg=" << resp.result.errMsg
            << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() << ", sql=" << sql);
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.fields.empty())
    {
        LOGA("onLoadAvatarPreviewsFromDB success. errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
            << ", sql msg=" << resp.result.errMsg
            << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() << ", sql=" << sql);

        LOGD("onLoadLastUIDFromDB _nextAvatarID=" << _nextAvatarID << ", areaID=" << ServerConfig::getRef().getAreaID()
            << ", area begin uid=" << ServerConfig::getRef().getMinServiceID());
        finishLoad();
        return;
    }
    DBResult result;
    result.buildResult((QueryErrorCode)resp.result.qc, resp.result.errMsg, resp.result.sql, resp.result.affected, resp.result.fields);
    while (result.haveRow())
    {
        AvatarPreview up;
        up.fetchFromDBResult(result);

        if (_userStatusByID.find(up.avatarID) != _userStatusByID.end()
            || _userStatusByName.find(up.userName) != _userStatusByName.end())
        {
            LOGA("onLoadAvatarPreviewsFromDB . errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
                << ", sql msg=" << resp.result.errMsg
                << ", curLimit=" << curLimit << ",  inited user=" << _userStatusByID.size() << ", sql=" << sql);
            LOGE("User ID or Name conflict. " << up);
            return;
        }
        updateAvatarPreview(up);
        if (_nextAvatarID < up.avatarID)
        {
            _nextAvatarID = up.avatarID;
        }
    }
    DBQueryReq req(sql + "limit " + toString(curLimit+100) + ", 100");
    toService(STInfoDBMgr, req,
        std::bind(&AvatarMgrService::onLoadAvatarPreviewsFromDB, std::static_pointer_cast<AvatarMgrService>(shared_from_this()), _1, curLimit+100, sql));

}




void AvatarMgrService::updateAvatarPreview(const AvatarPreview & pre)
{
    AvatarStatusPtr usp;
    if (true)
    {
        auto founder = _userStatusByID.find(pre.avatarID);
        if (founder == _userStatusByID.end())
        {
            usp = std::make_shared<AvatarStatus>();
            usp->_status = SS_NONE;
            usp->_preview = pre;
            _userStatusByID[pre.avatarID] = usp;
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
        acs._players[pre.avatarID] = usp;
    }
}

void AvatarMgrService::onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    LoadServiceNotice notice;
    rs >> notice;
    for (const auto & si : notice.shellServiceInfos)
    {
        if (si.serviceType == STAvatar)
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




void AvatarMgrService::onClientAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    ClientAuthReq req;
    rs >> req;
    ClientAuthResp resp;
    if (req.account.empty() || req.token != req.token)
    {
        resp.account = req.account;
        resp.token = req.token;
        resp.previews.clear();
        resp.retCode = EC_PERMISSION_DENIED;
        backToService(trace, resp);
        return;
    }

    std::string sql = trim(AvatarPreview().getDBSelectPure(), " ");
    sql = subStringWithoutBack(sql, " ");
    sql += " `tb_AvatarBaseInfo` where account=?;";

    DBQuery q(sql);
    q << req.account;
    DBQueryReq sqlReq(q.pickSQL());
    toService(STInfoDBMgr, sqlReq,
        std::bind(&AvatarMgrService::onClientAuthReqFromDB, std::static_pointer_cast<AvatarMgrService>(shared_from_this()), _1, trace, req));
}


void AvatarMgrService::onClientAuthReqFromDB(zsummer::proto4z::ReadStream & rs, const Tracing & trace, const ClientAuthReq & req)
{
    LOGD("AvatarMgrService::onClientAuthReqFromDB");
    DBResult dbResult;
    DBQueryResp sqlResp;
    rs >> sqlResp;
    dbResult.buildResult((QueryErrorCode)sqlResp.result.qc, sqlResp.result.errMsg, sqlResp.result.sql, sqlResp.result.affected, sqlResp.result.fields);


    ClientAuthResp resp;
    resp.account = req.account;
    resp.token = req.token;
    resp.previews.clear();
    resp.retCode = sqlResp.retCode != EC_SUCCESS ? sqlResp.retCode : (dbResult.getErrorCode() != QEC_SUCCESS ? EC_DB_ERROR : EC_SUCCESS);
    if (sqlResp.retCode == EC_SUCCESS && dbResult.getErrorCode() == QEC_SUCCESS )
    {
        _accountStatus[resp.account];
        while (dbResult.haveRow())
        {
            AvatarPreview pre;
            pre.fetchFromDBResult(dbResult);
            resp.previews.push_back(pre);
            updateAvatarPreview(pre);
        }
    }
    toDocker(trace.oob.clientDockerID, trace.oob, resp);
}

void AvatarMgrService::onCreateAvatarReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    CreateAvatarReq req;
    rs >> req;
    CreateAvatarResp resp;
    resp.retCode = EC_SUCCESS;
    resp.previews.clear();


    auto founder = _accountStatus.find(req.accountName);
    if (founder == _accountStatus.end())
    {
        resp.retCode = EC_AVATAR_NOT_FOUND;
        LOGE("onCreateAvatarReq error. EC_AVATAR_NOT_FOUND trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    if (founder->second._players.size() > 4 )
    {
        resp.retCode = EC_AVATAR_COUNT_LIMITE;
        LOGE("onCreateAvatarReq error. EC_AVATAR_COUNT_LIMITE trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    if ( getNowTime() - founder->second._lastCreateTime < 60)
    {
        resp.retCode = EC_AVATAR_FREQ_LIMITE;
        LOGE("onCreateAvatarReq error. EC_AVATAR_FREQ_LIMITE trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }

    if (_userStatusByName.find(req.userName) != _userStatusByName.end())
    {
        resp.retCode = EC_AVATAR_NAME_CONFLICT;
        LOGE("onCreateAvatarReq error. EC_AVATAR_NAME_CONFLICT trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    founder->second._lastCreateTime = getNowTime();
    AvatarBaseInfo userBaseInfo;
    userBaseInfo.account = req.accountName;
    userBaseInfo.avatarID = ++_nextAvatarID;
    userBaseInfo.userName = req.userName;
    userBaseInfo.level = 1;
    userBaseInfo.iconID = 0;

    DBQueryReq sql(userBaseInfo.getDBInsert());
    toService(STInfoDBMgr, sql,
        std::bind(&AvatarMgrService::onCreateAvatarReqFromDB, std::static_pointer_cast<AvatarMgrService>(shared_from_this()), _1, userBaseInfo, trace, req));
}

void AvatarMgrService::onCreateAvatarReqFromDB(zsummer::proto4z::ReadStream & rs, const AvatarBaseInfo & ubi, const Tracing & trace, const CreateAvatarReq & req)
{
    LOGD("AvatarMgrService::onCreateUserFromUserMgrReqFromDB");
    DBQueryResp sqlResp;
    rs >> sqlResp;

    CreateAvatarResp resp;
    resp.retCode = EC_SUCCESS;
    resp.previews.clear();
    resp.retCode = sqlResp.retCode;
    
    if (sqlResp.result.qc != QEC_SUCCESS || sqlResp.result.affected == 0)
    {
        LOGE("onCreateAvatarReqFromDB error. trace =" << trace << ", req=" << req);
        resp.retCode = EC_DB_ERROR;
    }
    if (resp.retCode == EC_SUCCESS)
    {
        AvatarPreview up(ubi.avatarID, ubi.userName, ubi.account, ubi.iconID, ubi.level);
        updateAvatarPreview(up);
        for (const auto & kv : _accountStatus[ubi.account]._players)
        {
            resp.previews.push_back(kv.second->_preview);
        }
    }
    directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
}

void AvatarMgrService::onAttachAvatarReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    AttachAvatarReq req;
    rs >> req;
    AttachAvatarResp resp;
    resp.avatarID = req.avatarID;
    resp.retCode = EC_SUCCESS;

    auto founder = _userStatusByID.find(req.avatarID);
    if (founder == _userStatusByID.end() || founder->second->_preview.account != req.accountName)
    {
        resp.retCode = EC_ERROR;
        LOGE("attach avatar error. trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    auto & status = *founder->second;
    if (status._status == SS_UNLOADING || status._status == SS_INITING )
    {
        resp.retCode = EC_ERROR;
        LOGE("attach avatar status error. trace =" << trace << ", req=" << req << ", status=" << status._status);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    status._lastChangeTime = getNowTime();
    _freeList.erase(req.avatarID);
    if (status._status == SS_NONE || status._status == SS_DESTROY)
    {
        DockerID dockerID = Docker::getRef().getAvatarBalance().selectAuto();
        if (dockerID == InvalidDockerID)
        {
            resp.retCode = EC_ERROR;
            LOGE("attach avatar error. no valid docker load avatar. trace =" << trace << ", req=" << req << ", status=" << status._status);
            directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
            return;
        }
        status._status = SS_INITING;
        status._clientDockerID = trace.oob.clientDockerID;
        status._clientSessionID = trace.oob.clientSessionID;
        LoadService notice(STAvatar, req.avatarID, status._preview.userName, status._clientDockerID, status._clientSessionID);
        Docker::getRef().sendViaDockerID(dockerID, notice);
    }
    else if(status._status == SS_WORKING)
    {
        status._clientDockerID = trace.oob.clientDockerID;
        status._clientSessionID = trace.oob.clientSessionID;
        SwitchServiceClientNotice change(STAvatar, req.avatarID, status._clientDockerID, status._clientSessionID);
        Docker::getRef().broadcastToDockers(change, true);
    }
    else
    {
        resp.retCode = EC_ERROR; 
        LOGE("attach avatar unknown error. trace =" << trace << ", req=" << req << ", status=" << status._status);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
}


void AvatarMgrService::onRealClientClosedNotice(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
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
        SwitchServiceClientNotice change(STAvatar, notice.serviceID, InvalidDockerID, InvalidSessionID);
        Docker::getRef().sendViaServiceID(STAvatar, notice.serviceID, change);
        founder->second->_lastChangeTime = getNowTime();
        _freeList[notice.serviceID] = founder->second;
    }

}



void AvatarMgrService::onGetSceneTokenInfoResp(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}
void AvatarMgrService::onJoinSceneResp(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}
void AvatarMgrService::onJoinSceneNotice(const Tracing & trace, zsummer::proto4z::ReadStream  & rs)
{
    toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}
void AvatarMgrService::onLeaveSceneResp(const Tracing & trace, zsummer::proto4z::ReadStream  & rs)
{
    toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}
