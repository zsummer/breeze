 
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
 
Proto4z.register(1000,"Tracing") 
Proto4z.Tracing = {} --docker间追踪数据 
Proto4z.Tracing.__protoID = 1000 
Proto4z.Tracing.__protoName = "Tracing" 
Proto4z.Tracing[1] = {name="toDockerID", type="ui32" } --forward转发时候先尝试通过DockerID进行转发 然后再尝试ServiceID  
Proto4z.Tracing[2] = {name="toServiceType", type="ui16" } --目标service类型 
Proto4z.Tracing[3] = {name="toServiceID", type="ui64" } --目标serviceID, 如果是单例 ID为InvalidServiceID.  
Proto4z.Tracing[4] = {name="fromDockerID", type="ui32" } --来源DockerID 
Proto4z.Tracing[5] = {name="fromServiceType", type="ui16" } --来源 
Proto4z.Tracing[6] = {name="fromServiceID", type="ui64" } --来源 
Proto4z.Tracing[7] = {name="traceID", type="ui32" } --本地cbID   
Proto4z.Tracing[8] = {name="traceBackID", type="ui32" } --把远程cbID透传回去  
 
Proto4z.register(1001,"UserPreview") 
Proto4z.UserPreview = {} --用户预览信息 
Proto4z.UserPreview.__protoID = 1001 
Proto4z.UserPreview.__protoName = "UserPreview" 
Proto4z.UserPreview[1] = {name="serviceID", type="ui64" } --用户唯一ID 
Proto4z.UserPreview[2] = {name="serviceName", type="string" } --昵称 
Proto4z.UserPreview[3] = {name="account", type="string" } --帐号 
Proto4z.UserPreview[4] = {name="iconID", type="i16" } --头像 
Proto4z.UserPreview[5] = {name="level", type="i32" } --等级 
 
Proto4z.UserPreviewArray = {}  
Proto4z.UserPreviewArray.__protoName = "UserPreviewArray" 
Proto4z.UserPreviewArray.__protoDesc = "array" 
Proto4z.UserPreviewArray.__protoTypeV = "UserPreview" 
 
Proto4z.ServiceIDArray = {}  
Proto4z.ServiceIDArray.__protoName = "ServiceIDArray" 
Proto4z.ServiceIDArray.__protoDesc = "array" 
Proto4z.ServiceIDArray.__protoTypeV = "ui64" 
 
Proto4z.register(1002,"UserBaseInfo") 
Proto4z.UserBaseInfo = {} --用户基础数据 
Proto4z.UserBaseInfo.__protoID = 1002 
Proto4z.UserBaseInfo.__protoName = "UserBaseInfo" 
Proto4z.UserBaseInfo[1] = {name="serviceID", type="ui64" } --用户唯一ID 
Proto4z.UserBaseInfo[2] = {name="serviceName", type="string" } --昵称 
Proto4z.UserBaseInfo[3] = {name="account", type="string" } --帐号 
Proto4z.UserBaseInfo[4] = {name="iconID", type="i16" } --头像 
Proto4z.UserBaseInfo[5] = {name="level", type="i32" } --等级 
 
Proto4z.UserBaseInfoArray = {}  
Proto4z.UserBaseInfoArray.__protoName = "UserBaseInfoArray" 
Proto4z.UserBaseInfoArray.__protoDesc = "array" 
Proto4z.UserBaseInfoArray.__protoTypeV = "UserBaseInfo" 
 
Proto4z.register(1003,"MoneyTree") 
Proto4z.MoneyTree = {} --摇钱树功能模块 
Proto4z.MoneyTree.__protoID = 1003 
Proto4z.MoneyTree.__protoName = "MoneyTree" 
Proto4z.MoneyTree[1] = {name="lastTime", type="ui32" } --最后一次执行时间 
Proto4z.MoneyTree[2] = {name="freeCount", type="ui32" } --今日剩余免费次数 
Proto4z.MoneyTree[3] = {name="payCount", type="ui32" } --今日已购买次数 
Proto4z.MoneyTree[4] = {name="statSum", type="ui32" } --历史总和 
Proto4z.MoneyTree[5] = {name="statCount", type="ui32" } --历史总次数 
 
Proto4z.register(1004,"SimplePack") 
Proto4z.SimplePack = {} --简单示例 
Proto4z.SimplePack.__protoID = 1004 
Proto4z.SimplePack.__protoName = "SimplePack" 
Proto4z.SimplePack[1] = {name="id", type="ui32" } --id, 对应数据库的结构为自增ID,key 
Proto4z.SimplePack[2] = {name="name", type="string" } --昵称, 唯一索引 
Proto4z.SimplePack[3] = {name="createTime", type="ui32" } --创建时间, 普通索引 
Proto4z.SimplePack[4] = {name="moneyTree", type="MoneyTree" }  
