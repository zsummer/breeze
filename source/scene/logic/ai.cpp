#include "ai.h"
#include "scene.h"
#include "sceneMgr.h"

AI::AI()
{

}
AI::~AI()
{

}
void AI::init(std::weak_ptr<Scene> scene)
{
    _scene = scene;
}


void AI::update()
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
    }

    double now = getFloatNowTime();
    if (now - _lastCheckMonstr > 0.5)
    {
        _lastCheckMonstr = getFloatSteadyNowTime();
    }


    if (scene->_sceneType != SCENE_HOME)
    {
        return;
    }
    while (_monsters.size() < scene->_players.size() * 3)
    {
        auto entity = scene->makeEntity(rand()%20+1,
            InvalidAvatarID,
            "小白兔",
            DictArrayKey(),
            InvalidGroupID);
        entity->_props.hp = 5000;
        entity->_props.moveSpeed = 4.0;
        entity->_props.attackSpeed = 1.0;
        entity->_props.attack = 200;
        entity->_state.maxHP = entity->_props.hp;
        entity->_state.curHP = entity->_state.maxHP;
        entity->_state.camp = ENTITY_CAMP_BLUE + 100;
        entity->_skillSys.dictBootSkills[1] = DBDict::getRef().getOneKeyDictSkill(1).second;
        scene->addEntity(entity);
        _monsters[entity->_state.eid] = entity;


    }
    for (auto monster : _monsters)
    {
        if (monster.second->_move.follow == InvalidEntityID || realRand() > 0.7)
        {
            auto ret = scene->searchTarget(monster.second, monster.second->_move.position, 0, 1);
            if (ret.size() > 0)
            {
            monster.second->_move.follow = ret.front()->_state.eid;
            }
        }
    }

    for (auto kv : scene->_entitys)
    {
        if (kv.second->_move.follow == InvalidEntityID || kv.second->_state.foe != InvalidEntityID)
        {
            continue;
        }
        auto entity = kv.second;
        auto follow = scene->getEntity(kv.second->_move.follow);
        if (!follow)
        {
            kv.second->_move.follow = InvalidEntityID;
            continue;
        }
        auto dist = getDistance(entity->_move.position, follow->_move.position);
        if (dist > 10 - 2 ) // 近战距离 
        {
            EPositionArray ways;
            ways.push_back(follow->_move.position);
            scene->_move->doMove(entity->_state.eid, MOVE_ACTION_FOLLOW, entity->getSpeed(), follow->_state.eid, ways);
        }
        else if (entity->_move.action == MOVE_ACTION_FOLLOW)
        {
            scene->_move->doMove(entity->_state.eid, MOVE_ACTION_IDLE, entity->getSpeed(), follow->_state.eid, EPositionArray());
        }
    }






    SceneEventNotice eventNotice;
    for (auto kv : scene->_entitys)
    {
        if (kv.second->_state.state == ENTITY_STATE_LIE || kv.second->_state.state == ENTITY_STATE_DIED)
        {
            if (kv.second->_state.etype == ENTITY_FLIGHT)
            {
                scene->pushAsync(std::bind(&Scene::removeEntity, scene, kv.second->_state.eid));
            }
            else if (kv.second->_control.stateChageTime + 10.0 < getFloatSteadyNowTime())
            {
                kv.second->_state.state = ENTITY_STATE_ACTIVE;
                kv.second->_state.curHP = kv.second->_props.hp;
                kv.second->_isInfoDirty = true;
                kv.second->_move.position = kv.second->_control.spawnpoint;
                if (scene->_move->isValidAgent(kv.second->_control.agentNo))
                {
                    scene->_move->setAgentPosition(kv.second->_control.agentNo, kv.second->_move.position);
                }
                SceneEventInfo ev;
                ev.src = InvalidEntityID;
                ev.dst = kv.second->_state.eid;
                ev.ev = SCENE_EVENT_REBIRTH;
                ev.val = kv.second->_state.curHP;
                mergeToString(ev.mix, ",", kv.second->_move.position.x);
                mergeToString(ev.mix, ",", kv.second->_move.position.y);
                eventNotice.info.push_back(ev);
            }
        }
        scene->broadcast(eventNotice);
    }

}






