 
Proto4z.SCENE_NONE = 0--无效 
Proto4z.SCENE_HOME = 1--主城 
Proto4z.SCENE_MELEE = 2--乱斗场 
Proto4z.SCENE_ARENA = 3--竞技场 
Proto4z.SCENE_GUILD = 4--公会 
Proto4z.SCENE_MASTER_INSTANCING = 5--主线副本 
Proto4z.SCENE_BRANCH_INSTANCING = 6--支线副本 
Proto4z.SCENE_MAX = 7--最大类型数值. 扩展类型在该枚举之前插入新类型. 
 
Proto4z.SCENE_STATE_NONE = 0--不存在 
Proto4z.SCENE_STATE_MATCHING = 1--匹配中 
Proto4z.SCENE_STATE_CHOISE = 2--选择英雄 
Proto4z.SCENE_STATE_ALLOCATE = 3--服务器分配场景中 
Proto4z.SCENE_STATE_WAIT = 4--等待玩家加入战场 
Proto4z.SCENE_STATE_ACTIVE = 5--战斗中 
 
Proto4z.register(2000,"SceneGroupAvatarInfo") 
Proto4z.SceneGroupAvatarInfo = {}  
Proto4z.SceneGroupAvatarInfo.__protoID = 2000 
Proto4z.SceneGroupAvatarInfo.__protoName = "SceneGroupAvatarInfo" 
Proto4z.SceneGroupAvatarInfo[1] = {name="areaID", type="ui64" } --考虑混服情况,必须指定该玩家来自哪个当前区 
Proto4z.SceneGroupAvatarInfo[2] = {name="modelID", type="ui64" } --模型ID 
Proto4z.SceneGroupAvatarInfo[3] = {name="equips", type="DictArrayKey" } --额外装备 
Proto4z.SceneGroupAvatarInfo[4] = {name="avatarID", type="ui64" }  
Proto4z.SceneGroupAvatarInfo[5] = {name="avatarName", type="string" }  
Proto4z.SceneGroupAvatarInfo[6] = {name="rankScore", type="double" } --天梯分数 
Proto4z.SceneGroupAvatarInfo[7] = {name="powerType", type="ui16" } --组队权限: 0普通,1leader,2master 
Proto4z.SceneGroupAvatarInfo[8] = {name="token", type="string" } --scene服务器的口令, 该字段在广播给客户端时需要清空非自己所属的token,否则将会造成token公开. 
 
Proto4z.SceneGroupAvatarInfoArray = {}  
Proto4z.SceneGroupAvatarInfoArray.__protoName = "SceneGroupAvatarInfoArray" 
Proto4z.SceneGroupAvatarInfoArray.__protoDesc = "array" 
Proto4z.SceneGroupAvatarInfoArray.__protoTypeV = "SceneGroupAvatarInfo" 
 
Proto4z.SceneGroupAvatarInfoMap = {}  
Proto4z.SceneGroupAvatarInfoMap.__protoName = "SceneGroupAvatarInfoMap" 
Proto4z.SceneGroupAvatarInfoMap.__protoDesc = "map" 
Proto4z.SceneGroupAvatarInfoMap.__protoTypeK = "ui64" 
Proto4z.SceneGroupAvatarInfoMap.__protoTypeV = "SceneGroupAvatarInfo" 
 
Proto4z.register(2001,"SceneGroupInfo") 
Proto4z.SceneGroupInfo = {} --编队数据 
Proto4z.SceneGroupInfo.__protoID = 2001 
Proto4z.SceneGroupInfo.__protoName = "SceneGroupInfo" 
Proto4z.SceneGroupInfo[1] = {name="groupID", type="ui64" }  
Proto4z.SceneGroupInfo[2] = {name="sceneType", type="ui16" } --场景类型 
Proto4z.SceneGroupInfo[3] = {name="sceneState", type="ui16" } --状态 
Proto4z.SceneGroupInfo[4] = {name="mapID", type="ui64" }  
Proto4z.SceneGroupInfo[5] = {name="lineID", type="ui64" } --分线ID 
Proto4z.SceneGroupInfo[6] = {name="sceneID", type="ui64" } --场景实例ID 
Proto4z.SceneGroupInfo[7] = {name="host", type="string" } --服务器host 
Proto4z.SceneGroupInfo[8] = {name="port", type="ui16" } --服务器port 
Proto4z.SceneGroupInfo[9] = {name="members", type="SceneGroupAvatarInfoMap" } --队友数据 
Proto4z.SceneGroupInfo[10] = {name="invitees", type="ServiceIDMap" } --邀请列表, 如果需要丰富该功能可扩展类型信息 
 
