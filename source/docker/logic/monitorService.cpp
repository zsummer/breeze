#include "docker.h"
#include "monitorService.h"




MonitorService::MonitorService()
{
    slotting<RefreshServiceToMgrNotice>([](Tracing, ReadStream &rs) {});

}

MonitorService::~MonitorService()
{
    
}

void MonitorService::onTick()
{
}


void MonitorService::_checkSafeDestroy()
{
    auto service = Docker::getRef().peekService(ServiceUserMgr, InvalidServiceID);
    if (!service)
    {
        finishUnload();
        return;
    }
    SessionManager::getRef().createTimer(500, std::bind(&MonitorService::_checkSafeDestroy, this));
}
void MonitorService::onUnload()
{
    _checkSafeDestroy();
}

bool MonitorService::onLoad()
{
    finishLoad();
    return true;
}

void MonitorService::onClientChange()
{
    return ;
}




