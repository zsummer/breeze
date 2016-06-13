#include "docker.h"
#include "offlineService.h"




OfflineService::OfflineService()
{
    slotting<RefreshServiceToMgrNotice>([](Tracing, ReadStream &rs) {});

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
    finishLoad();
    return true;
}

void OfflineService::onClientChange()
{
    return ;
}




