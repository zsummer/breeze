--require
--process msg
require("scene")

function addMonster(pos, camp, name)
    local prop = {hp=1200, attack=200, attackQuick=1, moveSpeed=8}
    local state = {modelID=math.random(1,20), 
                    avatarName=name or "unknown", 
                    camp= camp , 
                    maxHP=prop.hp, 
                    curHP=prop.hp, 
                    etype=Proto4z.ENTITY_AI, 
                    state=Proto4z.ENTITY_STATE_ACTIVE}

    local skill = {dictEquippedSkills = {[5]=0}, readySkillID = 5 , combating = 0  }
    if camp < Proto4z.ENTITY_CAMP_NEUTRAL then
        skill = {dictEquippedSkills = {[3]=0}, readySkillID = 3 , combating = 0  }
    end
    local ctl = {spawnpoint = {x=pos.x or pos[1], y=pos.y or pos[2]},  collision=1 }

    local propData = Proto4z.encode(prop, "DictProp")
    local stateData = Proto4z.encode(state, "EntityState")
    local skillData = Proto4z.encode(skill, "EntitySkillSystem")
    local ctlData = Proto4z.encode(ctl, "EntityControl")
    return Scene.addEntity(propData, stateData, skillData, ctlData)
end


monster = {}
entitys = {}

local OriginPos = {34, 170}
local MonsterCount = 20
local Dia = 40
function fillMonster()
    local sps = {}
    for i=0, MonsterCount do 
        table.insert(sps, getRemotePos(OriginPos, math.pi*2.0/(MonsterCount+1)*i,  Dia/2))
    end
    for _, sp in pairs(sps) do
        local eid = addMonster(sp, Proto4z.ENTITY_CAMP_NEUTRAL)
        monster[eid] = entitys[eid]
    end
end

function sceneInit()
    fillMonster()
end







PATH_PRECISION = 1.0
_sceneInit = false
standTime = 0
function onUpdate()
    if not _sceneInit then
        _sceneInit = true
        sceneInit()
    end
    for eid, e in pairs(monster) do
        if e.mv.action ~= Proto4z.MOVE_ACTION_IDLE then
            standTime = Scene.now()
            break
        end
    end
    local now = Scene.now()
    if now - standTime > 8 then
        for eid, e in pairs(monster) do
            if type(e) == "table" and e.control then
                local dist = getDistance(e.control.spawnpoint, e.mv.position)
                local rpos = {e.control.spawnpoint.x, e.control.spawnpoint.y}
                if dist < (PATH_PRECISION + Dia/10) then
                    rpos = getFarPos(rpos, getVector2(e.control.spawnpoint, OriginPos), Dia)
                    dump(rpos)
                end
                Scene.doMove(e.state.eid, Proto4z.MOVE_ACTION_PATH, 0, { rpos})
            end
        end
    end


end

function onAddEntityNotice(msg)
    logd("onAddEntityNotice sceneID=" .. Scene.sceneID)
    
    for _, client in pairs(msg.syncs) do
        logd("onAddEntityNotice sceneID=" .. Scene.sceneID .. ", add eid=" .. client.state.eid)
        local entity = entitys[client.state.eid] or {}
        entitys[client.state.eid] = entity
        entity.props = client.props
        entity.state = client.state
        entity.mv = client.mv
        entity.report = client.report
    end
end

function onRemoveEntityNotice(msg)
    logd("onRemoveEntityNotice sceneID=" .. Scene.sceneID)
    dump(msg)
    for k, eid in pairs(msg.eids) do
        logd("onRemoveEntityNotice sceneID=" .. Scene.sceneID .. ", remove eid=" .. eid)
        monster[eid] = nil
        entitys[eid] = nil
    end
end


function onSceneRefreshNotice(msg)
    logd("onSceneRefreshNotice sceneID=" .. Scene.sceneID)


    for _, state in pairs(msg.entityStates) do
        local entity =  entitys[state.eid]
        if entity then
            entity.state = state
        end
    end

    for _, mv in pairs(msg.entityMoves) do
        local entity =  entitys[mv.eid]
        if entity then
            entity.mv = mv
        end
    end

end


function onEntityScriptNotice(msg)
    --logd("onEntityScriptNotice sceneID=" .. Scene.sceneID)

    for _, ctl in pairs(msg.controls) do
        local entity =  entitys[ctl.eid]
        if entity then
            entity.control = ctl
        end
    end

    for _, skill in pairs(msg.skills) do
        local entity =  entitys[skill.eid]
        if entity then
            entity.skill = skill
        end
    end

end
















