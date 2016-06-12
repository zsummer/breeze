#include "docker.h"
#include "offlineService.h"




OfflineService::OfflineService()
{
}

OfflineService::~OfflineService()
{
    
}

void OfflineService::onTick()
{
}



void OfflineService::onUnload()
{
    finishUnload();
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




