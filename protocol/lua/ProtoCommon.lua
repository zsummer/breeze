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
 
Protoz.UserInfo = {} --用户信息 
Protoz.UserInfo.__getName = "UserInfo" 
Protoz.UserInfo.__getTag = "1111111" 
Protoz.UserInfo[1] = {name="uID", type="ui64" }  
Protoz.UserInfo[2] = {name="nickName", type="string" } --用户昵称 
Protoz.UserInfo[3] = {name="iconID", type="i16" } --头像 
Protoz.UserInfo[4] = {name="diamond", type="i32" } --当前剩余的充值钻石 
Protoz.UserInfo[5] = {name="hisotryDiamond", type="i32" } --历史充值钻石总额 
Protoz.UserInfo[6] = {name="giftDiamond", type="i32" } --当前剩余的赠送钻石 
Protoz.UserInfo[7] = {name="joinTime", type="ui32" } --加入时间 
 
Protoz.UserInfoVct = {}  
Protoz.UserInfoVct.__getName = "UserInfoVct" 
Protoz.UserInfoVct.__getDesc = "array" 
Protoz.UserInfoVct.__getTypeV = "UserInfo" 
 
Protoz.UserIDVct = {}  
Protoz.UserIDVct.__getName = "UserIDVct" 
Protoz.UserIDVct.__getDesc = "array" 
Protoz.UserIDVct.__getTypeV = "ui64" 
Protoz.ETRIGGER_USER_LOGIN = 0--用户登录, 用户ID 
Protoz.ETRIGGER_USER_LOGOUT = 1--用户登出, 用户ID 
