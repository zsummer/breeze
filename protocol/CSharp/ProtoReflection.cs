
namespace Proto4z
{
    static class Reflection
    {
        public static ushort getProtoID(string protoName)
        {
            try
            {
                return _nameToID[protoName];
            }
            catch (System.Exception)
            {
            }
            return 0;
        }
        public static string getProtoName(ushort protoID)
        {
            try
            {
                return _idToName[protoID];
            }
            catch (System.Exception)
            {
            }
            return "UnknownProtoID_" + protoID;
        }
        public static string getErrorDesc(ushort errCode)
        {
            try
            {
                return _errCodes[errCode];
            }
            catch (System.Exception)
            {
            }
            return "UnknownErrorCode_" + errCode;
        }
        static System.Collections.Generic.Dictionary<string, ushort> _nameToID = new System.Collections.Generic.Dictionary<string, ushort>();
        static System.Collections.Generic.Dictionary<ushort, string> _idToName = new System.Collections.Generic.Dictionary<ushort, string>();
        static System.Collections.Generic.Dictionary<ushort, string> _errCodes = new System.Collections.Generic.Dictionary<ushort, string>();
        static Reflection()
        {
        

                    
            _nameToID.Add("Routing", 1000);
            _idToName.Add(1000, "Routing");
            _nameToID.Add("OutOfBand", 1001);
            _idToName.Add(1001, "OutOfBand");
            _nameToID.Add("Tracing", 1002);
            _idToName.Add(1002, "Tracing");
            _nameToID.Add("AvatarPreview", 1003);
            _idToName.Add(1003, "AvatarPreview");
            _nameToID.Add("AvatarBaseInfo", 1004);
            _idToName.Add(1004, "AvatarBaseInfo");
            _nameToID.Add("DictGlobal", 1005);
            _idToName.Add(1005, "DictGlobal");
            _nameToID.Add("DictRaffleAward", 1006);
            _idToName.Add(1006, "DictRaffleAward");
            _nameToID.Add("DictRafflePool", 1007);
            _idToName.Add(1007, "DictRafflePool");
            _nameToID.Add("DictBaseProps", 1008);
            _idToName.Add(1008, "DictBaseProps");
            _nameToID.Add("DictItem", 1009);
            _idToName.Add(1009, "DictItem");
            _nameToID.Add("ItemInfo", 1010);
            _idToName.Add(1010, "ItemInfo");
            _nameToID.Add("LogChat", 1011);
            _idToName.Add(1011, "LogChat");
            _nameToID.Add("MoneyTree", 1012);
            _idToName.Add(1012, "MoneyTree");
            _nameToID.Add("SimplePack", 1013);
            _idToName.Add(1013, "SimplePack");
            _nameToID.Add("DockerKnock", 2000);
            _idToName.Add(2000, "DockerKnock");
            _nameToID.Add("DockerPulse", 2001);
            _idToName.Add(2001, "DockerPulse");
            _nameToID.Add("LoadService", 2002);
            _idToName.Add(2002, "LoadService");
            _nameToID.Add("ServiceInfo", 2003);
            _idToName.Add(2003, "ServiceInfo");
            _nameToID.Add("LoadServiceNotice", 2004);
            _idToName.Add(2004, "LoadServiceNotice");
            _nameToID.Add("RefreshServiceToMgrNotice", 2005);
            _idToName.Add(2005, "RefreshServiceToMgrNotice");
            _nameToID.Add("SwitchServiceClientNotice", 2006);
            _idToName.Add(2006, "SwitchServiceClientNotice");
            _nameToID.Add("KickRealClient", 2007);
            _idToName.Add(2007, "KickRealClient");
            _nameToID.Add("RealClientClosedNotice", 2008);
            _idToName.Add(2008, "RealClientClosedNotice");
            _nameToID.Add("UnloadServiceInDocker", 2009);
            _idToName.Add(2009, "UnloadServiceInDocker");
            _nameToID.Add("UnloadedServiceNotice", 2010);
            _idToName.Add(2010, "UnloadedServiceNotice");
            _nameToID.Add("ShutdownClusterServer", 2011);
            _idToName.Add(2011, "ShutdownClusterServer");
            _nameToID.Add("ForwardToService", 2012);
            _idToName.Add(2012, "ForwardToService");
            _nameToID.Add("ForwardToRealClient", 2013);
            _idToName.Add(2013, "ForwardToRealClient");
            _nameToID.Add("ForwardToDocker", 2014);
            _idToName.Add(2014, "ForwardToDocker");
            _nameToID.Add("DBDataResult", 2015);
            _idToName.Add(2015, "DBDataResult");
            _nameToID.Add("DBQueryReq", 2016);
            _idToName.Add(2016, "DBQueryReq");
            _nameToID.Add("DBQueryResp", 2017);
            _idToName.Add(2017, "DBQueryResp");
            _nameToID.Add("DBQueryArrayReq", 2018);
            _idToName.Add(2018, "DBQueryArrayReq");
            _nameToID.Add("DBQueryArrayResp", 2019);
            _idToName.Add(2019, "DBQueryArrayResp");
            _nameToID.Add("WebAgentClientRequestAPI", 2020);
            _idToName.Add(2020, "WebAgentClientRequestAPI");
            _nameToID.Add("WebServerRequest", 2021);
            _idToName.Add(2021, "WebServerRequest");
            _nameToID.Add("WebServerResponse", 2022);
            _idToName.Add(2022, "WebServerResponse");
            _nameToID.Add("AvatarOffline", 2023);
            _idToName.Add(2023, "AvatarOffline");
            _nameToID.Add("SceneGroupAvatarInfo", 10000);
            _idToName.Add(10000, "SceneGroupAvatarInfo");
            _nameToID.Add("SceneGroupInfo", 10001);
            _idToName.Add(10001, "SceneGroupInfo");
            _nameToID.Add("EPoint", 10002);
            _idToName.Add(10002, "EPoint");
            _nameToID.Add("SearchInfo", 10003);
            _idToName.Add(10003, "SearchInfo");
            _nameToID.Add("SkillBehaviour", 10004);
            _idToName.Add(10004, "SkillBehaviour");
            _nameToID.Add("SkillData", 10005);
            _idToName.Add(10005, "SkillData");
            _nameToID.Add("BuffData", 10006);
            _idToName.Add(10006, "BuffData");
            _nameToID.Add("HarmData", 10007);
            _idToName.Add(10007, "HarmData");
            _nameToID.Add("SkillInfo", 10008);
            _idToName.Add(10008, "SkillInfo");
            _nameToID.Add("BuffInfo", 10009);
            _idToName.Add(10009, "BuffInfo");
            _nameToID.Add("EntityInfo", 10010);
            _idToName.Add(10010, "EntityInfo");
            _nameToID.Add("EntityMove", 10011);
            _idToName.Add(10011, "EntityMove");
            _nameToID.Add("EntityControl", 10012);
            _idToName.Add(10012, "EntityControl");
            _nameToID.Add("EntityReport", 10013);
            _idToName.Add(10013, "EntityReport");
            _nameToID.Add("EntityFullData", 10014);
            _idToName.Add(10014, "EntityFullData");
            _nameToID.Add("SceneSection", 10015);
            _idToName.Add(10015, "SceneSection");
            _nameToID.Add("SceneKnock", 39000);
            _idToName.Add(39000, "SceneKnock");
            _nameToID.Add("ScenePulse", 39001);
            _idToName.Add(39001, "ScenePulse");
            _nameToID.Add("SceneServerJoinGroupIns", 39002);
            _idToName.Add(39002, "SceneServerJoinGroupIns");
            _nameToID.Add("SceneServerJoinGroupAck", 39003);
            _idToName.Add(39003, "SceneServerJoinGroupAck");
            _nameToID.Add("SceneServerEnterSceneIns", 39004);
            _idToName.Add(39004, "SceneServerEnterSceneIns");
            _nameToID.Add("SceneServerGroupStatusChangeIns", 39005);
            _idToName.Add(39005, "SceneServerGroupStatusChangeIns");
            _nameToID.Add("SceneServerGroupStateChangeIns", 39006);
            _idToName.Add(39006, "SceneServerGroupStateChangeIns");
            _nameToID.Add("ClientPulse", 40000);
            _idToName.Add(40000, "ClientPulse");
            _nameToID.Add("ClientAuthReq", 40001);
            _idToName.Add(40001, "ClientAuthReq");
            _nameToID.Add("ClientAuthResp", 40002);
            _idToName.Add(40002, "ClientAuthResp");
            _nameToID.Add("CreateAvatarReq", 40003);
            _idToName.Add(40003, "CreateAvatarReq");
            _nameToID.Add("CreateAvatarResp", 40004);
            _idToName.Add(40004, "CreateAvatarResp");
            _nameToID.Add("AttachAvatarReq", 40005);
            _idToName.Add(40005, "AttachAvatarReq");
            _nameToID.Add("AttachAvatarResp", 40006);
            _idToName.Add(40006, "AttachAvatarResp");
            _nameToID.Add("AvatarBaseInfoNotice", 40007);
            _idToName.Add(40007, "AvatarBaseInfoNotice");
            _nameToID.Add("AvatarPropMapNotice", 40008);
            _idToName.Add(40008, "AvatarPropMapNotice");
            _nameToID.Add("SceneGroupInfoNotice", 40009);
            _idToName.Add(40009, "SceneGroupInfoNotice");
            _nameToID.Add("SceneGroupGetStatusReq", 40010);
            _idToName.Add(40010, "SceneGroupGetStatusReq");
            _nameToID.Add("SceneGroupGetStatusResp", 40011);
            _idToName.Add(40011, "SceneGroupGetStatusResp");
            _nameToID.Add("SceneGroupEnterSceneReq", 40012);
            _idToName.Add(40012, "SceneGroupEnterSceneReq");
            _nameToID.Add("SceneGroupEnterSceneResp", 40013);
            _idToName.Add(40013, "SceneGroupEnterSceneResp");
            _nameToID.Add("SceneGroupCancelEnterReq", 40014);
            _idToName.Add(40014, "SceneGroupCancelEnterReq");
            _nameToID.Add("SceneGroupCancelEnterResp", 40015);
            _idToName.Add(40015, "SceneGroupCancelEnterResp");
            _nameToID.Add("SceneGroupCreateReq", 40016);
            _idToName.Add(40016, "SceneGroupCreateReq");
            _nameToID.Add("SceneGroupCreateResp", 40017);
            _idToName.Add(40017, "SceneGroupCreateResp");
            _nameToID.Add("SceneGroupJoinReq", 40018);
            _idToName.Add(40018, "SceneGroupJoinReq");
            _nameToID.Add("SceneGroupJoinResp", 40019);
            _idToName.Add(40019, "SceneGroupJoinResp");
            _nameToID.Add("SceneGroupInviteReq", 40020);
            _idToName.Add(40020, "SceneGroupInviteReq");
            _nameToID.Add("SceneGroupInviteResp", 40021);
            _idToName.Add(40021, "SceneGroupInviteResp");
            _nameToID.Add("SceneGroupInviteNotice", 40022);
            _idToName.Add(40022, "SceneGroupInviteNotice");
            _nameToID.Add("SceneGroupRejectReq", 40023);
            _idToName.Add(40023, "SceneGroupRejectReq");
            _nameToID.Add("SceneGroupRejectResp", 40024);
            _idToName.Add(40024, "SceneGroupRejectResp");
            _nameToID.Add("SceneGroupLeaveReq", 40025);
            _idToName.Add(40025, "SceneGroupLeaveReq");
            _nameToID.Add("SceneGroupLeaveResp", 40026);
            _idToName.Add(40026, "SceneGroupLeaveResp");
            _nameToID.Add("ChatReq", 40027);
            _idToName.Add(40027, "ChatReq");
            _nameToID.Add("ChatResp", 40028);
            _idToName.Add(40028, "ChatResp");
            _nameToID.Add("PingPongReq", 40029);
            _idToName.Add(40029, "PingPongReq");
            _nameToID.Add("PingPongResp", 40030);
            _idToName.Add(40030, "PingPongResp");
            _nameToID.Add("ChangeIconIDReq", 40031);
            _idToName.Add(40031, "ChangeIconIDReq");
            _nameToID.Add("ChangeIconIDResp", 40032);
            _idToName.Add(40032, "ChangeIconIDResp");
            _nameToID.Add("ChangeModeIDReq", 40033);
            _idToName.Add(40033, "ChangeModeIDReq");
            _nameToID.Add("ChangeModeIDResp", 40034);
            _idToName.Add(40034, "ChangeModeIDResp");
            _nameToID.Add("SceneGroupGetReq", 40035);
            _idToName.Add(40035, "SceneGroupGetReq");
            _nameToID.Add("SceneGroupGetResp", 40036);
            _idToName.Add(40036, "SceneGroupGetResp");
            _nameToID.Add("SceneGroupEnterReq", 40037);
            _idToName.Add(40037, "SceneGroupEnterReq");
            _nameToID.Add("SceneGroupEnterResp", 40038);
            _idToName.Add(40038, "SceneGroupEnterResp");
            _nameToID.Add("SceneGroupCancelReq", 40039);
            _idToName.Add(40039, "SceneGroupCancelReq");
            _nameToID.Add("SceneGroupCancelResp", 40040);
            _idToName.Add(40040, "SceneGroupCancelResp");
            _nameToID.Add("SceneClientPulse", 50000);
            _idToName.Add(50000, "SceneClientPulse");
            _nameToID.Add("AttachSceneReq", 50001);
            _idToName.Add(50001, "AttachSceneReq");
            _nameToID.Add("AttachSceneResp", 50002);
            _idToName.Add(50002, "AttachSceneResp");
            _nameToID.Add("SceneSectionNotice", 50003);
            _idToName.Add(50003, "SceneSectionNotice");
            _nameToID.Add("SceneRefreshNotice", 50004);
            _idToName.Add(50004, "SceneRefreshNotice");
            _nameToID.Add("SceneReportsNotice", 50005);
            _idToName.Add(50005, "SceneReportsNotice");
            _nameToID.Add("AddEntityNotice", 50006);
            _idToName.Add(50006, "AddEntityNotice");
            _nameToID.Add("RemoveEntityNotice", 50007);
            _idToName.Add(50007, "RemoveEntityNotice");
            _nameToID.Add("MoveReq", 50008);
            _idToName.Add(50008, "MoveReq");
            _nameToID.Add("MoveResp", 50009);
            _idToName.Add(50009, "MoveResp");
            _nameToID.Add("MoveNotice", 50010);
            _idToName.Add(50010, "MoveNotice");
            _nameToID.Add("AddBuffNotice", 50011);
            _idToName.Add(50011, "AddBuffNotice");
            _nameToID.Add("RemoveBuffNotice", 50012);
            _idToName.Add(50012, "RemoveBuffNotice");
            _nameToID.Add("UserSkillReq", 50013);
            _idToName.Add(50013, "UserSkillReq");
            _nameToID.Add("UserSkillResp", 50014);
            _idToName.Add(50014, "UserSkillResp");
            _nameToID.Add("UserSkillNotice", 50015);
            _idToName.Add(50015, "UserSkillNotice");
            _nameToID.Add("UseSkillReq", 50016);
            _idToName.Add(50016, "UseSkillReq");
            _nameToID.Add("UseSkillResp", 50017);
            _idToName.Add(50017, "UseSkillResp");
            _nameToID.Add("UseSkillNotice", 50018);
            _idToName.Add(50018, "UseSkillNotice");
            _errCodes.Add(0, "成功");
            _errCodes.Add(1, "错误");
            _errCodes.Add(2, "内部错误");
            _errCodes.Add(3, "数据库错误");
            _errCodes.Add(4, "非法参数");
            _errCodes.Add(5, "权限错误");
            _errCodes.Add(6, "请求操作已过期");
            _errCodes.Add(7, "操作目标不存在");
            _errCodes.Add(8, "令牌过期");
            _errCodes.Add(50, "错误的用户信息");
            _errCodes.Add(51, "创建用户的数量超出限制");
            _errCodes.Add(52, "创建用户的频率超出限制");
            _errCodes.Add(53, "创建用户的昵称冲突");
            _errCodes.Add(100, "请先删除与该好友建立的关系");
            _errCodes.Add(101, "达到好友上限");
            _errCodes.Add(102, "不能添加对方为好友");
            _errCodes.Add(103, "好友不存在");
            _errCodes.Add(104, "服务未开放");

        }
    }
}


