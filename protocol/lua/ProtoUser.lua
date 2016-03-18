 
Proto4z.register(1008,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__getID = 1008 
Proto4z.ClientAuthReq.__getName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(1009,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__getID = 1009 
Proto4z.ClientAuthResp.__getName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(1010,"UserAuthReq") 
Proto4z.UserAuthReq = {} --认证请求 
Proto4z.UserAuthReq.__getID = 1010 
Proto4z.UserAuthReq.__getName = "UserAuthReq" 
Proto4z.UserAuthReq[1] = {name="account", type="string" }  
Proto4z.UserAuthReq[2] = {name="token", type="string" }  
Proto4z.UserAuthReq[3] = {name="clientSessionID", type="ui32" }  
Proto4z.UserAuthReq[4] = {name="clientClusterID", type="ui32" }  
 
Proto4z.register(1011,"UserAuthResp") 
Proto4z.UserAuthResp = {} --认证回复 
Proto4z.UserAuthResp.__getID = 1011 
Proto4z.UserAuthResp.__getName = "UserAuthResp" 
Proto4z.UserAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.UserAuthResp[2] = {name="account", type="string" }  
Proto4z.UserAuthResp[3] = {name="token", type="string" }  
Proto4z.UserAuthResp[4] = {name="clientSessionID", type="ui32" }  
Proto4z.UserAuthResp[5] = {name="clientClusterID", type="ui32" }  
Proto4z.UserAuthResp[6] = {name="previews", type="UserPreviewArray" }  
 
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
Proto4z.SelectUserResp[2] = {name="svrIP", type="string" }  
Proto4z.SelectUserResp[3] = {name="svrPort", type="ui16" }  
Proto4z.SelectUserResp[4] = {name="uID", type="ui64" }  
Proto4z.SelectUserResp[5] = {name="token", type="string" }  
 
Proto4z.register(1006,"LoginUserReq") 
Proto4z.LoginUserReq = {} --登录角色请求 
Proto4z.LoginUserReq.__getID = 1006 
Proto4z.LoginUserReq.__getName = "LoginUserReq" 
Proto4z.LoginUserReq[1] = {name="uID", type="ui64" }  
Proto4z.LoginUserReq[2] = {name="token", type="string" }  
 
Proto4z.register(1007,"LoginUserResp") 
Proto4z.LoginUserResp = {} --登录角色返回 
Proto4z.LoginUserResp.__getID = 1007 
Proto4z.LoginUserResp.__getName = "LoginUserResp" 
Proto4z.LoginUserResp[1] = {name="retCode", type="ui16" }  
