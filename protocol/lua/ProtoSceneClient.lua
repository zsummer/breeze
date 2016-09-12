 
Proto4z.register(50007,"SceneClientPulse") 
Proto4z.SceneClientPulse = {} --客户端脉冲请求 
Proto4z.SceneClientPulse.__protoID = 50007 
Proto4z.SceneClientPulse.__protoName = "SceneClientPulse" 
 
Proto4z.register(50000,"AttachSceneReq") 
Proto4z.AttachSceneReq = {}  
Proto4z.AttachSceneReq.__protoID = 50000 
Proto4z.AttachSceneReq.__protoName = "AttachSceneReq" 
Proto4z.AttachSceneReq[1] = {name="avatarID", type="ui64" }  
Proto4z.AttachSceneReq[2] = {name="sceneID", type="ui32" }  
Proto4z.AttachSceneReq[3] = {name="token", type="string" } --令牌 
 
Proto4z.register(50001,"AttachSceneResp") 
Proto4z.AttachSceneResp = {}  
Proto4z.AttachSceneResp.__protoID = 50001 
Proto4z.AttachSceneResp.__protoName = "AttachSceneResp" 
Proto4z.AttachSceneResp[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.AttachSceneResp[2] = {name="avatarID", type="ui64" }  
Proto4z.AttachSceneResp[3] = {name="sceneID", type="ui32" }  
 
Proto4z.register(50002,"FillSceneNotice") 
Proto4z.FillSceneNotice = {} --填充场景数据 
Proto4z.FillSceneNotice.__protoID = 50002 
Proto4z.FillSceneNotice.__protoName = "FillSceneNotice" 
Proto4z.FillSceneNotice[1] = {name="entitys", type="EntityFullInfoArray" } --这里包含有所有当前场景下的实体属性和状态数据 
Proto4z.FillSceneNotice[2] = {name="sceneStartTime", type="double" } --服务器战场开始时间 
Proto4z.FillSceneNotice[3] = {name="sceneEndTime", type="double" } --服务器战场结束时间 
Proto4z.FillSceneNotice[4] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50003,"RefreshSceneEntitysNotice") 
Proto4z.RefreshSceneEntitysNotice = {}  
Proto4z.RefreshSceneEntitysNotice.__protoID = 50003 
Proto4z.RefreshSceneEntitysNotice.__protoName = "RefreshSceneEntitysNotice" 
Proto4z.RefreshSceneEntitysNotice[1] = {name="entitys", type="EntityInfoArray" }  
Proto4z.RefreshSceneEntitysNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50004,"RefreshSceneReportsNotice") 
Proto4z.RefreshSceneReportsNotice = {}  
Proto4z.RefreshSceneReportsNotice.__protoID = 50004 
Proto4z.RefreshSceneReportsNotice.__protoName = "RefreshSceneReportsNotice" 
Proto4z.RefreshSceneReportsNotice[1] = {name="reports", type="EntityReportArray" }  
Proto4z.RefreshSceneReportsNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50005,"AddEntityNotice") 
Proto4z.AddEntityNotice = {} --一批实体加入场景时, 把这些实体的数据广播给其他玩家 
Proto4z.AddEntityNotice.__protoID = 50005 
Proto4z.AddEntityNotice.__protoName = "AddEntityNotice" 
Proto4z.AddEntityNotice[1] = {name="entitys", type="EntityFullInfoArray" }  
Proto4z.AddEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50006,"RemoveEntityNotice") 
Proto4z.RemoveEntityNotice = {} --实体离开场景时, 把该实体的数据广播给其他玩家 
Proto4z.RemoveEntityNotice.__protoID = 50006 
Proto4z.RemoveEntityNotice.__protoName = "RemoveEntityNotice" 
Proto4z.RemoveEntityNotice[1] = {name="eids", type="EntityIDArray" }  
Proto4z.RemoveEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
