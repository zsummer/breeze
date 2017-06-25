--require
--process msg
require("scene")











function sceneInit()

    Scene.cleanObstacle()
    -- area map
    Scene.addObstacle({ {-74.36,17.82},  {-74.36,115},  {108,115}, {108,17.82}})
    -- tower  
    Scene.addObstacle({ {56.42102, 22.90412}, {60.42102,22.90412}, {60.42102,26.90412}, {56.42102,26.90412} })
    Scene.addObstacle({ {2.88739,97.46877}, {46.88739,97.46877}, {46.88739,101.4688}, {42.88739,101.4688} })
    Scene.addObstacle({ {74.99521,59.90725}, {80.99521,59.90725}, {80.99521,65.90725}, {74.99521,65.90725} })
    Scene.addObstacle({ {-23.42829,98.30267}, {-19.42829,98.30267}, {-19.42829,102.3027}, {-23.42829,102.3027} })
    Scene.addObstacle({ {-8.417503,22.44292}, {-4.417503,22.44292}, {-4.417503,26.44292}, {-8.417503,26.44292} })
    Scene.addObstacle({ {-46.01012,60.03914}, {-40.01012,60.03914}, {-40.01012,66.03914}, {-46.01012,66.03914} })
    -- right birth area guard
    Scene.addObstacle({ {71,42.4}, {82.1,28.5}, {108.29,5}, {134,70}, {103,125}, {82.7,97}, {70.5,84.6}, {63,62} })
    -- left birth area guard 
    Scene.addObstacle({ {-90.3,5.4}, {-48.2,30}, {-36,43.3}, {-27.5,62.5}, {-37,83.8}, {-49,95.6}, {-96.55,118.5}, {-103,45} })
    --right build 
    Scene.addObstacle({ {51.05,70.14}, {53.34,64.0}, {51.52,55.37}, {71.03,42.33}, {64.90,62.80}, {71.68,84.72} })
    Scene.addObstacle({ {-17,57.58},  {-21.23,61.90}, {-18.43,70},  {-37.45,86.0}, {-31.0,63.70}, {-36.25,42.88} })

    Scene.processObstacle()
end
sceneInit()



monster = {}
entitys = {}

local updateCount = 0
function onUpdate()
--    logd("scene_2_0 entityid=" .. Scene.sceneID)
    if not monster.init then
        monster.init = true
        local eid = addEntity(11,22)
        if eid then
            monster[eid] = 1
        end
    end

    updateCount = updateCount + 1
    if math.fmod(updateCount, 100) == 0 then
        dump(entitys)
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
        if monster[entity.state.eid] and type(monster[entity.state.eid]) ~= "table" then
            monster[entity.state.eid] = entity
        end
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
    logd("onEntityScriptNotice sceneID=" .. Scene.sceneID)

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
















