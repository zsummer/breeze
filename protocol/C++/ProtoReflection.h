
#ifndef _ProtoReflection_H_ 
#define _ProtoReflection_H_ 
class ProtoReflection
{
public:
    static std::string getProtoName(ui16 protoID)
    {
        switch (protoID)
        {
            case 0:
            {
                return "InvalidProtoID";
            }
            break;
            case 1000:
            {
                   return "Routing";
            }
            break;
            case 1001:
            {
                   return "OutOfBand";
            }
            break;
            case 1002:
            {
                   return "Tracing";
            }
            break;
            case 1003:
            {
                   return "AvatarPreview";
            }
            break;
            case 1004:
            {
                   return "AvatarBaseInfo";
            }
            break;
            case 1005:
            {
                   return "ItemInfo";
            }
            break;
            case 1006:
            {
                   return "LogChat";
            }
            break;
            case 1007:
            {
                   return "MoneyTree";
            }
            break;
            case 1008:
            {
                   return "SimplePack";
            }
            break;
            case 2000:
            {
                   return "SceneGroupAvatarInfo";
            }
            break;
            case 2001:
            {
                   return "SceneGroupInfo";
            }
            break;
            case 2002:
            {
                   return "EPosition";
            }
            break;
            case 2003:
            {
                   return "SceneEventInfo";
            }
            break;
            case 2004:
            {
                   return "EntityState";
            }
            break;
            case 2005:
            {
                   return "EntityMove";
            }
            break;
            case 2006:
            {
                   return "EntityReport";
            }
            break;
            case 2007:
            {
                   return "EntityControl";
            }
            break;
            case 2008:
            {
                   return "EntityClientSync";
            }
            break;
            case 2009:
            {
                   return "SceneSection";
            }
            break;
            case 2010:
            {
                   return "EntitySkillInfo";
            }
            break;
            case 2011:
            {
                   return "EntityBuffInfo";
            }
            break;
            case 2012:
            {
                   return "EntitySkillSystem";
            }
            break;
            case 3000:
            {
                   return "DockerKnock";
            }
            break;
            case 3001:
            {
                   return "DockerPulse";
            }
            break;
            case 3002:
            {
                   return "LoadService";
            }
            break;
            case 3003:
            {
                   return "ServiceInfo";
            }
            break;
            case 3004:
            {
                   return "LoadServiceNotice";
            }
            break;
            case 3005:
            {
                   return "RefreshServiceToMgrNotice";
            }
            break;
            case 3006:
            {
                   return "SwitchServiceClientNotice";
            }
            break;
            case 3007:
            {
                   return "KickRealClient";
            }
            break;
            case 3008:
            {
                   return "RealClientClosedNotice";
            }
            break;
            case 3009:
            {
                   return "UnloadServiceInDocker";
            }
            break;
            case 3010:
            {
                   return "UnloadedServiceNotice";
            }
            break;
            case 3011:
            {
                   return "ShutdownClusterServer";
            }
            break;
            case 3012:
            {
                   return "ForwardToService";
            }
            break;
            case 3013:
            {
                   return "ForwardToRealClient";
            }
            break;
            case 3014:
            {
                   return "ForwardToDocker";
            }
            break;
            case 3015:
            {
                   return "ReloadDBDictNotice";
            }
            break;
            case 3016:
            {
                   return "ReloadDBDictFinish";
            }
            break;
            case 3017:
            {
                   return "KickClientsNotice";
            }
            break;
            case 3018:
            {
                   return "DBDataResult";
            }
            break;
            case 3019:
            {
                   return "DBQueryReq";
            }
            break;
            case 3020:
            {
                   return "DBQueryResp";
            }
            break;
            case 3021:
            {
                   return "DBQueryArrayReq";
            }
            break;
            case 3022:
            {
                   return "DBQueryArrayResp";
            }
            break;
            case 3023:
            {
                   return "WebAgentClientRequestAPI";
            }
            break;
            case 3024:
            {
                   return "WebServerRequest";
            }
            break;
            case 3025:
            {
                   return "WebServerResponse";
            }
            break;
            case 3026:
            {
                   return "AvatarOffline";
            }
            break;
            case 4000:
            {
                   return "SceneKnock";
            }
            break;
            case 4001:
            {
                   return "ScenePulse";
            }
            break;
            case 4002:
            {
                   return "SceneServerJoinGroupIns";
            }
            break;
            case 4003:
            {
                   return "SceneServerJoinGroupAck";
            }
            break;
            case 4004:
            {
                   return "SceneServerEnterSceneIns";
            }
            break;
            case 4005:
            {
                   return "SceneServerCancelSceneIns";
            }
            break;
            case 4006:
            {
                   return "SceneServerGroupStateFeedback";
            }
            break;
            case 4007:
            {
                   return "EntityControlNotice";
            }
            break;
            case 4008:
            {
                   return "EntityScriptNotice";
            }
            break;
            case 10000:
            {
                   return "DictPairValue";
            }
            break;
            case 10001:
            {
                   return "DictGlobal";
            }
            break;
            case 10002:
            {
                   return "DictDrop";
            }
            break;
            case 10003:
            {
                   return "DictItem";
            }
            break;
            case 11000:
            {
                   return "DictProp";
            }
            break;
            case 11001:
            {
                   return "AOESearch";
            }
            break;
            case 11002:
            {
                   return "DictBuff";
            }
            break;
            case 11003:
            {
                   return "DictSkill";
            }
            break;
            case 20000:
            {
                   return "LogLogin";
            }
            break;
            case 20001:
            {
                   return "LogQuit";
            }
            break;
            case 50000:
            {
                   return "SceneClientPulse";
            }
            break;
            case 50001:
            {
                   return "AttachSceneReq";
            }
            break;
            case 50002:
            {
                   return "AttachSceneResp";
            }
            break;
            case 50003:
            {
                   return "SceneSectionNotice";
            }
            break;
            case 50004:
            {
                   return "SceneRefreshNotice";
            }
            break;
            case 50005:
            {
                   return "SceneReportsNotice";
            }
            break;
            case 50006:
            {
                   return "AddEntityNotice";
            }
            break;
            case 50007:
            {
                   return "RemoveEntityNotice";
            }
            break;
            case 50008:
            {
                   return "MoveReq";
            }
            break;
            case 50009:
            {
                   return "MoveResp";
            }
            break;
            case 50010:
            {
                   return "MoveNotice";
            }
            break;
            case 50011:
            {
                   return "AddBuffNotice";
            }
            break;
            case 50012:
            {
                   return "RemoveBuffNotice";
            }
            break;
            case 50013:
            {
                   return "UseSkillReq";
            }
            break;
            case 50014:
            {
                   return "UseSkillResp";
            }
            break;
            case 50015:
            {
                   return "UseSkillNotice";
            }
            break;
            case 50016:
            {
                   return "SceneEventNotice";
            }
            break;
            case 50017:
            {
                   return "ClientCustomReq";
            }
            break;
            case 50018:
            {
                   return "ClientCustomResp";
            }
            break;
            case 50019:
            {
                   return "ClientCustomNotice";
            }
            break;
            case 50020:
            {
                   return "ClientPingTestReq";
            }
            break;
            case 50021:
            {
                   return "ClientPingTestResp";
            }
            break;
            case 55000:
            {
                   return "ClientPulse";
            }
            break;
            case 55001:
            {
                   return "ClientAuthReq";
            }
            break;
            case 55002:
            {
                   return "ClientAuthResp";
            }
            break;
            case 55003:
            {
                   return "CreateAvatarReq";
            }
            break;
            case 55004:
            {
                   return "CreateAvatarResp";
            }
            break;
            case 55005:
            {
                   return "AttachAvatarReq";
            }
            break;
            case 55006:
            {
                   return "AttachAvatarResp";
            }
            break;
            case 55007:
            {
                   return "AvatarBaseInfoNotice";
            }
            break;
            case 55008:
            {
                   return "AvatarPropMapNotice";
            }
            break;
            case 55009:
            {
                   return "SceneGroupInfoNotice";
            }
            break;
            case 55010:
            {
                   return "SceneGroupGetReq";
            }
            break;
            case 55011:
            {
                   return "SceneGroupGetResp";
            }
            break;
            case 55012:
            {
                   return "SceneGroupEnterReq";
            }
            break;
            case 55013:
            {
                   return "SceneGroupEnterResp";
            }
            break;
            case 55014:
            {
                   return "SceneGroupCancelReq";
            }
            break;
            case 55015:
            {
                   return "SceneGroupCancelResp";
            }
            break;
            case 55016:
            {
                   return "SceneGroupCreateReq";
            }
            break;
            case 55017:
            {
                   return "SceneGroupCreateResp";
            }
            break;
            case 55018:
            {
                   return "SceneGroupJoinReq";
            }
            break;
            case 55019:
            {
                   return "SceneGroupJoinResp";
            }
            break;
            case 55020:
            {
                   return "SceneGroupInviteReq";
            }
            break;
            case 55021:
            {
                   return "SceneGroupInviteResp";
            }
            break;
            case 55022:
            {
                   return "SceneGroupInviteNotice";
            }
            break;
            case 55023:
            {
                   return "SceneGroupRejectReq";
            }
            break;
            case 55024:
            {
                   return "SceneGroupRejectResp";
            }
            break;
            case 55025:
            {
                   return "SceneGroupLeaveReq";
            }
            break;
            case 55026:
            {
                   return "SceneGroupLeaveResp";
            }
            break;
            case 55027:
            {
                   return "ChatReq";
            }
            break;
            case 55028:
            {
                   return "ChatResp";
            }
            break;
            case 55029:
            {
                   return "PingPongReq";
            }
            break;
            case 55030:
            {
                   return "PingPongResp";
            }
            break;
            case 55031:
            {
                   return "ChangeIconIDReq";
            }
            break;
            case 55032:
            {
                   return "ChangeIconIDResp";
            }
            break;
            case 55033:
            {
                   return "ChangeModeIDReq";
            }
            break;
            case 55034:
            {
                   return "ChangeModeIDResp";
            }
            break;
            case 55035:
            {
                   return "ClientDeviceInfoUpdate";
            }
            break;

        }
        char buf[20];
        printf(buf, protoID);
        return std::string("UnknownProtoID_") + buf;
    }

