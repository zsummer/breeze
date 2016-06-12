 
Proto4z.register(4000,"SelectUserPreviewsFromUserMgrReq") 
Proto4z.SelectUserPreviewsFromUserMgrReq = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrReq.__protoID = 4000 
Proto4z.SelectUserPreviewsFromUserMgrReq.__protoName = "SelectUserPreviewsFromUserMgrReq" 
Proto4z.SelectUserPreviewsFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[2] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4001,"SelectUserPreviewsFromUserMgrResp") 
Proto4z.SelectUserPreviewsFromUserMgrResp = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrResp.__protoID = 4001 
Proto4z.SelectUserPreviewsFromUserMgrResp.__protoName = "SelectUserPreviewsFromUserMgrResp" 
Proto4z.SelectUserPreviewsFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[2] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[3] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[4] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[5] = {name="clientSessionID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[6] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4002,"CreateUserFromUserMgrReq") 
Proto4z.CreateUserFromUserMgrReq = {} --创角色请求 
Proto4z.CreateUserFromUserMgrReq.__protoID = 4002 
Proto4z.CreateUserFromUserMgrReq.__protoName = "CreateUserFromUserMgrReq" 
Proto4z.CreateUserFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.CreateUserFromUserMgrReq[2] = {name="serviceName", type="string" }  
Proto4z.CreateUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4003,"CreateUserFromUserMgrResp") 
Proto4z.CreateUserFromUserMgrResp = {} --创角色请求返回 
Proto4z.CreateUserFromUserMgrResp.__protoID = 4003 
Proto4z.CreateUserFromUserMgrResp.__protoName = "CreateUserFromUserMgrResp" 
Proto4z.CreateUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[4] = {name="serviceID", type="ui64" }  
Proto4z.CreateUserFromUserMgrResp[5] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(4004,"AttachUserFromUserMgrReq") 
Proto4z.AttachUserFromUserMgrReq = {} --选角色请求 
Proto4z.AttachUserFromUserMgrReq.__protoID = 4004 
Proto4z.AttachUserFromUserMgrReq.__protoName = "AttachUserFromUserMgrReq" 
Proto4z.AttachUserFromUserMgrReq[1] = {name="serviceID", type="ui64" }  
Proto4z.AttachUserFromUserMgrReq[2] = {name="account", type="string" }  
Proto4z.AttachUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.AttachUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(4005,"AttachUserFromUserMgrResp") 
Proto4z.AttachUserFromUserMgrResp = {} --选角色请求返回 
Proto4z.AttachUserFromUserMgrResp.__protoID = 4005 
Proto4z.AttachUserFromUserMgrResp.__protoName = "AttachUserFromUserMgrResp" 
Proto4z.AttachUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.AttachUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.AttachUserFromUserMgrResp[4] = {name="serviceID", type="ui64" }  
