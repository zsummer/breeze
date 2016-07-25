 
Proto4z.register(50013,"AttachSpaceReq") 
Proto4z.AttachSpaceReq = {}  
Proto4z.AttachSpaceReq.__protoID = 50013 
Proto4z.AttachSpaceReq.__protoName = "AttachSpaceReq" 
Proto4z.AttachSpaceReq[1] = {name="userID", type="ui64" }  
Proto4z.AttachSpaceReq[2] = {name="spaceID", type="ui32" }  
Proto4z.AttachSpaceReq[3] = {name="token", type="string" } --令牌 
 
Proto4z.register(50014,"AttachSpaceResp") 
Proto4z.AttachSpaceResp = {}  
Proto4z.AttachSpaceResp.__protoID = 50014 
Proto4z.AttachSpaceResp.__protoName = "AttachSpaceResp" 
Proto4z.AttachSpaceResp[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.AttachSpaceResp[2] = {name="userID", type="ui64" }  
Proto4z.AttachSpaceResp[3] = {name="spaceID", type="ui32" }  
 
Proto4z.register(50009,"FillSpaceNotice") 
Proto4z.FillSpaceNotice = {} --填充场景数据 
Proto4z.FillSpaceNotice.__protoID = 50009 
Proto4z.FillSpaceNotice.__protoName = "FillSpaceNotice" 
Proto4z.FillSpaceNotice[1] = {name="entitys", type="EntityFullInfoArray" } --这里包含有所有当前场景下的实体属性和状态数据 
Proto4z.FillSpaceNotice[2] = {name="spaceStartTime", type="double" } --服务器战场开始时间 
Proto4z.FillSpaceNotice[3] = {name="spaceEndTime", type="double" } --服务器战场结束时间 
Proto4z.FillSpaceNotice[4] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50015,"RefreshSpaceEntitysNotice") 
Proto4z.RefreshSpaceEntitysNotice = {}  
Proto4z.RefreshSpaceEntitysNotice.__protoID = 50015 
Proto4z.RefreshSpaceEntitysNotice.__protoName = "RefreshSpaceEntitysNotice" 
Proto4z.RefreshSpaceEntitysNotice[1] = {name="entitys", type="EntityInfoArray" }  
Proto4z.RefreshSpaceEntitysNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50016,"RefreshSpaceReportsNotice") 
Proto4z.RefreshSpaceReportsNotice = {}  
Proto4z.RefreshSpaceReportsNotice.__protoID = 50016 
Proto4z.RefreshSpaceReportsNotice.__protoName = "RefreshSpaceReportsNotice" 
Proto4z.RefreshSpaceReportsNotice[1] = {name="reports", type="EntityReportArray" }  
Proto4z.RefreshSpaceReportsNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50011,"AddEntityNotice") 
Proto4z.AddEntityNotice = {} --一批实体加入场景时, 把这些实体的数据广播给其他玩家 
Proto4z.AddEntityNotice.__protoID = 50011 
Proto4z.AddEntityNotice.__protoName = "AddEntityNotice" 
Proto4z.AddEntityNotice[1] = {name="entitys", type="EntityFullInfoArray" }  
Proto4z.AddEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50012,"RemoveEntityNotice") 
Proto4z.RemoveEntityNotice = {} --实体离开场景时, 把该实体的数据广播给其他玩家 
Proto4z.RemoveEntityNotice.__protoID = 50012 
Proto4z.RemoveEntityNotice.__protoName = "RemoveEntityNotice" 
Proto4z.RemoveEntityNotice[1] = {name="eids", type="EntityIDArray" }  
Proto4z.RemoveEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
