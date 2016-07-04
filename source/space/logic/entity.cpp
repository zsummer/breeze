#include "entity.h"
Entity::Entity()
{

}

Entity::~Entity()
{

}


ui32 Entity::getElapsed(ui32 now)
{
    if (_control.lastMoveTick < _control.extBeginTick)_control.lastMoveTick = _control.extBeginTick;
    if (_control.lastMoveTick > now) _control.lastMoveTick = now;
    ui32 elapse = now - _control.lastMoveTick;
    _control.lastMoveTick = now;
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






