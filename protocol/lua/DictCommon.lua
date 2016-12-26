 
Proto4z.register(10000,"DictGlobal") 
Proto4z.DictGlobal = {} --全局配置 
Proto4z.DictGlobal.__protoID = 10000 
Proto4z.DictGlobal.__protoName = "DictGlobal" 
Proto4z.DictGlobal[1] = {name="id", type="ui64" }  
Proto4z.DictGlobal[2] = {name="val", type="ui64" } --整数 
Proto4z.DictGlobal[3] = {name="valFloat", type="double" } --浮点数 
Proto4z.DictGlobal[4] = {name="combo", type="string" } --字符串 
Proto4z.DictGlobal[5] = {name="desc", type="string" }  
 
Proto4z.register(10007,"DictReward") 
Proto4z.DictReward = {} --奖品 
Proto4z.DictReward.__protoID = 10007 
Proto4z.DictReward.__protoName = "DictReward" 
Proto4z.DictReward[1] = {name="id", type="ui64" } --奖品ID 
Proto4z.DictReward[2] = {name="count", type="ui64" } --数量 
Proto4z.DictReward[3] = {name="probability", type="double" } --概率[0~1], 0为永远无法随机到 1是100%随机到 
 
Proto4z.DictRewardArray = {}  
Proto4z.DictRewardArray.__protoName = "DictRewardArray" 
Proto4z.DictRewardArray.__protoDesc = "array" 
Proto4z.DictRewardArray.__protoTypeV = "DictReward" 
 
Proto4z.register(10008,"DictDrop") 
Proto4z.DictDrop = {} --道具抽奖,道具掉落 
Proto4z.DictDrop.__protoID = 10008 
Proto4z.DictDrop.__protoName = "DictDrop" 
Proto4z.DictDrop[1] = {name="id", type="ui64" }  
Proto4z.DictDrop[2] = {name="dropType", type="ui64" } --0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到 
Proto4z.DictDrop[3] = {name="rewards", type="DictRewardArray" } --奖池 
Proto4z.DictDrop[4] = {name="rewardsString", type="string" } --奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式 
 
Proto4z.register(10003,"DictItem") 
Proto4z.DictItem = {} --道具字典 
Proto4z.DictItem.__protoID = 10003 
Proto4z.DictItem.__protoName = "DictItem" 
Proto4z.DictItem[1] = {name="id", type="ui64" }  
Proto4z.DictItem[2] = {name="visible", type="ui16" } --是否可见 
Proto4z.DictItem[3] = {name="icon", type="ui16" }  
Proto4z.DictItem[4] = {name="stacks", type="ui16" } --可堆叠个数,0和1都是1次 
Proto4z.DictItem[5] = {name="autoUse", type="ui16" } --0 不可使用, 1 可使用, 2 获得后自动使用 
Proto4z.DictItem[6] = {name="dropID", type="ui64" }  
Proto4z.DictItem[7] = {name="propID", type="ui64" }  
Proto4z.DictItem[8] = {name="vocationLimit", type="ui16" } --限制职业类型, 装备类型 
Proto4z.DictItem[9] = {name="levelLimit", type="double" } --限制职业最小等级, 装备类型 
Proto4z.DictItem[10] = {name="desc", type="string" }  
 
Proto4z.register(10004,"DictProp") 
Proto4z.DictProp = {}  
Proto4z.DictProp.__protoID = 10004 
Proto4z.DictProp.__protoName = "DictProp" 
Proto4z.DictProp[1] = {name="id", type="ui64" }  
Proto4z.DictProp[2] = {name="hp", type="double" } --血量值 
Proto4z.DictProp[3] = {name="hpRegen", type="double" } --每秒血量值恢复 
Proto4z.DictProp[4] = {name="attack", type="double" } --伤害 
Proto4z.DictProp[5] = {name="defense", type="double" } --防御 
Proto4z.DictProp[6] = {name="crit", type="double" } --暴击 
Proto4z.DictProp[7] = {name="toughness", type="double" } --韧性 
Proto4z.DictProp[8] = {name="moveSpeed", type="double" } --移动速度 
Proto4z.DictProp[9] = {name="attackSpeed", type="double" } --攻击速度 
Proto4z.DictProp[10] = {name="vampirk", type="double" } --吸血 
 
