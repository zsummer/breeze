 
namespace Proto4z  
{ 
 
    public class SceneKnock: Proto4z.IProtoObject //战场服务器挂载  
    {     
        //proto id   
        public const ushort protoID = 4000;  
        static public ushort getProtoID() { return 4000; } 
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
        public const ushort protoID = 4001;  
        static public ushort getProtoID() { return 4001; } 
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
        public const ushort protoID = 4002;  
        static public ushort getProtoID() { return 4002; } 
        static public string getProtoName() { return "SceneServerJoinGroupIns"; } 
        //members   
        public ulong refresh; //0为客户端请求操作, 1为仅仅刷新数据  
        public ulong groupID; //编队ID, 0为创建  
        public ulong modelID; //模型ID  
        public DictArrayKey equips; //额外装备  
        public ulong avatarID;  
        public string avatarName;  
        public double rankScore; //天梯分数  
        public SceneServerJoinGroupIns()  
        { 
            refresh = 0;  
            groupID = 0;  
            modelID = 0;  
            equips = new DictArrayKey();  
            avatarID = 0;  
            avatarName = "";  
            rankScore = 0.0;  
        } 
        public SceneServerJoinGroupIns(ulong refresh, ulong groupID, ulong modelID, DictArrayKey equips, ulong avatarID, string avatarName, double rankScore) 
        { 
            this.refresh = refresh; 
            this.groupID = groupID; 
            this.modelID = modelID; 
            this.equips = equips; 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.rankScore = rankScore; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.refresh)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modelID)); 
            if (this.equips == null) this.equips = new DictArrayKey(); 
            data.AddRange(this.equips.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.rankScore)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.refresh = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.equips = new DictArrayKey(); 
            this.equips.__decode(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.rankScore = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneServerJoinGroupAck: Proto4z.IProtoObject //创建/加入编队响应结果  
    {     
        //proto id   
        public const ushort protoID = 4003;  
        static public ushort getProtoID() { return 4003; } 
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
        public const ushort protoID = 4004;  
        static public ushort getProtoID() { return 4004; } 
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
        public const ushort protoID = 4005;  
        static public ushort getProtoID() { return 4005; } 
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
        public const ushort protoID = 4006;  
        static public ushort getProtoID() { return 4006; } 
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
 
 
