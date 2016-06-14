#include "docker.h"
#include "webService.h"
#include <ProtoWebAgent.h>



WebService::WebService()
{
    slotting<RefreshServiceToMgrNotice>([](Tracing, ReadStream &rs) {});
    slotting<WebAgentToService>(std::bind(&WebService::onWebAgentToService, this, _1, _2)); //不需要shared_from_this
}

WebService::~WebService()
{
    
}

void WebService::onTick()
{
}

void WebService::_checkSafeDestroy()
{
    auto service = Docker::getRef().peekService(ServiceUserMgr, InvalidServiceID);
    if (!service)
    {
        finishUnload();
        return;
    }
    SessionManager::getRef().createTimer(500, std::bind(&WebService::_checkSafeDestroy, this));
}

void WebService::onUnload()
{
    _checkSafeDestroy();
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

void WebService::responseError(DockerID dockerID, SessionID clientID)
{
    WriteHTTP wh;
    wh.addHead("Content-type", "application/json");
    wh.response("404", R"(   {"result":"error", "support apis":"/getonline, /offlinechat?ServiceID=2222&msg=2222"}      )");
    Docker::getRef().packetToClientViaDocker(dockerID, clientID, wh.getStream(), wh.getStreamLen());
}
void WebService::responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body)
{
    WriteHTTP wh;
    wh.addHead("Content-type", "application/json");
    wh.response("200", body);
    Docker::getRef().packetToClientViaDocker(dockerID, clientID, wh.getStream(), wh.getStreamLen());
}
void WebService::onWebAgentToService(Tracing trace, ReadStream &rs)
{
    WebAgentToService notice;
    rs >> notice;

    if (compareStringIgnCase(notice.method, "get") || compareStringIgnCase(notice.method, "post"))
    {
        std::string uri;
        std::vector<std::pair<std::string,std::string>> params;
        bool needUrldecode = false;
        if (compareStringIgnCase(notice.method, "get"))
        {
            uri = notice.methodLine;
        }
        else 
        {
            uri = notice.body;
            auto founder = notice.heads.find("Content-Type");
            if (founder != notice.heads.end())
            {
                if (founder->second.find("urlencoded") != std::string::npos)
                {
                    needUrldecode = true;
                }
            }
        }
        auto pr = splitPairString(uri, "?");
        uri = pr.first;
        auto spts = splitString(pr.second, "&", "");
        for (auto & pm : spts)
        {
            pr = splitPairString(pm, "=");
            if (needUrldecode)
            {
                params.push_back(std::make_pair(urlDecode(pr.first), urlDecode(pr.second)));
            }
            else
            {
                params.push_back(pr);
            }
        }

        if (uri == "/getonline")
        {
            responseSuccess(trace.fromDockerID, notice.webClientID, R"({"online":)" + toString(Docker::getRef().peekService(ServiceUser).size()) + "}");
        }
        else if (uri == "/offlinechat")
        {

        }
        else
        {
            responseError(trace.fromDockerID, notice.webClientID);
        }
    }

    
}



