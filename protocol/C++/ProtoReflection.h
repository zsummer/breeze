
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
                   return "DictGlobal";
            }
            break;
            case 1006:
            {
                   return "DictRaffleAward";
            }
            break;
            case 1007:
            {
                   return "DictRafflePool";
            }
            break;
            case 1008:
            {
                   return "DictBaseProps";
            }
            break;
            case 1009:
            {
                   return "DictItem";
            }
            break;
            case 1010:
            {
                   return "ItemInfo";
            }
            break;
            case 1011:
            {
                   return "LogChat";
            }
            break;
            case 1012:
            {
                   return "MoneyTree";
            }
            break;
            case 1013:
            {
                   return "SimplePack";
            }
            break;
            case 2000:
            {
                   return "DockerKnock";
            }
            break;
            case 2001:
            {
                   return "DockerPulse";
            }
            break;
            case 2002:
            {
                   return "LoadService";
            }
            break;
            case 2003:
            {
                   return "ServiceInfo";
            }
            break;
            case 2004:
            {
                   return "LoadServiceNotice";
            }
            break;
            case 2005:
            {
                   return "RefreshServiceToMgrNotice";
            }
            break;
            case 2006:
            {
                   return "SwitchServiceClientNotice";
            }
            break;
            case 2007:
            {
                   return "KickRealClient";
            }
            break;
            case 2008:
            {
                   return "RealClientClosedNotice";
            }
            break;
            case 2009:
            {
                   return "UnloadServiceInDocker";
            }
            break;
            case 2010:
            {
                   return "UnloadedServiceNotice";
            }
            break;
            case 2011:
            {
                   return "ShutdownClusterServer";
            }
            break;
            case 2012:
            {
                   return "ForwardToService";
            }
            break;
            case 2013:
            {
                   return "ForwardToRealClient";
            }
            break;
            case 2014:
            {
                   return "ForwardToDocker";
            }
            break;
            case 2015:
            {
                   return "DBDataResult";
            }
            break;
            case 2016:
            {
                   return "DBQueryReq";
            }
            break;
            case 2017:
            {
                   return "DBQueryResp";
            }
            break;
            case 2018:
            {
                   return "DBQueryArrayReq";
            }
            break;
            case 2019:
            {
                   return "DBQueryArrayResp";
            }
            break;
            case 2020:
            {
                   return "WebAgentClientRequestAPI";
            }
            break;
            case 2021:
            {
                   return "WebServerRequest";
            }
            break;
            case 2022:
            {
                   return "WebServerResponse";
            }
            break;
            case 2023:
            {
                   return "AvatarOffline";
            }
            break;
            case 10000:
            {
                   return "SceneGroupAvatarInfo";
            }
            break;
            case 10001:
            {
                   return "SceneGroupInfo";
            }
            break;
            case 10002:
            {
                   return "EPosition";
            }
            break;
            case 10003:
            {
                   return "SearchInfo";
            }
            break;
            case 10004:
            {
                   return "SkillBehaviour";
            }
            break;
            case 10005:
            {
                   return "SkillData";
            }
            break;
            case 10006:
            {
                   return "BuffData";
            }
            break;
            case 10007:
            {
                   return "HarmData";
            }
            break;
            case 10008:
            {
                   return "SkillInfo";
            }
            break;
            case 10009:
            {
                   return "BuffInfo";
            }
            break;
            case 10010:
            {
                   return "EntityInfo";
            }
            break;
            case 10011:
            {
                   return "EntityMove";
            }
            break;
            case 10012:
            {
                   return "EntityReport";
            }
            break;
            case 10013:
            {
                   return "EntityFullData";
            }
            break;
            case 10014:
            {
                   return "SceneSection";
            }
            break;
            case 10015:
            {
                   return "SceneEventInfo";
            }
            break;
            case 39000:
            {
                   return "SceneKnock";
            }
            break;
            case 39001:
            {
                   return "ScenePulse";
            }
            break;
            case 39002:
            {
                   return "SceneServerJoinGroupIns";
            }
            break;
            case 39003:
            {
                   return "SceneServerJoinGroupAck";
            }
            break;
            case 39004:
            {
                   return "SceneServerEnterSceneIns";
            }
            break;
            case 39005:
            {
                   return "SceneServerCancelSceneIns";
            }
            break;
            case 39006:
            {
                   return "SceneServerGroupStateChangeIns";
            }
            break;
            case 40000:
            {
                   return "ClientPulse";
            }
            break;
            case 40001:
            {
                   return "ClientAuthReq";
            }
            break;
            case 40002:
            {
                   return "ClientAuthResp";
            }
            break;
            case 40003:
            {
                   return "CreateAvatarReq";
            }
            break;
            case 40004:
            {
                   return "CreateAvatarResp";
            }
            break;
            case 40005:
            {
                   return "AttachAvatarReq";
            }
            break;
            case 40006:
            {
                   return "AttachAvatarResp";
            }
            break;
            case 40007:
            {
                   return "AvatarBaseInfoNotice";
            }
            break;
            case 40008:
            {
                   return "AvatarPropMapNotice";
            }
            break;
            case 40009:
            {
                   return "SceneGroupInfoNotice";
            }
            break;
            case 40010:
            {
                   return "SceneGroupGetReq";
            }
            break;
            case 40011:
            {
                   return "SceneGroupGetResp";
            }
            break;
            case 40012:
            {
                   return "SceneGroupEnterReq";
            }
            break;
            case 40013:
            {
                   return "SceneGroupEnterResp";
            }
            break;
            case 40014:
            {
                   return "SceneGroupCancelReq";
            }
            break;
            case 40015:
            {
                   return "SceneGroupCancelResp";
            }
            break;
            case 40016:
            {
                   return "SceneGroupCreateReq";
            }
            break;
            case 40017:
            {
                   return "SceneGroupCreateResp";
            }
            break;
            case 40018:
            {
                   return "SceneGroupJoinReq";
            }
            break;
            case 40019:
            {
                   return "SceneGroupJoinResp";
            }
            break;
            case 40020:
            {
                   return "SceneGroupInviteReq";
            }
            break;
            case 40021:
            {
                   return "SceneGroupInviteResp";
            }
            break;
            case 40022:
            {
                   return "SceneGroupInviteNotice";
            }
            break;
            case 40023:
            {
                   return "SceneGroupRejectReq";
            }
            break;
            case 40024:
            {
                   return "SceneGroupRejectResp";
            }
            break;
            case 40025:
            {
                   return "SceneGroupLeaveReq";
            }
            break;
            case 40026:
            {
                   return "SceneGroupLeaveResp";
            }
            break;
            case 40027:
            {
                   return "ChatReq";
            }
            break;
            case 40028:
            {
                   return "ChatResp";
            }
            break;
            case 40029:
            {
                   return "PingPongReq";
            }
            break;
            case 40030:
            {
                   return "PingPongResp";
            }
            break;
            case 40031:
            {
                   return "ChangeIconIDReq";
            }
            break;
            case 40032:
            {
                   return "ChangeIconIDResp";
            }
            break;
            case 40033:
            {
                   return "ChangeModeIDReq";
            }
            break;
            case 40034:
            {
                   return "ChangeModeIDResp";
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
                   return "ClientCustomReq";
            }
            break;
            case 50017:
            {
                   return "ClientCustomResp";
            }
            break;
            case 50018:
            {
                   return "ClientCustomNotice";
            }
            break;
            case 50019:
            {
                   return "ClientPingTestReq";
            }
            break;
            case 50020:
            {
                   return "ClientPingTestResp";
            }
            break;
            case 50021:
            {
                   return "SceneEventNotice";
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


