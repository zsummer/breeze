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
    _lastSpaceStatusChangeTick = getFloatTick();
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
    _lastSpaceStatusChangeTick = getFloatTick();

    
    //load map
    //load entitys
    SpaceMgr::getRef().refreshSpaceStatusToWorld(getSpaceID());
    return true;
}


bool Space::onUpdate()
{
    return true;
}




