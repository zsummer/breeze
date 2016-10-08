 
namespace Proto4z  
{ 
 
    public class SceneClientPulse: Proto4z.IProtoObject //客户端脉冲请求  
    {     
        //proto id   
        public const ushort protoID = 50000;  
        static public ushort getProtoID() { return 50000; } 
        static public string getProtoName() { return "SceneClientPulse"; } 
        //members   
        public SceneClientPulse()  
        { 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            return pos; 
        } 
    } 
 
    public class AttachSceneReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50001;  
        static public ushort getProtoID() { return 50001; } 
        static public string getProtoName() { return "AttachSceneReq"; } 
        //members   
        public ulong avatarID;  
        public ulong sceneID;  
        public string token; //令牌  
        public AttachSceneReq()  
        { 
            avatarID = 0;  
            sceneID = 0;  
            token = "";  
        } 
        public AttachSceneReq(ulong avatarID, ulong sceneID, string token) 
        { 
            this.avatarID = avatarID; 
            this.sceneID = sceneID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachSceneResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50002;  
        static public ushort getProtoID() { return 50002; } 
        static public string getProtoName() { return "AttachSceneResp"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong avatarID;  
        public ulong sceneID;  
        public AttachSceneResp()  
        { 
            retCode = 0;  
            avatarID = 0;  
            sceneID = 0;  
        } 
        public AttachSceneResp(ushort retCode, ulong avatarID, ulong sceneID) 
        { 
            this.retCode = retCode; 
            this.avatarID = avatarID; 
            this.sceneID = sceneID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneSectionNotice: Proto4z.IProtoObject //填充场景数据  
    {     
        //proto id   
        public const ushort protoID = 50010;  
        static public ushort getProtoID() { return 50010; } 
        static public string getProtoName() { return "SceneSectionNotice"; } 
        //members   
        public SceneSection section;  
        public SceneSectionNotice()  
        { 
            section = new SceneSection();  
        } 
        public SceneSectionNotice(SceneSection section) 
        { 
            this.section = section; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.section == null) this.section = new SceneSection(); 
            data.AddRange(this.section.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.section = new SceneSection(); 
            this.section.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneRefreshNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50012;  
        static public ushort getProtoID() { return 50012; } 
        static public string getProtoName() { return "SceneRefreshNotice"; } 
        //members   
        public EntityInfoArray entityInfos;  
        public EntityMoveArray entityMoves;  
        public SceneRefreshNotice()  
        { 
            entityInfos = new EntityInfoArray();  
            entityMoves = new EntityMoveArray();  
        } 
        public SceneRefreshNotice(EntityInfoArray entityInfos, EntityMoveArray entityMoves) 
        { 
            this.entityInfos = entityInfos; 
            this.entityMoves = entityMoves; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entityInfos == null) this.entityInfos = new EntityInfoArray(); 
            data.AddRange(this.entityInfos.__encode()); 
            if (this.entityMoves == null) this.entityMoves = new EntityMoveArray(); 
            data.AddRange(this.entityMoves.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entityInfos = new EntityInfoArray(); 
            this.entityInfos.__decode(binData, ref pos); 
            this.entityMoves = new EntityMoveArray(); 
            this.entityMoves.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneReportsNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50013;  
        static public ushort getProtoID() { return 50013; } 
        static public string getProtoName() { return "SceneReportsNotice"; } 
        //members   
        public EntityReportArray reports;  
        public SceneReportsNotice()  
        { 
            reports = new EntityReportArray();  
        } 
        public SceneReportsNotice(EntityReportArray reports) 
        { 
            this.reports = reports; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.reports == null) this.reports = new EntityReportArray(); 
            data.AddRange(this.reports.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.reports = new EntityReportArray(); 
            this.reports.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AddEntityNotice: Proto4z.IProtoObject //一批实体加入场景时, 把这些实体的数据广播给其他玩家  
    {     
        //proto id   
        public const ushort protoID = 50006;  
        static public ushort getProtoID() { return 50006; } 
        static public string getProtoName() { return "AddEntityNotice"; } 
        //members   
        public EntityFullDataArray entitys;  
        public AddEntityNotice()  
        { 
            entitys = new EntityFullDataArray();  
        } 
        public AddEntityNotice(EntityFullDataArray entitys) 
        { 
            this.entitys = entitys; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityFullDataArray(); 
            data.AddRange(this.entitys.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityFullDataArray(); 
            this.entitys.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RemoveEntityNotice: Proto4z.IProtoObject //实体离开场景时, 把该实体的数据广播给其他玩家  
    {     
        //proto id   
        public const ushort protoID = 50007;  
        static public ushort getProtoID() { return 50007; } 
        static public string getProtoName() { return "RemoveEntityNotice"; } 
        //members   
        public EntityIDArray eids;  
        public RemoveEntityNotice()  
        { 
            eids = new EntityIDArray();  
        } 
        public RemoveEntityNotice(EntityIDArray eids) 
        { 
            this.eids = eids; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.eids == null) this.eids = new EntityIDArray(); 
            data.AddRange(this.eids.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eids = new EntityIDArray(); 
            this.eids.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoveReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50014;  
        static public ushort getProtoID() { return 50014; } 
        static public string getProtoName() { return "MoveReq"; } 
        //members   
        public ulong eid;  
        public ushort maction;  
        public EPoint pos;  
        public MoveReq()  
        { 
            eid = 0;  
            maction = 0;  
            pos = new EPoint();  
        } 
        public MoveReq(ulong eid, ushort maction, EPoint pos) 
        { 
            this.eid = eid; 
            this.maction = maction; 
            this.pos = pos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.maction)); 
            if (this.pos == null) this.pos = new EPoint(); 
            data.AddRange(this.pos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.maction = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.pos = new EPoint(); 
            this.pos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoveResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50015;  
        static public ushort getProtoID() { return 50015; } 
        static public string getProtoName() { return "MoveResp"; } 
        //members   
        public ushort retCode;  
        public ulong eid;  
        public ushort maction;  
        public EPoint pos;  
        public MoveResp()  
        { 
            retCode = 0;  
            eid = 0;  
            maction = 0;  
            pos = new EPoint();  
        } 
        public MoveResp(ushort retCode, ulong eid, ushort maction, EPoint pos) 
        { 
            this.retCode = retCode; 
            this.eid = eid; 
            this.maction = maction; 
            this.pos = pos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.maction)); 
            if (this.pos == null) this.pos = new EPoint(); 
            data.AddRange(this.pos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.maction = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.pos = new EPoint(); 
            this.pos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoveNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50016;  
        static public ushort getProtoID() { return 50016; } 
        static public string getProtoName() { return "MoveNotice"; } 
        //members   
        public ulong eid;  
        public ushort maction;  
        public EPoints path;  
        public MoveNotice()  
        { 
            eid = 0;  
            maction = 0;  
            path = new EPoints();  
        } 
        public MoveNotice(ulong eid, ushort maction, EPoints path) 
        { 
            this.eid = eid; 
            this.maction = maction; 
            this.path = path; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.maction)); 
            if (this.path == null) this.path = new EPoints(); 
            data.AddRange(this.path.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.maction = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.path = new EPoints(); 
            this.path.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AddBuffNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50008;  
        static public ushort getProtoID() { return 50008; } 
        static public string getProtoName() { return "AddBuffNotice"; } 
        //members   
        public ulong eid;  
        public AddBuffNotice()  
        { 
            eid = 0;  
        } 
        public AddBuffNotice(ulong eid) 
        { 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RemoveBuffNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50009;  
        static public ushort getProtoID() { return 50009; } 
        static public string getProtoName() { return "RemoveBuffNotice"; } 
        //members   
        public ulong eid;  
        public RemoveBuffNotice()  
        { 
            eid = 0;  
        } 
        public RemoveBuffNotice(ulong eid) 
        { 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserSkillReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50017;  
        static public ushort getProtoID() { return 50017; } 
        static public string getProtoName() { return "UserSkillReq"; } 
        //members   
        public ulong eid;  
        public UserSkillReq()  
        { 
            eid = 0;  
        } 
        public UserSkillReq(ulong eid) 
        { 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserSkillResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50018;  
        static public ushort getProtoID() { return 50018; } 
        static public string getProtoName() { return "UserSkillResp"; } 
        //members   
        public ushort retCode;  
        public ulong eid;  
        public UserSkillResp()  
        { 
            retCode = 0;  
            eid = 0;  
        } 
        public UserSkillResp(ushort retCode, ulong eid) 
        { 
            this.retCode = retCode; 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserSkillNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50019;  
        static public ushort getProtoID() { return 50019; } 
        static public string getProtoName() { return "UserSkillNotice"; } 
        //members   
        public ulong eid;  
        public UserSkillNotice()  
        { 
            eid = 0;  
        } 
        public UserSkillNotice(ulong eid) 
        { 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
