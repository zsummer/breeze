 
Proto4z.register(20000,"SelectUserPreviewsFromUserMgrReq") 
Proto4z.SelectUserPreviewsFromUserMgrReq = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrReq.__getID = 20000 
Proto4z.SelectUserPreviewsFromUserMgrReq.__getName = "SelectUserPreviewsFromUserMgrReq" 
Proto4z.SelectUserPreviewsFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[2] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(20001,"SelectUserPreviewsFromUserMgrResp") 
Proto4z.SelectUserPreviewsFromUserMgrResp = {} --获取角色预览数据 
Proto4z.SelectUserPreviewsFromUserMgrResp.__getID = 20001 
Proto4z.SelectUserPreviewsFromUserMgrResp.__getName = "SelectUserPreviewsFromUserMgrResp" 
Proto4z.SelectUserPreviewsFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[2] = {name="account", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[3] = {name="token", type="string" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[4] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[5] = {name="clientSessionID", type="ui32" }  
Proto4z.SelectUserPreviewsFromUserMgrResp[6] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(20002,"CreateUserFromUserMgrReq") 
Proto4z.CreateUserFromUserMgrReq = {} --创角色请求 
Proto4z.CreateUserFromUserMgrReq.__getID = 20002 
Proto4z.CreateUserFromUserMgrReq.__getName = "CreateUserFromUserMgrReq" 
Proto4z.CreateUserFromUserMgrReq[1] = {name="account", type="string" }  
Proto4z.CreateUserFromUserMgrReq[2] = {name="nickname", type="string" }  
Proto4z.CreateUserFromUserMgrReq[3] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrReq[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(20003,"CreateUserFromUserMgrResp") 
Proto4z.CreateUserFromUserMgrResp = {} --创角色请求返回 
Proto4z.CreateUserFromUserMgrResp.__getID = 20003 
Proto4z.CreateUserFromUserMgrResp.__getName = "CreateUserFromUserMgrResp" 
Proto4z.CreateUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.CreateUserFromUserMgrResp[4] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(20004,"SelectUserFromUserMgrReq") 
Proto4z.SelectUserFromUserMgrReq = {} --选角色请求 
Proto4z.SelectUserFromUserMgrReq.__getID = 20004 
Proto4z.SelectUserFromUserMgrReq.__getName = "SelectUserFromUserMgrReq" 
Proto4z.SelectUserFromUserMgrReq[1] = {name="uID", type="ui64" }  
Proto4z.SelectUserFromUserMgrReq[2] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserFromUserMgrReq[3] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(20005,"SelectUserFromUserMgrResp") 
Proto4z.SelectUserFromUserMgrResp = {} --选角色请求返回 
Proto4z.SelectUserFromUserMgrResp.__getID = 20005 
Proto4z.SelectUserFromUserMgrResp.__getName = "SelectUserFromUserMgrResp" 
Proto4z.SelectUserFromUserMgrResp[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserFromUserMgrResp[2] = {name="clientDockerID", type="ui32" }  
Proto4z.SelectUserFromUserMgrResp[3] = {name="clientSessionID", type="ui32" }  
Proto4z.SelectUserFromUserMgrResp[4] = {name="userServiceID", type="ui64" }  
