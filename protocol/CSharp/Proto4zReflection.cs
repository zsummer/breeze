
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
            return "unknown";
        }

        static System.Collections.Generic.Dictionary<string, ushort> _nameToID = new System.Collections.Generic.Dictionary<string, ushort>();
        static System.Collections.Generic.Dictionary<ushort, string> _idToName = new System.Collections.Generic.Dictionary<ushort, string>();
        static Reflection()
        {
        

                    
            _nameToID.Add("AddEntityNotice", 50005);
            _idToName.Add(50005, "AddEntityNotice");
            _nameToID.Add("AllocateSceneReq", 39000);
            _idToName.Add(39000, "AllocateSceneReq");
            _nameToID.Add("AllocateSceneResp", 39001);
            _idToName.Add(39001, "AllocateSceneResp");
            _nameToID.Add("AttachAvatarReq", 40005);
            _idToName.Add(40005, "AttachAvatarReq");
            _nameToID.Add("AttachAvatarResp", 40006);
            _idToName.Add(40006, "AttachAvatarResp");
            _nameToID.Add("AttachSceneReq", 50000);
            _idToName.Add(50000, "AttachSceneReq");
            _nameToID.Add("AttachSceneResp", 50001);
            _idToName.Add(50001, "AttachSceneResp");
            _nameToID.Add("AvatarBaseInfo", 1004);
            _idToName.Add(1004, "AvatarBaseInfo");
            _nameToID.Add("AvatarOffline", 2023);
            _idToName.Add(2023, "AvatarOffline");
            _nameToID.Add("AvatarPreview", 1003);
            _idToName.Add(1003, "AvatarPreview");
            _nameToID.Add("BuffData", 10005);
            _idToName.Add(10005, "BuffData");
            _nameToID.Add("BuffInfo", 10008);
            _idToName.Add(10008, "BuffInfo");
            _nameToID.Add("ChatReq", 40014);
            _idToName.Add(40014, "ChatReq");
            _nameToID.Add("ChatResp", 40015);
            _idToName.Add(40015, "ChatResp");
            _nameToID.Add("ClientAuthReq", 40001);
            _idToName.Add(40001, "ClientAuthReq");
            _nameToID.Add("ClientAuthResp", 40002);
            _idToName.Add(40002, "ClientAuthResp");
            _nameToID.Add("ClientPulse", 40000);
            _idToName.Add(40000, "ClientPulse");
            _nameToID.Add("CreateAvatarReq", 40003);
            _idToName.Add(40003, "CreateAvatarReq");
            _nameToID.Add("CreateAvatarResp", 40004);
            _idToName.Add(40004, "CreateAvatarResp");
            _nameToID.Add("DBDataResult", 2015);
            _idToName.Add(2015, "DBDataResult");
            _nameToID.Add("DBQueryArrayReq", 2018);
            _idToName.Add(2018, "DBQueryArrayReq");
            _nameToID.Add("DBQueryArrayResp", 2019);
            _idToName.Add(2019, "DBQueryArrayResp");
            _nameToID.Add("DBQueryReq", 2016);
            _idToName.Add(2016, "DBQueryReq");
            _nameToID.Add("DBQueryResp", 2017);
            _idToName.Add(2017, "DBQueryResp");
            _nameToID.Add("DictBaseProps", 1008);
            _idToName.Add(1008, "DictBaseProps");
            _nameToID.Add("DictGlobal", 1005);
            _idToName.Add(1005, "DictGlobal");
            _nameToID.Add("DictItem", 1009);
            _idToName.Add(1009, "DictItem");
            _nameToID.Add("DictRaffleAward", 1006);
            _idToName.Add(1006, "DictRaffleAward");
            _nameToID.Add("DictRafflePool", 1007);
            _idToName.Add(1007, "DictRafflePool");
            _nameToID.Add("DockerPulse", 2001);
            _idToName.Add(2001, "DockerPulse");
            _nameToID.Add("EPoint", 10001);
            _idToName.Add(10001, "EPoint");
            _nameToID.Add("EntityControl", 10010);
            _idToName.Add(10010, "EntityControl");
            _nameToID.Add("EntityFullInfo", 10012);
            _idToName.Add(10012, "EntityFullInfo");
            _nameToID.Add("EntityInfo", 10009);
            _idToName.Add(10009, "EntityInfo");
            _nameToID.Add("EntityReport", 10011);
            _idToName.Add(10011, "EntityReport");
            _nameToID.Add("FillSceneNotice", 50002);
            _idToName.Add(50002, "FillSceneNotice");
            _nameToID.Add("ForwardToDocker", 2014);
            _idToName.Add(2014, "ForwardToDocker");
            _nameToID.Add("ForwardToRealClient", 2013);
            _idToName.Add(2013, "ForwardToRealClient");
            _nameToID.Add("ForwardToService", 2012);
            _idToName.Add(2012, "ForwardToService");
            _nameToID.Add("GetSceneTokenInfoReq", 40007);
            _idToName.Add(40007, "GetSceneTokenInfoReq");
            _nameToID.Add("GetSceneTokenInfoResp", 40008);
            _idToName.Add(40008, "GetSceneTokenInfoResp");
            _nameToID.Add("HarmData", 10006);
            _idToName.Add(10006, "HarmData");
            _nameToID.Add("ItemInfo", 1010);
            _idToName.Add(1010, "ItemInfo");
            _nameToID.Add("JoinSceneNotice", 40011);
            _idToName.Add(40011, "JoinSceneNotice");
            _nameToID.Add("JoinSceneReq", 40009);
            _idToName.Add(40009, "JoinSceneReq");
            _nameToID.Add("JoinSceneResp", 40010);
            _idToName.Add(40010, "JoinSceneResp");
            _nameToID.Add("KickRealClient", 2007);
            _idToName.Add(2007, "KickRealClient");
            _nameToID.Add("LeaveSceneReq", 40012);
            _idToName.Add(40012, "LeaveSceneReq");
            _nameToID.Add("LeaveSceneResp", 40013);
            _idToName.Add(40013, "LeaveSceneResp");
            _nameToID.Add("LoadService", 2002);
            _idToName.Add(2002, "LoadService");
            _nameToID.Add("LoadServiceNotice", 2004);
            _idToName.Add(2004, "LoadServiceNotice");
            _nameToID.Add("MoneyTree", 1011);
            _idToName.Add(1011, "MoneyTree");
            _nameToID.Add("OutOfBand", 1001);
            _idToName.Add(1001, "OutOfBand");
            _nameToID.Add("PingPongReq", 40016);
            _idToName.Add(40016, "PingPongReq");
            _nameToID.Add("PingPongResp", 40017);
            _idToName.Add(40017, "PingPongResp");
            _nameToID.Add("RealClientClosedNotice", 2008);
            _idToName.Add(2008, "RealClientClosedNotice");
            _nameToID.Add("RefreshSceneEntitysNotice", 50003);
            _idToName.Add(50003, "RefreshSceneEntitysNotice");
            _nameToID.Add("RefreshSceneReportsNotice", 50004);
            _idToName.Add(50004, "RefreshSceneReportsNotice");
            _nameToID.Add("RefreshServiceToMgrNotice", 2005);
            _idToName.Add(2005, "RefreshServiceToMgrNotice");
            _nameToID.Add("RemoveEntityNotice", 50006);
            _idToName.Add(50006, "RemoveEntityNotice");
            _nameToID.Add("Routing", 1000);
            _idToName.Add(1000, "Routing");
            _nameToID.Add("SceneTokenInfo", 10000);
            _idToName.Add(10000, "SceneTokenInfo");
            _nameToID.Add("SearchInfo", 10002);
            _idToName.Add(10002, "SearchInfo");
            _nameToID.Add("SelfBeingPulse", 2000);
            _idToName.Add(2000, "SelfBeingPulse");
            _nameToID.Add("ServiceInfo", 2003);
            _idToName.Add(2003, "ServiceInfo");
            _nameToID.Add("ShutdownClusterServer", 2011);
            _idToName.Add(2011, "ShutdownClusterServer");
            _nameToID.Add("SimplePack", 1012);
            _idToName.Add(1012, "SimplePack");
            _nameToID.Add("SkillBehaviour", 10003);
            _idToName.Add(10003, "SkillBehaviour");
            _nameToID.Add("SkillData", 10004);
            _idToName.Add(10004, "SkillData");
            _nameToID.Add("SkillInfo", 10007);
            _idToName.Add(10007, "SkillInfo");
            _nameToID.Add("SwitchServiceClientNotice", 2006);
            _idToName.Add(2006, "SwitchServiceClientNotice");
            _nameToID.Add("Tracing", 1002);
            _idToName.Add(1002, "Tracing");
            _nameToID.Add("UnloadServiceInDocker", 2009);
            _idToName.Add(2009, "UnloadServiceInDocker");
            _nameToID.Add("UnloadedServiceNotice", 2010);
            _idToName.Add(2010, "UnloadedServiceNotice");
            _nameToID.Add("WebAgentClientRequestAPI", 2020);
            _idToName.Add(2020, "WebAgentClientRequestAPI");
            _nameToID.Add("WebServerRequest", 2021);
            _idToName.Add(2021, "WebServerRequest");
            _nameToID.Add("WebServerResponse", 2022);
            _idToName.Add(2022, "WebServerResponse");

        }
    }
}


