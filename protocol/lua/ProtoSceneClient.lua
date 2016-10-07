 
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
 
Proto4z.register(50010,"SceneSectionNotice") 
Proto4z.SceneSectionNotice = {} --填充场景数据 
Proto4z.SceneSectionNotice.__protoID = 50010 
Proto4z.SceneSectionNotice.__protoName = "SceneSectionNotice" 
Proto4z.SceneSectionNotice[1] = {name="section", type="SceneSection" }  
 
Proto4z.register(50011,"RefreshEntityNotice") 
Proto4z.RefreshEntityNotice = {}  
Proto4z.RefreshEntityNotice.__protoID = 50011 
Proto4z.RefreshEntityNotice.__protoName = "RefreshEntityNotice" 
Proto4z.RefreshEntityNotice[1] = {name="entityInfos", type="EntityInfoArray" }  
Proto4z.RefreshEntityNotice[2] = {name="entityPoints", type="EntityPointArray" }  
Proto4z.RefreshEntityNotice[3] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50005,"RefreshSceneReportsNotice") 
Proto4z.RefreshSceneReportsNotice = {}  
Proto4z.RefreshSceneReportsNotice.__protoID = 50005 
Proto4z.RefreshSceneReportsNotice.__protoName = "RefreshSceneReportsNotice" 
Proto4z.RefreshSceneReportsNotice[1] = {name="reports", type="EntityReportArray" }  
Proto4z.RefreshSceneReportsNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50006,"AddEntityNotice") 
Proto4z.AddEntityNotice = {} --一批实体加入场景时, 把这些实体的数据广播给其他玩家 
Proto4z.AddEntityNotice.__protoID = 50006 
Proto4z.AddEntityNotice.__protoName = "AddEntityNotice" 
Proto4z.AddEntityNotice[1] = {name="entitys", type="EntityFullDataArray" }  
Proto4z.AddEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50007,"RemoveEntityNotice") 
Proto4z.RemoveEntityNotice = {} --实体离开场景时, 把该实体的数据广播给其他玩家 
Proto4z.RemoveEntityNotice.__protoID = 50007 
Proto4z.RemoveEntityNotice.__protoName = "RemoveEntityNotice" 
Proto4z.RemoveEntityNotice[1] = {name="eids", type="EntityIDArray" }  
Proto4z.RemoveEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50008,"AddBuffNotice") 
Proto4z.AddBuffNotice = {}  
Proto4z.AddBuffNotice.__protoID = 50008 
Proto4z.AddBuffNotice.__protoName = "AddBuffNotice" 
Proto4z.AddBuffNotice[1] = {name="eid", type="ui64" }  
Proto4z.AddBuffNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50009,"RemoveBuffNotice") 
Proto4z.RemoveBuffNotice = {}  
Proto4z.RemoveBuffNotice.__protoID = 50009 
Proto4z.RemoveBuffNotice.__protoName = "RemoveBuffNotice" 
Proto4z.RemoveBuffNotice[1] = {name="eid", type="ui64" }  
Proto4z.RemoveBuffNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
