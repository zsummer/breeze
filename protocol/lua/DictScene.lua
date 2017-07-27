 
Proto4z.register(11000,"DictProp") 
Proto4z.DictProp = {} --战斗属性 
Proto4z.DictProp.__protoID = 11000 
Proto4z.DictProp.__protoName = "DictProp" 
Proto4z.DictProp[1] = {name="id", type="ui64" }  
Proto4z.DictProp[2] = {name="hp", type="double" } --血量值 
Proto4z.DictProp[3] = {name="attack", type="double" } --伤害 
Proto4z.DictProp[4] = {name="moveSpeed", type="double" } --移动速度 
Proto4z.DictProp[5] = {name="attackQuick", type="double" } --攻击加速 
Proto4z.DictProp[6] = {name="desc", type="string" }  
 
Proto4z.DictPropArray = {}  
Proto4z.DictPropArray.__protoName = "DictPropArray" 
Proto4z.DictPropArray.__protoDesc = "array" 
Proto4z.DictPropArray.__protoTypeV = "DictProp" 
 
Proto4z.DictPropMap = {}  
Proto4z.DictPropMap.__protoName = "DictPropMap" 
Proto4z.DictPropMap.__protoDesc = "map" 
Proto4z.DictPropMap.__protoTypeK = "ui64" 
Proto4z.DictPropMap.__protoTypeV = "DictProp" 
 
Proto4z.FILTER_NONE = 1--全部 
Proto4z.FILTER_SELF = 2--自己 
Proto4z.FILTER_OTHER_FRIEND = 3--友方阵营 
Proto4z.FILTER_ENEMY_CAMP = 4--敌方阵营 
Proto4z.FILTER_NEUTRAL_CAMP = 5--中立阵营 
 
Proto4z.register(11001,"AOESearch") 
Proto4z.AOESearch = {}  
Proto4z.AOESearch.__protoID = 11001 
Proto4z.AOESearch.__protoName = "AOESearch" 
Proto4z.AOESearch[1] = {name="id", type="ui64" }  
Proto4z.AOESearch[2] = {name="etype", type="ui16" } --实体类型, 玩家/AI 或者是NONE忽略该选项 
Proto4z.AOESearch[3] = {name="filter", type="ui64" }  
Proto4z.AOESearch[4] = {name="filterText", type="string" }  
Proto4z.AOESearch[5] = {name="isRect", type="ui16" } --0扇形, 其他矩形 
Proto4z.AOESearch[6] = {name="value1", type="double" } --伤害距离 
Proto4z.AOESearch[7] = {name="value2", type="double" } --弧度或者远端宽度 
Proto4z.AOESearch[8] = {name="value3", type="double" } --忽略或者近端宽度 
Proto4z.AOESearch[9] = {name="compensate", type="double" } --距离补偿, 一般填负数 规避视觉上的灯下黑问题 
Proto4z.AOESearch[10] = {name="clip", type="double" } --可以裁剪扇形的尖角, 圆环等 矩形忽略该参数 
Proto4z.AOESearch[11] = {name="limitEntitys", type="ui64" } --最大目标数, 距离优先 
 
