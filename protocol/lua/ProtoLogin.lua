 
Protoz.register(100,"LoginReq") 
Protoz.LoginReq = {} --登录请求 
Protoz.LoginReq.__getID = 100 
Protoz.LoginReq.__getName = "LoginReq" 
Protoz.LoginReq.__getTag = "11" 
Protoz.LoginReq[1] = {name="user", type="string" }  
Protoz.LoginReq[2] = {name="passwd", type="string" }  
 
Protoz.register(101,"LoginAck") 
Protoz.LoginAck = {} --登录结果 
Protoz.LoginAck.__getID = 101 
Protoz.LoginAck.__getName = "LoginAck" 
Protoz.LoginAck.__getTag = "11" 
Protoz.LoginAck[1] = {name="retCode", type="ui16" }  
Protoz.LoginAck[2] = {name="info", type="UserInfo" } --用户信息 
 
Protoz.register(102,"CreateUserReq") 
Protoz.CreateUserReq = {} --填写用户信息 
Protoz.CreateUserReq.__getID = 102 
Protoz.CreateUserReq.__getName = "CreateUserReq" 
Protoz.CreateUserReq.__getTag = "11" 
Protoz.CreateUserReq[1] = {name="nickName", type="string" } --昵称 
Protoz.CreateUserReq[2] = {name="iconID", type="i32" } --头像 
 
Protoz.register(103,"CreateUserAck") 
Protoz.CreateUserAck = {} --返回 
Protoz.CreateUserAck.__getID = 103 
Protoz.CreateUserAck.__getName = "CreateUserAck" 
Protoz.CreateUserAck.__getTag = "11" 
Protoz.CreateUserAck[1] = {name="retCode", type="ui16" }  
Protoz.CreateUserAck[2] = {name="info", type="UserInfo" }  
 
Protoz.register(104,"ServerPulse") 
Protoz.ServerPulse = {} --服务器生命脉冲 
Protoz.ServerPulse.__getID = 104 
Protoz.ServerPulse.__getName = "ServerPulse" 
Protoz.ServerPulse.__getTag = "11" 
Protoz.ServerPulse[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Protoz.ServerPulse[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Protoz.register(105,"ServerPulseEcho") 
Protoz.ServerPulseEcho = {} --服务器生命脉冲客户端回放 
Protoz.ServerPulseEcho.__getID = 105 
Protoz.ServerPulseEcho.__getName = "ServerPulseEcho" 
Protoz.ServerPulseEcho.__getTag = "11" 
Protoz.ServerPulseEcho[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Protoz.ServerPulseEcho[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