Proto4z.DictPropArray = {}  
Proto4z.DictPropArray.__protoName = "DictPropArray" 
Proto4z.DictPropArray.__protoDesc = "array" 
Proto4z.DictPropArray.__protoTypeV = "DictProp" 
 
Proto4z.DictPropMap = {}  
Proto4z.DictPropMap.__protoName = "DictPropMap" 
Proto4z.DictPropMap.__protoDesc = "map" 
Proto4z.DictPropMap.__protoTypeK = "ui64" 
Proto4z.DictPropMap.__protoTypeV = "DictProp" 
 
Proto4z.register(10005,"DictSceneUpLevel") 
Proto4z.DictSceneUpLevel = {}  
Proto4z.DictSceneUpLevel.__protoID = 10005 
Proto4z.DictSceneUpLevel.__protoName = "DictSceneUpLevel" 
Proto4z.DictSceneUpLevel[1] = {name="id", type="ui64" }  
Proto4z.DictSceneUpLevel[2] = {name="nextID", type="ui64" } --下一等级的ID 
Proto4z.DictSceneUpLevel[3] = {name="propID", type="ui64" } --对应的prop数值 
Proto4z.DictSceneUpLevel[4] = {name="upExp", type="double" } --升级所需经验 
 
Proto4z.DictSceneUpLevelArray = {}  
Proto4z.DictSceneUpLevelArray.__protoName = "DictSceneUpLevelArray" 
Proto4z.DictSceneUpLevelArray.__protoDesc = "array" 
Proto4z.DictSceneUpLevelArray.__protoTypeV = "DictSceneUpLevel" 
 
Proto4z.DictSceneUpLevelMap = {}  
Proto4z.DictSceneUpLevelMap.__protoName = "DictSceneUpLevelMap" 
Proto4z.DictSceneUpLevelMap.__protoDesc = "map" 
Proto4z.DictSceneUpLevelMap.__protoTypeK = "ui64" 
Proto4z.DictSceneUpLevelMap.__protoTypeV = "DictSceneUpLevel" 
 
Proto4z.register(10006,"DictModel") 
Proto4z.DictModel = {}  
Proto4z.DictModel.__protoID = 10006 
Proto4z.DictModel.__protoName = "DictModel" 
Proto4z.DictModel[1] = {name="eid", type="ui64" }  
Proto4z.DictModel[2] = {name="modelID", type="ui64" }  
Proto4z.DictModel[3] = {name="modelName", type="string" }  
Proto4z.DictModel[4] = {name="avatarID", type="ui64" }  
Proto4z.DictModel[5] = {name="avatarName", type="string" }  
Proto4z.DictModel[6] = {name="iconID", type="ui64" } --头像 
Proto4z.DictModel[7] = {name="level", type="double" } --等级 
Proto4z.DictModel[8] = {name="exp", type="double" } --经验 
Proto4z.DictModel[9] = {name="gold", type="double" } --金币 
Proto4z.DictModel[10] = {name="camp", type="ui16" }  
Proto4z.DictModel[11] = {name="etype", type="ui16" }  
Proto4z.DictModel[12] = {name="state", type="ui16" }  
 
Proto4z.DictModelArray = {}  
Proto4z.DictModelArray.__protoName = "DictModelArray" 
Proto4z.DictModelArray.__protoDesc = "array" 
Proto4z.DictModelArray.__protoTypeV = "DictModel" 
 
Proto4z.DictModelMap = {}  
Proto4z.DictModelMap.__protoName = "DictModelMap" 
Proto4z.DictModelMap.__protoDesc = "map" 
Proto4z.DictModelMap.__protoTypeK = "ui64" 
Proto4z.DictModelMap.__protoTypeV = "DictModel" 
