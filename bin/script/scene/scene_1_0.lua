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

    local skill = {dictEquippedSkills = {[5]=0}, readySkillID = 5 , combating = 1  }
    if camp < Proto4z.ENTITY_CAMP_NEUTRAL then
        skill = {dictEquippedSkills = {[3]=0}, readySkillID = 3 , combating = 1  }
    end
    local ctl = {spawnpoint = {x=pos.x or pos[1], y=pos.y or pos[2]},  collision=1 }

    local propData = Proto4z.encode(prop, "DictProp")
    local stateData = Proto4z.encode(state, "EntityState")
    local skillData = Proto4z.encode(skill, "EntitySkillSystem")
    local ctlData = Proto4z.encode(ctl, "EntityControl")
    return Scene.addEntity(propData, stateData, skillData, ctlData)
end






function fillObstacle()
    Scene.cleanObstacle()
    -- area map
    Scene.addObstacle({ {-74.36,17.82},  {-74.36,115},  {108,115}, {108,17.82}})
    -- tower  
    Scene.addObstacle({ {56.42102, 22.90412}, {60.42102,22.90412}, {60.42102,26.90412}, {56.42102,26.90412} })
    Scene.addObstacle({ {42.88739,97.46877}, {46.88739,97.46877}, {46.88739,101.4688}, {42.88739,101.4688} })
    Scene.addObstacle({ {74.99521,59.90725}, {80.99521,59.90725}, {80.99521,65.90725}, {74.99521,65.90725} })
    Scene.addObstacle({ {-23.42829,98.30267}, {-19.42829,98.30267}, {-19.42829,102.3027}, {-23.42829,102.3027} })
    Scene.addObstacle({ {-8.417503,22.44292}, {-4.417503,22.44292}, {-4.417503,26.44292}, {-8.417503,26.44292} })
    Scene.addObstacle({ {-46.01012,60.03914}, {-40.01012,60.03914}, {-40.01012,66.03914}, {-46.01012,66.03914} })
    -- right birth area guard
    --Scene.addObstacle({ {71,42.4}, {82.1,28.5}, {108.29,5}, {134,70}, {103,125}, {82.7,97}, {70.5,84.6}, {63,62} })
    -- left birth area guard 
    --Scene.addObstacle({ {-90.3,5.4}, {-48.2,30}, {-36,43.3}, {-27.5,62.5}, {-37,83.8}, {-49,95.6}, {-96.55,118.5}, {-103,45} })
    --right build 
    Scene.addObstacle({ {51.05,70.14}, {53.34,64.0}, {51.52,55.37}, {71.03,42.33}, {64.90,62.80}, {71.68,84.72} })
    Scene.addObstacle({ {-17,57.58},  {-21.23,61.90}, {-18.43,70},  {-37.45,86.0}, {-31.0,63.70}, {-36.25,42.88} })

    Scene.processObstacle()
end

monster = {}
walker = {}
entitys = {}

campWaypoints = {
    [Proto4z.ENTITY_CAMP_BLUE] = {{86.8,90.4}, {44.7,95}, {-20.7,95},  {-52.7,90}},
    [Proto4z.ENTITY_CAMP_RED] = {{-52.7,90}, {-20.7,95}, {44.7,95}, {86.8,90.4}}
}

local lastSpawnWalker = 0
local lastWalkerback = 0
function updateWalker()
    local now = Scene.now()
    if now - lastSpawnWalker > 15 then
        lastSpawnWalker = now
        
        dump(campWaypoints)
        local blueSpPos = campWaypoints[Proto4z.ENTITY_CAMP_BLUE][1]
        local eid = addMonster(blueSpPos, Proto4z.ENTITY_CAMP_BLUE, "blue_walker")
        walker[eid] = entitys[eid]

        local redSpPos = campWaypoints[Proto4z.ENTITY_CAMP_RED][1]
        eid = addMonster(redSpPos, Proto4z.ENTITY_CAMP_RED, "red_walker")
        walker[eid] = entitys[eid]
    end
    local removes = {}
    for k,e in pairs(walker) do
        if e.state.state ~= Proto4z.ENTITY_STATE_ACTIVE then
            removes[k] = 1
        else 
            if now - lastWalkerback > 3.0 then
                lastWalkerback = now
                if  e.mv.action == Proto4z.MOVE_ACTION_IDLE or e.mv.action == Proto4z.MOVE_ACTION_FOLLOW then
                    local way = Scene.wayFinding(e.mv.position, campWaypoints[e.state.camp])
                    if not way or not way[1] or getDistance(way[#way], e.mv.position) < (Scene.pathPrecision + e.control.collision)*1.2  then
                        dump(way, "camp=" .. e.state.camp)
                        removes[k] = 1
                    else
                        dump(way, "camp=" .. e.state.camp)
                        Scene.doMove(e.state.eid, Proto4z.MOVE_ACTION_FORCE_PATH, 0, {way[1]})
                    end
                end
            elseif e.mv.action == Proto4z.MOVE_ACTION_IDLE  and e.skill  and  now - e.skill.breakoffAttackTime  > 3.0  then
                local way = Scene.wayFinding(e.mv.position, campWaypoints[e.state.camp])
                if not way or not way[1] or getDistance(way[#way], e.mv.position) < (Scene.pathPrecision + e.control.collision)*1.2  then
                    dump(way, "camp=" .. e.state.camp)
                    removes[k] = 1
                else
                    dump(way, "camp=" .. e.state.camp)
                    Scene.doMove(e.state.eid, Proto4z.MOVE_ACTION_PATH, 0, way)
                end
            end
        end
    end
    for k,_ in pairs(removes) do
        Scene.removeEntity(k)
    end
end

function fillMonster()
    local sps = {{51.92,80.98 },
                    {-15.90,43.03 },
                    {47.45,63.14 },
                    {-13.15,63.14 },
                    {52.05,43.08 },
                    {3.65,44.45 },
                    {25.84,44.65 },
                    {33.58,81.71 },
                    {10.63,81.18 },
                    {-17.07,80.59 }}

    for _, sp in pairs(sps) do
        local eid = addMonster(sp, Proto4z.ENTITY_CAMP_NEUTRAL, "monster")
        monster[eid] = entitys[eid]
    end

end

function sceneInit()

    fillObstacle()
    fillMonster()



end







PATH_PRECISION = 1.0
_sceneInit = false
function onUpdate()
    if not _sceneInit then
        _sceneInit = true
        sceneInit()
    end
    updateWalker()

    for eid, e in pairs(monster) do
        if type(e) == "table" and e.control then
            local dist = getDistance(e.control.spawnpoint, e.mv.position)
            local back = false
            if dist > 20 then
                back = true
            end
            if dist > e.control.collision + PATH_PRECISION and e.state.foe == 0 then
                back = true
            end

            if e.state.foe == 0 and e.mv.action == Proto4z.MOVE_ACTION_FOLLOW then
                back = true
            end

            if back and e.mv.action ~= Proto4z.MOVE_ACTION_FORCE_PATH then
                Scene.doMove(e.state.eid, Proto4z.MOVE_ACTION_FORCE_PATH, 0, { {e.control.spawnpoint.x, e.control.spawnpoint.y} })
            end
        end

    end

end

function onAddEntityNotice(msg)
    if not msg.syncs or #msg.syncs == 0 then
        loge("onAddEntityNotice sceneID=" .. Scene.sceneID)
    end
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
        walker[eid] = nil
    end
end


function onSceneRefreshNotice(msg)
    --logd("onSceneRefreshNotice sceneID=" .. Scene.sceneID)


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
















