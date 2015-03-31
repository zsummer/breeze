require("proto4z")
require("ProtoCommon")
require("ProtoLogin")

local messageHandler = {}

function messageHandler:ctor( ... )
	setmetatable(self, self)
	self.__index = function(obj, key)  error("function messageHandler:" .. (key or "nil") .. " is not exsit.")  end
end

function messageHandler:onMessage(sID, pID, binData)
	logd("onMessage. sID=" .. sID .. ", pID=" .. pID )
	local name = Protoz.getName(pID)
	local msg = Protoz.decode(binData, name)
	self["on_"..name](self, sID, msg)
end

function messageHandler:on_LoginAck(sID, msg)
	if msg.retCode ~= Protoz.BEC_SUCCESS and msg.retCode ~= Protoz.BEC_AUTH_ACCOUNT_INCORRECT then
			loge("LoginAck retcode ~= BEC_SUCCESS. ret=" .. msg.retCode)
			return nil
	end
	if msg.retCode == Protoz.BEC_AUTH_ACCOUNT_INCORRECT then
		local nickname = string.format("summer%04d", sID%1000)
		local data = Protoz.encode({nickName=nickname, iconID=100}, "CreateUserReq")
		summer.sendContent(sID, Protoz.CreateUserReq.__getID, data)
	else
		logi("login success.")
		Protoz.dump(msg.info, "user info:", 5)
	end
end


function messageHandler:on_CreateUserAck(sID, msg)
	if msg.retCode ~= Protoz.BEC_SUCCESS and msg.retCode ~= Protoz.BEC_AUTH_ACCOUNT_INCORRECT  then
		loge("create user error. ret=" .. msg.retCode)
		return nil
	end
	logi("create user success.")
	Protoz.dump(msg.info, "user info:", 5)
end

function messageHandler:on_ServerPulse(sID, msg)
	Protoz.dump(msg, "on_ServerPulse:", 5)
	local data = Protoz.encode({timeStamp=msg.timeStamp, timeTick=msg.timeTick}, "ServerPulseEcho")
	summer.sendContent(sID, Protoz.ServerPulseEcho.__getID, data)
end


function messageHandler:onConnect(sID)
	logd("stressTest is on connected. sID=" .. sID)
	local user = string.format("zhangyawei%04d", sID%1000)
  	local data = Protoz.encode({user=user, passwd="123"}, "LoginReq")
	summer.sendContent(sID, Protoz.LoginReq.__getID, data)
end

function messageHandler:onDisconnect(sID)
	logi("session is on disconnect. sID=" .. sID)
end

messageHandler:ctor()
return messageHandler