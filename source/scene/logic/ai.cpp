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
    if (_monsters.empty())
    {
        std::vector<EPosition>  sps = { {62.4,62.4},{47.1,63.6}, {100,63},{-13.3, 62.5}, { -62.4,63.4 } };
        for (auto sp : sps)
        {
            auto entity = scene->makeEntity(rand() % 20 + 1,
                InvalidAvatarID,
                "mylittleairport",
                DictArrayKey(),
                InvalidGroupID);
            entity->_props.hp = 3000 + (rand() % 100) * 20;
            entity->_props.moveSpeed = 4.0;
            entity->_props.attackQuick = 0.5;
            entity->_props.attack = 80;
            entity->_state.maxHP = entity->_props.hp;
            entity->_state.curHP = entity->_state.maxHP;
            entity->_state.camp = ENTITY_CAMP_BLUE + 100;
            entity->_state.collision = 1.0;
            entity->_skillSys.dictBootSkills.insert(2);
            entity->_skillSys.autoAttack = true;

            entity->_move.position = sp;
            entity->_control.spawnpoint = sp;

            scene->addEntity(entity);
            _monsters[entity->_state.eid] = entity;
            scene->pushAsync([scene, entity]() {scene->_skill->useSkill(scene, entity->_state.eid, 1); });
        }

    }



    for (auto kv : scene->_entitys)
    {
        if (kv.second->_move.follow == InvalidEntityID || kv.second->_state.foe != InvalidEntityID)
        {
            continue;
        }
        auto entity = kv.second;
        auto dist = getDistance(entity->_move.position, entity->_control.spawnpoint);
        if ((dist > 20 || (dist > 8 && entity->_state.foe == InvalidEntityID)) && entity->_move.action != MOVE_ACTION_FORCE_PATH)
        {
            EPositionArray dsts;
            dsts.push_back(entity->_control.spawnpoint);
            scene->_move->doMove(entity->_state.eid, MOVE_ACTION_FORCE_PATH, entity->getSpeed(), InvalidEntityID, dsts);
            continue;
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






