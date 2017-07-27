#include "scene.h"
#include "sceneMgr.h"
#include <aoe/aoe.h>
Scene::Scene(SceneID sceneID)
{
    _sceneID = sceneID;
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
    _script.reset();
    return true;
}

bool Scene::initScene(SCENE_TYPE sceneType, MapID mapID)
{
    if (_sceneStatus != SCENE_STATE_NONE)
    {
        LOGE("Scene::loadScene  scene status error");
        return false;
    }

    double now = getFloatNowTime();
    _sceneType = sceneType;
    _mapID = mapID;
    _sceneStatus = SCENE_STATE_ACTIVE;
    _lastEID = ServerConfig::getRef().getSceneConfig()._lineID * 1000 + 1000;

    _startTime = getFloatSteadyNowTime();
    _endTime = getFloatSteadyNowTime() + 600;

    _move = std::make_shared<MoveSync>();
    _move->init(shared_from_this());

    _skill = std::make_shared<Skill>();
    _skill->init(shared_from_this());


    _ai = std::make_shared<AI>();
    _ai->init(shared_from_this());

    _script = std::make_shared<Script>();
    _script->init(shared_from_this());


    //load map
    //load entitys
    onSceneInit();

    LOGD("initScene success. used time=" << getFloatNowTime() - now);
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

    entity->_skillSys.eid = entity->_state.eid;
    return entity;
}

