#include "scene.h"
#include "sceneMgr.h"
Scene::Scene(SceneID id)
{
    _sceneID = id;
    cleanScene();
}
Scene::~Scene()
{
    if(_sim)
    {
        delete _sim;
        _sim = nullptr;
    }
}
GroupID Scene::getGroupID(ServiceID avatarID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity)
    {
        return entity->_info.groupID;
    }
    return InvalidGroupID;
}
void Scene::getSceneSection(SceneSection & ss)
{
    ss.sceneID = _sceneID;
    ss.sceneType = _sceneType;
    ss.sceneStatus = _sceneStatus;
    ss.sceneStartTime = _startTime;
    ss.sceneEndTime = _endTime;
    ss.serverTime = getFloatNowTime();
    for (auto & entity : _entitys)
    {
        ss.entitys.push_back(entity.second->getFullData());
    }
}



bool Scene::cleanScene()
{
    _lastEID = ServerConfig::getRef().getSceneConfig()._lineID * 1000 + 1000;
    _entitys.clear();
    _players.clear();
    while (!_asyncs.empty()) _asyncs.pop();
    _sceneType = SCENE_NONE;
    _sceneStatus = SCENE_STATE_NONE;
    _lastStatusChangeTime = getFloatNowTime();
    if (_sim)
    {
        delete _sim;
        _sim = nullptr;
    }

    return true;
}

bool Scene::initScene(SceneType sceneType, MapID mapID)
{
    if (_sceneStatus != SCENE_STATE_NONE || _sim)
    {
        LOGE("Scene::loadScene  scene status error");
        return false;
    }
    _sceneType = sceneType;
    _sceneStatus = SCENE_STATE_ACTIVE;
    _lastStatusChangeTime = getFloatNowTime();
    _startTime = getFloatNowTime();
    _endTime = getFloatNowTime() + 600;
    _sim = new RVO::RVOSimulator();
    _sim->setTimeStep(0.33);
    _sim->setAgentDefaults(15.0, 10, 10.0, 5.0, 2.0, 2.0);
    if (true)
    {
        std::vector<RVO::Vector2> vertices;
        vertices.push_back(RVO::Vector2(-7.0, -20.0));
        vertices.push_back(RVO::Vector2(7.0, -20.0));
        vertices.push_back(RVO::Vector2(7.0, 20.0));
        vertices.push_back(RVO::Vector2(-7.0, 20.0));
        _sim->addObstacle(vertices);
        _sim->processObstacles();
    }

    //load map
    //load entitys

    return true;
}



EntityPtr Scene::getEntity(EntityID eID)
{
    auto founder = _entitys.find(eID);
    if (founder == _entitys.end())
    {
        return nullptr;
    }
    return founder->second;
}
EntityPtr Scene::getEntityByAvatarID(ServiceID avatarID)
{
    auto founder = _players.find(avatarID);
    if (founder == _players.end())
    {
        return nullptr;
    }
    return founder->second;
}



EntityPtr Scene::addEntity(const AvatarBaseInfo & baseInfo,
    const AvatarPropMap & baseProps,
    EntityCampType ecolor,
    EntityType etype,
    EntityState state,
    GroupID groupID)
{
    EntityPtr entity = std::make_shared<Entity>();

    entity->_baseInfo = baseInfo;
    entity->_baseProps = baseProps;



    entity->_info.eid = ++_lastEID;
    entity->_info.color = ecolor;
    entity->_info.etype = etype;
    entity->_info.groupID = groupID;
    entity->_info.state = ENTITY_STATE_ACTIVE;
    entity->_info.leader = InvalidEntityID;
    entity->_info.foe = InvalidEntityID;

    entity->_info.curHP = 100;

    entity->_control.spawnpoint = { 0.0,0.0 };
    entity->_control.eid = entity->_info.eid;
    entity->_control.agentNo = -1;
    entity->_control.stateChageTick = getFloatNowTime();

    entity->_move.eid = entity->_info.eid;
    entity->_move.pos = entity->_control.spawnpoint;
    entity->_move.follow = InvalidEntityID;
    entity->_move.waypoints.clear();
    entity->_move.action = MOVE_ACTION_IDLE;

    entity->_report.eid = entity->_info.eid;

    entity->_control.agentNo = _sim->addAgent(RVO::Vector2(entity->_move.pos.x, entity->_move.pos.y));

    _entitys.insert(std::make_pair(entity->_info.eid, entity));

    if (baseInfo.avatarID != InvalidServiceID)
    {
        _players[baseInfo.avatarID] = entity;
    }

    AddEntityNotice notice;
    notice.entitys.push_back(entity->getFullData());
    broadcast(notice, entity->_baseInfo.avatarID);

    return entity;
}

