#include "docker.h"
#include "shellService.h"




ShellService::ShellService()
{
}

ShellService::~ShellService()
{
    
}

void ShellService::onTick()
{
}



void ShellService::onUnload()
{
    finishUnload();
}

bool ShellService::onLoad()
{
    finishLoad();
    return true;
}

void ShellService::onClientChange()
{
    return ;
}




