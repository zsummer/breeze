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
    local x1 = pos1[1] or pos1.x 
    local y1 = pos1[2] or pos1.y 
    local x2 = pos2[1] or pos2.x 
    local y2 = pos2[2] or pos2.y 
    return ((x2 - x1)^2 + (y2 - y1)^2)^0.5 
end

function getVector2(org, dst)
    local x1 = org[1] or org.x 
    local y1 = org[2] or org.y 
    local x2 = dst[1] or dst.x 
    local y2 = dst[2] or dst.y 
    return {(x2 - x1), (y2 - y1)} 
end

function getRemotePos(pos, radian, dist)
    local x = pos[1] or pos.x 
    local y = pos[2] or pos.y
    return {x + math.cos(radian) * dist, y + math.sin(radian) * dist}
end

function getFarPos(pos, vt, dist)
    local x =  pos[1] or pos.x 
    local y =  pos[2] or pos.y 
    local vx = vt[1] or vt.x   
    local vy = vt[2] or vt.y      
    local md = (vx^2+vy^2)^0.5
    return {x + vx/md*dist, y+vy/md*dist}
end








