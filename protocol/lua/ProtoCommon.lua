 
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
Proto4z.EC_USER_COUNT_LIMITE = 51--创建用户的数量超出限制 
Proto4z.EC_USER_FREQ_LIMITE = 52--创建用户的频率超出限制 
Proto4z.EC_USER_NAME_CONFLICT = 53--创建用户的昵称冲突 
Proto4z.EC_FRIEND_DUPLICATE = 100--请先删除与该好友建立的关系 
Proto4z.EC_FRIEND_CEILING = 101--达到好友上限 
Proto4z.EC_FRIEND_REFUSE = 102--不能添加对方为好友 
Proto4z.EC_FRIEND_NOT_EXIST = 103--好友不存在 
 
Proto4z.register(1005,"Routing") 
Proto4z.Routing = {} --docker to docker 路由信息 
Proto4z.Routing.__protoID = 1005 
Proto4z.Routing.__protoName = "Routing" 
Proto4z.Routing[1] = {name="toServiceType", type="ui16" } --目标service类型 
Proto4z.Routing[2] = {name="toServiceID", type="ui64" } --目标serviceID, 如果是单例 ID为InvalidServiceID.  
Proto4z.Routing[3] = {name="fromServiceType", type="ui16" } --来源 
Proto4z.Routing[4] = {name="fromServiceID", type="ui64" } --来源 
Proto4z.Routing[5] = {name="traceID", type="ui32" } --本地产生的回调ID 
Proto4z.Routing[6] = {name="traceBackID", type="ui32" } --远端产生的回调ID 
 
Proto4z.register(1006,"OutOfBand") 
Proto4z.OutOfBand = {} --带外信息 
Proto4z.OutOfBand.__protoID = 1006 
Proto4z.OutOfBand.__protoName = "OutOfBand" 
Proto4z.OutOfBand[1] = {name="clientDockerID", type="ui32" } --该数据由docker获得来自客户端的消息时自动填充. 
Proto4z.OutOfBand[2] = {name="clientSessionID", type="ui32" } --该数据由docker获得来自客户端的消息时自动填充. 
Proto4z.OutOfBand[3] = {name="clientUserID", type="ui64" } --该数据由docker获得来自客户端的消息时自动填充. 
 
Proto4z.register(1000,"Tracing") 
Proto4z.Tracing = {} --docker间追踪数据 
Proto4z.Tracing.__protoID = 1000 
Proto4z.Tracing.__protoName = "Tracing" 
Proto4z.Tracing[1] = {name="routing", type="Routing" } --路由信息 
Proto4z.Tracing[2] = {name="oob", type="OutOfBand" } --来自客户端的带外信息 
 
Proto4z.UserIDArray = {}  
Proto4z.UserIDArray.__protoName = "UserIDArray" 
Proto4z.UserIDArray.__protoDesc = "array" 
Proto4z.UserIDArray.__protoTypeV = "ui64" 
 
Proto4z.register(1001,"UserPreview") 
Proto4z.UserPreview = {} --用户预览信息 
Proto4z.UserPreview.__protoID = 1001 
Proto4z.UserPreview.__protoName = "UserPreview" 
Proto4z.UserPreview[1] = {name="userID", type="ui64" } --用户唯一ID, 对应UserService的ServiceID 
Proto4z.UserPreview[2] = {name="userName", type="string" } --用户唯一昵称, 对应UserService的ServiceName 
Proto4z.UserPreview[3] = {name="account", type="string" } --帐号 
Proto4z.UserPreview[4] = {name="iconID", type="i16" } --头像 
Proto4z.UserPreview[5] = {name="level", type="i32" } --等级 
 
Proto4z.UserPreviewArray = {}  
Proto4z.UserPreviewArray.__protoName = "UserPreviewArray" 
Proto4z.UserPreviewArray.__protoDesc = "array" 
Proto4z.UserPreviewArray.__protoTypeV = "UserPreview" 
 
Proto4z.register(1002,"UserBaseInfo") 
Proto4z.UserBaseInfo = {} --用户基础数据 
Proto4z.UserBaseInfo.__protoID = 1002 
Proto4z.UserBaseInfo.__protoName = "UserBaseInfo" 
Proto4z.UserBaseInfo[1] = {name="userID", type="ui64" } --用户唯一ID, 对应UserService的ServiceID 
Proto4z.UserBaseInfo[2] = {name="userName", type="string" } --用户唯一昵称, 对应UserService的ServiceName 
Proto4z.UserBaseInfo[3] = {name="account", type="string" } --帐号 
Proto4z.UserBaseInfo[4] = {name="iconID", type="i16" } --头像 
Proto4z.UserBaseInfo[5] = {name="level", type="i32" } --等级 
Proto4z.UserBaseInfo[6] = {name="hp", type="double" } --血量值 
Proto4z.UserBaseInfo[7] = {name="hpRegen", type="double" } --每秒血量值恢复 
Proto4z.UserBaseInfo[8] = {name="attack", type="double" } --伤害 
Proto4z.UserBaseInfo[9] = {name="defense", type="double" } --防御 
Proto4z.UserBaseInfo[10] = {name="crit", type="double" } --暴击 
Proto4z.UserBaseInfo[11] = {name="toughness", type="double" } --韧性 
Proto4z.UserBaseInfo[12] = {name="moveSpeed", type="double" } --移动速度 
Proto4z.UserBaseInfo[13] = {name="attackSpeed", type="double" } --攻击速度 
Proto4z.UserBaseInfo[14] = {name="vampirk", type="double" } --吸血 
 
