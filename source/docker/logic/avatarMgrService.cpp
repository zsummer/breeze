#include "docker.h"
#include "avatarMgrService.h"
#include <ProtoCommon.h>
#include <ProtoClient.h>
#include <LogCommon.h>

AvatarMgrService::AvatarMgrService()
{
    slotting<RefreshServiceToMgrNotice>(std::bind(&AvatarMgrService::onRefreshServiceToMgrNotice, this, _1, _2));
    slotting<RealClientClosedNotice>(std::bind(&AvatarMgrService::onRealClientClosedNotice, this, _1, _2));
    slotting<ClientAuthReq>(std::bind(&AvatarMgrService::onClientAuthReq, this, _1, _2));
    slotting<CreateAvatarReq>(std::bind(&AvatarMgrService::onCreateAvatarReq, this, _1, _2));
    slotting<AttachAvatarReq>(std::bind(&AvatarMgrService::onAttachAvatarReq, this, _1, _2));
    slotting<KickClientsNotice>(std::bind(&AvatarMgrService::onKickClientsNotice, this, _1, _2));


}

AvatarMgrService::~AvatarMgrService()
{
    
}

void AvatarMgrService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    checkOfflineList();
    systemAutoChat();
}

void AvatarMgrService::systemAutoChat()
{
    if (getFloatSteadyNowTime() - _lastSystemChat < 30.0)
    {
        return;
    }
    _lastSystemChat = getFloatSteadyNowTime();

    auto avatars = Docker::getRef().peekService(STAvatar);
    ChatResp resp;
    resp.channelID = CC_SYSTEM;
    resp.chatTime = getNowTime();
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
void AvatarMgrService::checkOfflineList()
{
    
    if (getFloatSteadyNowTime() - _lastCheckOfflineList < 10.0)
    {
        return;
    }
    _lastCheckOfflineList = getFloatSteadyNowTime();


    LOGI("AvatarMgrService::onTick balance=" << Docker::getRef().getAvatarBalance().getBalanceStatus());


    for (auto iter = _offlineAvatars.begin(); iter != _offlineAvatars.end();)
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
            iter = _offlineAvatars.erase(iter);
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
    std::string sql = replaceString(AvatarPreview().getDBSelectPure(), "tb_AvatarPreview", "tb_AvatarBaseInfo", false);
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
            << ", curLimit=" << curLimit << ",  inited user=" << _avatarStatusByID.size() <<  ", sql=" << sql);
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.qc != QEC_SUCCESS )
    {
        LOGE("onLoadAvatarPreviewsFromDB error. errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
            << ", sql msg=" << resp.result.errMsg
            << ", curLimit=" << curLimit << ",  inited user=" << _avatarStatusByID.size() << ", sql=" << sql);
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.fields.empty())
    {
        LOGA("onLoadAvatarPreviewsFromDB success. errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
            << ", sql msg=" << resp.result.errMsg
            << ", curLimit=" << curLimit << ",  inited user=" << _avatarStatusByID.size() << ", sql=" << sql);

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

        if (_avatarStatusByID.find(up.avatarID) != _avatarStatusByID.end()
            || _avatarStatusByName.find(up.avatarName) != _avatarStatusByName.end())
        {
            LOGA("onLoadAvatarPreviewsFromDB . errCode=" << resp.retCode << ", resp.result.qc=" << resp.result.qc
                << ", sql msg=" << resp.result.errMsg
                << ", curLimit=" << curLimit << ",  inited user=" << _avatarStatusByID.size() << ", sql=" << sql);
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
        usp = getAvatarStatus(pre.avatarID);
        if (!usp)
        {
            usp = std::make_shared<AvatarStatus>();
            usp->_status = SS_NONE;
            _avatarStatusByID[pre.avatarID] = usp;
            _avatarStatusByName[pre.avatarName] = usp;
        }
        usp->_preview = pre;
    }
    if (true)
    {
        auto acc = getAccountStatus(pre.account);
        if (!acc)
        {
            acc = std::make_shared<AccountStatus>();
            _accountStatus[pre.account] = acc;
        }
        acc->_players[pre.avatarID] = usp;
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
            auto founder = _avatarStatusByID.find(si.serviceID);
            if (founder == _avatarStatusByID.end())
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
    if (req.account.empty() || req.token != req.token || isForbid(req.account))
    {
        resp.account = req.account;
        resp.token = req.token;
        resp.previews.clear();
        resp.retCode = EC_PERMISSION_DENIED;
        backToService(trace, resp);
        return;
    }

    std::string sql = replaceString(AvatarPreview().getDBSelectPure(), "tb_AvatarPreview", "tb_AvatarBaseInfo", false);
    sql += " where account=?;";

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
        auto asp = getAccountStatus(req.account);
        if (!asp)
        {
            asp = std::make_shared<AccountStatus>();
            _accountStatus[req.account] = asp;
        }
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

    auto asp = getAccountStatus(req.accountName);
    if (!asp)
    {
        resp.retCode = EC_AVATAR_NOT_FOUND;
        LOGE("onCreateAvatarReq error. EC_AVATAR_NOT_FOUND trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    if (asp->_players.size() > 4 )
    {
        resp.retCode = EC_AVATAR_COUNT_LIMITE;
        LOGE("onCreateAvatarReq error. EC_AVATAR_COUNT_LIMITE trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    if ( getNowTime() - asp->_lastCreateTime < 60)
    {
        resp.retCode = EC_AVATAR_FREQ_LIMITE;
        LOGE("onCreateAvatarReq error. EC_AVATAR_FREQ_LIMITE trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }

    if (_avatarStatusByName.find(req.avatarName) != _avatarStatusByName.end())
    {
        resp.retCode = EC_AVATAR_NAME_CONFLICT;
        LOGE("onCreateAvatarReq error. EC_AVATAR_NAME_CONFLICT trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
        return;
    }
    asp->_lastCreateTime = getNowTime();
    AvatarBaseInfo userBaseInfo;
    userBaseInfo.account = req.accountName;
    userBaseInfo.avatarID = ++_nextAvatarID;
    userBaseInfo.avatarName = req.avatarName;
    userBaseInfo.level = 1;
    userBaseInfo.iconID = 0;
    userBaseInfo.createTime = getNowTime();

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
        AvatarPreview up(ubi.avatarID, ubi.avatarName, ubi.account, ubi.iconID, ubi.modeID, ubi.level);
        updateAvatarPreview(up);
        auto asp = getAccountStatus(ubi.account);
        for (const auto & kv : asp->_players)
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
    resp.retCode = EC_SUCCESS;
    if (isForbid(req.avatarID))
    {
        resp.retCode = EC_PERMISSION_DENIED;
        LOGE("attach avatar error. trace =" << trace << ", req=" << req);
        directToRealClient(trace.oob.clientDockerID, trace.oob.clientSessionID, resp);
    }

    auto founder = _avatarStatusByID.find(req.avatarID);
    if (founder == _avatarStatusByID.end() || founder->second->_preview.account != req.accountName)
    {
        resp.retCode = EC_TARGET_NOT_EXIST;
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
    _offlineAvatars.erase(req.avatarID);
    if (status._status == SS_NONE || status._status == SS_DESTROY)
    {
        DockerID dockerID = Docker::getRef().getAvatarBalance().pickNode(1,1);
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
        LoadService notice(STAvatar, req.avatarID, status._preview.avatarName, status._clientDockerID, status._clientSessionID);
        Docker::getRef().sendViaDockerID(dockerID, notice);

        if (true)
        {
            LogLogin ll;
            ll.avatarID = req.avatarID;
            auto ptr = getAvatarStatus(req.avatarID);
            if (ptr)
            {
                ll.avatarName = ptr->_preview.avatarName;
            }
            ll.logTime = getNowTime();
            ll.id = 0;
            for (auto & kv : req.di)
            {
                ll.deviceInfo += kv.first;
                ll.deviceInfo += ":";
                ll.deviceInfo += kv.second;
                ll.deviceInfo += ",  ";
            }

            DBQueryReq req(ll.getDBInsert());
            toService(STLogDBMgr, req, NULL);
        }


    }
    else if(status._status == SS_WORKING)
    {
        status._clientDockerID = trace.oob.clientDockerID;
        status._clientSessionID = trace.oob.clientSessionID;
        SwitchServiceClientNotice change(STAvatar, req.avatarID, status._clientDockerID, status._clientSessionID);
        Docker::getRef().broadcastToDockers(change, true);

        if (true)
        {
            LogLogin ll;
            ll.avatarID = req.avatarID;
            auto ptr = getAvatarStatus(req.avatarID);
            if (ptr)
            {
                ll.avatarName = ptr->_preview.avatarName;
            }
            ll.logTime = getNowTime();
            ll.id = 0;
            for (auto & kv : req.di)
            {
                ll.deviceInfo += kv.first;
                ll.deviceInfo += ":";
                ll.deviceInfo += kv.second;
                ll.deviceInfo += ",  ";
            }

            DBQueryReq req(ll.getDBInsert());
            toService(STLogDBMgr, req, NULL);
        }

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
    auto founder = _avatarStatusByID.find(notice.serviceID);
    if (founder == _avatarStatusByID.end())
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
        _offlineAvatars[notice.serviceID] = founder->second;
    }
}

void AvatarMgrService::onKickClientsNotice(const Tracing & trace, zsummer::proto4z::ReadStream & rs)
{
    KickClientsNotice notice;
    time_t endTime = getNowTime() + notice.forbidDuration;
    rs >> notice;
    if (notice.isAll)
    {
        _tmpForbidAllClientTime = endTime;
        Docker::getRef().broadcastToDockers(notice, true);
        return;
    }
    else
    {
        std::map<ServiceID, AvatarStatusPtr> tmp;



        for (auto id : notice.avatars)
        {
            _tmpForbidAvatar[id] = endTime;
            auto asp = getAvatarStatus(id);
            if (asp && asp->_clientSessionID != InvalidSessionID)
            {
                tmp[id] = asp;
            }
        }

        for (const auto &account : notice.accounts)
        {
            auto acsp = getAccountStatus(account);
            if (acsp && acsp->_players.size() > 0)
            {
                _tmpForbidAccount[account] = endTime;
                for (auto kv : acsp->_players)
                {
                    notice.avatars.push_back(kv.first);
                    if (kv.second && kv.second->_clientSessionID != InvalidSessionID)
                    {
                        tmp[kv.first] = kv.second;
                    }
                }
            }
        }

        notice.accounts.clear();
        toDocker(STWorldMgr, notice);

        for (auto kv : tmp)
        {
            SwitchServiceClientNotice change(STAvatar, kv.first, InvalidDockerID, InvalidSessionID);
            Docker::getRef().sendViaServiceID(STAvatar, kv.first, change);
            kv.second->_lastChangeTime = getNowTime();
            _offlineAvatars[kv.first] = kv.second;
        }

    }
    
}


bool AvatarMgrService::isForbid(std::string account)
{
    time_t now = getNowTime();
    if (now < _tmpForbidAllClientTime)
    {
        return true;
    }
    auto founder = _tmpForbidAccount.find(account);
    if (founder == _tmpForbidAccount.end() || time(NULL) > founder->second)
    {
        return false;
    }
    return true;
}
bool AvatarMgrService::isForbid(ServiceID avatarID)
{
    time_t now = getNowTime();
    if (now < _tmpForbidAllClientTime)
    {
        return true;
    }
    auto founder = _tmpForbidAvatar.find(avatarID);
    if (founder == _tmpForbidAvatar.end() || time(NULL) > founder->second)
    {
        return false;
    }
    return true;
}

AvatarStatusPtr AvatarMgrService::getAvatarStatus(ServiceID avatarID)
{
    auto founder = _avatarStatusByID.find(avatarID);
    if (founder != _avatarStatusByID.end())
    {
        return founder->second;
    }
    return nullptr;
}

AvatarStatusPtr AvatarMgrService::getAvatarStatus(std::string avatarName)
{
    auto founder = _avatarStatusByName.find(avatarName);
    if (founder != _avatarStatusByName.end())
    {
        return founder->second;
    }
    return nullptr;
}

AccountStatusPtr AvatarMgrService::getAccountStatus(std::string account)
{
    auto founder = _accountStatus.find(account);
    if (founder != _accountStatus.end())
    {
        return founder->second;
    }
    return nullptr;
}






