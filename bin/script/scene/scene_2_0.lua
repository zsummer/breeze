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


