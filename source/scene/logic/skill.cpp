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


bool Skill::isOutCD(const EntitySkillInfo & skill, const DictSkill & dict)
{
    double now = getFloatSteadyNowTime();
    if (skill.activeTime == 0.0)
    {
        return true;
    }
    double keep = dict.keep;
    if (keep < dict.interval)
    {
        keep = dict.interval;
    }
    if (now <= skill.activeTime + dict.cd)
    {
        return false;
    }
    if (now <= skill.activeTime + dict.delay + keep)
    {
        return false;
    }
    if (now <= skill.lastTriggerTime + dict.interval)
    {
        return false;
    }
    return true;
}

bool Skill::updateSkillPos(ScenePtr scene, EntitySkillInfoPtr skill, const DictSkill & dictSkill)
{
    if (skill->activeOrgEID != InvalidEntityID)
    {
        EntityPtr orgE = scene->getEntity(skill->activeOrgEID);
        if (orgE)
        {
            skill->activeOrg = orgE->_move.position;
        }
        else
        {
            skill->activeOrgEID = InvalidEntityID;
        }
    }
    if (skill->activeDstEID != InvalidEntityID)
    {
        EntityPtr dstE = scene->getEntity(skill->activeDstEID);
        if (dstE)
        {
            skill->activeDst = dstE->_move.position;
        }
        else
        {
            skill->activeDstEID = InvalidEntityID;
        }
    }
    return true;
}

void Skill::selectFoe(ScenePtr scene, EntityPtr caster, bool onlyCancelCheck, bool change)
{

    if (onlyCancelCheck && caster->_state.foe == InvalidEntityID)
    {
        return; 
    }

    DictID searchID = InvalidDictID;
    for (auto &skill : caster->_skillSys.dictBootSkills)
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

    auto result = scene->searchTarget(caster, caster->_move.position,  caster->_control.lastClientFaceRadian, dictSearch.second);
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

        //check boot skill 
        for (auto &skill : e._skillSys.dictBootSkills)
        {
            if (e._skillSys.activeSkills.find(skill.first) == e._skillSys.activeSkills.end())
            {
                auto ptr = std::make_shared<EntitySkillInfo>();
                ptr->skillID = skill.second.id;
                e._skillSys.activeSkills[skill.second.id] = ptr;
            }
        }


        //check select
        if (e._skillSys.autoAttack)
        {
            selectFoe(scene, pr.second, false, false);
        }
        else if (e._state.foe != InvalidEntityID)
        {
            selectFoe(scene, pr.second, true, false);
        }


        //自动攻击
        if (e._skillSys.autoAttack && e._state.foe != InvalidEntityID)
        {
            for (auto &skill : e._skillSys.dictBootSkills)
            {
                if (getBitFlag(skill.second.stamp, SKILL_AUTO_USE))
                {
                    auto finder = e._skillSys.activeSkills.find(skill.first);
                    if (finder == e._skillSys.activeSkills.end())
                    {
                        LOGE("error. boot skill not fill. skill id=" << skill.second.id);
                    }
                    else
                    {
                        //激活 追敌逻辑  
                        updateSkillPos(scene, finder->second, skill.second);

                        auto aoeSearch = DBDict::getRef().getOneKeyAOESearch(skill.second.aoeID);
                        auto radian = getRadian(finder->second->activeOrg.x, finder->second->activeOrg.y, finder->second->activeDst.x, finder->second->activeDst.y);
                        auto ret = scene->searchTarget(finder->second->activeOrg, radian, aoeSearch.second.isRect, aoeSearch.second.distance, aoeSearch.second.value,
                            aoeSearch.second.compensateForward, aoeSearch.second.compensateRight);
                        EntityID foe = e._state.foe;
                        if (std::find_if(ret.begin(), ret.end(), [foe](EntityPtr ep) {return ep->_state.eid == foe; }) != ret.end())
                        {
                            scene->_move->doMove(e._state.eid, MOVE_ACTION_IDLE, e.getSpeed(), foe, std::vector<EPosition>());
                            if (isOutCD(*finder->second, skill.second) && finder->second->isFinish)
                            {
                                useSkill(scene, e._state.eid, skill.first);
                            }
                        }
                        else
                        {
                            scene->_move->doMove(e._state.eid, MOVE_ACTION_FOLLOW, e.getSpeed(), foe, std::vector<EPosition>());
                        }
                    }
                }
            }
        }


        //被动技能 
        for (auto &skill : e._skillSys.dictBootSkills)
        {
            if (getBitFlag(skill.second.stamp, SKILL_PASSIVE) )
            {
                auto finder = e._skillSys.activeSkills.find(skill.second.id);
                if (finder != e._skillSys.activeSkills.end())
                {
                    if (isOutCD(*finder->second, skill.second) && finder->second->isFinish)
                    {
                        useSkill(scene, e._state.eid, skill.first);
                    }
                }
            }
        }

        //trigger skill 
        std::map<DictID, EntitySkillInfoPtr> skills = e._skillSys.activeSkills;
        for (auto prSkill: skills)
        {
            auto dictSkill = DBDict::getRef().getOneKeyDictSkill(prSkill.first);
            if (dictSkill.first)
            {
                triggerSkill(scene, pr.second, prSkill.second, dictSkill.second);
            }
            
        }

        //trigger buff

    }
}

