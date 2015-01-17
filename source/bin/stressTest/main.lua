--require
package.path = package.path .. ";" .. "../../../protocol/lua/?.lua"
logi = summer.logi
--print = summer.logi

require("net")


-- 连接成功事件
function onConnect(sID)
	logi("stressTest is on connected. sID=" .. sID)
  	local data = Protoz.encode({user="zhangyawei0000", passwd="123"}, "C2LS_LoginReq")
	summer.sendContent(sID, Protoz.C2LS_LoginReq.__getID, data)
end
summer.registerConnect(onConnect)

-- 收到消息
function onMessage(sID, pID, content)
	logi("onMessage. sID=" .. sID .. ", pID=" .. pID )
	Protoz.putbin(content)
	local msg = Protoz.decode(content, pID)
	Protoz.dump(msg)

end
summer.registerMessage(onMessage)

-- 连接断开事件
function onDisconnect(sID)
	logi("session is on disconnect. sID=" .. sID)
end
summer.registerDisconnect(onDisconnect)


--启动网络
summer.start()

--连接服务器
local id = summer.addConnect({ip="127.0.0.1", port=21010, reconnect=2})
if id == nil then
	summer.logw("id == nil when addConnect")
end
summer.logi("new connect id=" .. id)

--进入循环
--如果嵌入其他程序 例如cocos2dx, 可以吧runOnce设置true然后放入update中.
while 1 do
	summer.runOnce()
--	summer.runOnce(true)
end


