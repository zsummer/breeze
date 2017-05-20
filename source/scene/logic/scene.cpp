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


EntityPtr Scene::makeEntity(ui64 modelID, ui64 avatarID, std::string avatarName, DictArrayKey equips,GroupID groupID)
{

    EntityPtr entity = std::make_shared<Entity>();

    entity->_props = DictProp();
    entity->_state.curHP = entity->_props.hp;


    entity->_state.eid = ++_lastEID;
    entity->_state.avatarID = avatarID;
    entity->_state.avatarName = avatarName;
    entity->_state.modelID = modelID;
    entity->_state.groupID = groupID;

    entity->_state.camp = ENTITY_CAMP_NONE;
    entity->_state.etype = avatarID == InvalidAvatarID ? ENTITY_AI : ENTITY_PLAYER;

    entity->_state.state = ENTITY_STATE_ACTIVE;

    entity->_state.master = InvalidEntityID;
    entity->_state.foe = InvalidEntityID;

    

    entity->_control.spawnpoint = { 0.0 - 30 +  realRandF()*30 ,60 -30 + realRandF()*30 };
    entity->_control.eid = entity->_state.eid;
    entity->_control.agentNo = RVO::RVO_ERROR;
    entity->_control.stateChageTime = getFloatSteadyNowTime();

    entity->_move.eid = entity->_state.eid;
    entity->_move.position = entity->_control.spawnpoint;
    entity->_move.follow = InvalidEntityID;
    entity->_move.waypoints.clear();
    entity->_move.action = MOVE_ACTION_IDLE;

    entity->_report.eid = entity->_state.eid;

    entity->_control.agentNo = RVO::RVO_ERROR;
    return entity;
}

