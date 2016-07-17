 
namespace Proto4z  
{ 
 
    public class SceneInfoReq: Proto4z.IProtoObject //获取场景信息  
    {     
        //proto id   
        public const ushort protoID = 50000;  
        static public ushort getProtoID() { return 50000; } 
        static public string getProtoName() { return "SceneInfoReq"; } 
        //members   
        public SceneInfoReq()  
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
 
    public class SceneInfoAck: Proto4z.IProtoObject //获取场景信息  
    {     
        //proto id   
        public const ushort protoID = 50001;  
        static public ushort getProtoID() { return 50001; } 
        static public string getProtoName() { return "SceneInfoAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes;  
        public SceneInfoAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public SceneInfoAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class TryEnterSceneReq: Proto4z.IProtoObject //进入场景  
    {     
        //proto id   
        public const ushort protoID = 50002;  
        static public ushort getProtoID() { return 50002; } 
        static public string getProtoName() { return "TryEnterSceneReq"; } 
        //members   
        public ushort type; //类型, 如果是不同类型,该请求会触发场景切换动作  
        public TryEnterSceneReq()  
        { 
            type = 0;  
        } 
        public TryEnterSceneReq(ushort type) 
        { 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class TryEnterSceneAck: Proto4z.IProtoObject //进入场景  
    {     
        //proto id   
        public const ushort protoID = 50003;  
        static public ushort getProtoID() { return 50003; } 
        static public string getProtoName() { return "TryEnterSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public TryEnterSceneAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public TryEnterSceneAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneInfoNotice: Proto4z.IProtoObject //场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中  
    {     
        //proto id   
        public const ushort protoID = 50004;  
        static public ushort getProtoID() { return 50004; } 
        static public string getProtoName() { return "SceneInfoNotice"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public SceneInfoNotice()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public SceneInfoNotice(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSceneReq: Proto4z.IProtoObject //离开场景  
    {     
        //proto id   
        public const ushort protoID = 50005;  
        static public ushort getProtoID() { return 50005; } 
        static public string getProtoName() { return "LeaveSceneReq"; } 
        //members   
        public ushort type; //类型  
        public LeaveSceneReq()  
        { 
            type = 0;  
        } 
        public LeaveSceneReq(ushort type) 
        { 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSceneAck: Proto4z.IProtoObject //离开场景  
    {     
        //proto id   
        public const ushort protoID = 50006;  
        static public ushort getProtoID() { return 50006; } 
        static public string getProtoName() { return "LeaveSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public LeaveSceneAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public LeaveSceneAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class QuitSceneReq: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 50007;  
        static public ushort getProtoID() { return 50007; } 
        static public string getProtoName() { return "QuitSceneReq"; } 
        //members   
        public ushort type; //类型  
        public QuitSceneReq()  
        { 
            type = 0;  
        } 
        public QuitSceneReq(ushort type) 
        { 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class QuitSceneAck: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 50008;  
        static public ushort getProtoID() { return 50008; } 
        static public string getProtoName() { return "QuitSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public QuitSceneAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public QuitSceneAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
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
 
    public class RefreshSpaceNotice: Proto4z.IProtoObject //增量更新场景中的实体数据, 服务器定时100ms广播  
    {     
        //proto id   
        public const ushort protoID = 50010;  
        static public ushort getProtoID() { return 50010; } 
        static public string getProtoName() { return "RefreshSpaceNotice"; } 
        //members   
        public EntityInfoArray entitys;  
        public EntityReportArray reports;  
        public double serverTime; //服务器当前时间  
        public RefreshSpaceNotice()  
        { 
            entitys = new EntityInfoArray();  
            reports = new EntityReportArray();  
            serverTime = 0.0;  
        } 
        public RefreshSpaceNotice(EntityInfoArray entitys, EntityReportArray reports, double serverTime) 
        { 
            this.entitys = entitys; 
            this.reports = reports; 
            this.serverTime = serverTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entitys == null) this.entitys = new EntityInfoArray(); 
            data.AddRange(this.entitys.__encode()); 
            if (this.reports == null) this.reports = new EntityReportArray(); 
            data.AddRange(this.reports.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.serverTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entitys = new EntityInfoArray(); 
            this.entitys.__decode(binData, ref pos); 
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
 
 
