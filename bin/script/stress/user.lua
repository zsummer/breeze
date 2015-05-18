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
	self.account = string.format("zhangyawei%04d", sID%1000)
    
  	local data = Proto4z.encode({account=self.account, token="token"}, "PlatAuthReq")
	summer.sendContent(sID, Proto4z.PlatAuthReq.__getID, data)
end

function User:onDisconnect(sID, remoteIP, remotePort)
	logi("session is on disconnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
end

function User:on_PlatAuthAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_PlatAuthAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
		return
	end
    dump(msg)
    self.users = msg.users
	
    local _, user = next(self.users)
    if not _ then
        local data = Proto4z.encode({nickName=self.account, iconID=1001}, "CreateUserReq")
	    summer.sendContent(sID, Proto4z.CreateUserReq.__getID, data)
    else
        self.userinfo = user
        local data = Proto4z.encode({uID=self.userinfo.uID}, "SelectUserReq")
	    summer.sendContent(sID, Proto4z.SelectUserReq.__getID, data)
        dump(self.user)
    end
end

function User:on_CreateUserAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_CreateUserAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
    dump(msg)
    self.users = msg.users
	
    local _, user = next(self.users)
    if not _ then
        loge("create user failed. account=" .. self.account )
    else
       self.userinfo = user
       local data = Proto4z.encode({uID=self.userinfo.uID}, "SelectUserReq")
       summer.sendContent(sID, Proto4z.SelectUserReq.__getID, data)
       dump(self.user)
    end
end

function User:on_SelectUserAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_SelectUserAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
    self.uID = msg.uID
    self.token = msg.token
    dump(msg)
    
end





