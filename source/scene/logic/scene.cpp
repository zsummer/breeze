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

bool Scene::initScene(SceneType sceneType, MapID mapID)
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



EntityPtr Scene::addEntity(const EntityBase & baseInfo,
    const EntityProp & fixedProps,
    const EntityProp & growProps,
    const EntityProp & growth,
    GroupID groupID)
{
    EntityPtr entity = std::make_shared<Entity>();

    entity->_baseInfo = baseInfo;


    entity->_props = fixedProps + growProps * (growth * baseInfo.level);
    

    entity->_entityInfo.eid = ++_lastEID;
    entity->_entityInfo.camp = baseInfo.camp;
    entity->_entityInfo.etype = baseInfo.etype;
    entity->_entityInfo.groupID = groupID;
    entity->_entityInfo.state = baseInfo.state;
    entity->_entityInfo.leader = InvalidEntityID;
    entity->_entityInfo.foe = InvalidEntityID;

    entity->_entityInfo.curHP = entity->_props.hp;

    entity->_control.spawnpoint = { 0.0 - 30 +  realRandF()*30 ,60 -30 + realRandF()*30 };
    entity->_control.eid = entity->_entityInfo.eid;
    entity->_control.agentNo = -1;
    entity->_control.stateChageTime = getFloatSteadyNowTime();

    entity->_entityMove.eid = entity->_entityInfo.eid;
    entity->_entityMove.position = entity->_control.spawnpoint;
    entity->_entityMove.follow = InvalidEntityID;
    entity->_entityMove.waypoints.clear();
    entity->_entityMove.action = MOVE_ACTION_IDLE;

    entity->_report.eid = entity->_entityInfo.eid;

    entity->_control.agentNo = _move->addAgent(entity->_entityMove.position);
    _entitys.insert(std::make_pair(entity->_entityInfo.eid, entity));

    if (baseInfo.avatarID != InvalidServiceID && entity->_entityInfo.etype == ENTITY_PLAYER)
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
        return removeEntity(entity->_entityInfo.eid);
    }
    return false;
}
bool Scene::removePlayerByGroupID(GroupID groupID)
{
    std::set<EntityID> removes;
    for (auto entity : _entitys)
    {
        if (entity.second->_entityInfo.etype == ENTITY_PLAYER && entity.second->_entityInfo.groupID == groupID)
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
    if(_move->isValidAgent(entity->_control.agentNo))
    {
        _move->delAgent(entity->_control.agentNo);
        entity->_control.agentNo = -1;
    }
    if (entity->_entityInfo.etype == ENTITY_PLAYER)
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


    _move->update();
    _skill->update();
    _ai->update();



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
        if (!entity || entity->_baseInfo.avatarID != avatarID || entity->_entityInfo.etype != ENTITY_PLAYER 
            || req.action == MOVE_ACTION_PASV_PATH || req.action == MOVE_ACTION_FORCE_PATH 
                    || !_move->doMove(req.eid, (MoveAction)req.action, entity->getSpeed(), req.follow, req.clientPos, req.waypoints))
        {
            sendToClient(avatarID, MoveResp(EC_ERROR, req.eid, req.action));
        }
    }
    else if (rs.getProtoID() == UseSkillReq::getProtoID())
    {
        UseSkillReq req;
        rs >> req;
        auto entity = getEntity(req.eid);
        if (!entity || entity->_baseInfo.avatarID != avatarID || entity->_entityInfo.etype != ENTITY_PLAYER
            ||!_skill->trigger(req.eid, req.skillID, req.foe, req.dst))
        {
            sendToClient(avatarID, UseSkillResp(EC_ERROR, req.eid, req.skillID, req.foe, req.dst));
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









std::vector<EntityPtr> Scene::searchTarget(EntityPtr caster, double radian, const SearchInfo & search)
{
    EntityPtr master = caster;
    std::vector<EntityPtr> ret;
    if (caster->_entityInfo.etype == ENTITY_FLIGHT  && caster->_entityInfo.leader != InvalidEntityID)
    {
        auto m = getEntity(caster->_entityInfo.leader);
        if (!m)
        {
            LOGE("");
            return ret;
        }
        master = m;
    }
    //偏移修正
    auto org = caster->_entityMove.position;
    if (true)
    {
        auto y = getFarPoint(caster->_entityMove.position.x, caster->_entityMove.position.y, radian, search.offsetY);
        auto x = getFarPoint(std::get<0>(y), std::get<1>(y), fmod(radian+ PI*2.0 - PI/2.0, PI*2.0), search.offsetX);
        org.x = std::get<0>(x);
        org.y = std::get<1>(x);
    }

    for (auto kv : _entitys)
    {
        auto & entity = *(kv.second);
        if (entity._entityInfo.etype != ENTITY_PLAYER && entity._entityInfo.etype != ENTITY_AI)
        {
            continue;
        }
        if (entity._entityInfo.state != ENTITY_STATE_ACTIVE)
        {
            continue;
        }
        if (getBitFlag(search.camp, SEARCH_CAMP_SELF) && entity._entityInfo.eid == master->_entityInfo.eid)
        {
            ret.push_back(kv.second);
            continue;
        }
        if (search.camp == SEARCH_CAMP_NONE
            ||(getBitFlag(search.camp, SEARCH_CAMP_SELF) && master->_entityInfo.eid == entity._entityInfo.eid)
            ||(getBitFlag(search.camp, SEARCH_CAMP_SAME_WITHOUT_SELF)
              && master->_entityInfo.camp == entity._entityInfo.camp
              && master->_entityInfo.eid != entity._entityInfo.eid)
            || (getBitFlag(search.camp, SEARCH_CAMP_ALIEN) && master->_entityInfo.camp != entity._entityInfo.camp))
        {
            //matched target camp
        }
        else
        {
            continue;
        }
        if (search.etype != ENTITY_NONE)
        {
            if (entity._entityInfo.etype != search.etype)
            {
                continue;
            }
        }

        if (getDistance(org, entity._entityMove.position) > search.distance)
        {
            continue;
        }
        if (search.method == SEARCH_METHOD_SEACTOR && search.radian < PI*2.0*0.9)
        {
            double radianEntity = getRadian(org.x, org.y, entity._entityMove.position.x, entity._entityMove.position.y);
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
        if (search.method == SEARCH_METHOD_RECT)
        {
            double curRadian = getRadian(org.x, org.y, entity._entityMove.position.x, entity._entityMove.position.y);
            auto dst = rotatePoint(org.x, org.y, curRadian,
                getDistance(org, entity._entityMove.position), PI*2.0 - curRadian );
            if (abs(std::get<1>(dst) - caster->_entityMove.position.y) > search.radian/2.0)
            {
                continue;
            }
        }
        ret.push_back(kv.second);
    }
    std::sort(ret.begin(), ret.end(), [caster](const EntityPtr & entity1, const EntityPtr & entity2)
    {return getDistance(entity1->_entityMove.position, caster->_entityMove.position) < getDistance(entity2->_entityMove.position, caster->_entityMove.position); });
    while (ret.size() > search.limitEntitys)
    {
        ret.pop_back();
    }
    return std::move(ret);
}



