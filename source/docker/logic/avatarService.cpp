#include "avatarService.h"
#include <ProtoClient.h>
#include <ProtoSceneServer.h>
#include <LogCommon.h>

AvatarService::AvatarService()
{

    slotting<ChatReq>(std::bind(&AvatarService::onChatReq, this, _1, _2));
    slotting<ChatResp>(std::bind(&AvatarService::onChatResp, this, _1, _2));
    slotting<PingPongReq>(std::bind(&AvatarService::onPingPongReq, this, _1, _2));
    slotting<ChangeIconIDReq>(std::bind(&AvatarService::onChangeIconIDReq, this, _1, _2));
    slotting<ChangeModeIDReq>(std::bind(&AvatarService::onChangeModeIDReq, this, _1, _2));
    
    _scene.onModuleInit(*this);


}

AvatarService::~AvatarService() 
{

}


void AvatarService::onTick(TimerID tID, ui32 count, ui32 repeat)
{
    LOGI("AvatarService::onTick");
}




void AvatarService::onClientChange()
{
    if (getClientDockerID() != InvalidDockerID && getClientSessionID() != InvalidSessionID)
    {
        AttachAvatarResp resp(EC_SUCCESS, _baseInfo._data);
        toDocker(getClientDockerID(), resp);
    }
    if (getClientSessionID() == InvalidSessionID)
    {
        if (true)
        {
            ChatResp resp;
            resp.channelID = CC_SYSTEM;
            resp.chatTime = getNowTime();
            resp.msg = "player <color=blue>[" + getServiceName() + "]</color> is offline. now online client["
                + toString(Docker::getRef().peekService(STAvatar).size()) + "].";
            for (auto kv : Docker::getRef().peekService(STAvatar))
            {
                toService(STClient, kv.second->getServiceID(), resp);
            }
        } 


        if (true)
        {
            LogQuit lq;
            lq.avatarID = _baseInfo._data.avatarID;
            lq.avatarName = _baseInfo._data.avatarName;
            lq.logTime = getNowTime();
            lq.id = 0;

            DBQueryReq req(lq.getDBInsert());
            toService(STLogDBMgr, req, NULL);
        }

    }
}

bool AvatarService::onLoad()
{
    AvatarBaseInfo ubi;
    ubi.avatarID = getServiceID();
    ubi.avatarName = getServiceName();
    _baseInfo.loadFromDB(shared_from_this(), ubi, std::bind(&AvatarService::onModuleLoad, std::static_pointer_cast<AvatarService>(shared_from_this()), _1, _2));
    return true;
}

void AvatarService::onUnload()
{
    _baseInfo.writeToDB(std::bind(&AvatarService::onModuleUnload, std::static_pointer_cast<AvatarService>(shared_from_this()), _1, _2));
}


void AvatarService::onModuleLoad(bool success, const std::string & moduleName)
{
    if (success)
    {
        _curLoadModuleCount++;
    }
    else 
    { 
        LOGE(" AvatarService::onModuleLoad false");
        return ; 
    }
    if (_curLoadModuleCount == _totalModuleCount)
    {
        //process prop
//         if (_baseInfo._data.level > 0)
//         {
//             refreshProp("hp", 1000);
//             refreshProp("hpRegen", 1);
//             refreshProp("attack", 100);
//             refreshProp("defense", 0.2);
//             refreshProp("crit", 0.1);
//             refreshProp("toughness", 0.1);
//             refreshProp("moveSpeed", 7);
//             refreshProp("attackQuick", 1);
//             refreshProp("vampirk", 0.2);
//         }
        finishLoad();
        AttachAvatarResp resp(EC_SUCCESS, _baseInfo._data);
        toDocker(getClientDockerID(), resp);
    }
    return ;
}


void AvatarService::onModuleUnload(bool success, const std::string & moduleName)
{
    if (success)
    {
        _curUnloadModuleCount++;
    }
    else
    {
        LOGE(" AvatarService::onModuleUnload false");
        return;
    }
    if (_curLoadModuleCount == _totalModuleCount)
    {
        finishUnload();
    }
    return;
}


