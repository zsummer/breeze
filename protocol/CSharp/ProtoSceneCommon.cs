 
namespace Proto4z  
{ 
 
    public enum SceneType : ushort 
    { 
        SCENE_NONE = 0, //无效  
        SCENE_HOME = 1, //主城  
        SCENE_MELEE = 2, //乱斗场  
        SCENE_ARENA = 3, //竞技场  
        SCENE_GUILD = 4, //公会  
        SCENE_MASTER_INSTANCING = 5, //主线副本  
        SCENE_BRANCH_INSTANCING = 6, //支线副本  
        SCENE_MAX = 7, //最大类型数值. 扩展类型在该枚举之前插入新类型.  
    }; 
 
    public enum SceneState : ushort 
    { 
        SCENE_STATE_NONE = 0, //不存在  
        SCENE_STATE_MATCHING = 1, //匹配中  
        SCENE_STATE_CHOISE = 2, //选择英雄  
        SCENE_STATE_ALLOCATE = 3, //服务器分配场景中  
        SCENE_STATE_WAIT = 4, //等待玩家加入战场  
        SCENE_STATE_ACTIVE = 5, //战斗中  
    }; 
 
    public class SceneGroupAvatarInfo: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10000;  
        static public ushort getProtoID() { return 10000; } 
        static public string getProtoName() { return "SceneGroupAvatarInfo"; } 
        //members   
        public ulong areaID; //考虑混服情况,必须指定该玩家来自哪个当前区  
        public AvatarBaseInfo baseInfo; //玩家基础数据  
        public AvatarPropMap baseProps; //角色属性数据  
        public ushort powerType; //组队权限: 0普通,1leader,2master  
        public string token; //scene服务器的口令, 该字段在广播给客户端时需要清空非自己所属的token,否则将会造成token公开.  
        public SceneGroupAvatarInfo()  
        { 
            areaID = 0;  
            baseInfo = new AvatarBaseInfo();  
            baseProps = new AvatarPropMap();  
            powerType = 0;  
            token = "";  
        } 
        public SceneGroupAvatarInfo(ulong areaID, AvatarBaseInfo baseInfo, AvatarPropMap baseProps, ushort powerType, string token) 
        { 
            this.areaID = areaID; 
            this.baseInfo = baseInfo; 
            this.baseProps = baseProps; 
            this.powerType = powerType; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.areaID)); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.baseProps == null) this.baseProps = new AvatarPropMap(); 
            data.AddRange(this.baseProps.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.powerType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.areaID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.baseProps = new AvatarPropMap(); 
            this.baseProps.__decode(binData, ref pos); 
            this.powerType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SceneGroupAvatarInfoArray : System.Collections.Generic.List<SceneGroupAvatarInfo>, Proto4z.IProtoObject  
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
                    var data = new SceneGroupAvatarInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class SceneGroupAvatarInfoMap : System.Collections.Generic.Dictionary<ulong, SceneGroupAvatarInfo>, Proto4z.IProtoObject  
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
                    var val = new SceneGroupAvatarInfo(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class SceneGroupInfo: Proto4z.IProtoObject //编队数据  
    {     
        //proto id   
        public const ushort protoID = 10001;  
        static public ushort getProtoID() { return 10001; } 
        static public string getProtoName() { return "SceneGroupInfo"; } 
        //members   
        public ulong groupID;  
        public ushort sceneType; //场景类型  
        public ushort sceneState; //状态  
        public ulong mapID;  
        public ulong lineID; //分线ID  
        public ulong sceneID; //场景实例ID  
        public string host; //服务器host  
        public ushort port; //服务器port  
        public SceneGroupAvatarInfoMap members; //队友数据  
        public ServiceIDMap invitees; //邀请列表, 如果需要丰富该功能可扩展类型信息  
        public SceneGroupInfo()  
        { 
            groupID = 0;  
            sceneType = 0;  
            sceneState = 0;  
            mapID = 0;  
            lineID = 0;  
            sceneID = 0;  
            host = "";  
            port = 0;  
            members = new SceneGroupAvatarInfoMap();  
            invitees = new ServiceIDMap();  
        } 
        public SceneGroupInfo(ulong groupID, ushort sceneType, ushort sceneState, ulong mapID, ulong lineID, ulong sceneID, string host, ushort port, SceneGroupAvatarInfoMap members, ServiceIDMap invitees) 
        { 
            this.groupID = groupID; 
            this.sceneType = sceneType; 
            this.sceneState = sceneState; 
            this.mapID = mapID; 
            this.lineID = lineID; 
            this.sceneID = sceneID; 
            this.host = host; 
            this.port = port; 
            this.members = members; 
            this.invitees = invitees; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneState)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.mapID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.lineID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            if (this.members == null) this.members = new SceneGroupAvatarInfoMap(); 
            data.AddRange(this.members.__encode()); 
            if (this.invitees == null) this.invitees = new ServiceIDMap(); 
            data.AddRange(this.invitees.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.sceneState = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.lineID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.members = new SceneGroupAvatarInfoMap(); 
            this.members.__decode(binData, ref pos); 
            this.invitees = new ServiceIDMap(); 
            this.invitees.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SceneGroupInfoArray : System.Collections.Generic.List<SceneGroupInfo>, Proto4z.IProtoObject  
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
                    var data = new SceneGroupInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class SceneGroupInfoMap : System.Collections.Generic.Dictionary<ulong, SceneGroupInfo>, Proto4z.IProtoObject  
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
                    var val = new SceneGroupInfo(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class EntityIDArray : System.Collections.Generic.List<ulong>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI64(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class EPosition: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10002;  
        static public ushort getProtoID() { return 10002; } 
        static public string getProtoName() { return "EPosition"; } 
        //members   
        public double x;  
        public double y;  
        public EPosition()  
        { 
            x = 0.0;  
            y = 0.0;  
        } 
        public EPosition(double x, double y) 
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
 
 
    public class EPositionArray : System.Collections.Generic.List<EPosition>, Proto4z.IProtoObject  
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
 
 
    public class SkillIDArray : System.Collections.Generic.List<ulong>, Proto4z.IProtoObject //技能ID数组  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI64(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class BuffIDArray : System.Collections.Generic.List<ulong>, Proto4z.IProtoObject //buff ID 数组  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI64(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public enum EntityState : ushort 
    { 
        ENTITY_STATE_NONE = 0, //无效  
        ENTITY_STATE_FREEZING = 1, //冻结, 不可被攻击,不可主动移动,攻击等  
        ENTITY_STATE_ACTIVE = 2, //活跃状态  
        ENTITY_STATE_LIE = 3, //跪, 不计死亡次数  
        ENTITY_STATE_DIED = 4, //死, 记死亡次数  
    }; 
 
    public enum EntityType : ushort 
    { 
        ENTITY_NONE = 0,  
        ENTITY_PLAYER = 1,  
        ENTITY_AI = 2,  
        ENTITY_FLIGHT = 3, //飞行道具  
    }; 
 
    public enum EntityCampType : ushort 
    { 
        ENTITY_CAMP_NONE = 0,  
        ENTITY_CAMP_RED = 1, //红方  
        ENTITY_CAMP_BLUE = 2, //蓝方  
        ENTITY_CAMP_NEUTRAL = 1000, //[0~ENTITY_CAMP_NEUTRAL)阵营相互敌对, [ENTITY_CAMP_NEUTRAL~)中立温和阵营  
    }; 
 
    public enum MoveAction : ushort 
    { 
        MOVE_ACTION_IDLE = 0, //空闲  
        MOVE_ACTION_FOLLOW = 1, //跟随  
        MOVE_ACTION_PATH = 2, //路径  
        MOVE_ACTION_PASV_PATH = 3, //不可取消, 直线移动一次.  
        MOVE_ACTION_FORCE_PATH = 4, //不可取消&穿越地形, 直线移动一次  
    }; 
 
    public enum SearchMethodType : ushort 
    { 
        SEARCH_METHOD_SEACTOR = 0, //org 扇形  
        SEARCH_METHOD_RECT = 1, //org 矩形  
    }; 
 
    public enum SearchCampType : ulong 
    { 
        SEARCH_CAMP_NONE = 0,  
        SEARCH_CAMP_SELF = 1, //自身  
        SEARCH_CAMP_SAME_WITHOUT_SELF = 2, //同阵营非自己  
        SEARCH_CAMP_ALIEN = 3, //非己方阵营  
    }; 
 
    public enum SkillType : ulong 
    { 
        SKILL_NONE = 0,  
        SKILL_AUTO = 1, //自动循环攻击  
        SKILL_PASSIVE = 2, //被动技能  
        SKILL_CAN_BREAK = 3, //可被中断  
        SKILL_CAN_MOVE = 4, //可移动  
        SKILL_PHYSICAL = 5, //物理攻击  
        SKILL_MAGIC = 6, //魔法攻击  
    }; 
 
    public enum SkillBehaviourType : ulong 
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
 
    public enum BuffType : ulong 
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
 
    public class SearchInfo: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10003;  
        static public ushort getProtoID() { return 10003; } 
        static public string getProtoName() { return "SearchInfo"; } 
        //members   
        public ushort etype; //实体类型, 玩家/AI 或者是NONE忽略该选项  
        public ulong camp; //0忽略改选项, 1位标识自己, 2位标识同阵营非自己, 3其他阵营,   逗号分割 多选 SearchCampType  
        public ushort method; //0扇形, 1矩形 SearchMethodType  
        public double distance; //伤害距离  
        public double radian; //弧度或者宽度  
        public double offsetX; //坐标偏移量, 以caster为原点, 朝向为y轴  
        public double offsetY; //坐标偏移量, 以caster为原点, 朝向为y轴  
        public ulong limitEntitys; //最大目标数  
        public SearchInfo()  
        { 
            etype = 0;  
            camp = 0;  
            method = 0;  
            distance = 0.0;  
            radian = 0.0;  
            offsetX = 0.0;  
            offsetY = 0.0;  
            limitEntitys = 0;  
        } 
        public SearchInfo(ushort etype, ulong camp, ushort method, double distance, double radian, double offsetX, double offsetY, ulong limitEntitys) 
        { 
            this.etype = etype; 
            this.camp = camp; 
            this.method = method; 
            this.distance = distance; 
            this.radian = radian; 
            this.offsetX = offsetX; 
            this.offsetY = offsetY; 
            this.limitEntitys = limitEntitys; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.etype)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.camp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.method)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.distance)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.radian)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.offsetX)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.offsetY)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.limitEntitys)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.etype = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.camp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.method = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.distance = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.radian = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.offsetX = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.offsetY = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.limitEntitys = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SkillBehaviour: Proto4z.IProtoObject //技能触发行为  
    {     
        //proto id   
        public const ushort protoID = 10004;  
        static public ushort getProtoID() { return 10004; } 
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
        public const ushort protoID = 10005;  
        static public ushort getProtoID() { return 10005; } 
        static public string getProtoName() { return "SkillData"; } 
        //members   
        public ulong skillID; //skillID  
        public ulong skillType; //SkillType  
        public SkillBehaviourArray behaviours;  
        public double cd;  
        public SkillData()  
        { 
            skillID = 0;  
            skillType = 0;  
            behaviours = new SkillBehaviourArray();  
            cd = 0.0;  
        } 
        public SkillData(ulong skillID, ulong skillType, SkillBehaviourArray behaviours, double cd) 
        { 
            this.skillID = skillID; 
            this.skillType = skillType; 
            this.behaviours = behaviours; 
            this.cd = cd; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillType)); 
            if (this.behaviours == null) this.behaviours = new SkillBehaviourArray(); 
            data.AddRange(this.behaviours.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.cd)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
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
        public const ushort protoID = 10006;  
        static public ushort getProtoID() { return 10006; } 
        static public string getProtoName() { return "BuffData"; } 
        //members   
        public ulong buffID;  
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
        public BuffData(ulong buffID, ulong buffType, double piletime, double keepTime, double value1, double value2) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.buffID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.buffType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.piletime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.keepTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value1)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.value2)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.buffID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.buffType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.piletime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.keepTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.value1 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.value2 = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum SceneEvent : ushort 
    { 
        SCENE_EVENT_LIE = 0,  
        SCENE_EVENT_DIED = 1,  
        SCENE_EVENT_FREEZE = 2,  
        SCENE_EVENT_REBIRTH = 3,  
        SCENE_EVENT_HARM_ATTACK = 4,  
        SCENE_EVENT_HARM_HILL = 5,  
        SCENE_EVENT_HARM_MISS = 6,  
        SCENE_EVENT_HARM_CRITICAL = 7,  
    }; 
 
    public class SceneEventInfo: Proto4z.IProtoObject //伤害数据  
    {     
        //proto id   
        public const ushort protoID = 10015;  
        static public ushort getProtoID() { return 10015; } 
        static public string getProtoName() { return "SceneEventInfo"; } 
        //members   
        public ulong src; //eid  
        public ulong dst; //eid  
        public ushort ev; //事件类型  
        public double val; //数值  
        public SceneEventInfo()  
        { 
            src = 0;  
            dst = 0;  
            ev = 0;  
            val = 0.0;  
        } 
        public SceneEventInfo(ulong src, ulong dst, ushort ev, double val) 
        { 
            this.src = src; 
            this.dst = dst; 
            this.ev = ev; 
            this.val = val; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.src)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dst)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.ev)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.val)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.src = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.ev = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.val = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SceneEventInfoArray : System.Collections.Generic.List<SceneEventInfo>, Proto4z.IProtoObject  
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
                    var data = new SceneEventInfo(); 
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
        public const ushort protoID = 10008;  
        static public ushort getProtoID() { return 10008; } 
        static public string getProtoName() { return "SkillInfo"; } 
        //members   
        public ulong skillID;  
        public double startTime;  
        public EPosition dst; //目标位置  
        public ulong foe; //锁定的目标  
        public SkillData data; //配置数据  
        public SkillInfo()  
        { 
            skillID = 0;  
            startTime = 0.0;  
            dst = new EPosition();  
            foe = 0;  
            data = new SkillData();  
        } 
        public SkillInfo(ulong skillID, double startTime, EPosition dst, ulong foe, SkillData data) 
        { 
            this.skillID = skillID; 
            this.startTime = startTime; 
            this.dst = dst; 
            this.foe = foe; 
            this.data = data; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.startTime)); 
            if (this.dst == null) this.dst = new EPosition(); 
            data.AddRange(this.dst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.foe)); 
            if (this.data == null) this.data = new SkillData(); 
            data.AddRange(this.data.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.startTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.dst = new EPosition(); 
            this.dst.__decode(binData, ref pos); 
            this.foe = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
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
        public const ushort protoID = 10009;  
        static public ushort getProtoID() { return 10009; } 
        static public string getProtoName() { return "BuffInfo"; } 
        //members   
        public ulong eid; //施放该buff的entity id  
        public ulong skillID; //如果该buff是被技能触发的 则记录该技能, 被动技能是0  
        public ulong buffID;  
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
        public BuffInfo(ulong eid, ulong skillID, ulong buffID, double start, double lastTrigerTick, BuffData data) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.buffID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.start)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.lastTrigerTick)); 
            if (this.data == null) this.data = new BuffData(); 
            data.AddRange(this.data.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skillID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.buffID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
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
 
    public class EntityInfo: Proto4z.IProtoObject //EntityInfo  
    {     
        //proto id   
        public const ushort protoID = 10010;  
        static public ushort getProtoID() { return 10010; } 
        static public string getProtoName() { return "EntityInfo"; } 
        //members   
        public ulong eid; //eid  
        public ushort camp; //阵营  
        public ulong groupID; //组队ID  
        public ushort etype; //实体类型  
        public ushort state; //状态  
        public ulong foe; //锁定的敌人  
        public ulong leader; //实体的老大, 如果是飞行道具 这个指向施放飞行道具的人  
        public double curHP; //当前的血量  
        public EntityInfo()  
        { 
            eid = 0;  
            camp = 0;  
            groupID = 0;  
            etype = 0;  
            state = 0;  
            foe = 0;  
            leader = 0;  
            curHP = 0.0;  
        } 
        public EntityInfo(ulong eid, ushort camp, ulong groupID, ushort etype, ushort state, ulong foe, ulong leader, double curHP) 
        { 
            this.eid = eid; 
            this.camp = camp; 
            this.groupID = groupID; 
            this.etype = etype; 
            this.state = state; 
            this.foe = foe; 
            this.leader = leader; 
            this.curHP = curHP; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.camp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.etype)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.state)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.foe)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.leader)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.curHP)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.camp = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.etype = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.state = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.foe = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.leader = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
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
 
    public class EntityMove: Proto4z.IProtoObject //EntityMove  
    {     
        //proto id   
        public const ushort protoID = 10011;  
        static public ushort getProtoID() { return 10011; } 
        static public string getProtoName() { return "EntityMove"; } 
        //members   
        public ulong eid; //eid  
        public EPosition position; //当前坐标  
        public ushort action; //移动状态  
        public double realSpeed; //实时速度  
        public double expectSpeed; //期望速度  
        public EPositionArray waypoints; //移动路点  
        public ulong follow; //eid  
        public EntityMove()  
        { 
            eid = 0;  
            position = new EPosition();  
            action = 0;  
            realSpeed = 0.0;  
            expectSpeed = 0.0;  
            waypoints = new EPositionArray();  
            follow = 0;  
        } 
        public EntityMove(ulong eid, EPosition position, ushort action, double realSpeed, double expectSpeed, EPositionArray waypoints, ulong follow) 
        { 
            this.eid = eid; 
            this.position = position; 
            this.action = action; 
            this.realSpeed = realSpeed; 
            this.expectSpeed = expectSpeed; 
            this.waypoints = waypoints; 
            this.follow = follow; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            if (this.position == null) this.position = new EPosition(); 
            data.AddRange(this.position.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.action)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.realSpeed)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.expectSpeed)); 
            if (this.waypoints == null) this.waypoints = new EPositionArray(); 
            data.AddRange(this.waypoints.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.follow)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.position = new EPosition(); 
            this.position.__decode(binData, ref pos); 
            this.action = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.realSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.expectSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.waypoints = new EPositionArray(); 
            this.waypoints.__decode(binData, ref pos); 
            this.follow = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityMoveArray : System.Collections.Generic.List<EntityMove>, Proto4z.IProtoObject  
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
                    var data = new EntityMove(); 
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
        public const ushort protoID = 10012;  
        static public ushort getProtoID() { return 10012; } 
        static public string getProtoName() { return "EntityReport"; } 
        //members   
        public ulong eid; //eid  
        public ulong killOtherCount; //杀死其他玩家次数  
        public ulong killOtherTime; //杀死其他玩家的时间  
        public ulong diedCount; //死亡次数  
        public ulong topMultiKills; //最高连杀次数  
        public ulong curMultiKills; //当前连杀次数  
        public EntityReport()  
        { 
            eid = 0;  
            killOtherCount = 0;  
            killOtherTime = 0;  
            diedCount = 0;  
            topMultiKills = 0;  
            curMultiKills = 0;  
        } 
        public EntityReport(ulong eid, ulong killOtherCount, ulong killOtherTime, ulong diedCount, ulong topMultiKills, ulong curMultiKills) 
        { 
            this.eid = eid; 
            this.killOtherCount = killOtherCount; 
            this.killOtherTime = killOtherTime; 
            this.diedCount = diedCount; 
            this.topMultiKills = topMultiKills; 
            this.curMultiKills = curMultiKills; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.killOtherCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.killOtherTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.diedCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.topMultiKills)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.curMultiKills)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.killOtherCount = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.killOtherTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.diedCount = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.topMultiKills = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.curMultiKills = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
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
 
    public class EntityFullData: Proto4z.IProtoObject //EntityFullData  
    {     
        //proto id   
        public const ushort protoID = 10013;  
        static public ushort getProtoID() { return 10013; } 
        static public string getProtoName() { return "EntityFullData"; } 
        //members   
        public AvatarBaseInfo baseInfo;  
        public AvatarPropMap baseProps;  
        public EntityInfo entityInfo;  
        public EntityMove entityMove;  
        public EntityReport report;  
        public EntityFullData()  
        { 
            baseInfo = new AvatarBaseInfo();  
            baseProps = new AvatarPropMap();  
            entityInfo = new EntityInfo();  
            entityMove = new EntityMove();  
            report = new EntityReport();  
        } 
        public EntityFullData(AvatarBaseInfo baseInfo, AvatarPropMap baseProps, EntityInfo entityInfo, EntityMove entityMove, EntityReport report) 
        { 
            this.baseInfo = baseInfo; 
            this.baseProps = baseProps; 
            this.entityInfo = entityInfo; 
            this.entityMove = entityMove; 
            this.report = report; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.baseProps == null) this.baseProps = new AvatarPropMap(); 
            data.AddRange(this.baseProps.__encode()); 
            if (this.entityInfo == null) this.entityInfo = new EntityInfo(); 
            data.AddRange(this.entityInfo.__encode()); 
            if (this.entityMove == null) this.entityMove = new EntityMove(); 
            data.AddRange(this.entityMove.__encode()); 
            if (this.report == null) this.report = new EntityReport(); 
            data.AddRange(this.report.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.baseProps = new AvatarPropMap(); 
            this.baseProps.__decode(binData, ref pos); 
            this.entityInfo = new EntityInfo(); 
            this.entityInfo.__decode(binData, ref pos); 
            this.entityMove = new EntityMove(); 
            this.entityMove.__decode(binData, ref pos); 
            this.report = new EntityReport(); 
            this.report.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityFullDataArray : System.Collections.Generic.List<EntityFullData>, Proto4z.IProtoObject  
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
                    var data = new EntityFullData(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class SceneSection: Proto4z.IProtoObject //场景全景切片数据  
    {     
        //proto id   
        public const ushort protoID = 10014;  
        static public ushort getProtoID() { return 10014; } 
        static public string getProtoName() { return "SceneSection"; } 
        //members   
        public ulong sceneID;  
        public ushort sceneType;  
        public ushort sceneState;  
        public double sceneStartTime; //服务器战场开始时间  
        public double sceneEndTime; //服务器战场结束时间  
        public double serverTime; //服务器当前时间  
        public EntityFullDataArray entitys; //这里包含有所有当前场景下的实体属性和状态数据  
        public SceneSection()  
        { 
            sceneID = 0;  
            sceneType = 0;  
            sceneState = 0;  
            sceneStartTime = 0.0;  
            sceneEndTime = 0.0;  
            serverTime = 0.0;  
            entitys = new EntityFullDataArray();  
        } 
        public SceneSection(ulong sceneID, ushort sceneType, ushort sceneState, double sceneStartTime, double sceneEndTime, double serverTime, EntityFullDataArray entitys) 
        { 
            this.sceneID = sceneID; 
            this.sceneType = sceneType; 
            this.sceneState = sceneState; 
            this.sceneStartTime = sceneStartTime; 
            this.sceneEndTime = sceneEndTime; 
            this.serverTime = serverTime; 
            this.entitys = entitys; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneState)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.sceneStartTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.sceneEndTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            if (this.entitys == null) this.entitys = new EntityFullDataArray(); 
            data.AddRange(this.entitys.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.sceneState = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.sceneStartTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.sceneEndTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.entitys = new EntityFullDataArray(); 
            this.entitys.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
