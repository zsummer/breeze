 
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
        SCENE_STATUS_CHOISE = 2, //匹配成功,选择英雄  
        SCENE_STATUS_WAITING = 3, //匹配成功,等待玩家进入  
        SCENE_STATUS_INSTANCING = 4, //场景中  
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
        public string token; //令牌  
        public byte isActive; //当前活跃场景, 用于场景切换过渡,或者同时多个场景存在的情况  
        public UserBaseInfoArray involeds; //匹配列表中的玩家  
        public SceneInfo()  
        { 
            type = 0;  
            status = 0;  
            host = "";  
            port = 0;  
            spaceID = 0;  
            token = "";  
            isActive = 0;  
            involeds = new UserBaseInfoArray();  
        } 
        public SceneInfo(ushort type, ushort status, string host, ushort port, uint spaceID, string token, byte isActive, UserBaseInfoArray involeds) 
        { 
            this.type = type; 
            this.status = status; 
            this.host = host; 
            this.port = port; 
            this.spaceID = spaceID; 
            this.token = token; 
            this.isActive = isActive; 
            this.involeds = involeds; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.isActive)); 
            if (this.involeds == null) this.involeds = new UserBaseInfoArray(); 
            data.AddRange(this.involeds.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.isActive = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.involeds = new UserBaseInfoArray(); 
            this.involeds.__decode(binData, ref pos); 
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
 
    public enum SPACE_STATUS : ushort 
    { 
        SPACE_STATUS_FREE = 0, //自由  
        SCENE_STATUS_ACTIVE = 1, //活跃  
        SCENE_STATUS_LINGER = 2, //驻留  
    }; 
 
    public class SpaceInfo: Proto4z.IProtoObject //空间信息  
    {     
        //proto id   
        public const ushort protoID = 10017;  
        static public ushort getProtoID() { return 10017; } 
        static public string getProtoName() { return "SpaceInfo"; } 
        //members   
        public uint spaceID;  
        public ushort type; //类型  
        public ushort status; //状态  
        public uint users; //目前负载  
        public SpaceInfo()  
        { 
            spaceID = 0;  
            type = 0;  
            status = 0;  
            users = 0;  
        } 
        public SpaceInfo(uint spaceID, ushort type, ushort status, uint users) 
        { 
            this.spaceID = spaceID; 
            this.type = type; 
            this.status = status; 
            this.users = users; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.users)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.users = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SpaceInfoArray : System.Collections.Generic.List<SpaceInfo>, Proto4z.IProtoObject  
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
                    var data = new SpaceInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public enum ENTITY_STATE : ushort 
    { 
        ESTATE_NONE = 0, //无效  
        ESTATE_FREEZING = 1, //冻结, 不可被攻击,不可主动移动,攻击等  
        ESTATE_ACTIVE = 2, //活跃状态  
        ESTATE_LIE = 3, //跪, 不计死亡次数  
        ESTATE_DIED = 4, //死, 记死亡次数  
    }; 
 
    public enum ENTITY_TYPE : ushort 
    { 
        ETYPE_NONE = 0,  
        ETYPE_AVATAR = 1,  
        ETYPE_AI = 2,  
        ETYPE_FLIGHT = 3, //飞行道具  
    }; 
 
    public enum ENTITY_COLOR : ushort 
    { 
        ECOLOR_NONE = 0,  
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
 
    public enum SEARCH_METHOD : ushort 
    { 
        SEARCH_METHOD_DISTANCE = 0, //org 半径,360度扇形的优化  
        SEARCH_METHOD_SEACTOR = 1, //org 扇形  
        SEARCH_METHOD_RECT = 2, //org 矩形  
    }; 
 
    public enum SEARCH_TARGET : ulong 
    { 
        SEARCH_TARGET_NONE = 0, //无  
        SEARCH_TARGET_SELF = 1, //自身, 玩家或者AI  
        SEARCH_TARGET_ENEMY = 2, //敌人  
        SEARCH_TARGET_FRIEND = 3, //友方  
        SEARCH_TARGET_NEUTRAL = 4, //中立  
    }; 
 
    public enum SKILL_TYPE : ulong 
    { 
        SKILL_NONE = 0,  
        SKILL_AUTO = 1, //普攻  
        SKILL_PASSIVE = 2, //被动技能  
        SKILL_CAN_BREAK = 3, //可被中断  
        SKILL_CAN_MOVE = 4, //可移动  
        SKILL_PHYSICAL = 5, //物理攻击  
        SKILL_MAGIC = 6, //魔法攻击  
    }; 
 
    public enum SKILL_BEHAVIOUR : ulong 
    { 
        SKILL_BEHAVIOUR_NONE = 0,  
        SKILL_BEHAVIOUR_HIT = 1, //攻击  
        SKILL_BEHAVIOUR_TELEPORT_TARGET = 2, //瞬移到目标  
        SKILL_BEHAVIOUR_BREAK_MOVE = 3, //打断移动  
        SKILL_BEHAVIOUR_BREAK_SKILL = 4, //打断技能  
        SKILL_BEHAVIOUR_REMOVE_DEBUFF = 5, //驱散减益BUFF  
        SKILL_BEHAVIOUR_REMOVE_BUFF = 6, //驱散增益BUFF  
        SKILL_BEHAVIOUR_TRIGGER_BUFF = 7, //触发buff  
        SKILL_BEHAVIOUR_TRIGGER_SKILL = 8, //触发技能  
    }; 
 
    public enum BUFF_TYPE : ulong 
    { 
        BUFF_HALO = 1, //非表达可检索类型: 光环  
        BUFF_BUFF = 2, //非表达可检索类型: 增益buff  
        BUFF_DEBUFF = 3, //非表达可检索类型: 减益BUFF  
        BUFF_HIDE = 4, //非表达可检索类型: 客户端不表现  
        BUFF_SNEAK = 5, //潜行类型: 潜行 不会被非己方阵营的任何AOE技能搜索到  
        BUFF_HOLD_MOVE = 15, //控制: 禁止移动  
        BUFF_REVERSE_MOVE = 16, //控制: 移动反向  
        BUFF_SILENCE_AUTO_ATTACK = 17, //控制: 沉默普攻  
        BUFF_SILENCE_WITHOUT_AUTO_ATTACK = 18, //控制: 沉默非普攻技能  
        BUFF_SILENCE_PHYSICAL = 19, //控制: 沉默物理攻击  
        BUFF_SILENCE_MAGIC = 20, //控制: 沉默魔法攻击  
        BUFF_IMMUNE_MOVE = 25, //免疫: 免疫移动类控制  
        BUFF_IMMUNE_SILENCE = 26, //免疫: 免疫沉默  
        BUFF_IMMUNE_DEBUFF = 27, //免疫: 免疫添加DEBUFF, 指被地方添加不利buff  
        BUFF_IMMUNE_REMOVE_BUFF = 28, //免疫: 免疫驱散BUFF,指被敌方移除有益buff  
        BUFF_IMMUNE_PHYSICAL = 29, //免疫: 物攻免疫  
        BUFF_IMMUNE_MAGIC = 30, //免疫: 法攻免疫  
        BUFF_INC_HARM = 35, //属性加成: 最终扣血加成, value1加法, value2乘法  
        BUFF_INC_DAMAGE = 36, //属性加成: 伤害加成, value1加法, value2乘法  
        BUFF_INC_SPEED = 37, //属性加成: 速度加成, value1加法, value2乘法  
        BUFF_INC_SUCK_BLOOD = 38, //属性加成: 吸血加成 value1加法  
        BUFF_LIGHT_SKILL = 50, //持续性触发: value1为技能ID, value2为间隔, 用于光环类,持续触发类buff实现  
    }; 
 
    public class EPoint: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10018;  
        static public ushort getProtoID() { return 10018; } 
        static public string getProtoName() { return "EPoint"; } 
        //members   
        public double x;  
        public double y;  
        public EPoint()  
        { 
            x = 0.0;  
            y = 0.0;  
        } 
        public EPoint(double x, double y) 
        { 
            this.x = x; 
            this.y = y; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.x)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.y)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.x = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.y = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EPoints : System.Collections.Generic.List<EPoint>, Proto4z.IProtoObject  
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
                    var data = new EPoint(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
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
 
    public class SearchInfo: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10015;  
        static public ushort getProtoID() { return 10015; } 
        static public string getProtoName() { return "SearchInfo"; } 
        //members   
        public ushort searchMethod;  
        public ulong searchTarget;  
        public double rate; //概率  
        public double distance; //伤害距离  
        public double radian; //弧度或者宽度  
        public double offsetX; //坐标偏移量, 正数为x = x + offset  
        public double offsetY; //坐标偏移量, 正数为y = y + offset  
        public uint targetMaxCount; //最大目标数  
        public SearchInfo()  
        { 
            searchMethod = 0;  
            searchTarget = 0;  
            rate = 0.0;  
            distance = 0.0;  
            radian = 0.0;  
            offsetX = 0.0;  
            offsetY = 0.0;  
            targetMaxCount = 0;  
        } 
        public SearchInfo(ushort searchMethod, ulong searchTarget, double rate, double distance, double radian, double offsetX, double offsetY, uint targetMaxCount) 
        { 
            this.searchMethod = searchMethod; 
            this.searchTarget = searchTarget; 
            this.rate = rate; 
            this.distance = distance; 
            this.radian = radian; 
            this.offsetX = offsetX; 
            this.offsetY = offsetY; 
            this.targetMaxCount = targetMaxCount; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.searchMethod)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.searchTarget)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.rate)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.distance)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.radian)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.offsetX)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.offsetY)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.targetMaxCount)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.searchMethod = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.searchTarget = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.rate = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.distance = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.radian = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.offsetX = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.offsetY = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.targetMaxCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SkillBehaviour: Proto4z.IProtoObject //技能触发行为  
    {     
        //proto id   
        public const ushort protoID = 10016;  
        static public ushort getProtoID() { return 10016; } 
        static public string getProtoName() { return "SkillBehaviour"; } 
        //members   
        public ulong behaviour;  
        public double delay;  
        public SearchInfo search;  
        public SkillIDArray skills;  
        public BuffIDArray buffs;  
        public SkillBehaviour()  
        { 
            behaviour = 0;  
            delay = 0.0;  
            search = new SearchInfo();  
            skills = new SkillIDArray();  
            buffs = new BuffIDArray();  
        } 
        public SkillBehaviour(ulong behaviour, double delay, SearchInfo search, SkillIDArray skills, BuffIDArray buffs) 
        { 
            this.behaviour = behaviour; 
            this.delay = delay; 
            this.search = search; 
            this.skills = skills; 
            this.buffs = buffs; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.behaviour)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.delay)); 
            if (this.search == null) this.search = new SearchInfo(); 
            data.AddRange(this.search.__encode()); 
            if (this.skills == null) this.skills = new SkillIDArray(); 
            data.AddRange(this.skills.__encode()); 
            if (this.buffs == null) this.buffs = new BuffIDArray(); 
            data.AddRange(this.buffs.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.behaviour = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.delay = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.search = new SearchInfo(); 
            this.search.__decode(binData, ref pos); 
            this.skills = new SkillIDArray(); 
            this.skills.__decode(binData, ref pos); 
            this.buffs = new BuffIDArray(); 
            this.buffs.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SkillBehaviourArray : System.Collections.Generic.List<SkillBehaviour>, Proto4z.IProtoObject  
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
                    var data = new SkillBehaviour(); 
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
        public SkillBehaviourArray behaviours;  
        public double cd;  
        public SkillData()  
        { 
            skillID = 0;  
            skillType = 0;  
            behaviours = new SkillBehaviourArray();  
            cd = 0.0;  
        } 
        public SkillData(uint skillID, ulong skillType, SkillBehaviourArray behaviours, double cd) 
        { 
            this.skillID = skillID; 
            this.skillType = skillType; 
            this.behaviours = behaviours; 
            this.cd = cd; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillType)); 
            if (this.behaviours == null) this.behaviours = new SkillBehaviourArray(); 
            data.AddRange(this.behaviours.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.cd)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.skillType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.behaviours = new SkillBehaviourArray(); 
            this.behaviours.__decode(binData, ref pos); 
            this.cd = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public ulong buffType; //buff类型  
        public double piletime; //最大叠加时间  
        public double keepTime; //保持时间  
        public double value1;  
        public double value2;  
        public BuffData()  
        { 
            buffID = 0;  
            buffType = 0;  
            piletime = 0.0;  
            keepTime = 0.0;  
            value1 = 0.0;  
            value2 = 0.0;  
        } 
        public BuffData(uint buffID, ulong buffType, double piletime, double keepTime, double value1, double value2) 
        { 
            this.buffID = buffID; 
            this.buffType = buffType; 
            this.piletime = piletime; 
            this.keepTime = keepTime; 
            this.value1 = value1; 
            this.value2 = value2; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.buffID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.buffType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.piletime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.keepTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value1)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value2)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.buffID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.buffType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.piletime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.keepTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.value1 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.value2 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum HARM_TYPE : ushort 
    { 
        HARM_TYPE_GENERAL = 0, //普通伤害  
        HARM_TYPE_MISS = 1, //闪避  
        HARM_TYPE_CRITICAL = 2, //暴击  
        HARM_TYPE_HILL = 3, //治疗  
    }; 
 
    public class HarmData: Proto4z.IProtoObject //伤害数据  
    {     
        //proto id   
        public const ushort protoID = 10006;  
        static public ushort getProtoID() { return 10006; } 
        static public string getProtoName() { return "HarmData"; } 
        //members   
        public uint eid; //目标eid  
        public ushort type; //伤害类型HARM_TYPE  
        public double harm; //如果为正是伤害, 为负则是回血  
        public HarmData()  
        { 
            eid = 0;  
            type = 0;  
            harm = 0.0;  
        } 
        public HarmData(uint eid, ushort type, double harm) 
        { 
            this.eid = eid; 
            this.type = type; 
            this.harm = harm; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.harm)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.harm = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public double start; //start (server)tick  
        public double lastHitTick; //lastHitTick  
        public uint seq; //hit seq  
        public EPoint dst; //目标位置  
        public uint foe; //锁定的目标  
        public SkillData data; //配置数据  
        public SkillInfo()  
        { 
            skillID = 0;  
            start = 0.0;  
            lastHitTick = 0.0;  
            seq = 0;  
            dst = new EPoint();  
            foe = 0;  
            data = new SkillData();  
        } 
        public SkillInfo(uint skillID, double start, double lastHitTick, uint seq, EPoint dst, uint foe, SkillData data) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.start)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.lastHitTick)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.seq)); 
            if (this.dst == null) this.dst = new EPoint(); 
            data.AddRange(this.dst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.foe)); 
            if (this.data == null) this.data = new SkillData(); 
            data.AddRange(this.data.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.start = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.lastHitTick = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.seq = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.dst = new EPoint(); 
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
        public double start; //start (server)tick  
        public double lastTrigerTick; //lastTrigerTick  
        public BuffData data; //配置数据  
        public BuffInfo()  
        { 
            eid = 0;  
            skillID = 0;  
            buffID = 0;  
            start = 0.0;  
            lastTrigerTick = 0.0;  
            data = new BuffData();  
        } 
        public BuffInfo(uint eid, uint skillID, uint buffID, double start, double lastTrigerTick, BuffData data) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.start)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.lastTrigerTick)); 
            if (this.data == null) this.data = new BuffData(); 
            data.AddRange(this.data.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.skillID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.buffID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.start = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.lastTrigerTick = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public FightEffect fight; //战斗属性  
        public EntityDict()  
        { 
            serviceID = 0;  
            base = new UserBaseInfo();  
            fight = new FightEffect();  
        } 
        public EntityDict(ulong serviceID, UserBaseInfo base, FightEffect fight) 
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
            if (this.fight == null) this.fight = new FightEffect(); 
            data.AddRange(this.fight.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.base = new UserBaseInfo(); 
            this.base.__decode(binData, ref pos); 
            this.fight = new FightEffect(); 
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
        public EPoint pos; //当前坐标  
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
            pos = new EPoint();  
            moveAction = 0;  
            movePath = new EPoints();  
            foe = 0;  
            leader = 0;  
            follow = 0;  
            curHP = 0.0;  
        } 
        public EntityInfo(uint eid, ushort color, ushort state, EPoint pos, ushort moveAction, EPoints movePath, uint foe, uint leader, uint follow, double curHP) 
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
            if (this.pos == null) this.pos = new EPoint(); 
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
            this.pos = new EPoint(); 
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
        public EPoint spawnpoint; //出生点  
        public EPoint lastPos; //上一帧实体坐标, 如果是瞬移 则和pos相同  
        public SkillInfoArray skills; //技能数据  
        public BuffInfoArray buffs; //BUFF数据, 小标ID对应bufftype  
        public uint diedTick; //实体死亡时间点 -1为永久, 仅飞行道具类有效  
        public int hitTimes; //实体碰撞 -1为永久, 仅飞行道具类有效  
        public uint lastMoveTick; //最后一次移动时间  
        public EPoint lastClientPos; //最后一次客户端提交的坐标  
        public EntityControl()  
        { 
            eid = 0;  
            stateChageTick = 0;  
            extSpeed = 0.0;  
            extBeginTick = 0;  
            extKeepTick = 0;  
            spawnpoint = new EPoint();  
            lastPos = new EPoint();  
            skills = new SkillInfoArray();  
            buffs = new BuffInfoArray();  
            diedTick = 0;  
            hitTimes = 0;  
            lastMoveTick = 0;  
            lastClientPos = new EPoint();  
        } 
        public EntityControl(uint eid, uint stateChageTick, double extSpeed, uint extBeginTick, uint extKeepTick, EPoint spawnpoint, EPoint lastPos, SkillInfoArray skills, BuffInfoArray buffs, uint diedTick, int hitTimes, uint lastMoveTick, EPoint lastClientPos) 
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
            if (this.spawnpoint == null) this.spawnpoint = new EPoint(); 
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
            if (this.lastClientPos == null) this.lastClientPos = new EPoint(); 
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
            this.spawnpoint = new EPoint(); 
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
            this.lastClientPos = new EPoint(); 
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
 
 
