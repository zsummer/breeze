#include "scene.h"
#include "sceneMgr.h"
Scene::Scene(SceneID id)
{
    _sceneID = id;
    cleanScene();
}
bool Scene::cleanScene()
{
    _lastEID = ServerConfig::getRef().getSceneConfig()._sceneID * 1000 + 1000;
    _entitys.clear();
    _players.clear();
    _sceneType = SCENE_TYPE_NONE;
    _sceneStatus = SCENE_STATUS_NONE;
    _lastStatusChangeTime = getFloatNowTime();
    SceneMgr::getRef().refreshSceneStatusToWorld(getSceneID());
    return true;
}

bool Scene::loadScene(SCENE_TYPE sceneType)
{
    if (_sceneStatus != SCENE_STATUS_NONE)
    {
        LOGE("Scene::loadScene  scene status error");
        return false;
    }
    _sceneType = sceneType;
    _sceneStatus = SCENE_STATUS_WAIT;
    _lastStatusChangeTime = getFloatNowTime();
    _startTime = getFloatNowTime();
    _endTime = getFloatNowTime() + 3600;
    
    //load map
    //load entitys
    SceneMgr::getRef().refreshSceneStatusToWorld(getSceneID());
    return true;
}


bool Scene::onUpdate()
{
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
EntityPtr Scene::getUserEntity(ServiceID avatarID)
{
    auto founder = _players.find(avatarID);
    if (founder == _players.end())
    {
        return nullptr;
    }
    return founder->second;
}

EntityPtr Scene::makeNewEntity(const AvatarBaseInfo & base)
{
    EntityPtr entity = std::make_shared<Entity>();
    entity->_base = base;
    entity->_control.spawnpoint = { 0.0,0.0 };
    entity->_info.eid = ++_lastEID;
    entity->_control.eid = entity->_info.eid;
    entity->_report.eid = entity->_info.eid;
    entity->_control.stateChageTick = getFloatNowTime();
    entity->_info.color = ECOLOR_NONE;
    entity->_info.curHP = 100;
    entity->_info.moveAction = MACTION_IDLE;
    entity->_info.pos = entity->_control.spawnpoint;
    entity->_info.state = ESTATE_NONE;
    return entity;
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

bool Scene::addEntity(EntityPtr entity)
{
    _entitys.insert(std::make_pair(entity->_info.eid, entity));
    AddEntityNotice notice;
    EntityFullInfo full;
    entity->pickProto(full);
    notice.entitys.push_back(full);
    notice.serverTime = getFloatNowTime();
    broadcast(notice, entity->_base.avatarID);
    return true;
}
bool Scene::removeEntity(EntityID eid)
{
    RemoveEntityNotice notice;
    notice.eids.push_back(eid);
    notice.serverTime = getFloatNowTime();
    _entitys.erase(eid);
    broadcast(notice);
    return true;
}
bool Scene::enterScene(ServiceID avatarID, const std::string & token, SessionID sID)
{
    EntityPtr entity = getUserEntity(avatarID);
    if (!entity)
    {
        return false;
    }
    if (entity->_token != token)
    {
        return false;
    }
    entity->_clientSessionID = sID;
    if (!getEntity(entity->_info.eid))
    {
        addEntity(entity);
    }
    FillSceneNotice notice;
    EntityFullInfo info;
    for (auto kv : _entitys)
    {
        kv.second->pickProto(info);
        notice.entitys.push_back(info);
    }
    notice.serverTime = getFloatNowTime();
    notice.sceneStartTime = _startTime;
    notice.sceneEndTime = _endTime;
    sendToClient(avatarID, notice);
    return true;
}



bool Scene::leaveScene(ServiceID avatarID, SessionID sID)
{
    auto entity = getUserEntity(avatarID);
    if (entity && entity->_clientSessionID == sID)
    {
        entity->_clientSessionID = InvalidSessionID;
    }
    return true;
}







