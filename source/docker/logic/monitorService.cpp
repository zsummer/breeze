#include "docker.h"
#include "monitorService.h"




MonitorService::MonitorService()
{
}

MonitorService::~MonitorService()
{
    
}

void MonitorService::onTick()
{
}



void MonitorService::onUnload()
{
    finishUnload();
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