void Scene::addEntity(EntityPtr entity)
{
    entity->_control.agentNo = _move->addAgent(entity->_move.position, entity->_state.collision);

    _entitys.insert(std::make_pair(entity->_state.eid, entity));

    if (entity->_state.avatarID != InvalidServiceID && entity->_state.etype == ENTITY_PLAYER)
    {
        _players[entity->_state.avatarID] = entity;
    }


    AddEntityNotice notice;
    notice.entitys.push_back(entity->getFullData());
    broadcast(notice, entity->_state.avatarID);
    onAddEntity(entity);
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
        entity->_control.agentNo = RVO::RVO_ERROR;
    }
    if (entity->_state.etype == ENTITY_PLAYER)
    {
        _players.erase(entity->_state.avatarID);
        SceneMgr::getRef().sendToWorld(SceneServerGroupStateFeedback(getSceneID(), entity->_state.groupID, SCENE_NONE));
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
            notice.entityStates.push_back(kv.second->_state);
            kv.second->_isInfoDirty = false;
        }
        if (kv.second->_isMoveDirty)
        {
            notice.entityMoves.push_back(kv.second->_move);
            kv.second->_isMoveDirty = false;
        }
    }
    if (!notice.entityStates.empty() || !notice.entityMoves.empty())
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
                    )
        {
            sendToClient(avatarID, MoveResp(EC_ERROR, req.eid, req.action));
            return;
        }
        if (!_move->doMove(req.eid, (MOVE_ACTION)req.action, entity->getSpeed(), req.follow, req.waypoints))
        {
            sendToClient(avatarID, MoveResp(EC_ERROR, req.eid, req.action));
            return;
        }
        if (entity->_skillSys.autoAttack)
        {
            entity->_skillSys.autoAttack = false;
        }

    }
    else if (rs.getProtoID() == UseSkillReq::getProtoID())
    {
        UseSkillReq req;
        rs >> req;
        auto entity = getEntity(req.eid);
        if (!entity || entity->_state.avatarID != avatarID || entity->_state.etype != ENTITY_PLAYER 
            || ! _skill->useSkill(shared_from_this(), req.eid, req.skillID, req.dst, req.foeFirst)
           )
        {
            sendToClient(avatarID, UseSkillResp(EC_ERROR, req.eid, req.skillID,  req.dst, req.foeFirst));
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







std::vector<EntityPtr> Scene::searchTarget(EntityPtr caster, EPosition org, double radian, ui64  searchID)
{
    auto search = DBDict::getRef().getOneKeyAOESearch(searchID);
    if (!search.first)
    {
        LOGE("Scene::searchTarget not found search config. searchID=" << searchID);
        return std::vector<EntityPtr>();
    }
    return searchTarget(caster, org, radian, search.second);
}

std::vector<EntityPtr> Scene::searchTarget(EntityPtr caster, EPosition org, double radian, const AOESearch & search)
{
    EntityPtr master = caster;
    if (caster->_state.etype == ENTITY_FLIGHT && caster->_state.master != InvalidEntityID)
    {
        master = getEntity(caster->_state.master);
    }

    auto ret = searchTarget(org, radian, search.isRect,
        search.distance, search.value, search.compensateForward, search.compensateRight);

    std::vector<EntityPtr> filtered;
    for (auto e : ret)
    {
        if (filtered.size() >= search.limitEntitys)
        {
            break;
        }
        if (search.etype != ENTITY_NONE && search.etype != e->_state.etype)
        {
            continue;
        }

        if (getBitFlag(search.filter, FILTER_SELF) && master && master->_state.eid == e->_state.eid)
        {
            filtered.push_back(e);
            continue;
        }
        if (getBitFlag(search.filter, FILTER_OTHER_FRIEND) &&  caster->_state.camp == e->_state.camp)
        {
            if (master && master->_state.eid == e->_state.eid)
            {
                continue;
            }
            filtered.push_back(e);
            continue;
        }
        if (getBitFlag(search.filter, FILTER_ENEMY_CAMP) && caster->_state.camp != e->_state.camp && e->_state.camp < ENTITY_CAMP_NEUTRAL)
        {
            filtered.push_back(e);
            continue;
        }
        if (getBitFlag(search.filter, FILTER_ENEMY_CAMP) && caster->_state.camp != e->_state.camp && e->_state.camp > ENTITY_CAMP_NEUTRAL)
        {
            filtered.push_back(e);
            continue;
        }
    }
    return std::move(filtered);
}

std::vector<EntityPtr> Scene::searchTarget(EPosition org, EPosition vt, ui16 isRect, double value1, double value2, double value3, double compensate, double clip)
{
    std::vector<EntityPtr> ret;
    org = org + vt*compensate;
    value1 = value1 + compensate;
    EPosition orgc = org + vt*clip;
    if (clip != 0.0 && (isRect || value2 > PI*2*0.9))
    {
        LOGE("searchTarget not support clip when rect or circle");
    }
    double areaDistance= value1;
    if (isRect)
    {
        double v = std::max(value2, value3)/2.0;
        areaDistance = std::sqrt(v*v + value1*value1);
    }

    std::vector<EPosition> convexs;
    EPosition bot;
    EPosition top;

    if (isRect)
    {
        EPosition rvt = toEPosition(rotateVertical(vt.x, vt.y, true));
        convexs.push_back(org + rvt*value3 / 2.0);
        convexs.push_back(org + vt * value1 + rvt*value3 / 2.0);
        convexs.push_back(org + vt * value1 - rvt*value3 / 2.0);
        convexs.push_back(org - rvt*value3 / 2.0);
        for (size_t i = 0; i < convexs.size(); i++)
        {
            bot.x = std::min(bot.x, convexs[i].x);
            bot.y = std::min(bot.y, convexs[i].y);
            top.x = std::max(top.x, convexs[i].x);
            top.y = std::max(top.y, convexs[i].y);
        }
    }

    for (auto kv : _entitys)
    {
        EPosition dstPos = kv.second->_move.position;
        double distance = getDistance(org, dstPos) - kv.second->_state.collision;
        if (distance > areaDistance)
        {
            continue;
        }

        //circle 
        if (!isRect && value2 > PI * 2.0 * 0.9)
        {
            /*
            //small clip
            if (clip != 0.0 && getDistance(orgc, entity._move.position) < clip)
            {
                continue;
            }
            // big clip 
            if (clip != 0.0 && getDistance(orgc, entity._move.position) < value1)
            {
                continue;
            }
            */
            ret.push_back(kv.second);
            continue;
        }
        //radian 
        if (!isRect)
        {
            //clip
            if (clip != 0.0 && distance < clip)
            {
                continue;
            }
            double r = getRadian(dstPos - orgc, vt);
            if (r < value2/2.0)
            {
                ret.push_back(kv.second);
            }
            continue;
        }
        if (isRect)
        {
            if (convexs.size() < 3 )
            {
                LOGE("");
                continue;
            }
            //fast check
            if (dstPos.x < bot.x || dstPos.y < bot.y || dstPos.x > top.x || dstPos.y > top.y)
            {
                continue;
            }
            bool prime = false;
            for (int i = 0, j = convexs.size() - 1; i < convexs.size(); j = i++) 
            {
                if (((convexs[i].y > dstPos.y) != (convexs[j].y > dstPos.y)) 
                    &&
                    (dstPos.x < (convexs[j].x - convexs[i].x) * (dstPos.y - convexs[i].y)  / (convexs[j].y - convexs[i].y) + convexs[i].x))
                    prime = !prime;
            }
            if (prime)
            {
                ret.push_back(kv.second);
            }
            continue;
        }
    }
    std::sort(ret.begin(), ret.end(), [org](const EntityPtr & entity1, const EntityPtr & entity2)
    {return getDistance(org, entity1->_move.position) < getDistance(org, entity2->_move.position); });
    return ret;
}

std::vector<EntityPtr> Scene::searchTarget(EPosition org, double radian, ui16 isRect, double distance, double value, double compensateForward, double compensateRight)
{
    //位移补偿
    if (true)
    {
        auto ofstForward = getFarPoint(org.x, org.y, radian, compensateForward);
        auto ofstRight = getFarPoint(std::get<0>(ofstForward), std::get<1>(ofstForward), fmod(radian+ PI*2.0 - PI/2.0, PI*2.0), compensateRight);
        distance += getDistance(org.x, org.y, std::get<0>(ofstRight), std::get<1>(ofstRight));
        org.x = std::get<0>(ofstRight);
        org.y = std::get<1>(ofstRight);
    }

    std::vector<EntityPtr> ret;

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
        
        if (getDistance(org, entity._move.position) > distance)
        {
            continue;
        }
        if (!isRect && value < PI*2.0*0.9)
        {
            double radianEntity = getRadian(entity._move.position.x - org.x, entity._move.position.y - org.y);
            double curRadian = fmod(radian+value/2.0, PI*2.0);
            if ((curRadian >= radianEntity && curRadian - radianEntity < value)
                || (curRadian < radianEntity && curRadian + PI*2.0 - radianEntity < value))
            {

            }
            else
            {
                continue;
            }
        }
        if (isRect)
        {
            double curRadian = getRadian(entity._move.position.x - org.x, entity._move.position.y - org.y);
  
        }
        ret.push_back(kv.second);
    }
    std::sort(ret.begin(), ret.end(), [org](const EntityPtr & entity1, const EntityPtr & entity2)
    {return getDistance(org, entity1->_move.position) < getDistance(org, entity2->_move.position); });
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

