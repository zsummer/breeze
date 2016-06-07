require("proto4z")
require("ProtoCommon")
require("ProtoUser")


Session = {}

function Session.new(...)
    local session = {}
    for k,v in pairs(Session) do 
        session[k] = v 
    end
    session:ctor(...)
    return session
end

function Session:ctor(sID, account, token, serviceName, iconID)
    self.sID=sID
    self.account=account
    self.token=token
    self.serviceName=serviceName
    self.serviceID=0
    self.iconID = iconID
end
function Session:whenPulse(sID)
    logi("Session:whenPulse.  sID=" .. sID)
    send(sID, "ClientPulse", {})
end


function Session:whenLinked(sID, remoteIP, remotePort)
    send(sID, "ClientAuthReq", {account=self.account, token=self.token})
end

function Session:onDisconnect(sID, remoteIP, remotePort)
	logi("session is on disconnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
end

function Session:onClientAuthResp(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        if next(msg.previews) then
            self.serviceID = msg.previews[1].serviceID
            send(sID, "AttachUserReq", {serviceID=msg.previews[1].serviceID})
        else
            send(sID, "CreateUserReq", {serviceName=self.serviceName})
        end
    else
	dump(msg, "error Session:onClientAuthResp")
    end
end

function Session:onCreateUserResp(sID, msg)
    if next(msg.previews) then
        self.serviceID = msg.previews[1].serviceID
        send(sID, "AttachUserReq", {serviceID=msg.previews[1].serviceID})
    else
        loge("onCreateUserResp error.")
    end
end

function Session:onAttachUserResp(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        if math.fmod(self.serviceID, 10)  > 1 then
            send(sID, "UserChatReq", {toServiceID=self.serviceID-1, msg="hello"})
        end
        send(sID, "UserPingPongReq", { msg="hello"})
    end
end

-- 登录游戏
function Session:onUserChatResp(sID, msg)
    dump(msg)
end
-- 登录游戏
function Session:onUserPingPongResp(sID, msg)
    send(sID, "UserPingPongReq", { msg="hello"})
end
