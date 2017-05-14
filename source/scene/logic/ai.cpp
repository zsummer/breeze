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


    if (scene->_sceneType != SCENE_HOME && scene->_sceneType != SCENE_MELEE)
    {
        return;
    }
    if (_monsters.empty())
    {
        std::string aiFileName;
        std::vector<EPosition>  sps;
        if (scene->getSceneType() == SCENE_HOME)
        {
            aiFileName = "../scripts/home_ai.txt";
        }
        else if (scene->getSceneType() == SCENE_MELEE)
        {
            aiFileName = "../scripts/melee_ai.txt";
        }
        if (!aiFileName.empty() && accessFile(aiFileName))
        {
            std::string content = readFileContent(aiFileName);
            auto obs = splitString<std::string>(content, "\n", " \r");
            for (auto &ob : obs)
            {
                std::vector<RVO::Vector2> vertices;
                auto as = splitArrayString<double, double>(ob, " ", ",", "");
                for (auto &pos : as)
                {
                    sps.push_back(EPosition(std::get<0>(pos), std::get<1>(pos)));
                }
            }
        }

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



    for (auto kv : _monsters)
    {
        bool checkBack = false;
        do 
        {
            auto entity = kv.second;
            auto dist = getDistance(entity->_move.position, entity->_control.spawnpoint);
            if (dist > 20)
            {
                checkBack = true;
                break;
            }
            if (dist > entity->_state.collision + PATH_PRECISION + 1.0 && entity->_state.foe == InvalidEntityID)
            {
                checkBack = true;
                break;
            }
            if (entity->_state.foe == InvalidEntityID && entity->_move.action == MOVE_ACTION_FOLLOW)
            {
                checkBack = true;
                break;
            }
        } while (false);
        if (checkBack && kv.second->_move.action != MOVE_ACTION_FORCE_PATH)
        {
            EPositionArray dsts;
            dsts.push_back(kv.second->_control.spawnpoint);
            scene->_move->doMove(kv.second->_state.eid, MOVE_ACTION_FORCE_PATH, kv.second->getSpeed(), InvalidEntityID, dsts);
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