Proto4z.UserBaseInfoArray = {}  
Proto4z.UserBaseInfoArray.__protoName = "UserBaseInfoArray" 
Proto4z.UserBaseInfoArray.__protoDesc = "array" 
Proto4z.UserBaseInfoArray.__protoTypeV = "UserBaseInfo" 
 
Proto4z.register(1007,"DictGlobal") 
Proto4z.DictGlobal = {} --全局配置 
Proto4z.DictGlobal.__protoID = 1007 
Proto4z.DictGlobal.__protoName = "DictGlobal" 
Proto4z.DictGlobal[1] = {name="id", type="ui32" }  
Proto4z.DictGlobal[2] = {name="val", type="ui64" } --整数 
Proto4z.DictGlobal[3] = {name="valFloat", type="double" } --浮点数 
Proto4z.DictGlobal[4] = {name="combo", type="string" } --字符串 
Proto4z.DictGlobal[5] = {name="desc", type="string" }  
 
Proto4z.register(1008,"DictRaffleAward") 
Proto4z.DictRaffleAward = {} --奖池中的奖品 
Proto4z.DictRaffleAward.__protoID = 1008 
Proto4z.DictRaffleAward.__protoName = "DictRaffleAward" 
Proto4z.DictRaffleAward[1] = {name="id", type="ui32" } --奖品ID 
Proto4z.DictRaffleAward[2] = {name="weight", type="ui32" } --本奖品在奖池中的权重, 总权重在[10000~30000]之间的随机效果最好 
Proto4z.DictRaffleAward[3] = {name="probability", type="double" } --[0~1]独立随机的概率,0为永远无法随机到 1是100%随机到 
 
Proto4z.DictRaffleAwardArray = {}  
Proto4z.DictRaffleAwardArray.__protoName = "DictRaffleAwardArray" 
Proto4z.DictRaffleAwardArray.__protoDesc = "array" 
Proto4z.DictRaffleAwardArray.__protoTypeV = "DictRaffleAward" 
 
Proto4z.register(1009,"DictRafflePool") 
Proto4z.DictRafflePool = {} --道具抽奖,道具掉落 
Proto4z.DictRafflePool.__protoID = 1009 
Proto4z.DictRafflePool.__protoName = "DictRafflePool" 
Proto4z.DictRafflePool[1] = {name="id", type="ui32" }  
Proto4z.DictRafflePool[2] = {name="raffleCount", type="i32" } --批量抽取次数 
Proto4z.DictRafflePool[3] = {name="pool", type="DictRaffleAwardArray" } --奖池 
Proto4z.DictRafflePool[4] = {name="poolString", type="string" } --奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式 
 
Proto4z.register(1010,"DictBaseProps") 
Proto4z.DictBaseProps = {} --战斗属性效果,用于装备,属性类增减益buff 
Proto4z.DictBaseProps.__protoID = 1010 
Proto4z.DictBaseProps.__protoName = "DictBaseProps" 
Proto4z.DictBaseProps[1] = {name="id", type="ui32" }  
Proto4z.DictBaseProps[2] = {name="hp", type="double" } --血量值 
Proto4z.DictBaseProps[3] = {name="hpRegen", type="double" } --每秒血量值恢复 
Proto4z.DictBaseProps[4] = {name="attack", type="double" } --伤害 
Proto4z.DictBaseProps[5] = {name="defense", type="double" } --防御 
Proto4z.DictBaseProps[6] = {name="crit", type="double" } --暴击 
Proto4z.DictBaseProps[7] = {name="toughness", type="double" } --韧性 
Proto4z.DictBaseProps[8] = {name="moveSpeed", type="double" } --移动速度 
Proto4z.DictBaseProps[9] = {name="attackSpeed", type="double" } --攻击速度 
Proto4z.DictBaseProps[10] = {name="vampirk", type="double" } --吸血 
 
Proto4z.register(1011,"DictItem") 
Proto4z.DictItem = {} --道具字典 
Proto4z.DictItem.__protoID = 1011 
Proto4z.DictItem.__protoName = "DictItem" 
Proto4z.DictItem[1] = {name="id", type="ui32" }  
Proto4z.DictItem[2] = {name="primitiveType", type="ui16" } --主类型 
Proto4z.DictItem[3] = {name="subType", type="ui16" } --子类型 
Proto4z.DictItem[4] = {name="visible", type="ui16" } --是否可见 
Proto4z.DictItem[5] = {name="stacks", type="ui16" } --可堆叠个数,0和1都是1次 
Proto4z.DictItem[6] = {name="fightEffectID", type="ui32" } --战斗属性效果,装备后生效 
Proto4z.DictItem[7] = {name="autoUse", type="ui16" } --0 不可使用, 1 可使用, 2 获得后自动使用 
Proto4z.DictItem[8] = {name="dropID", type="ui32" } --DictRafflePool中的id, 使用后销毁本道具并根据配置进行道具抽取 
Proto4z.DictItem[9] = {name="vocationLimit", type="ui16" } --限制职业类型, 装备类型 
Proto4z.DictItem[10] = {name="levelLimit", type="i32" } --限制职业最小等级, 装备类型 
Proto4z.DictItem[11] = {name="desc", type="string" }  
 
Proto4z.register(1012,"ItemInfo") 
Proto4z.ItemInfo = {} --道具字典 
Proto4z.ItemInfo.__protoID = 1012 
Proto4z.ItemInfo.__protoName = "ItemInfo" 
Proto4z.ItemInfo[1] = {name="stacks", type="ui16" } --可堆叠个数,0和1都是1次 
 
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
