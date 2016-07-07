#include "space.h"
#include "spaceMgr.h"
Space::Space(SpaceID id)
{
    _spaceID = id;
    cleanSpace();
}
bool Space::cleanSpace()
{
    _lastEID = ServerConfig::getRef().getSpaceConfig()._spaceID * 1000 + 1000;
    _entitys.clear();
    _users.clear();
    _sceneType = SCENE_TYPE_NONE;
    _spaceStatus = SPACE_STATUS_NONE;
    _lastSpaceStatusChangeTick = getFloatNowTime();
    SpaceMgr::getRef().refreshSpaceStatusToWorld(getSpaceID());
    return true;
}

bool Space::loadSpace(SCENE_TYPE sceneType)
{
    if (_spaceStatus != SPACE_STATUS_NONE)
    {
        LOGE("Space::loadSpace  space status error");
        return false;
    }
    _sceneType = sceneType;
    _spaceStatus = SPACE_STATUS_WAIT;
    _lastSpaceStatusChangeTick = getFloatNowTime();

    
    //load map
    //load entitys
    SpaceMgr::getRef().refreshSpaceStatusToWorld(getSpaceID());
    return true;
}


bool Space::onUpdate()
{
    return true;
}

EntityPtr Space::getEntity(EntityID eID)
{
    auto founder = _entitys.find(eID);
    if (founder == _entitys.end())
    {
        return nullptr;
    }
    return founder->second;
}
EntityPtr Space::getUserEntity(ServiceID userID)
{
    auto founder = _users.find(userID);
    if (founder == _users.end())
    {
        return nullptr;
    }
    return founder->second;
}

EntityPtr Space::makeNewEntity(const UserBaseInfo & base)
{
    EntityPtr entity = std::make_shared<Entity>();
    entity->_base = base;
    entity->_control.spawnpoint = { 0.0,0.0 };
    entity->_info.eid = ++_lastEID;
    entity->_control.eid = entity->_info.eid;
    entity->_report.eid = entity->_info.eid;
    entity->_control.stateChageTick = getFloatNowTime();
    entity->_info.color = ECOLOR_NONE;
    entity->_info.curHP = entity->_base.hp;
    entity->_info.moveAction = MACTION_IDLE;
    entity->_info.pos = entity->_control.spawnpoint;
    entity->_info.state = ESTATE_NONE;
    return entity;
}

void Space::fillUserProp(const FillUserToSpaceReq& req)
{
    auto entity = getUserEntity(req.baseInfo.userID);
    if (entity)
    {
        LOGE("already had");
        return;
    }
    entity = makeNewEntity(req.baseInfo);
    entity->_token = req.token;
    entity->_info.state = ESTATE_FREEZING;
    entity->_isClientDirty = true;
}

bool Space::addEntity(EntityPtr entity)
{
    AddEntityNotice notice;
    EntityFullInfo full;
    full.base = entity->_base;
    full.info = entity->_info;
    full.report = entity->_report;
    notice.entitys.push_back(full);
    notice.serverTime = getFloatNowTime();
    broadcast(notice);
    return true;
    return true;
}
bool Space::removeEntity(EntityID eid)
{
    return true;
}
bool Space::enterSpace(ServiceID userID)
{
    return true;
}
bool Space::leaveSpace(ServiceID userID)
{
    return true;
}







