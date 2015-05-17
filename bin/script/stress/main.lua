--require
--process msg

local handler = require("script.stress.net")
local config = require("config")
dump = Proto4z.dump

--event on connect
summer.registerConnect(function(sID, ip, port)
							handler:onConnect(sID, ip, port)
						end)

--event on recv message
summer.registerMessage(function(sID, pID, binData)
							handler:onMessage(sID, pID, binData)
						end)

--event on disconnect
summer.registerDisconnect(function(sID, ip, port)
								handler:onDisconnect(sID, ip, port)
							end)

--start summer
summer.start()
--debug.debug()
--dump(config)
--add connector
for i=1, 3 do
	local id = summer.addConnect({ip=config.connect.stress[1].ip, port=config.connect.stress[1].port, reconnect=2})
	if id == nil then
		summer.logw("id == nil when addConnect")
	end
	summer.logi("new connect id=" .. id)
end



--local jsonData = cjson.decode("{\"Himi\":\"himigame.com\"}")
--Proto4z.dump(jsonData)
--start summer event loop
while 1 do
	summer.runOnce()
--	summer.runOnce(true) -- call retuen is immediately.
end


