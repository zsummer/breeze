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
    _sceneType = SCENE_TYPE_NONE;
    _sceneStatus = SCENE_STATUS_NONE;
    _lastStatusChangeTime = getFloatNowTime();
    if (_sim)
    {
        delete _sim;
        _sim = nullptr;
    }
    while (!_freeAgentNo.empty()) _freeAgentNo.pop();

    return true;
}

bool Scene::initScene(SCENE_TYPE sceneType, MapID mapID)
{
    if (_sceneStatus != SCENE_STATUS_NONE || _sim)
    {
        LOGE("Scene::loadScene  scene status error");
        return false;
    }
    _sceneType = sceneType;
    _sceneStatus = SCENE_STATUS_ACTIVE;
    _lastStatusChangeTime = getFloatNowTime();
    _startTime = getFloatNowTime();
    _endTime = getFloatNowTime() + 600;
    _sim = new RVO::RVOSimulator();
    _sim->setTimeStep(0.33f);
    _sim->setAgentDefaults(15.0f, 10, 10.0f, 5.0f, 2.0f, 2.0f);
    if (true)
    {
        std::vector<RVO::Vector2> vertices;
        vertices.push_back(RVO::Vector2(-7.0f, -20.0f));
        vertices.push_back(RVO::Vector2(7.0f, -20.0f));
        vertices.push_back(RVO::Vector2(7.0f, 20.0f));
        vertices.push_back(RVO::Vector2(-7.0f, 20.0f));
        _sim->addObstacle(vertices);
        _sim->processObstacles();
    }

    //load map
    //load entitys

    return true;
}


bool Scene::onUpdate()
{
    if (getFloatNowTime() > _endTime)
    {
        return false;
    }
    if (_sim)
    {
        for (size_t i = 0; i < _sim->getNumAgents() ; ++i)
        {
             if(true)
             {
                 _sim->setAgentPrefVelocity(i, RVO::Vector2(0.0f, 0.0f));
             }
             else
             {
                 _sim->setAgentPrefVelocity(i, RVO::Vector2(0.0f, 0.0f));
             }
        }
        _sim->doStep();
    }

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

// void Scene::fillUserProp(const FillUserToSceneReq& req)
// {
//     auto entity = getUserEntity(req.baseInfo.avatarID);
//     if (entity)
//     {
//         LOGE("already had");
//         return;
//     }
//     entity = makeNewEntity(req.baseInfo);
//     entity->_token = req.token;
//     entity->_info.state = ESTATE_FREEZING;
//     entity->_isClientDirty = true;
// }

EntityPtr Scene::addEntity(const AvatarBaseInfo & baseInfo,
    const AvatarPropMap & baseProps,
    ENTITY_COLOR ecolor,
    ENTITY_TYPE etype,
    ENTITY_STATE state,
    GroupID groupID)
{
    EntityPtr entity = std::make_shared<Entity>();

    entity->_baseInfo = baseInfo;
    entity->_baseProps = baseProps;



    entity->_info.eid = ++_lastEID;
    entity->_info.color = ecolor;
    entity->_info.etype = etype;
    entity->_info.groupID = groupID;
    entity->_info.state = ESTATE_ACTIVE;
    entity->_info.leader = InvalidEntityID;
    entity->_info.foe = InvalidEntityID;

    entity->_info.curHP = 100;

    entity->_control.spawnpoint = { 0.0,0.0 };
    entity->_control.eid = entity->_info.eid;
    entity->_control.agentNo = -1;
    entity->_control.stateChageTick = getFloatNowTime();

    entity->_point.eid = entity->_info.eid;
    entity->_point.pos = entity->_control.spawnpoint;
    entity->_point.follow = InvalidEntityID;
    entity->_point.movePath.clear();
    entity->_point.moveAction = MACTION_IDLE;

    entity->_report.eid = entity->_info.eid;

    size_t agentNo = -1;
    if (_freeAgentNo.empty())
    {
        agentNo = _sim->addAgent(RVO::Vector2(entity->_point.pos.x, entity->_point.pos.y));
    }
    else
    {
        agentNo = _freeAgentNo.front();
        _freeAgentNo.pop();
        _sim->setAgentPosition(agentNo, RVO::Vector2(entity->_point.pos.x, entity->_point.pos.y));
    }
    entity->_control.agentNo = agentNo;
    _entitys.insert(std::make_pair(entity->_info.eid, entity));

    if (baseInfo.avatarID != InvalidServiceID)
    {
        _players[baseInfo.avatarID] = entity;
    }

    AddEntityNotice notice;
    notice.entitys.push_back(entity->getFullData());
    notice.serverTime = getFloatNowTime();
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
    if(entity->_control.agentNo != -1  && entity->_control.agentNo < _sim->getNumAgents())
    {
        _freeAgentNo.push(entity->_control.agentNo);
        _sim->setAgentPosition(entity->_control.agentNo, RVO::Vector2(1E20, 1E20*entity->_control.agentNo));
    }
    if (entity->_info.etype == ETYPE_AVATAR)
    {
        _players.erase(entity->_baseInfo.avatarID);
    }
    _entitys.erase(eid);

    RemoveEntityNotice notice;
    notice.eids.push_back(eid);
    notice.serverTime = getFloatNowTime();
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







