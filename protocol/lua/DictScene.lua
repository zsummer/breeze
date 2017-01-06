 
Proto4z.register(11000,"DictProp") 
Proto4z.DictProp = {} --战斗属性 
Proto4z.DictProp.__protoID = 11000 
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
Proto4z.DictProp[11] = {name="desc", type="string" }  
 
Proto4z.DictPropArray = {}  
Proto4z.DictPropArray.__protoName = "DictPropArray" 
Proto4z.DictPropArray.__protoDesc = "array" 
Proto4z.DictPropArray.__protoTypeV = "DictProp" 
 
Proto4z.DictPropMap = {}  
Proto4z.DictPropMap.__protoName = "DictPropMap" 
Proto4z.DictPropMap.__protoDesc = "map" 
Proto4z.DictPropMap.__protoTypeK = "ui64" 
Proto4z.DictPropMap.__protoTypeV = "DictProp" 
 
Proto4z.register(11001,"DictModelLevel") 
Proto4z.DictModelLevel = {}  
Proto4z.DictModelLevel.__protoID = 11001 
Proto4z.DictModelLevel.__protoName = "DictModelLevel" 
Proto4z.DictModelLevel[1] = {name="modelID", type="ui64" }  
Proto4z.DictModelLevel[2] = {name="levelID", type="ui64" }  
Proto4z.DictModelLevel[3] = {name="needExp", type="double" } --升级所需经验 
Proto4z.DictModelLevel[4] = {name="propID", type="ui64" } --战斗属性 
Proto4z.DictModelLevel[5] = {name="skills", type="DictArrayKey" } --该等级带来的可用技能 
Proto4z.DictModelLevel[6] = {name="skillsText", type="string" } --该等级带来的可用技能 格式id,id,id  
Proto4z.DictModelLevel[7] = {name="buffs", type="DictArrayKey" } --该等级带来的可用buff 
Proto4z.DictModelLevel[8] = {name="buffsText", type="string" } --该等级带来的可用buff 格式id,id,id 
 
Proto4z.DictModelLevelArray = {}  
Proto4z.DictModelLevelArray.__protoName = "DictModelLevelArray" 
Proto4z.DictModelLevelArray.__protoDesc = "array" 
Proto4z.DictModelLevelArray.__protoTypeV = "DictModelLevel" 
 
Proto4z.DictModelLevelMap = {}  
Proto4z.DictModelLevelMap.__protoName = "DictModelLevelMap" 
Proto4z.DictModelLevelMap.__protoDesc = "map" 
Proto4z.DictModelLevelMap.__protoTypeK = "ui64" 
Proto4z.DictModelLevelMap.__protoTypeV = "DictModelLevel" 
 
Proto4z.register(11002,"DictModel") 
Proto4z.DictModel = {}  
Proto4z.DictModel.__protoID = 11002 
Proto4z.DictModel.__protoName = "DictModel" 
Proto4z.DictModel[1] = {name="modelID", type="ui64" }  
Proto4z.DictModel[2] = {name="modelName", type="string" }  
Proto4z.DictModel[3] = {name="modelRedius", type="double" } --碰撞半径 
Proto4z.DictModel[4] = {name="iconID", type="ui64" } --头像 
Proto4z.DictModel[5] = {name="initLevel", type="double" } --等级 
Proto4z.DictModel[6] = {name="initCamp", type="ui16" }  
Proto4z.DictModel[7] = {name="initItems", type="DictMapPairValue" }  
Proto4z.DictModel[8] = {name="initItemsText", type="string" }  
Proto4z.DictModel[9] = {name="initState", type="ui16" } --初始化状态 
Proto4z.DictModel[10] = {name="actionScriptPath", type="string" } --行为树脚本路径 
Proto4z.DictModel[11] = {name="clientModelPath", type="string" } --客户端模型路径 
Proto4z.DictModel[12] = {name="desc", type="string" }  
 
Proto4z.DictModelArray = {}  
Proto4z.DictModelArray.__protoName = "DictModelArray" 
Proto4z.DictModelArray.__protoDesc = "array" 
Proto4z.DictModelArray.__protoTypeV = "DictModel" 
 
Proto4z.DictModelMap = {}  
Proto4z.DictModelMap.__protoName = "DictModelMap" 
Proto4z.DictModelMap.__protoDesc = "map" 
Proto4z.DictModelMap.__protoTypeK = "ui64" 
Proto4z.DictModelMap.__protoTypeV = "DictModel" 
 
