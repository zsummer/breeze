#include "docker.h"
#include "shellService.h"
#include <ProtoDBService.h>



ShellService::ShellService()
{
}

ShellService::~ShellService()
{
    
}

void ShellService::onTick()
{
    LOGE("ShellService::onTick");
}



void ShellService::onUninit()
{
    finishUninit();
}

bool ShellService::onInit()
{
    finishInit();
    return true;
}

void ShellService::onClientChange()
{
    return ;
}




