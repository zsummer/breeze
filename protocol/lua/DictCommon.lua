 
Proto4z.DictArrayValue = {} --通用Value数组 
Proto4z.DictArrayValue.__protoName = "DictArrayValue" 
Proto4z.DictArrayValue.__protoDesc = "array" 
Proto4z.DictArrayValue.__protoTypeV = "double" 
 
Proto4z.DictArrayKey = {} --通用KEY数组 
Proto4z.DictArrayKey.__protoName = "DictArrayKey" 
Proto4z.DictArrayKey.__protoDesc = "array" 
Proto4z.DictArrayKey.__protoTypeV = "ui64" 
 
Proto4z.DictMapKeyValue = {} --通用Key value 
Proto4z.DictMapKeyValue.__protoName = "DictMapKeyValue" 
Proto4z.DictMapKeyValue.__protoDesc = "map" 
Proto4z.DictMapKeyValue.__protoTypeK = "ui64" 
Proto4z.DictMapKeyValue.__protoTypeV = "double" 
 
Proto4z.register(10000,"DictPairValue") 
Proto4z.DictPairValue = {}  
Proto4z.DictPairValue.__protoID = 10000 
Proto4z.DictPairValue.__protoName = "DictPairValue" 
Proto4z.DictPairValue[1] = {name="val1", type="double" }  
Proto4z.DictPairValue[2] = {name="val2", type="double" }  
 
Proto4z.DictMapPairValue = {}  
Proto4z.DictMapPairValue.__protoName = "DictMapPairValue" 
Proto4z.DictMapPairValue.__protoDesc = "map" 
Proto4z.DictMapPairValue.__protoTypeK = "ui64" 
Proto4z.DictMapPairValue.__protoTypeV = "DictPairValue" 
 
Proto4z.DictArrayPairValue = {}  
Proto4z.DictArrayPairValue.__protoName = "DictArrayPairValue" 
Proto4z.DictArrayPairValue.__protoDesc = "array" 
Proto4z.DictArrayPairValue.__protoTypeV = "DictPairValue" 
 
Proto4z.register(10001,"DictGlobal") 
Proto4z.DictGlobal = {} --全局配置 
Proto4z.DictGlobal.__protoID = 10001 
Proto4z.DictGlobal.__protoName = "DictGlobal" 
Proto4z.DictGlobal[1] = {name="id", type="ui64" }  
Proto4z.DictGlobal[2] = {name="val", type="ui64" } --整数 
Proto4z.DictGlobal[3] = {name="valFloat", type="double" } --浮点数 
Proto4z.DictGlobal[4] = {name="combo", type="string" } --字符串 
Proto4z.DictGlobal[5] = {name="desc", type="string" }  
 
Proto4z.DictGlobalArray = {}  
Proto4z.DictGlobalArray.__protoName = "DictGlobalArray" 
Proto4z.DictGlobalArray.__protoDesc = "array" 
Proto4z.DictGlobalArray.__protoTypeV = "DictGlobal" 
 
Proto4z.DictGlobalMap = {}  
Proto4z.DictGlobalMap.__protoName = "DictGlobalMap" 
Proto4z.DictGlobalMap.__protoDesc = "map" 
Proto4z.DictGlobalMap.__protoTypeK = "ui64" 
Proto4z.DictGlobalMap.__protoTypeV = "DictGlobal" 
 
Proto4z.register(10002,"DictDrop") 
Proto4z.DictDrop = {} --道具抽奖,道具掉落 
Proto4z.DictDrop.__protoID = 10002 
Proto4z.DictDrop.__protoName = "DictDrop" 
Proto4z.DictDrop[1] = {name="id", type="ui64" }  
Proto4z.DictDrop[2] = {name="dropType", type="ui16" } --0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到 
Proto4z.DictDrop[3] = {name="rewards", type="DictMapPairValue" } --奖池 
Proto4z.DictDrop[4] = {name="rewardsText", type="string" } --奖池 格式为 id|count|prob,id|count|prob  
Proto4z.DictDrop[5] = {name="desc", type="string" }  
 
Proto4z.register(10003,"DictItem") 
Proto4z.DictItem = {} --道具字典 
Proto4z.DictItem.__protoID = 10003 
Proto4z.DictItem.__protoName = "DictItem" 
Proto4z.DictItem[1] = {name="id", type="ui64" }  
Proto4z.DictItem[2] = {name="icon", type="ui16" }  
Proto4z.DictItem[3] = {name="autoUse", type="ui16" } --0 手动, 其他 自动使用 
Proto4z.DictItem[4] = {name="stacks", type="double" } --可堆叠个数,0和1都是1次 
Proto4z.DictItem[5] = {name="costItems", type="DictMapKeyValue" } --使用该道具需要消耗的其他道具 
Proto4z.DictItem[6] = {name="costItemsText", type="DictMapKeyValue" } --使用该道具需要消耗的其他道具 
Proto4z.DictItem[7] = {name="dropID", type="ui64" } --使用该道具后会产生掉落效果 0为无效 
Proto4z.DictItem[8] = {name="propID", type="ui64" } --装备该道具带来的属性加成 
Proto4z.DictItem[9] = {name="skills", type="DictArrayKey" } --装备该道具带来的可用技能 
Proto4z.DictItem[10] = {name="skillsText", type="string" } --装备该道具带来的可用技能 格式id,id,id  
Proto4z.DictItem[11] = {name="buffs", type="DictArrayKey" } --装备该道具带来的可用buff 
Proto4z.DictItem[12] = {name="buffsText", type="string" } --装备该道具带来的可用buff 格式id,id,id 
Proto4z.DictItem[13] = {name="visible", type="ui16" } --是否可见 
Proto4z.DictItem[14] = {name="desc", type="string" }  
 
Proto4z.DictItemArray = {}  
Proto4z.DictItemArray.__protoName = "DictItemArray" 
Proto4z.DictItemArray.__protoDesc = "array" 
Proto4z.DictItemArray.__protoTypeV = "DictItem" 
 
Proto4z.DictItemMap = {}  
Proto4z.DictItemMap.__protoName = "DictItemMap" 
Proto4z.DictItemMap.__protoDesc = "map" 
Proto4z.DictItemMap.__protoTypeK = "ui64" 
Proto4z.DictItemMap.__protoTypeV = "DictItem" 