Proto4z.register(11003,"AOESearch") 
Proto4z.AOESearch = {}  
Proto4z.AOESearch.__protoID = 11003 
Proto4z.AOESearch.__protoName = "AOESearch" 
Proto4z.AOESearch[1] = {name="id", type="ui64" }  
Proto4z.AOESearch[2] = {name="etype", type="ui16" } --实体类型, 玩家/AI 或者是NONE忽略该选项 
Proto4z.AOESearch[3] = {name="camp", type="ui64" } --0忽略阵营, 1自己, 2同阵营非自己, 3敌方,  4中立 
Proto4z.AOESearch[4] = {name="campText", type="string" }  
Proto4z.AOESearch[5] = {name="isRect", type="ui16" } --0扇形, 其他矩形 
Proto4z.AOESearch[6] = {name="distance", type="double" } --伤害距离 
Proto4z.AOESearch[7] = {name="radian", type="double" } --弧度或者宽度 
Proto4z.AOESearch[8] = {name="offsetX", type="double" } --坐标偏移量, 以caster为原点, 朝向为y轴 
Proto4z.AOESearch[9] = {name="offsetY", type="double" } --坐标偏移量, 以caster为原点, 朝向为y轴 
Proto4z.AOESearch[10] = {name="limitEntitys", type="ui64" } --最大目标数, 距离优先 
 
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
 
Proto4z.BUFF_EFFECT_PROP_MULTIPLICATION = 1--属性求积, 没有该标记为求和 
Proto4z.BUFF_EFFECT_LAST_TRIGGER_CLEAN = 2--触发超出限制后移除buff 
Proto4z.BUFF_EFFECT_TRIGGER_TIMMER = 3--定时检测触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_LOAD = 5--加载buff立刻触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_UNLOAD = 6--卸载buff立刻触发 
Proto4z.BUFF_EFFECT_TRIGGER_PRE_DEATH = 10--死亡前触发 
Proto4z.BUFF_EFFECT_TRIGGER_AFT_DEATH = 11--死亡后触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_GENERAL = 15--攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_PHYSICAL = 16--攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_MAGIC = 17--攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_ON_GENERAL = 20--被攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_ON_PHYSICAL = 21--被攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_ON_MAGIC = 22--被攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_ATTACH_GENERAL = 30--攻击触发 
Proto4z.BUFF_EFFECT_TRIGGER_WHEN_ON_ATTACH = 31--被攻击触发 
 
Proto4z.register(11004,"DictBuffEffect") 
Proto4z.DictBuffEffect = {}  
Proto4z.DictBuffEffect.__protoID = 11004 
Proto4z.DictBuffEffect.__protoName = "DictBuffEffect" 
Proto4z.DictBuffEffect[1] = {name="id", type="ui64" }  
Proto4z.DictBuffEffect[2] = {name="stamp", type="ui64" } --BUFF_EFFECT_STAMP 
Proto4z.DictBuffEffect[3] = {name="stampText", type="string" }  
Proto4z.DictBuffEffect[4] = {name="propID", type="ui64" } --提升的属性效果, 求积方式的参数是基础属性 不算其他装备 
Proto4z.DictBuffEffect[5] = {name="skills", type="DictArrayKey" } --触发技能 
Proto4z.DictBuffEffect[6] = {name="skillsText", type="string" } --触发技能 格式id,id,id  
Proto4z.DictBuffEffect[7] = {name="buffs", type="DictArrayKey" } --触发buff 
Proto4z.DictBuffEffect[8] = {name="buffsText", type="string" } --触发buff 格式id,id,id 
Proto4z.DictBuffEffect[9] = {name="areaTrigger", type="double" } --距离触发, 0为无效 
Proto4z.DictBuffEffect[10] = {name="intervalLimit", type="double" } --最小触发间隔时间, 0为无效 
Proto4z.DictBuffEffect[11] = {name="countLimit", type="double" } --触发次数限制 
Proto4z.DictBuffEffect[12] = {name="desc", type="string" }  
 
