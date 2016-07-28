 
namespace Proto4z  
{ 
 
    public class AttachSpaceReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50013;  
        static public ushort getProtoID() { return 50013; } 
        static public string getProtoName() { return "AttachSpaceReq"; } 
        //members   
        public ulong avatarID;  
        public uint spaceID;  
        public string token; //令牌  
        public AttachSpaceReq()  
        { 
            avatarID = 0;  
            spaceID = 0;  
            token = "";  
        } 
        public AttachSpaceReq(ulong avatarID, uint spaceID, string token) 
        { 
            this.avatarID = avatarID; 
            this.spaceID = spaceID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachSpaceResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50014;  
        static public ushort getProtoID() { return 50014; } 
        static public string getProtoName() { return "AttachSpaceResp"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong avatarID;  
        public uint spaceID;  
        public AttachSpaceResp()  
        { 
            retCode = 0;  
            avatarID = 0;  
            spaceID = 0;  
        } 
        public AttachSpaceResp(ushort retCode, ulong avatarID, uint spaceID) 
        { 
            this.retCode = retCode; 
            this.avatarID = avatarID; 
            this.spaceID = spaceID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class FillSpaceNotice: Proto4z.IProtoObject //填充场景数据  
    {     
        //proto id   
        public const ushort protoID = 50009;  
        static public ushort getProtoID() { return 50009; } 
        static public string getProtoName() { return "FillSpaceNotice"; } 
        //members   
        public EntityFullInfoArray entitys; //这里包含有所有当前场景下的实体属性和状态数据  
        public double spaceStartTime; //服务器战场开始时间  
        public double spaceEndTime; //服务器战场结束时间  
        public double serverTime; //服务器当前时间  
        public FillSpaceNotice()  
        { 
            entitys = new EntityFullInfoArray();  
            spaceStartTime = 0.0;  
            spaceEndTime = 0.0;  
            serverTime = 0.0;  
        } 
        public FillSpaceNotice(EntityFullInfoArray entitys, double spaceStartTime, double spaceEndTime, double serverTime) 
        { 
            this.entitys = entitys; 
            this.spaceStartTime = spaceStartTime; 
            this.spaceEndTime = spaceEndTime; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityFullInfoArray(); 
            data.AddRange(this.entitys.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.spaceStartTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.spaceEndTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityFullInfoArray(); 
            this.entitys.__decode(binData, ref pos); 
            this.spaceStartTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.spaceEndTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.serverTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RefreshSpaceEntitysNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50015;  
        static public ushort getProtoID() { return 50015; } 
        static public string getProtoName() { return "RefreshSpaceEntitysNotice"; } 
        //members   
        public EntityInfoArray entitys;  
        public double serverTime; //服务器当前时间  
        public RefreshSpaceEntitysNotice()  
        { 
            entitys = new EntityInfoArray();  
            serverTime = 0.0;  
        } 
        public RefreshSpaceEntitysNotice(EntityInfoArray entitys, double serverTime) 
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
 
    public class RefreshSpaceReportsNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50016;  
        static public ushort getProtoID() { return 50016; } 
        static public string getProtoName() { return "RefreshSpaceReportsNotice"; } 
        //members   
        public EntityReportArray reports;  
        public double serverTime; //服务器当前时间  
        public RefreshSpaceReportsNotice()  
        { 
            reports = new EntityReportArray();  
            serverTime = 0.0;  
        } 
        public RefreshSpaceReportsNotice(EntityReportArray reports, double serverTime) 
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
        public const ushort protoID = 50011;  
        static public ushort getProtoID() { return 50011; } 
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
        public const ushort protoID = 50012;  
        static public ushort getProtoID() { return 50012; } 
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
 
 