    static std::string getErrorDesc(ui16 errCode)
    {
        switch (errCode)
        {
            case 0:
            {
                   return "成功";
            }
            break;
            case 1:
            {
                   return "错误";
            }
            break;
            case 2:
            {
                   return "内部错误";
            }
            break;
            case 3:
            {
                   return "数据库错误";
            }
            break;
            case 4:
            {
                   return "非法参数";
            }
            break;
            case 5:
            {
                   return "权限错误";
            }
            break;
            case 6:
            {
                   return "请求操作已过期";
            }
            break;
            case 7:
            {
                   return "操作目标不存在";
            }
            break;
            case 8:
            {
                   return "令牌过期";
            }
            break;
            case 50:
            {
                   return "错误的用户信息";
            }
            break;
            case 51:
            {
                   return "创建用户的数量超出限制";
            }
            break;
            case 52:
            {
                   return "创建用户的频率超出限制";
            }
            break;
            case 53:
            {
                   return "创建用户的昵称冲突";
            }
            break;
            case 100:
            {
                   return "请先删除与该好友建立的关系";
            }
            break;
            case 101:
            {
                   return "达到好友上限";
            }
            break;
            case 102:
            {
                   return "不能添加对方为好友";
            }
            break;
            case 103:
            {
                   return "好友不存在";
            }
            break;
            case 104:
            {
                   return "服务未开放";
            }
            break;

        }
        char buf[20];
        printf(buf, errCode);
        return std::string("UnknownErrorCode_") + buf;
    }
};

#endif


