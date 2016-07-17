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

function Session:ctor(sID, account, token, userName, iconID)
    self.sID=sID
    self.account=account
    self.token=token
    self.userName=userName
    self.userID=0
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
            self.userID = msg.previews[1].userID
            send(sID, "AttachUserReq", {userID=msg.previews[1].userID})
        else
            send(sID, "CreateUserReq", {userName=self.userName})
        end
    else
	dump(msg, "error Session:onClientAuthResp")
    end
end

function Session:onCreateUserResp(sID, msg)
    if next(msg.previews) then
        self.userID = msg.previews[1].userID
        send(sID, "AttachUserReq", {userID=msg.previews[1].userID})
    else
        loge("onCreateUserResp error. msg.retCode=" .. msg.retCode)
    end
end

function Session:onAttachUserResp(sID, msg)
    if msg.retCode == Proto4z.EC_SUCCESS then
        __global_userID_array = __global_userID_array or {}
        if #__global_userID_array > 0 then
            local rdx = math.random(#__global_userID_array)
            send(sID, "UserChatReq", {touserID=__global_userID_array[rdx], msg="hello"})
        end
        table.insert(__global_userID_array, self.userID)
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
