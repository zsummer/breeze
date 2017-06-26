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

logd = summer.logd
logi = summer.logi
logw = summer.logw
loge = summer.loge
print = summer.logd
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

function getDistance(pos1, pos2)
    return ((pos2.x - pos1.x)^2 + (pos2.y - pos1.y)^2)^0.5 
end
function getRemotePos(pos, radian, dist)
    return {pos[1] + math.cos(radian) * dist, pos[2] + math.sin(radian) * dist}
end
function getFarPos(pos, vt, dist)
    dump(pos)
    dump(vt)
    dump(dist)
    local md = (vt[1]^2+vt[2]^2)^0.5
    return {pos[1] + vt[1]/md*dist, pos[2]+vt[2]/md*dist}
end








