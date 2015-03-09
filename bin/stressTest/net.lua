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

function messageHandler:on_LS2C_LoginAck(sID, msg)
	if msg.retCode ~= Protoz.BEC_SUCCESS then
			loge("LS2C_LoginAck retcode ~= BEC_SUCCESS. ret=" .. msg.retCode)
			return nil
	end
	if msg.needCreateUser > 0 then
		local nickname = string.format("summer%04d", sID%1000)
		local data = Protoz.encode({nickName=nickname, iconID=100}, "C2LS_CreateUserReq")
		summer.sendContent(sID, Protoz.C2LS_CreateUserReq.__getID, data)
	else
		logi("login success.")
		Protoz.dump(msg.info, "user info:", 5)
	end
end


function messageHandler:on_LS2C_CreateUserAck(sID, msg)
	if msg.retCode ~= Protoz.BEC_SUCCESS or msg.needCreateUser > 0 then
		loge("create user error. ret=" .. msg.retCode .. ", need change name = " .. msg.needCreateUser)
		return nil
	end
	logi("create user success.")
	Protoz.dump(msg.info, "user info:", 5)
end

function messageHandler:on_X2X_ServerPulse(sID, msg)
	Protoz.dump(msg, "on_X2X_ServerPulse:", 5)
	local data = Protoz.encode({timeStamp=msg.timeStamp, timeTick=msg.timeTick}, "X2X_ServerPulse")
	summer.sendContent(sID, Protoz.X2X_ServerPulse.__getID, data)
end


function messageHandler:onConnect(sID)
	logd("stressTest is on connected. sID=" .. sID)
	local user = string.format("zhangyawei%04d", sID%1000)
  	local data = Protoz.encode({user=user, passwd="123"}, "C2LS_LoginReq")
	summer.sendContent(sID, Protoz.C2LS_LoginReq.__getID, data)
end

function messageHandler:onDisconnect(sID)
	logi("session is on disconnect. sID=" .. sID)
end

messageHandler:ctor()
return messageHandler