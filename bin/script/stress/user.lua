require("proto4z")
require("ProtoCommon")
require("ProtoLogin")
require("ProtoChat")

User = {}

function User.new(...)
    local user = {}
    for k,v in pairs(User) do 
        user[k] = v 
    end
    user:ctor(...)
    return user
end

function User:ctor()
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
        self.users = nil
        local data = Proto4z.encode({uID=self.userinfo.uID}, "SelectUserReq")
	    summer.sendContent(sID, Proto4z.SelectUserReq.__getID, data)
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
       self.users = {}
       local data = Proto4z.encode({uID=self.userinfo.uID}, "SelectUserReq")
       summer.sendContent(sID, Proto4z.SelectUserReq.__getID, data)
    end
end

function User:on_SelectUserAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_SelectUserAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
    self.uID = msg.uID
    self.token = msg.token
    local data = Proto4z.encode({uID=self.uID, token=self.token}, "LinkServerReq")
    summer.sendContent(sID, Proto4z.LinkServerReq.__getID, data)  
end

-- 登录游戏
function User:on_LinkServerAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_LinkServerAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
    logi("login success. account=" .. self.account .. ", nickName=" .. self.userinfo.nickName)

    --获取自己的交友信息
	local data = Proto4z.encode({uID=self.uID}, "GetContactInfoReq")
    summer.sendContent(sID, Proto4z.GetContactInfoReq.__getID, data) 
end

-- 保存服务器端传来的交友信息
function User:on_GetContactInfoAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_GetContactInfoAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
   
    self.contact = msg.contact

    logi("on_GetContactInfoAck success. totalFriends=" .. msg.contact.totalFriends )
    dump(msg, "on_GetContactInfoAck")

    --获取一些在线的陌生人ID
    if msg.contact.totalFriends == 0 then
    	local data = Proto4z.encode({}, "GetSomeStrangersReq")
        summer.sendContent(sID, Proto4z.GetSomeStrangersReq.__getID, data) 
    end
end

function User:on_GetSomeStrangersAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_GetSomeStrangersAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
    logi("on_GetSomeStrangersAck success. #uIDs=" .. #msg.uIDs )
	dump(msg, "on_GetSomeStrangersAck")
    for _, uID in ipairs(msg.uIDs) do
        local data = Proto4z.encode({uID=uID, oFlag=Proto4z.FRIEND_ADDFRIEND}, "FriendOperationReq")
        summer.sendContent(sID, Proto4z.FriendOperationReq.__getID, data) 
    end
end

function User:on_FriendOperationAck(sID, msg)
	if msg.retCode ~= Proto4z.EC_SUCCESS then
		loge("on_GetSomeStrangersAck retcode ~= EC_SUCCESS. ret=" .. msg.retCode)
	    return
	end
    logi("on_FriendOperationAck success. srcUID=" .. msg.srcUID .. ", srcFlag=" .. msg.srcFlag .. ", dstUID=" .. msg.dstUID )
	if msg.dstUID == self.uID then
	    if msg.srcFlag == Proto4z.FRIEND_ADDFRIEND then
            local data = Proto4z.encode({uID=msg.srcUID, oFlag=Proto4z.FRIEND_ALLOW}, "FriendOperationReq")
            summer.sendContent(sID, Proto4z.FriendOperationReq.__getID, data) 
        end
	end
end