bool Scene::removeEntity(EntityID eid)
{
    auto entity = getEntity(eid);
    if (!entity)
    {
        LOGE("");
        return false;
    }
    if(entity->_control.agentNo < _sim->getNumAgents())
    {
        _sim->removeAgent(entity->_control.agentNo);
        entity->_control.agentNo = -1;
    }
    if (entity->_info.etype == ENTITY_AVATAR)
    {
        _players.erase(entity->_baseInfo.avatarID);
    }
    _entitys.erase(eid);

    RemoveEntityNotice notice;
    notice.eids.push_back(eid);
    broadcast(notice);
    return true;
}

bool Scene::playerAttach(ServiceID avatarID, SessionID sID)
{
    EntityPtr entity = getEntityByAvatarID(avatarID);
    if (!entity)
    {
        return false;
    }
    entity->_clientSessionID = sID;

    SceneSectionNotice notice;
    getSceneSection(notice.section);
    sendToClient(avatarID, notice);
    return true;
}



bool Scene::playerDettach(ServiceID avatarID, SessionID sID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity && entity->_clientSessionID == sID)
    {
        entity->_clientSessionID = InvalidSessionID;
    }
    return true;
}



bool Scene::onUpdate()
{
    if (getFloatNowTime() > _endTime)
    {
        return false;
    }
    while(!_asyncs.empty())
    {
        auto func = _asyncs.front();
        _asyncs.pop();
        func();
    }
    doStepRVO();

    SceneRefreshNotice notice;
    for (auto &kv : _entitys)
    {
        if (kv.second->_isInfoDirty)
        {
            notice.entityInfos.push_back(kv.second->_info);
        }
        if (kv.second->_isMoveDirty)
        {
            notice.entityMoves.push_back(kv.second->_move);
        }
    }
    broadcast(notice);
    return true;
}

void Scene::doStepRVO()
{
    if (_sim)
    {
        for (auto &kv:_entitys)
        {
            auto &entity = *kv.second;
            if (entity._control.agentNo  >= _sim->getNumAgents())
            {
                continue;
            }
            if (entity._move.action == MOVE_ACTION_IDLE)
            {
                continue;
            }
            do
            {
                EPoint dst;
                if (entity._move.action == MOVE_ACTION_FOLLOW)
                {
                    auto follow = getEntity(entity._move.follow);
                    if (!follow)
                    {
                        entity._move.action = MOVE_ACTION_IDLE;
                        entity._move.waypoints.clear();
                        break;
                    }
                    dst = follow->_move.pos;
                }
                else if (entity._move.waypoints.empty())
                {
                    entity._move.action = MOVE_ACTION_IDLE;
                    break;
                }
                else
                {
                    dst = entity._move.waypoints.front();
                }

                if (entity._move.action == MOVE_ACTION_FORCE_PATH)
                {
                   // _sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0.0, 0.0));
                }
                else
                {
                    
                }
                _sim->setAgentMaxSpeed(entity._control.agentNo, entity._move.speed);
                _sim->setAgentPrefVelocity(entity._control.agentNo, RVO::normalize(RVO::Vector2(dst.x, dst.y) - RVO::Vector2(entity._move.pos.x, entity._move.pos.y)));
            } while (false);

            if (entity._move.action == MOVE_ACTION_IDLE)
            {
                broadcast(MoveNotice(entity._move));
                _sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0.0, 0.0));
            }
            entity._isMoveDirty = true;
        }
        _sim->doStep();

        for (auto &kv : _entitys)
        {
            auto &entity = *kv.second;
            if (entity._control.agentNo >= _sim->getNumAgents())
            {
                continue;
            }
            if (entity._move.action == MOVE_ACTION_IDLE)
            {
                continue;
            }
            auto cur = _sim->getAgentPosition(entity._control.agentNo);
            entity._move.pos.x = cur.x();
            entity._move.pos.y = cur.y();
            do
            {
                EPoint dst;
                if (entity._move.action == MOVE_ACTION_FOLLOW)
                {
                    auto follow = getEntity(entity._move.follow);
                    if (!follow)
                    {
                        entity._move.action = MOVE_ACTION_IDLE;
                        entity._move.waypoints.clear();
                        break;
                    }
                    dst = follow->_move.pos;
                }
                else if (entity._move.waypoints.empty())
                {
                    entity._move.action = MOVE_ACTION_IDLE;
                    break;
                }
                else
                {
                    dst = entity._move.waypoints.front();
                }


                if (getDistance(entity._move.pos.x, entity._move.pos.y, dst.x, dst.y) < 1.0)
                {
                    if (entity._move.action == MOVE_ACTION_FOLLOW)
                    {
                        break;
                    }
                    else if (entity._move.waypoints.size() > 1)
                    {
                        entity._move.waypoints.erase(entity._move.waypoints.begin());
                        break;
                    }
                    else
                    {
                        entity._move.action = MOVE_ACTION_IDLE;
                        entity._move.waypoints.clear();
                        break;
                    }
                }
            } while (false);

            if (entity._move.action == MOVE_ACTION_IDLE)
            {
                broadcast(MoveNotice(entity._move));
                _sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0.0, 0.0));
            }
            entity._isMoveDirty = true;
        }
        
    }
}

