 
namespace Proto4z  
{ 
 
    public enum SCENE_TYPE : ushort 
    { 
        SCENE_TYPE_NONE = 0, //无效  
        SCENE_TYPE_HOME = 1, //主城  
        SCENE_TYPE_SOME_INSTANCING = 2, //一些副本  
        SCENE_TYPE_ARENA = 3, //竞技场  
        SCENE_TYPE_GUILD = 4, //公会  
    }; 
 
    public enum SCENE_STATUS : ushort 
    { 
        SCENE_STATUS_NONE = 0, //不存在  
        SCENE_STATUS_MATCHING = 1, //正在匹配  
        SCENE_STATUS_WAITING = 2, //匹配成功,等待玩家进入  
        SCENE_STATUS_INSTANCING = 3, //场景中  
    }; 
 
    public class SceneInfo: Proto4z.IProtoObject //场景信息  
    {     
        //proto id   
        public const ushort protoID = 10000;  
        static public ushort getProtoID() { return 10000; } 
        static public string getProtoName() { return "SceneInfo"; } 
        //members   
        public ushort type; //类型  
        public ushort status; //状态  
        public string host; //服务器host  
        public ushort port; //服务器port  
        public uint spaceID; //空间(场景,房间,战场,INSTANCING ID)的实例ID  
        public SessionToken token; //令牌  
        public byte isActive; //当前活跃场景, 用于场景切换过渡,或者同时多个场景存在的情况  
        public SceneInfo()  
        { 
            type = 0;  
            status = 0;  
            host = "";  
            port = 0;  
            spaceID = 0;  
            token = new SessionToken();  
            isActive = 0;  
        } 
        public SceneInfo(ushort type, ushort status, string host, ushort port, uint spaceID, SessionToken token, byte isActive) 
        { 
            this.type = type; 
            this.status = status; 
            this.host = host; 
            this.port = port; 
            this.spaceID = spaceID; 
            this.token = token; 
            this.isActive = isActive; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            if (this.token == null) this.token = new SessionToken(); 
            data.AddRange(this.token.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.isActive)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.token = new SessionToken(); 
            this.token.__decode(binData, ref pos); 
            this.isActive = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SceneInfoArray : System.Collections.Generic.List<SceneInfo>, Proto4z.IProtoObject  
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
                    var data = new SceneInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public enum ENTITY_STATE : ushort 
    { 
        ESTATE_FREEZING = 0, //冻结, 不能移动,不能操作, 100%免伤  
        ESTATE_ACTIVE = 1, //活跃状态  
        ESTATE_PRE_DIED = 2, //进入死亡流程  
        ESTATE_DIED = 3, //死亡状态  
    }; 
 
    public enum ENTITY_TYPE : ushort 
    { 
        ETYPE_INVALID = 0,  
        ETYPE_AVATAR = 1,  
        ETYPE_AI = 2,  
        ETYPE_FLIGHT = 3, //飞行道具  
    }; 
 
    public enum ENTITY_COLOR : ushort 
    { 
        ECOLOR_INVALID = 0, //红方  
        ECOLOR_RED = 1, //红方  
        ECOLOR_BLUE = 2, //蓝方  
        ECOLOR_NEUTRAL = 1000, //[0~ECOLOR_NEUTRAL)阵营相互敌对, [ECOLOR_NEUTRAL~)中立温和阵营  
    }; 
 
    public enum MoveAction : ushort 
    { 
        MACTION_IDLE = 0, //空闲  
        MACTION_FACE = 1, //朝向  
        MACTION_FOLLOW = 2, //跟随  
        MACTION_PATH = 3, //路径  
    }; 
 
    public enum SEARCH_TYPE : ushort 
    { 
        SEARCH_DISTANCE = 1, //org 半径  
        SEARCH_SEACTOR = 2, //org 扇形  
        SEARCH_RECT = 3, //org 矩形  
    }; 
 
    public enum SEARCH_TARGET_TYPE : uint 
    { 
        SEARCH_TARGET_SELF = 1, //自身, 玩家或者AI  
        SEARCH_TARGET_AVATAR = 2, //施法者, 玩家或者AI  
        SEARCH_TARGET_AI = 3, //施法者, 玩家或者AI  
        SEARCH_TARGET_BARRIER = 4, //障碍  
        SEARCH_TARGET_FLIGHT = 5, //飞行道具  
        SEARCH_TARGET_ENEMY = 6, //敌人  
        SEARCH_TARGET_FRIEND = 7, //全体友方  
        SEARCH_TARGET_NEUTRAL = 8, //中立  
    }; 
 
    public enum SKILL_TYPE : ulong 
    { 
        SKILL_NORMAL_ATTACK = 1, //普通攻击  
        SKILL_AUTO = 2, //被动技能  
        SKILL_CAN_BREAK = 3, //可被中断  
        SKILL_CAN_MOVE = 4, //可移动  
        SKILL_PHYSICAL = 5, //物理攻击  
        SKILL_MAGIC = 6, //魔法攻击  
        SKILL_HARM = 7, //进行伤害计算  
        SKILL_BREAK_SELF_MOVE = 8, //打断自己移动  
        SKILL_BREAK_SELF_SKILL = 9, //打断自己的技能  
        SKILL_BREAK_TARGET_MOVE = 10, //打断目标移动  
        SKILL_BREAK_TARGET_SKILL = 11, //打断目标技能  
        SKILL_BREAK_TARGET_DEBUFF = 12, //驱散目标减益BUFF  
        SKILL_BREAK_TARGET_BUFF = 13, //驱散目标增益BUFF  
    }; 
 
    public enum BUFF_TYPE : ulong 
    { 
        BUFF_HALO = 1, //组合类型: 光环  
        BUFF_BUFF = 2, //组合类型: 增益buff  
        BUFF_DEBUFF = 3, //组合类型: 减益BUFF  
        BUFF_HIDE = 4, //组合类型: 客户端不表现  
        BUFF_SNEAK = 5, //组合类型: 潜行 不会被非己方阵营的任何AOE技能搜索到  
        BUFF_HOLD_MOVE = 15, //控制: 禁止移动  
        BUFF_REVERSE_MOVE = 16, //控制: 移动反向  
        BUFF_SILENCE = 17, //控制: 沉默所有技能  
        BUFF_SILENCE_WITHOUT_NORMAL = 18, //控制: 沉默非普通攻击  
        BUFF_SILENCE_PHYSICAL = 19, //控制: 沉默物理攻击  
        BUFF_SILENCE_MAGIC = 20, //控制: 沉默魔法攻击  
        BUFF_IMMUNE_MOVE = 25, //免疫: 免疫被控 移动禁止  
        BUFF_IMMUNE_SILENCE = 26, //免疫: 免疫沉默  
        BUFF_IMMUNE_DEBUFF = 27, //免疫: 免疫DEBUFF  
        BUFF_IMMUNE_PHYSICAL = 28, //免疫: 物攻免疫  
        BUFF_IMMUNE_MAGIC = 29, //免疫: 法攻免疫  
        BUFF_IMMUNE_BREAK = 30, //免疫: 不可被技能驱散  
        BUFF_INC_DAMAGE = 35, //属性加成: 加增伤率 万分比(除以10000)  value1为基础概率, value2为成长概率   
        BUFF_SUB_DAMAGE = 36, //属性加成: 减伤率 万分比(除以10000)  value1为基础概率, value2为成长概率   
        BUFF_INC_SPEED = 41, //属性加成: 加速度  万分比(除以10000) value1为固定速度加成, value2为概率加成  
        BUFF_INC_SUCK_BLOOD = 42, //属性加成: 吸血率 万分比(除以10000)  value1为基础概率, value2为成长概率   
        BUFF_LIGHT_LIFE = 50, //持续性触发: 治疗(生命), 点燃(生命)   value1为每秒固定值, value2为每秒恢复/扣除相对于自己最大血量的万分比(除以10000)  
        BUFF_LIGHT_RUNSKILL = 51, //持续性触发: 触发一个技能,  光环BUFF,   配置:value填写要触发的技能ID, value1为间隔时间  
    }; 
 
 
    public class SkillIDArray : System.Collections.Generic.List<uint>, Proto4z.IProtoObject //技能ID数组  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI32(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI32(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class BuffIDArray : System.Collections.Generic.List<uint>, Proto4z.IProtoObject //buff ID 数组  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI32(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI32(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class TargetSearch: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10001;  
        static public ushort getProtoID() { return 10001; } 
        static public string getProtoName() { return "TargetSearch"; } 
        //members   
        public ushort searchType;  
        public ulong targetType;  
        public float distance; //伤害距离  
        public float radian; //弧度或者宽度  
        public float offsetX; //坐标偏移量  
        public float offsetY; //坐标偏移量  
        public uint targetMaxCount; //最大目标数  
        public TargetSearch()  
        { 
            searchType = 0;  
            targetType = 0;  
            distance = 0.0f;  
            radian = 0.0f;  
            offsetX = 0.0f;  
            offsetY = 0.0f;  
            targetMaxCount = 0;  
        } 
        public TargetSearch(ushort searchType, ulong targetType, float distance, float radian, float offsetX, float offsetY, uint targetMaxCount) 
        { 
            this.searchType = searchType; 
            this.targetType = targetType; 
            this.distance = distance; 
            this.radian = radian; 
            this.offsetX = offsetX; 
            this.offsetY = offsetY; 
            this.targetMaxCount = targetMaxCount; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.searchType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.targetType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.distance)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.radian)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.offsetX)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.offsetY)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.targetMaxCount)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.searchType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.targetType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.distance = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            this.radian = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            this.offsetX = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            this.offsetY = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            this.targetMaxCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class TargetAddSkillBuff: Proto4z.IProtoObject //目标上技能和buff  
    {     
        //proto id   
        public const ushort protoID = 10002;  
        static public ushort getProtoID() { return 10002; } 
        static public string getProtoName() { return "TargetAddSkillBuff"; } 
        //members   
        public TargetSearch search;  
        public SkillIDArray skills;  
        public BuffIDArray buffs;  
        public TargetAddSkillBuff()  
        { 
            search = new TargetSearch();  
            skills = new SkillIDArray();  
            buffs = new BuffIDArray();  
        } 
        public TargetAddSkillBuff(TargetSearch search, SkillIDArray skills, BuffIDArray buffs) 
        { 
            this.search = search; 
            this.skills = skills; 
            this.buffs = buffs; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.search == null) this.search = new TargetSearch(); 
            data.AddRange(this.search.__encode()); 
            if (this.skills == null) this.skills = new SkillIDArray(); 
            data.AddRange(this.skills.__encode()); 
            if (this.buffs == null) this.buffs = new BuffIDArray(); 
            data.AddRange(this.buffs.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.search = new TargetSearch(); 
            this.search.__decode(binData, ref pos); 
            this.skills = new SkillIDArray(); 
            this.skills.__decode(binData, ref pos); 
            this.buffs = new BuffIDArray(); 
            this.buffs.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class TargetAddSkillBuffArray : System.Collections.Generic.List<TargetAddSkillBuff>, Proto4z.IProtoObject  
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
                    var data = new TargetAddSkillBuff(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class HitData: Proto4z.IProtoObject //技能  
    {     
        //proto id   
        public const ushort protoID = 10003;  
        static public ushort getProtoID() { return 10003; } 
        static public string getProtoName() { return "HitData"; } 
        //members   
        public ushort act; //序列  
        public float rate; //概率  
        public uint buffID;  
        public uint delay; //序列延迟  
        public HitData()  
        { 
            act = 0;  
            rate = 0.0f;  
            buffID = 0;  
            delay = 0;  
        } 
        public HitData(ushort act, float rate, uint buffID, uint delay) 
        { 
            this.act = act; 
            this.rate = rate; 
            this.buffID = buffID; 
            this.delay = delay; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.act)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.rate)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.buffID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.delay)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.act = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.rate = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            this.buffID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.delay = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class HitDataArray : System.Collections.Generic.List<HitData>, Proto4z.IProtoObject  
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
                    var data = new HitData(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class SkillData: Proto4z.IProtoObject //技能  
    {     
        //proto id   
        public const ushort protoID = 10004;  
        static public ushort getProtoID() { return 10004; } 
        static public string getProtoName() { return "SkillData"; } 
        //members   
        public uint skillID; //skillID  
        public ulong skillType; //SKILL_TYPE  
        public uint cd;  
        public HitDataArray hitActions; //动作触发序列  
        public TargetAddSkillBuffArray targetAddSkillBuffs; //上技能或者buff, 每个动作触发一次  
        public TargetSearch targetDamage; //触发伤害  
        public float teleportDistance; //瞬移  
        public SkillData()  
        { 
            skillID = 0;  
            skillType = 0;  
            cd = 0;  
            hitActions = new HitDataArray();  
            targetAddSkillBuffs = new TargetAddSkillBuffArray();  
            targetDamage = new TargetSearch();  
            teleportDistance = 0.0f;  
        } 
        public SkillData(uint skillID, ulong skillType, uint cd, HitDataArray hitActions, TargetAddSkillBuffArray targetAddSkillBuffs, TargetSearch targetDamage, float teleportDistance) 
        { 
            this.skillID = skillID; 
            this.skillType = skillType; 
            this.cd = cd; 
            this.hitActions = hitActions; 
            this.targetAddSkillBuffs = targetAddSkillBuffs; 
            this.targetDamage = targetDamage; 
            this.teleportDistance = teleportDistance; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.cd)); 
            if (this.hitActions == null) this.hitActions = new HitDataArray(); 
            data.AddRange(this.hitActions.__encode()); 
            if (this.targetAddSkillBuffs == null) this.targetAddSkillBuffs = new TargetAddSkillBuffArray(); 
            data.AddRange(this.targetAddSkillBuffs.__encode()); 
            if (this.targetDamage == null) this.targetDamage = new TargetSearch(); 
            data.AddRange(this.targetDamage.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.teleportDistance)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.skillType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.cd = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.hitActions = new HitDataArray(); 
            this.hitActions.__decode(binData, ref pos); 
            this.targetAddSkillBuffs = new TargetAddSkillBuffArray(); 
            this.targetAddSkillBuffs.__decode(binData, ref pos); 
            this.targetDamage = new TargetSearch(); 
            this.targetDamage.__decode(binData, ref pos); 
            this.teleportDistance = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class BuffData: Proto4z.IProtoObject //buff  
    {     
        //proto id   
        public const ushort protoID = 10005;  
        static public ushort getProtoID() { return 10005; } 
        static public string getProtoName() { return "BuffData"; } 
        //members   
        public uint buffID;  
        public uint piletime; //最大叠加时间  
        public uint keepTime; //保持时间  
        public ulong buffType; //buff类型  
        public int value1; //值1  
        public int value2; //值2  
        public BuffData()  
        { 
            buffID = 0;  
            piletime = 0;  
            keepTime = 0;  
            buffType = 0;  
            value1 = 0;  
            value2 = 0;  
        } 
        public BuffData(uint buffID, uint piletime, uint keepTime, ulong buffType, int value1, int value2) 
        { 
            this.buffID = buffID; 
            this.piletime = piletime; 
            this.keepTime = keepTime; 
            this.buffType = buffType; 
            this.value1 = value1; 
            this.value2 = value2; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.buffID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.piletime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.keepTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.buffType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.value1)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.value2)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.buffID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.piletime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.keepTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.buffType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.value1 = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.value2 = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum HARM_TYPE : ushort 
    { 
        HARMTYPE_GENERAL = 0, //普通伤害  
        HARMTYPE_MISS = 1, //闪避  
        HARMTYPE_CRITICAL = 2, //暴击  
        HARMTYPE_HILL = 3, //治疗  
    }; 
 
    public class HarmData: Proto4z.IProtoObject //伤害数据  
    {     
        //proto id   
        public const ushort protoID = 10006;  
        static public ushort getProtoID() { return 10006; } 
        static public string getProtoName() { return "HarmData"; } 
        //members   
        public uint eid; //目标eid  
        public float harm; //如果为正是伤害, 为负则是回血  
        public ushort type; //伤害类型HARM_TYPE  
        public HarmData()  
        { 
            eid = 0;  
            harm = 0.0f;  
            type = 0;  
        } 
        public HarmData(uint eid, float harm, ushort type) 
        { 
            this.eid = eid; 
            this.harm = harm; 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeSingle(this.harm)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.harm = Proto4z.BaseProtoObject.decodeSingle(binData, ref pos); 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class HarmDataArray : System.Collections.Generic.List<HarmData>, Proto4z.IProtoObject  
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
                    var data = new HarmData(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class SkillInfo: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10007;  
        static public ushort getProtoID() { return 10007; } 
        static public string getProtoName() { return "SkillInfo"; } 
        //members   
        public uint skillID;  
        public uint start; //start (server)tick  
        public uint lastHitTick; //lastHitTick  
        public uint seq; //hit seq  
        public EPosition dst; //目标位置,只有需要用到的这个参数的技能才会读这个字段  
        public uint foe; //锁定的目标  
        public SkillData data; //配置数据  
        public SkillInfo()  
        { 
            skillID = 0;  
            start = 0;  
            lastHitTick = 0;  
            seq = 0;  
            dst = new EPosition();  
            foe = 0;  
            data = new SkillData();  
        } 
        public SkillInfo(uint skillID, uint start, uint lastHitTick, uint seq, EPosition dst, uint foe, SkillData data) 
        { 
            this.skillID = skillID; 
            this.start = start; 
            this.lastHitTick = lastHitTick; 
            this.seq = seq; 
            this.dst = dst; 
            this.foe = foe; 
            this.data = data; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.start)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.lastHitTick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.seq)); 
            if (this.dst == null) this.dst = new EPosition(); 
            data.AddRange(this.dst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.foe)); 
            if (this.data == null) this.data = new SkillData(); 
            data.AddRange(this.data.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.start = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.lastHitTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.seq = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.dst = new EPosition(); 
            this.dst.__decode(binData, ref pos); 
            this.foe = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.data = new SkillData(); 
            this.data.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SkillInfoArray : System.Collections.Generic.List<SkillInfo>, Proto4z.IProtoObject  
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
                    var data = new SkillInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class BuffInfo: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10008;  
        static public ushort getProtoID() { return 10008; } 
        static public string getProtoName() { return "BuffInfo"; } 
        //members   
        public uint eid; //施放该buff的entity id  
        public uint skillID; //如果该buff是被技能触发的 则记录该技能, 被动技能是0  
        public uint buffID;  
        public uint start; //start (server)tick  
        public uint lastTrigerTick; //lastTrigerTick  
        public BuffData data; //配置数据  
        public BuffInfo()  
        { 
            eid = 0;  
            skillID = 0;  
            buffID = 0;  
            start = 0;  
            lastTrigerTick = 0;  
            data = new BuffData();  
        } 
        public BuffInfo(uint eid, uint skillID, uint buffID, uint start, uint lastTrigerTick, BuffData data) 
        { 
            this.eid = eid; 
            this.skillID = skillID; 
            this.buffID = buffID; 
            this.start = start; 
            this.lastTrigerTick = lastTrigerTick; 
            this.data = data; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.buffID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.start)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.lastTrigerTick)); 
            if (this.data == null) this.data = new BuffData(); 
            data.AddRange(this.data.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.skillID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.buffID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.start = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.lastTrigerTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.data = new BuffData(); 
            this.data.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class BuffInfoArray : System.Collections.Generic.List<BuffInfo>, Proto4z.IProtoObject  
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
                    var data = new BuffInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EntityDict: Proto4z.IProtoObject //字典属性  
    {     
        //proto id   
        public const ushort protoID = 10009;  
        static public ushort getProtoID() { return 10009; } 
        static public string getProtoName() { return "EntityDict"; } 
        //members   
        public ulong serviceID; //用户ID, 非用户为InvalidServiceID  
        public UserBaseInfo base;  
        public DictFightEffect fight; //战斗属性  
        public EntityDict()  
        { 
            serviceID = 0;  
            base = new UserBaseInfo();  
            fight = new DictFightEffect();  
        } 
        public EntityDict(ulong serviceID, UserBaseInfo base, DictFightEffect fight) 
        { 
            this.serviceID = serviceID; 
            this.base = base; 
            this.fight = fight; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            if (this.base == null) this.base = new UserBaseInfo(); 
            data.AddRange(this.base.__encode()); 
            if (this.fight == null) this.fight = new DictFightEffect(); 
            data.AddRange(this.fight.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.base = new UserBaseInfo(); 
            this.base.__decode(binData, ref pos); 
            this.fight = new DictFightEffect(); 
            this.fight.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityDictArray : System.Collections.Generic.List<EntityDict>, Proto4z.IProtoObject  
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
                    var data = new EntityDict(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EPosition: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10010;  
        static public ushort getProtoID() { return 10010; } 
        static public string getProtoName() { return "EPosition"; } 
        //members   
        public double x;  
        public double y;  
        public double face;  
        public EPosition()  
        { 
            x = 0.0;  
            y = 0.0;  
            face = 0.0;  
        } 
        public EPosition(double x, double y, double face) 
        { 
            this.x = x; 
            this.y = y; 
            this.face = face; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.x)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.y)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.face)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.x = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.y = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.face = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EPositions : System.Collections.Generic.List<EPosition>, Proto4z.IProtoObject  
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
                    var data = new EPosition(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EntityInfo: Proto4z.IProtoObject //EntityInfo  
    {     
        //proto id   
        public const ushort protoID = 10011;  
        static public ushort getProtoID() { return 10011; } 
        static public string getProtoName() { return "EntityInfo"; } 
        //members   
        public uint eid; //eid  
        public ushort color; //阵营  
        public ushort state; //状态  
        public EPosition pos; //当前坐标  
        public ushort moveAction; //状态  
        public EPoints movePath; //当前的移动路径  
        public uint foe; //锁定的敌人  
        public uint leader; //实体的老大, 如果是飞行道具 这个指向施放飞行道具的人  
        public uint follow; //移动跟随的实体  
        public double curHP; //当前的血量  
        public EntityInfo()  
        { 
            eid = 0;  
            color = 0;  
            state = 0;  
            pos = new EPosition();  
            moveAction = 0;  
            movePath = new EPoints();  
            foe = 0;  
            leader = 0;  
            follow = 0;  
            curHP = 0.0;  
        } 
        public EntityInfo(uint eid, ushort color, ushort state, EPosition pos, ushort moveAction, EPoints movePath, uint foe, uint leader, uint follow, double curHP) 
        { 
            this.eid = eid; 
            this.color = color; 
            this.state = state; 
            this.pos = pos; 
            this.moveAction = moveAction; 
            this.movePath = movePath; 
            this.foe = foe; 
            this.leader = leader; 
            this.follow = follow; 
            this.curHP = curHP; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.color)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.state)); 
            if (this.pos == null) this.pos = new EPosition(); 
            data.AddRange(this.pos.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.moveAction)); 
            if (this.movePath == null) this.movePath = new EPoints(); 
            data.AddRange(this.movePath.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.foe)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.leader)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.follow)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.curHP)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.color = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.state = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.pos = new EPosition(); 
            this.pos.__decode(binData, ref pos); 
            this.moveAction = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.movePath = new EPoints(); 
            this.movePath.__decode(binData, ref pos); 
            this.foe = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.leader = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.follow = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.curHP = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityInfoArray : System.Collections.Generic.List<EntityInfo>, Proto4z.IProtoObject  
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
                    var data = new EntityInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EntityControl: Proto4z.IProtoObject //EntityControl  
    {     
        //proto id   
        public const ushort protoID = 10012;  
        static public ushort getProtoID() { return 10012; } 
        static public string getProtoName() { return "EntityControl"; } 
        //members   
        public uint eid; //eid  
        public uint stateChageTick; //状态改变时间  
        public double extSpeed; //扩展速度  
        public uint extBeginTick; //扩展速度的开始时间  
        public uint extKeepTick; //扩展速度的保持时间  
        public EPosition spawnpoint; //出生点  
        public EPoint lastPos; //上一帧实体坐标, 如果是瞬移 则和pos相同  
        public SkillInfoArray skills; //技能数据  
        public BuffInfoArray buffs; //BUFF数据, 小标ID对应bufftype  
        public uint diedTick; //实体死亡时间点 -1为永久, 仅飞行道具类有效  
        public int hitTimes; //实体碰撞 -1为永久, 仅飞行道具类有效  
        public uint lastMoveTick; //最后一次移动时间  
        public EPosition lastClientPos; //最后一次客户端提交的坐标  
        public EntityControl()  
        { 
            eid = 0;  
            stateChageTick = 0;  
            extSpeed = 0.0;  
            extBeginTick = 0;  
            extKeepTick = 0;  
            spawnpoint = new EPosition();  
            lastPos = new EPoint();  
            skills = new SkillInfoArray();  
            buffs = new BuffInfoArray();  
            diedTick = 0;  
            hitTimes = 0;  
            lastMoveTick = 0;  
            lastClientPos = new EPosition();  
        } 
        public EntityControl(uint eid, uint stateChageTick, double extSpeed, uint extBeginTick, uint extKeepTick, EPosition spawnpoint, EPoint lastPos, SkillInfoArray skills, BuffInfoArray buffs, uint diedTick, int hitTimes, uint lastMoveTick, EPosition lastClientPos) 
        { 
            this.eid = eid; 
            this.stateChageTick = stateChageTick; 
            this.extSpeed = extSpeed; 
            this.extBeginTick = extBeginTick; 
            this.extKeepTick = extKeepTick; 
            this.spawnpoint = spawnpoint; 
            this.lastPos = lastPos; 
            this.skills = skills; 
            this.buffs = buffs; 
            this.diedTick = diedTick; 
            this.hitTimes = hitTimes; 
            this.lastMoveTick = lastMoveTick; 
            this.lastClientPos = lastClientPos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.stateChageTick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.extSpeed)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.extBeginTick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.extKeepTick)); 
            if (this.spawnpoint == null) this.spawnpoint = new EPosition(); 
            data.AddRange(this.spawnpoint.__encode()); 
            if (this.lastPos == null) this.lastPos = new EPoint(); 
            data.AddRange(this.lastPos.__encode()); 
            if (this.skills == null) this.skills = new SkillInfoArray(); 
            data.AddRange(this.skills.__encode()); 
            if (this.buffs == null) this.buffs = new BuffInfoArray(); 
            data.AddRange(this.buffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.diedTick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.hitTimes)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.lastMoveTick)); 
            if (this.lastClientPos == null) this.lastClientPos = new EPosition(); 
            data.AddRange(this.lastClientPos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.stateChageTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.extSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.extBeginTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.extKeepTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.spawnpoint = new EPosition(); 
            this.spawnpoint.__decode(binData, ref pos); 
            this.lastPos = new EPoint(); 
            this.lastPos.__decode(binData, ref pos); 
            this.skills = new SkillInfoArray(); 
            this.skills.__decode(binData, ref pos); 
            this.buffs = new BuffInfoArray(); 
            this.buffs.__decode(binData, ref pos); 
            this.diedTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.hitTimes = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.lastMoveTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.lastClientPos = new EPosition(); 
            this.lastClientPos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityControlArray : System.Collections.Generic.List<EntityControl>, Proto4z.IProtoObject  
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
                    var data = new EntityControl(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EntityReport: Proto4z.IProtoObject //EntityReport  
    {     
        //proto id   
        public const ushort protoID = 10013;  
        static public ushort getProtoID() { return 10013; } 
        static public string getProtoName() { return "EntityReport"; } 
        //members   
        public uint eid; //eid  
        public uint killCount; //杀死其他玩家次数  
        public uint killTick; //杀死其他玩家的时间  
        public uint diedCount; //死亡次数  
        public uint topMultiKills; //最高连杀次数  
        public uint curMultiKills; //当前连杀次数  
        public EntityReport()  
        { 
            eid = 0;  
            killCount = 0;  
            killTick = 0;  
            diedCount = 0;  
            topMultiKills = 0;  
            curMultiKills = 0;  
        } 
        public EntityReport(uint eid, uint killCount, uint killTick, uint diedCount, uint topMultiKills, uint curMultiKills) 
        { 
            this.eid = eid; 
            this.killCount = killCount; 
            this.killTick = killTick; 
            this.diedCount = diedCount; 
            this.topMultiKills = topMultiKills; 
            this.curMultiKills = curMultiKills; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.killCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.killTick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.diedCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.topMultiKills)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.curMultiKills)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.killCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.killTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.diedCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.topMultiKills = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.curMultiKills = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityReportArray : System.Collections.Generic.List<EntityReport>, Proto4z.IProtoObject  
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
                    var data = new EntityReport(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EntityFullInfo: Proto4z.IProtoObject //EntityFullInfo  
    {     
        //proto id   
        public const ushort protoID = 10014;  
        static public ushort getProtoID() { return 10014; } 
        static public string getProtoName() { return "EntityFullInfo"; } 
        //members   
        public EntityDict dict;  
        public EntityInfo info;  
        public EntityReport report;  
        public EntityFullInfo()  
        { 
            dict = new EntityDict();  
            info = new EntityInfo();  
            report = new EntityReport();  
        } 
        public EntityFullInfo(EntityDict dict, EntityInfo info, EntityReport report) 
        { 
            this.dict = dict; 
            this.info = info; 
            this.report = report; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.dict == null) this.dict = new EntityDict(); 
            data.AddRange(this.dict.__encode()); 
            if (this.info == null) this.info = new EntityInfo(); 
            data.AddRange(this.info.__encode()); 
            if (this.report == null) this.report = new EntityReport(); 
            data.AddRange(this.report.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.dict = new EntityDict(); 
            this.dict.__decode(binData, ref pos); 
            this.info = new EntityInfo(); 
            this.info.__decode(binData, ref pos); 
            this.report = new EntityReport(); 
            this.report.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityFullInfoArray : System.Collections.Generic.List<EntityFullInfo>, Proto4z.IProtoObject  
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
                    var data = new EntityFullInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
} 
 
 
