 
Proto4z.SCENE_TYPE_NONE = 0--无效 
Proto4z.SCENE_TYPE_HOME = 1--主城 
Proto4z.SCENE_TYPE_SOME_INSTANCING = 2--一些副本 
Proto4z.SCENE_TYPE_ARENA = 3--竞技场 
Proto4z.SCENE_TYPE_GUILD = 4--公会 
 
Proto4z.SCENE_STATUS_NONE = 0--不存在 
Proto4z.SCENE_STATUS_MATCHING = 1--正在匹配 
Proto4z.SCENE_STATUS_WAITING = 2--匹配成功,等待玩家进入 
Proto4z.SCENE_STATUS_INSTANCING = 3--场景中 
 
Proto4z.register(10000,"SceneInfo") 
Proto4z.SceneInfo = {} --场景信息 
Proto4z.SceneInfo.__protoID = 10000 
Proto4z.SceneInfo.__protoName = "SceneInfo" 
Proto4z.SceneInfo[1] = {name="type", type="ui16" } --类型 
Proto4z.SceneInfo[2] = {name="status", type="ui16" } --状态 
Proto4z.SceneInfo[3] = {name="host", type="string" } --服务器host 
Proto4z.SceneInfo[4] = {name="port", type="ui16" } --服务器port 
Proto4z.SceneInfo[5] = {name="spaceID", type="ui32" } --空间(场景,房间,战场,INSTANCING ID)的实例ID 
Proto4z.SceneInfo[6] = {name="token", type="SessionToken" } --令牌 
Proto4z.SceneInfo[7] = {name="isActive", type="ui8" } --当前活跃场景, 用于场景切换过渡,或者同时多个场景存在的情况 
 
Proto4z.SceneInfoArray = {}  
Proto4z.SceneInfoArray.__protoName = "SceneInfoArray" 
Proto4z.SceneInfoArray.__protoDesc = "array" 
Proto4z.SceneInfoArray.__protoTypeV = "SceneInfo" 
 
Proto4z.ESTATE_FREEZING = 0--冻结, 不能移动,不能操作, 100%免伤 
Proto4z.ESTATE_ACTIVE = 1--活跃状态 
Proto4z.ESTATE_PRE_DIED = 2--进入死亡流程 
Proto4z.ESTATE_DIED = 3--死亡状态 
 
Proto4z.ETYPE_INVALID = 0 
Proto4z.ETYPE_AVATAR = 1 
Proto4z.ETYPE_AI = 2 
Proto4z.ETYPE_FLIGHT = 3--飞行道具 
 
Proto4z.ECOLOR_INVALID = 0--红方 
Proto4z.ECOLOR_RED = 1--红方 
Proto4z.ECOLOR_BLUE = 2--蓝方 
Proto4z.ECOLOR_NEUTRAL = 1000--[0~ECOLOR_NEUTRAL)阵营相互敌对, [ECOLOR_NEUTRAL~)中立温和阵营 
 
Proto4z.MACTION_IDLE = 0--空闲 
Proto4z.MACTION_FACE = 1--朝向 
Proto4z.MACTION_FOLLOW = 2--跟随 
Proto4z.MACTION_PATH = 3--路径 
 
Proto4z.SEARCH_DISTANCE = 1--org 半径 
Proto4z.SEARCH_SEACTOR = 2--org 扇形 
Proto4z.SEARCH_RECT = 3--org 矩形 
 
Proto4z.SEARCH_TARGET_SELF = 1--自身, 玩家或者AI 
Proto4z.SEARCH_TARGET_AVATAR = 2--施法者, 玩家或者AI 
Proto4z.SEARCH_TARGET_AI = 3--施法者, 玩家或者AI 
Proto4z.SEARCH_TARGET_BARRIER = 4--障碍 
Proto4z.SEARCH_TARGET_FLIGHT = 5--飞行道具 
Proto4z.SEARCH_TARGET_ENEMY = 6--敌人 
Proto4z.SEARCH_TARGET_FRIEND = 7--全体友方 
Proto4z.SEARCH_TARGET_NEUTRAL = 8--中立 
 
