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





EntityPtr Skill::lockFoe(ScenePtr scene, EntityPtr caster, const EntitySkillInfo & skill)
{
    EntityPtr foe;
    while(caster->_state.foe != InvalidEntityID)
    {
        EntityPtr locked;
        locked = scene->getEntity(caster->_state.foe);
        if (!locked)
        {
            break;
        }
        if (locked->_state.state != ENTITY_STATE_ACTIVE)
        {
            break;
        }
        EntityPtr master = caster;
        if (caster->_state.etype == ENTITY_FLIGHT )
        {
            if (caster->_state.master != InvalidEntityID)
            {
                master = scene->getEntity(caster->_state.master);
            }
            else
            {
                master = nullptr;
            }
        }

        if (!scene->searchMatched(master, caster,locked, skill.dict.aosDict))
        {
            break;
        }
        if (skill.dict.aosType == SKILL_LOCKED_ENTITY)
        {
            return locked;
        }
        if (skill.dict.aosType == SKILL_LOCKED_FREE)
        {
            double dist = getDistance(caster, locked);
            if (dist > skill.dict.aoeDict.value1)
            {
                break;
            }
        }
        foe = locked;
        break;
    }
    if (!foe && caster->_state.foe != InvalidEntityID)
    {
        caster->_state.foe = InvalidEntityID;
        caster->_isStateDirty = true;
    }
    if (!foe)
    {
        auto foeList = scene->searchTarget(caster, caster->_move.position, EPosition(1, 1), skill.dict.aosDict);
        if (!foeList.empty())
        {
            foe = foeList.front().first;
            caster->_state.foe = foe->_state.eid;
            caster->_isStateDirty = true;
        }
    }
    return foe;
};


void Skill::update()
{

    auto scene = _scene.lock();
    if (! scene)
    {
        return;
    }

    for (auto pr : scene->_entitys)
    {
        Entity & e = *pr.second;

        //check equipped skill 
        for (auto iter = e._skillSys.dictEquippedSkills.begin(); iter != e._skillSys.dictEquippedSkills.end();)
        {
            if (e._skillSys.activeSkills.find(iter->first) == e._skillSys.activeSkills.end())
            {
                if (!doSkill(scene, e._state.eid, iter->first, { 1,1 }, InvalidEntityID, false, true))
                {
                    LOGE("Skill::update auto fill skill info error. skillid=" << iter->first);
                    iter = e._skillSys.dictEquippedSkills.erase(iter);
                    continue;
                }
            }
            iter++;
        }

        //check active skill 
        //only this can erase iter.
        EntitySkillInfo * skill = nullptr;
        for (auto iter = e._skillSys.activeSkills.begin(); iter != e._skillSys.activeSkills.end();)
        {
            if (e._skillSys.dictEquippedSkills.find(iter->first) == e._skillSys.dictEquippedSkills.end())
            {
                if (iter->second.activeState == ENTITY_SKILL_NONE)
                {
                    iter = e._skillSys.activeSkills.erase(iter);
                    continue;
                }
            }
            if (getBitFlag(iter->second.dict.stamp, SKILL_NORMAL))
            {
                e._skillSys.normalSkillID = iter->second.skillID;
                if (e._skillSys.readySkillID == InvalidDictID)
                {
                    e._skillSys.readySkillID = iter->second.skillID;
                }
            }
            if (iter->first == e._skillSys.readySkillID)
            {
                skill = &iter->second;
            }
            iter++;
        }

        EntityPtr foe;
        if (skill)
        {
            foe = lockFoe(scene, pr.second, *skill);
        }


        //自动攻击
        while (skill && foe && e._state.state == ENTITY_STATE_ACTIVE && e._skillSys.combating)
        {
            double distance = getDistance(pr.second, foe);
            if (e._move.action == MOVE_ACTION_FORCE_PATH || e._move.action == MOVE_ACTION_PASV_PATH)
            {
                break;
            }

            if (e._move.action == MOVE_ACTION_FOLLOW &&
                distance > (std::max(skill->dict.aoeDict.value1, skill->dict.aoeDict.value2) + foe->_control.collision)*0.8)
            {
                break;
            }

            auto ret = scene->searchTarget(pr.second, e._move.position, foe->_move.position - e._move.position, skill->dict.aoeDict);

            if (std::find_if(ret.begin(), ret.end(), [foe](const std::pair<EntityPtr, double> & ep) {return ep.first->_state.eid == foe->_state.eid; }) != ret.end())
            {
                if (e._move.action != MOVE_ACTION_IDLE)
                {
                    scene->_move->doMove(e._state.eid, MOVE_ACTION_IDLE, e.getSpeed(), foe->_state.eid, std::vector<EPosition>());
                }
                if (skill->activeState == ENTITY_SKILL_NONE )
                {
                    doSkill(scene, pr.second, *skill, { 1,1 }, true);
                }
                
            }
            else if (e._move.action == MOVE_ACTION_IDLE)
            {
                scene->_move->doMove(e._state.eid, MOVE_ACTION_FOLLOW, e.getSpeed(), foe->_state.eid, std::vector<EPosition>());
            }

            break; // once  
        }



        //被动技能 
        for (auto &kv : e._skillSys.activeSkills)
        {

            if (getBitFlag(kv.second.dict.stamp, SKILL_PASSIVE) )
            {
                if (kv.second.activeState == ENTITY_SKILL_NONE )
                {
                    doSkill(scene, pr.second, kv.second, { 1,1 }, true);
                }
            }
        }

        for (auto & kv : e._skillSys.activeSkills)
        {
            if (kv.second.activeState == ENTITY_SKILL_PREFIX || kv.second.activeState == ENTITY_SKILL_ACTIVE || kv.second.activeState == ENTITY_SKILL_CD)
            {
                updateSkill(scene, pr.second, kv.second);
            }
        }

        //trigger buff
    }
}



