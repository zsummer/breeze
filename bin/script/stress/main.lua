--require
--process msg
local config = require("config")
require("proto4z")
require("user")

dump = Proto4z.dump


_sessions = {}
function onConnect(sID, ip, port)
    local session = _sessions[sID]
    if not session then
        return
    end
    session.ip = ip
    session.port = port
    session.user:onConnect(sID, ip, port)
end

function onDisconnect(sID, ip, port)
    local session = _sessions[sID]
    if not session then
        return
    end
    session.user:onDisconnect(sID, ip, port)
 
end

function onMessage(sID, pID, binData)
    local name = Proto4z.getName(pID)
    if not name then
        logw("onMessage. sID=" .. sID .. ", pID=" .. pID )
        return
    end
    local msg = Proto4z.decode(binData, name)
    local session = _sessions[sID]
    if not session then
        loge("onMessage not found session data")
        return
    end
    if not session.user or not session.user["on_" .. name] then
        loge("not have the message process function. name=on_" .. name)
        return
    end
    if name == "GetContactInfoAck" then
        dump(msg)
        logd("onMessage. sID=" .. sID .. ", pID=" .. pID .. ", typename=" .. name )
    end
    session.user["on_" .. name](session.user, sID, msg)
end



--event on connect
summer.registerConnect(onConnect)

--event on recv message
summer.registerMessage(onMessage)

--event on disconnect
summer.registerDisconnect(onDisconnect)

--start summer
summer.start()
--debug.debug()
--dump(config)
--add connector
for i=1, 1 do
	local id = summer.addConnect({ip=config.connect.stress[1].ip, port=config.connect.stress[1].port, reconnect=4})
	if id == nil then
		summer.logw("id == nil when addConnect")
	end
	summer.logi("new connect id=" .. id)
    local session = {}
    _sessions[id] = session
    session.user  = User.new(sID)
end



--local jsonData = cjson.decode("{\"Himi\":\"himigame.com\"}")
--Proto4z.dump(jsonData)
--start summer event loop
while summer.runOnce() do
--	while summer.runOnce(true)  do -- call retuen is immediately.
end


