#include "move.h"
#include "scene.h"
#include "sceneMgr.h"

MoveSync::MoveSync()
{

}
MoveSync::~MoveSync()
{
    if (_sim)
    {
        delete _sim;
        _sim = nullptr;
    }
}
void MoveSync::init(std::weak_ptr<Scene> scene)
{
    _scene = scene;
    _sim = new RVO::RVOSimulator();
    _sim->setTimeStep(SceneFrameInterval);
    _sim->setAgentDefaults(15.0, 1000, 70.0, 70.0, 2.0, 7.0);
    if (false)
    {
        std::vector<RVO::Vector2> vertices;
        vertices.push_back(RVO::Vector2(-7.0, -20.0));
        vertices.push_back(RVO::Vector2(7.0, -20.0));
        vertices.push_back(RVO::Vector2(7.0, 20.0));
        vertices.push_back(RVO::Vector2(-7.0, 20.0));
        _sim->addObstacle(vertices);
        _sim->processObstacles();
    }
    _lastDoRVO = getFloatSteadyNowTime();
    _lastPrintStatus = _lastDoRVO;
}
void MoveSync::checkStepRVO(bool preCheck)
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
    }
    if (!_sim)
    {
        return;
    }
    auto sim = _sim;

    for (auto &kv : scene->_entitys)
    {
        auto &entity = *kv.second;
        if (entity._control.agentNo >= sim->getNumAgents())
        {
            continue;
        }
        if (entity._move.action == MOVE_ACTION_IDLE)
        {
            continue;
        }
        do
        {
            while (!entity._move.waypoints.empty())
            {
                double dist = getDistance(entity._move.position, entity._move.waypoints.front());
                if (dist < 1.0 || (dist < 6.0&&entity._move.action == MOVE_ACTION_FOLLOW))
                {
                    entity._move.waypoints.erase(entity._move.waypoints.begin());
                    continue;
                }
                break;
            }
            if (entity._move.waypoints.empty())
            {
                LOGD("END MOVE[" << entity._state.avatarName << "]: all waypoints is gone");
                entity._move.action = MOVE_ACTION_IDLE;
                break;
            }
            if (entity._control.blockMoveCount > 1.0 / SceneFrameInterval)
            {
                LOGW("BREAK MOVE[" << entity._state.avatarName << "][" << entity._state.eid << "]: block long time. count = " << entity._control.blockMoveCount);
                entity._move.waypoints.clear();
                entity._move.action = MOVE_ACTION_IDLE;
                entity._control.blockMoveCount = 0;
                break;
            }
            if (!preCheck)
            {
                break;
            }
            if (::accessFile("../rvo.txt"))
            {
                std::string content = readFileContent("../rvo.txt");
                auto tp = splitTupleString<double, size_t, double, double, double>(content, ",", " ");
                sim->setAgentNeighborDist(entity._control.agentNo, std::get<0>(tp));
                sim->setAgentMaxNeighbors(entity._control.agentNo, std::get<1>(tp));
                sim->setAgentTimeHorizon(entity._control.agentNo, std::get<2>(tp));
                sim->setAgentTimeHorizonObst(entity._control.agentNo, std::get<3>(tp));
                sim->setAgentRadius(entity._control.agentNo, std::get<4>(tp));
            }

            sim->setAgentMaxSpeed(entity._control.agentNo, entity._move.expectSpeed);
            double dist = getDistance(entity._move.position, entity._move.waypoints.front());
            double needTime = dist / entity._move.expectSpeed;
            RVO::Vector2 dir = RVO::normalize(toRVOVector2(entity._move.waypoints.front()) - toRVOVector2(entity._move.position));
            if (needTime > SceneFrameInterval)
            {
                dir *= entity._move.expectSpeed;
            }
            else
            {
                dir *= needTime / SceneFrameInterval;
            }
            sim->setAgentPrefVelocity(entity._control.agentNo, dir);
            LOGD("RVO PRE MOVE[" << entity._state.avatarName << "] local=" << entity._move.position
                << ", dst=" << entity._move.waypoints.front() << ", dir=" << dir);
        } while (false);

        if (entity._move.action == MOVE_ACTION_IDLE)
        {
            entity._move.waypoints.clear();
            sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0, 0));
            scene->broadcast(MoveNotice(entity._move));
            LOGD("RVO FIN MOVE[" << entity._state.avatarName << "] local=" << entity._move.position);
        }
        entity._isMoveDirty = true;
    }
}

