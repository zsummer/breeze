#include "docker.h"
#include "space.h"



SpaceService::SpaceService()
{
    slotting<UserOffline>(std::bind(&SpaceService::onUserOffline, this, _1, _2));
    slotting<RefreshServiceToMgrNotice>(std::bind(&SpaceService::onRefreshServiceToMgrNotice, this, _1, _2));
}

SpaceService::~SpaceService()
{
    
}

void SpaceService::onTick()
{
}



void SpaceService::onUnload()
{
    finishUnload();
}

bool SpaceService::onLoad()
{
    DBQueryReq req("SELECT max(id) FROM `tb_UserOffline`");
    toService(STInfoDBMgr, req, std::bind(&SpaceService::onLoadMaxOfflineID, this, _1));
    return true;
}

void SpaceService::onLoadMaxOfflineID(zsummer::proto4z::ReadStream &rs)
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
    _offlines.loadFromDB(shared_from_this(), sql, std::bind(&SpaceService::onModuleLoad,
        std::static_pointer_cast<SpaceService>(shared_from_this()), _1, _2));
}

void SpaceService::onModuleLoad(bool success, const std::string & moduleName)
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
void SpaceService::onClientChange()
{
    return ;
}
void SpaceService::onUserOffline(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    UserOffline offline;
    rs >> offline;
    offline.timestamp = getNowTime();
    offline.status = 0;
    offline.id = _offlineNextID++;
    _offlines.insertToDB(offline, std::bind(&SpaceService::onInsert,
        std::static_pointer_cast<SpaceService>(shared_from_this()), _1, _2));
}

void SpaceService::onInsert(bool success, const UserOffline & offline)
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
void SpaceService::onRefreshServiceToMgrNotice(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
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

