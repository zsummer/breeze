 
Proto4z.register(50000,"SceneClientPulse") 
Proto4z.SceneClientPulse = {} --客户端脉冲请求 
Proto4z.SceneClientPulse.__protoID = 50000 
Proto4z.SceneClientPulse.__protoName = "SceneClientPulse" 
 
Proto4z.register(50001,"AttachSceneReq") 
Proto4z.AttachSceneReq = {}  
Proto4z.AttachSceneReq.__protoID = 50001 
Proto4z.AttachSceneReq.__protoName = "AttachSceneReq" 
Proto4z.AttachSceneReq[1] = {name="avatarID", type="ui64" }  
Proto4z.AttachSceneReq[2] = {name="sceneID", type="ui64" }  
Proto4z.AttachSceneReq[3] = {name="token", type="string" } --令牌 
 
Proto4z.register(50002,"AttachSceneResp") 
Proto4z.AttachSceneResp = {}  
Proto4z.AttachSceneResp.__protoID = 50002 
Proto4z.AttachSceneResp.__protoName = "AttachSceneResp" 
Proto4z.AttachSceneResp[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.AttachSceneResp[2] = {name="avatarID", type="ui64" }  
Proto4z.AttachSceneResp[3] = {name="sceneID", type="ui64" }  
 
Proto4z.register(50003,"SceneSectionNotice") 
Proto4z.SceneSectionNotice = {} --填充场景数据 
Proto4z.SceneSectionNotice.__protoID = 50003 
Proto4z.SceneSectionNotice.__protoName = "SceneSectionNotice" 
Proto4z.SceneSectionNotice[1] = {name="section", type="SceneSection" }  
 
Proto4z.register(50004,"SceneRefreshNotice") 
Proto4z.SceneRefreshNotice = {}  
Proto4z.SceneRefreshNotice.__protoID = 50004 
Proto4z.SceneRefreshNotice.__protoName = "SceneRefreshNotice" 
Proto4z.SceneRefreshNotice[1] = {name="entityStates", type="EntityStateArray" }  
Proto4z.SceneRefreshNotice[2] = {name="entityMoves", type="EntityMoveArray" }  
 
Proto4z.register(50005,"SceneReportsNotice") 
Proto4z.SceneReportsNotice = {}  
Proto4z.SceneReportsNotice.__protoID = 50005 
Proto4z.SceneReportsNotice.__protoName = "SceneReportsNotice" 
Proto4z.SceneReportsNotice[1] = {name="reports", type="EntityReportArray" }  
 
Proto4z.register(50006,"AddEntityNotice") 
Proto4z.AddEntityNotice = {} --一批实体加入场景时, 把这些实体的数据广播给其他玩家 
Proto4z.AddEntityNotice.__protoID = 50006 
Proto4z.AddEntityNotice.__protoName = "AddEntityNotice" 
Proto4z.AddEntityNotice[1] = {name="syncs", type="EntityClientSyncArray" }  
 
Proto4z.register(50007,"RemoveEntityNotice") 
Proto4z.RemoveEntityNotice = {} --实体离开场景时, 把该实体的数据广播给其他玩家 
Proto4z.RemoveEntityNotice.__protoID = 50007 
Proto4z.RemoveEntityNotice.__protoName = "RemoveEntityNotice" 
Proto4z.RemoveEntityNotice[1] = {name="eids", type="EntityIDArray" }  
 
Proto4z.register(50008,"MoveReq") 
Proto4z.MoveReq = {}  
Proto4z.MoveReq.__protoID = 50008 
Proto4z.MoveReq.__protoName = "MoveReq" 
Proto4z.MoveReq[1] = {name="eid", type="ui64" }  
Proto4z.MoveReq[2] = {name="action", type="ui16" }  
Proto4z.MoveReq[3] = {name="clientPos", type="EPosition" }  
Proto4z.MoveReq[4] = {name="waypoints", type="EPositionArray" }  
Proto4z.MoveReq[5] = {name="follow", type="ui64" }  
 
Proto4z.register(50009,"MoveResp") 
Proto4z.MoveResp = {} --只有失败时才会使用该协议 
Proto4z.MoveResp.__protoID = 50009 
Proto4z.MoveResp.__protoName = "MoveResp" 
Proto4z.MoveResp[1] = {name="retCode", type="ui16" }  
Proto4z.MoveResp[2] = {name="eid", type="ui64" }  
Proto4z.MoveResp[3] = {name="action", type="ui16" }  
 
Proto4z.register(50010,"MoveNotice") 
Proto4z.MoveNotice = {} --移动开始/结束通知 
Proto4z.MoveNotice.__protoID = 50010 
Proto4z.MoveNotice.__protoName = "MoveNotice" 
Proto4z.MoveNotice[1] = {name="moveInfo", type="EntityMove" }  
 
Proto4z.register(50011,"AddBuffNotice") 
Proto4z.AddBuffNotice = {}  
Proto4z.AddBuffNotice.__protoID = 50011 
Proto4z.AddBuffNotice.__protoName = "AddBuffNotice" 
Proto4z.AddBuffNotice[1] = {name="eid", type="ui64" }  
 
Proto4z.register(50012,"RemoveBuffNotice") 
Proto4z.RemoveBuffNotice = {}  
Proto4z.RemoveBuffNotice.__protoID = 50012 
Proto4z.RemoveBuffNotice.__protoName = "RemoveBuffNotice" 
Proto4z.RemoveBuffNotice[1] = {name="eid", type="ui64" }  
 
Proto4z.register(50013,"UseSkillReq") 
Proto4z.UseSkillReq = {}  
Proto4z.UseSkillReq.__protoID = 50013 
Proto4z.UseSkillReq.__protoName = "UseSkillReq" 
Proto4z.UseSkillReq[1] = {name="eid", type="ui64" }  
Proto4z.UseSkillReq[2] = {name="skillID", type="ui64" }  
Proto4z.UseSkillReq[3] = {name="dst", type="EPosition" }  
Proto4z.UseSkillReq[4] = {name="foeFirst", type="ui16" }  
 
Proto4z.register(50014,"UseSkillResp") 
Proto4z.UseSkillResp = {} --只有失败时才会使用该协议 
Proto4z.UseSkillResp.__protoID = 50014 
Proto4z.UseSkillResp.__protoName = "UseSkillResp" 
Proto4z.UseSkillResp[1] = {name="retCode", type="ui16" }  
Proto4z.UseSkillResp[2] = {name="eid", type="ui64" }  
Proto4z.UseSkillResp[3] = {name="skillID", type="ui64" }  
Proto4z.UseSkillResp[4] = {name="dst", type="EPosition" }  
Proto4z.UseSkillResp[5] = {name="foeFirst", type="ui16" }  
 
Proto4z.register(50015,"UseSkillNotice") 
Proto4z.UseSkillNotice = {}  
Proto4z.UseSkillNotice.__protoID = 50015 
Proto4z.UseSkillNotice.__protoName = "UseSkillNotice" 
Proto4z.UseSkillNotice[1] = {name="eid", type="ui64" }  
Proto4z.UseSkillNotice[2] = {name="skill", type="EntitySkillInfo" }  
 
Proto4z.register(50016,"SceneEventNotice") 
Proto4z.SceneEventNotice = {}  
Proto4z.SceneEventNotice.__protoID = 50016 
Proto4z.SceneEventNotice.__protoName = "SceneEventNotice" 
Proto4z.SceneEventNotice[1] = {name="info", type="SceneEventInfoArray" }  
 
Proto4z.register(50017,"ClientCustomReq") 
Proto4z.ClientCustomReq = {}  
Proto4z.ClientCustomReq.__protoID = 50017 
Proto4z.ClientCustomReq.__protoName = "ClientCustomReq" 
Proto4z.ClientCustomReq[1] = {name="eid", type="ui64" }  
Proto4z.ClientCustomReq[2] = {name="customID", type="ui64" }  
Proto4z.ClientCustomReq[3] = {name="fValue", type="double" }  
Proto4z.ClientCustomReq[4] = {name="uValue", type="ui64" }  
Proto4z.ClientCustomReq[5] = {name="sValue", type="string" }  
 
Proto4z.register(50018,"ClientCustomResp") 
Proto4z.ClientCustomResp = {} --只有失败时才会使用该协议 
Proto4z.ClientCustomResp.__protoID = 50018 
Proto4z.ClientCustomResp.__protoName = "ClientCustomResp" 
Proto4z.ClientCustomResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientCustomResp[2] = {name="eid", type="ui64" }  
Proto4z.ClientCustomResp[3] = {name="customID", type="ui64" }  
 
Proto4z.register(50019,"ClientCustomNotice") 
Proto4z.ClientCustomNotice = {}  
Proto4z.ClientCustomNotice.__protoID = 50019 
Proto4z.ClientCustomNotice.__protoName = "ClientCustomNotice" 
Proto4z.ClientCustomNotice[1] = {name="eid", type="ui64" }  
Proto4z.ClientCustomNotice[2] = {name="customID", type="ui64" }  
Proto4z.ClientCustomNotice[3] = {name="fValue", type="double" }  
Proto4z.ClientCustomNotice[4] = {name="uValue", type="ui64" }  
Proto4z.ClientCustomNotice[5] = {name="sValue", type="string" }  
 
Proto4z.register(50020,"ClientPingTestReq") 
Proto4z.ClientPingTestReq = {}  
Proto4z.ClientPingTestReq.__protoID = 50020 
Proto4z.ClientPingTestReq.__protoName = "ClientPingTestReq" 
Proto4z.ClientPingTestReq[1] = {name="seqID", type="ui64" }  
Proto4z.ClientPingTestReq[2] = {name="clientTime", type="double" }  
 
Proto4z.register(50021,"ClientPingTestResp") 
Proto4z.ClientPingTestResp = {}  
Proto4z.ClientPingTestResp.__protoID = 50021 
Proto4z.ClientPingTestResp.__protoName = "ClientPingTestResp" 
Proto4z.ClientPingTestResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientPingTestResp[2] = {name="seqID", type="ui64" }  
Proto4z.ClientPingTestResp[3] = {name="clientTime", type="double" }  
