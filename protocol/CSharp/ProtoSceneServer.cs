 
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
        public ulong groupID; //编队ID, 0为创建  
        public AvatarBaseInfo baseInfo; //角色数据  
        public AvatarPropMap baseProps; //角色属性数据  
        public SceneServerJoinGroupIns()  
        { 
            groupID = 0;  
            baseInfo = new AvatarBaseInfo();  
            baseProps = new AvatarPropMap();  
        } 
        public SceneServerJoinGroupIns(ulong groupID, AvatarBaseInfo baseInfo, AvatarPropMap baseProps) 
        { 
            this.groupID = groupID; 
            this.baseInfo = baseInfo; 
            this.baseProps = baseProps; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.baseProps == null) this.baseProps = new AvatarPropMap(); 
            data.AddRange(this.baseProps.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.baseProps = new AvatarPropMap(); 
            this.baseProps.__decode(binData, ref pos); 
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
 
    public class SceneServerGroupStatusChangeIns: Proto4z.IProtoObject //scene ==> world  
    {     
        //proto id   
        public const ushort protoID = 39005;  
        static public ushort getProtoID() { return 39005; } 
        static public string getProtoName() { return "SceneServerGroupStatusChangeIns"; } 
        //members   
        public ulong groupID;  
        public ulong sceneID;  
        public ushort status; //如果是NONE 说明离开场景  
        public SceneServerGroupStatusChangeIns()  
        { 
            groupID = 0;  
            sceneID = 0;  
            status = 0;  
        } 
        public SceneServerGroupStatusChangeIns(ulong groupID, ulong sceneID, ushort status) 
        { 
            this.groupID = groupID; 
            this.sceneID = sceneID; 
            this.status = status; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
