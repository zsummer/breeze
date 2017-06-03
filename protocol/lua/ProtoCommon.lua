 
Proto4z.EC_SUCCESS = 0--成功 
Proto4z.EC_ERROR = 1--错误 
Proto4z.EC_INNER_ERROR = 2--内部错误 
Proto4z.EC_DB_ERROR = 3--数据库错误 
Proto4z.EC_PARAM_DENIED = 4--非法参数 
Proto4z.EC_PERMISSION_DENIED = 5--权限错误 
Proto4z.EC_REQUEST_EXPIRE = 6--请求操作已过期 
Proto4z.EC_TARGET_NOT_EXIST = 7--操作目标不存在 
Proto4z.EC_TOKEN_EXPIRE = 8--令牌过期 
Proto4z.EC_AVATAR_NOT_FOUND = 50--错误的用户信息 
Proto4z.EC_AVATAR_COUNT_LIMITE = 51--创建用户的数量超出限制 
Proto4z.EC_AVATAR_FREQ_LIMITE = 52--创建用户的频率超出限制 
Proto4z.EC_AVATAR_NAME_CONFLICT = 53--创建用户的昵称冲突 
Proto4z.EC_FRIEND_DUPLICATE = 100--请先删除与该好友建立的关系 
Proto4z.EC_FRIEND_CEILING = 101--达到好友上限 
Proto4z.EC_FRIEND_REFUSE = 102--不能添加对方为好友 
Proto4z.EC_FRIEND_NOT_EXIST = 103--好友不存在 
Proto4z.EC_SERVICE_NOT_OPEN = 104--服务未开放 
 
Proto4z.register(1000,"Routing") 
Proto4z.Routing = {} --docker to docker 路由信息 
Proto4z.Routing.__protoID = 1000 
Proto4z.Routing.__protoName = "Routing" 
Proto4z.Routing[1] = {name="toServiceType", type="ui16" } --目标service类型 
Proto4z.Routing[2] = {name="toServiceID", type="ui64" } --目标serviceID, 如果是单例 ID为InvalidServiceID.  
Proto4z.Routing[3] = {name="fromServiceType", type="ui16" } --来源 
Proto4z.Routing[4] = {name="fromServiceID", type="ui64" } --来源 
Proto4z.Routing[5] = {name="traceID", type="ui64" } --本地产生的回调ID 
Proto4z.Routing[6] = {name="traceBackID", type="ui64" } --远端产生的回调ID 
 
Proto4z.register(1001,"OutOfBand") 
Proto4z.OutOfBand = {} --带外信息 
Proto4z.OutOfBand.__protoID = 1001 
Proto4z.OutOfBand.__protoName = "OutOfBand" 
Proto4z.OutOfBand[1] = {name="clientDockerID", type="ui64" } --该数据由docker获得来自客户端的消息时自动填充. 
Proto4z.OutOfBand[2] = {name="clientSessionID", type="ui32" } --该数据由docker获得来自客户端的消息时自动填充. 
Proto4z.OutOfBand[3] = {name="clientAvatarID", type="ui64" } --该数据由docker获得来自客户端的消息时自动填充. 
 
Proto4z.register(1002,"Tracing") 
Proto4z.Tracing = {} --docker间追踪数据 
Proto4z.Tracing.__protoID = 1002 
Proto4z.Tracing.__protoName = "Tracing" 
Proto4z.Tracing[1] = {name="routing", type="Routing" } --路由信息 
Proto4z.Tracing[2] = {name="oob", type="OutOfBand" } --来自客户端的带外信息 
 
Proto4z.ServiceIDArray = {}  
Proto4z.ServiceIDArray.__protoName = "ServiceIDArray" 
Proto4z.ServiceIDArray.__protoDesc = "array" 
Proto4z.ServiceIDArray.__protoTypeV = "ui64" 
 
Proto4z.ServiceIDMap = {}  
Proto4z.ServiceIDMap.__protoName = "ServiceIDMap" 
Proto4z.ServiceIDMap.__protoDesc = "map" 
Proto4z.ServiceIDMap.__protoTypeK = "ui64" 
Proto4z.ServiceIDMap.__protoTypeV = "ui64" 
 
Proto4z.AccountArray = {}  
Proto4z.AccountArray.__protoName = "AccountArray" 
Proto4z.AccountArray.__protoDesc = "array" 
Proto4z.AccountArray.__protoTypeV = "string" 
 
Proto4z.register(1003,"AvatarPreview") 
Proto4z.AvatarPreview = {} --用户预览信息 
Proto4z.AvatarPreview.__protoID = 1003 
Proto4z.AvatarPreview.__protoName = "AvatarPreview" 
Proto4z.AvatarPreview[1] = {name="avatarID", type="ui64" } --用户唯一ID, 对应AvatarService的ServiceID 
Proto4z.AvatarPreview[2] = {name="avatarName", type="string" } --用户唯一昵称, 对应AvatarService的ServiceName 
Proto4z.AvatarPreview[3] = {name="account", type="string" } --帐号 
Proto4z.AvatarPreview[4] = {name="iconID", type="ui64" } --头像 
Proto4z.AvatarPreview[5] = {name="modeID", type="ui64" } --模型 
Proto4z.AvatarPreview[6] = {name="level", type="double" } --等级 
 
