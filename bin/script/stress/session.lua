require("proto4z")
require("ProtoCommon")
require("ProtoLogin")
require("ProtoChat")

Session = {}

function Session.new(...)
    local session = {}
    for k,v in pairs(Session) do 
        session[k] = v 
    end
    session:ctor(...)
    return session
end

function Session:ctor(sID, account, token, nickName, iconID)
    self.sID=sID
    self.account=account
    self.token=token
    self.nickName=nickName
    self.iconID = iconID
end
function Session:whenPulse(sID)
    logi("Session:whenPulse.  sID=" .. sID)
end

function Session:onHeartbeat(sID, msg)
    send(sID, "HeartbeatEcho", {timeStamp=msg.timeStamp,timeTick=msg.timeTick})
end

function Session:whenLinked(sID, remoteIP, remotePort)
    if self.authed then
        send(sID, "AttachLogicReq", {uID=self.uID, token=self.token})
    else
        send(sID, "PlatAuthReq", {account=self.account, token=self.token})
    end
end

function Session:onDisconnect(sID, remoteIP, remotePort)
	logi("session is on disconnect. sID=" .. sID .. ", remoteIP=" .. remoteIP .. ", remotePort=" .. remotePort)
end

function Session:onPlatAuthAck(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        if next(msg.users) then
            send(sID, "SelectUserReq", {uID=msg.users[1].uID})
        else
            send(sID, "CreateUserReq", {nickName=self.nickName, iconID=self.iconID})
        end
    end
end

function Session:onCreateUserAck(sID, msg)
    if next(msg.users) then
        send(sID, "SelectUserReq", {uID=msg.users[1].uID})
    end
end

function Session:onSelectUserAck(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        self.uID = msg.uID
        self.token = msg.token
        self.ip = msg.ip
        self.port = msg.port
        self.authed = true
        summer.kick(sID)
        _sessions[sID] = nil
        local newID = summer.addConnect(self.ip, self.port, nil, 4)
        _sessions[newID] = self
    end
end

-- 登录游戏
function Session:onAttachLogicAck(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        
    end

end
