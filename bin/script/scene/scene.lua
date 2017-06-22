--require
--process msg

require("proto4z")

require("DictCommon")
require("DictScene")
require("ProtoCommon")
require("ProtoDocker")

require("ProtoSceneCommon")
require("ProtoSceneServer")
require("ProtoSceneClient")



dump = Proto4z.dump
--[[
Scene.__scene,  --point
Scene.sceneType,
Scene.mapID,
Scene.sceneID,
function Scene.addEntity()
    return {eid, data}
end
]]--
dump(Scene)

function addEntity(pos)
    local prop = {hp=1000, attak=100, attackQuick=1, moveSpeed=8}
    local state = {modelID=math.random(1,20), avatarName="scripts", camp=Proto4z.ENTITY_CAMP_NEUTRAL, maxHP=prop.hp, curHP=prop.hp, etype=Proto4z.ENTITY_AI, state=Proto4z.ENTITY_STATE_ACTIVE}
    local skill = {dictEquippedSkills = {[2]=0}, readySkillID = 2 , combating = 1  }
    local ctl = {spawnpoint = pos,  collision=1 }

    local propData = Proto4z.encode(prop, "DictProp")
    local stateData = Proto4z.encode(state, "EntityState")
    local skillData = Proto4z.encode(skill, "EntitySkillSystem")
    local ctlData = Proto4z.encode(ctl, "EntityControl")
    logd("prop len=" .. #propData .. ", state len=" .. #stateData)
    return Scene.addEntity(propData, stateData, skillData, ctlData)
end





function onSyncEntry(protoName, binData)
    local len, msg = Proto4z.unpack(binData, protoName)
    if not msg then
        logw("onSyncEntry decode error")
        return
    end
    local pfunc = _G["on" .. protoName]
    if pfunc then 
        pfunc (msg)
    else 
        logd("not found proto [" .. protoName .. "] process function.")
    end
end











