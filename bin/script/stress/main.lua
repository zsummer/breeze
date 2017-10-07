--require
--process msg
package.path =  "../../depends/include/proto4z/?.lua;" .. package.path
local config = require("config")
require("proto4z")
require("session")

dump = Proto4z.dump
dump = function(...) end

local g_sendCount = 0
local g_lastCleanCount = os.time()

--{sID : {account, token, uID, nickName, iconID, ip, port, authed}}
-- if authed then login logic server, else login login server.
_sessions = {}

function send(sID, protoName, proto)
    logd("send " .. protoName)
    local data = Proto4z.encode(proto, protoName)
    summer.sendContent(sID, Proto4z[protoName].__protoID, data)
    g_sendCount = g_sendCount + 1

end

local function whenLinked(sID, ip, port)
    local session = _sessions[sID]
    session:whenLinked(sID, ip, port)
end
summer.whenLinked(whenLinked)

local function whenClosed(sID, ip, port)
    logi("whenClosed sID=" .. sID)
end
summer.whenClosed(whenClosed)

local function whenPulse(sID)
    session = _sessions[sID]
    if not session then
        logw("whenPulse unknown session. sID=" .. sID)
        return
    end
    session:whenPulse(sID)

    local now = os.time()
    if now - g_lastCleanCount > 0 then
        logi("send speed=" .. g_sendCount/(now - g_lastCleanCount) )
        g_lastCleanCount = now
        g_sendCount = 0
    end
end
summer.whenPulse(whenPulse)

local function whenMessage(sID, pID, binData)
    logd("whenMessage sID=" .. sID .. ", protoID=" .. pID )
    session = _sessions[sID]
    if not session then
        logw("whenMessage unknown session. sID=" .. sID)
        return
    end

    local proto = Proto4z.getName(pID)
    if not proto then
        logw("whenMessage. can not found this proto. sID=" .. sID .. ", pID=" .. pID )
        return
    end
    local msg = Proto4z.decode(binData, proto)
    if not msg then
        logw("whenMessage decode error")
        return
    end

    local session = _sessions[sID]
    if not session then
        logw("whenMessage. can not found session. sID=" .. sID .. ", pID=" .. pID )
        return
    end
    if not session["on" .. proto] then
        loge("not have the message process function. name=on_" .. proto)
        return
    end
    dump(msg, "proto=" .. proto)
    session["on" .. proto](session, sID, msg)
end
summer.whenMessage(whenMessage)






--start summer
summer.start()


for i=1, 6 do
    local cur = 2
    cur = math.fmod (i, cur) + 1
    local sID = summer.addConnect(config.docker[cur].clientPubHost, config.docker[cur].clientPubPort, nil, 0)
    if sID == nil then
        summer.logw("sID == nil when addConnect")
    else
        summer.logi("new connect sID=" .. sID)
        _sessions[sID] = Session.new(sID, string.format("test%04d", i), "111222", string.format("nick%04d", i), 0)
    end

end



summer.run()

--while summer.runOnce(true) do
--end


