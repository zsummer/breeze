 
Proto4z.register(0,"Heartbeat") 
Proto4z.Heartbeat = {} --心跳包 
Proto4z.Heartbeat.__getID = 0 
Proto4z.Heartbeat.__getName = "Heartbeat" 
Proto4z.Heartbeat[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Proto4z.Heartbeat[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Proto4z.register(1,"HeartbeatEcho") 
Proto4z.HeartbeatEcho = {} --心跳包需要立刻回复 
Proto4z.HeartbeatEcho.__getID = 1 
Proto4z.HeartbeatEcho.__getName = "HeartbeatEcho" 
Proto4z.HeartbeatEcho[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Proto4z.HeartbeatEcho[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Proto4z.register(2,"PlatAuthReq") 
Proto4z.PlatAuthReq = {} --平台认证 
Proto4z.PlatAuthReq.__getID = 2 
Proto4z.PlatAuthReq.__getName = "PlatAuthReq" 
Proto4z.PlatAuthReq[1] = {name="account", type="string" } --用户名 
Proto4z.PlatAuthReq[2] = {name="token", type="string" } --令牌 
 
Proto4z.register(3,"PlatAuthAck") 
Proto4z.PlatAuthAck = {} --认证结果, 包含该用户的所有用户/角色数据 
Proto4z.PlatAuthAck.__getID = 3 
Proto4z.PlatAuthAck.__getName = "PlatAuthAck" 
Proto4z.PlatAuthAck[1] = {name="retCode", type="ui16" }  
Proto4z.PlatAuthAck[2] = {name="users", type="BaseInfoArray" } --该帐号下的所有用户信息 
 
Proto4z.register(4,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创建一个新的用户数据 
Proto4z.CreateUserReq.__getID = 4 
Proto4z.CreateUserReq.__getName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="nickName", type="string" } --昵称 
Proto4z.CreateUserReq[2] = {name="iconID", type="i32" } --头像 
 
Proto4z.register(5,"CreateUserAck") 
Proto4z.CreateUserAck = {} --创建结果和所有用户数据 
Proto4z.CreateUserAck.__getID = 5 
Proto4z.CreateUserAck.__getName = "CreateUserAck" 
Proto4z.CreateUserAck[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserAck[2] = {name="users", type="BaseInfoArray" } --该帐号下的所有用户信息 
 
Proto4z.register(6,"SelectUserReq") 
Proto4z.SelectUserReq = {} --获取需要登录用户的所在服务器和认证令牌 
Proto4z.SelectUserReq.__getID = 6 
Proto4z.SelectUserReq.__getName = "SelectUserReq" 
Proto4z.SelectUserReq[1] = {name="uID", type="ui64" }  
 
Proto4z.register(7,"SelectUserAck") 
Proto4z.SelectUserAck = {} --获取需要登录用户的所在服务器和认证令牌 
Proto4z.SelectUserAck.__getID = 7 
Proto4z.SelectUserAck.__getName = "SelectUserAck" 
Proto4z.SelectUserAck[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserAck[2] = {name="uID", type="ui64" }  
Proto4z.SelectUserAck[3] = {name="token", type="string" }  
Proto4z.SelectUserAck[4] = {name="ip", type="string" }  
Proto4z.SelectUserAck[5] = {name="port", type="ui16" }  
 
Proto4z.register(8,"AttachLogicReq") 
Proto4z.AttachLogicReq = {} --挂到logic服务器上 
Proto4z.AttachLogicReq.__getID = 8 
Proto4z.AttachLogicReq.__getName = "AttachLogicReq" 
Proto4z.AttachLogicReq[1] = {name="uID", type="ui64" }  
Proto4z.AttachLogicReq[2] = {name="token", type="string" }  
 
Proto4z.register(9,"AttachLogicAck") 
Proto4z.AttachLogicAck = {} --挂到logic服务器上 
Proto4z.AttachLogicAck.__getID = 9 
Proto4z.AttachLogicAck.__getName = "AttachLogicAck" 
Proto4z.AttachLogicAck[1] = {name="retCode", type="ui16" }  