Proto4z.BUFF_HALO = 1--描述性类型: 光环 
Proto4z.BUFF_BUFF = 2--描述性类型: 增益buff 
Proto4z.BUFF_DEBUFF = 3--描述性类型: 减益BUFF 
Proto4z.BUFF_HIDE = 4--描述性类型: 客户端不表现 
Proto4z.BUFF_PASSIVE = 5--描述性类型: 被动技能, 无法永久存在, 但死亡会停止任何触发 
Proto4z.BUFF_HOLD_MOVE = 10--控制: 禁止移动 
Proto4z.BUFF_REVERSE_MOVE = 11--控制: 移动反向 
Proto4z.BUFF_SILENCE_GENERAL = 12--控制: 沉默普攻 
Proto4z.BUFF_SILENCE_PHYSICAL = 13--控制: 沉默物攻 
Proto4z.BUFF_SILENCE_MAGIC = 14--控制: 沉默法攻 
Proto4z.BUFF_IMMUNE_MOVE = 20--免疫: 免疫移动类控制 
Proto4z.BUFF_IMMUNE_SILENCE_GENERAL = 21--免疫: 免疫普攻沉默 
Proto4z.BUFF_IMMUNE_SILENCE_PHYSICAL = 22--免疫: 免疫物攻沉默 
Proto4z.BUFF_IMMUNE_SILENCE_MAGIC = 23--免疫: 免疫法攻沉默 
Proto4z.BUFF_IMMUNE_DEBUFF = 30--免疫: 免疫DEBUFF 
Proto4z.BUFF_IMMUNE_BUFF = 31--免疫: 免疫增益BUFF 
Proto4z.BUFF_IMMUNE_OCCUPIED = 32--免疫: 免疫占据 
Proto4z.BUFF_IMMUNE_FLOAT = 33--免疫: 免疫击飞 
Proto4z.BUFF_IMMUNE_MOVEBACK = 34--免疫: 免疫击退 
Proto4z.BUFF_IMMUNE_BREAK = 35--免疫: 免疫技能中断 
 
Proto4z.register(11002,"DictBuff") 
Proto4z.DictBuff = {}  
Proto4z.DictBuff.__protoID = 11002 
Proto4z.DictBuff.__protoName = "DictBuff" 
Proto4z.DictBuff[1] = {name="id", type="ui64" }  
Proto4z.DictBuff[2] = {name="stamp", type="ui64" } --BUFF_STAMP 
Proto4z.DictBuff[3] = {name="stampText", type="string" }  
Proto4z.DictBuff[4] = {name="propID", type="ui64" } --提升的属性效果, 求积方式的参数是基础属性 不算其他装备 
Proto4z.DictBuff[5] = {name="skills", type="DictArrayKey" } --触发技能 
Proto4z.DictBuff[6] = {name="skillsText", type="string" } --触发技能 格式id,id,id  
Proto4z.DictBuff[7] = {name="buffs", type="DictArrayKey" } --触发buff 
Proto4z.DictBuff[8] = {name="buffsText", type="string" } --触发buff 格式id,id,id 
Proto4z.DictBuff[9] = {name="triggerAoeSearchID", type="double" } --search结果不为空触发 
Proto4z.DictBuff[10] = {name="triggerDelay", type="double" } --延迟触发, 当间隔触发不为0时生效 
Proto4z.DictBuff[11] = {name="triggerInterval", type="double" } --间隔触发 
Proto4z.DictBuff[12] = {name="triggerCountLimit", type="double" } --触发次数限制 
Proto4z.DictBuff[13] = {name="triggerAutoRemove", type="double" } --触发后移除buff 
Proto4z.DictBuff[14] = {name="keepTime", type="double" }  
Proto4z.DictBuff[15] = {name="limitStackTime", type="double" } --相同buff叠加时间并且刷新触发次数 
Proto4z.DictBuff[16] = {name="desc", type="string" }  
 
Proto4z.SKILL_NONE = 0 
Proto4z.SKILL_NORMAL = 1--普攻攻击技能 
Proto4z.SKILL_PASSIVE = 2--被动技能 
Proto4z.SKILL_PHYSICAL = 3--物理伤害 
Proto4z.SKILL_MAGIC = 4--魔法伤害 
Proto4z.SKILL_HARM = 5--血量减损 
Proto4z.SKILL_REGEN = 6--血量再生 
Proto4z.SKILL_ON_HIT_BREAK = 7--可被中断 
Proto4z.SKILL_ON_MOVE_BREAK = 8--可被中断 
Proto4z.SKILL_CAN_MOVE = 9--可移动 
Proto4z.SKILL_REMOVE_DEBUFF = 10--驱散减益BUFF 
Proto4z.SKILL_REMOVE_BUFF = 11--驱散增益BUFF 
 
