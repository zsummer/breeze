#include "docker.h"
#include "webService.h"




WebService::WebService()
{
}

WebService::~WebService()
{
    
}

void WebService::onTick()
{
}



void WebService::onUnload()
{
    finishUnload();
}

bool WebService::onLoad()
{
    finishLoad();
    return true;
}

void WebService::onClientChange()
{
    return ;
}




