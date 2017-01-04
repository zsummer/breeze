/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
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

#ifndef _MOVE_SYNC_H_
#define _MOVE_SYNC_H_
#include "entity.h"

class Scene;
class MoveSync : public std::enable_shared_from_this<MoveSync>
{
    double _lastDoRVO = 0.0;
    double _lastPrintStatus = 0.0;
    RVO::RVOSimulator *_sim = nullptr;
    std::weak_ptr<Scene> _scene;
public:
    MoveSync();
    ~MoveSync();
    void init(std::weak_ptr<Scene> scene);
    void checkStepRVO(bool preCheck);
    void update();

    ui64 addAgent(EPosition pos);
    void delAgent(ui64 agent);
    bool isValidAgent(ui64 agent);
    bool setAgentPosition(ui64 agent, EPosition pos);
    bool doMove(ui64 eid, MOVE_ACTION action, double speed, ui64 follow, EPosition clt, EPositionArray dsts);
};

using MoveSyncPtr = std::shared_ptr<MoveSync>;



































#endif