void Scene::pushAsync(std::function<void()> && func)
{
    _asyncs.push(std::move(func));
}

void Scene::onPlayerInstruction(ServiceID avatarID, ReadStream & rs)
{
    if (avatarID == InvalidAvatarID)
    {
        return;
    }
    if (rs.getProtoID() == MoveReq::getProtoID())
    {
        MoveReq req;
        rs >> req;
        if (!doMove(req.eid, (MoveAction)req.action, 0.0, -1, InvalidEntityID, req.dstPos, avatarID))
        {
            sendToClient(avatarID, MoveResp(EC_ERROR, req.eid, req.action));
        }
    }
    else if (rs.getProtoID() == UseSkillReq::getProtoID())
    {
        UseSkillReq req;
        rs >> req;
        if (!doSkill())
        {
            sendToClient(avatarID, UseSkillResp(EC_ERROR, req.eid));
        }
    }
}

bool Scene::doMove(ui64 eid, MoveAction action, double speed, ui64 frames, ui64 follow, EPoint dst, AvatarID avatarID, bool clean)
{
    auto entity = getEntity(eid);
    if(!entity)
    {
        return false;
    }
    if (avatarID != InvalidAvatarID && (entity->_baseInfo.avatarID != avatarID || entity->_info.etype == ENTITY_FLIGHT))
    {
        //玩家操作不属于自己控制范围的实体
        return false;
    }
    auto & moveInfo = entity->_move;
    if (moveInfo.action == MOVE_ACTION_PASV_PATH || moveInfo.action == MOVE_ACTION_FORCE_PATH)
    {
        return false;
    }

    moveInfo.action = action;
    moveInfo.speed = avatarID == InvalidAvatarID ? speed : entity->getSpeed();
    moveInfo.frames = frames;
    moveInfo.follow = follow;
    
    if (clean || action == MOVE_ACTION_IDLE)
    {
        moveInfo.waypoints.clear();
    }
    if (action != MOVE_ACTION_IDLE)
    {
        moveInfo.waypoints.insert(moveInfo.waypoints.begin(), dst);
    }
    if (moveInfo.action == MOVE_ACTION_IDLE && entity->_control.agentNo < _sim->getNumAgents())
    {
        _sim->setAgentVelocity(entity->_control.agentNo, RVO::Vector2(0.0, 0.0));
    }

    entity->_isMoveDirty = true;
    broadcast(MoveNotice(moveInfo));
    return true;
}
bool Scene::doSkill()
{
    return true;
}
bool Scene::cleanSkill()
{
    return true;
}
bool Scene::addBuff()
{
    return true;
}
bool Scene::cleanBuff()
{
    return true;
}





