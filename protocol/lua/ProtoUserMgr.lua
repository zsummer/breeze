 
Proto4z.register(4000,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__getID = 4000 
Proto4z.ClientAuthReq.__getName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(4001,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__getID = 4001 
Proto4z.ClientAuthResp.__getName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4002,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创角色请求 
Proto4z.CreateUserReq.__getID = 4002 
Proto4z.CreateUserReq.__getName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="serviceName", type="string" }  
 
Proto4z.register(4003,"CreateUserResp") 
Proto4z.CreateUserResp = {} --创角色请求返回 
Proto4z.CreateUserResp.__getID = 4003 
Proto4z.CreateUserResp.__getName = "CreateUserResp" 
Proto4z.CreateUserResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserResp[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateUserResp[3] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4004,"AttachUserReq") 
Proto4z.AttachUserReq = {} --选角色请求 
Proto4z.AttachUserReq.__getID = 4004 
Proto4z.AttachUserReq.__getName = "AttachUserReq" 
Proto4z.AttachUserReq[1] = {name="serviceID", type="ui64" }  
 
Proto4z.register(4005,"AttachUserResp") 
Proto4z.AttachUserResp = {} --选角色请求返回 
Proto4z.AttachUserResp.__getID = 4005 
Proto4z.AttachUserResp.__getName = "AttachUserResp" 
Proto4z.AttachUserResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(4006,"SelectUserPreviewsFromUserMgrReq") 
Proto4z.SelectUserPreviewsFromUserMgrReq = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrReq.__getID = 4006 
Proto4z.SelectUserPreviewsFromUserMgrReq.__getName = "SelectUserPreviewsFromUserMgrReq" 
Proto4z.SelectUserPreviewsFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[2] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4007,"SelectUserPreviewsFromUserMgrResp") 
Proto4z.SelectUserPreviewsFromUserMgrResp = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrResp.__getID = 4007 
Proto4z.SelectUserPreviewsFromUserMgrResp.__getName = "SelectUserPreviewsFromUserMgrResp" 
Proto4z.SelectUserPreviewsFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[2] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[3] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[4] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[5] = {name="clientSessionID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[6] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4008,"CreateUserFromUserMgrReq") 
Proto4z.CreateUserFromUserMgrReq = {} --创角色请求 
Proto4z.CreateUserFromUserMgrReq.__getID = 4008 
Proto4z.CreateUserFromUserMgrReq.__getName = "CreateUserFromUserMgrReq" 
Proto4z.CreateUserFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.CreateUserFromUserMgrReq[2] = {name="serviceName", type="string" }  
Proto4z.CreateUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4009,"CreateUserFromUserMgrResp") 
Proto4z.CreateUserFromUserMgrResp = {} --创角色请求返回 
Proto4z.CreateUserFromUserMgrResp.__getID = 4009 
Proto4z.CreateUserFromUserMgrResp.__getName = "CreateUserFromUserMgrResp" 
Proto4z.CreateUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[4] = {name="serviceID", type="ui64" }  
Proto4z.CreateUserFromUserMgrResp[5] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4010,"AttachUserFromUserMgrReq") 
Proto4z.AttachUserFromUserMgrReq = {} --选角色请求 
Proto4z.AttachUserFromUserMgrReq.__getID = 4010 
Proto4z.AttachUserFromUserMgrReq.__getName = "AttachUserFromUserMgrReq" 
Proto4z.AttachUserFromUserMgrReq[1] = {name="serviceID", type="ui64" }  
Proto4z.AttachUserFromUserMgrReq[2] = {name="account", type="string" }  
Proto4z.AttachUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.AttachUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4011,"AttachUserFromUserMgrResp") 
Proto4z.AttachUserFromUserMgrResp = {} --选角色请求返回 
Proto4z.AttachUserFromUserMgrResp.__getID = 4011 
Proto4z.AttachUserFromUserMgrResp.__getName = "AttachUserFromUserMgrResp" 
Proto4z.AttachUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.AttachUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.AttachUserFromUserMgrResp[4] = {name="serviceID", type="ui64" }  