Proto4z.SKILL_NORMAL_ATTACK = 1--普通攻击 
Proto4z.SKILL_AUTO = 2--被动技能 
Proto4z.SKILL_CAN_BREAK = 3--可被中断 
Proto4z.SKILL_CAN_MOVE = 4--可移动 
Proto4z.SKILL_PHYSICAL = 5--物理攻击 
Proto4z.SKILL_MAGIC = 6--魔法攻击 
Proto4z.SKILL_HARM = 7--进行伤害计算 
Proto4z.SKILL_BREAK_SELF_MOVE = 8--打断自己移动 
Proto4z.SKILL_BREAK_SELF_SKILL = 9--打断自己的技能 
Proto4z.SKILL_BREAK_TARGET_MOVE = 10--打断目标移动 
Proto4z.SKILL_BREAK_TARGET_SKILL = 11--打断目标技能 
Proto4z.SKILL_BREAK_TARGET_DEBUFF = 12--驱散目标减益BUFF 
Proto4z.SKILL_BREAK_TARGET_BUFF = 13--驱散目标增益BUFF 
 
Proto4z.BUFF_HALO = 1--组合类型: 光环 
Proto4z.BUFF_BUFF = 2--组合类型: 增益buff 
Proto4z.BUFF_DEBUFF = 3--组合类型: 减益BUFF 
Proto4z.BUFF_HIDE = 4--组合类型: 客户端不表现 
Proto4z.BUFF_SNEAK = 5--组合类型: 潜行 不会被非己方阵营的任何AOE技能搜索到 
Proto4z.BUFF_HOLD_MOVE = 15--控制: 禁止移动 
Proto4z.BUFF_REVERSE_MOVE = 16--控制: 移动反向 
Proto4z.BUFF_SILENCE = 17--控制: 沉默所有技能 
Proto4z.BUFF_SILENCE_WITHOUT_NORMAL = 18--控制: 沉默非普通攻击 
Proto4z.BUFF_SILENCE_PHYSICAL = 19--控制: 沉默物理攻击 
Proto4z.BUFF_SILENCE_MAGIC = 20--控制: 沉默魔法攻击 
Proto4z.BUFF_IMMUNE_MOVE = 25--免疫: 免疫被控 移动禁止 
Proto4z.BUFF_IMMUNE_SILENCE = 26--免疫: 免疫沉默 
Proto4z.BUFF_IMMUNE_DEBUFF = 27--免疫: 免疫DEBUFF 
Proto4z.BUFF_IMMUNE_PHYSICAL = 28--免疫: 物攻免疫 
Proto4z.BUFF_IMMUNE_MAGIC = 29--免疫: 法攻免疫 
Proto4z.BUFF_IMMUNE_BREAK = 30--免疫: 不可被技能驱散 
Proto4z.BUFF_INC_DAMAGE = 35--属性加成: 加增伤率 万分比(除以10000)  value1为基础概率, value2为成长概率  
Proto4z.BUFF_SUB_DAMAGE = 36--属性加成: 减伤率 万分比(除以10000)  value1为基础概率, value2为成长概率  
Proto4z.BUFF_INC_SPEED = 41--属性加成: 加速度  万分比(除以10000) value1为固定速度加成, value2为概率加成 
Proto4z.BUFF_INC_SUCK_BLOOD = 42--属性加成: 吸血率 万分比(除以10000)  value1为基础概率, value2为成长概率  
Proto4z.BUFF_LIGHT_LIFE = 50--持续性触发: 治疗(生命), 点燃(生命)   value1为每秒固定值, value2为每秒恢复/扣除相对于自己最大血量的万分比(除以10000) 
Proto4z.BUFF_LIGHT_RUNSKILL = 51--持续性触发: 触发一个技能,  光环BUFF,   配置:value填写要触发的技能ID, value1为间隔时间 
 
Proto4z.SkillIDArray = {} --技能ID数组 
Proto4z.SkillIDArray.__protoName = "SkillIDArray" 
Proto4z.SkillIDArray.__protoDesc = "array" 
Proto4z.SkillIDArray.__protoTypeV = "ui32" 
 
Proto4z.BuffIDArray = {} --buff ID 数组 
Proto4z.BuffIDArray.__protoName = "BuffIDArray" 
Proto4z.BuffIDArray.__protoDesc = "array" 
Proto4z.BuffIDArray.__protoTypeV = "ui32" 
 
Proto4z.register(10001,"TargetSearch") 
Proto4z.TargetSearch = {}  
Proto4z.TargetSearch.__protoID = 10001 
Proto4z.TargetSearch.__protoName = "TargetSearch" 
Proto4z.TargetSearch[1] = {name="searchType", type="ui16" }  
Proto4z.TargetSearch[2] = {name="targetType", type="ui64" }  
Proto4z.TargetSearch[3] = {name="distance", type="float" } --伤害距离 
Proto4z.TargetSearch[4] = {name="radian", type="float" } --弧度或者宽度 
Proto4z.TargetSearch[5] = {name="offsetX", type="float" } --坐标偏移量 
Proto4z.TargetSearch[6] = {name="offsetY", type="float" } --坐标偏移量 
Proto4z.TargetSearch[7] = {name="targetMaxCount", type="ui32" } --最大目标数 
 
