#include "scene.h"
#include "sceneMgr.h"
Scene::Scene(SceneID id)
{
    _sceneID = id;
    cleanScene();
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
    return true;
}

bool Scene::initScene(SCENE_TYPE sceneType, MapID mapID)
{
    if (_sceneStatus != SCENE_STATUS_NONE)
    {
        LOGE("Scene::loadScene  scene status error");
        return false;
    }
    _sceneType = sceneType;
    _sceneStatus = SCENE_STATUS_ACTIVE;
    _lastStatusChangeTime = getFloatNowTime();
    _startTime = getFloatNowTime();
    _endTime = getFloatNowTime() + 600;
    
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
    entity->_control.stateChageTick = getFloatNowTime();

    entity->_point.eid = entity->_info.eid;
    entity->_point.pos = entity->_control.spawnpoint;
    entity->_point.follow = InvalidEntityID;
    entity->_point.movePath.clear();
    entity->_point.moveAction = MACTION_IDLE;

    entity->_report.eid = entity->_info.eid;


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







