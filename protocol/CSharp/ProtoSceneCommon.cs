 
namespace Proto4z  
{ 
 
    public enum SCENE_TYPE : ushort 
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
 
    public enum SCENE_STATE : ushort 
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
        public const ushort protoID = 2000;  
        static public ushort getProtoID() { return 2000; } 
        static public string getProtoName() { return "SceneGroupAvatarInfo"; } 
        //members   
        public ulong areaID; //考虑混服情况,必须指定该玩家来自哪个当前区  
        public ulong modelID; //模型ID  
        public DictArrayKey equips; //额外装备  
        public ulong avatarID;  
        public string avatarName;  
        public double rankScore; //天梯分数  
        public ushort powerType; //组队权限: 0普通,1leader,2master  
        public string token; //scene服务器的口令, 该字段在广播给客户端时需要清空非自己所属的token,否则将会造成token公开.  
        public SceneGroupAvatarInfo()  
        { 
            areaID = 0;  
            modelID = 0;  
            equips = new DictArrayKey();  
            avatarID = 0;  
            avatarName = "";  
            rankScore = 0.0;  
            powerType = 0;  
            token = "";  
        } 
        public SceneGroupAvatarInfo(ulong areaID, ulong modelID, DictArrayKey equips, ulong avatarID, string avatarName, double rankScore, ushort powerType, string token) 
        { 
            this.areaID = areaID; 
            this.modelID = modelID; 
            this.equips = equips; 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.rankScore = rankScore; 
            this.powerType = powerType; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.areaID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modelID)); 
            if (this.equips == null) this.equips = new DictArrayKey(); 
            data.AddRange(this.equips.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.rankScore)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.powerType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.areaID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.equips = new DictArrayKey(); 
            this.equips.__decode(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.rankScore = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public const ushort protoID = 2001;  
        static public ushort getProtoID() { return 2001; } 
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
        public const ushort protoID = 2002;  
        static public ushort getProtoID() { return 2002; } 
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
 
    public enum ENTITY_STATE : ushort 
    { 
        ENTITY_STATE_NONE = 0, //无效  
        ENTITY_STATE_FREEZING = 1, //冻结, 不可被攻击,不可主动移动,攻击等  
        ENTITY_STATE_ACTIVE = 2, //活跃状态  
        ENTITY_STATE_LIE = 3, //跪, 不计死亡次数  
        ENTITY_STATE_DIED = 4, //死, 记死亡次数  
    }; 
 
    public enum ENTITY_TYPE : ushort 
    { 
        ENTITY_NONE = 0,  
        ENTITY_PLAYER = 1,  
        ENTITY_AI = 2,  
        ENTITY_FLIGHT = 3, //飞行道具  
    }; 
 
    public enum ENTITY_CAMP : ulong 
    { 
        ENTITY_CAMP_NONE = 0,  
        ENTITY_CAMP_RED = 1, //红方  
        ENTITY_CAMP_BLUE = 2, //蓝方  
        ENTITY_CAMP_NEUTRAL = 1000, //[0~ENTITY_CAMP_NEUTRAL)阵营相互敌对, [ENTITY_CAMP_NEUTRAL~)中立温和阵营  
    }; 
 
    public enum MOVE_ACTION : ushort 
    { 
        MOVE_ACTION_IDLE = 0, //空闲  
        MOVE_ACTION_FOLLOW = 1, //跟随  
        MOVE_ACTION_PATH = 2, //路径  
        MOVE_ACTION_PASV_PATH = 3, //不可取消, 直线移动一次.  
        MOVE_ACTION_FORCE_PATH = 4, //不可取消&穿越地形, 直线移动一次  
    }; 
 
    public enum SCENE_EVENT : ushort 
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
        public const ushort protoID = 2003;  
        static public ushort getProtoID() { return 2003; } 
        static public string getProtoName() { return "SceneEventInfo"; } 
        //members   
        public ulong src; //eid  
        public ulong dst; //eid  
        public ushort ev; //事件类型  
        public double val; //数值  
        public string mix; //数值  
        public SceneEventInfo()  
        { 
            src = 0;  
            dst = 0;  
            ev = 0;  
            val = 0.0;  
            mix = "";  
        } 
        public SceneEventInfo(ulong src, ulong dst, ushort ev, double val, string mix) 
        { 
            this.src = src; 
            this.dst = dst; 
            this.ev = ev; 
            this.val = val; 
            this.mix = mix; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.src)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dst)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.ev)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.val)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.mix)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.src = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.ev = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.val = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.mix = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
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
 
    public class EntityState: Proto4z.IProtoObject //EntityState  
    {     
        //proto id   
        public const ushort protoID = 2004;  
        static public ushort getProtoID() { return 2004; } 
        static public string getProtoName() { return "EntityState"; } 
        //members   
        public ulong eid;  
        public ulong avatarID;  
        public string avatarName;  
        public ulong modelID;  
        public double collision; //collision radius  
        public ushort camp; //阵营  
        public ulong groupID; //组队ID  
        public ushort etype; //实体类型  
        public ushort state; //状态  
        public ulong foe; //锁定的敌人  
        public ulong master; //如果是飞行道具 这个指向施放飞行道具的人  
        public double curHP; //当前的血量  
        public double maxHP; //当前的血量上限  
        public EntityState()  
        { 
            eid = 0;  
            avatarID = 0;  
            avatarName = "";  
            modelID = 0;  
            collision = 0.0;  
            camp = 0;  
            groupID = 0;  
            etype = 0;  
            state = 0;  
            foe = 0;  
            master = 0;  
            curHP = 0.0;  
            maxHP = 0.0;  
        } 
        public EntityState(ulong eid, ulong avatarID, string avatarName, ulong modelID, double collision, ushort camp, ulong groupID, ushort etype, ushort state, ulong foe, ulong master, double curHP, double maxHP) 
        { 
            this.eid = eid; 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.modelID = modelID; 
            this.collision = collision; 
            this.camp = camp; 
            this.groupID = groupID; 
            this.etype = etype; 
            this.state = state; 
            this.foe = foe; 
            this.master = master; 
            this.curHP = curHP; 
            this.maxHP = maxHP; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.collision)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.camp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.etype)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.state)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.foe)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.master)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.curHP)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.maxHP)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.modelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.collision = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.camp = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.etype = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.state = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.foe = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.master = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.curHP = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.maxHP = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class EntityStateArray : System.Collections.Generic.List<EntityState>, Proto4z.IProtoObject  
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
                    var data = new EntityState(); 
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
        public const ushort protoID = 2005;  
        static public ushort getProtoID() { return 2005; } 
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
        public const ushort protoID = 2006;  
        static public ushort getProtoID() { return 2006; } 
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
        public const ushort protoID = 2007;  
        static public ushort getProtoID() { return 2007; } 
        static public string getProtoName() { return "EntityFullData"; } 
        //members   
        public DictProp props; //战斗属性  
        public EntityState state;  
        public EntityMove mv;  
        public EntityReport report;  
        public EntityFullData()  
        { 
            props = new DictProp();  
            state = new EntityState();  
            mv = new EntityMove();  
            report = new EntityReport();  
        } 
        public EntityFullData(DictProp props, EntityState state, EntityMove mv, EntityReport report) 
        { 
            this.props = props; 
            this.state = state; 
            this.mv = mv; 
            this.report = report; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.props == null) this.props = new DictProp(); 
            data.AddRange(this.props.__encode()); 
            if (this.state == null) this.state = new EntityState(); 
            data.AddRange(this.state.__encode()); 
            if (this.mv == null) this.mv = new EntityMove(); 
            data.AddRange(this.mv.__encode()); 
            if (this.report == null) this.report = new EntityReport(); 
            data.AddRange(this.report.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.props = new DictProp(); 
            this.props.__decode(binData, ref pos); 
            this.state = new EntityState(); 
            this.state.__decode(binData, ref pos); 
            this.mv = new EntityMove(); 
            this.mv.__decode(binData, ref pos); 
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
        public const ushort protoID = 2008;  
        static public ushort getProtoID() { return 2008; } 
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
 
    public class EntitySkillInfo: Proto4z.IProtoObject //技能  
    {     
        //proto id   
        public const ushort protoID = 2009;  
        static public ushort getProtoID() { return 2009; } 
        static public string getProtoName() { return "EntitySkillInfo"; } 
        //members   
        public ulong skillID;  
        public EPosition activeOrg;  
        public ulong activeOrgEID;  
        public EPosition activeDst;  
        public ushort activeFoeFirst;  
        public double activeTime;  
        public double lastTriggerTime;  
        public ushort isFinish;  
        public double activeCount;  
        public EntitySkillInfo()  
        { 
            skillID = 0;  
            activeOrg = new EPosition();  
            activeOrgEID = 0;  
            activeDst = new EPosition();  
            activeFoeFirst = 0;  
            activeTime = 0.0;  
            lastTriggerTime = 0.0;  
            isFinish = 0;  
            activeCount = 0.0;  
        } 
        public EntitySkillInfo(ulong skillID, EPosition activeOrg, ulong activeOrgEID, EPosition activeDst, ushort activeFoeFirst, double activeTime, double lastTriggerTime, ushort isFinish, double activeCount) 
        { 
            this.skillID = skillID; 
            this.activeOrg = activeOrg; 
            this.activeOrgEID = activeOrgEID; 
            this.activeDst = activeDst; 
            this.activeFoeFirst = activeFoeFirst; 
            this.activeTime = activeTime; 
            this.lastTriggerTime = lastTriggerTime; 
            this.isFinish = isFinish; 
            this.activeCount = activeCount; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillID)); 
            if (this.activeOrg == null) this.activeOrg = new EPosition(); 
            data.AddRange(this.activeOrg.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.activeOrgEID)); 
            if (this.activeDst == null) this.activeDst = new EPosition(); 
            data.AddRange(this.activeDst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.activeFoeFirst)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.activeTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.lastTriggerTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.isFinish)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.activeCount)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.skillID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.activeOrg = new EPosition(); 
            this.activeOrg.__decode(binData, ref pos); 
            this.activeOrgEID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.activeDst = new EPosition(); 
            this.activeDst.__decode(binData, ref pos); 
            this.activeFoeFirst = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.activeTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.lastTriggerTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.isFinish = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.activeCount = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class EntityBuffInfo: Proto4z.IProtoObject //BUFF  
    {     
        //proto id   
        public const ushort protoID = 2010;  
        static public ushort getProtoID() { return 2010; } 
        static public string getProtoName() { return "EntityBuffInfo"; } 
        //members   
        public ulong buffID;  
        public EPosition activeOrg;  
        public ulong activeOrgEID;  
        public EPosition activeDst;  
        public ulong activeDstEID;  
        public double activeTime;  
        public double lastTriggerTime;  
        public double activeCount;  
        public EntityBuffInfo()  
        { 
            buffID = 0;  
            activeOrg = new EPosition();  
            activeOrgEID = 0;  
            activeDst = new EPosition();  
            activeDstEID = 0;  
            activeTime = 0.0;  
            lastTriggerTime = 0.0;  
            activeCount = 0.0;  
        } 
        public EntityBuffInfo(ulong buffID, EPosition activeOrg, ulong activeOrgEID, EPosition activeDst, ulong activeDstEID, double activeTime, double lastTriggerTime, double activeCount) 
        { 
            this.buffID = buffID; 
            this.activeOrg = activeOrg; 
            this.activeOrgEID = activeOrgEID; 
            this.activeDst = activeDst; 
            this.activeDstEID = activeDstEID; 
            this.activeTime = activeTime; 
            this.lastTriggerTime = lastTriggerTime; 
            this.activeCount = activeCount; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.buffID)); 
            if (this.activeOrg == null) this.activeOrg = new EPosition(); 
            data.AddRange(this.activeOrg.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.activeOrgEID)); 
            if (this.activeDst == null) this.activeDst = new EPosition(); 
            data.AddRange(this.activeDst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.activeDstEID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.activeTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.lastTriggerTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.activeCount)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.buffID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.activeOrg = new EPosition(); 
            this.activeOrg.__decode(binData, ref pos); 
            this.activeOrgEID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.activeDst = new EPosition(); 
            this.activeDst.__decode(binData, ref pos); 
            this.activeDstEID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.activeTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.lastTriggerTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.activeCount = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