Proto4z.register(10002,"TargetAddSkillBuff") 
Proto4z.TargetAddSkillBuff = {} --目标上技能和buff 
Proto4z.TargetAddSkillBuff.__protoID = 10002 
Proto4z.TargetAddSkillBuff.__protoName = "TargetAddSkillBuff" 
Proto4z.TargetAddSkillBuff[1] = {name="search", type="TargetSearch" }  
Proto4z.TargetAddSkillBuff[2] = {name="skills", type="SkillIDArray" }  
Proto4z.TargetAddSkillBuff[3] = {name="buffs", type="BuffIDArray" }  
 
Proto4z.TargetAddSkillBuffArray = {}  
Proto4z.TargetAddSkillBuffArray.__protoName = "TargetAddSkillBuffArray" 
Proto4z.TargetAddSkillBuffArray.__protoDesc = "array" 
Proto4z.TargetAddSkillBuffArray.__protoTypeV = "TargetAddSkillBuff" 
 
Proto4z.register(10003,"HitData") 
Proto4z.HitData = {} --技能 
Proto4z.HitData.__protoID = 10003 
Proto4z.HitData.__protoName = "HitData" 
Proto4z.HitData[1] = {name="act", type="ui16" } --序列 
Proto4z.HitData[2] = {name="rate", type="float" } --概率 
Proto4z.HitData[3] = {name="buffID", type="ui32" }  
Proto4z.HitData[4] = {name="delay", type="ui32" } --序列延迟 
 
Proto4z.HitDataArray = {}  
Proto4z.HitDataArray.__protoName = "HitDataArray" 
Proto4z.HitDataArray.__protoDesc = "array" 
Proto4z.HitDataArray.__protoTypeV = "HitData" 
 
Proto4z.register(10004,"SkillData") 
Proto4z.SkillData = {} --技能 
Proto4z.SkillData.__protoID = 10004 
Proto4z.SkillData.__protoName = "SkillData" 
Proto4z.SkillData[1] = {name="skillID", type="ui32" } --skillID 
Proto4z.SkillData[2] = {name="skillType", type="ui64" } --SKILL_TYPE 
Proto4z.SkillData[3] = {name="cd", type="ui32" }  
Proto4z.SkillData[4] = {name="hitActions", type="HitDataArray" } --动作触发序列 
Proto4z.SkillData[5] = {name="targetAddSkillBuffs", type="TargetAddSkillBuffArray" } --上技能或者buff, 每个动作触发一次 
Proto4z.SkillData[6] = {name="targetDamage", type="TargetSearch" } --触发伤害 
Proto4z.SkillData[7] = {name="teleportDistance", type="float" } --瞬移 
 
Proto4z.register(10005,"BuffData") 
Proto4z.BuffData = {} --buff 
Proto4z.BuffData.__protoID = 10005 
Proto4z.BuffData.__protoName = "BuffData" 
Proto4z.BuffData[1] = {name="buffID", type="ui32" }  
Proto4z.BuffData[2] = {name="piletime", type="ui32" } --最大叠加时间 
Proto4z.BuffData[3] = {name="keepTime", type="ui32" } --保持时间 
Proto4z.BuffData[4] = {name="buffType", type="ui64" } --buff类型 
Proto4z.BuffData[5] = {name="value1", type="i32" } --值1 
Proto4z.BuffData[6] = {name="value2", type="i32" } --值2 
 
Proto4z.HARMTYPE_GENERAL = 0--普通伤害 
Proto4z.HARMTYPE_MISS = 1--闪避 
Proto4z.HARMTYPE_CRITICAL = 2--暴击 
Proto4z.HARMTYPE_HILL = 3--治疗 
 
Proto4z.register(10006,"HarmData") 
Proto4z.HarmData = {} --伤害数据 
Proto4z.HarmData.__protoID = 10006 
Proto4z.HarmData.__protoName = "HarmData" 
Proto4z.HarmData[1] = {name="eid", type="ui32" } --目标eid 
Proto4z.HarmData[2] = {name="harm", type="float" } --如果为正是伤害, 为负则是回血 
Proto4z.HarmData[3] = {name="type", type="ui16" } --伤害类型HARM_TYPE 
 
Proto4z.HarmDataArray = {}  
Proto4z.HarmDataArray.__protoName = "HarmDataArray" 
Proto4z.HarmDataArray.__protoDesc = "array" 
Proto4z.HarmDataArray.__protoTypeV = "HarmData" 
 
