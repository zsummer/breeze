require("proto4z")
require("ProtoCommon")
require("ProtoLogin")

local messageHandler = {}

function messageHandler:onConnect(sID)
	logd("stressTest is on connected. sID=" .. sID)
	local user = string.format("zhangyawei%04d", sID%1000)
  	local data = Protoz.encode({user=user, passwd="123"}, "C2LS_LoginReq")
	summer.sendContent(sID, Protoz.C2LS_LoginReq.__getID, data)
end

function messageHandler:onMessage(sID, pID, binData)
	logd("onMessage. sID=" .. sID .. ", pID=" .. pID )
	local msg = Protoz.decode(binData, pID)
	if pID == Protoz.LS2C_LoginAck.__getID then
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
	elseif pID == Protoz.LS2C_CreateUserAck.__getID then
		if msg.retCode ~= Protoz.BEC_SUCCESS or msg.needCreateUser > 0 then
			loge("create user error. ret=" .. msg.retCode .. ", need change name = " .. msg.needCreateUser)
			return nil
		end
		logi("create user success.")
		Protoz.dump(msg.info, "user info:", 5)
	elseif pID == Protoz.AS2C_ServerPulse.__getID then
		summer.sendContent(sID, Protoz.C2AS_ClientPulse.__getID, "")
	end
end

function messageHandler:onDisconnect(sID)
	logi("session is on disconnect. sID=" .. sID)
end


return messageHandler