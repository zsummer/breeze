#include "entity.h"
Entity::Entity()
{

}

Entity::~Entity()
{

}



double Entity::getSpeed()
{
    if (_entityInfo.etype == ENTITY_PLAYER)
    {
        return 12.0;
    }
    else if (_entityInfo.etype == ENTITY_AI)
    {
        return 8.0;
    }
    else if (_entityInfo.etype == ENTITY_FLIGHT)
    {
        return 20.0;
    }
    else
    {
        return 10.0;
    }
    
}

double Entity::getSuckBlood()
{
    return 0.0;
}

double Entity::getAttack()
{
    return 1.0;
}

EntityFullData Entity::getFullData()
{
    return EntityFullData(_baseInfo, _baseProps, _entityInfo, _entityMove, _report);
}