Proto4z.SceneGroupInfoArray = {}  
Proto4z.SceneGroupInfoArray.__protoName = "SceneGroupInfoArray" 
Proto4z.SceneGroupInfoArray.__protoDesc = "array" 
Proto4z.SceneGroupInfoArray.__protoTypeV = "SceneGroupInfo" 
 
Proto4z.SceneGroupInfoMap = {}  
Proto4z.SceneGroupInfoMap.__protoName = "SceneGroupInfoMap" 
Proto4z.SceneGroupInfoMap.__protoDesc = "map" 
Proto4z.SceneGroupInfoMap.__protoTypeK = "ui64" 
Proto4z.SceneGroupInfoMap.__protoTypeV = "SceneGroupInfo" 
 
Proto4z.EntityIDArray = {}  
Proto4z.EntityIDArray.__protoName = "EntityIDArray" 
Proto4z.EntityIDArray.__protoDesc = "array" 
Proto4z.EntityIDArray.__protoTypeV = "ui64" 
 
Proto4z.register(2002,"EPosition") 
Proto4z.EPosition = {}  
Proto4z.EPosition.__protoID = 2002 
Proto4z.EPosition.__protoName = "EPosition" 
Proto4z.EPosition[1] = {name="x", type="double" }  
Proto4z.EPosition[2] = {name="y", type="double" }  
 
Proto4z.EPositionArray = {}  
Proto4z.EPositionArray.__protoName = "EPositionArray" 
Proto4z.EPositionArray.__protoDesc = "array" 
Proto4z.EPositionArray.__protoTypeV = "EPosition" 
 
Proto4z.SkillIDArray = {} --技能ID数组 
Proto4z.SkillIDArray.__protoName = "SkillIDArray" 
Proto4z.SkillIDArray.__protoDesc = "array" 
Proto4z.SkillIDArray.__protoTypeV = "ui64" 
 
Proto4z.BuffIDArray = {} --buff ID 数组 
Proto4z.BuffIDArray.__protoName = "BuffIDArray" 
Proto4z.BuffIDArray.__protoDesc = "array" 
Proto4z.BuffIDArray.__protoTypeV = "ui64" 
 
Proto4z.ENTITY_STATE_NONE = 0--无效 
Proto4z.ENTITY_STATE_FREEZING = 1--冻结, 不可被攻击,不可主动移动,攻击等 
Proto4z.ENTITY_STATE_ACTIVE = 2--活跃状态 
Proto4z.ENTITY_STATE_LIE = 3--跪, 不计死亡次数 
Proto4z.ENTITY_STATE_DIED = 4--死, 记死亡次数 
 
Proto4z.ENTITY_NONE = 0 
Proto4z.ENTITY_PLAYER = 1 
Proto4z.ENTITY_AI = 2 
Proto4z.ENTITY_FLIGHT = 3--飞行道具 
 
Proto4z.ENTITY_CAMP_NONE = 0 
Proto4z.ENTITY_CAMP_RED = 1--红方 
Proto4z.ENTITY_CAMP_BLUE = 2--蓝方 
Proto4z.ENTITY_CAMP_NEUTRAL = 1000--[0~ENTITY_CAMP_NEUTRAL)阵营相互敌对, [ENTITY_CAMP_NEUTRAL~)中立温和阵营 
 
Proto4z.MOVE_ACTION_IDLE = 0--空闲 
Proto4z.MOVE_ACTION_FOLLOW = 1--跟随 
Proto4z.MOVE_ACTION_PATH = 2--路径 
Proto4z.MOVE_ACTION_PASV_PATH = 3--不可取消, 直线移动一次. 
Proto4z.MOVE_ACTION_FORCE_PATH = 4--不可取消&穿越地形, 直线移动一次 
 
