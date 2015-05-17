Proto4z.EC_SUCCESS = 0--成功 
Proto4z.EC_UNKOWN_ERROR = 1--未知错误 
Proto4z.EC_INNER_ERROR = 2--内部错误 
Proto4z.EC_DB_ERROR = 3--数据库错误 
Proto4z.EC_PARAM_DENIED = 4--非法参数 
Proto4z.EC_PERMISSION_DENIED = 5--权限非法 
Proto4z.EC_SYSTEM_ERROR = 6--系统错误 
Proto4z.EC_INVALIDE_USERID = 50--用户ID无效 
Proto4z.EC_AUTH_USER_NOT_EXIST = 60--认证错误:用户不存在 
Proto4z.EC_AUTH_PASSWD_INCORRECT = 61--认证错误:密码错误 
Proto4z.EC_NO_USER = 62--没有该用户 
 
Proto4z.SessionToken = {} --认证令牌 
Proto4z.SessionToken.__getName = "SessionToken" 
Proto4z.SessionToken.__getTag = "111" 
Proto4z.SessionToken[1] = {name="uID", type="ui64" }  
Proto4z.SessionToken[2] = {name="token", type="string" }  
Proto4z.SessionToken[3] = {name="tokenExpire", type="ui32" }  
 
Proto4z.UserInfo = {} --用户信息 
Proto4z.UserInfo.__getName = "UserInfo" 
Proto4z.UserInfo.__getTag = "11111111" 
Proto4z.UserInfo[1] = {name="uID", type="ui64" } --用户唯一ID 
Proto4z.UserInfo[2] = {name="account", type="string" } --帐号 
Proto4z.UserInfo[3] = {name="nickName", type="string" } --昵称 
Proto4z.UserInfo[4] = {name="iconID", type="i16" } --头像 
Proto4z.UserInfo[5] = {name="diamond", type="i32" } --当前剩余的充值钻石 
Proto4z.UserInfo[6] = {name="hisotryDiamond", type="i32" } --历史充值钻石总额 
Proto4z.UserInfo[7] = {name="giftDiamond", type="i32" } --当前剩余的赠送钻石 
Proto4z.UserInfo[8] = {name="joinTime", type="ui32" } --加入时间 
 
Proto4z.UserInfoArray = {}  
Proto4z.UserInfoArray.__getName = "UserInfoArray" 
Proto4z.UserInfoArray.__getDesc = "array" 
Proto4z.UserInfoArray.__getTypeV = "UserInfo" 
 
Proto4z.UserIDArray = {}  
Proto4z.UserIDArray.__getName = "UserIDArray" 
Proto4z.UserIDArray.__getDesc = "array" 
Proto4z.UserIDArray.__getTypeV = "ui64" 
Proto4z.ETRIGGER_USER_LOGIN = 0--用户登录, 用户ID 
Proto4z.ETRIGGER_USER_LOGOUT = 1--用户登出, 用户ID 
 
Proto4z.register(200,"Heartbeat") 
Proto4z.Heartbeat = {} --心跳包 
Proto4z.Heartbeat.__getID = 200 
Proto4z.Heartbeat.__getName = "Heartbeat" 
Proto4z.Heartbeat.__getTag = "11" 
Proto4z.Heartbeat[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Proto4z.Heartbeat[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 
Proto4z.register(201,"HeartbeatEcho") 
Proto4z.HeartbeatEcho = {} --心跳包需要立刻回复 
Proto4z.HeartbeatEcho.__getID = 201 
Proto4z.HeartbeatEcho.__getName = "HeartbeatEcho" 
Proto4z.HeartbeatEcho.__getTag = "11" 
Proto4z.HeartbeatEcho[1] = {name="timeStamp", type="ui32" } --服务器当前UTC时间戳 
Proto4z.HeartbeatEcho[2] = {name="timeTick", type="ui32" } --服务器当前tick时间戳 毫秒, 服务启动时刻为0 
