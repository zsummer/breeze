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

void Skill::selectFoe(ScenePtr scene, EntityPtr caster, bool onlyCancelCheck, bool change)
{

    if (onlyCancelCheck && caster->_state.foe == InvalidEntityID)
    {
        return; 
    }

    DictID searchID = InvalidDictID;
    for (auto &skill : caster->_skillSys.dictPlayerSkills)
    {
        if (skill.second.searchID != InvalidDictID)
        {
            searchID = skill.second.searchID;
            break;
        }
    }

    auto dictSearch = DBDict::getRef().getOneKeyAOESearch(searchID);
    if (!dictSearch.first)
    {
        if (caster->_state.foe != InvalidEntityID)
        {
            caster->_state.foe = InvalidEntityID;
            caster->_isInfoDirty = true;
        }
        LOGE("can not found searchID config . searchID=" << searchID);
        return;
    }



    if (caster->_state.foe != InvalidEntityID )
    {
        auto dst = scene->getEntity(caster->_state.foe);
        if (!dst || dst->_state.state != ENTITY_STATE_ACTIVE)
        {
            caster->_state.foe = InvalidEntityID;
            caster->_isInfoDirty = true;
        }
        else
        {
            double dis = getDistance(caster->_move.position, dst->_move.position);
            if (dis > dictSearch.second.distance * 1.5)
            {
                caster->_state.foe = InvalidEntityID;
                caster->_isInfoDirty = true;
            }
        }
    }

    if (onlyCancelCheck)
    {
        return;
    }

    if (caster->_state.foe != InvalidEntityID && !change)
    {
        return; //needn't change foe .  
    }

    auto result = scene->searchTarget(caster, caster->_control.lastClientFaceRadian, dictSearch.second);
    if (!result.empty())
    {
        for (auto dst : result)
        {
            if (caster->_state.foe != dst->_state.eid)
            {
                caster->_state.foe = dst->_state.eid;
                caster->_isInfoDirty = true;
                return;
            }
        }
    }
}

void Skill::update()
{
    double now = getFloatNowTime();
    auto scene = _scene.lock();
    if (! scene)
    {
        return;
    }
    std::map<EntityID, EntityPtr> entitys = scene->_entitys;
    for (auto pr : entitys)
    {
        Entity & e = *pr.second;

        //check
        if (e._state.foe != InvalidEntityID)
        {
            selectFoe(scene, pr.second, true, false);
        }



        //被动技能 
        for (auto &skill : e._skillSys.dictPlayerSkills)
        {
            if (getBitFlag(skill.second.stamp, SKILL_PASSIVE) )
            {
                if (e._skillSys.activeSkills.find(skill.first) == e._skillSys.activeSkills.end())
                {
                    trigger(scene, e._state.eid, skill.first);
                }
            }
        }

        //自动攻击
        if (e._skillSys.autoAttack)
        {
            for (auto &skill : e._skillSys.dictPlayerSkills)
            {
                if (getBitFlag(skill.second.stamp, SKILL_AUTO_USE))
                {
                    auto finder = e._skillSys.activeSkills.find(skill.first);
                    if (finder == e._skillSys.activeSkills.end())
                    {
                        trigger(scene, e._state.eid, skill.first);
                    }
                    else
                    {
                        if ((finder->second.lastTrigger  == 0.0 && finder->second.beginTime + skill.second.delay <=  getFloatSteadyNowTime())
                            || (skill.second.interval > 0 && finder->second.lastTrigger + skill.second.interval <= getFloatSteadyNowTime()) )
                        {
                            //re trigger 
                            trigger(scene, e._state.eid, skill.first);
                        }
                    }
                }
            }
        }
        



        //检查自动攻击, 被动技能
        std::map<DictID, EntitySkillInfo> skills = e._skillSys.activeSkills;
        for (auto & skill : skills)
        {
        }

        //检查buff
        std::map<DictID, EntitySkillInfo> buffs = e._skillSys.activeBuffs;
        for (auto & buff : buffs)
        {
        }
    }
}

//填充默认的技能参数
bool  Skill::trigger(ScenePtr scene, EntityID casterID, ui64 skillID)
{
    auto e = scene->getEntity(casterID);
    if (!e)
    {
        LOGE("not found caster. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }
    auto dictSkill =  DBDict::getRef().getOneKeyDictSkill(skillID);
    if (!dictSkill.first)
    {
        LOGE("not found skill. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }
    if (dictSkill.second.aoeID == InvalidDictID)
    {
        LOGE("not found aoeid. casterID=" << casterID << ", skillID=" << skillID << ", aoeID=" << dictSkill.second.aoeID);
        return false;
    }
    auto aoeSearch = DBDict::getRef().getOneKeyAOESearch(dictSkill.second.aoeID);
    if (!aoeSearch.first)
    {
        LOGE("not found aoeid. casterID=" << casterID << ", skillID=" << skillID << ", aoeID=" << dictSkill.second.aoeID);
        return false;
    }

    auto tpPos = getFarPoint(e->_move.position.x, e->_move.position.y, e->_control.lastClientFaceRadian, aoeSearch.second.distance);
    EPosition pos;
    pos.x = std::get<0>(tpPos);
    pos.y = std::get<1>(tpPos);
    trigger(scene, casterID, skillID, pos, true);
}


bool Skill::trigger(ScenePtr scene, EntityID casterID, ui64 skillID, const EPosition & dst, bool foeFirst)
{
    auto e = scene->getEntity(casterID);
    if (!e)
    {
        LOGE("not found caster. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }
    auto dictSkill = DBDict::getRef().getOneKeyDictSkill(skillID);
    if (!dictSkill.first)
    {
        LOGE("not found skill. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }
    if (dictSkill.second.aoeID == InvalidDictID)
    {
        LOGE("not found aoeid. casterID=" << casterID << ", skillID=" << skillID << ", aoeID=" << dictSkill.second.aoeID);
        return false;
    }




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






