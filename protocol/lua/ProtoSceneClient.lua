 
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
Proto4z.SceneRefreshNotice[1] = {name="entityInfos", type="EntityInfoArray" }  
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
Proto4z.AddEntityNotice[1] = {name="entitys", type="EntityFullDataArray" }  
 
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
Proto4z.MoveReq[2] = {name="maction", type="ui16" }  
Proto4z.MoveReq[3] = {name="pos", type="EPoint" }  
 
Proto4z.register(50009,"MoveResp") 
Proto4z.MoveResp = {}  
Proto4z.MoveResp.__protoID = 50009 
Proto4z.MoveResp.__protoName = "MoveResp" 
Proto4z.MoveResp[1] = {name="retCode", type="ui16" }  
Proto4z.MoveResp[2] = {name="eid", type="ui64" }  
Proto4z.MoveResp[3] = {name="maction", type="ui16" }  
Proto4z.MoveResp[4] = {name="pos", type="EPoint" }  
 
Proto4z.register(50010,"MoveNotice") 
Proto4z.MoveNotice = {}  
Proto4z.MoveNotice.__protoID = 50010 
Proto4z.MoveNotice.__protoName = "MoveNotice" 
Proto4z.MoveNotice[1] = {name="eid", type="ui64" }  
Proto4z.MoveNotice[2] = {name="maction", type="ui16" }  
Proto4z.MoveNotice[3] = {name="path", type="EPoints" }  
 
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
 
Proto4z.register(50013,"UserSkillReq") 
Proto4z.UserSkillReq = {}  
Proto4z.UserSkillReq.__protoID = 50013 
Proto4z.UserSkillReq.__protoName = "UserSkillReq" 
Proto4z.UserSkillReq[1] = {name="eid", type="ui64" }  
 
Proto4z.register(50014,"UserSkillResp") 
Proto4z.UserSkillResp = {}  
Proto4z.UserSkillResp.__protoID = 50014 
Proto4z.UserSkillResp.__protoName = "UserSkillResp" 
Proto4z.UserSkillResp[1] = {name="retCode", type="ui16" }  
Proto4z.UserSkillResp[2] = {name="eid", type="ui64" }  
 
Proto4z.register(50015,"UserSkillNotice") 
Proto4z.UserSkillNotice = {}  
Proto4z.UserSkillNotice.__protoID = 50015 
Proto4z.UserSkillNotice.__protoName = "UserSkillNotice" 
Proto4z.UserSkillNotice[1] = {name="eid", type="ui64" }  
