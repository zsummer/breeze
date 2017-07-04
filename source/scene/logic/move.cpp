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
void MoveSync::init(std::weak_ptr<Scene> weak_scene)
{
    _scene = weak_scene;
    _sim = new RVO::RVOSimulator();
    _sim->setTimeStep(SceneFrameInterval);
    _sim->setAgentDefaults(30.0, 10, 1.0, 1.0, 1.0, 0.0);
    _lastDoRVO = getFloatSteadyNowTime();
    _lastPrintStatus = _lastDoRVO;

}


void MoveSync::fillRVO(double frame)
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

            if (entity._move.action == MOVE_ACTION_FOLLOW)
            {
                do
                {
                    entity._move.waypoints.clear();
                    if (entity._move.follow == InvalidEntityID)
                    {
                        LOGE("doMove follow EntityID is invalid. self eid=" << entity._state.eid);
                        break;
                    }
                    auto followEntity = scene->getEntity(entity._move.follow);
                    if (!followEntity || followEntity->_state.state != ENTITY_STATE_ACTIVE)
                    {
                        LOGW("doMove follow EntityID not found or state not active. self eid=" << entity._state.eid << ", follow eid=" << entity._move.follow);
                        break;
                    }

                    //collision check 
                    double dist = getDistance(entity._move.position, followEntity->_move.position);
                    if (dist <= entity._control.collision + followEntity->_control.collision + PATH_PRECISION)
                    {
                        break;
                    }
                    entity._move.waypoints.push_back(followEntity->_move.position);
                } while (false);
            }


            while (!entity._move.waypoints.empty())
            {
                double dist = getDistance(entity._move.position, entity._move.waypoints.front());
                if (dist < entity._control.collision +  PATH_PRECISION )
                {
                    entity._move.waypoints.erase(entity._move.waypoints.begin());
                    continue;
                }
                break;
            }
            if (entity._move.waypoints.empty())
            {
                entity._move.waypoints.push_back(entity._move.position);
                entity._isMoveDirty = true;
                break;
            }



            double dist = getDistance(entity._move.position, entity._move.waypoints.front());
            if (dist < entity._control.collision + PATH_PRECISION)
            {
                sim->setAgentMaxSpeed(entity._control.agentNo, 0 );
                sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0,0));
            }
            else if (dist < entity._move.expectSpeed * frame)
            {
                sim->setAgentMaxSpeed(entity._control.agentNo,  dist / frame);
                RVO::Vector2 dir = RVO::normalize(toRVOVector2(entity._move.waypoints.front()) - toRVOVector2(entity._move.position));
                dir *= dist / frame;
                sim->setAgentPrefVelocity(entity._control.agentNo, dir);
            }
            else
            {
                sim->setAgentMaxSpeed(entity._control.agentNo, entity._move.expectSpeed);
                RVO::Vector2 dir = RVO::normalize(toRVOVector2(entity._move.waypoints.front()) - toRVOVector2(entity._move.position));
                dir *= entity._move.expectSpeed;
                sim->setAgentPrefVelocity(entity._control.agentNo, dir);
            }
            sim->setAgentRadius(entity._control.agentNo, entity._control.collision);
            if (entity._state.etype == ENTITY_PLAYER)
            {
                sim->setAgentTimeHorizon(entity._control.agentNo, 0.1);
            }
            else
            {
                sim->setAgentTimeHorizon(entity._control.agentNo, frame*3);
            }
            
            sim->setAgentTimeHorizonObst(entity._control.agentNo, frame);
            sim->setAgentNeighborDist(entity._control.agentNo, 1.5 * sim->getAgentMaxSpeed(entity._control.agentNo));
            sim->setAgentMaxNeighbors(entity._control.agentNo, 100);



            /* LOGD("RVO fill move[" << entity._state.avatarName << "] local=" << entity._move.position
                << ", dst=" << entity._move.waypoints.front() << ", dir=" << sim->getAgentPrefVelocity(entity._control.agentNo) << ", max Speed=" 
            << sim->getAgentMaxSpeed(entity._control.agentNo)); */

        } while (false);
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
    if (!_sim)
    {
        return;
    }
    double now = getFloatSteadyNowTime();

    if (now - _lastPrintStatus > 10)
    {
        _lastPrintStatus = getFloatSteadyNowTime();
        LOGI("sceneID=" << scene->_sceneID << ", rvo sum second=" << _sim->getGlobalTime() << ", scene sum second=" << now - scene->_startTime);
    }

    

    auto sim = _sim;
    double timeStep = now - _lastDoRVO;
    _lastDoRVO = now;

    fillRVO(timeStep);
    sim->setTimeStep(timeStep);
    sim->doStep();
    fixDirtyMove(timeStep);

}
void MoveSync::fixDirtyMove(double frame)
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
            LOGE("MoveSync::fixDirtyMove no agentNo. eid=" << entity._state.eid << ", name=" << entity._state.avatarName);
            continue;
        }
        auto rvoPos = toEPosition(sim->getAgentPosition(entity._control.agentNo));
        //auto realMove = rvoPos - entity._move.position;
        auto realDist = getDistance(rvoPos, entity._move.position);
        if (entity._move.action == MOVE_ACTION_IDLE)
        {
            if (realDist > 0.3)
            {
                if (entity._state.etype == ENTITY_PLAYER)
                {
                    sim->setAgentPosition(entity._control.agentNo, toRVOVector2(entity._move.position));
                }
                else
                {
                    entity._move.position = rvoPos;
                    entity._isMoveDirty = true;
                }
            }
            continue;
        }
        

        entity._move.position = rvoPos;
        entity._move.realSpeed = realDist / frame;
        entity._isMoveDirty = true;
        
        if (entity._move.waypoints.empty())
        {
            LOGD("MoveSync::fixDirtyMove waypoints out.  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos);
        }
        else
        {
//            LOGD("MoveSync::fixDirtyMove waypoints update.  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
//            << ", waypoints=" << entity._move.waypoints);
        } 



        //check move end
        bool moveEnd = false;
        do
        {
            if (entity._state.state != ENTITY_STATE_ACTIVE)
            {
                moveEnd = true;
                LOGD("MoveSync::fixDirtyMove move end. state not active .  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                    << ", waypoints=" << entity._move.waypoints);
                break;
            }
            if (entity._move.action == MOVE_ACTION_FOLLOW)
            {
                if (entity._move.follow == InvalidEntityID)
                {
                    moveEnd = true;
                    LOGD("MoveSync::fixDirtyMove move end. invalid follow .  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                        << ", waypoints=" << entity._move.waypoints);
                    break;
                }
                auto follow = scene->getEntity(entity._move.follow);
                if (!follow || follow->_state.state != ENTITY_STATE_ACTIVE)
                {
                    moveEnd = true;
                    LOGD("MoveSync::fixDirtyMove move end.  the follow target not active .  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                        << ", waypoints=" << entity._move.waypoints);
                    break;
                }
                if (getDistance(entity._move.position, follow->_move.position) <= entity._control.collision + follow->_control.collision + PATH_PRECISION)
                {
                    moveEnd = true;
                    LOGD("MoveSync::fixDirtyMove move end.  catch follow target.  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                        << ", waypoints=" << entity._move.waypoints);
                    break;
                }
                break;
            }
            if (entity._move.waypoints.empty())
            {
                LOGE("MoveSync::fixDirtyMove unintended flow.  entity move waypoints is empty but move state not idle.  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                    << ", waypoints=" << entity._move.waypoints);
                moveEnd = true;
                break;
            }

            while (!entity._move.waypoints.empty())
            {
                double dist = getDistance(entity._move.position, entity._move.waypoints.front());
                if (dist <= entity._control.collision + PATH_PRECISION)
                {
                    entity._move.waypoints.erase(entity._move.waypoints.begin());
                    LOGD("MoveSync::fixDirtyMove pop one waypoint.  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                        << ", waypoints=" << entity._move.waypoints);
                    continue;
                }
                break;
            }
            if (entity._move.waypoints.empty())
            {
                moveEnd = true;
                break;
            }
        } while (false);

        if (moveEnd)
        {
            entity._move.waypoints.clear();
            entity._move.action = MOVE_ACTION_IDLE;
            sim->setAgentMaxSpeed(entity._control.agentNo, 0);
            sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0, 0));
            LOGD("MoveSync::fixDirtyMove broadcast end notice.  eid=" << entity._state.eid << ", name=" << entity._state.avatarName << " old" << entity._move.position << ", new" << rvoPos
                << ", waypoints=" << entity._move.waypoints);
            scene->broadcast(MoveNotice(entity._move));
        }
    }
}



ui64 MoveSync::addAgent(EPosition pos, double collision)
{
    auto agent = _sim->addAgent(toRVOVector2(pos));
    _sim->setAgentMaxSpeed(agent, 0);
    _sim->setAgentPrefVelocity(agent, RVO::Vector2(0, 0));
    _sim->setAgentRadius(agent, collision);
    return agent;
}

void MoveSync::delAgent(ui64 agent)
{
    _sim->removeAgent(agent);
}
void MoveSync::addObstacle(const std::vector<RVO::Vector2> &vertices)
{
    if (_sim)
    {
        _sim->addObstacle(vertices);
    }
}
void MoveSync::cleanObstacle()
{
    if (_sim)
    {
        _sim->cleanObstacle();
    }
}
void MoveSync::processObstacles()
{
    if (_sim)
    {
        _sim->processObstacles();
    }
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
bool MoveSync::doMove(ui64 eid, MOVE_ACTION action, double speed, ui64 follow, EPositionArray waypoints)
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



    if (action == MOVE_ACTION_FOLLOW)
    {
        do
        {
            action = MOVE_ACTION_IDLE;
            waypoints.clear();
            if (follow == InvalidEntityID)
            {
                LOGE("doMove follow EntityID is invalid. self eid=" << eid);
                break;
            }
            auto followEntity = scene->getEntity(follow);
            if (!followEntity || followEntity->_state.state != ENTITY_STATE_ACTIVE)
            {
                LOGW("doMove follow EntityID not found or state not active. self eid=" << eid << ", follow eid=" << follow);
                break;
            }

            //collision check 
            double dist = getDistance(entity->_move.position, followEntity->_move.position);
            if (dist <= entity->_control.collision + followEntity->_control.collision + PATH_PRECISION)
            {
                break;
            }
            action = MOVE_ACTION_FOLLOW;
            waypoints.push_back(followEntity->_move.position);
        }
        while (false);
    }

    if (action != MOVE_ACTION_IDLE &&  waypoints.empty())
    {
        LOGE("doMove param error. action = " << (int)action << ", waypoints is empty.");
        return false;
    }

    if (action == MOVE_ACTION_IDLE && moveInfo.action == MOVE_ACTION_IDLE)
    {
        return false;  //invalid action 
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
        _sim->setAgentMaxSpeed(entity->_control.agentNo, 0);
    }
    //begin move
    else if (moveInfo.action == MOVE_ACTION_IDLE)
    {
        moveInfo.action = action;
        moveInfo.realSpeed = 0.0f;
        moveInfo.expectSpeed = speed;
        moveInfo.follow = follow;
        moveInfo.waypoints = waypoints;
    }
    //refresh move
    else
    {
        moveInfo.action = action;
        moveInfo.realSpeed = moveInfo.realSpeed;
        moveInfo.expectSpeed = speed;
        moveInfo.follow = follow;
        moveInfo.waypoints = waypoints;
    }


    entity->_isMoveDirty = true;
    scene->broadcast(MoveNotice(moveInfo));
    return true;
}


