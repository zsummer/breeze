--require
--process msg
package.path =  "../../depends/include/proto4z/?.lua;" .. package.path
local config = require("config")
require("proto4z")
require("user")

dump = Proto4z.dump



-- sID <=> user
_users = {}
function onConnect(sID, ip, port)
    local user = _users[sID]
    if not user then
        return
    end
    user.ip = ip
    user.port = port
    user:onConnect(sID, ip, port)
end

function onDisconnect(sID, ip, port)
    local user = _users[sID]
    if not user then
        return
    end
    user:onDisconnect(sID, ip, port)
end

function onMessage(sID, pID, binData)
    local proto = Proto4z.getName(pID)
    if not proto then
        logw("onMessage. can not found this proto. sID=" .. sID .. ", pID=" .. pID )
        return
    end
    local msg = Proto4z.decode(binData, proto)
    local user = _users[sID]
    if not user then
        logw("onMessage. can not found this session data (user). sID=" .. sID .. ", pID=" .. pID )
        return
    end
    if not user or not user["on_" .. proto] then
        loge("not have the message process function. name=on_" .. proto)
        return
    end
    user["on_" .. proto](user, sID, msg)
end



--event on connect
summer.whenLinked(onConnect)

--event on recv message
summer.whenMessage(onMessage)

--event on disconnect
summer.whenClosed(onDisconnect)

--start summer
summer.start()
--debug.debug()
--dump(config)
--add connector
for i=1, 3 do
	local sID = summer.addConnect(config.connect.stress[1].ip, config.connect.stress[1].port, nil, 4)
	if sID == nil then
		summer.logw("sID == nil when addConnect")
	end
	summer.logi("new connect sID=" .. sID)
    local user =  User.new()
    user.sID = sID
    _users[sID] = user
end



--local jsonData = cjson.decode("{\"Himi\":\"himigame.com\"}")
--Proto4z.dump(jsonData)
--start summer event loop
while summer.runOnce() do
--	while summer.runOnce(true)  do -- call retuen is immediately.
end


