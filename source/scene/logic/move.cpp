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

            while (!entity._move.waypoints.empty())
            {
                double dist = getDistance(entity._move.position, entity._move.waypoints.front());
                if (dist < entity._state.collision +  PATH_PRECISTION )
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

            if (::accessFile("../rvo.txt"))
            {
                std::string content = readFileContent("../rvo.txt");
                auto tp = splitTupleString<double, size_t, double, double, double>(content, ",", " ");
                sim->setAgentNeighborDist(entity._control.agentNo, std::get<0>(tp));
                sim->setAgentMaxNeighbors(entity._control.agentNo, std::get<1>(tp));
                sim->setAgentTimeHorizon(entity._control.agentNo, std::get<2>(tp));
                sim->setAgentTimeHorizonObst(entity._control.agentNo, std::get<3>(tp));
                
            }
            sim->setAgentRadius(entity._control.agentNo, entity._state.collision);
            double dist = getDistance(entity._move.position, entity._move.waypoints.front());
            if (dist < entity._state.collision + PATH_PRECISTION)
            {
                sim->setAgentMaxSpeed(entity._control.agentNo, 0);
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
            LOGD("RVO fill move[" << entity._state.avatarName << "] local=" << entity._move.position
                << ", dst=" << entity._move.waypoints.front() << ", dir=" << sim->getAgentPrefVelocity(entity._control.agentNo) << ", max Speed=" 
            << sim->getAgentMaxSpeed(entity._control.agentNo));

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
            if (entity._move.action != MOVE_ACTION_IDLE)
            {
                entity._move.waypoints.clear();
                sim->setAgentMaxSpeed(entity._control.agentNo, 0);
                sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0, 0));
                entity._move.action = MOVE_ACTION_IDLE;
                scene->broadcast(MoveNotice(entity._move));
                LOGE("move update no agentNo. entity id=" << entity._state.eid);
            }
            continue;
        }
        if (entity._move.action == MOVE_ACTION_IDLE)
        {
            //check
            auto rvoPos = toEPosition(sim->getAgentPosition(entity._control.agentNo));
            if (getDistance(rvoPos, entity._move.position) > 0.1 )
            {
                LOGE("move idle entity had move.  entity pos =" << entity._move.position << ", rvoPos=" << rvoPos 
                    << ", rvo v=" << sim->getAgentPrefVelocity(entity._control.agentNo)
                    << ", rvo speed=" << sim->getAgentMaxSpeed(entity._control.agentNo));
            }
            //end check 
            sim->setAgentPosition(entity._control.agentNo, toRVOVector2(entity._move.position));
            continue;
        }
        entity._isMoveDirty = true;
        auto rvoPos = toEPosition(sim->getAgentPosition(entity._control.agentNo));
        auto realMove = toRVOVector2(rvoPos) - toRVOVector2(entity._move.position);
        entity._move.realSpeed = RVO::abs(realMove) / frame;

        if (entity._move.waypoints.empty())
        {
            LOGD("RVO MOVE[" << entity._state.avatarName << "] old=" << entity._move.position << ", new=" << rvoPos << ", move=" << toEPosition(realMove));
        }
        else
        {
            LOGD("RVO MOVE[" << entity._state.avatarName << "] old=" << entity._move.position << ", new=" << rvoPos << ", move=" << toEPosition(realMove)
             << ", dst=" << entity._move.waypoints.front());
        }

        entity._move.position = rvoPos;

        //check move end
        bool moveEnd = false;
        do
        {
            if (entity._state.state != ENTITY_STATE_ACTIVE)
            {
                moveEnd = true;
                break;
            }
            if (entity._move.action == MOVE_ACTION_FOLLOW)
            {
                if (entity._move.follow == InvalidEntityID)
                {
                    moveEnd = true;
                    break;
                }
                auto follow = scene->getEntity(entity._move.follow);
                if (!follow || follow->_state.state != ENTITY_STATE_ACTIVE)
                {
                    moveEnd = true;
                    break;
                }
                if (getDistance(entity._move.position, follow->_move.position) <= entity._state.collision + follow->_state.collision + PATH_PRECISTION)
                {
                    moveEnd = true;
                    break;
                }
                break;
            }
            if (entity._move.waypoints.empty())
            {
                LOGE("");
                moveEnd = true;
                break;
            }

            while (!entity._move.waypoints.empty())
            {
                double dist = getDistance(entity._move.position, entity._move.waypoints.front());
                if (dist <= entity._state.collision + PATH_PRECISTION)
                {
                    entity._move.waypoints.erase(entity._move.waypoints.begin());
                    continue;
                }
                break;
            }
            if (entity._move.waypoints.empty())
            {
                entity._move.waypoints.push_back(entity._move.position);
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
            scene->broadcast(MoveNotice(entity._move));
            LOGD("RVO FIN MOVE[" << entity._state.avatarName << "] local=" << entity._move.position);
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

    if (action == MOVE_ACTION_FOLLOW)
    {
        do
        {
            action = MOVE_ACTION_IDLE;
            dsts.clear();
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
            double dist = getDistance(entity->_move.position.x, entity->_move.position.y, followEntity->_move.position.x, followEntity->_move.position.y);
            if (dist <= entity->_state.collision + followEntity->_state.collision + PATH_PRECISTION)
            {
                break;
            }
            action = MOVE_ACTION_FOLLOW;
            dsts.push_back(followEntity->_move.position);
        }
        while (false);
    }

    if (action != MOVE_ACTION_IDLE &&  dsts.empty())
    {
        LOGE("doMove param error. action = " << action << ", dsts is empty.");
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
        moveInfo.waypoints = dsts;
    }
    //refresh move
    else
    {
        moveInfo.action = action;
        moveInfo.realSpeed = moveInfo.realSpeed;
        moveInfo.expectSpeed = speed;
        moveInfo.follow = follow;
        moveInfo.waypoints = dsts;
    }

    if (action != MOVE_ACTION_IDLE && !dsts.empty())
    {
        entity->_control.lastClientFaceRadian = getRadian(entity->_move.position.x, entity->_move.position.y, dsts.at(0).x, dsts.at(0).y);
    }

    entity->_isMoveDirty = true;
    scene->broadcast(MoveNotice(moveInfo));
    return true;
}


