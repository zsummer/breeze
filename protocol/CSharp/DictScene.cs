 
namespace Proto4z  
{ 
 
    public class DictProp: Proto4z.IProtoObject //战斗属性  
    {     
        //proto id   
        public const ushort protoID = 11000;  
        static public ushort getProtoID() { return 11000; } 
        static public string getProtoName() { return "DictProp"; } 
        //members   
        public ulong id;  
        public double hp; //血量值  
        public double attack; //伤害  
        public double moveSpeed; //移动速度  
        public double attackQuick; //攻击加速  
        public string desc;  
        public DictProp()  
        { 
            id = 0;  
            hp = 0.0;  
            attack = 0.0;  
            moveSpeed = 0.0;  
            attackQuick = 0.0;  
            desc = "";  
        } 
        public DictProp(ulong id, double hp, double attack, double moveSpeed, double attackQuick, string desc) 
        { 
            this.id = id; 
            this.hp = hp; 
            this.attack = attack; 
            this.moveSpeed = moveSpeed; 
            this.attackQuick = attackQuick; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.attack)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.moveSpeed)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.attackQuick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.hp = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.attack = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.moveSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.attackQuick = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictPropArray : System.Collections.Generic.List<DictProp>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            int len = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            if(len > 0) 
            { 
                for (int i=0; i<len; i++) 
                { 
                    var data = new DictProp(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictPropMap : System.Collections.Generic.Dictionary<ulong, DictProp>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Key)); 
                ret.AddRange(kv.Value.__encode()); 
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            int len = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            if(len > 0) 
            { 
                for (int i=0; i<len; i++) 
                { 
                    var key = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                    var val = new DictProp(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public enum FILTER_STAMP : ulong 
    { 
        FILTER_NONE = 1, //全部  
        FILTER_SELF = 2, //自己  
        FILTER_OTHER_FRIEND = 3, //友方阵营  
        FILTER_ENEMY_CAMP = 4, //敌方阵营  
        FILTER_NEUTRAL_CAMP = 5, //中立阵营  
    }; 
 
    public class AOESearch: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 11001;  
        static public ushort getProtoID() { return 11001; } 
        static public string getProtoName() { return "AOESearch"; } 
        //members   
        public ulong id;  
        public ushort etype; //实体类型, 玩家/AI 或者是NONE忽略该选项  
        public ulong filter;  
        public string filterText;  
        public ushort isRect; //0扇形, 其他矩形  
        public double value1; //伤害距离  
        public double value2; //弧度或者远端宽度  
        public double value3; //忽略或者近端宽度  
        public double compensate; //距离补偿, 一般填负数 规避视觉上的灯下黑问题  
        public double clip; //可以裁剪扇形的尖角, 圆环等 矩形忽略该参数  
        public ulong limitEntitys; //最大目标数, 距离优先  
        public AOESearch()  
        { 
            id = 0;  
            etype = 0;  
            filter = 0;  
            filterText = "";  
            isRect = 0;  
            value1 = 0.0;  
            value2 = 0.0;  
            value3 = 0.0;  
            compensate = 0.0;  
            clip = 0.0;  
            limitEntitys = 0;  
        } 
        public AOESearch(ulong id, ushort etype, ulong filter, string filterText, ushort isRect, double value1, double value2, double value3, double compensate, double clip, ulong limitEntitys) 
        { 
            this.id = id; 
            this.etype = etype; 
            this.filter = filter; 
            this.filterText = filterText; 
            this.isRect = isRect; 
            this.value1 = value1; 
            this.value2 = value2; 
            this.value3 = value3; 
            this.compensate = compensate; 
            this.clip = clip; 
            this.limitEntitys = limitEntitys; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.etype)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.filter)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.filterText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.isRect)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value1)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value2)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value3)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.compensate)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.clip)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.limitEntitys)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.etype = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.filter = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.filterText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.isRect = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.value1 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.value2 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.value3 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.compensate = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.clip = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.limitEntitys = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum BUFF_STAMP : ulong 
    { 
        BUFF_HALO = 1, //描述性类型: 光环  
        BUFF_BUFF = 2, //描述性类型: 增益buff  
        BUFF_DEBUFF = 3, //描述性类型: 减益BUFF  
        BUFF_HIDE = 4, //描述性类型: 客户端不表现  
        BUFF_PASSIVE = 5, //描述性类型: 被动技能, 无法永久存在, 但死亡会停止任何触发  
        BUFF_HOLD_MOVE = 10, //控制: 禁止移动  
        BUFF_REVERSE_MOVE = 11, //控制: 移动反向  
        BUFF_SILENCE_GENERAL = 12, //控制: 沉默普攻  
        BUFF_SILENCE_PHYSICAL = 13, //控制: 沉默物攻  
        BUFF_SILENCE_MAGIC = 14, //控制: 沉默法攻  
        BUFF_IMMUNE_MOVE = 20, //免疫: 免疫移动类控制  
        BUFF_IMMUNE_SILENCE_GENERAL = 21, //免疫: 免疫普攻沉默  
        BUFF_IMMUNE_SILENCE_PHYSICAL = 22, //免疫: 免疫物攻沉默  
        BUFF_IMMUNE_SILENCE_MAGIC = 23, //免疫: 免疫法攻沉默  
        BUFF_IMMUNE_DEBUFF = 30, //免疫: 免疫DEBUFF  
        BUFF_IMMUNE_BUFF = 31, //免疫: 免疫增益BUFF  
        BUFF_IMMUNE_OCCUPIED = 32, //免疫: 免疫占据  
        BUFF_IMMUNE_FLOAT = 33, //免疫: 免疫击飞  
        BUFF_IMMUNE_MOVEBACK = 34, //免疫: 免疫击退  
        BUFF_IMMUNE_BREAK = 35, //免疫: 免疫技能中断  
    }; 
 
    public class DictBuff: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 11002;  
        static public ushort getProtoID() { return 11002; } 
        static public string getProtoName() { return "DictBuff"; } 
        //members   
        public ulong id;  
        public ulong stamp; //BUFF_STAMP  
        public string stampText;  
        public ulong propID; //提升的属性效果, 求积方式的参数是基础属性 不算其他装备  
        public DictArrayKey skills; //触发技能  
        public string skillsText; //触发技能 格式id,id,id   
        public DictArrayKey buffs; //触发buff  
        public string buffsText; //触发buff 格式id,id,id  
        public double triggerAoeSearchID; //search结果不为空触发  
        public double triggerDelay; //延迟触发, 当间隔触发不为0时生效  
        public double triggerInterval; //间隔触发  
        public double triggerCountLimit; //触发次数限制  
        public double triggerAutoRemove; //触发后移除buff  
        public double keepTime;  
        public double limitStackTime; //相同buff叠加时间并且刷新触发次数  
        public string desc;  
        public DictBuff()  
        { 
            id = 0;  
            stamp = 0;  
            stampText = "";  
            propID = 0;  
            skills = new DictArrayKey();  
            skillsText = "";  
            buffs = new DictArrayKey();  
            buffsText = "";  
            triggerAoeSearchID = 0.0;  
            triggerDelay = 0.0;  
            triggerInterval = 0.0;  
            triggerCountLimit = 0.0;  
            triggerAutoRemove = 0.0;  
            keepTime = 0.0;  
            limitStackTime = 0.0;  
            desc = "";  
        } 
        public DictBuff(ulong id, ulong stamp, string stampText, ulong propID, DictArrayKey skills, string skillsText, DictArrayKey buffs, string buffsText, double triggerAoeSearchID, double triggerDelay, double triggerInterval, double triggerCountLimit, double triggerAutoRemove, double keepTime, double limitStackTime, string desc) 
        { 
            this.id = id; 
            this.stamp = stamp; 
            this.stampText = stampText; 
            this.propID = propID; 
            this.skills = skills; 
            this.skillsText = skillsText; 
            this.buffs = buffs; 
            this.buffsText = buffsText; 
            this.triggerAoeSearchID = triggerAoeSearchID; 
            this.triggerDelay = triggerDelay; 
            this.triggerInterval = triggerInterval; 
            this.triggerCountLimit = triggerCountLimit; 
            this.triggerAutoRemove = triggerAutoRemove; 
            this.keepTime = keepTime; 
            this.limitStackTime = limitStackTime; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.stamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.stampText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            if (this.skills == null) this.skills = new DictArrayKey(); 
            data.AddRange(this.skills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.skillsText)); 
            if (this.buffs == null) this.buffs = new DictArrayKey(); 
            data.AddRange(this.buffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.buffsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.triggerAoeSearchID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.triggerDelay)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.triggerInterval)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.triggerCountLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.triggerAutoRemove)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.keepTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.limitStackTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stamp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stampText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skills = new DictArrayKey(); 
            this.skills.__decode(binData, ref pos); 
            this.skillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.buffs = new DictArrayKey(); 
            this.buffs.__decode(binData, ref pos); 
            this.buffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.triggerAoeSearchID = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.triggerDelay = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.triggerInterval = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.triggerCountLimit = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.triggerAutoRemove = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.keepTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.limitStackTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum SKILL_STAMP : ulong 
    { 
        SKILL_NONE = 0,  
        SKILL_NORMAL = 1, //普攻攻击技能  
        SKILL_PASSIVE = 2, //被动技能  
        SKILL_PHYSICAL = 3, //物理伤害  
        SKILL_MAGIC = 4, //魔法伤害  
        SKILL_HARM = 5, //血量减损  
        SKILL_REGEN = 6, //血量再生  
        SKILL_ON_HIT_BREAK = 7, //可被中断  
        SKILL_ON_MOVE_BREAK = 8, //可被中断  
        SKILL_CAN_MOVE = 9, //可移动  
        SKILL_REMOVE_DEBUFF = 10, //驱散减益BUFF  
        SKILL_REMOVE_BUFF = 11, //驱散增益BUFF  
    }; 
 
    public enum SKILL_AOS : ulong 
    { 
        SKILL_LOCKED_POS = 0, //锁坐标  
        SKILL_LOCKED_VECTOR = 1, //锁方向  
        SKILL_LOCKED_ENTITY = 2, //永久锁目标  
        SKILL_LOCKED_FREE = 3, //自由锁定  
    }; 
 
    public class DictSkill: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 11003;  
        static public ushort getProtoID() { return 11003; } 
        static public string getProtoName() { return "DictSkill"; } 
        //members   
        public ulong id;  
        public ulong stamp;  
        public ulong aosID; //锁敌范围  
        public AOESearch aosDict; //锁敌  
        public ushort aosType; //0一次性锁坐标, 1一次性锁方向, 2永久锁目标, 3锁目标 超出范围外锁坐标  
        public ulong aoeID; //AOE范围  
        public AOESearch aoeDict;  
        public double delay;  
        public double interval; //自动释放间隔,针对自动施法,被动技能有效  
        public double keep; //持续时间  
        public double cd; //冷却  
        public double hpAdd; //附加真实伤害  
        public double hpAddScaleRemanent;  
        public double hpAddScaleLost;  
        public ulong propID; //附加属性提升  
        public double dstTeleport; //目标闪现到自己  
        public double selfTeleport; //自己闪现到目标  
        public double dstMoveTime; //附加给目标朝向自己的位移时间  
        public double dstMoveSpeed; //附加给目标朝向自己的位移速度  
        public double selfMoveTime; //附加给自己朝向目标的位移时间  
        public double selfMoveSpeed; //附加给自己朝向目标的位移速度  
        public DictArrayKey appendBuffs;  
        public string appendBuffsText; //触发buff 格式 k,k,k,   
        public ulong appendBuffsAreaID; //上buff的searchid  
        public AOESearch appendBuffsAreaDict;  
        public DictArrayKey harmBuffs;  
        public string harmBuffsText; //触发buff 格式 k,k,k,   
        public DictArrayKey combSkills;  
        public string combSkillsText; //组合技能  
        public DictArrayKey followSkills;  
        public string followSkillsText; //跟随技能  
        public string desc;  
        public DictSkill()  
        { 
            id = 0;  
            stamp = 0;  
            aosID = 0;  
            aosDict = new AOESearch();  
            aosType = 0;  
            aoeID = 0;  
            aoeDict = new AOESearch();  
            delay = 0.0;  
            interval = 0.0;  
            keep = 0.0;  
            cd = 0.0;  
            hpAdd = 0.0;  
            hpAddScaleRemanent = 0.0;  
            hpAddScaleLost = 0.0;  
            propID = 0;  
            dstTeleport = 0.0;  
            selfTeleport = 0.0;  
            dstMoveTime = 0.0;  
            dstMoveSpeed = 0.0;  
            selfMoveTime = 0.0;  
            selfMoveSpeed = 0.0;  
            appendBuffs = new DictArrayKey();  
            appendBuffsText = "";  
            appendBuffsAreaID = 0;  
            appendBuffsAreaDict = new AOESearch();  
            harmBuffs = new DictArrayKey();  
            harmBuffsText = "";  
            combSkills = new DictArrayKey();  
            combSkillsText = "";  
            followSkills = new DictArrayKey();  
            followSkillsText = "";  
            desc = "";  
        } 
        public DictSkill(ulong id, ulong stamp, ulong aosID, AOESearch aosDict, ushort aosType, ulong aoeID, AOESearch aoeDict, double delay, double interval, double keep, double cd, double hpAdd, double hpAddScaleRemanent, double hpAddScaleLost, ulong propID, double dstTeleport, double selfTeleport, double dstMoveTime, double dstMoveSpeed, double selfMoveTime, double selfMoveSpeed, DictArrayKey appendBuffs, string appendBuffsText, ulong appendBuffsAreaID, AOESearch appendBuffsAreaDict, DictArrayKey harmBuffs, string harmBuffsText, DictArrayKey combSkills, string combSkillsText, DictArrayKey followSkills, string followSkillsText, string desc) 
        { 
            this.id = id; 
            this.stamp = stamp; 
            this.aosID = aosID; 
            this.aosDict = aosDict; 
            this.aosType = aosType; 
            this.aoeID = aoeID; 
            this.aoeDict = aoeDict; 
            this.delay = delay; 
            this.interval = interval; 
            this.keep = keep; 
            this.cd = cd; 
            this.hpAdd = hpAdd; 
            this.hpAddScaleRemanent = hpAddScaleRemanent; 
            this.hpAddScaleLost = hpAddScaleLost; 
            this.propID = propID; 
            this.dstTeleport = dstTeleport; 
            this.selfTeleport = selfTeleport; 
            this.dstMoveTime = dstMoveTime; 
            this.dstMoveSpeed = dstMoveSpeed; 
            this.selfMoveTime = selfMoveTime; 
            this.selfMoveSpeed = selfMoveSpeed; 
            this.appendBuffs = appendBuffs; 
            this.appendBuffsText = appendBuffsText; 
            this.appendBuffsAreaID = appendBuffsAreaID; 
            this.appendBuffsAreaDict = appendBuffsAreaDict; 
            this.harmBuffs = harmBuffs; 
            this.harmBuffsText = harmBuffsText; 
            this.combSkills = combSkills; 
            this.combSkillsText = combSkillsText; 
            this.followSkills = followSkills; 
            this.followSkillsText = followSkillsText; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.stamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.aosID)); 
            if (this.aosDict == null) this.aosDict = new AOESearch(); 
            data.AddRange(this.aosDict.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.aosType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.aoeID)); 
            if (this.aoeDict == null) this.aoeDict = new AOESearch(); 
            data.AddRange(this.aoeDict.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.delay)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.interval)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.keep)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.cd)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hpAdd)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hpAddScaleRemanent)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hpAddScaleLost)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.dstTeleport)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.selfTeleport)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.dstMoveTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.dstMoveSpeed)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.selfMoveTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.selfMoveSpeed)); 
            if (this.appendBuffs == null) this.appendBuffs = new DictArrayKey(); 
            data.AddRange(this.appendBuffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.appendBuffsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.appendBuffsAreaID)); 
            if (this.appendBuffsAreaDict == null) this.appendBuffsAreaDict = new AOESearch(); 
            data.AddRange(this.appendBuffsAreaDict.__encode()); 
            if (this.harmBuffs == null) this.harmBuffs = new DictArrayKey(); 
            data.AddRange(this.harmBuffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.harmBuffsText)); 
            if (this.combSkills == null) this.combSkills = new DictArrayKey(); 
            data.AddRange(this.combSkills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.combSkillsText)); 
            if (this.followSkills == null) this.followSkills = new DictArrayKey(); 
            data.AddRange(this.followSkills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.followSkillsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stamp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.aosID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.aosDict = new AOESearch(); 
            this.aosDict.__decode(binData, ref pos); 
            this.aosType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.aoeID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.aoeDict = new AOESearch(); 
            this.aoeDict.__decode(binData, ref pos); 
            this.delay = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.interval = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.keep = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.cd = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.hpAdd = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.hpAddScaleRemanent = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.hpAddScaleLost = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dstTeleport = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.selfTeleport = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.dstMoveTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.dstMoveSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.selfMoveTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.selfMoveSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.appendBuffs = new DictArrayKey(); 
            this.appendBuffs.__decode(binData, ref pos); 
            this.appendBuffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.appendBuffsAreaID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.appendBuffsAreaDict = new AOESearch(); 
            this.appendBuffsAreaDict.__decode(binData, ref pos); 
            this.harmBuffs = new DictArrayKey(); 
            this.harmBuffs.__decode(binData, ref pos); 
            this.harmBuffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.combSkills = new DictArrayKey(); 
            this.combSkills.__decode(binData, ref pos); 
            this.combSkillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.followSkills = new DictArrayKey(); 
            this.followSkills.__decode(binData, ref pos); 
            this.followSkillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