void AvatarService::onChatReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    ChatReq req;
    rs >> req;
    LOGI("onChatReq" << req );

    ChatResp resp;
    resp.sourceID = getServiceID();
    resp.sourceName = getServiceName();
    resp.targetID = req.targetID;
    resp.msg = req.msg;
    resp.channelID = req.channelID;
    resp.chatTime = getNowTime();

    double now = getFloatSteadyNowTime();
    double limit = req.channelID == CC_WORLD ? 5.0 : 1.0;

    if (now - _lastChatTime < limit)
    {
        resp.msg = "<color=yellow>chat speed limit " + toString((int)(limit - (now - _lastChatTime))) + " s</color>";
        resp.targetID = getServiceID();
        resp.targetName = getServiceName();
        resp.channelID = CC_SYSTEM;
        resp.sourceID = 0;
        resp.sourceName = "system";
        toService(STClient, getServiceID(), resp);
        return;
    }
    _lastChatTime = now;
    if (req.channelID == CC_PRIVATE)
    {
        auto tgr = Docker::getRef().peekService(STAvatar, req.targetID);
        if (tgr)
        {
            resp.targetName = tgr->getServiceName();
        }
        toService(STClient, req.targetID, resp);
    }
    else if (req.channelID == CC_WORLD)
    {
        auto onlines = Docker::getRef().peekService(STAvatar);
        for (auto kv : onlines)
        {
            toService(STClient, kv.second->getServiceID(), resp);
        }
    }
    else if (req.channelID == CC_GROUP || req.channelID == CC_CAMP || req.channelID == CC_SCENE)
    {
        if (Docker::getRef().peekService(STWorldMgr, InvalidServiceID))
        {
            toService(STWorldMgr, trace.oob, rs.getStream(), rs.getStreamLen());
        }
        else
        {
            LOGW("STWorldMgr service not open. " << trace);
        }
    }
    if (true)
    {
        LogChat log;
        log.id = 0;
        log.channelID = resp.channelID;
        log.chatTime = resp.chatTime;
        log.sourceID = resp.sourceID;
        log.sourceName = resp.sourceName;
        log.targetID = resp.targetID;
        log.targetName = resp.targetName;
        log.msg = resp.msg;
        DBQueryReq logReq(log.getDBInsert());
        toService(STLogDBMgr, logReq);
    }
    
}



void AvatarService::onChatResp(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    toService(STClient, trace.oob, rs.getStream(), rs.getStreamLen());
}


void AvatarService::onPingPongReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    PingPongReq req;
    rs >> req;
    PingPongResp resp;
    resp.msg = req.msg;
    toService(STClient, getServiceID(), resp);
    static int testCount = 0;
    testCount++;
    if (testCount %10000 == 0)
    {
        LOGA("onPingPongReq " << *this << " count=" << testCount);
    }
}
void AvatarService::onChangeIconIDReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    ChangeIconIDReq req;
    rs >> req;
    _baseInfo._data.iconID = req.iconID;
    _baseInfo.writeToDB();
    toService(STClient, getServiceID(), AvatarBaseInfoNotice(_baseInfo._data));
    toService(STClient, getServiceID(), ChangeIconIDResp(EC_SUCCESS, req.iconID));
}
void AvatarService::onChangeModeIDReq(const Tracing & trace, zsummer::proto4z::ReadStream &rs)
{
    ChangeModeIDReq req;
    rs >> req;
    _baseInfo._data.modeID = req.modeID;
    _baseInfo.writeToDB();
    _scene.refreshGroupInfo(*this);
    toService(STClient, getServiceID(), AvatarBaseInfoNotice(_baseInfo._data));
    toService(STClient, getServiceID(), ChangeModeIDResp(EC_SUCCESS, req.modeID));
}















