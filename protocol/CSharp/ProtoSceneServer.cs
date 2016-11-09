 
namespace Proto4z  
{ 
 
    public class SceneKnock: Proto4z.IProtoObject //战场服务器挂载  
    {     
        //proto id   
        public const ushort protoID = 39000;  
        static public ushort getProtoID() { return 39000; } 
        static public string getProtoName() { return "SceneKnock"; } 
        //members   
        public ulong lineID; //分线ID  
        public string pubHost;  
        public ushort pubPort;  
        public SceneKnock()  
        { 
            lineID = 0;  
            pubHost = "";  
            pubPort = 0;  
        } 
        public SceneKnock(ulong lineID, string pubHost, ushort pubPort) 
        { 
            this.lineID = lineID; 
            this.pubHost = pubHost; 
            this.pubPort = pubPort; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.lineID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.pubHost)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.pubPort)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.lineID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.pubHost = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.pubPort = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ScenePulse: Proto4z.IProtoObject //集群脉冲  
    {     
        //proto id   
        public const ushort protoID = 39001;  
        static public ushort getProtoID() { return 39001; } 
        static public string getProtoName() { return "ScenePulse"; } 
        //members   
        public ScenePulse()  
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
 
    public class SceneServerJoinGroupIns: Proto4z.IProtoObject //创建/加入编队, 来自docker的指令  
    {     
        //proto id   
        public const ushort protoID = 39002;  
        static public ushort getProtoID() { return 39002; } 
        static public string getProtoName() { return "SceneServerJoinGroupIns"; } 
        //members   
        public ulong refresh; //0为客户端请求操作, 1为仅仅刷新数据  
        public ulong groupID; //编队ID, 0为创建  
        public EntityBase baseInfo; //玩家基础数据  
        public EntityProp fixedProps; //基础固定属性  
        public EntityProp growthProps; //成长基础属性  
        public EntityProp growths; //成长系数  
        public SceneServerJoinGroupIns()  
        { 
            refresh = 0;  
            groupID = 0;  
            baseInfo = new EntityBase();  
            fixedProps = new EntityProp();  
            growthProps = new EntityProp();  
            growths = new EntityProp();  
        } 
        public SceneServerJoinGroupIns(ulong refresh, ulong groupID, EntityBase baseInfo, EntityProp fixedProps, EntityProp growthProps, EntityProp growths) 
        { 
            this.refresh = refresh; 
            this.groupID = groupID; 
            this.baseInfo = baseInfo; 
            this.fixedProps = fixedProps; 
            this.growthProps = growthProps; 
            this.growths = growths; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.refresh)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            if (this.baseInfo == null) this.baseInfo = new EntityBase(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.fixedProps == null) this.fixedProps = new EntityProp(); 
            data.AddRange(this.fixedProps.__encode()); 
            if (this.growthProps == null) this.growthProps = new EntityProp(); 
            data.AddRange(this.growthProps.__encode()); 
            if (this.growths == null) this.growths = new EntityProp(); 
            data.AddRange(this.growths.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.refresh = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.baseInfo = new EntityBase(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.fixedProps = new EntityProp(); 
            this.fixedProps.__decode(binData, ref pos); 
            this.growthProps = new EntityProp(); 
            this.growthProps.__decode(binData, ref pos); 
            this.growths = new EntityProp(); 
            this.growths.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneServerJoinGroupAck: Proto4z.IProtoObject //创建/加入编队响应结果  
    {     
        //proto id   
        public const ushort protoID = 39003;  
        static public ushort getProtoID() { return 39003; } 
        static public string getProtoName() { return "SceneServerJoinGroupAck"; } 
        //members   
        public ushort retCode;  
        public ulong newGroupID;  
        public ulong oldGroupID;  
        public SceneServerJoinGroupAck()  
        { 
            retCode = 0;  
            newGroupID = 0;  
            oldGroupID = 0;  
        } 
        public SceneServerJoinGroupAck(ushort retCode, ulong newGroupID, ulong oldGroupID) 
        { 
            this.retCode = retCode; 
            this.newGroupID = newGroupID; 
            this.oldGroupID = oldGroupID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.newGroupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.oldGroupID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.newGroupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.oldGroupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneServerEnterSceneIns: Proto4z.IProtoObject //开辟场景  
    {     
        //proto id   
        public const ushort protoID = 39004;  
        static public ushort getProtoID() { return 39004; } 
        static public string getProtoName() { return "SceneServerEnterSceneIns"; } 
        //members   
        public ushort sceneType; //类型  
        public ulong mapID;  
        public SceneGroupInfoArray groups; //多个编队  
        public SceneServerEnterSceneIns()  
        { 
            sceneType = 0;  
            mapID = 0;  
            groups = new SceneGroupInfoArray();  
        } 
        public SceneServerEnterSceneIns(ushort sceneType, ulong mapID, SceneGroupInfoArray groups) 
        { 
            this.sceneType = sceneType; 
            this.mapID = mapID; 
            this.groups = groups; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.mapID)); 
            if (this.groups == null) this.groups = new SceneGroupInfoArray(); 
            data.AddRange(this.groups.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.groups = new SceneGroupInfoArray(); 
            this.groups.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneServerCancelSceneIns: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 39005;  
        static public ushort getProtoID() { return 39005; } 
        static public string getProtoName() { return "SceneServerCancelSceneIns"; } 
        //members   
        public ulong sceneID; //sceneID  
        public ulong groupID; //groupID  
        public SceneServerCancelSceneIns()  
        { 
            sceneID = 0;  
            groupID = 0;  
        } 
        public SceneServerCancelSceneIns(ulong sceneID, ulong groupID) 
        { 
            this.sceneID = sceneID; 
            this.groupID = groupID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneServerGroupStateChangeIns: Proto4z.IProtoObject //scene ==> world  
    {     
        //proto id   
        public const ushort protoID = 39006;  
        static public ushort getProtoID() { return 39006; } 
        static public string getProtoName() { return "SceneServerGroupStateChangeIns"; } 
        //members   
        public ulong sceneID;  
        public ulong groupID;  
        public ushort state; //如果是NONE 说明离开场景  
        public SceneServerGroupStateChangeIns()  
        { 
            sceneID = 0;  
            groupID = 0;  
            state = 0;  
        } 
        public SceneServerGroupStateChangeIns(ulong sceneID, ulong groupID, ushort state) 
        { 
            this.sceneID = sceneID; 
            this.groupID = groupID; 
            this.state = state; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.state)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.state = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
