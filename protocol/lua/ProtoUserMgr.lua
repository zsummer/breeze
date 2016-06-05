 
Proto4z.register(4000,"SelectUserPreviewsFromUserMgrReq") 
Proto4z.SelectUserPreviewsFromUserMgrReq = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrReq.__getID = 4000 
Proto4z.SelectUserPreviewsFromUserMgrReq.__getName = "SelectUserPreviewsFromUserMgrReq" 
Proto4z.SelectUserPreviewsFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[2] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4001,"SelectUserPreviewsFromUserMgrResp") 
Proto4z.SelectUserPreviewsFromUserMgrResp = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrResp.__getID = 4001 
Proto4z.SelectUserPreviewsFromUserMgrResp.__getName = "SelectUserPreviewsFromUserMgrResp" 
Proto4z.SelectUserPreviewsFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[2] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[3] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[4] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[5] = {name="clientSessionID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[6] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4002,"CreateUserFromUserMgrReq") 
Proto4z.CreateUserFromUserMgrReq = {} --创角色请求 
Proto4z.CreateUserFromUserMgrReq.__getID = 4002 
Proto4z.CreateUserFromUserMgrReq.__getName = "CreateUserFromUserMgrReq" 
Proto4z.CreateUserFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.CreateUserFromUserMgrReq[2] = {name="serviceName", type="string" }  
Proto4z.CreateUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4003,"CreateUserFromUserMgrResp") 
Proto4z.CreateUserFromUserMgrResp = {} --创角色请求返回 
Proto4z.CreateUserFromUserMgrResp.__getID = 4003 
Proto4z.CreateUserFromUserMgrResp.__getName = "CreateUserFromUserMgrResp" 
Proto4z.CreateUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[4] = {name="serviceID", type="ui64" }  
Proto4z.CreateUserFromUserMgrResp[5] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4004,"AttachUserFromUserMgrReq") 
Proto4z.AttachUserFromUserMgrReq = {} --选角色请求 
Proto4z.AttachUserFromUserMgrReq.__getID = 4004 
Proto4z.AttachUserFromUserMgrReq.__getName = "AttachUserFromUserMgrReq" 
Proto4z.AttachUserFromUserMgrReq[1] = {name="serviceID", type="ui64" }  
Proto4z.AttachUserFromUserMgrReq[2] = {name="account", type="string" }  
Proto4z.AttachUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.AttachUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4005,"AttachUserFromUserMgrResp") 
Proto4z.AttachUserFromUserMgrResp = {} --选角色请求返回 
Proto4z.AttachUserFromUserMgrResp.__getID = 4005 
Proto4z.AttachUserFromUserMgrResp.__getName = "AttachUserFromUserMgrResp" 
Proto4z.AttachUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.AttachUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.AttachUserFromUserMgrResp[4] = {name="serviceID", type="ui64" }  
 
Proto4z.register(4006,"ClientDisconnectReq") 
Proto4z.ClientDisconnectReq = {} --客户端断开了,通知给UserMgr 
Proto4z.ClientDisconnectReq.__getID = 4006 
Proto4z.ClientDisconnectReq.__getName = "ClientDisconnectReq" 
Proto4z.ClientDisconnectReq[1] = {name="retCode", type="ui16" }  
Proto4z.ClientDisconnectReq[2] = {name="clientDockerID", type="ui32" }  
Proto4z.ClientDisconnectReq[3] = {name="clientSessionID", type="ui32" }  
Proto4z.ClientDisconnectReq[4] = {name="serviceID", type="ui64" }  
