#include "entity.h"
Entity::Entity()
{

}

Entity::~Entity()
{

}



double Entity::getSpeed()
{
    if (_state.etype == ENTITY_PLAYER)
    {
        return 12.0;
    }
    else if (_state.etype == ENTITY_AI)
    {
        return 8.0;
    }
    else if (_state.etype == ENTITY_FLIGHT)
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
    return EntityFullData(_baseProps, _props, _state, _move, _report);
}


void Entity::flushProp()
{
    _props = _baseProps;
    if (_props.hp > _state.maxHP)
    {
        _state.curHP += _props.hp - _state.maxHP;
    }
    _state.maxHP = _props.hp;
    if (_state.curHP > _state.maxHP)
    {
        _state.curHP = _state.maxHP;
    }
}