//填充默认的技能参数
bool  Skill::useSkill(ScenePtr scene, EntityID casterID, ui64 skillID)
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
    return useSkill(scene, casterID, skillID, pos, true);
}


bool Skill::useSkill(ScenePtr scene, EntityID casterID, ui64 skillID, const EPosition & dst, ui16 foeFirst)
{
    auto e = scene->getEntity(casterID);
    if (!e)
    {
        LOGE("Skill::useSkill not found caster. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }
    auto dictSkill = DBDict::getRef().getOneKeyDictSkill(skillID);
    if (!dictSkill.first)
    {
        LOGE("Skill::useSkill not found skill. casterID=" << casterID << ", skillID=" << skillID);
        return false;
    }
    if (dictSkill.second.aoeID == InvalidDictID)
    {
        LOGE("Skill::useSkill not found aoeid. casterID=" << casterID << ", skillID=" << skillID << ", aoeID=" << dictSkill.second.aoeID);
        return false;
    }
    if (getBitFlag(dictSkill.second.stamp, SKILL_AUTO_USE))
    {
        e->_skillSys.autoAttack = true;
    }

    EntitySkillInfoPtr skill;
    auto finder = e->_skillSys.activeSkills.find(dictSkill.second.id);
    if (finder != e->_skillSys.activeSkills.end())
    {
        skill = finder->second;
        if (!isOutCD(*skill, dictSkill.second))
        {
            LOGE("Skill::useSkill cd ing. casterID=" << casterID << ", skillID=" << skillID << ", aoeID=" << dictSkill.second.aoeID);
            return false;
        }
    }
    if (!skill)
    {
        skill = std::make_shared<EntitySkillInfo>();
        skill->skillID = dictSkill.second.id;
        if (e->_skillSys.dictBootSkills.find(dictSkill.first) != e->_skillSys.dictBootSkills.end())
        {
            LOGE("Skill::useSkill boot skill only fill in skill system update. skillID=" << dictSkill.second.id);
            return false;
        }
        e->_skillSys.activeSkills.insert(std::make_pair(dictSkill.second.id, skill));
    }
    if (!skill)
    {
        LOGF("");
        return false;
    }
    skill->activeCount++;
    skill->activeTime = getFloatSteadyNowTime();
    skill->lastTriggerTime = skill->activeTime - 1;
    skill->isFinish = 0;

    auto foe = scene->getEntity(e->_state.foe);
    if (dictSkill.second.orgType == 1)
    {
        // 普通类型的技能 施法位置以施法者为中心  以客户端传来的目标位置dst或者锁定的敌人为目标(方向) . 
        // 根据orgFixed选项可以选择施法中心是否跟随施法者(如果不是引导技能 跟随不跟随的没有区别) 
        // 飞行道具类的技能也必须配置为该类型.  (只支持从自身位置飞向锁定敌人或者目标方向的飞行道具)  
        skill->activeOrgEID = casterID;
        skill->activeOrg = e->_move.position;
        skill->activeDst = dst;
        skill->activeDstEID = InvalidEntityID;

        if (foeFirst && foe)
        {
            skill->activeDstEID = e->_state.foe;
            skill->activeDst = foe->_move.position;
        }
        if (dictSkill.second.orgFixed)
        {
            skill->activeDstEID = InvalidEntityID;
            skill->activeOrgEID = InvalidEntityID;
        }
    }
    else
    {
        //在指定的目标位置为中心进行施法 
        //例如 鲁班七号的手雷(王者荣耀), 人族大法的暴风雪(war3 引导技能)  
        skill->activeOrgEID = InvalidEntityID;
        skill->activeOrg = dst;
        //fix foe   
        if (foe)
        {
            skill->activeOrgEID = foe->_state.eid;
            skill->activeOrg = foe->_move.position;
        }
        double radian = getRadian(e->_move.position.x, e->_move.position.y, skill->activeDst.x, skill->activeDst.y);
        if (getDistance(e->_move.position, skill->activeOrg) > dictSkill.second.orgLimitDistance)
        {
            auto pos = getFarPoint(e->_move.position.x, e->_move.position.y, radian, dictSkill.second.orgLimitDistance);
            skill->activeOrg.x = std::get<0>(pos);
            skill->activeOrg.y = std::get<1>(pos);
            skill->activeOrgEID = InvalidEntityID; //这种情况要退化成fixed dst, 否则外挂可以造成地图炮. 
        }
        auto pos = getFarPoint(skill->activeOrg.x, skill->activeOrg.y, radian, 10.0/*这里只是起到radian作用*/); 
        skill->activeDst.x = std::get<0>(pos);
        skill->activeDst.y = std::get<1>(pos);
        skill->activeDstEID = InvalidEntityID;
    }

    scene->broadcast(UseSkillNotice(casterID, *skill));

    triggerSkill(scene, e, skill, dictSkill.second);
    return true;
}



bool Skill::triggerSkill(ScenePtr scene, EntityPtr caster, EntitySkillInfoPtr skill, const DictSkill & dictSkill)
{
    double now = getFloatSteadyNowTime();

    int damageCount = 0;
    //check first trigger 
    //isOutCD can assure  all active skill (lastTriggerTime < activeTime) is true after active skill. 
    if (skill->lastTriggerTime < skill->activeTime + dictSkill.delay && now >= skill->activeTime + dictSkill.delay)
    {
        for (auto skillID : dictSkill.combSkills)
        {

        }
        if (dictSkill.appendBuffsAoeID != InvalidDictID)
        {
            auto dictAoeBuff = DBDict::getRef().getOneKeyAOESearch(dictSkill.appendBuffsAoeID);
            if (dictAoeBuff.first)
            {
                for (auto buffID: dictSkill.appendBuffs)
                {

                }
            }
        }

        attack(scene, caster, skill, dictSkill);
        skill->lastTriggerTime = skill->activeTime + dictSkill.delay;
    }

    //引导技能
    while (dictSkill.interval > 0 
        && skill->lastTriggerTime >= skill->activeTime + dictSkill.delay
        && dictSkill.keep > dictSkill.interval 
        && now - skill->lastTriggerTime > dictSkill.interval)
    {
        attack(scene, caster, skill, dictSkill);
        skill->lastTriggerTime += dictSkill.interval;
    }

    //结束判断
    if (skill->lastTriggerTime >= skill->activeTime + dictSkill.delay //已经触发过一次 
        && isOutCD(*skill, dictSkill) )
    {
        skill->isFinish = 1;
        for (auto skillID : dictSkill.followSkills)
        {

        }
    }
    return true;
}



bool Skill::attack(ScenePtr scene, EntityPtr caster, EntitySkillInfoPtr skill, const DictSkill & dictSkill)
{
    //update skill pos  
    updateSkillPos(scene, skill, dictSkill);

    auto dictAoe = DBDict::getRef().getOneKeyAOESearch(dictSkill.aoeID);
    if (!dictAoe.first)
    {
        return false;
    }

    auto result = scene->searchTarget(caster, skill->activeOrg,
        getRadian(skill->activeOrg.x, skill->activeOrg.y, skill->activeDst.x, skill->activeDst.y),
        dictAoe.second);

   if (result.empty())
   {
       return true;
   }
   
   return damage(scene, caster, skill, dictSkill, result);
}


bool Skill::damage(ScenePtr scene, EntityPtr caster, EntitySkillInfoPtr skill, const DictSkill & dictSkill, std::vector<EntityPtr> & targets)
{
    SceneEventNotice notice;
    for (auto target : targets)
    {
        if (target->_state.state != ENTITY_STATE_ACTIVE)
        {
            continue;
        }
        target->_state.curHP -= 80;
        target->_isInfoDirty = true;
        if (caster->_state.etype != ENTITY_FLIGHT)
        {
            notice.info.push_back(SceneEventInfo(caster->_state.eid, target->_state.eid, SCENE_EVENT_HARM_ATTACK, 80, ""));
        }
        else
        {
            notice.info.push_back(SceneEventInfo(caster->_state.master, target->_state.eid, SCENE_EVENT_HARM_ATTACK, 80, ""));
        }

        if (target->_state.curHP <= 0)
        {
            target->_state.curHP = 0.0;
            target->_state.state = ENTITY_STATE_LIE;
            target->_move.action = MOVE_ACTION_IDLE;
            target->_move.follow = InvalidEntityID;
            target->_state.foe = InvalidEntityID;

            target->_control.stateChageTime = getFloatSteadyNowTime();

            if (caster->_state.etype != ENTITY_FLIGHT)
            {
                notice.info.push_back(SceneEventInfo(caster->_state.eid, target->_state.eid, SCENE_EVENT_LIE, 0, ""));
            }
            else
            {
                notice.info.push_back(SceneEventInfo(caster->_state.master, target->_state.eid, SCENE_EVENT_LIE, 0, ""));
            }
        }
    }
    scene->broadcast(notice);
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