Proto4z.SCENE_EVENT_LIE = 0 
Proto4z.SCENE_EVENT_DIED = 1 
Proto4z.SCENE_EVENT_FREEZE = 2 
Proto4z.SCENE_EVENT_REBIRTH = 3 
Proto4z.SCENE_EVENT_HARM_ATTACK = 4 
Proto4z.SCENE_EVENT_HARM_HILL = 5 
Proto4z.SCENE_EVENT_HARM_MISS = 6 
Proto4z.SCENE_EVENT_HARM_CRITICAL = 7 
 
Proto4z.register(2003,"SceneEventInfo") 
Proto4z.SceneEventInfo = {} --伤害数据 
Proto4z.SceneEventInfo.__protoID = 2003 
Proto4z.SceneEventInfo.__protoName = "SceneEventInfo" 
Proto4z.SceneEventInfo[1] = {name="src", type="ui64" } --eid 
Proto4z.SceneEventInfo[2] = {name="dst", type="ui64" } --eid 
Proto4z.SceneEventInfo[3] = {name="ev", type="ui16" } --事件类型 
Proto4z.SceneEventInfo[4] = {name="val", type="double" } --数值 
Proto4z.SceneEventInfo[5] = {name="mix", type="string" } --数值 
 
Proto4z.SceneEventInfoArray = {}  
Proto4z.SceneEventInfoArray.__protoName = "SceneEventInfoArray" 
Proto4z.SceneEventInfoArray.__protoDesc = "array" 
Proto4z.SceneEventInfoArray.__protoTypeV = "SceneEventInfo" 
 
Proto4z.register(2004,"EntityState") 
Proto4z.EntityState = {} --EntityState 
Proto4z.EntityState.__protoID = 2004 
Proto4z.EntityState.__protoName = "EntityState" 
Proto4z.EntityState[1] = {name="eid", type="ui64" }  
Proto4z.EntityState[2] = {name="avatarID", type="ui64" }  
Proto4z.EntityState[3] = {name="avatarName", type="string" }  
Proto4z.EntityState[4] = {name="modelID", type="ui64" }  
Proto4z.EntityState[5] = {name="camp", type="ui16" } --阵营 
Proto4z.EntityState[6] = {name="groupID", type="ui64" } --组队ID 
Proto4z.EntityState[7] = {name="etype", type="ui16" } --实体类型 
Proto4z.EntityState[8] = {name="state", type="ui16" } --状态 
Proto4z.EntityState[9] = {name="foe", type="ui64" } --锁定的敌人 
Proto4z.EntityState[10] = {name="master", type="ui64" } --如果是飞行道具 这个指向施放飞行道具的人 
Proto4z.EntityState[11] = {name="curHP", type="double" } --当前的血量 
Proto4z.EntityState[12] = {name="maxHP", type="double" } --当前的血量上限 
 
Proto4z.EntityStateArray = {}  
Proto4z.EntityStateArray.__protoName = "EntityStateArray" 
Proto4z.EntityStateArray.__protoDesc = "array" 
Proto4z.EntityStateArray.__protoTypeV = "EntityState" 
 
Proto4z.register(2005,"EntityMove") 
Proto4z.EntityMove = {} --EntityMove 
Proto4z.EntityMove.__protoID = 2005 
Proto4z.EntityMove.__protoName = "EntityMove" 
Proto4z.EntityMove[1] = {name="eid", type="ui64" } --eid 
Proto4z.EntityMove[2] = {name="position", type="EPosition" } --当前坐标 
Proto4z.EntityMove[3] = {name="action", type="ui16" } --移动状态 
Proto4z.EntityMove[4] = {name="realSpeed", type="double" } --实时速度 
Proto4z.EntityMove[5] = {name="expectSpeed", type="double" } --期望速度 
Proto4z.EntityMove[6] = {name="waypoints", type="EPositionArray" } --移动路点 
Proto4z.EntityMove[7] = {name="follow", type="ui64" } --eid 
 
Proto4z.EntityMoveArray = {}  
Proto4z.EntityMoveArray.__protoName = "EntityMoveArray" 
Proto4z.EntityMoveArray.__protoDesc = "array" 
Proto4z.EntityMoveArray.__protoTypeV = "EntityMove" 
 
