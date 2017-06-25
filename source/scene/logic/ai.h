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

#ifndef _AI_H_
#define _AI_H_
#include "entity.h"

class Scene;
class AI : public std::enable_shared_from_this<AI>
{
    std::weak_ptr<Scene> _scene;



    std::vector<EntityPtr> _march;
    EPosition _marchOrg;
    double _lastMarch = 0;
public:
    AI();
    ~AI();
    void init(std::weak_ptr<Scene> scene);
    void update();


    void rebirthCheck();
};

using AIPtr = std::shared_ptr<AI>;



















































#endif
