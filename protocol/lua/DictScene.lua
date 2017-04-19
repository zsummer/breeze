 
Proto4z.register(11000,"DictProp") 
Proto4z.DictProp = {} --战斗属性 
Proto4z.DictProp.__protoID = 11000 
Proto4z.DictProp.__protoName = "DictProp" 
Proto4z.DictProp[1] = {name="id", type="ui64" }  
Proto4z.DictProp[2] = {name="hp", type="double" } --血量值 
Proto4z.DictProp[3] = {name="attack", type="double" } --伤害 
Proto4z.DictProp[4] = {name="moveSpeed", type="double" } --移动速度 
Proto4z.DictProp[5] = {name="attackSpeed", type="double" } --攻击速度 
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
 
Proto4z.SKILL_TRIGGER_WHEN_LOAD_BUFF = 5--加载buff立刻触发 
Proto4z.SKILL_TRIGGER_WHEN_UNLOAD_BUFF = 6--卸载buff立刻触发 
Proto4z.SKILL_TRIGGER_PRE_DEATH = 10--死亡前触发 
Proto4z.SKILL_TRIGGER_AFT_DEATH = 11--死亡后触发 
Proto4z.SKILL_TRIGGER_WHEN_GENERAL = 15--攻击触发 
Proto4z.SKILL_TRIGGER_WHEN_PHYSICAL = 16--攻击触发 
Proto4z.SKILL_TRIGGER_WHEN_MAGIC = 17--攻击触发 
Proto4z.SKILL_TRIGGER_ON_GENERAL = 20--被攻击触发 
Proto4z.SKILL_TRIGGER_ON_PHYSICAL = 21--被攻击触发 
Proto4z.SKILL_TRIGGER_ON_MAGIC = 22--被攻击触发 
Proto4z.SKILL_TRIGGER_WHEN_ATTACH_GENERAL = 30--攻击触发 
Proto4z.SKILL_TRIGGER_WHEN_ON_ATTACH = 31--被攻击触发 
 
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
 
Proto4z.register(11004,"DictBuffEffect") 
Proto4z.DictBuffEffect = {}  
Proto4z.DictBuffEffect.__protoID = 11004 
Proto4z.DictBuffEffect.__protoName = "DictBuffEffect" 
Proto4z.DictBuffEffect[1] = {name="id", type="ui64" }  
Proto4z.DictBuffEffect[2] = {name="listenTriggerStamp", type="ui64" }  
Proto4z.DictBuffEffect[3] = {name="listenTriggerStampText", type="string" }  
Proto4z.DictBuffEffect[4] = {name="propID", type="ui64" } --提升的属性效果, 求积方式的参数是基础属性 不算其他装备 
Proto4z.DictBuffEffect[5] = {name="skills", type="DictArrayKey" } --触发技能 
Proto4z.DictBuffEffect[6] = {name="skillsText", type="string" } --触发技能 格式id,id,id  
Proto4z.DictBuffEffect[7] = {name="buffs", type="DictArrayKey" } --触发buff 
Proto4z.DictBuffEffect[8] = {name="buffsText", type="string" } --触发buff 格式id,id,id 
Proto4z.DictBuffEffect[9] = {name="areaTrigger", type="double" } --距离触发, 0为无效 
Proto4z.DictBuffEffect[10] = {name="timerTrigger", type="double" } --定时器触发间隔 
Proto4z.DictBuffEffect[11] = {name="intervalLimit", type="double" } --最小触发间隔时间, 0为无效 
Proto4z.DictBuffEffect[12] = {name="triggerCountLimit", type="double" } --触发次数限制 
Proto4z.DictBuffEffect[13] = {name="autoUnloadBuff", type="double" } --超出触发次数后自动移除buff 
Proto4z.DictBuffEffect[14] = {name="desc", type="string" }  
 
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
Proto4z.DictBuff[7] = {name="limitStackTime", type="double" } --相同buff叠加时间并且刷新触发次数 
Proto4z.DictBuff[8] = {name="desc", type="string" }  
 
Proto4z.SKILL_NONE = 0 
Proto4z.SKILL_AUTO_USE = 1--自动施法 
Proto4z.SKILL_PASSIVE = 2--被动技能 
Proto4z.SKILL_ON_HIT_BREAK = 3--可被中断 
Proto4z.SKILL_ON_MOVE_BREAK = 4--可被中断 
Proto4z.SKILL_CAN_MOVE = 5--可移动 
Proto4z.SKILL_PHYSICAL = 6--物理类型 
Proto4z.SKILL_MAGIC = 7--魔法类型 
 
