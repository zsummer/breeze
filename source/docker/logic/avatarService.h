
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





#ifndef _AVATAR_SERVICE_H_
#define _AVATAR_SERVICE_H_
#include <common.h>
#include "service.h"
#include "module.h"
#include "docker.h"




class AvatarService : public Service
{
public:
    AvatarService();
    ~AvatarService();
public:
    bool onLoad() override final;
    void onUnload() override final;
    void onClientChange() override final;
    void onTick(TimerID tID, ui32 count, ui32 repeat) override final; //只有client在线时候才会被调用, 间隔为session pulse的间隔. 精度为分钟.  


public:
	void refreshProp(const std::string &prop, double val, bool overwrite = true);
	double getProp(const std::string &prop);
	inline const AvatarPropMap& getProps() { return _props; };

private:
    void onModuleLoad(bool success, const std::string & moduleName);
    void onModuleUnload(bool success, const std::string & moduleName);
private:
    void onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
	void onPingPongReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
	void onChangeIconIDReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
	void onChangeModeIDReq(const Tracing & trace, zsummer::proto4z::ReadStream &);

    void onGetSceneAvatarStatusReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onApplyForSceneReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
    void onCancelSceneReq(const Tracing & trace, zsummer::proto4z::ReadStream &);



private:
    int _curLoadModuleCount = 0;
    int _curUnloadModuleCount = 0;
    int _totalModuleCount = 1;
    ModuleData<AvatarBaseInfo> _baseInfo;
	AvatarPropMap _props;
private:
    double _lastChatTime = getFloatNowTime();
};



































#endif
