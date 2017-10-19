#include "docker.h"
#include "offlineService.h"



OfflineService::OfflineService()
{
    slotting<AvatarOffline>(std::bind(&OfflineService::onAvatarOffline, this, _1, _2));
    slotting<RefreshServiceToMgrNotice>(std::bind(&OfflineService::onRefreshServiceToMgrNotice, this, _1, _2));
}

OfflineService::~OfflineService()
{
    
}

void OfflineService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
}



void OfflineService::onUnload()
{
    finishUnload();
}

bool OfflineService::onLoad()
{
    DBQueryReq req("SELECT max(id) FROM `tb_AvatarOffline`");
    toService(STInfoDBMgr, req, std::bind(&OfflineService::onLoadMaxOfflineID, this, _1));
    return true;
}

void OfflineService::onLoadMaxOfflineID(zsummer::proto4z::ReadStream &rs)
{
    DBQueryResp resp;
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
        _offlineNextID = fromString<ui64>(resp.result.fields.front())+1;
    }
    if (_offlineNextID < ServerConfig::getRef().getMinServiceID())
    {
        _offlineNextID = ServerConfig::getRef().getMinServiceID() + 1;
    }
    auto sql = AvatarOffline().getDBSelectPure() + " where status=0 ";
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
void OfflineService::onAvatarOffline(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    AvatarOffline offline;
    rs >> offline;
    offline.timestamp = getNowTime();
    offline.status = 0;
    offline.id = _offlineNextID++;
    _offlines.insertToDB(offline, std::bind(&OfflineService::onInsert,
        std::static_pointer_cast<OfflineService>(shared_from_this()), _1, _2));
}

void OfflineService::onInsert(bool success, const AvatarOffline & offline)
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
    RefreshServiceToMgrNotice notice;
    rs >> notice;
    for (const auto & si : notice.shellServiceInfos)
    {
        if (si.status == SS_WORKING && si.clientSessionID != InvalidSessionID)
        {
            for (auto iter = _offlines._data.begin(); iter != _offlines._data.end();)
            {
                auto offline = *iter;
                if (offline.avatarID == si.serviceID && offline.status == 0)
                {
                    toService(STAvatar, offline.avatarID, offline.streamBlob.c_str(), (unsigned int)offline.streamBlob.length());
                    offline.status = 1;
                    _offlines.updateToDB(offline);
                    iter = _offlines._data.erase(iter);
                    continue;
                }
                iter++;
            }
        }
    }
}

