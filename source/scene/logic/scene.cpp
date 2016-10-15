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
        return entity->_entityInfo.groupID;
    }
    return InvalidGroupID;
}
void Scene::getSceneSection(SceneSection & ss)
{
    ss.sceneID = _sceneID;
    ss.sceneType = _sceneType;
    ss.sceneState = _sceneStatus;
    ss.sceneStartTime = _startTime;
    ss.sceneEndTime = _endTime;
    ss.serverTime = getFloatSteadyNowTime();
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
    _monsters.clear();
    while (!_asyncs.empty()) _asyncs.pop();
    _sceneType = SCENE_NONE;
    _sceneStatus = SCENE_STATE_NONE;
    _lastStatusChangeTime = getFloatSteadyNowTime();
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
    _lastStatusChangeTime = getFloatSteadyNowTime();
    _startTime = getFloatSteadyNowTime();
    _endTime = getFloatSteadyNowTime() + 600;
    _sim = new RVO::RVOSimulator();
    _sim->setTimeStep(SceneFrameInterval);
    _sim->setAgentDefaults(15.0, 1000, 10000.0, 10000.0, 2.0, 7.0);
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
    EntityCampType camp,
    EntityType etype,
    EntityState state,
    GroupID groupID)
{
    EntityPtr entity = std::make_shared<Entity>();

    entity->_baseInfo = baseInfo;
    entity->_baseProps = baseProps;



    entity->_entityInfo.eid = ++_lastEID;
    entity->_entityInfo.camp = camp;
    entity->_entityInfo.etype = etype;
    entity->_entityInfo.groupID = groupID;
    entity->_entityInfo.state = ENTITY_STATE_ACTIVE;
    entity->_entityInfo.leader = InvalidEntityID;
    entity->_entityInfo.foe = InvalidEntityID;

    entity->_entityInfo.curHP = 100;

    entity->_control.spawnpoint = { 0.0 - 30 +  realRandF()*30 ,60 -30 + realRandF()*30 };
    entity->_control.eid = entity->_entityInfo.eid;
    entity->_control.agentNo = -1;
    entity->_control.stateChageTick = getFloatSteadyNowTime();

    entity->_entityMove.eid = entity->_entityInfo.eid;
    entity->_entityMove.pos = entity->_control.spawnpoint;
    entity->_entityMove.follow = InvalidEntityID;
    entity->_entityMove.waypoints.clear();
    entity->_entityMove.action = MOVE_ACTION_IDLE;

    entity->_report.eid = entity->_entityInfo.eid;

    entity->_control.agentNo = _sim->addAgent(toRVOVector2(entity->_entityMove.pos));
    _entitys.insert(std::make_pair(entity->_entityInfo.eid, entity));

    if (baseInfo.avatarID != InvalidServiceID && etype == ENTITY_AVATAR)
    {
        _players[baseInfo.avatarID] = entity;
        _sim->setAgentRadius(entity->_control.agentNo, 0.5f);
    }
    else
    {
        _sim->setAgentRadius(entity->_control.agentNo, 1.1f);
    }

    AddEntityNotice notice;
    notice.entitys.push_back(entity->getFullData());
    broadcast(notice, entity->_baseInfo.avatarID);

    return entity;
}
bool Scene::removePlayer(AvatarID avatarID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity)
    {
        return removeEntity(entity->_entityInfo.eid);
    }
    return false;
}
bool Scene::removePlayerByGroupID(GroupID groupID)
{
    std::set<EntityID> removes;
    for (auto entity : _entitys)
    {
        if (entity.second->_entityInfo.etype == ENTITY_AVATAR && entity.second->_entityInfo.groupID == groupID)
        {
            removes.insert(entity.second->_entityInfo.eid);
        }
    }
    for (auto eid : removes)
    {
        removeEntity(eid);
    }
    return true;
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
    if (entity->_entityInfo.etype == ENTITY_AVATAR)
    {
        _players.erase(entity->_baseInfo.avatarID);
        SceneMgr::getRef().sendToWorld(SceneServerGroupStateChangeIns(getSceneID(), entity->_entityInfo.groupID, SCENE_NONE));
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

    LOGI("Scene::playerAttach avatarName=" << entity->_baseInfo.avatarName << " sessionID=" << sID << ", entityID=" << entity->_entityInfo.eid);
    EntityFullDataArray entitys;
    SceneSectionNotice section;
    getSceneSection(section.section);
    entitys.swap(section.section.entitys);
    sendToClient(avatarID, section);

    AddEntityNotice notice;
    while (!entitys.empty())
    {
        notice.entitys.push_back(entitys.back());
        entitys.pop_back();
        if (notice.entitys.size() >= 10)
        {
            sendToClient(avatarID, notice);
            notice.entitys.clear();
        }
    }
    if (!notice.entitys.empty())
    {
        sendToClient(avatarID, notice);
    }
    return true;
}



bool Scene::playerDettach(ServiceID avatarID, SessionID sID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity && entity->_clientSessionID == sID)
    {
        LOGI("Scene::playerDettach avatarName=" << entity->_baseInfo.avatarName << " sessionID=" << sID << ", entityID=" << entity->_entityInfo.eid);
        entity->_clientSessionID = InvalidSessionID;
    }
    return true;
}