Proto4z.AvatarPreviewArray = {}  
Proto4z.AvatarPreviewArray.__protoName = "AvatarPreviewArray" 
Proto4z.AvatarPreviewArray.__protoDesc = "array" 
Proto4z.AvatarPreviewArray.__protoTypeV = "AvatarPreview" 
 
Proto4z.register(1004,"AvatarBaseInfo") 
Proto4z.AvatarBaseInfo = {} --用户基础数据 
Proto4z.AvatarBaseInfo.__protoID = 1004 
Proto4z.AvatarBaseInfo.__protoName = "AvatarBaseInfo" 
Proto4z.AvatarBaseInfo[1] = {name="avatarID", type="ui64" } --用户唯一ID, 对应AvatarService的ServiceID 
Proto4z.AvatarBaseInfo[2] = {name="avatarName", type="string" } --用户唯一昵称, 对应AvatarService的ServiceName 
Proto4z.AvatarBaseInfo[3] = {name="account", type="string" } --帐号 
Proto4z.AvatarBaseInfo[4] = {name="iconID", type="ui64" } --头像 
Proto4z.AvatarBaseInfo[5] = {name="modeID", type="ui64" } --模型 
Proto4z.AvatarBaseInfo[6] = {name="level", type="double" } --等级 
Proto4z.AvatarBaseInfo[7] = {name="exp", type="double" } --经验 
Proto4z.AvatarBaseInfo[8] = {name="gold", type="double" } --金币 
Proto4z.AvatarBaseInfo[9] = {name="diamond", type="double" } --钻石 
Proto4z.AvatarBaseInfo[10] = {name="createTime", type="ui64" } --角色创建时间 
 
Proto4z.AvatarBaseInfoArray = {}  
Proto4z.AvatarBaseInfoArray.__protoName = "AvatarBaseInfoArray" 
Proto4z.AvatarBaseInfoArray.__protoDesc = "array" 
Proto4z.AvatarBaseInfoArray.__protoTypeV = "AvatarBaseInfo" 
 
Proto4z.register(1005,"ItemInfo") 
Proto4z.ItemInfo = {} --道具字典 
Proto4z.ItemInfo.__protoID = 1005 
Proto4z.ItemInfo.__protoName = "ItemInfo" 
Proto4z.ItemInfo[1] = {name="stacks", type="ui16" } --可堆叠个数,0和1都是1次 
 
Proto4z.CC_WORLD = 0--世界频道 
Proto4z.CC_PRIVATE = 1--私人频道 
Proto4z.CC_SYSTEM = 2--系统频道 
Proto4z.CC_GROUP = 3--同编队频道 
Proto4z.CC_CAMP = 4--同阵营频道 
Proto4z.CC_SCENE = 5--同场景频道 
 
Proto4z.register(1006,"LogChat") 
Proto4z.LogChat = {} --聊天日志 
Proto4z.LogChat.__protoID = 1006 
Proto4z.LogChat.__protoName = "LogChat" 
Proto4z.LogChat[1] = {name="id", type="ui64" }  
Proto4z.LogChat[2] = {name="channelID", type="ui16" }  
Proto4z.LogChat[3] = {name="sourceID", type="ui64" }  
Proto4z.LogChat[4] = {name="sourceName", type="string" }  
Proto4z.LogChat[5] = {name="targetID", type="ui64" }  
Proto4z.LogChat[6] = {name="targetName", type="string" }  
Proto4z.LogChat[7] = {name="msg", type="string" }  
Proto4z.LogChat[8] = {name="chatTime", type="ui64" }  
 
Proto4z.register(1007,"MoneyTree") 
Proto4z.MoneyTree = {} --摇钱树功能模块 
Proto4z.MoneyTree.__protoID = 1007 
Proto4z.MoneyTree.__protoName = "MoneyTree" 
Proto4z.MoneyTree[1] = {name="lastTime", type="ui64" } --最后一次执行时间 
Proto4z.MoneyTree[2] = {name="freeCount", type="ui64" } --今日剩余免费次数 
Proto4z.MoneyTree[3] = {name="payCount", type="ui64" } --今日已购买次数 
Proto4z.MoneyTree[4] = {name="statSum", type="ui64" } --历史总和 
Proto4z.MoneyTree[5] = {name="statCount", type="ui64" } --历史总次数 
 
Proto4z.register(1008,"SimplePack") 
Proto4z.SimplePack = {} --简单示例 
Proto4z.SimplePack.__protoID = 1008 
Proto4z.SimplePack.__protoName = "SimplePack" 
Proto4z.SimplePack[1] = {name="id", type="ui64" } --id, 对应数据库的结构为自增ID,key 
Proto4z.SimplePack[2] = {name="name", type="string" } --昵称, 唯一索引 
Proto4z.SimplePack[3] = {name="createTime", type="ui64" } --创建时间, 普通索引 
Proto4z.SimplePack[4] = {name="moneyTree", type="MoneyTree" }  
