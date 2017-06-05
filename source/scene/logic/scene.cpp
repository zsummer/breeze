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

    entity->_control.agentNo = RVO::RVO_ERROR;
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


    AddEntityNotice notice;
    notice.syncs.push_back(entity->getClientSyncData());
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
    if (getFloatSteadyNowTime() > _endTime)
    {
        return false;
    }

    _move->update();
    _skill->update();
    _ai->update();



    SceneRefreshNotice notice;
    EntityControlNotice controls;
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
        if (kv.second->_isControlDirty)
        {
            kv.second->_isControlDirty = false;
            controls.controls.push_back(kv.second->_control);
        }
    }
    if (!notice.entityStates.empty() || !notice.entityMoves.empty())
    {
        broadcast(notice);
    }
    if (!controls.controls.empty())
    {
        _script->protoSync(controls);
    }
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
            || req.action == MOVE_ACTION_PASV_PATH || req.action == MOVE_ACTION_FORCE_PATH 
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
        if (!entity || entity->_state.avatarID != avatarID || entity->_state.etype != ENTITY_PLAYER || entity->_state.state != ENTITY_STATE_ACTIVE
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

std::vector<std::pair<EntityPtr, double>> Scene::searchTarget(EntityPtr caster, EPosition org, EPosition vt, const AOESearch & search)
{
    EntityPtr master = caster;
    if (caster->_state.etype == ENTITY_FLIGHT && caster->_state.master != InvalidEntityID)
    {
        master = getEntity(caster->_state.master);
    }

    auto ret = searchTarget(org, vt, search.isRect,
        search.value1, search.value2, search.value3, search.compensate, search.clip);
    auto beginIter = std::remove_if(ret.begin(), ret.end(), [&search, master, caster](const std::pair<EntityPtr, double> & e)
    {
        if (search.etype != ENTITY_NONE && search.etype != e.first->_state.etype)
        {
            return true;
        }

        if (getBitFlag(search.filter, FILTER_SELF) && master && master->_state.eid == e.first->_state.eid)
        {
            return false;
        }

        if (getBitFlag(search.filter, FILTER_OTHER_FRIEND) && caster->_state.camp == e.first->_state.camp)
        {
            if (master && master->_state.eid == e.first->_state.eid)
            {
                return true;
            }
            return false;
        }

        if (getBitFlag(search.filter, FILTER_ENEMY_CAMP) && caster->_state.camp != e.first->_state.camp && e.first->_state.camp < ENTITY_CAMP_NEUTRAL)
        {
            return false;
        }
        if (getBitFlag(search.filter, FILTER_NEUTRAL_CAMP) && e.first->_state.camp > ENTITY_CAMP_NEUTRAL)
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
    org = org - vt*compensate;
    value1 = value1 + compensate;
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