Proto4z.register(2006,"EntityReport") 
Proto4z.EntityReport = {} --EntityReport 
Proto4z.EntityReport.__protoID = 2006 
Proto4z.EntityReport.__protoName = "EntityReport" 
Proto4z.EntityReport[1] = {name="eid", type="ui64" } --eid 
Proto4z.EntityReport[2] = {name="killOtherCount", type="ui64" } --杀死其他玩家次数 
Proto4z.EntityReport[3] = {name="killOtherTime", type="ui64" } --杀死其他玩家的时间 
Proto4z.EntityReport[4] = {name="diedCount", type="ui64" } --死亡次数 
Proto4z.EntityReport[5] = {name="topMultiKills", type="ui64" } --最高连杀次数 
Proto4z.EntityReport[6] = {name="curMultiKills", type="ui64" } --当前连杀次数 
 
Proto4z.EntityReportArray = {}  
Proto4z.EntityReportArray.__protoName = "EntityReportArray" 
Proto4z.EntityReportArray.__protoDesc = "array" 
Proto4z.EntityReportArray.__protoTypeV = "EntityReport" 
 
Proto4z.register(2007,"EntityControl") 
Proto4z.EntityControl = {} --EntityControl 
Proto4z.EntityControl.__protoID = 2007 
Proto4z.EntityControl.__protoName = "EntityControl" 
Proto4z.EntityControl[1] = {name="eid", type="ui64" }  
Proto4z.EntityControl[2] = {name="agentNo", type="ui64" }  
Proto4z.EntityControl[3] = {name="collision", type="double" }  
Proto4z.EntityControl[4] = {name="stateChageTime", type="double" }  
Proto4z.EntityControl[5] = {name="spawnpoint", type="EPosition" }  
Proto4z.EntityControl[6] = {name="blockMoveCount", type="double" }  
 
Proto4z.EntityControlArray = {}  
Proto4z.EntityControlArray.__protoName = "EntityControlArray" 
Proto4z.EntityControlArray.__protoDesc = "array" 
Proto4z.EntityControlArray.__protoTypeV = "EntityControl" 
 
Proto4z.register(2008,"EntityClientSync") 
Proto4z.EntityClientSync = {} --EntityClientSync 
Proto4z.EntityClientSync.__protoID = 2008 
Proto4z.EntityClientSync.__protoName = "EntityClientSync" 
Proto4z.EntityClientSync[1] = {name="props", type="DictProp" } --战斗属性 
Proto4z.EntityClientSync[2] = {name="state", type="EntityState" }  
Proto4z.EntityClientSync[3] = {name="mv", type="EntityMove" }  
Proto4z.EntityClientSync[4] = {name="report", type="EntityReport" }  
 
Proto4z.EntityClientSyncArray = {}  
Proto4z.EntityClientSyncArray.__protoName = "EntityClientSyncArray" 
Proto4z.EntityClientSyncArray.__protoDesc = "array" 
Proto4z.EntityClientSyncArray.__protoTypeV = "EntityClientSync" 
 
Proto4z.register(2009,"SceneSection") 
Proto4z.SceneSection = {} --场景全景切片数据 
Proto4z.SceneSection.__protoID = 2009 
Proto4z.SceneSection.__protoName = "SceneSection" 
Proto4z.SceneSection[1] = {name="sceneID", type="ui64" }  
Proto4z.SceneSection[2] = {name="sceneType", type="ui16" }  
Proto4z.SceneSection[3] = {name="sceneState", type="ui16" }  
Proto4z.SceneSection[4] = {name="sceneStartTime", type="double" } --服务器战场开始时间 
Proto4z.SceneSection[5] = {name="sceneEndTime", type="double" } --服务器战场结束时间 
Proto4z.SceneSection[6] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.ENTITY_SKILL_NONE = 0--无效 
Proto4z.ENTITY_SKILL_PREFIX = 1--前摇 
Proto4z.ENTITY_SKILL_ACTIVE = 2--执行中 
Proto4z.ENTITY_SKILL_CD = 3--冷却中 
 
Proto4z.register(2010,"EntitySkillInfo") 
Proto4z.EntitySkillInfo = {} --技能 
Proto4z.EntitySkillInfo.__protoID = 2010 
Proto4z.EntitySkillInfo.__protoName = "EntitySkillInfo" 
Proto4z.EntitySkillInfo[1] = {name="skillID", type="ui64" }  
Proto4z.EntitySkillInfo[2] = {name="activeDst", type="EPosition" }  
Proto4z.EntitySkillInfo[3] = {name="activeFoeFirst", type="ui16" }  
Proto4z.EntitySkillInfo[4] = {name="lastActiveTime", type="double" }  
Proto4z.EntitySkillInfo[5] = {name="lastTriggerTime", type="double" }  
Proto4z.EntitySkillInfo[6] = {name="activeState", type="ui16" } --ENTITY_SKILL_STATE 
Proto4z.EntitySkillInfo[7] = {name="activeCount", type="double" }  
Proto4z.EntitySkillInfo[8] = {name="dict", type="DictSkill" }  
 
