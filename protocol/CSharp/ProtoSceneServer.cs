 
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
        public SceneServerJoinGroupIns()  
        { 
            groupID = 0;  
            baseInfo = new AvatarBaseInfo();  
        } 
        public SceneServerJoinGroupIns(ulong groupID, AvatarBaseInfo baseInfo) 
        { 
            this.groupID = groupID; 
            this.baseInfo = baseInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ApplyForSceneServerReq: Proto4z.IProtoObject //请求战场  
    {     
        //proto id   
        public const ushort protoID = 39003;  
        static public ushort getProtoID() { return 39003; } 
        static public string getProtoName() { return "ApplyForSceneServerReq"; } 
        //members   
        public ushort sceneType; //类型  
        public ulong mapID;  
        public AvatarBaseInfoArray avatars; //匹配列表中的玩家  
        public ApplyForSceneServerReq()  
        { 
            sceneType = 0;  
            mapID = 0;  
            avatars = new AvatarBaseInfoArray();  
        } 
        public ApplyForSceneServerReq(ushort sceneType, ulong mapID, AvatarBaseInfoArray avatars) 
        { 
            this.sceneType = sceneType; 
            this.mapID = mapID; 
            this.avatars = avatars; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.mapID)); 
            if (this.avatars == null) this.avatars = new AvatarBaseInfoArray(); 
            data.AddRange(this.avatars.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatars = new AvatarBaseInfoArray(); 
            this.avatars.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class FeedbackAvatarStatusNotice: Proto4z.IProtoObject //scene ==> world  
    {     
        //proto id   
        public const ushort protoID = 39004;  
        static public ushort getProtoID() { return 39004; } 
        static public string getProtoName() { return "FeedbackAvatarStatusNotice"; } 
        //members   
        public ulong avatarID;  
        public ushort status;  
        public string token;  
        public FeedbackAvatarStatusNotice()  
        { 
            avatarID = 0;  
            status = 0;  
            token = "";  
        } 
        public FeedbackAvatarStatusNotice(ulong avatarID, ushort status, string token) 
        { 
            this.avatarID = avatarID; 
            this.status = status; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
