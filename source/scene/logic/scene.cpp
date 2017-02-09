#include "scene.h"
#include "sceneMgr.h"
Scene::Scene(SceneID id)
{
    _sceneID = id;
    _sceneType = SCENE_NONE;
    _sceneStatus = SCENE_STATE_NONE;
}

Scene::~Scene()
{

}
GroupID Scene::getGroupID(ServiceID avatarID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity)
    {
        return entity->_state.groupID;
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
    //放入free列表要先clean, 减小内存占用
    _sceneType = SCENE_NONE;
    _sceneStatus = SCENE_STATE_NONE;
    _lastEID = ServerConfig::getRef().getSceneConfig()._lineID * 1000 + 1000;
    _entitys.clear();
    _players.clear();
    while (!_asyncs.empty()) _asyncs.pop();
    _move.reset();
    _skill.reset();
    _ai.reset();
    return true;
}

bool Scene::initScene(SCENE_TYPE sceneType, MapID mapID)
{
    if (_sceneStatus != SCENE_STATE_NONE)
    {
        LOGE("Scene::loadScene  scene status error");
        return false;
    }

    _sceneType = sceneType;
    _sceneStatus = SCENE_STATE_ACTIVE;

    _lastStatusChangeTime = getFloatSteadyNowTime();

    _lastStatusChangeTime = getFloatSteadyNowTime();
    _startTime = getFloatSteadyNowTime();
    _endTime = getFloatSteadyNowTime() + 600;

    _move = std::make_shared<MoveSync>();
    _move->init(shared_from_this());

    _skill = std::make_shared<Skill>();
    _skill->init(shared_from_this());


    _ai = std::make_shared<AI>();
    _ai->init(shared_from_this());



    //load map
    //load entitys
    onSceneInit();
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



EntityPtr Scene::addEntity(ui64 modelID, ui64 avatarID, std::string avatarName, DictMapKeyValue equips,GroupID groupID)
{
    EntityPtr entity = std::make_shared<Entity>();

    entity->_state.eid = ++_lastEID;
    entity->_state.avatarID = avatarID;
    entity->_state.avatarName = avatarName;
    entity->_state.modelID = modelID;
    entity->_state.camp = 0;
    entity->_state.etype = ENTITY_STATE_ACTIVE;
    entity->_state.groupID = groupID;
    entity->_state.state = ENTITY_STATE_ACTIVE;
    entity->_state.leader = InvalidEntityID;
    entity->_state.foe = InvalidEntityID;

    entity->_state.curHP = entity->_props.hp;

    entity->_control.spawnpoint = { 0.0 - 30 +  realRandF()*30 ,60 -30 + realRandF()*30 };
    entity->_control.eid = entity->_state.eid;
    entity->_control.agentNo = -1;
    entity->_control.stateChageTime = getFloatSteadyNowTime();

    entity->_move.eid = entity->_state.eid;
    entity->_move.position = entity->_control.spawnpoint;
    entity->_move.follow = InvalidEntityID;
    entity->_move.waypoints.clear();
    entity->_move.action = MOVE_ACTION_IDLE;

    entity->_report.eid = entity->_state.eid;

    entity->_control.agentNo = _move->addAgent(entity->_move.position);
    _entitys.insert(std::make_pair(entity->_state.eid, entity));

    if (entity->_state.avatarID != InvalidServiceID && entity->_state.etype == ENTITY_PLAYER)
    {
        _players[entity->_state.avatarID] = entity;
    }


    AddEntityNotice notice;
    notice.entitys.push_back(entity->getFullData());
    broadcast(notice, entity->_state.avatarID);
    onAddEntity(entity);
    return entity;
}
bool Scene::removePlayer(AvatarID avatarID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity)
    {
        return removeEntity(entity->_state.eid);
    }
    return false;
}
bool Scene::removePlayerByGroupID(GroupID groupID)
{
    std::set<EntityID> removes;
    for (auto entity : _entitys)
    {
        if (entity.second->_state.etype == ENTITY_PLAYER && entity.second->_state.groupID == groupID)
        {
            removes.insert(entity.second->_state.eid);
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
    if(_move->isValidAgent(entity->_control.agentNo))
    {
        _move->delAgent(entity->_control.agentNo);
        entity->_control.agentNo = -1;
    }
    if (entity->_state.etype == ENTITY_PLAYER)
    {
        _players.erase(entity->_state.avatarID);
        SceneMgr::getRef().sendToWorld(SceneServerGroupStateChangeIns(getSceneID(), entity->_state.groupID, SCENE_NONE));
    }
    _entitys.erase(eid);

    RemoveEntityNotice notice;
    notice.eids.push_back(eid);
    broadcast(notice);
    onRemoveEntity(entity);
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

    LOGI("Scene::playerAttach avatarName=" << entity->_state.avatarName << " sessionID=" << sID << ", entityID=" << entity->_state.eid);
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
    onPlayerAttach(entity);
    return true;
}



bool Scene::playerDettach(ServiceID avatarID, SessionID sID)
{
    auto entity = getEntityByAvatarID(avatarID);
    if (entity && entity->_clientSessionID == sID)
    {
        LOGI("Scene::playerDettach avatarName=" << entity->_state.avatarName << " sessionID=" << sID << ", entityID=" << entity->_state.eid);
        entity->_clientSessionID = InvalidSessionID;
        onPlayerDettach(entity);
    }
    return true;
}



bool Scene::onUpdate()
{
    if (getFloatSteadyNowTime() > _endTime)
    {
        return false;
    }

    _move->update();
    _skill->update();
    _ai->update();



    SceneRefreshNotice notice;
    for (auto &kv : _entitys)
    {
        if (kv.second->_isInfoDirty)
        {
            notice.entityInfos.push_back(kv.second->_state);
            kv.second->_isInfoDirty = false;
        }
        if (kv.second->_isMoveDirty)
        {
            notice.entityMoves.push_back(kv.second->_move);
            kv.second->_isMoveDirty = false;
        }
    }
    if (!notice.entityInfos.empty() || !notice.entityMoves.empty())
    {
        broadcast(notice);
    }
    while (!_asyncs.empty())
    {
        auto func = _asyncs.front();
        _asyncs.pop();
        func();
    }

    return true;
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
        auto entity = getEntity(req.eid);
        if (!entity || entity->_state.avatarID != avatarID || entity->_state.etype != ENTITY_PLAYER
            || req.action == MOVE_ACTION_PASV_PATH || req.action == MOVE_ACTION_FORCE_PATH 
                    || !_move->doMove(req.eid, (MOVE_ACTION)req.action, entity->getSpeed(), req.follow, req.clientPos, req.waypoints))
        {
            sendToClient(avatarID, MoveResp(EC_ERROR, req.eid, req.action));
        }
    }
    else if (rs.getProtoID() == UseSkillReq::getProtoID())
    {
        UseSkillReq req;
        rs >> req;
        auto entity = getEntity(req.eid);
        if (!entity || entity->_state.avatarID != avatarID || entity->_state.etype != ENTITY_PLAYER
           )
        {
            sendToClient(avatarID, UseSkillResp(EC_ERROR, req.eid, req.skillID, req.foe, req.dst));
        }
    }
    else if (rs.getProtoID() == ClientCustomReq::getProtoID())
    {
        ClientCustomReq req;
        rs >> req;
        auto entity = getEntity(req.eid);
        if (entity && entity->_state.avatarID == avatarID)
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







std::vector<EntityPtr> Scene::searchTarget(EntityPtr caster, double radian, ui64  searchID)
{
    auto founder =  DBDict::getRef().getOneKeyAOESearch(searchID);
    if (!founder.first)
    {
        return std::vector<EntityPtr>();
    }
    return searchTarget(caster, radian, founder.second);
}

std::vector<EntityPtr> Scene::searchTarget(EntityPtr caster, double radian, const AOESearch & search)
{
    EntityPtr master = caster;
    std::vector<EntityPtr> ret;
    if (caster->_state.etype == ENTITY_FLIGHT  && caster->_state.leader != InvalidEntityID)
    {
        auto m = getEntity(caster->_state.leader);
        if (!m)
        {
            LOGE("");
            return ret;
        }
        master = m;
    }
    //偏移修正
    auto org = caster->_move.position;
    if (true)
    {
        auto y = getFarPoint(caster->_move.position.x, caster->_move.position.y, radian, search.offsetY);
        auto x = getFarPoint(std::get<0>(y), std::get<1>(y), fmod(radian+ PI*2.0 - PI/2.0, PI*2.0), search.offsetX);
        org.x = std::get<0>(x);
        org.y = std::get<1>(x);
    }

    for (auto kv : _entitys)
    {
        auto & entity = *(kv.second);
        if (entity._state.etype != ENTITY_PLAYER && entity._state.etype != ENTITY_AI)
        {
            continue;
        }
        if (entity._state.state != ENTITY_STATE_ACTIVE)
        {
            continue;
        }
        if (getBitFlag(search.camp, 1) && entity._state.eid == master->_state.eid)
        {
            ret.push_back(kv.second);
            continue;
        }
        if (search.camp == 0
            ||(getBitFlag(search.camp, 1) && master->_state.eid == entity._state.eid)
            ||(getBitFlag(search.camp, 2)
              && master->_state.camp == entity._state.camp
              && master->_state.eid != entity._state.eid)
            || (getBitFlag(search.camp, 3) && master->_state.camp != entity._state.camp))
        {
            //matched target camp
        }
        else
        {
            continue;
        }
        if (search.etype != ENTITY_NONE)
        {
            if (entity._state.etype != search.etype)
            {
                continue;
            }
        }

        if (getDistance(org, entity._move.position) > search.distance)
        {
            continue;
        }
        if (!search.isRect && search.radian < PI*2.0*0.9)
        {
            double radianEntity = getRadian(org.x, org.y, entity._move.position.x, entity._move.position.y);
            double curRadian = fmod(radian+search.radian/2.0, PI*2.0);
            if ((curRadian >= radianEntity && curRadian - radianEntity < search.radian)
                || (curRadian < radianEntity && curRadian + PI*2.0 - radianEntity < search.radian))
            {

            }
            else
            {
                continue;
            }
        }
        if (search.isRect)
        {
            double curRadian = getRadian(org.x, org.y, entity._move.position.x, entity._move.position.y);
            auto dst = rotatePoint(org.x, org.y, curRadian,
                getDistance(org, entity._move.position), PI*2.0 - curRadian );
            if (abs(std::get<1>(dst) - caster->_move.position.y) > search.radian/2.0)
            {
                continue;
            }
        }
        ret.push_back(kv.second);
    }
    std::sort(ret.begin(), ret.end(), [caster](const EntityPtr & entity1, const EntityPtr & entity2)
    {return getDistance(entity1->_move.position, caster->_move.position) < getDistance(entity2->_move.position, caster->_move.position); });
    while (ret.size() > search.limitEntitys)
    {
        ret.pop_back();
    }
    return std::move(ret);
}

void Scene::onSceneInit()
{

}
void Scene::onAddEntity(EntityPtr entity)
{

}
void Scene::onRemoveEntity(EntityPtr entity)
{

}
void Scene::onPlayerAttach(EntityPtr entity)
{

}
void Scene::onPlayerDettach(EntityPtr entity)
{

}

