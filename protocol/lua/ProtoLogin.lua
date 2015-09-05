 
Proto4z.register(100,"PlatAuthReq") 
Proto4z.PlatAuthReq = {} --平台认证 
Proto4z.PlatAuthReq.__getID = 100 
Proto4z.PlatAuthReq.__getName = "PlatAuthReq" 
Proto4z.PlatAuthReq[1] = {name="account", type="string" } --用户名 
Proto4z.PlatAuthReq[2] = {name="token", type="string" } --令牌 
 
Proto4z.register(101,"PlatAuthAck") 
Proto4z.PlatAuthAck = {} --认证结果, 包含该用户的所有用户/角色数据 
Proto4z.PlatAuthAck.__getID = 101 
Proto4z.PlatAuthAck.__getName = "PlatAuthAck" 
Proto4z.PlatAuthAck[1] = {name="retCode", type="ui16" }  
Proto4z.PlatAuthAck[2] = {name="users", type="UserInfoArray" } --该帐号下的所有用户信息 
 
Proto4z.register(102,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创建一个新的用户数据 
Proto4z.CreateUserReq.__getID = 102 
Proto4z.CreateUserReq.__getName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="nickName", type="string" } --昵称 
Proto4z.CreateUserReq[2] = {name="iconID", type="i32" } --头像 
 
Proto4z.register(103,"CreateUserAck") 
Proto4z.CreateUserAck = {} --创建结果和所有用户数据 
Proto4z.CreateUserAck.__getID = 103 
Proto4z.CreateUserAck.__getName = "CreateUserAck" 
Proto4z.CreateUserAck[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserAck[2] = {name="users", type="UserInfoArray" } --该帐号下的所有用户信息 
 
Proto4z.register(104,"SelectUserReq") 
Proto4z.SelectUserReq = {} --获取需要登录用户的所在服务器和认证令牌 
Proto4z.SelectUserReq.__getID = 104 
Proto4z.SelectUserReq.__getName = "SelectUserReq" 
Proto4z.SelectUserReq[1] = {name="uID", type="ui64" }  
 
Proto4z.register(105,"SelectUserAck") 
Proto4z.SelectUserAck = {} --获取需要登录用户的所在服务器和认证令牌 
Proto4z.SelectUserAck.__getID = 105 
Proto4z.SelectUserAck.__getName = "SelectUserAck" 
Proto4z.SelectUserAck[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserAck[2] = {name="uID", type="ui64" }  
Proto4z.SelectUserAck[3] = {name="token", type="string" }  
Proto4z.SelectUserAck[4] = {name="ip", type="string" }  
Proto4z.SelectUserAck[5] = {name="port", type="ui16" }  
 
Proto4z.register(106,"LinkServerReq") 
Proto4z.LinkServerReq = {} --连接到服务器 
Proto4z.LinkServerReq.__getID = 106 
Proto4z.LinkServerReq.__getName = "LinkServerReq" 
Proto4z.LinkServerReq[1] = {name="uID", type="ui64" }  
Proto4z.LinkServerReq[2] = {name="token", type="string" }  
 
Proto4z.register(107,"LinkServerAck") 
Proto4z.LinkServerAck = {} --连接到服务器 
Proto4z.LinkServerAck.__getID = 107 
Proto4z.LinkServerAck.__getName = "LinkServerAck" 
Proto4z.LinkServerAck[1] = {name="retCode", type="ui16" }  
