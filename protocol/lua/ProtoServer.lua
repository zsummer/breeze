 
Proto4z.register(50000,"Heartbeat") 
Proto4z.Heartbeat = {} --心跳包 
Proto4z.Heartbeat.__getID = 50000 
Proto4z.Heartbeat.__getName = "Heartbeat" 
Proto4z.Heartbeat[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Proto4z.Heartbeat[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Proto4z.register(50001,"HeartbeatEcho") 
Proto4z.HeartbeatEcho = {} --心跳包需要立刻回复 
Proto4z.HeartbeatEcho.__getID = 50001 
Proto4z.HeartbeatEcho.__getName = "HeartbeatEcho" 
Proto4z.HeartbeatEcho[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Proto4z.HeartbeatEcho[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Proto4z.register(50002,"PlatAuthReq") 
Proto4z.PlatAuthReq = {} --平台认证 
Proto4z.PlatAuthReq.__getID = 50002 
Proto4z.PlatAuthReq.__getName = "PlatAuthReq" 
Proto4z.PlatAuthReq[1] = {name="account", type="string" } --用户名 
Proto4z.PlatAuthReq[2] = {name="token", type="string" } --令牌 
 
Proto4z.register(50003,"PlatAuthAck") 
Proto4z.PlatAuthAck = {} --认证结果, 包含该用户的所有用户/角色数据 
Proto4z.PlatAuthAck.__getID = 50003 
Proto4z.PlatAuthAck.__getName = "PlatAuthAck" 
Proto4z.PlatAuthAck[1] = {name="retCode", type="ui16" }  
Proto4z.PlatAuthAck[2] = {name="users", type="BaseInfoArray" } --该帐号下的所有用户信息 
 
Proto4z.register(50004,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创建一个新的用户数据 
Proto4z.CreateUserReq.__getID = 50004 
Proto4z.CreateUserReq.__getName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="nickName", type="string" } --昵称 
Proto4z.CreateUserReq[2] = {name="iconID", type="i32" } --头像 
 
Proto4z.register(50005,"CreateUserAck") 
Proto4z.CreateUserAck = {} --创建结果和所有用户数据 
Proto4z.CreateUserAck.__getID = 50005 
Proto4z.CreateUserAck.__getName = "CreateUserAck" 
Proto4z.CreateUserAck[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserAck[2] = {name="users", type="BaseInfoArray" } --该帐号下的所有用户信息 
 
Proto4z.register(50006,"SelectUserReq") 
Proto4z.SelectUserReq = {} --获取需要登录用户的所在服务器和认证令牌 
Proto4z.SelectUserReq.__getID = 50006 
Proto4z.SelectUserReq.__getName = "SelectUserReq" 
Proto4z.SelectUserReq[1] = {name="uID", type="ui64" }  
 
Proto4z.register(50007,"SelectUserAck") 
Proto4z.SelectUserAck = {} --获取需要登录用户的所在服务器和认证令牌 
Proto4z.SelectUserAck.__getID = 50007 
Proto4z.SelectUserAck.__getName = "SelectUserAck" 
Proto4z.SelectUserAck[1] = {name="retCode", type="ui16" }  
Proto4z.SelectUserAck[2] = {name="uID", type="ui64" }  
Proto4z.SelectUserAck[3] = {name="token", type="string" }  
Proto4z.SelectUserAck[4] = {name="ip", type="string" }  
Proto4z.SelectUserAck[5] = {name="port", type="ui16" }  
 
Proto4z.register(50008,"AttachLogicReq") 
Proto4z.AttachLogicReq = {} --挂到logic服务器上 
Proto4z.AttachLogicReq.__getID = 50008 
Proto4z.AttachLogicReq.__getName = "AttachLogicReq" 
Proto4z.AttachLogicReq[1] = {name="uID", type="ui64" }  
Proto4z.AttachLogicReq[2] = {name="token", type="string" }  
 
Proto4z.register(50009,"AttachLogicAck") 
Proto4z.AttachLogicAck = {} --挂到logic服务器上 
Proto4z.AttachLogicAck.__getID = 50009 
Proto4z.AttachLogicAck.__getName = "AttachLogicAck" 
Proto4z.AttachLogicAck[1] = {name="retCode", type="ui16" }  