Proto4z.register(10007,"SkillInfo") 
Proto4z.SkillInfo = {}  
Proto4z.SkillInfo.__protoID = 10007 
Proto4z.SkillInfo.__protoName = "SkillInfo" 
Proto4z.SkillInfo[1] = {name="skillID", type="ui32" }  
Proto4z.SkillInfo[2] = {name="start", type="ui32" } --start (server)tick 
Proto4z.SkillInfo[3] = {name="lastHitTick", type="ui32" } --lastHitTick 
Proto4z.SkillInfo[4] = {name="seq", type="ui32" } --hit seq 
Proto4z.SkillInfo[5] = {name="dst", type="EPosition" } --目标位置,只有需要用到的这个参数的技能才会读这个字段 
Proto4z.SkillInfo[6] = {name="foe", type="ui32" } --锁定的目标 
Proto4z.SkillInfo[7] = {name="data", type="SkillData" } --配置数据 
 
Proto4z.SkillInfoArray = {}  
Proto4z.SkillInfoArray.__protoName = "SkillInfoArray" 
Proto4z.SkillInfoArray.__protoDesc = "array" 
Proto4z.SkillInfoArray.__protoTypeV = "SkillInfo" 
 
Proto4z.register(10008,"BuffInfo") 
Proto4z.BuffInfo = {}  
Proto4z.BuffInfo.__protoID = 10008 
Proto4z.BuffInfo.__protoName = "BuffInfo" 
Proto4z.BuffInfo[1] = {name="eid", type="ui32" } --施放该buff的entity id 
Proto4z.BuffInfo[2] = {name="skillID", type="ui32" } --如果该buff是被技能触发的 则记录该技能, 被动技能是0 
Proto4z.BuffInfo[3] = {name="buffID", type="ui32" }  
Proto4z.BuffInfo[4] = {name="start", type="ui32" } --start (server)tick 
Proto4z.BuffInfo[5] = {name="lastTrigerTick", type="ui32" } --lastTrigerTick 
Proto4z.BuffInfo[6] = {name="data", type="BuffData" } --配置数据 
 
Proto4z.BuffInfoArray = {}  
Proto4z.BuffInfoArray.__protoName = "BuffInfoArray" 
Proto4z.BuffInfoArray.__protoDesc = "array" 
Proto4z.BuffInfoArray.__protoTypeV = "BuffInfo" 
 
Proto4z.register(10009,"EntityDict") 
Proto4z.EntityDict = {} --字典属性 
Proto4z.EntityDict.__protoID = 10009 
Proto4z.EntityDict.__protoName = "EntityDict" 
Proto4z.EntityDict[1] = {name="serviceID", type="ui64" } --用户ID, 非用户为InvalidServiceID 
Proto4z.EntityDict[2] = {name="base", type="UserBaseInfo" }  
Proto4z.EntityDict[3] = {name="fight", type="DictFightEffect" } --战斗属性 
 
Proto4z.EntityDictArray = {}  
Proto4z.EntityDictArray.__protoName = "EntityDictArray" 
Proto4z.EntityDictArray.__protoDesc = "array" 
Proto4z.EntityDictArray.__protoTypeV = "EntityDict" 
 
Proto4z.register(10010,"EPosition") 
Proto4z.EPosition = {}  
Proto4z.EPosition.__protoID = 10010 
Proto4z.EPosition.__protoName = "EPosition" 
Proto4z.EPosition[1] = {name="x", type="double" }  
Proto4z.EPosition[2] = {name="y", type="double" }  
Proto4z.EPosition[3] = {name="face", type="double" }  
 
Proto4z.EPositions = {}  
Proto4z.EPositions.__protoName = "EPositions" 
Proto4z.EPositions.__protoDesc = "array" 
Proto4z.EPositions.__protoTypeV = "EPosition" 
 
Proto4z.register(10011,"EntityInfo") 
Proto4z.EntityInfo = {} --EntityInfo 
Proto4z.EntityInfo.__protoID = 10011 
Proto4z.EntityInfo.__protoName = "EntityInfo" 
Proto4z.EntityInfo[1] = {name="eid", type="ui32" } --eid 
Proto4z.EntityInfo[2] = {name="color", type="ui16" } --阵营 
Proto4z.EntityInfo[3] = {name="state", type="ui16" } --状态 
Proto4z.EntityInfo[4] = {name="pos", type="EPosition" } --当前坐标 
Proto4z.EntityInfo[5] = {name="moveAction", type="ui16" } --状态 
Proto4z.EntityInfo[6] = {name="movePath", type="EPoints" } --当前的移动路径 
Proto4z.EntityInfo[7] = {name="foe", type="ui32" } --锁定的敌人 
Proto4z.EntityInfo[8] = {name="leader", type="ui32" } --实体的老大, 如果是飞行道具 这个指向施放飞行道具的人 
Proto4z.EntityInfo[9] = {name="follow", type="ui32" } --移动跟随的实体 
Proto4z.EntityInfo[10] = {name="curHP", type="double" } --当前的血量 
 
