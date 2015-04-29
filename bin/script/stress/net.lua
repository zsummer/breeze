require("proto4z")
require("ProtoCommon")
require("ProtoLogin")

local messageHandler = {}

function messageHandler:ctor( ... )
	setmetatable(self, self)
	self.__index = function(obj, key)  error("function messageHandler:" .. (key or "nil") .. " is not exsit.")  end
end

function messageHandler:onMessage(sID, pID, binData)
	local name = Protoz.getName(pID)
	if name then
		logd("onMessage. sID=" .. sID .. ", pID=" .. pID .. ", typename=" .. name )
		local msg = Protoz.decode(binData, name)
		self["on_"..name](self, sID, msg)
	else
		logw("onMessage. sID=" .. sID .. ", pID=" .. pID )
	end
end

function messageHandler:on_LoginAck(sID, msg)
	if msg.retCode ~= Protoz.EC_SUCCESS then
			loge("LoginAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
			return nil
	end
	if msg.needCreate ~= 0 then
		summer.post(1000, function()
							local nickname = string.format("summer%04d", sID%1000)
							local data = Protoz.encode({nickName=nickname, iconID=100}, "CreateUserReq")
							summer.sendContent(sID, Protoz.CreateUserReq.__getID, data)
						end)

	else
		logi("login success.")
		Protoz.dump(msg.info, "user info:", 5)
	end
end




function messageHandler:on_ServerPulse(sID, msg)
	Protoz.dump(msg, "on_ServerPulse:", 5)
	local data = Protoz.encode({timeStamp=msg.timeStamp, timeTick=msg.timeTick}, "ServerPulseEcho")
	summer.sendContent(sID, Protoz.ServerPulseEcho.__getID, data)
end


function messageHandler:onConnect(sID, remoteIP, remotePort)
	logd("stressTest is on connected. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
	local user = string.format("zhangyawei%04d", sID%1000)
  	local data = Protoz.encode({user=user, passwd="123"}, "LoginReq")
	summer.sendContent(sID, Protoz.LoginReq.__getID, data)
end

function messageHandler:onDisconnect(sID, remoteIP, remotePort)
	logi("session is on disconnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
end

messageHandler:ctor()
return messageHandler