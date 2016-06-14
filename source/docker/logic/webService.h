
/*
* breeze License
* Copyright (C) 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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




class WebService : public Service
{
public:
    WebService();
    ~WebService();
    bool onLoad() override final;
    void onClientChange() override final;
    void onUnload() override final;
    void onTick() override final;
private:
    void _checkSafeDestroy();
private:
    void onWebAgentClientRequestAPI(Tracing trace, ReadStream &rs);
    void getonline(DockerID dockerID, SessionID clientID, const std::vector<std::pair<std::string, std::string>> &params);
    void offlinechat(DockerID dockerID, SessionID clientID, const std::vector<std::pair<std::string, std::string>> &params);

private:
    void onWebServerRequest(Tracing trace, ReadStream &rs);
    void onWebServerResponseTest(Tracing trace, ReadStream &rs);
    void onWebServerResponseTestCallback(ReadStream &rs, DockerID dockerID, SessionID clientID);
private:
    void responseError(DockerID dockerID, SessionID clientID);
    void responseSuccess(DockerID dockerID, SessionID clientID, const std::string & body);
private:
    Balance _balance;
};

































#endif
