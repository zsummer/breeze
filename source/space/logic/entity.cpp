#include "entity.h"
Entity::Entity()
{

}

Entity::~Entity()
{

}


double Entity::getElapsed(double now)
{
    if (_control.lastMoveTime < _control.extBeginTime)_control.lastMoveTime = _control.extBeginTime;
    if (_control.lastMoveTime > now) _control.lastMoveTime = now;
    double elapse = now - _control.lastMoveTime;
    _control.lastMoveTime = now;
    return elapse;
}
double Entity::getSpeed()
{
    if (_info.moveAction == MACTION_IDLE)
    {
        return 0.0;
    }
    if (_info.moveAction != MACTION_PATH && _info.moveAction != MACTION_FOLLOW && _info.moveAction != MACTION_IDLE)
    {
        return _control.extSpeed;
    }
    return 5.0;
}

double Entity::getSuckBlood()
{
    return 0.0;
}

double Entity::getAttack()
{
    return 1.0;
}

void Entity::pickProto(EntityFullInfo & info)
{
    info.userInfo = _base;
    info.info = _info;
    info.report = _report;
}




