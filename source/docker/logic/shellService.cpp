#include "docker.h"
#include "shellService.h"




ShellService::ShellService()
{
}

ShellService::~ShellService()
{
    
}

void ShellService::onTick(TimerID tID, ui32 count, ui32 repeat)
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