bool Scene::onUpdate()
{
    if (getFloatSteadyNowTime() > _endTime)
    {
        return false;
    }

    while(!_asyncs.empty())
    {
        auto func = _asyncs.front();
        _asyncs.pop();
        func();
    }
    if (getFloatSteadyNowTime() - _lastCheckMonstr > 0.5)
    {
        _lastCheckMonstr = getFloatSteadyNowTime();
        doMonster();
        doFollow();
    }

    doStepRVO();

    SceneRefreshNotice notice;
    for (auto &kv : _entitys)
    {
        if (kv.second->_isInfoDirty)
        {
            notice.entityInfos.push_back(kv.second->_entityInfo);
            kv.second->_isInfoDirty = false;
        }
        if (kv.second->_isMoveDirty)
        {
            notice.entityMoves.push_back(kv.second->_entityMove);
            kv.second->_isMoveDirty = false;
//            LOGD("Scene::onUpdate avatarName=" << kv.second->_baseInfo.avatarName <<  ", EntityMove=" << kv.second->_entityMove);
        }
    }
    if (!notice.entityInfos.empty() || !notice.entityMoves.empty())
    {
        broadcast(notice);
    }
    return true;
}

void Scene::checkStepRVO(bool preCheck)
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
            if (entity._entityMove.action == MOVE_ACTION_IDLE)
            {
                continue;
            }
            do
            {
                while (!entity._entityMove.waypoints.empty() 
                    && (getDistance(entity._entityMove.pos, entity._entityMove.waypoints.front()) < 1.0 || (getDistance(entity._entityMove.pos, entity._entityMove.waypoints.front()) < 5.0 && entity._entityMove.action == MOVE_ACTION_FOLLOW)) )
                {
                    entity._entityMove.waypoints.erase(entity._entityMove.waypoints.begin());
                }
                if (entity._entityMove.waypoints.empty())
                {
                    entity._entityMove.action = MOVE_ACTION_IDLE;
                    break;
                }
                if (entity._control.blockMoveCount > 1.0/SceneFrameInterval)
                {
                    entity._entityMove.waypoints.clear();
                    entity._entityMove.action = MOVE_ACTION_IDLE;
                    break;
                }
                if (!preCheck)
                {
                    break;
                }
                _sim->setAgentMaxSpeed(entity._control.agentNo, entity._entityMove.speed);
                double dist = getDistance(entity._entityMove.pos, entity._entityMove.waypoints.front());
                double needTime = dist / entity._entityMove.speed;
                RVO::Vector2 dir = RVO::normalize(toRVOVector2(entity._entityMove.waypoints.front()) - toRVOVector2(entity._entityMove.pos));
                if (needTime > SceneFrameInterval)
                {
                    dir *= entity._entityMove.speed;
                }
                else
                {
                    dir *= needTime / SceneFrameInterval;
                }
                _sim->setAgentPrefVelocity(entity._control.agentNo, dir);
                LOGD("RVO PRE MOVE[" << entity._baseInfo.avatarName << "] local=" << entity._entityMove.pos << ", dst=" << entity._entityMove.waypoints.front() << ", dir=" << dir);
            } while (false);

            if (entity._entityMove.action == MOVE_ACTION_IDLE)
            {
                entity._entityMove.waypoints.clear();
                _sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0, 0));
                broadcast(MoveNotice(entity._entityMove));
                LOGD("RVO FIN MOVE[" << entity._baseInfo.avatarName << "] local=" << entity._entityMove.pos);
            }
            entity._isMoveDirty = true;
        }
    }
}
void Scene::doStepRVO()
{
    checkStepRVO(true);
    if (_sim)
    {
        _sim->doStep();
        for (auto &kv : _entitys)
        {
            auto &entity = *kv.second;
            if (entity._control.agentNo >= _sim->getNumAgents())
            {
                continue;
            }
            auto rvoPos = toEPoint(_sim->getAgentPosition(entity._control.agentNo));
            if (entity._isMoveDirty)
            {
                auto realMove = toRVOVector2(rvoPos) - toRVOVector2(entity._entityMove.pos);
                auto expectMove = _sim->getAgentVelocity(entity._control.agentNo);
                if (RVO::abs(realMove) / RVO::abs(expectMove) < 0.1)
                {
                    entity._control.blockMoveCount++;
                }
                else
                {
                    entity._control.blockMoveCount = 0;
                }
            }

            if (getDistance(entity._entityMove.pos, rvoPos) > 0.1)
            {
                entity._isMoveDirty = true;
            }
            entity._entityMove.pos = toEPoint(_sim->getAgentPosition(entity._control.agentNo));
            if (entity._isMoveDirty)
            {
                LOGD("RVO AFT MOVE[" << entity._baseInfo.avatarName << "] local=" << entity._entityMove.pos);
            }
            
        }
    }
    checkStepRVO(false);
}


