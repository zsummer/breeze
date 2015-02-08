 
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
Protoz.LS2C_LoginAck.__getTag = "111" 
Protoz.LS2C_LoginAck[1] = {name="retCode", type="i32" }  
Protoz.LS2C_LoginAck[2] = {name="needCreateUser", type="i32" }  
Protoz.LS2C_LoginAck[3] = {name="info", type="UserInfo" } --认证成功但昵称为空 则说明需要创建用户信息 
 
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
Protoz.LS2C_CreateUserAck.__getTag = "111" 
Protoz.LS2C_CreateUserAck[1] = {name="retCode", type="ui16" }  
Protoz.LS2C_CreateUserAck[2] = {name="needCreateUser", type="i32" } --nickname冲突需要重新创建 
Protoz.LS2C_CreateUserAck[3] = {name="info", type="UserInfo" }  
 
Protoz.register(106,"C2AS_ClientPulse") 
Protoz.C2AS_ClientPulse = {} --客户端存活脉冲 
Protoz.C2AS_ClientPulse.__getID = 106 
Protoz.C2AS_ClientPulse.__getName = "C2AS_ClientPulse" 
Protoz.C2AS_ClientPulse.__getTag = "" 
 
Protoz.register(107,"AS2C_ServerPulse") 
Protoz.AS2C_ServerPulse = {} --服务端存活脉冲 
Protoz.AS2C_ServerPulse.__getID = 107 
Protoz.AS2C_ServerPulse.__getName = "AS2C_ServerPulse" 
Protoz.AS2C_ServerPulse.__getTag = "11" 
Protoz.AS2C_ServerPulse[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Protoz.AS2C_ServerPulse[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