bool Skill::doSkill(ScenePtr scene, EntityID casterID, ui64 skillID, const EPosition & clientDst, EntityID clientFoe, bool autoFoe, bool onlyFill)
{
    auto e = scene->getEntity(casterID);
    if (!e)
    {
        LOGE("Skill::useSkill not found caster. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }

    EntitySkillInfo * skill = nullptr;
    auto finder = e->_skillSys.activeSkills.find(skillID);
    if (finder != e->_skillSys.activeSkills.end())
    {
        skill = &finder->second;
    }
    if (!skill)
    {
        auto dictSkill = DBDict::getRef().getOneKeyDictSkill(skillID);
        if (!dictSkill.first)
        {
            LOGE("Skill::useSkill not found skill dict. casterID=" << casterID << ", skillID=" << skillID);
            return false;
        }

        auto inst = e->_skillSys.activeSkills.insert(std::make_pair(skillID, EntitySkillInfo()));
        skill = &inst.first->second;
        skill->skillID = skillID;
        skill->activeState = ENTITY_SKILL_NONE;
        skill->dict = dictSkill.second;
    }
    if (onlyFill)
    {
        return true;
    }
    if (clientFoe != InvalidEntityID && autoFoe)
    {
        e->_state.eid = clientFoe;
    }


    return doSkill(scene, e, *skill, clientDst, autoFoe);
}

bool Skill::doSkill(ScenePtr scene, EntityPtr caster, EntitySkillInfo & skill, const EPosition & clientDst, bool autoFoe)
{
    if (skill.activeState != ENTITY_SKILL_NONE )
    {
        LOGE("Skill::doSkill error. state not none . casterID="<< caster->_state.eid << ", skillID=" << skill.skillID 
            << ", state=" << skill.activeState << ", trace=" << proto4z_traceback());        return false;
    }

    if (getBitFlag(skill.dict.stamp, SKILL_NORMAL))
    {
        caster->_skillSys.combating = true;
        caster->_skillSys.normalSkillID = skill.skillID;
    }
    caster->_skillSys.readySkillID = skill.skillID;

    auto foe = lockFoe(scene, caster, skill);
    if (foe && getBitFlag(skill.dict.stamp, SKILL_NORMAL))
    {
        auto ret = scene->searchTarget(caster, caster->_move.position, foe->_move.position - caster->_move.position, skill.dict.aoeDict);

        if (std::find_if(ret.begin(), ret.end(), [foe](const std::pair<EntityPtr, double> & ep) {return ep.first->_state.eid == foe->_state.eid; }) != ret.end())
        {
            if (caster->_move.action == MOVE_ACTION_FOLLOW)
            {
                scene->_move->doMove(caster->_state.eid, MOVE_ACTION_IDLE, caster->getSpeed(), foe->_state.eid, std::vector<EPosition>());
            }
        }
        else if (caster->_move.action == MOVE_ACTION_IDLE)
        {
            scene->_move->doMove(caster->_state.eid, MOVE_ACTION_FOLLOW, caster->getSpeed(), foe->_state.eid, std::vector<EPosition>());
            return true;
        }
    }


    skill.activeCount++;
    skill.lastActiveTime = getFloatSteadyNowTime();
    skill.lastTriggerTime = skill.lastActiveTime;
    skill.activeState = ENTITY_SKILL_PREFIX;
    skill.activeFoeFirst = autoFoe ? 1: 0;
    skill.activeDst = clientDst;
    if (autoFoe && foe)
    {
        skill.activeDst = foe->_move.position;
    }

    scene->broadcast(UseSkillNotice(caster->_state.eid, skill));

    updateSkill(scene, caster, skill);
    return true;
}

bool Skill::updateSkill(ScenePtr scene, EntityPtr caster, EntitySkillInfo & skill)
{
    if (skill.activeState != ENTITY_SKILL_PREFIX && skill.activeState != ENTITY_SKILL_ACTIVE
        && skill.activeState != ENTITY_SKILL_CD)
    {
        LOGE("Skill::updateSkill error. state not prefix or active or cd. casterID="
            << caster->_state.eid << ", skillID=" << skill.skillID);
        return false;
    }
    double now = getFloatSteadyNowTime();
    int damageCount = 0;
    if (skill.activeState == ENTITY_SKILL_PREFIX && skill.lastActiveTime + 0 <= now)
    {
        skill.lastTriggerTime = skill.lastActiveTime + 0;
        skill.activeState = ENTITY_SKILL_ACTIVE;
        //consume MP 
        //combSkills
        for (auto combID : skill.dict.combSkills)
        {
            doSkill(scene, caster->_state.eid, combID, skill.activeDst, caster->_state.foe, skill.activeFoeFirst != 0);
        }
        damageCount++;
    }


    if (skill.activeState == ENTITY_SKILL_ACTIVE && skill.dict.interval > 0 && skill.dict.keep > 0 && now > skill.lastTriggerTime)
    {
        double endtime = std::min(skill.lastActiveTime + 0 + skill.dict.keep, now);
        double intv = std::min(endtime - skill.lastTriggerTime, skill.dict.keep);
        double spd = std::max(skill.dict.interval / (1 + caster->_props.attackQuick), 0.05);
        int addCount = (int)floor(std::max(intv, 0.0) / spd);
        if (addCount > 0)
        {
            skill.lastTriggerTime += spd*addCount;
        }
        damageCount += addCount;
    }

    for (int i=0; i < damageCount; i++)
    {
        if (skill.dict.appendBuffsAreaID != InvalidDictID)
        {
            for (auto buffID : skill.dict.appendBuffs)
            {

            }
        }
        attack(scene, caster, skill);
    }

    //进入CD  
    if (skill.activeState == ENTITY_SKILL_ACTIVE 
        && now > skill.lastActiveTime + 0 + std::max(std::max(skill.dict.interval / (1 + caster->_props.attackQuick), 0.05), skill.dict.keep))
    {
        skill.activeState = ENTITY_SKILL_CD;
        if (skill.skillID == caster->_skillSys.readySkillID)
        {
            caster->_skillSys.readySkillID = InvalidDictID;
        }
    }

    //CD结束 
    if (skill.activeState == ENTITY_SKILL_CD
        && now > skill.lastActiveTime + 0 + std::max(std::max(std::max(skill.dict.interval / (1 + caster->_props.attackQuick), 0.05), skill.dict.keep), skill.dict.cd))
    {
        skill.activeState = ENTITY_SKILL_NONE;
        for (auto buffID : skill.dict.followSkills)
        {

        }
    }
    return true;
}



bool Skill::attack(ScenePtr scene, EntityPtr caster, EntitySkillInfo & skill)
{
    //update skill pos  
    auto foe = lockFoe(scene, caster, skill);
    if (skill.activeFoeFirst && foe)
    {
        skill.activeDst = foe->_move.position;
    }
    std::vector<std::pair<EntityPtr, double>> targets;
    if (foe && skill.dict.aoeID == InvalidDictID)
    {
        targets.push_back(std::make_pair(foe, getDistance(caster, foe)));
    }
    if (skill.dict.aoeID != InvalidDictID)
    {
        targets = scene->searchTarget(caster, caster->_move.position,
            normalize(skill.activeDst - caster->_move.position), skill.dict.aoeDict);
    }

   if (targets.empty())
   {
       return true;
   }
   
   return damage(scene, caster, skill, targets);
}


bool Skill::damage(ScenePtr scene, EntityPtr caster, EntitySkillInfo & skill,  std::vector<std::pair<EntityPtr, double>> & targets)
{
    SceneEventNotice notice;
    caster->_skillSys.breakoffAttackTime = getFloatSteadyNowTime();
    for (auto target : targets)
    {
        if (target.first->_state.state != ENTITY_STATE_ACTIVE)
        {
            continue;
        }
        target.first->_skillSys.breakoffAttackTime = getFloatSteadyNowTime();
        //process harm     
        double harm = caster->_props.attack;  
        target.first->_state.curHP -= harm;
        target.first->_isStateDirty = true;
        if (caster->_state.etype != ENTITY_FLIGHT)
        {
            notice.info.push_back(SceneEventInfo(caster->_state.eid, target.first->_state.eid, SCENE_EVENT_HARM_ATTACK, harm, ""));
        }
        else
        {
            notice.info.push_back(SceneEventInfo(caster->_state.master, target.first->_state.eid, SCENE_EVENT_HARM_ATTACK, harm, ""));
        }

        if (target.first->_state.curHP <= 0)
        {
            target.first->_state.curHP = 0.0;
            target.first->_state.state = ENTITY_STATE_LIE;
            target.first->_move.action = MOVE_ACTION_IDLE;
            target.first->_move.follow = InvalidEntityID;
            target.first->_state.foe = InvalidEntityID;

            target.first->_control.stateChageTime = getFloatSteadyNowTime();

            if (caster->_state.etype != ENTITY_FLIGHT)
            {
                notice.info.push_back(SceneEventInfo(caster->_state.eid, target.first->_state.eid, SCENE_EVENT_LIE, 0, ""));
            }
            else
            {
                notice.info.push_back(SceneEventInfo(caster->_state.master, target.first->_state.eid, SCENE_EVENT_LIE, 0, ""));
            }
        }
        target.first->_isStateDirty = true;
    }
    if (!notice.info.empty())
    {
        scene->broadcast(notice);
    }
    
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






