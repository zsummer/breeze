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
    _lastStatusChangeTime = getFloatNowTime();
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
    _lastStatusChangeTime = getFloatNowTime();
    _startTime = getFloatNowTime();
    _endTime = getFloatNowTime() + 3600;
    
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
    _entitys.insert(std::make_pair(entity->_info.eid, entity));
    AddEntityNotice notice;
    EntityFullInfo full;
    entity->pickProto(full);
    notice.entitys.push_back(full);
    notice.serverTime = getFloatNowTime();
    broadcast(notice, entity->_base.userID);
    return true;
}
bool Space::removeEntity(EntityID eid)
{
    RemoveEntityNotice notice;
    notice.eids.push_back(eid);
    notice.serverTime = getFloatNowTime();
    _entitys.erase(eid);
    broadcast(notice);
    return true;
}
bool Space::enterSpace(ServiceID userID, const std::string & token, SessionID sID)
{
    EntityPtr entity = getUserEntity(userID);
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
    FillSpaceNotice notice;
    EntityFullInfo info;
    for (auto kv : _entitys)
    {
        kv.second->pickProto(info);
        notice.entitys.push_back(info);
    }
    notice.serverTime = getFloatNowTime();
    notice.spaceStartTime = _startTime;
    notice.spaceEndTime = _endTime;
    sendToClient(userID, notice);
    return true;
}



bool Space::leaveSpace(ServiceID userID, SessionID sID)
{
    auto entity = getUserEntity(userID);
    if (entity && entity->_clientSessionID == sID)
    {
        entity->_clientSessionID = InvalidSessionID;
    }
    return true;
}