void Scene::addEntity(EntityPtr entity)
{
    entity->_control.agentNo = _move->addAgent(entity->_move.position, entity->_control.collision);

    _entitys.insert(std::make_pair(entity->_state.eid, entity));

    if (entity->_state.avatarID != InvalidServiceID && entity->_state.etype == ENTITY_PLAYER)
    {
        _players[entity->_state.avatarID] = entity;
    }

    LOGD("Scene::addEntity. eid[" << entity->_state.eid << "] aid[" << entity->_state.avatarID << "][" << entity->_state.avatarName
        << "]  modleID=" << entity->_state.modelID << ", camp=" << entity->_state.camp << ", etype=" << entity->_state.etype << ", state=" << entity->_state.state 
        << ", agentNo=" << entity->_control.agentNo  << ", hp=[" << entity->_state.curHP << "/" << entity->_state.maxHP 
        << "], spawnpoint" << entity->_control.spawnpoint<< ", position=" << entity->_move.position);
    AddEntityNotice notice;
    notice.syncs.push_back(entity->getClientSyncData());
    broadcast(notice, entity->_state.avatarID);
    EntityScriptNotice sn;
    sn.controls.push_back(entity->_control);
    sn.skills.push_back(entity->_skillSys);
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
    SceneSectionNotice section;
    getSceneSection(section.section);
    sendToClient(avatarID, section);

    AddEntityNotice notice;
    for (auto & e : _entitys)
    {
        notice.syncs.push_back(e.second->getClientSyncData());
    }
    if (!notice.syncs.empty())
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
    if (getFloatSteadyNowTime() > _endTime || _players.empty())
    {
        return false;
    }

    _move->update();
    _skill->update();
    _ai->update();



    SceneRefreshNotice notice;
    EntityScriptNotice scripts;
    for (auto &kv : _entitys)
    {
        if (kv.second->_isStateDirty)
        {
            notice.entityStates.push_back(kv.second->_state);
            kv.second->_isStateDirty = false;
        }
        if (kv.second->_isMoveDirty)
        {
            notice.entityMoves.push_back(kv.second->_move);
            kv.second->_isMoveDirty = false;
        }
        scripts.controls.push_back(kv.second->_control);
        scripts.skills.push_back(kv.second->_skillSys);
    }
    if (!notice.entityStates.empty() || !notice.entityMoves.empty())
    {
        broadcast(notice);
    }
    
    _script->protoSync(scripts);
    //after flush data
    _script->update();

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
            || (req.action != MOVE_ACTION_IDLE && req.action == MOVE_ACTION_FOLLOW && req.action == MOVE_ACTION_PATH)
            || entity->_state.state != ENTITY_STATE_ACTIVE
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
        if (entity->_skillSys.combating)
        {
            entity->_skillSys.combating = false;
        }

    }
    else if (rs.getProtoID() == UseSkillReq::getProtoID())
    {
        UseSkillReq req;
        rs >> req;
        auto entity = getEntity(req.eid);
        if (!entity || entity->_state.avatarID != avatarID || entity->_state.etype != ENTITY_PLAYER || entity->_state.state != ENTITY_STATE_ACTIVE
            || ! _skill->doSkill(shared_from_this(), req.eid, req.skillID, req.dst)
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







std::vector<std::pair<EntityPtr, double>> Scene::searchTarget(EntityPtr caster, EPosition org, EPosition vt, ui64  searchID)
{
    auto search = DBDict::getRef().getOneKeyAOESearch(searchID);
    if (!search.first)
    {
        LOGE("Scene::searchTarget not found search config. searchID=" << searchID);
        return std::vector<std::pair<EntityPtr, double>>();
    }
    return searchTarget(caster, org, vt, search.second);
}

bool Scene::searchMatched(const EntityPtr & master, const EntityPtr & caster, const EntityPtr & dst, const AOESearch & search)
{
    if (getBitFlag(search.filter, FILTER_SELF) && master && master->_state.eid == dst->_state.eid)
    {
        return true;
    }

    if (search.etype != ENTITY_NONE && search.etype != dst->_state.etype)
    {
        return false;
    }

    if (getBitFlag(search.filter, FILTER_OTHER_FRIEND) && caster->_state.camp == dst->_state.camp)
    {
        if (master && master->_state.eid == dst->_state.eid)
        {
            return false;
        }
        return true;
    }
    if (getBitFlag(search.filter, FILTER_ENEMY_CAMP) && caster->_state.camp != dst->_state.camp && dst->_state.camp < ENTITY_CAMP_NEUTRAL)
    {
        return true;
    }
    if (getBitFlag(search.filter, FILTER_NEUTRAL_CAMP) && dst->_state.camp >= ENTITY_CAMP_NEUTRAL)
    {
        return true;
    }
    return false;
}


std::vector<std::pair<EntityPtr, double>> Scene::searchTarget(EntityPtr caster, EPosition org, EPosition vt, const AOESearch & search)
{
    EntityPtr master = caster;
    if (caster->_state.etype == ENTITY_FLIGHT)
    {
        if (caster->_state.master != InvalidEntityID)
        {
            master = getEntity(caster->_state.master);
        }
        else
        {
            master = nullptr;
        }
    }

    auto ret = searchTarget(org, vt, search.isRect,
        search.value1, search.value2, search.value3, search.compensate, search.clip);
    if (getBitFlag(search.filter, FILTER_SELF) && master)
    {
        if (std::find_if(ret.begin(), ret.end(), [&master](const std::pair<EntityPtr, double> & pr) {return pr.first->_state.eid == master->_state.eid; })
             == ret.end())
        {
            ret.push_back(std::make_pair(master, 0));
        }
    }
    auto beginIter = std::remove_if(ret.begin(), ret.end(), [this, &search, &master, &caster](const std::pair<EntityPtr, double> & e)
    {
        if (searchMatched(master, caster, e.first, search))
        {
            return false;
        }
        return true;
    });
    ret.erase(beginIter, ret.end());
    if (ret.size()> search.limitEntitys)
    {
        ret.resize(search.limitEntitys);
    }
    return ret;
}

std::vector<std::pair<EntityPtr, double>>  Scene::searchTarget(EPosition org, EPosition vt, ui16 isRect, double value1, double value2, double value3, double compensate, double clip)
{
    std::vector<std::pair<EntityPtr, double>> ret;
    vt = normalize(vt);
    org = org + vt*compensate;
    value1 = value1 - compensate;
    AOECheck ac;
    ac.init(toTuple(org), toTuple(vt), isRect != 0, value1, value2, value3, clip);

    for (auto kv : _entitys)
    {
        EPosition pos = kv.second->_move.position;
        if (kv.second->_state.etype != ENTITY_PLAYER && kv.second->_state.etype != ENTITY_AI)
        {
            continue;
        }
        if (kv.second->_state.state != ENTITY_STATE_ACTIVE)
        {
            continue;
        }
        auto cRet = ac.check(toTuple(pos), kv.second->_control.collision);
        if (std::get<0>(cRet))
        {
            ret.push_back(std::make_pair(kv.second, std::get<1>(cRet)));
        }
    }
    std::sort(ret.begin(), ret.end(), [org](const std::pair<EntityPtr, double> & e1, const std::pair<EntityPtr, double> & e2){return e1.second < e2.second; });
    return ret;
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