Proto4z.SKILL_BEHAVIOUR_NONE = 0 
Proto4z.SKILL_BEHAVIOUR_HIT = 1--攻击 
Proto4z.SKILL_BEHAVIOUR_HILL = 2--治疗 
Proto4z.SKILL_BEHAVIOUR_TELEPORT_TARGET = 3--瞬移到目标 
Proto4z.SKILL_BEHAVIOUR_REMOVE_DEBUFF = 4--驱散减益BUFF 
Proto4z.SKILL_BEHAVIOUR_REMOVE_BUFF = 5--驱散增益BUFF 
Proto4z.SKILL_BEHAVIOUR_TRIGGER_BUFF = 6--触发buff 
Proto4z.SKILL_BEHAVIOUR_TRIGGER_SKILL = 7--触发技能 
 
Proto4z.register(11006,"DictSkillBehaviour") 
Proto4z.DictSkillBehaviour = {}  
Proto4z.DictSkillBehaviour.__protoID = 11006 
Proto4z.DictSkillBehaviour.__protoName = "DictSkillBehaviour" 
Proto4z.DictSkillBehaviour[1] = {name="id", type="ui64" }  
Proto4z.DictSkillBehaviour[2] = {name="isHit", type="ui16" } --0为普通, 1为攻击 
Proto4z.DictSkillBehaviour[3] = {name="searchID", type="ui64" } --如果为0则默认是给已锁定敌人或者锁定区域释放 
Proto4z.DictSkillBehaviour[4] = {name="hpAdd", type="double" } --附加真实伤害 
Proto4z.DictSkillBehaviour[5] = {name="hpAddScaleTotal", type="double" }  
Proto4z.DictSkillBehaviour[6] = {name="hpAddScaleRemanent", type="double" }  
Proto4z.DictSkillBehaviour[7] = {name="hpAddScaleLost", type="double" }  
Proto4z.DictSkillBehaviour[8] = {name="propID", type="ui64" } --附加属性提升 
Proto4z.DictSkillBehaviour[9] = {name="dstTeleport", type="double" } --目标闪现到自己 
Proto4z.DictSkillBehaviour[10] = {name="selfTeleport", type="double" } --自己闪现到目标 
Proto4z.DictSkillBehaviour[11] = {name="dstMoveTime", type="double" } --附加给目标朝向自己的位移时间 
Proto4z.DictSkillBehaviour[12] = {name="dstMoveSpeed", type="double" } --附加给目标朝向自己的位移速度 
Proto4z.DictSkillBehaviour[13] = {name="selfMoveTime", type="double" } --附加给自己朝向目标的位移时间 
Proto4z.DictSkillBehaviour[14] = {name="selfMoveSpeed", type="double" } --附加给自己朝向目标的位移速度 
Proto4z.DictSkillBehaviour[15] = {name="skills", type="DictArrayKey" } --触发技能 
Proto4z.DictSkillBehaviour[16] = {name="skillsText", type="string" } --触发技能 格式id,id,id  
Proto4z.DictSkillBehaviour[17] = {name="buffs", type="DictArrayKey" } --触发buff 
Proto4z.DictSkillBehaviour[18] = {name="buffsText", type="string" } --触发buff 格式id,id,id 
Proto4z.DictSkillBehaviour[19] = {name="desc", type="string" }  
 
Proto4z.register(11007,"DictSkill") 
Proto4z.DictSkill = {} --吟唱,引导 
Proto4z.DictSkill.__protoID = 11007 
Proto4z.DictSkill.__protoName = "DictSkill" 
Proto4z.DictSkill[1] = {name="id", type="ui64" }  
Proto4z.DictSkill[2] = {name="stamp", type="ui64" }  
Proto4z.DictSkill[3] = {name="cd", type="double" }  
Proto4z.DictSkill[4] = {name="searchID", type="ui64" }  
Proto4z.DictSkill[5] = {name="effects", type="DictArrayPairValue" }  
Proto4z.DictSkill[6] = {name="effectsText", type="string" } --时间:效果,时间:效果, 
Proto4z.DictSkill[7] = {name="desc", type="string" }  
