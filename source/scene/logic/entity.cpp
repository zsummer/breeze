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
    if (_move.moveAction == MACTION_IDLE)
    {
        return 0.0;
    }
    if (_move.moveAction != MACTION_PATH && _move.moveAction != MACTION_FOLLOW && _move.moveAction != MACTION_IDLE)
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

EntityFullData Entity::getFullData()
{
    return EntityFullData(_baseInfo, _baseProps, _info, _move, _report);
}




