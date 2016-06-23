#include "docker.h"
#include "spaceMgr.h"



SpaceMgrService::SpaceMgrService()
{
    slotting<UserOffline>(std::bind(&SpaceMgrService::onUserOffline, this, _1, _2));
    slotting<RefreshServiceToMgrNotice>(std::bind(&SpaceMgrService::onRefreshServiceToMgrNotice, this, _1, _2));
}

SpaceMgrService::~SpaceMgrService()
{
    
}

void SpaceMgrService::onTick()
{
}



void SpaceMgrService::onUnload()
{
    finishUnload();
}

bool SpaceMgrService::onLoad()
{
    DBQueryReq req("SELECT max(id) FROM `tb_UserOffline`");
    toService(STInfoDBMgr, req, std::bind(&SpaceMgrService::onLoadMaxOfflineID, this, _1));
    return true;
}

void SpaceMgrService::onLoadMaxOfflineID(zsummer::proto4z::ReadStream &rs)
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
        _offlineNextID = fromString<ui64>(resp.result.fields.front(), 0)+1;
    }
    if (_offlineNextID < ServerConfig::getRef().getMinServiceID())
    {
        _offlineNextID = ServerConfig::getRef().getMinServiceID() + 1;
    }
    auto sql = UserOffline().getDBSelectPure() + " where status=0 ";
    _offlines.loadFromDB(shared_from_this(), sql, std::bind(&SpaceMgrService::onModuleLoad,
        std::static_pointer_cast<SpaceMgrService>(shared_from_this()), _1, _2));
}

void SpaceMgrService::onModuleLoad(bool success, const std::string & moduleName)
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
void SpaceMgrService::onClientChange()
{
    return ;
}
void SpaceMgrService::onUserOffline(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserOffline offline;
    rs >> offline;
    offline.timestamp = getNowTime();
    offline.status = 0;
    offline.id = _offlineNextID++;
    _offlines.insertToDB(offline, std::bind(&SpaceMgrService::onInsert,
        std::static_pointer_cast<SpaceMgrService>(shared_from_this()), _1, _2));
}

void SpaceMgrService::onInsert(bool success, const UserOffline & offline)
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
void SpaceMgrService::onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
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
                if (offline.serviceID == si.serviceID && offline.status == 0)
                {
                    toService(STUser, offline.serviceID, offline.streamBlob.c_str(), (unsigned int)offline.streamBlob.length());
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

