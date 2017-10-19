/*
* breeze License
* Copyright (C) 2015 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
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

#ifndef _SCRIPT_H_
#define _SCRIPT_H_
#include "entity.h"




class Scene;
class Script : public std::enable_shared_from_this<Script>
{
    std::weak_ptr<Scene> _scene;
    lua_State * _luaState = nullptr;
public:
    Script();
    ~Script();
public:
    void init(std::weak_ptr<Scene> scene);
    void update();
    void protoSync(const std::string & protoName, const char * data, unsigned int len);
    template<class Proto>
    void protoSync(const Proto & proto);
};

using ScriptPtr = std::shared_ptr<Script>;






















template<class Proto>
void Script::protoSync(const Proto & proto)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        protoSync(Proto::getProtoName(), ws.getStream(), ws.getStreamLen());
    }
    catch (const std::exception & e)
    {
        LOGE("Scene::protoSync protoid=" << Proto::getProtoID() << ", e=" << e.what());
        return;
    }
}















































#endif
