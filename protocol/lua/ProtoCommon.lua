Protoz.EC_SUCCESS = 0--成功 
Protoz.EC_UNKOWN_ERROR = 1--未知错误 
Protoz.EC_INNER_ERROR = 2--内部错误 
Protoz.EC_DB_ERROR = 3--数据库错误 
Protoz.EC_PARAM_DENIED = 4--非法参数 
Protoz.EC_PERMISSION_DENIED = 5--权限非法 
Protoz.EC_SYSTEM_ERROR = 6--系统错误 
Protoz.EC_INVALIDE_USERID = 50--用户ID无效 
Protoz.EC_AUTH_USER_NOT_EXIST = 60--认证错误:用户不存在 
Protoz.EC_AUTH_PASSWD_INCORRECT = 61--认证错误:密码错误 
Protoz.EC_NO_USER = 62--没有该用户 
 
Protoz.SessionToken = {} --认证令牌 
Protoz.SessionToken.__getName = "SessionToken" 
Protoz.SessionToken.__getTag = "111" 
Protoz.SessionToken[1] = {name="uID", type="ui64" }  
Protoz.SessionToken[2] = {name="token", type="string" }  
Protoz.SessionToken[3] = {name="tokenExpire", type="ui32" }  
 
Protoz.UserInfo = {} --用户信息 
Protoz.UserInfo.__getName = "UserInfo" 
Protoz.UserInfo.__getTag = "11111111" 
Protoz.UserInfo[1] = {name="uID", type="ui64" } --用户唯一ID 
Protoz.UserInfo[2] = {name="account", type="string" } --帐号 
Protoz.UserInfo[3] = {name="nickName", type="string" } --昵称 
Protoz.UserInfo[4] = {name="iconID", type="i16" } --头像 
Protoz.UserInfo[5] = {name="diamond", type="i32" } --当前剩余的充值钻石 
Protoz.UserInfo[6] = {name="hisotryDiamond", type="i32" } --历史充值钻石总额 
Protoz.UserInfo[7] = {name="giftDiamond", type="i32" } --当前剩余的赠送钻石 
Protoz.UserInfo[8] = {name="joinTime", type="ui32" } --加入时间 
 
Protoz.UserInfoArray = {}  
Protoz.UserInfoArray.__getName = "UserInfoArray" 
Protoz.UserInfoArray.__getDesc = "array" 
Protoz.UserInfoArray.__getTypeV = "UserInfo" 
 
Protoz.UserIDArray = {}  
Protoz.UserIDArray.__getName = "UserIDArray" 
Protoz.UserIDArray.__getDesc = "array" 
Protoz.UserIDArray.__getTypeV = "ui64" 
Protoz.ETRIGGER_USER_LOGIN = 0--用户登录, 用户ID 
Protoz.ETRIGGER_USER_LOGOUT = 1--用户登出, 用户ID 
 
Protoz.register(200,"Heartbeat") 
Protoz.Heartbeat = {} --心跳包 
Protoz.Heartbeat.__getID = 200 
Protoz.Heartbeat.__getName = "Heartbeat" 
Protoz.Heartbeat.__getTag = "11" 
Protoz.Heartbeat[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Protoz.Heartbeat[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Protoz.register(201,"HeartbeatEcho") 
Protoz.HeartbeatEcho = {} --心跳包需要立刻回复 
Protoz.HeartbeatEcho.__getID = 201 
Protoz.HeartbeatEcho.__getName = "HeartbeatEcho" 
Protoz.HeartbeatEcho.__getTag = "11" 
Protoz.HeartbeatEcho[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Protoz.HeartbeatEcho[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
