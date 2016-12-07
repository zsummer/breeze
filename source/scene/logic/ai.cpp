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
        EntityBase base;
        base.avatarID = 1000 + _monsters.size();
        base.avatarName = "MyLittlePet_";
        base.avatarName += toString(_monsters.size());
        base.modelID = rand() % 45 + 1;
        base.modelName = base.avatarName;
        base.camp = ENTITY_CAMP_BLUE + 100;
        base.etype = ENTITY_AI;
        base.state = ENTITY_STATE_ACTIVE;
        EntityProp fixedProps;
        fixedProps.hp = 1000;
        fixedProps.attack = 10;
        EntityProp grow;

        auto monster = scene->addEntity(base, fixedProps, grow, grow);
        _monsters[monster->_entityInfo.eid] = monster;
    }
    for (auto monster : _monsters)
    {
        SearchInfo search;
        search.camp = SEARCH_CAMP_NONE;
        search.etype = ENTITY_PLAYER;
        search.limitEntitys = 1;
        search.radian = PI*2.0;
        search.method = SEARCH_METHOD_SEACTOR;
        search.distance = 1E20;
        search.offsetX = 0;
        search.offsetY = 0;
        auto ret = scene->searchTarget(monster.second, 0, search);
        if (ret.size() > 0)
        {
            if (monster.second->_entityMove.follow != ret.front()->_entityInfo.eid && monster.second->_entityInfo.state == ENTITY_STATE_ACTIVE)
            {
                if (monster.second->_entityMove.follow == InvalidEntityID || realRand() > 0.7)
                {
                    monster.second->_entityMove.follow = ret.front()->_entityInfo.eid;
                }
            }
        }
    }

    for (auto kv : scene->_entitys)
    {
        if (kv.second->_entityMove.follow == InvalidEntityID)
        {
            continue;
        }
        auto entity = kv.second;
        auto follow = scene->getEntity(kv.second->_entityMove.follow);
        if (!follow)
        {
            kv.second->_entityMove.follow = InvalidEntityID;
            continue;
        }
        auto dist = getDistance(entity->_entityMove.position, follow->_entityMove.position);
        if (dist > 12)
        {
            EPositionArray ways;
            ways.push_back(follow->_entityMove.position);
            scene->_move->doMove(entity->_entityInfo.eid, MOVE_ACTION_FOLLOW, entity->getSpeed(), follow->_entityInfo.eid,
                entity->_entityMove.position, ways);
        }
    }






    SceneEventNotice eventNotice;
    for (auto kv : scene->_entitys)
    {
        if (kv.second->_entityInfo.state == ENTITY_STATE_LIE || kv.second->_entityInfo.state == ENTITY_STATE_DIED)
        {
            if (kv.second->_entityInfo.etype == ENTITY_FLIGHT)
            {
                scene->pushAsync(std::bind(&Scene::removeEntity, scene, kv.second->_entityInfo.eid));
            }
            else if (kv.second->_control.stateChageTime + 10.0 < getFloatSteadyNowTime())
            {
                kv.second->_entityInfo.state = ENTITY_STATE_ACTIVE;
                kv.second->_entityInfo.curHP = kv.second->_props.hp;
                kv.second->_isInfoDirty = true;
                kv.second->_entityMove.position = kv.second->_control.spawnpoint;
                if (scene->_move->isValidAgent(kv.second->_control.agentNo))
                {
                    scene->_move->setAgentPosition(kv.second->_control.agentNo, kv.second->_entityMove.position);
                }
                SceneEventInfo ev;
                ev.src = InvalidEntityID;
                ev.dst = kv.second->_entityInfo.eid;
                ev.ev = SCENE_EVENT_REBIRTH;
                ev.val = kv.second->_entityInfo.curHP;
                mergeToString(ev.mix, ",", kv.second->_entityMove.position.x);
                mergeToString(ev.mix, ",", kv.second->_entityMove.position.y);
                eventNotice.info.push_back(ev);
            }
        }
        scene->broadcast(eventNotice);
    }

}






