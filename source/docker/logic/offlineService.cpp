#include "docker.h"
#include "offlineService.h"



OfflineService::OfflineService()
{
    slotting<UserOffline>(std::bind(&OfflineService::onUserOffline, this, _1, _2));
    slotting<RefreshServiceToMgrNotice>(std::bind(&OfflineService::onRefreshServiceToMgrNotice, this, _1, _2));
}

OfflineService::~OfflineService()
{
    
}

void OfflineService::onTick()
{
}

void OfflineService::_checkSafeDestroy()
{
    auto service = Docker::getRef().peekService(ServiceUserMgr, InvalidServiceID);
    if (!service)
    {
        finishUnload();
        return;
    }
    SessionManager::getRef().createTimer(500, std::bind(&OfflineService::_checkSafeDestroy, this));
}

void OfflineService::onUnload()
{
    _checkSafeDestroy();
}

bool OfflineService::onLoad()
{
    SQLQueryReq req("SELECT max(id) FROM `tb_useroffline`");
    toService(ServiceInfoDBMgr, req, std::bind(&OfflineService::onLoadMaxOfflineID, this, _1));
    return true;
}

void OfflineService::onLoadMaxOfflineID(zsummer::proto4z::ReadStream &rs)
{
    SQLQueryResp resp;
    rs >> resp;
    if (resp.retCode != EC_SUCCESS || resp.result.qc != QEC_SUCCESS)
    {
        Docker::getRef().forceStop();
        return;
    }
    if (resp.result.fields.empty())
    {
        _offlineNextID = 1;
    }
    else
    {
        _offlineNextID = fromString<ui32>(resp.result.fields.front(), 0)+1;
    }
    auto sql = UserOffline().getDBSelectPure() + " where status=0 ";
    _offlines.loadFromDB(shared_from_this(), sql, std::bind(&OfflineService::onModuleLoad,
        std::static_pointer_cast<OfflineService>(shared_from_this()), _1, _2));
}

void OfflineService::onModuleLoad(bool success, const std::string & moduleName)
{
    if (success)
    {
        finishLoad();
    }
    else
    {
        Docker::getRef().forceStop();
    }
}
void OfflineService::onClientChange()
{
    return ;
}
void OfflineService::onUserOffline(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserOffline offline;
    rs >> offline;
    offline.timestamp = getNowTime();
    offline.status = 0;
    offline.id = _offlineNextID++;
    _offlines.insertToDB(offline, std::bind(&OfflineService::onInsert,
        std::static_pointer_cast<OfflineService>(shared_from_this()), _1, _2));
}

void OfflineService::onInsert(bool success, const UserOffline & offline)
{
    if (success)
    {
        _offlines._data.push_back(offline);
    }
    else
    {
        LOGE("insert offline error. ");
    }
}
void OfflineService::onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    RefreshServiceToMgrNotice ref;
    rs >> ref;
    if (ref.status == SS_WORKING && ref.clientSessionID != InvalidSessionID)
    {
        for (auto & offline : _offlines._data)
        {
            if (offline.serviceID == ref.serviceID && offline.status == 0)
            {
                toService(ServiceUser, offline.serviceID, offline.streamBlob.c_str(), offline.streamBlob.length());
                offline.status = 1;
                _offlines.updateToDB(offline);
            }
        }
    }
}

