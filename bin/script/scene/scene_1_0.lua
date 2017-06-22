--require
--process msg
require("scene")











function sceneInit()

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
















