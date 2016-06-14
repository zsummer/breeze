#include "docker.h"
#include "webService.h"
#include <ProtoWebAgent.h>
#include <ProtoUser.h>
#include <ProtoOffline.h>


WebService::WebService()
{
    slotting<RefreshServiceToMgrNotice>([](Tracing, ReadStream &rs) {});
    slotting<WebAgentClientRequestAPI>(std::bind(&WebService::onWebAgentClientRequestAPI, this, _1, _2)); //不需要shared_from_this
    slotting<WebServerRequest>(std::bind(&WebService::onWebServerRequest, this, _1, _2)); //不需要shared_from_this
    slotting<WebServerResponse>(std::bind(&WebService::onWebServerResponseTest, this, _1, _2)); //不需要shared_from_this
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
    for (auto config : ServerConfig::getRef().getDockerConfig())
    {
        if (!config._webIP.empty() && config._webPort != 0)
        {
            _balance.enableNode(config._dockerID);
        }
    }
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
    wh.response("404", R"(   {"result":"error", "support apis":"/getonline, /offlinechat?serviceID=2222&msg=2222"}      )");
    Docker::getRef().packetToClientViaDocker(dockerID, clientID, wh.getStream(), wh.getStreamLen());
}
void WebService::responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body)
{
    WriteHTTP wh;
    wh.addHead("Content-type", "application/json");
    wh.response("200", body);
    Docker::getRef().packetToClientViaDocker(dockerID, clientID, wh.getStream(), wh.getStreamLen());
}


void WebService::onWebAgentClientRequestAPI(Tracing trace, ReadStream &rs)
{
    WebAgentClientRequestAPI notice;
    rs >> notice;

    if (compareStringIgnCase(notice.method, "get") || compareStringIgnCase(notice.method, "post"))
    {
        std::string uri;
        std::vector<std::pair<std::string,std::string>> params;
        if (compareStringIgnCase(notice.method, "get"))
        {
            uri = urlDecode(notice.methodLine);
        }
        else 
        {
            uri = notice.body;
            auto founder = notice.heads.find("Content-Type");
            if (founder == notice.heads.end() || founder->second.find("urlencoded") == std::string::npos)
            {
                uri = urlDecode(notice.body);;
            }
        }
        auto pr = splitPairString(uri, "?");
        uri = pr.first;
        auto spts = splitString(pr.second, "&", "");
        for (auto & pm : spts)
        {
            pr = splitPairString(pm, "=");
            params.push_back(pr);
        }

        if (uri == "/getonline")
        {
            getonline(trace.fromDockerID, notice.webClientID, params);
        }
        else if (uri == "/offlinechat")
        {
            offlinechat(trace.fromDockerID, notice.webClientID, params);
        }
        else if (uri == "/test")
        {
            WebServerRequest request;
            request.ip = "42.121.252.58";
            request.port = 80;
            request.isGet = true;
            request.uri = "www.cnblogs.com";
            toService(ServiceWebAgent, request);
            toService(ServiceWebAgent, request, std::bind(&WebService::onWebServerResponseTestCallback, std::static_pointer_cast<WebService>(shared_from_this()),
                _1, trace.fromDockerID, notice.webClientID));
            
        }
        else
        {
            responseError(trace.fromDockerID, notice.webClientID);
        }
    }

    
}
void WebService::getonline(DockerID dockerID, SessionID clientID, const std::vector<std::pair<std::string, std::string>> &params)
{
    responseSuccess(dockerID, clientID, R"({"result":"success","online":)" + toString(Docker::getRef().peekService(ServiceUser).size()) + "}");
}

void WebService::offlinechat(DockerID dockerID, SessionID clientID, const std::vector<std::pair<std::string, std::string>> &params)
{
    UserChatReq req;
    for (auto & pm : params)
    {
        if (pm.first == "serviceID")
        {
            req.toServiceID = fromString<ui64>(pm.second, InvalidServiceID);
        }
        if (pm.first == "msg")
        {
            req.msg = pm.second;
        }
    }
    if (req.toServiceID != InvalidServiceID)
    {
        UserOffline offline;
        offline.serviceID = req.toServiceID;
        offline.status = 0;
        offline.timestamp = getNowTime();
        WriteStream ws(UserChatReq::getProtoID());
        ws << req;
        offline.streamBlob.assign(ws.getStream(), ws.getStreamLen());
        toService(ServiceOfflineMgr, offline);
        responseSuccess(dockerID, clientID, R"({"result":"success"})");

    }
    else
    {
        responseError(dockerID, clientID);
    }
}

void WebService::onWebServerRequest(Tracing trace, ReadStream &rs)
{
    WebServerRequest request;
    rs >> request;
    request.traceID = trace.traceID;
    request.fromServiceType = trace.fromServiceType;
    request.fromServiceID = trace.fromServiceID;
    Docker::getRef().sendToDocker(_balance.selectAuto(), request);
}

void WebService::onWebServerResponseTest(Tracing trace, ReadStream &rs)
{
    WebServerResponse resp;
    rs >> resp;
    LOGI("onWebServerResponse test " << resp.body);
}
void WebService::onWebServerResponseTestCallback(ReadStream &rs, DockerID dockerID, SessionID clientID)
{
    WebServerResponse resp;
    rs >> resp;
    responseSuccess(dockerID, clientID, resp.body);
}