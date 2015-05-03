 
Protoz.register(100,"PlatAuthReq") 
Protoz.PlatAuthReq = {} --平台认证 
Protoz.PlatAuthReq.__getID = 100 
Protoz.PlatAuthReq.__getName = "PlatAuthReq" 
Protoz.PlatAuthReq.__getTag = "11" 
Protoz.PlatAuthReq[1] = {name="account", type="string" } --用户名 
Protoz.PlatAuthReq[2] = {name="token", type="string" } --令牌 
 
Protoz.register(101,"PlatAuthAck") 
Protoz.PlatAuthAck = {} --认证结果, 包含该用户的所有用户/角色数据 
Protoz.PlatAuthAck.__getID = 101 
Protoz.PlatAuthAck.__getName = "PlatAuthAck" 
Protoz.PlatAuthAck.__getTag = "11" 
Protoz.PlatAuthAck[1] = {name="retCode", type="ui16" }  
Protoz.PlatAuthAck[2] = {name="users", type="UserInfoArray" } --该帐号下的所有用户信息 
 
Protoz.register(102,"CreateUserReq") 
Protoz.CreateUserReq = {} --创建一个新的用户数据 
Protoz.CreateUserReq.__getID = 102 
Protoz.CreateUserReq.__getName = "CreateUserReq" 
Protoz.CreateUserReq.__getTag = "11" 
Protoz.CreateUserReq[1] = {name="nickName", type="string" } --昵称 
Protoz.CreateUserReq[2] = {name="iconID", type="i32" } --头像 
 
Protoz.register(103,"CreateUserAck") 
Protoz.CreateUserAck = {} --创建结果和所有用户数据 
Protoz.CreateUserAck.__getID = 103 
Protoz.CreateUserAck.__getName = "CreateUserAck" 
Protoz.CreateUserAck.__getTag = "11" 
Protoz.CreateUserAck[1] = {name="retCode", type="ui16" }  
Protoz.CreateUserAck[2] = {name="users", type="UserInfoArray" } --该帐号下的所有用户信息 
 
Protoz.register(104,"SelectUserReq") 
Protoz.SelectUserReq = {} --获取需要登录用户的所在服务器和认证令牌 
Protoz.SelectUserReq.__getID = 104 
Protoz.SelectUserReq.__getName = "SelectUserReq" 
Protoz.SelectUserReq.__getTag = "1" 
Protoz.SelectUserReq[1] = {name="uID", type="ui64" }  
 
Protoz.register(105,"SelectUserAck") 
Protoz.SelectUserAck = {} --获取需要登录用户的所在服务器和认证令牌 
Protoz.SelectUserAck.__getID = 105 
Protoz.SelectUserAck.__getName = "SelectUserAck" 
Protoz.SelectUserAck.__getTag = "11111" 
Protoz.SelectUserAck[1] = {name="retCode", type="ui16" }  
Protoz.SelectUserAck[2] = {name="uID", type="ui64" }  
Protoz.SelectUserAck[3] = {name="token", type="string" }  
Protoz.SelectUserAck[4] = {name="ip", type="string" }  
Protoz.SelectUserAck[5] = {name="port", type="ui16" }  
 
Protoz.register(106,"LoginReq") 
Protoz.LoginReq = {} --登录请求 
Protoz.LoginReq.__getID = 106 
Protoz.LoginReq.__getName = "LoginReq" 
Protoz.LoginReq.__getTag = "11" 
Protoz.LoginReq[1] = {name="uID", type="ui64" }  
Protoz.LoginReq[2] = {name="token", type="string" }  
 
Protoz.register(107,"LoginAck") 
Protoz.LoginAck = {} --登录结果 
Protoz.LoginAck.__getID = 107 
Protoz.LoginAck.__getName = "LoginAck" 
Protoz.LoginAck.__getTag = "1" 
Protoz.LoginAck[1] = {name="retCode", type="ui16" }  