void MoveSync::update()
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
    }
    if (getFloatSteadyNowTime() - _lastPrintStatus > 10)
    {
        _lastPrintStatus = getFloatSteadyNowTime();
        LOGI("sceneID=" << scene->_sceneID << ", rvo sum second=" << _sim->getGlobalTime() << ", scene sum second=" << getFloatSteadyNowTime() - scene->_startTime);
    }

    checkStepRVO(true);
    if (!_sim)
    {
        return;
    }
    auto sim = _sim;

    double timeStep = getFloatSteadyNowTime() - _lastDoRVO;
    _lastDoRVO = getFloatSteadyNowTime();
    sim->setTimeStep(timeStep);
    sim->doStep();
    for (auto &kv : scene->_entitys)
    {
        auto &entity = *kv.second;
        if (entity._control.agentNo >= sim->getNumAgents())
        {
            continue;
        }
        auto rvoPos = toEPoint(sim->getAgentPosition(entity._control.agentNo));
        if (getDistance(entity._move.position, rvoPos) > 0.1)
        {
            entity._isMoveDirty = true;
        }
        if (entity._isMoveDirty)
        {
            auto realMove = toRVOVector2(rvoPos) - toRVOVector2(entity._move.position);
            auto expectMove = sim->getAgentPrefVelocity(entity._control.agentNo);
            entity._move.realSpeed = RVO::abs(realMove) / timeStep;
            if (RVO::abs(expectMove) > 0.0001) //float over
            {
                if (RVO::abs(realMove) / (RVO::abs(expectMove) / ServerPulseInterval) < 0.1)
                {
                    entity._control.blockMoveCount++;
                    LOGW("EXPECT MOVE DIST WRONG[" << entity._state.eid << "]: DIFF=" << RVO::abs(realMove) / RVO::abs(expectMove) << ", now blocks=" << entity._control.blockMoveCount);
                }
                else
                {
                    entity._control.blockMoveCount = 0;
                }
            }
        }

        entity._move.position = toEPoint(sim->getAgentPosition(entity._control.agentNo));
        if (entity._isMoveDirty)
        {
            LOGD("RVO AFT MOVE[" << entity._state.avatarName << "] local=" << entity._move.position);
        }

    }

    checkStepRVO(false);
    
}
ui64 MoveSync::addAgent(EPosition pos)
{
    auto agent = _sim->addAgent(toRVOVector2(pos));
    _sim->setAgentRadius(agent, 0.5f);
    return agent;
}

void MoveSync::delAgent(ui64 agent)
{
    _sim->removeAgent(agent);
}
bool MoveSync::isValidAgent(ui64 agent)
{
    if (_sim)
    {
        return agent < _sim->getNumAgents();
    }
    return false;
}
bool MoveSync::setAgentPosition(ui64 agent, EPosition pos)
{
    if (_sim && isValidAgent(agent))
    {
        _sim->setAgentPosition(agent, toRVOVector2(pos));
        return true;
    }
    return false;
}
bool MoveSync::doMove(ui64 eid, MOVE_ACTION action, double speed, ui64 follow, EPositionArray dsts)
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return false;
    }

    auto entity = scene->getEntity(eid);
    if (!entity)
    {
        return false;
    }
    if (!isValidAgent(entity->_control.agentNo))
    {
        return false;
    }
    if (entity->_state.state != ENTITY_STATE_ACTIVE)
    {
        return false;
    }
    auto & moveInfo = entity->_move;
    if (moveInfo.action == MOVE_ACTION_PASV_PATH || moveInfo.action == MOVE_ACTION_FORCE_PATH)
    {
        return false;
    }



    auto followEntity = scene->getEntity(follow);
    if (!followEntity || followEntity->_state.state != ENTITY_STATE_ACTIVE)
    {
        action = MOVE_ACTION_IDLE;
    }


    if (action != MOVE_ACTION_FOLLOW && action != MOVE_ACTION_IDLE && dsts.empty())
    {
        return false;
    }


    //stop
    if (action == MOVE_ACTION_IDLE)
    {
        moveInfo.action = MOVE_ACTION_IDLE;
        moveInfo.realSpeed = 0.0;
        moveInfo.expectSpeed = moveInfo.expectSpeed; //don't reset here
        moveInfo.follow = moveInfo.follow; //don't reset here
        moveInfo.waypoints.clear();
        _sim->setAgentPrefVelocity(entity->_control.agentNo, RVO::Vector2(0, 0));
    }
    //begin move
    else if (moveInfo.action == MOVE_ACTION_IDLE)
    {
        moveInfo.action = action;
        moveInfo.realSpeed = 0.0f;
        moveInfo.expectSpeed = speed;
        moveInfo.follow = follow;
        moveInfo.waypoints = dsts;
    }
    //refresh move
    else
    {
        moveInfo.action = action;
        moveInfo.realSpeed = moveInfo.realSpeed;
        moveInfo.expectSpeed = speed;
        moveInfo.follow = follow;
        if (action != MOVE_ACTION_FOLLOW)
        {
            moveInfo.waypoints = dsts;
        }
        else
        {
            moveInfo.waypoints.clear();
            moveInfo.waypoints.push_back(followEntity->_move.position);
        }
        
    }
    if (action != MOVE_ACTION_IDLE && !dsts.empty())
    {
        entity->_control.lastClientFaceRadian = getRadian(entity->_move.position.x, entity->_move.position.y, dsts.at(0).x, dsts.at(0).y);
    }
    entity->_isMoveDirty = true;
    scene->broadcast(MoveNotice(moveInfo));
    return true;
}