Proto4z.register(11005,"DictBuff") 
Proto4z.DictBuff = {}  
Proto4z.DictBuff.__protoID = 11005 
Proto4z.DictBuff.__protoName = "DictBuff" 
Proto4z.DictBuff[1] = {name="id", type="ui64" }  
Proto4z.DictBuff[2] = {name="stamp", type="ui64" } --BUFF_STAMP 
Proto4z.DictBuff[3] = {name="stampText", type="string" }  
Proto4z.DictBuff[4] = {name="effects", type="DictArrayKey" } --DictBuffEffect ID 
Proto4z.DictBuff[5] = {name="effectsText", type="string" }  
Proto4z.DictBuff[6] = {name="keepTime", type="double" }  
Proto4z.DictBuff[7] = {name="mutexType", type="ui16" } --0无互斥, 1 同ID时间叠加, 2 同ID时间最长的覆盖, 3 同ID最强的覆盖 
Proto4z.DictBuff[8] = {name="mutexID", type="ui64" } --0 
Proto4z.DictBuff[9] = {name="mutexStrength", type="double" }  
Proto4z.DictBuff[10] = {name="limitTime", type="double" }  
Proto4z.DictBuff[11] = {name="desc", type="string" }  
 
Proto4z.SKILL_NONE = 0 
Proto4z.SKILL_AUTO_LOCK = 1--自动锁敌 
Proto4z.SKILL_AUTO_USE = 2--自动施法 
Proto4z.SKILL_PASSIVE = 3--被动技能 
Proto4z.SKILL_ON_HIT_BREAK = 4--可被中断 
Proto4z.SKILL_ON_MOVE_BREAK = 5--可被中断 
Proto4z.SKILL_CAN_MOVE = 6--可移动 
Proto4z.SKILL_PHYSICAL = 7--物理类型 
Proto4z.SKILL_MAGIC = 8--魔法类型 
 
Proto4z.SKILL_BEHAVIOUR_NONE = 0 
Proto4z.SKILL_BEHAVIOUR_HIT = 1--攻击 
Proto4z.SKILL_BEHAVIOUR_HILL = 2--治疗 
Proto4z.SKILL_BEHAVIOUR_TELEPORT_TARGET = 3--瞬移到目标 
Proto4z.SKILL_BEHAVIOUR_REMOVE_DEBUFF = 4--驱散减益BUFF 
Proto4z.SKILL_BEHAVIOUR_REMOVE_BUFF = 5--驱散增益BUFF 
Proto4z.SKILL_BEHAVIOUR_TRIGGER_BUFF = 6--触发buff 
Proto4z.SKILL_BEHAVIOUR_TRIGGER_SKILL = 7--触发技能 
 
Proto4z.register(11006,"DictSkillEffect") 
Proto4z.DictSkillEffect = {}  
Proto4z.DictSkillEffect.__protoID = 11006 
Proto4z.DictSkillEffect.__protoName = "DictSkillEffect" 
Proto4z.DictSkillEffect[1] = {name="id", type="ui64" }  
Proto4z.DictSkillEffect[2] = {name="stamp", type="ui64" }  
Proto4z.DictSkillEffect[3] = {name="searchID", type="ui64" }  
Proto4z.DictSkillEffect[4] = {name="hpMode", type="ui16" } --血量变化类型:0 相加, 1与总血量相乘后再相加, 2与剩余血量相乘后再相加, 3与已损失血量相乘后叠加 
Proto4z.DictSkillEffect[5] = {name="hpLeft", type="double" } --血量变化参数 
Proto4z.DictSkillEffect[6] = {name="hitKeepTime", type="double" } --击退,浮空,牵引,的持续时间 
Proto4z.DictSkillEffect[7] = {name="hitKeepSpeed", type="double" } --击退,浮空,牵引,的持速度 
Proto4z.DictSkillEffect[8] = {name="skills", type="DictArrayKey" } --触发技能 
Proto4z.DictSkillEffect[9] = {name="skillsText", type="string" } --触发技能 格式id,id,id  
Proto4z.DictSkillEffect[10] = {name="buffs", type="DictArrayKey" } --触发buff 
Proto4z.DictSkillEffect[11] = {name="buffsText", type="string" } --触发buff 格式id,id,id 
Proto4z.DictSkillEffect[12] = {name="desc", type="string" }  
 
Proto4z.register(11007,"DictSkill") 
Proto4z.DictSkill = {}  
Proto4z.DictSkill.__protoID = 11007 
Proto4z.DictSkill.__protoName = "DictSkill" 
Proto4z.DictSkill[1] = {name="id", type="ui64" }  
Proto4z.DictSkill[2] = {name="stamp", type="ui64" }  
Proto4z.DictSkill[3] = {name="effects", type="DictArrayPairValue" }  
Proto4z.DictSkill[4] = {name="effectsText", type="string" } --时间:效果,时间:效果, 
Proto4z.DictSkill[5] = {name="desc", type="string" }  
