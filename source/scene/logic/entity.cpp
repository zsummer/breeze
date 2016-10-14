#include "entity.h"
Entity::Entity()
{

}

Entity::~Entity()
{

}


double Entity::getElapsed(double now)
{
    if (_control.lastMoveTime > now) _control.lastMoveTime = now;
    double elapse = now - _control.lastMoveTime;
    _control.lastMoveTime = now;
    return elapse;
}
double Entity::getSpeed()
{
    if (_move.action == MOVE_ACTION_IDLE)
    {
        return 0.0;
    }
    if (_info.etype == ENTITY_AVATAR)
    {
        return 12.0;
    }
    else if (_info.etype == ENTITY_AI)
    {
        return 8.0;
    }
    else if (_info.etype == ENTITY_FLIGHT)
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
    return EntityFullData(_baseInfo, _baseProps, _info, _move, _report);
}




