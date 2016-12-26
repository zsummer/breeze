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
    auto scene = _scene.lock();
    if (!scene)
    {
        return;
    }

    double now = getFloatNowTime();
    for (auto kv : scene->_entitys)
    {
        EntityPtr self = kv.second;
        if (self->_control.skills.empty())
        {
            continue;
        }
        for (auto &skill : self->_control.skills)
        {
            while (!skill.data.behaviours.empty())
            {
                auto first = skill.data.behaviours.front();
                if (now < first.delay + skill.startTime)
                {
                    break;
                }
                if (getBitFlag(first.behaviour, SKILL_BEHAVIOUR_HIT))
                {
                    auto targets = scene->searchTarget(self, getRadian(self->_move.position.x, self->_move.position.y, skill.dst.x, skill.dst.y), first.search);
                    damage(self, targets);
                }
                skill.data.behaviours.erase(skill.data.behaviours.begin());
            }
        }
    }


}


bool Skill::trigger(EntityID eid, ui64 skillID, EntityID foe, const EPosition & dst)
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return false;
    }

    auto entity = scene->getEntity(eid);
    if (!entity)
    {
        return false;
    }
    if (entity->_state.state != ENTITY_STATE_ACTIVE)
    {
        return false;
    }
    auto &self = *entity;

    SkillData skill;
    skill.cd = 0;
    skill.skillID = skillID;
    skill.skillType = setBitFlag(0, SKILL_AUTO);

    SkillBehaviour behaviour;
    behaviour.behaviour = setBitFlag(0, SKILL_BEHAVIOUR_HIT);
    behaviour.delay = 0.15;
    behaviour.search.offsetX = -1;
    behaviour.search.offsetY = -1;
    behaviour.search.radian = PI / 2.0;
    behaviour.search.camp = setBitFlag(0, SEARCH_CAMP_ALIEN);
    behaviour.search.distance = 8.0;
    behaviour.search.limitEntitys = 100;
    skill.behaviours.push_back(behaviour);

    SkillInfo info;
    info.data = skill;
    info.dst = dst;
    info.foe = foe;
    info.skillID = skillID;
    info.startTime = getFloatSteadyNowTime();

    auto founder = std::find_if(self._control.skills.begin(), self._control.skills.end(),
        [&info](const SkillInfo & skill) {return skill.skillID == info.skillID; });
    if (founder != self._control.skills.end() && getFloatNowTime() - founder->startTime > founder->data.cd
        &&founder->data.behaviours.empty())
    {
        self._control.skills.erase(founder);
    }
    else if (founder != self._control.skills.end())
    {
        return false;//in cd
    }

    self._control.skills.push_back(info);
    scene->broadcast(UseSkillNotice(eid, skillID, foe, dst));
    return true;
}

bool Skill::damage(EntityPtr caster, std::vector<EntityPtr> & targets)
{
    auto scene = _scene.lock();
    if (!scene)
    {
        return false;
    }

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






