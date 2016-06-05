 
Proto4z.register(40000,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__getID = 40000 
Proto4z.ClientAuthReq.__getName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(40001,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__getID = 40001 
Proto4z.ClientAuthResp.__getName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(40002,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创角色请求 
Proto4z.CreateUserReq.__getID = 40002 
Proto4z.CreateUserReq.__getName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="serviceName", type="string" }  
 
Proto4z.register(40003,"CreateUserResp") 
Proto4z.CreateUserResp = {} --创角色请求返回 
Proto4z.CreateUserResp.__getID = 40003 
Proto4z.CreateUserResp.__getName = "CreateUserResp" 
Proto4z.CreateUserResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserResp[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateUserResp[3] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(40004,"AttachUserReq") 
Proto4z.AttachUserReq = {} --选角色请求 
Proto4z.AttachUserReq.__getID = 40004 
Proto4z.AttachUserReq.__getName = "AttachUserReq" 
Proto4z.AttachUserReq[1] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40005,"AttachUserResp") 
Proto4z.AttachUserResp = {} --选角色请求返回 
Proto4z.AttachUserResp.__getID = 40005 
Proto4z.AttachUserResp.__getName = "AttachUserResp" 
Proto4z.AttachUserResp[1] = {name="retCode", type="ui16" }  
