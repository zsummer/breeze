#include "skill.h"
#include "scene.h"
#include "sceneMgr.h"

Skill::Skill()
{

}
Skill::~Skill()
{

}
void Skill::init(std::weak_ptr<Scene> scene)
{
    _scene = scene;
}


void Skill::update()
{


    double now = getFloatNowTime();


}


bool Skill::trigger(ScenePtr scene, EntityID casterID, ui64 skillID, const EPosition & dst, bool foeFirst)
{
    auto entity = scene->getEntity(casterID);
    if (!entity)
    {
        return false;
    }

    auto &self = *entity;


    scene->broadcast(UseSkillNotice(casterID, skillID, self._state.foe, dst, foeFirst));
    return true;
}

bool Skill::damage(ScenePtr scene, EntityPtr caster, std::vector<EntityPtr> & targets)
{

    EntityPtr master = caster;
    if (caster->_state.etype == ENTITY_FLIGHT)
    {
        master = scene->getEntity(caster->_state.foe);
        if (!master)
        {
            return false;
        }
    }
    SceneEventNotice notice;
    for (auto target : targets)
    {
        if (target->_state.state != ENTITY_STATE_ACTIVE)
        {
            continue;
        }
        target->_state.curHP -= 20;
        target->_isInfoDirty = true;
        notice.info.push_back(SceneEventInfo(master->_state.eid, target->_state.eid, SCENE_EVENT_HARM_ATTACK, 20, ""));
        if (target->_state.curHP <= 0)
        {
            target->_state.curHP = 0.0;
            target->_state.state = ENTITY_STATE_LIE;
            target->_move.action = MOVE_ACTION_IDLE;
            target->_move.follow = InvalidEntityID;
            target->_state.foe = InvalidEntityID;

            target->_control.stateChageTime = getFloatSteadyNowTime();
            notice.info.push_back(SceneEventInfo(master->_state.eid, target->_state.eid, SCENE_EVENT_LIE, 0, ""));
        }
    }
    scene->broadcast(notice);
    return true;
}

bool Skill::cleanSkill()
{
    return true;
}
bool Skill::addBuff()
{
    return true;
}
bool Skill::cleanBuff()
{
    return true;
}






