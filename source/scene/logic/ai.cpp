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


    rebirthCheck();

}


void AI::rebirthCheck()
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
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
                kv.second->_isStateDirty = true;
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
                mergeToString(ev.mix, ',', kv.second->_move.position.x);
                mergeToString(ev.mix, ',', kv.second->_move.position.y);
                eventNotice.info.push_back(ev);
            }
        }
    }
    if (!eventNotice.info.empty())
    {
        scene->broadcast(eventNotice);
    }

}




