 
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
 
    public class RefreshEntityNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50011;  
        static public ushort getProtoID() { return 50011; } 
        static public string getProtoName() { return "RefreshEntityNotice"; } 
        //members   
        public EntityInfoArray entityInfos;  
        public EntityPointArray entityPoints;  
        public double serverTime; //服务器当前时间  
        public RefreshEntityNotice()  
        { 
            entityInfos = new EntityInfoArray();  
            entityPoints = new EntityPointArray();  
            serverTime = 0.0;  
        } 
        public RefreshEntityNotice(EntityInfoArray entityInfos, EntityPointArray entityPoints, double serverTime) 
        { 
            this.entityInfos = entityInfos; 
            this.entityPoints = entityPoints; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entityInfos == null) this.entityInfos = new EntityInfoArray(); 
            data.AddRange(this.entityInfos.__encode()); 
            if (this.entityPoints == null) this.entityPoints = new EntityPointArray(); 
            data.AddRange(this.entityPoints.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entityInfos = new EntityInfoArray(); 
            this.entityInfos.__decode(binData, ref pos); 
            this.entityPoints = new EntityPointArray(); 
            this.entityPoints.__decode(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RefreshSceneReportsNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50005;  
        static public ushort getProtoID() { return 50005; } 
        static public string getProtoName() { return "RefreshSceneReportsNotice"; } 
        //members   
        public EntityReportArray reports;  
        public double serverTime; //服务器当前时间  
        public RefreshSceneReportsNotice()  
        { 
            reports = new EntityReportArray();  
            serverTime = 0.0;  
        } 
        public RefreshSceneReportsNotice(EntityReportArray reports, double serverTime) 
        { 
            this.reports = reports; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.reports == null) this.reports = new EntityReportArray(); 
            data.AddRange(this.reports.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.reports = new EntityReportArray(); 
            this.reports.__decode(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public double serverTime; //服务器当前时间  
        public AddEntityNotice()  
        { 
            entitys = new EntityFullDataArray();  
            serverTime = 0.0;  
        } 
        public AddEntityNotice(EntityFullDataArray entitys, double serverTime) 
        { 
            this.entitys = entitys; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityFullDataArray(); 
            data.AddRange(this.entitys.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityFullDataArray(); 
            this.entitys.__decode(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public double serverTime; //服务器当前时间  
        public RemoveEntityNotice()  
        { 
            eids = new EntityIDArray();  
            serverTime = 0.0;  
        } 
        public RemoveEntityNotice(EntityIDArray eids, double serverTime) 
        { 
            this.eids = eids; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.eids == null) this.eids = new EntityIDArray(); 
            data.AddRange(this.eids.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eids = new EntityIDArray(); 
            this.eids.__decode(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public double serverTime; //服务器当前时间  
        public AddBuffNotice()  
        { 
            eid = 0;  
            serverTime = 0.0;  
        } 
        public AddBuffNotice(ulong eid, double serverTime) 
        { 
            this.eid = eid; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
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
        public double serverTime; //服务器当前时间  
        public RemoveBuffNotice()  
        { 
            eid = 0;  
            serverTime = 0.0;  
        } 
        public RemoveBuffNotice(ulong eid, double serverTime) 
        { 
            this.eid = eid; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
