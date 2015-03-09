 
Protoz.register(102,"C2LS_LoginReq") 
Protoz.C2LS_LoginReq = {} --登录请求 
Protoz.C2LS_LoginReq.__getID = 102 
Protoz.C2LS_LoginReq.__getName = "C2LS_LoginReq" 
Protoz.C2LS_LoginReq.__getTag = "11" 
Protoz.C2LS_LoginReq[1] = {name="user", type="string" }  
Protoz.C2LS_LoginReq[2] = {name="passwd", type="string" }  
 
Protoz.register(103,"LS2C_LoginAck") 
Protoz.LS2C_LoginAck = {} --登录结果 
Protoz.LS2C_LoginAck.__getID = 103 
Protoz.LS2C_LoginAck.__getName = "LS2C_LoginAck" 
Protoz.LS2C_LoginAck.__getTag = "11" 
Protoz.LS2C_LoginAck[1] = {name="retCode", type="i32" }  
Protoz.LS2C_LoginAck[2] = {name="info", type="UserInfo" } --用户信息 
 
Protoz.register(108,"C2LS_CreateUserReq") 
Protoz.C2LS_CreateUserReq = {} --填写用户信息 
Protoz.C2LS_CreateUserReq.__getID = 108 
Protoz.C2LS_CreateUserReq.__getName = "C2LS_CreateUserReq" 
Protoz.C2LS_CreateUserReq.__getTag = "11" 
Protoz.C2LS_CreateUserReq[1] = {name="nickName", type="string" } --昵称 
Protoz.C2LS_CreateUserReq[2] = {name="iconID", type="i32" } --头像 
 
Protoz.register(109,"LS2C_CreateUserAck") 
Protoz.LS2C_CreateUserAck = {} --返回 
Protoz.LS2C_CreateUserAck.__getID = 109 
Protoz.LS2C_CreateUserAck.__getName = "LS2C_CreateUserAck" 
Protoz.LS2C_CreateUserAck.__getTag = "11" 
Protoz.LS2C_CreateUserAck[1] = {name="retCode", type="ui16" }  
Protoz.LS2C_CreateUserAck[2] = {name="info", type="UserInfo" }  
 
Protoz.register(111,"X2X_ServerPulse") 
Protoz.X2X_ServerPulse = {} --服务端存活脉冲 
Protoz.X2X_ServerPulse.__getID = 111 
Protoz.X2X_ServerPulse.__getName = "X2X_ServerPulse" 
Protoz.X2X_ServerPulse.__getTag = "11" 
Protoz.X2X_ServerPulse[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Protoz.X2X_ServerPulse[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
