require("proto4z")
require("ProtoCommon")
require("ProtoLogin")

User = {}

function User.new(...)
    local user = {}
    for k,v in pairs(User) do 
        user[k] = v 
    end
    user:ctor(...)
    return user
end

function User:ctor(sID)
    _sID = sID
end

function User:onConnect(sID, remoteIP, remotePort)
	logd("User:onConnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
	local user = string.format("zhangyawei%04d", sID%1000)
  	local data = Proto4z.encode({account=user, token="token"}, "PlatAuthReq")
	summer.sendContent(sID, Proto4z.PlatAuthReq.__getID, data)
end

function User:onDisconnect(sID, remoteIP, remotePort)
	logi("session is on disconnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
end

function User:on_PlatAuthAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
			loge("on_PlatAuthAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
			return nil
	end
	dump(msg)
end


