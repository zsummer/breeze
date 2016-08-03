 
namespace Proto4z  
{ 
 
    public class AttachSceneReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50000;  
        static public ushort getProtoID() { return 50000; } 
        static public string getProtoName() { return "AttachSceneReq"; } 
        //members   
        public ulong avatarID;  
        public uint sceneID;  
        public string token; //令牌  
        public AttachSceneReq()  
        { 
            avatarID = 0;  
            sceneID = 0;  
            token = "";  
        } 
        public AttachSceneReq(ulong avatarID, uint sceneID, string token) 
        { 
            this.avatarID = avatarID; 
            this.sceneID = sceneID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachSceneResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50001;  
        static public ushort getProtoID() { return 50001; } 
        static public string getProtoName() { return "AttachSceneResp"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong avatarID;  
        public uint sceneID;  
        public AttachSceneResp()  
        { 
            retCode = 0;  
            avatarID = 0;  
            sceneID = 0;  
        } 
        public AttachSceneResp(ushort retCode, ulong avatarID, uint sceneID) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.sceneID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class FillSceneNotice: Proto4z.IProtoObject //填充场景数据  
    {     
        //proto id   
        public const ushort protoID = 50002;  
        static public ushort getProtoID() { return 50002; } 
        static public string getProtoName() { return "FillSceneNotice"; } 
        //members   
        public EntityFullInfoArray entitys; //这里包含有所有当前场景下的实体属性和状态数据  
        public double sceneStartTime; //服务器战场开始时间  
        public double sceneEndTime; //服务器战场结束时间  
        public double serverTime; //服务器当前时间  
        public FillSceneNotice()  
        { 
            entitys = new EntityFullInfoArray();  
            sceneStartTime = 0.0;  
            sceneEndTime = 0.0;  
            serverTime = 0.0;  
        } 
        public FillSceneNotice(EntityFullInfoArray entitys, double sceneStartTime, double sceneEndTime, double serverTime) 
        { 
            this.entitys = entitys; 
            this.sceneStartTime = sceneStartTime; 
            this.sceneEndTime = sceneEndTime; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityFullInfoArray(); 
            data.AddRange(this.entitys.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.sceneStartTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.sceneEndTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityFullInfoArray(); 
            this.entitys.__decode(binData, ref pos); 
            this.sceneStartTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.sceneEndTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RefreshSceneEntitysNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50003;  
        static public ushort getProtoID() { return 50003; } 
        static public string getProtoName() { return "RefreshSceneEntitysNotice"; } 
        //members   
        public EntityInfoArray entitys;  
        public double serverTime; //服务器当前时间  
        public RefreshSceneEntitysNotice()  
        { 
            entitys = new EntityInfoArray();  
            serverTime = 0.0;  
        } 
        public RefreshSceneEntitysNotice(EntityInfoArray entitys, double serverTime) 
        { 
            this.entitys = entitys; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityInfoArray(); 
            data.AddRange(this.entitys.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityInfoArray(); 
            this.entitys.__decode(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RefreshSceneReportsNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50004;  
        static public ushort getProtoID() { return 50004; } 
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
        public const ushort protoID = 50005;  
        static public ushort getProtoID() { return 50005; } 
        static public string getProtoName() { return "AddEntityNotice"; } 
        //members   
        public EntityFullInfoArray entitys;  
        public double serverTime; //服务器当前时间  
        public AddEntityNotice()  
        { 
            entitys = new EntityFullInfoArray();  
            serverTime = 0.0;  
        } 
        public AddEntityNotice(EntityFullInfoArray entitys, double serverTime) 
        { 
            this.entitys = entitys; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityFullInfoArray(); 
            data.AddRange(this.entitys.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityFullInfoArray(); 
            this.entitys.__decode(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RemoveEntityNotice: Proto4z.IProtoObject //实体离开场景时, 把该实体的数据广播给其他玩家  
    {     
        //proto id   
        public const ushort protoID = 50006;  
        static public ushort getProtoID() { return 50006; } 
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
 
} 
 
 