Proto4z.EntitySkillInfoMap = {} --已装备的SKILL ID, 技能执行数据 
Proto4z.EntitySkillInfoMap.__protoName = "EntitySkillInfoMap" 
Proto4z.EntitySkillInfoMap.__protoDesc = "map" 
Proto4z.EntitySkillInfoMap.__protoTypeK = "ui64" 
Proto4z.EntitySkillInfoMap.__protoTypeV = "EntitySkillInfo" 
 
Proto4z.EntityEquippedSkillMap = {} --已装备的SKILL ID, value保留 
Proto4z.EntityEquippedSkillMap.__protoName = "EntityEquippedSkillMap" 
Proto4z.EntityEquippedSkillMap.__protoDesc = "map" 
Proto4z.EntityEquippedSkillMap.__protoTypeK = "ui64" 
Proto4z.EntityEquippedSkillMap.__protoTypeV = "ui64" 
 
Proto4z.register(2011,"EntityBuffInfo") 
Proto4z.EntityBuffInfo = {} --BUFF 
Proto4z.EntityBuffInfo.__protoID = 2011 
Proto4z.EntityBuffInfo.__protoName = "EntityBuffInfo" 
Proto4z.EntityBuffInfo[1] = {name="buffID", type="ui64" }  
Proto4z.EntityBuffInfo[2] = {name="activeOrg", type="EPosition" }  
Proto4z.EntityBuffInfo[3] = {name="activeOrgEID", type="ui64" }  
Proto4z.EntityBuffInfo[4] = {name="activeDst", type="EPosition" }  
Proto4z.EntityBuffInfo[5] = {name="activeDstEID", type="ui64" }  
Proto4z.EntityBuffInfo[6] = {name="lastActiveTime", type="double" }  
Proto4z.EntityBuffInfo[7] = {name="lastTriggerTime", type="double" }  
Proto4z.EntityBuffInfo[8] = {name="activeCount", type="double" }  
Proto4z.EntityBuffInfo[9] = {name="dict", type="DictBuff" }  
 
Proto4z.EntityBuffInfoMap = {} --附加到entity上的buff 
Proto4z.EntityBuffInfoMap.__protoName = "EntityBuffInfoMap" 
Proto4z.EntityBuffInfoMap.__protoDesc = "map" 
Proto4z.EntityBuffInfoMap.__protoTypeK = "ui64" 
Proto4z.EntityBuffInfoMap.__protoTypeV = "EntityBuffInfo" 
 
Proto4z.register(2012,"EntitySkillSystem") 
Proto4z.EntitySkillSystem = {} --EntitySkillSystem 
Proto4z.EntitySkillSystem.__protoID = 2012 
Proto4z.EntitySkillSystem.__protoName = "EntitySkillSystem" 
Proto4z.EntitySkillSystem[1] = {name="eid", type="ui64" }  
Proto4z.EntitySkillSystem[2] = {name="activeSkills", type="EntitySkillInfoMap" }  
Proto4z.EntitySkillSystem[3] = {name="activeBuffs", type="EntityBuffInfoMap" }  
Proto4z.EntitySkillSystem[4] = {name="dictEquippedSkills", type="EntityEquippedSkillMap" }  
Proto4z.EntitySkillSystem[5] = {name="combating", type="ui16" } --战斗中 
Proto4z.EntitySkillSystem[6] = {name="readySkillID", type="ui64" }  
Proto4z.EntitySkillSystem[7] = {name="normalSkillID", type="ui64" }  
Proto4z.EntitySkillSystem[8] = {name="breakoffAttackTime", type="double" }  
 
Proto4z.EntitySkillSystemArray = {}  
Proto4z.EntitySkillSystemArray.__protoName = "EntitySkillSystemArray" 
Proto4z.EntitySkillSystemArray.__protoDesc = "array" 
Proto4z.EntitySkillSystemArray.__protoTypeV = "EntitySkillSystem" 
