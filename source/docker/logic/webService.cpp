#include "docker.h"
#include "webService.h"
#include <ProtoClient.h>


WebService::WebService()
{
    slotting<RefreshServiceToMgrNotice>([](Tracing, ReadStream &rs) {});
    slotting<WebAgentClientRequestAPI>(std::bind(&WebService::onWebAgentClientRequestAPI, this, _1, _2)); //不需要shared_from_this
    slotting<WebServerRequest>(std::bind(&WebService::onWebServerRequest, this, _1, _2)); //不需要shared_from_this
    slotting<WebServerResponse>(std::bind(&WebService::onWebServerResponseTest, this, _1, _2)); //不需要shared_from_this
    slotting<ReloadDBDictFinish>(std::bind(&WebService::onReloadState, this, _1, _2)); //不需要shared_from_this
}

WebService::~WebService()
{
    
}

void WebService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    static time_t lastTick = getNowTime();
    time_t now = getNowTime();
    if (now - lastTick > 10 )
    {
        LOGA("WebService balance:" << Docker::getRef().getWebBalance().getBalanceStatus());
        lastTick = now;
    }
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

void WebService::responseError(DockerID dockerID, SessionID clientID, unsigned int ecode, const std::string & msg)
{
    WriteHTTP wh;
    wh.addHead("Content-type", "application/json");
    wh.response(toString(ecode), msg);
    directToRealClient(dockerID, clientID, wh.getStream(), wh.getStreamLen());
}

void WebService::responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body)
{
    responseSuccess(dockerID, clientID, body, { { "Content-type", "application/json" } });
}

void WebService::responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body, const std::map<std::string, std::string> & heads)
{
    WriteHTTP wh;
    for (const auto & head: heads)
    {
        wh.addHead(head.first, head.second);
    }
    wh.response("200", body);
    directToRealClient(dockerID, clientID, wh.getStream(), wh.getStreamLen());
}

void WebService::onWebServerRequest(Tracing trace, ReadStream &rs)
{
    WebServerRequest request;
    rs >> request;
    request.traceID = trace.routing.traceID;
    request.fromServiceType = trace.routing.fromServiceType;
    request.fromServiceID = trace.routing.fromServiceID;
    Docker::getRef().sendViaDockerID(Docker::getRef().getWebBalance().pickNode(1, 1), request);
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
    responseSuccess(dockerID, clientID, resp.body, resp.heads);
}



void WebService::onWebAgentClientRequestAPI(Tracing trace, ReadStream &rs)
{
    WebAgentClientRequestAPI notice;
    rs >> notice;

    if (compareStringIgnCase(notice.method, "get") || compareStringIgnCase(notice.method, "post"))
    {
        std::string uri;
        _Params params;
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
        auto pr = splitStringTuple<std::string,std::string>(uri, '?');
        uri = std::get<0>(pr);
        params = splitStringTupleDict<0, std::string, std::string>(std::get<1>(pr), '&', '=');


        if (compareStringIgnCase(uri, "/getonline"))
        {
            getonline(trace.oob.clientDockerID, trace.oob.clientSessionID, params);
        }
        else if (compareStringIgnCase(uri, "/reload"))

        {
            reload(trace.oob.clientDockerID, trace.oob.clientSessionID, params);
        }
        else if (compareStringIgnCase(uri, "/KickClients"))
        {
            KickClients(trace.oob.clientDockerID, trace.oob.clientSessionID, params);
        }
        else if (compareStringIgnCase(uri, "/offlinechat"))
        {
            offlinechat(trace.oob.clientDockerID, trace.oob.clientSessionID, params);
        }
        else if (compareStringIgnCase(uri, "/test"))
        {
            WebServerRequest request;
            request.ip = "42.121.252.58";
            request.port = 80;
            request.isGet = true;
            request.host = "www.cnblogs.com";
            request.uri = "/";
            toService(STWebAgent,request);
            toService(STWebAgent, request, std::bind(&WebService::onWebServerResponseTestCallback, std::static_pointer_cast<WebService>(shared_from_this()),
                _1, trace.oob.clientDockerID, trace.oob.clientSessionID));
            
        }
        else
        {
            responseError(trace.oob.clientDockerID, trace.oob.clientSessionID, 404, R"( {"result":"error", "msg":"unsupport uri"} )");
        }
    }

    
}
void WebService::getonline(DockerID dockerID, SessionID clientID, const _Params &params)
{
    responseSuccess(dockerID, clientID, R"({"result":"success","online":)" + toString(Docker::getRef().peekService(STAvatar).size()) + "}");
}