Proto4z.EntityInfoArray = {}  
Proto4z.EntityInfoArray.__protoName = "EntityInfoArray" 
Proto4z.EntityInfoArray.__protoDesc = "array" 
Proto4z.EntityInfoArray.__protoTypeV = "EntityInfo" 
 
Proto4z.register(10012,"EntityControl") 
Proto4z.EntityControl = {} --EntityControl 
Proto4z.EntityControl.__protoID = 10012 
Proto4z.EntityControl.__protoName = "EntityControl" 
Proto4z.EntityControl[1] = {name="eid", type="ui32" } --eid 
Proto4z.EntityControl[2] = {name="stateChageTick", type="ui32" } --状态改变时间 
Proto4z.EntityControl[3] = {name="extSpeed", type="double" } --扩展速度 
Proto4z.EntityControl[4] = {name="extBeginTick", type="ui32" } --扩展速度的开始时间 
Proto4z.EntityControl[5] = {name="extKeepTick", type="ui32" } --扩展速度的保持时间 
Proto4z.EntityControl[6] = {name="spawnpoint", type="EPosition" } --出生点 
Proto4z.EntityControl[7] = {name="lastPos", type="EPoint" } --上一帧实体坐标, 如果是瞬移 则和pos相同 
Proto4z.EntityControl[8] = {name="skills", type="SkillInfoArray" } --技能数据 
Proto4z.EntityControl[9] = {name="buffs", type="BuffInfoArray" } --BUFF数据, 小标ID对应bufftype 
Proto4z.EntityControl[10] = {name="diedTick", type="ui32" } --实体死亡时间点 -1为永久, 仅飞行道具类有效 
Proto4z.EntityControl[11] = {name="hitTimes", type="i32" } --实体碰撞 -1为永久, 仅飞行道具类有效 
Proto4z.EntityControl[12] = {name="lastMoveTick", type="ui32" } --最后一次移动时间 
Proto4z.EntityControl[13] = {name="lastClientPos", type="EPosition" } --最后一次客户端提交的坐标 
 
Proto4z.EntityControlArray = {}  
Proto4z.EntityControlArray.__protoName = "EntityControlArray" 
Proto4z.EntityControlArray.__protoDesc = "array" 
Proto4z.EntityControlArray.__protoTypeV = "EntityControl" 
 
Proto4z.register(10013,"EntityReport") 
Proto4z.EntityReport = {} --EntityReport 
Proto4z.EntityReport.__protoID = 10013 
Proto4z.EntityReport.__protoName = "EntityReport" 
Proto4z.EntityReport[1] = {name="eid", type="ui32" } --eid 
Proto4z.EntityReport[2] = {name="killCount", type="ui32" } --杀死其他玩家次数 
Proto4z.EntityReport[3] = {name="killTick", type="ui32" } --杀死其他玩家的时间 
Proto4z.EntityReport[4] = {name="diedCount", type="ui32" } --死亡次数 
Proto4z.EntityReport[5] = {name="topMultiKills", type="ui32" } --最高连杀次数 
Proto4z.EntityReport[6] = {name="curMultiKills", type="ui32" } --当前连杀次数 
 
Proto4z.EntityReportArray = {}  
Proto4z.EntityReportArray.__protoName = "EntityReportArray" 
Proto4z.EntityReportArray.__protoDesc = "array" 
Proto4z.EntityReportArray.__protoTypeV = "EntityReport" 
 
Proto4z.register(10014,"EntityFullInfo") 
Proto4z.EntityFullInfo = {} --EntityFullInfo 
Proto4z.EntityFullInfo.__protoID = 10014 
Proto4z.EntityFullInfo.__protoName = "EntityFullInfo" 
Proto4z.EntityFullInfo[1] = {name="dict", type="EntityDict" }  
Proto4z.EntityFullInfo[2] = {name="info", type="EntityInfo" }  
Proto4z.EntityFullInfo[3] = {name="report", type="EntityReport" }  
 
Proto4z.EntityFullInfoArray = {}  
Proto4z.EntityFullInfoArray.__protoName = "EntityFullInfoArray" 
Proto4z.EntityFullInfoArray.__protoDesc = "array" 
Proto4z.EntityFullInfoArray.__protoTypeV = "EntityFullInfo" 
