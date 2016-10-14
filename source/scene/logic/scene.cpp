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
    _sim->setAgentDefaults(5.0, 2, 3.0, 1.0, 2.0, 7.0);
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



    entity->_info.eid = ++_lastEID;
    entity->_info.color = camp;
    entity->_info.etype = etype;
    entity->_info.groupID = groupID;
    entity->_info.state = ENTITY_STATE_ACTIVE;
    entity->_info.leader = InvalidEntityID;
    entity->_info.foe = InvalidEntityID;

    entity->_info.curHP = 100;

    entity->_control.spawnpoint = { 0.0 - 30 +  realRandF()*30 ,60 -30 + realRandF()*30 };
    entity->_control.eid = entity->_info.eid;
    entity->_control.agentNo = -1;
    entity->_control.stateChageTick = getFloatSteadyNowTime();

    entity->_move.eid = entity->_info.eid;
    entity->_move.pos = entity->_control.spawnpoint;
    entity->_move.follow = InvalidEntityID;
    entity->_move.waypoints.clear();
    entity->_move.action = MOVE_ACTION_IDLE;

    entity->_report.eid = entity->_info.eid;

    entity->_control.agentNo = _sim->addAgent(toRVOVector2(entity->_move.pos));

    _entitys.insert(std::make_pair(entity->_info.eid, entity));

    if (baseInfo.avatarID != InvalidServiceID && etype == ENTITY_AVATAR)
    {
        _players[baseInfo.avatarID] = entity;
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
        return removeEntity(entity->_info.eid);
    }
    return false;
}
bool Scene::removePlayerByGroupID(GroupID groupID)
{
    std::set<EntityID> removes;
    for (auto entity : _entitys)
    {
        if (entity.second->_info.etype == ENTITY_AVATAR && entity.second->_info.groupID == groupID)
        {
            removes.insert(entity.second->_info.eid);
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
    if (entity->_info.etype == ENTITY_AVATAR)
    {
        _players.erase(entity->_baseInfo.avatarID);
        SceneMgr::getRef().sendToWorld(SceneServerGroupStateChangeIns(getSceneID(), entity->_info.groupID, SCENE_NONE));
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

    LOGI("Scene::playerAttach avatarName=" << entity->_baseInfo.avatarName << " sessionID=" << sID << ", entityID=" << entity->_info.eid);
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
        LOGI("Scene::playerDettach avatarName=" << entity->_baseInfo.avatarName << " sessionID=" << sID << ", entityID=" << entity->_info.eid);
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
            notice.entityInfos.push_back(kv.second->_info);
            kv.second->_isInfoDirty = false;
        }
        if (kv.second->_isMoveDirty)
        {
            notice.entityMoves.push_back(kv.second->_move);
            kv.second->_isMoveDirty = false;
            LOGD("Scene::onUpdate avatarName=" << kv.second->_baseInfo.avatarName <<  ", EntityMove=" << kv.second->_move);
        }
    }
    if (!notice.entityInfos.empty() || !notice.entityMoves.empty())
    {
        broadcast(notice);
    }
    return true;
}

void Scene::preStepRVO(bool onlyCheck)
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
                while (!entity._move.waypoints.empty() 
                    && (getDistance(entity._move.pos, entity._move.waypoints.front()) < 1.0 || (getDistance(entity._move.pos, entity._move.waypoints.front()) < 5.0 && entity._move.action == MOVE_ACTION_FOLLOW)) )
                {
                    entity._move.waypoints.erase(entity._move.waypoints.begin());
                }
                if (entity._move.waypoints.empty())
                {
                    entity._move.action = MOVE_ACTION_IDLE;
                    break;
                }
                if (onlyCheck)
                {
                    break;
                }
                _sim->setAgentMaxSpeed(entity._control.agentNo, entity._move.speed);
                double dist = getDistance(entity._move.pos, entity._move.waypoints.front());
                double needTime = dist / entity._move.speed;
                RVO::Vector2 dir = RVO::normalize(toRVOVector2(entity._move.waypoints.front()) - toRVOVector2(entity._move.pos));
                if (needTime > SceneFrameInterval)
                {
                    dir *= entity._move.speed;
                }
                else
                {
                    dir *= needTime / SceneFrameInterval;
                }
                _sim->setAgentPrefVelocity(entity._control.agentNo, dir);
                LOGD("RVO PRE MOVE[" << entity._baseInfo.avatarName << "] local=" << entity._move.pos << ", dst=" << entity._move.waypoints.front() << ", dir=" << dir);
            } while (false);

            if (entity._move.action == MOVE_ACTION_IDLE)
            {
                entity._move.waypoints.clear();
                _sim->setAgentPrefVelocity(entity._control.agentNo, RVO::Vector2(0, 0));
                broadcast(MoveNotice(entity._move));
                LOGD("RVO FIN MOVE[" << entity._baseInfo.avatarName << "] local=" << entity._move.pos);
            }
            entity._isMoveDirty = true;
        }
    }
}
void Scene::doStepRVO()
{
    preStepRVO(false);
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
            if (!entity._isMoveDirty)
            {
                continue;
            }
            auto cur = _sim->getAgentPosition(entity._control.agentNo);
            entity._move.pos.x = cur.x();
            entity._move.pos.y = cur.y();
            LOGD("RVO AFT MOVE[" << entity._baseInfo.avatarName << "] local=" << entity._move.pos);
        }
    }
    preStepRVO(true);
}


void Scene::doMonster()
{
    while (_monsters.size() < _players.size() * 3 )
    {
        AvatarBaseInfo base;
        base.avatarID = 1000 + _monsters.size();
        base.avatarName = "MyLittleBeetle_";
        base.avatarName += toString(_monsters.size());
        base.modeID = 20;
        AvatarPropMap prop;
        auto monster = addEntity(base, prop, ENTITY_CAMP_BLUE, ENTITY_AI);
        _monsters[monster->_info.eid] = monster;
    }
    for (auto monster: _monsters)
    {
        auto ret = searchPlayer(monster.second->_move.pos);
        if (ret.size() > 0)
        {
            monster.second->_move.follow = ret.front()->_info.eid;
        }
    }
}

void Scene::doFollow()
{
    for (auto kv: _entitys)
    {
        if (kv.second->_move.follow == InvalidEntityID)
        {
            continue;
        }
        auto entity = kv.second;
        auto follow = getEntity(kv.second->_move.follow);
        if (!follow)
        {
            kv.second->_move.follow = InvalidEntityID;
            continue;
        }
        auto dist = getDistance(entity->_move.pos, follow->_move.pos);
        if (dist > 6.0)
        {
            //auto dst = getFarOffset(entity->_move.pos.x, entity->_move.pos.y, follow->_move.pos.x, follow->_move.pos.y, dist - 5);
            doMove(entity->_info.eid, MOVE_ACTION_FOLLOW, 0, -1, follow->_info.eid, entity->_move.pos, follow->_move.pos);
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
    {return getDistance(entity1->_move.pos, org) < getDistance(entity2->_move.pos, org); });
    return std::move(ret);
}



