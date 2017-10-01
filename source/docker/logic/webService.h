
/*
* breeze License
* Copyright (C) 2016 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/





#ifndef _WEB_SERVICE_H_
#define _WEB_SERVICE_H_
#include <common.h>
#include "service.h"

/*
WebService
    通过docker的支持, 该服务提供对外的web访问接口, 包括连入和连出.
*/


class WebService : public Service
{
public:
    using _Params = std::map<std::string, std::tuple<std::string, std::string>>;
    WebService();
    ~WebService();
    bool onLoad() override final;
    void onClientChange() override final;
    void onUnload() override final;
    void onTick(TimerID tID, ui32 count, ui32 repeat) override final;
private:
    void onWebAgentClientRequestAPI(Tracing trace, ReadStream &rs);
    void getonline(DockerID dockerID, SessionID clientID, const _Params &params);
    void offlinechat(DockerID dockerID, SessionID clientID, const _Params &params);


    std::map<DockerID, std::tuple<double, double>> _reloadState;
    double _lastReloadTick = 0;
    void reload(DockerID dockerID, SessionID clientID, const _Params &params);
    void onReloadState(Tracing trace, ReadStream &rs);


    void KickClients(DockerID dockerID, SessionID clientID, const _Params &params);

private:
    void onWebServerRequest(Tracing trace, ReadStream &rs);
    void onWebServerResponseTest(Tracing trace, ReadStream &rs);
    void onWebServerResponseTestCallback(ReadStream &rs, DockerID dockerID, SessionID clientID);
private:
    void responseError(DockerID dockerID, SessionID clientID, unsigned int ecode, const std::string & msg);
    void responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body);
    void responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body, const std::map<std::string, std::string> &  heads);
private:
};

































#endif
