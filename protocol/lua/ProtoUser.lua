 
Proto4z.register(1000,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__getID = 1000 
Proto4z.ClientAuthReq.__getName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(1001,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__getID = 1001 
Proto4z.ClientAuthResp.__getName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(1002,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创角色请求 
Proto4z.CreateUserReq.__getID = 1002 
Proto4z.CreateUserReq.__getName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="nickname", type="string" }  
 
Proto4z.register(1003,"CreateUserResp") 
Proto4z.CreateUserResp = {} --创角色请求返回 
Proto4z.CreateUserResp.__getID = 1003 
Proto4z.CreateUserResp.__getName = "CreateUserResp" 
Proto4z.CreateUserResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserResp[2] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(1004,"SelectUserReq") 
Proto4z.SelectUserReq = {} --选角色请求 
Proto4z.SelectUserReq.__getID = 1004 
Proto4z.SelectUserReq.__getName = "SelectUserReq" 
Proto4z.SelectUserReq[1] = {name="uID", type="ui64" }  
 
Proto4z.register(1005,"SelectUserResp") 
Proto4z.SelectUserResp = {} --选角色请求返回 
Proto4z.SelectUserResp.__getID = 1005 
Proto4z.SelectUserResp.__getName = "SelectUserResp" 
Proto4z.SelectUserResp[1] = {name="retCode", type="ui16" }  
