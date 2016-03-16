 
Proto4z.register(1000,"AuthReq") 
Proto4z.AuthReq = {} --认证请求 
Proto4z.AuthReq.__getID = 1000 
Proto4z.AuthReq.__getName = "AuthReq" 
Proto4z.AuthReq[1] = {name="account", type="string" }  
Proto4z.AuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(1001,"AuthResp") 
Proto4z.AuthResp = {} --认证返回 
Proto4z.AuthResp.__getID = 1001 
Proto4z.AuthResp.__getName = "AuthResp" 
Proto4z.AuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.AuthResp[2] = {name="previews", type="UserPreviewArray" }  
 
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
