
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
            _nameToID.Add("ItemInfo", 1005);
            _idToName.Add(1005, "ItemInfo");
            _nameToID.Add("LogChat", 1006);
            _idToName.Add(1006, "LogChat");
            _nameToID.Add("MoneyTree", 1007);
            _idToName.Add(1007, "MoneyTree");
            _nameToID.Add("SimplePack", 1008);
            _idToName.Add(1008, "SimplePack");
            _nameToID.Add("SceneGroupAvatarInfo", 2000);
            _idToName.Add(2000, "SceneGroupAvatarInfo");
            _nameToID.Add("SceneGroupInfo", 2001);
            _idToName.Add(2001, "SceneGroupInfo");
            _nameToID.Add("EPosition", 2002);
            _idToName.Add(2002, "EPosition");
            _nameToID.Add("SceneEventInfo", 2003);
            _idToName.Add(2003, "SceneEventInfo");
            _nameToID.Add("EntityState", 2004);
            _idToName.Add(2004, "EntityState");
            _nameToID.Add("EntityMove", 2005);
            _idToName.Add(2005, "EntityMove");
            _nameToID.Add("EntityReport", 2006);
            _idToName.Add(2006, "EntityReport");
            _nameToID.Add("EntityFullData", 2007);
            _idToName.Add(2007, "EntityFullData");
            _nameToID.Add("SceneSection", 2008);
            _idToName.Add(2008, "SceneSection");
            _nameToID.Add("EntitySkillInfo", 2009);
            _idToName.Add(2009, "EntitySkillInfo");
            _nameToID.Add("EntityBuffInfo", 2010);
            _idToName.Add(2010, "EntityBuffInfo");
            _nameToID.Add("DockerKnock", 3000);
            _idToName.Add(3000, "DockerKnock");
            _nameToID.Add("DockerPulse", 3001);
            _idToName.Add(3001, "DockerPulse");
            _nameToID.Add("LoadService", 3002);
            _idToName.Add(3002, "LoadService");
            _nameToID.Add("ServiceInfo", 3003);
            _idToName.Add(3003, "ServiceInfo");
            _nameToID.Add("LoadServiceNotice", 3004);
            _idToName.Add(3004, "LoadServiceNotice");
            _nameToID.Add("RefreshServiceToMgrNotice", 3005);
            _idToName.Add(3005, "RefreshServiceToMgrNotice");
            _nameToID.Add("SwitchServiceClientNotice", 3006);
            _idToName.Add(3006, "SwitchServiceClientNotice");
            _nameToID.Add("KickRealClient", 3007);
            _idToName.Add(3007, "KickRealClient");
            _nameToID.Add("RealClientClosedNotice", 3008);
            _idToName.Add(3008, "RealClientClosedNotice");
            _nameToID.Add("UnloadServiceInDocker", 3009);
            _idToName.Add(3009, "UnloadServiceInDocker");
            _nameToID.Add("UnloadedServiceNotice", 3010);
            _idToName.Add(3010, "UnloadedServiceNotice");
            _nameToID.Add("ShutdownClusterServer", 3011);
            _idToName.Add(3011, "ShutdownClusterServer");
            _nameToID.Add("ForwardToService", 3012);
            _idToName.Add(3012, "ForwardToService");
            _nameToID.Add("ForwardToRealClient", 3013);
            _idToName.Add(3013, "ForwardToRealClient");
            _nameToID.Add("ForwardToDocker", 3014);
            _idToName.Add(3014, "ForwardToDocker");
            _nameToID.Add("DBDataResult", 3015);
            _idToName.Add(3015, "DBDataResult");
            _nameToID.Add("DBQueryReq", 3016);
            _idToName.Add(3016, "DBQueryReq");
            _nameToID.Add("DBQueryResp", 3017);
            _idToName.Add(3017, "DBQueryResp");
            _nameToID.Add("DBQueryArrayReq", 3018);
            _idToName.Add(3018, "DBQueryArrayReq");
            _nameToID.Add("DBQueryArrayResp", 3019);
            _idToName.Add(3019, "DBQueryArrayResp");
            _nameToID.Add("WebAgentClientRequestAPI", 3020);
            _idToName.Add(3020, "WebAgentClientRequestAPI");
            _nameToID.Add("WebServerRequest", 3021);
            _idToName.Add(3021, "WebServerRequest");
            _nameToID.Add("WebServerResponse", 3022);
            _idToName.Add(3022, "WebServerResponse");
            _nameToID.Add("AvatarOffline", 3023);
            _idToName.Add(3023, "AvatarOffline");
            _nameToID.Add("SceneKnock", 4000);
            _idToName.Add(4000, "SceneKnock");
            _nameToID.Add("ScenePulse", 4001);
            _idToName.Add(4001, "ScenePulse");
            _nameToID.Add("SceneServerJoinGroupIns", 4002);
            _idToName.Add(4002, "SceneServerJoinGroupIns");
            _nameToID.Add("SceneServerJoinGroupAck", 4003);
            _idToName.Add(4003, "SceneServerJoinGroupAck");
            _nameToID.Add("SceneServerEnterSceneIns", 4004);
            _idToName.Add(4004, "SceneServerEnterSceneIns");
            _nameToID.Add("SceneServerCancelSceneIns", 4005);
            _idToName.Add(4005, "SceneServerCancelSceneIns");
            _nameToID.Add("SceneServerGroupStateChangeIns", 4006);
            _idToName.Add(4006, "SceneServerGroupStateChangeIns");
            _nameToID.Add("DictPairValue", 10000);
            _idToName.Add(10000, "DictPairValue");
            _nameToID.Add("DictGlobal", 10001);
            _idToName.Add(10001, "DictGlobal");
            _nameToID.Add("DictDrop", 10002);
            _idToName.Add(10002, "DictDrop");
            _nameToID.Add("DictItem", 10003);
            _idToName.Add(10003, "DictItem");
            _nameToID.Add("DictProp", 11000);
            _idToName.Add(11000, "DictProp");
            _nameToID.Add("DictModelLevel", 11001);
            _idToName.Add(11001, "DictModelLevel");
            _nameToID.Add("DictModel", 11002);
            _idToName.Add(11002, "DictModel");
            _nameToID.Add("AOESearch", 11003);
            _idToName.Add(11003, "AOESearch");
            _nameToID.Add("DictBuffEffect", 11004);
            _idToName.Add(11004, "DictBuffEffect");
            _nameToID.Add("DictBuff", 11005);
            _idToName.Add(11005, "DictBuff");
            _nameToID.Add("DictSkillBehaviour", 11006);
            _idToName.Add(11006, "DictSkillBehaviour");
            _nameToID.Add("DictSkill", 11007);
            _idToName.Add(11007, "DictSkill");
            _nameToID.Add("DictSpawnPoint", 11008);
            _idToName.Add(11008, "DictSpawnPoint");
            _nameToID.Add("DictObstacle", 11009);
            _idToName.Add(11009, "DictObstacle");
            _nameToID.Add("DictMonster", 11010);
            _idToName.Add(11010, "DictMonster");
            _nameToID.Add("DictMap", 11011);
            _idToName.Add(11011, "DictMap");
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
            _nameToID.Add("UseSkillReq", 50013);
            _idToName.Add(50013, "UseSkillReq");
            _nameToID.Add("UseSkillResp", 50014);
            _idToName.Add(50014, "UseSkillResp");
            _nameToID.Add("UseSkillNotice", 50015);
            _idToName.Add(50015, "UseSkillNotice");
            _nameToID.Add("SceneEventNotice", 50016);
            _idToName.Add(50016, "SceneEventNotice");
            _nameToID.Add("ClientCustomReq", 50017);
            _idToName.Add(50017, "ClientCustomReq");
            _nameToID.Add("ClientCustomResp", 50018);
            _idToName.Add(50018, "ClientCustomResp");
            _nameToID.Add("ClientCustomNotice", 50019);
            _idToName.Add(50019, "ClientCustomNotice");
            _nameToID.Add("ClientPingTestReq", 50020);
            _idToName.Add(50020, "ClientPingTestReq");
            _nameToID.Add("ClientPingTestResp", 50021);
            _idToName.Add(50021, "ClientPingTestResp");
            _nameToID.Add("ClientPulse", 55000);
            _idToName.Add(55000, "ClientPulse");
            _nameToID.Add("ClientAuthReq", 55001);
            _idToName.Add(55001, "ClientAuthReq");
            _nameToID.Add("ClientAuthResp", 55002);
            _idToName.Add(55002, "ClientAuthResp");
            _nameToID.Add("CreateAvatarReq", 55003);
            _idToName.Add(55003, "CreateAvatarReq");
            _nameToID.Add("CreateAvatarResp", 55004);
            _idToName.Add(55004, "CreateAvatarResp");
            _nameToID.Add("AttachAvatarReq", 55005);
            _idToName.Add(55005, "AttachAvatarReq");
            _nameToID.Add("AttachAvatarResp", 55006);
            _idToName.Add(55006, "AttachAvatarResp");
            _nameToID.Add("AvatarBaseInfoNotice", 55007);
            _idToName.Add(55007, "AvatarBaseInfoNotice");
            _nameToID.Add("AvatarPropMapNotice", 55008);
            _idToName.Add(55008, "AvatarPropMapNotice");
            _nameToID.Add("SceneGroupInfoNotice", 55009);
            _idToName.Add(55009, "SceneGroupInfoNotice");
            _nameToID.Add("SceneGroupGetReq", 55010);
            _idToName.Add(55010, "SceneGroupGetReq");
            _nameToID.Add("SceneGroupGetResp", 55011);
            _idToName.Add(55011, "SceneGroupGetResp");
            _nameToID.Add("SceneGroupEnterReq", 55012);
            _idToName.Add(55012, "SceneGroupEnterReq");
            _nameToID.Add("SceneGroupEnterResp", 55013);
            _idToName.Add(55013, "SceneGroupEnterResp");
            _nameToID.Add("SceneGroupCancelReq", 55014);
            _idToName.Add(55014, "SceneGroupCancelReq");
            _nameToID.Add("SceneGroupCancelResp", 55015);
            _idToName.Add(55015, "SceneGroupCancelResp");
            _nameToID.Add("SceneGroupCreateReq", 55016);
            _idToName.Add(55016, "SceneGroupCreateReq");
            _nameToID.Add("SceneGroupCreateResp", 55017);
            _idToName.Add(55017, "SceneGroupCreateResp");
            _nameToID.Add("SceneGroupJoinReq", 55018);
            _idToName.Add(55018, "SceneGroupJoinReq");
            _nameToID.Add("SceneGroupJoinResp", 55019);
            _idToName.Add(55019, "SceneGroupJoinResp");
            _nameToID.Add("SceneGroupInviteReq", 55020);
            _idToName.Add(55020, "SceneGroupInviteReq");
            _nameToID.Add("SceneGroupInviteResp", 55021);
            _idToName.Add(55021, "SceneGroupInviteResp");
            _nameToID.Add("SceneGroupInviteNotice", 55022);
            _idToName.Add(55022, "SceneGroupInviteNotice");
            _nameToID.Add("SceneGroupRejectReq", 55023);
            _idToName.Add(55023, "SceneGroupRejectReq");
            _nameToID.Add("SceneGroupRejectResp", 55024);
            _idToName.Add(55024, "SceneGroupRejectResp");
            _nameToID.Add("SceneGroupLeaveReq", 55025);
            _idToName.Add(55025, "SceneGroupLeaveReq");
            _nameToID.Add("SceneGroupLeaveResp", 55026);
            _idToName.Add(55026, "SceneGroupLeaveResp");
            _nameToID.Add("ChatReq", 55027);
            _idToName.Add(55027, "ChatReq");
            _nameToID.Add("ChatResp", 55028);
            _idToName.Add(55028, "ChatResp");
            _nameToID.Add("PingPongReq", 55029);
            _idToName.Add(55029, "PingPongReq");
            _nameToID.Add("PingPongResp", 55030);
            _idToName.Add(55030, "PingPongResp");
            _nameToID.Add("ChangeIconIDReq", 55031);
            _idToName.Add(55031, "ChangeIconIDReq");
            _nameToID.Add("ChangeIconIDResp", 55032);
            _idToName.Add(55032, "ChangeIconIDResp");
            _nameToID.Add("ChangeModeIDReq", 55033);
            _idToName.Add(55033, "ChangeModeIDReq");
            _nameToID.Add("ChangeModeIDResp", 55034);
            _idToName.Add(55034, "ChangeModeIDResp");
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


