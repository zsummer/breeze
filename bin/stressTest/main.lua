--require
package.path = package.path .. ";" .. "../../../protocol/lua/?.lua"
logd = summer.logd
logi = summer.logi
logw = summer.logw
loge = summer.loge
print = summer.logi

--process msg
local handler = require("net")

--event on connect
function onConnect(sID)
	handler:onConnect(sID)
end
summer.registerConnect(onConnect)

--event on recv message
function onMessage(sID, pID, binData)
	handler:onMessage(sID, pID, binData)
end
summer.registerMessage(onMessage)

--event on disconnect
function onDisconnect(sID)
	handler:onDisconnect(sID)
end
summer.registerDisconnect(onDisconnect)

--start summer
summer.start()

--add connector
for i=1, 3 do
	local id = summer.addConnect({ip="127.0.0.1", port=21010, reconnect=2})
	if id == nil then
		summer.logw("id == nil when addConnect")
	end
	summer.logi("new connect id=" .. id)
end

--start summer event loop
while 1 do
	summer.runOnce()
--	summer.runOnce(true) -- call retuen is immediately.
end


