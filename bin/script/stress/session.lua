require("proto4z")
require("ProtoCommon")
require("ProtoClient")


Session = {}

function Session.new(...)
    local session = {}
    for k,v in pairs(Session) do 
        session[k] = v 
    end
    session:ctor(...)
    return session
end

function Session:ctor(sID, account, token, avatarName, iconID)
    self.sID=sID
    self.account=account
    self.token=token
    self.avatarName=avatarName
    self.avatarID=0
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
            self.avatarID = msg.previews[1].avatarID
            send(sID, "AttachAvatarReq", {avatarID=msg.previews[1].avatarID})
        else
            send(sID, "CreateAvatarReq", {avatarName=self.avatarName})
        end
    else
    dump(msg, "error Session:onClientAuthResp")
    end
end

function Session:onCreateAvatarResp(sID, msg)
    if next(msg.previews) then
        self.avatarID = msg.previews[1].avatarID
        send(sID, "AttachAvatarReq", {avatarID=msg.previews[1].avatarID})
    else
        loge("onCreateAvatarResp error. msg.retCode=" .. msg.retCode)
    end
end

function Session:onAttachAvatarResp(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        __global_avatarID_array = __global_avatarID_array or {}
        if #__global_avatarID_array > 0 then
            local rdx = math.random(#__global_avatarID_array)
            send(sID, "ChatReq", {avatarID=__global_avatarID_array[rdx], msg="hello"})
        end
        table.insert(__global_avatarID_array, self.avatarID)
        send(sID, "PingPongReq", { msg="hello"})
    end
end

-- 登录游戏
function Session:onChatResp(sID, msg)
    dump(msg)
end
-- 登录游戏
function Session:onPingPongResp(sID, msg)
    send(sID, "PingPongReq", { msg="hello"})
end
