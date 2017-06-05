--require
--process msg
package.path =  "../../depends/include/proto4z/?.lua;" .. package.path
local config = require("config")
require("proto4z")

dump = Proto4z.dump
--[[
Scene.__scene,  --point
Scene.sceneType,
Scene.mapID,
Scene.sceneID,
function Scene.getEntity(eid)
    return {eid, data}
end
]]--
dump(Scene)

function sceneInit()

end
sceneInit()



function onUpdate()
--    logd("scene_2_0 entityid=" .. Scene.sceneID)
end

function onSyncEntry(protoName, binData)
    local len, msg = Proto4z.unpack(binData, protoName)
    if not msg then
        logw("onSyncEntry decode error")
        return
    end
    --dump(msg)
end