Proto4z.SKILL_LOCKED_POS = 0--锁坐标 
Proto4z.SKILL_LOCKED_VECTOR = 1--锁方向 
Proto4z.SKILL_LOCKED_ENTITY = 2--永久锁目标 
Proto4z.SKILL_LOCKED_FREE = 3--自由锁定 
 
Proto4z.register(11003,"DictSkill") 
Proto4z.DictSkill = {}  
Proto4z.DictSkill.__protoID = 11003 
Proto4z.DictSkill.__protoName = "DictSkill" 
Proto4z.DictSkill[1] = {name="id", type="ui64" }  
Proto4z.DictSkill[2] = {name="stamp", type="ui64" }  
Proto4z.DictSkill[3] = {name="aosID", type="ui64" } --锁敌范围 
Proto4z.DictSkill[4] = {name="aosDict", type="AOESearch" } --锁敌 
Proto4z.DictSkill[5] = {name="aosType", type="ui16" } --0一次性锁坐标, 1一次性锁方向, 2永久锁目标, 3锁目标 超出范围外锁坐标 
Proto4z.DictSkill[6] = {name="aoeID", type="ui64" } --AOE范围 
Proto4z.DictSkill[7] = {name="aoeDict", type="AOESearch" }  
Proto4z.DictSkill[8] = {name="delay", type="double" }  
Proto4z.DictSkill[9] = {name="interval", type="double" } --自动释放间隔,针对自动施法,被动技能有效 
Proto4z.DictSkill[10] = {name="keep", type="double" } --持续时间 
Proto4z.DictSkill[11] = {name="cd", type="double" } --冷却 
Proto4z.DictSkill[12] = {name="hpAdd", type="double" } --附加真实伤害 
Proto4z.DictSkill[13] = {name="hpAddScaleRemanent", type="double" }  
Proto4z.DictSkill[14] = {name="hpAddScaleLost", type="double" }  
Proto4z.DictSkill[15] = {name="propID", type="ui64" } --附加属性提升 
Proto4z.DictSkill[16] = {name="dstTeleport", type="double" } --目标闪现到自己 
Proto4z.DictSkill[17] = {name="selfTeleport", type="double" } --自己闪现到目标 
Proto4z.DictSkill[18] = {name="dstMoveTime", type="double" } --附加给目标朝向自己的位移时间 
Proto4z.DictSkill[19] = {name="dstMoveSpeed", type="double" } --附加给目标朝向自己的位移速度 
Proto4z.DictSkill[20] = {name="selfMoveTime", type="double" } --附加给自己朝向目标的位移时间 
Proto4z.DictSkill[21] = {name="selfMoveSpeed", type="double" } --附加给自己朝向目标的位移速度 
Proto4z.DictSkill[22] = {name="appendBuffs", type="DictArrayKey" }  
Proto4z.DictSkill[23] = {name="appendBuffsText", type="string" } --触发buff 格式 k,k,k,  
Proto4z.DictSkill[24] = {name="appendBuffsAreaID", type="ui64" } --上buff的searchid 
Proto4z.DictSkill[25] = {name="appendBuffsAreaDict", type="AOESearch" }  
Proto4z.DictSkill[26] = {name="harmBuffs", type="DictArrayKey" }  
Proto4z.DictSkill[27] = {name="harmBuffsText", type="string" } --触发buff 格式 k,k,k,  
Proto4z.DictSkill[28] = {name="combSkills", type="DictArrayKey" }  
Proto4z.DictSkill[29] = {name="combSkillsText", type="string" } --组合技能 
Proto4z.DictSkill[30] = {name="followSkills", type="DictArrayKey" }  
Proto4z.DictSkill[31] = {name="followSkillsText", type="string" } --跟随技能 
Proto4z.DictSkill[32] = {name="desc", type="string" }  
