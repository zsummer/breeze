 
Proto4z.EC_SUCCESS = 0--成功 
Proto4z.EC_ERROR = 1--错误 
Proto4z.EC_INNER_ERROR = 2--内部错误 
Proto4z.EC_DB_ERROR = 3--数据库错误 
Proto4z.EC_PARAM_DENIED = 4--非法参数 
Proto4z.EC_PERMISSION_DENIED = 5--权限错误 
Proto4z.EC_REQUEST_EXPIRE = 6--请求操作已过期 
Proto4z.EC_TARGET_NOT_EXIST = 7--操作目标不存在 
Proto4z.EC_TOKEN_EXPIRE = 8--令牌过期 
Proto4z.EC_USER_NOT_FOUND = 50--错误的用户信息 
Proto4z.EC_USER_OFFLINE = 51--错误的用户信息 
Proto4z.EC_FRIEND_DUPLICATE = 100--请先删除与该好友建立的关系 
Proto4z.EC_FRIEND_CEILING = 101--达到好友上限 
Proto4z.EC_FRIEND_REFUSE = 102--不能添加对方为好友 
Proto4z.EC_FRIEND_NOT_EXIST = 103--好友不存在 
 
Proto4z.register(1000,"UserPreview") 
Proto4z.UserPreview = {} --用户预览信息 
Proto4z.UserPreview.__getID = 1000 
Proto4z.UserPreview.__getName = "UserPreview" 
Proto4z.UserPreview[1] = {name="uID", type="ui64" } --用户ID 
Proto4z.UserPreview[2] = {name="uName", type="string" } --昵称 
Proto4z.UserPreview[3] = {name="iconID", type="i16" } --头像 
Proto4z.UserPreview[4] = {name="account", type="string" } --帐号 
 
Proto4z.UserPreviewArray = {}  
Proto4z.UserPreviewArray.__getName = "UserPreviewArray" 
Proto4z.UserPreviewArray.__getDesc = "array" 
Proto4z.UserPreviewArray.__getTypeV = "UserPreview" 
 
Proto4z.UIDS = {}  
Proto4z.UIDS.__getName = "UIDS" 
Proto4z.UIDS.__getDesc = "array" 
Proto4z.UIDS.__getTypeV = "ui64" 
 
Proto4z.register(1001,"UserBaseInfo") 
Proto4z.UserBaseInfo = {} --用户基础数据 
Proto4z.UserBaseInfo.__getID = 1001 
Proto4z.UserBaseInfo.__getName = "UserBaseInfo" 
Proto4z.UserBaseInfo[1] = {name="uID", type="ui64" } --用户唯一ID 
Proto4z.UserBaseInfo[2] = {name="account", type="string" } --帐号 
Proto4z.UserBaseInfo[3] = {name="nickName", type="string" } --昵称 
Proto4z.UserBaseInfo[4] = {name="iconID", type="i16" } --头像 
Proto4z.UserBaseInfo[5] = {name="level", type="i32" } --等级 
 
Proto4z.UserBaseInfoArray = {}  
Proto4z.UserBaseInfoArray.__getName = "UserBaseInfoArray" 
Proto4z.UserBaseInfoArray.__getDesc = "array" 
Proto4z.UserBaseInfoArray.__getTypeV = "UserBaseInfo" 
