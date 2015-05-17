require("proto4z")
require("ProtoCommon")
require("ProtoLogin")

local messageHandler = {}

function messageHandler:ctor( ... )
	setmetatable(self, self)
	self.__index = function(obj, key)  error("function messageHandler:" .. (key or "nil") .. " is not exsit.")  end
end

function messageHandler:onMessage(sID, pID, binData)
	local name = Proto4z.getName(pID)
	if name then
		logd("onMessage. sID=" .. sID .. ", pID=" .. pID .. ", typename=" .. name )
		local msg = Proto4z.decode(binData, name)
		self["on_"..name](self, sID, msg)
	else
		logw("onMessage. sID=" .. sID .. ", pID=" .. pID )
	end
end

function messageHandler:on_LoginAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
			loge("LoginAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
			return nil
	end
	if msg.needCreate ~= 0 then
		summer.post(1000, function()
							local nickname = string.format("summer%04d", sID%1000)
							local data = Proto4z.encode({nickName=nickname, iconID=100}, "CreateUserReq")
							summer.sendContent(sID, Proto4z.CreateUserReq.__getID, data)
						end)

	else
		logi("login success.")
		Proto4z.dump(msg.info, "user info:", 5)
	end
end




function messageHandler:on_ServerPulse(sID, msg)
	Proto4z.dump(msg, "on_ServerPulse:", 5)
	local data = Proto4z.encode({timeStamp=msg.timeStamp, timeTick=msg.timeTick}, "ServerPulseEcho")
	summer.sendContent(sID, Proto4z.ServerPulseEcho.__getID, data)
end


function messageHandler:onConnect(sID, remoteIP, remotePort)
	logd("stressTest is on connected. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
	local user = string.format("zhangyawei%04d", sID%1000)
  	local data = Proto4z.encode({user=user, passwd="123"}, "LoginReq")
	summer.sendContent(sID, Proto4z.LoginReq.__getID, data)
end

function messageHandler:onDisconnect(sID, remoteIP, remotePort)
	logi("session is on disconnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
end

messageHandler:ctor()
return messageHandler