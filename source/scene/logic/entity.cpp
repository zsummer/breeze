#include "entity.h"
Entity::Entity()
{
    _control.agentNo = RVO::RVO_ERROR;
}

Entity::~Entity()
{

}



double Entity::getSpeed()
{
    return _props.moveSpeed;
}

double Entity::getSuckBlood()
{
    return 0.0;
}

double Entity::getAttack()
{
    return 1.0;
}
EntityClientSync Entity::getClientSyncData()
{
    return EntityClientSync(_props, _state, _move, _report);
}




