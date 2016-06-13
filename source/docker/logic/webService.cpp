#include "docker.h"
#include "webService.h"
#include <ProtoWebAgent.h>



WebService::WebService()
{
    slotting<WebAgentToService>(std::bind(&WebService::onWebAgentToService, this, _1, _2)); //不需要shared_from_this
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



void WebService::onWebAgentToService(Tracing trace, ReadStream &rs)
{
    WebAgentToService notice;
    rs >> notice;
    if (compareStringIgnCase(notice.method, "get"))
    {
        WriteHTTP wh;
        wh.addHead("Content-type", "application/json");
        wh.response("200", R"({"online":)" + toString(Docker::getRef().peekService(ServiceUser).size()) + "}");
        Docker::getRef().packetToClientViaDocker(trace._fromDockerID, notice.webClientID, wh.getStream(), wh.getStreamLen());
    }
    
}



