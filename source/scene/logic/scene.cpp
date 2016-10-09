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
    entity->_move.movePath.clear();
    entity->_move.moveAction = MOVE_ACTION_IDLE;

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

    return true;
}

void Scene::doStepRVO()
{
    if (_sim)
    {
        for (size_t i = 0; i < _sim->getNumAgents(); ++i)
        {
            if (true)
            {
                _sim->setAgentPrefVelocity(i, RVO::Vector2(0.0, 0.0));
            }
            else
            {
                _sim->setAgentPrefVelocity(i, RVO::Vector2(0.0, 0.0));
            }
        }
        _sim->doStep();
    }
}
void Scene::onPlayerInstruction(ServiceID avatarID, ReadStream & rs)
{
    if (rs.getProtoID() == MoveReq::getProtoID())
    {
        MoveReq req;
        rs >> req;

    }
}
void Scene::pushAsync(std::function<void()> && func)
{
    _asyncs.push(std::move(func));
}
bool Scene::doMove(ui64 eid, MoveAction action, ui64 follow, EPoint dst, bool clean)
{
    auto entity = getEntity(eid);
    if(!entity)
    {
        return false;
    }
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





