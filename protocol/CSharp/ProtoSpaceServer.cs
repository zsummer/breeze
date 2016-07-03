 
namespace Proto4z  
{ 
 
    public class WorldSceneInfoReq: Proto4z.IProtoObject //获取场景信息  
    {     
        //proto id   
        public const ushort protoID = 39000;  
        static public ushort getProtoID() { return 39000; } 
        static public string getProtoName() { return "WorldSceneInfoReq"; } 
        //members   
        public ulong userID;  
        public WorldSceneInfoReq()  
        { 
            userID = 0;  
        } 
        public WorldSceneInfoReq(ulong userID) 
        { 
            this.userID = userID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldSceneInfoAck: Proto4z.IProtoObject //获取场景信息  
    {     
        //proto id   
        public const ushort protoID = 39001;  
        static public ushort getProtoID() { return 39001; } 
        static public string getProtoName() { return "WorldSceneInfoAck"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong userID;  
        public SceneInfoArray scenes;  
        public WorldSceneInfoAck()  
        { 
            retCode = 0;  
            userID = 0;  
            scenes = new SceneInfoArray();  
        } 
        public WorldSceneInfoAck(ushort retCode, ulong userID, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldTryEnterSceneReq: Proto4z.IProtoObject //进入场景  
    {     
        //proto id   
        public const ushort protoID = 39002;  
        static public ushort getProtoID() { return 39002; } 
        static public string getProtoName() { return "WorldTryEnterSceneReq"; } 
        //members   
        public ulong userID;  
        public ushort type; //类型, 如果是不同类型,该请求会触发场景切换动作  
        public WorldTryEnterSceneReq()  
        { 
            userID = 0;  
            type = 0;  
        } 
        public WorldTryEnterSceneReq(ulong userID, ushort type) 
        { 
            this.userID = userID; 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldTryEnterSceneAck: Proto4z.IProtoObject //进入场景  
    {     
        //proto id   
        public const ushort protoID = 39003;  
        static public ushort getProtoID() { return 39003; } 
        static public string getProtoName() { return "WorldTryEnterSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong userID;  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会直接切换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public WorldTryEnterSceneAck()  
        { 
            retCode = 0;  
            userID = 0;  
            scenes = new SceneInfoArray();  
        } 
        public WorldTryEnterSceneAck(ushort retCode, ulong userID, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldSceneInfoNotice: Proto4z.IProtoObject //场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中  
    {     
        //proto id   
        public const ushort protoID = 39004;  
        static public ushort getProtoID() { return 39004; } 
        static public string getProtoName() { return "WorldSceneInfoNotice"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong userID;  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public WorldSceneInfoNotice()  
        { 
            retCode = 0;  
            userID = 0;  
            scenes = new SceneInfoArray();  
        } 
        public WorldSceneInfoNotice(ushort retCode, ulong userID, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldLeaveSceneReq: Proto4z.IProtoObject //离开场景  
    {     
        //proto id   
        public const ushort protoID = 39005;  
        static public ushort getProtoID() { return 39005; } 
        static public string getProtoName() { return "WorldLeaveSceneReq"; } 
        //members   
        public ulong userID;  
        public ushort type; //类型  
        public WorldLeaveSceneReq()  
        { 
            userID = 0;  
            type = 0;  
        } 
        public WorldLeaveSceneReq(ulong userID, ushort type) 
        { 
            this.userID = userID; 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldLeaveSceneAck: Proto4z.IProtoObject //离开场景  
    {     
        //proto id   
        public const ushort protoID = 39006;  
        static public ushort getProtoID() { return 39006; } 
        static public string getProtoName() { return "WorldLeaveSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong userID;  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public WorldLeaveSceneAck()  
        { 
            retCode = 0;  
            userID = 0;  
            scenes = new SceneInfoArray();  
        } 
        public WorldLeaveSceneAck(ushort retCode, ulong userID, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldQuitSceneReq: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 39007;  
        static public ushort getProtoID() { return 39007; } 
        static public string getProtoName() { return "WorldQuitSceneReq"; } 
        //members   
        public ulong userID;  
        public ushort type; //类型  
        public WorldQuitSceneReq()  
        { 
            userID = 0;  
            type = 0;  
        } 
        public WorldQuitSceneReq(ulong userID, ushort type) 
        { 
            this.userID = userID; 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WorldQuitSceneAck: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 39008;  
        static public ushort getProtoID() { return 39008; } 
        static public string getProtoName() { return "WorldQuitSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong userID;  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public WorldQuitSceneAck()  
        { 
            retCode = 0;  
            userID = 0;  
            scenes = new SceneInfoArray();  
        } 
        public WorldQuitSceneAck(ushort retCode, ulong userID, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SpaceInfoToWorldNotice: Proto4z.IProtoObject //数据刷给world  
    {     
        //proto id   
        public const ushort protoID = 39010;  
        static public ushort getProtoID() { return 39010; } 
        static public string getProtoName() { return "SpaceInfoToWorldNotice"; } 
        //members   
        public string host; //服务器host  
        public ushort port; //服务器port  
        public SpaceInfoArray spaceInfos; //类型  
        public SpaceInfoToWorldNotice()  
        { 
            host = "";  
            port = 0;  
            spaceInfos = new SpaceInfoArray();  
        } 
        public SpaceInfoToWorldNotice(string host, ushort port, SpaceInfoArray spaceInfos) 
        { 
            this.host = host; 
            this.port = port; 
            this.spaceInfos = spaceInfos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            if (this.spaceInfos == null) this.spaceInfos = new SpaceInfoArray(); 
            data.AddRange(this.spaceInfos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceInfos = new SpaceInfoArray(); 
            this.spaceInfos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class TokenInfoToSpaceNotice: Proto4z.IProtoObject //token丢给space  
    {     
        //proto id   
        public const ushort protoID = 39011;  
        static public ushort getProtoID() { return 39011; } 
        static public string getProtoName() { return "TokenInfoToSpaceNotice"; } 
        //members   
        public ulong userID;  
        public string token; //服务器port  
        public SpaceID spaceID; //类型  
        public UserBaseInfo baseInfo; //类型  
        public FightEffect effects; //类型  
        public TokenInfoToSpaceNotice()  
        { 
            userID = 0;  
            token = "";  
            spaceID = new SpaceID();  
            baseInfo = new UserBaseInfo();  
            effects = new FightEffect();  
        } 
        public TokenInfoToSpaceNotice(ulong userID, string token, SpaceID spaceID, UserBaseInfo baseInfo, FightEffect effects) 
        { 
            this.userID = userID; 
            this.token = token; 
            this.spaceID = spaceID; 
            this.baseInfo = baseInfo; 
            this.effects = effects; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            if (this.spaceID == null) this.spaceID = new SpaceID(); 
            data.AddRange(this.spaceID.__encode()); 
            if (this.baseInfo == null) this.baseInfo = new UserBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.effects == null) this.effects = new FightEffect(); 
            data.AddRange(this.effects.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.spaceID = new SpaceID(); 
            this.spaceID.__decode(binData, ref pos); 
            this.baseInfo = new UserBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.effects = new FightEffect(); 
            this.effects.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