void Scene::doMonster()
{
    while (_monsters.size() < _players.size() * 3  )
    {
        AvatarBaseInfo base;
        base.avatarID = 1000 + _monsters.size();
        base.avatarName = "MyLittlePet_";
        base.avatarName += toString(_monsters.size());
        base.modeID = rand()%45+1;
        AvatarPropMap prop;
        auto monster = addEntity(base, prop, ENTITY_CAMP_BLUE, ENTITY_AI);
        _monsters[monster->_entityInfo.eid] = monster;
    }
    for (auto monster: _monsters)
    {
        auto ret = searchPlayer(monster.second->_entityMove.pos);
        if (ret.size() > 0)
        {
            if (monster.second->_entityMove.follow != ret.front()->_entityInfo.eid)
            {
                if (monster.second->_entityMove.follow == InvalidEntityID || realRand() > 0.7)
                {
                    monster.second->_entityMove.follow = ret.front()->_entityInfo.eid;
                }
            }
        }
    }
}

void Scene::doFollow()
{
    for (auto kv: _entitys)
    {
        if (kv.second->_entityMove.follow == InvalidEntityID)
        {
            continue;
        }
        auto entity = kv.second;
        auto follow = getEntity(kv.second->_entityMove.follow);
        if (!follow)
        {
            kv.second->_entityMove.follow = InvalidEntityID;
            continue;
        }
        auto dist = getDistance(entity->_entityMove.pos, follow->_entityMove.pos);
        if (dist > 6.0)
        {
            //auto dst = getFarOffset(entity->_entityMove.pos.x, entity->_entityMove.pos.y, follow->_entityMove.pos.x, follow->_entityMove.pos.y, dist - 5);
            doMove(entity->_entityInfo.eid, MOVE_ACTION_FOLLOW, 0, -1, follow->_entityInfo.eid, entity->_entityMove.pos, follow->_entityMove.pos);
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
        LOGD("MoveReq avatarID[" << avatarID << "] req=" << req);
        if (!doMove(req.eid, (MoveAction)req.action, 0.0, -1, InvalidEntityID, req.clientPos, req.dstPos, avatarID))
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
    else if (rs.getProtoID() == ClientCustomReq::getProtoID())
    {
        ClientCustomReq req;
        rs >> req;
        auto entity = getEntity(req.eid);
        if (entity && entity->_baseInfo.avatarID == avatarID)
        {
            broadcast(ClientCustomNotice(req.eid, req.customID, req.fValue,req.uValue, req.sValue));
        }
        else
        {
            sendToClient(avatarID, ClientCustomResp(EC_ERROR, req.eid, req.customID));
        }
    }
    else if (rs.getProtoID() == ClientPingTestReq::getProtoID())
    {
        ClientPingTestReq req;
        rs >> req;
        sendToClient(avatarID, ClientPingTestResp(EC_ERROR, req.seqID, req.clientTime));
    }
}

bool Scene::doMove(ui64 eid, MoveAction action, double speed, ui64 frames, ui64 follow, EPoint clt, EPoint dst, AvatarID avatarID, bool clean)
{
    auto entity = getEntity(eid);
    if(!entity)
    {
        return false;
    }
    if (avatarID != InvalidAvatarID && (entity->_baseInfo.avatarID != avatarID || entity->_entityInfo.etype == ENTITY_FLIGHT))
    {
        //玩家操作不属于自己控制范围的实体
        return false;
    }
    auto & moveInfo = entity->_entityMove;
    if (moveInfo.action == MOVE_ACTION_PASV_PATH || moveInfo.action == MOVE_ACTION_FORCE_PATH)
    {
        return false;
    }
    
    moveInfo.action = action;
    moveInfo.speed = entity->getSpeed();
    moveInfo.frames = frames;
    moveInfo.follow = follow;
    
    if (clean || action == MOVE_ACTION_IDLE)
    {
        moveInfo.waypoints.clear();
    }
    if (action == MOVE_ACTION_IDLE && entity->_control.agentNo < _sim->getNumAgents())
    {
        _sim->setAgentPrefVelocity(entity->_control.agentNo, RVO::Vector2(0, 0));
    }
    if (action != MOVE_ACTION_IDLE)
    {
        moveInfo.waypoints.insert(moveInfo.waypoints.begin(), dst);
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

std::vector<EntityPtr> Scene::searchPlayer(const EPoint &org)
{
    std::vector<EntityPtr> ret;
    if (_players.empty())
    {
        return ret;
    }
    for (auto entity : _players)
    {
        ret.push_back(entity.second);
    }
    std::sort(ret.begin(), ret.end(), [org](const EntityPtr & entity1, const EntityPtr & entity2)
    {return getDistance(entity1->_entityMove.pos, org) < getDistance(entity2->_entityMove.pos, org); });
    return std::move(ret);
}