void WebService::onReloadState(Tracing trace, ReadStream &rs)
{
    ReloadDBDictFinish f;
    rs >> f;
    auto &val = _reloadState[f.dockerID];
    std::get<0>(val) = f.activeTime;
    std::get<1>(val) = f.used;
}

void WebService::KickClients(DockerID dockerID, SessionID clientID, const _Params &params)
{
    KickClientsNotice notice;

    for (const auto & kv : params)
    {
        if (compareStringIgnCase(kv.first, "isAll"))
        {
            notice.isAll = fromString<ui16>(std::get<1>(kv.second));
        }
        else if (compareStringIgnCase(kv.first, "avatars"))
        {
            notice.avatars = splitStringSimpleArray<ui64>(std::get<1>(kv.second), ',');

        }
        else if (compareStringIgnCase(kv.first, "avatars"))
        {
            notice.accounts = splitStringSimpleArray<std::string>(std::get<1>(kv.second), ',');
        }
        else if (compareStringIgnCase(kv.first, "forbidDuration"))
        {
            notice.forbidDuration = fromString<ui64>(std::get<1>(kv.second));
        }
    }

    if (notice.isAll == 0 && notice.avatars.empty())
    {
        responseError(dockerID, clientID, 404, R"({"result":"error","msg":"KickClients no avatars to kick. "})");
        return;
    }

    responseSuccess(dockerID, clientID, R"({"result":"success","kicked":)" + toString(Docker::getRef().peekService(STAvatar).size()) + "}");
    toService(STAvatarMgr, notice);
}

void WebService::reload(DockerID dockerID, SessionID clientID, const _Params &params)
{
    double now = (double)getNowTime();
    auto makeState = [this, now]()
    {
        std::string ret;
        ret += "\t";
        ret += R"("current":)";
        ret += formatDateTimeString((time_t)now) + ",\r\n";

        ret += "\t";
        ret += R"("reload":)" + formatDateTimeString((time_t)_lastReloadTick) + ",\r\n";
        ret += "\t";
        ret += R"("state":)";
        ret += "\t"; 
        ret += "[\r\n";
        for (auto &kv : _reloadState)
        {
            ret += "\t\t{";
            ret += R"("id":)";
            ret += toString(kv.first);
            ret += R"(", update":)";
            ret += formatDateTimeString((time_t)std::get<0>(kv.second));
            ret += R"(", used":)";
            ret += toString(std::get<1>(kv.second));
            ret += "},\r\n";
        }
        ret += "\t";
        ret += "]";
        return ret;
    };

    if (now - _lastReloadTick > 30)
    {
        _lastReloadTick = now;
        _reloadState.clear();

        const auto & dockers = ServerConfig::getRef().getDockerConfigs();
        for (auto d : dockers)
        {
            _reloadState[d._dockerID] = std::make_tuple(0, 0);
        }
        Docker::getRef().broadcastToDockers(ReloadDBDictNotice(), true);
        responseSuccess(dockerID, clientID, R"({"result":"success",)"  "\r\n"  R"( "msg": {)" + makeState() +"}\r\n}\r\n");
    }
    else
    {
        responseSuccess(dockerID, clientID, R"({"result":"state",)"  "\r\n"  R"( "msg": {)" + makeState() + "}\r\n}\r\n");
    }

}




void WebService::offlinechat(DockerID dockerID, SessionID clientID, const _Params &params)
{
    ChatReq req;
    req.channelID = CC_PRIVATE;
    for (auto & pm : params)
    {
        if (pm.first == "serviceID")
        {
            req.targetID = fromString<ui64>(std::get<1>(pm.second));
        }
        if (pm.first == "msg")
        {
            req.msg = std::get<1>(pm.second);
        }
    }
    if (req.targetID != InvalidServiceID)
    {
        AvatarOffline offline;
        offline.avatarID = req.targetID;
        offline.status = 0;
        offline.timestamp = getNowTime();
        WriteStream ws(ChatReq::getProtoID());
        ws << req;
        offline.streamBlob.assign(ws.getStream(), ws.getStreamLen());
        toService(STOfflineMgr, offline);
        responseSuccess(dockerID, clientID, R"({"result":"success"})");

    }
    else
    {
        responseError(dockerID, clientID, 404, R"({"result":"error"})");
    }
}

