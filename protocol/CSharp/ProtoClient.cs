 
namespace Proto4z  
{ 
 
    public class ClientPulse: Proto4z.IProtoObject //客户端脉冲请求  
    {     
        //proto id   
        public const ushort protoID = 40000;  
        static public ushort getProtoID() { return 40000; } 
        static public string getProtoName() { return "ClientPulse"; } 
        //members   
        public ClientPulse()  
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
 
    public class ClientAuthReq: Proto4z.IProtoObject //认证请求  
    {     
        //proto id   
        public const ushort protoID = 40001;  
        static public ushort getProtoID() { return 40001; } 
        static public string getProtoName() { return "ClientAuthReq"; } 
        //members   
        public string account;  
        public string token;  
        public ClientAuthReq()  
        { 
            account = "";  
            token = "";  
        } 
        public ClientAuthReq(string account, string token) 
        { 
            this.account = account; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientAuthResp: Proto4z.IProtoObject //认证返回  
    {     
        //proto id   
        public const ushort protoID = 40002;  
        static public ushort getProtoID() { return 40002; } 
        static public string getProtoName() { return "ClientAuthResp"; } 
        //members   
        public ushort retCode;  
        public string account;  
        public string token;  
        public AvatarPreviewArray previews;  
        public ClientAuthResp()  
        { 
            retCode = 0;  
            account = "";  
            token = "";  
            previews = new AvatarPreviewArray();  
        } 
        public ClientAuthResp(ushort retCode, string account, string token, AvatarPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.account = account; 
            this.token = token; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            if (this.previews == null) this.previews = new AvatarPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.previews = new AvatarPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateAvatarReq: Proto4z.IProtoObject //创角色请求  
    {     
        //proto id   
        public const ushort protoID = 40003;  
        static public ushort getProtoID() { return 40003; } 
        static public string getProtoName() { return "CreateAvatarReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public string userName;  
        public CreateAvatarReq()  
        { 
            accountName = "";  
            userName = "";  
        } 
        public CreateAvatarReq(string accountName, string userName) 
        { 
            this.accountName = accountName; 
            this.userName = userName; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.userName)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.userName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateAvatarResp: Proto4z.IProtoObject //创角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 40004;  
        static public ushort getProtoID() { return 40004; } 
        static public string getProtoName() { return "CreateAvatarResp"; } 
        //members   
        public ushort retCode;  
        public ulong avatarID;  
        public AvatarPreviewArray previews;  
        public CreateAvatarResp()  
        { 
            retCode = 0;  
            avatarID = 0;  
            previews = new AvatarPreviewArray();  
        } 
        public CreateAvatarResp(ushort retCode, ulong avatarID, AvatarPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.avatarID = avatarID; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            if (this.previews == null) this.previews = new AvatarPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.previews = new AvatarPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachAvatarReq: Proto4z.IProtoObject //选角色请求  
    {     
        //proto id   
        public const ushort protoID = 40005;  
        static public ushort getProtoID() { return 40005; } 
        static public string getProtoName() { return "AttachAvatarReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public ulong avatarID;  
        public AttachAvatarReq()  
        { 
            accountName = "";  
            avatarID = 0;  
        } 
        public AttachAvatarReq(string accountName, ulong avatarID) 
        { 
            this.accountName = accountName; 
            this.avatarID = avatarID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachAvatarResp: Proto4z.IProtoObject //选角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 40006;  
        static public ushort getProtoID() { return 40006; } 
        static public string getProtoName() { return "AttachAvatarResp"; } 
        //members   
        public ushort retCode;  
        public AvatarBaseInfo baseInfo;  
        public AvatarPropMap props;  
        public AttachAvatarResp()  
        { 
            retCode = 0;  
            baseInfo = new AvatarBaseInfo();  
            props = new AvatarPropMap();  
        } 
        public AttachAvatarResp(ushort retCode, AvatarBaseInfo baseInfo, AvatarPropMap props) 
        { 
            this.retCode = retCode; 
            this.baseInfo = baseInfo; 
            this.props = props; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.props == null) this.props = new AvatarPropMap(); 
            data.AddRange(this.props.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.props = new AvatarPropMap(); 
            this.props.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class GetSceneTokenInfoReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40007;  
        static public ushort getProtoID() { return 40007; } 
        static public string getProtoName() { return "GetSceneTokenInfoReq"; } 
        //members   
        public GetSceneTokenInfoReq()  
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
 
    public class GetSceneTokenInfoResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40008;  
        static public ushort getProtoID() { return 40008; } 
        static public string getProtoName() { return "GetSceneTokenInfoResp"; } 
        //members   
        public ushort retCode;  
        public SceneTokenInfo tokenInfo;  
        public GetSceneTokenInfoResp()  
        { 
            retCode = 0;  
            tokenInfo = new SceneTokenInfo();  
        } 
        public GetSceneTokenInfoResp(ushort retCode, SceneTokenInfo tokenInfo) 
        { 
            this.retCode = retCode; 
            this.tokenInfo = tokenInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.tokenInfo == null) this.tokenInfo = new SceneTokenInfo(); 
            data.AddRange(this.tokenInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.tokenInfo = new SceneTokenInfo(); 
            this.tokenInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class JoinSceneReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40009;  
        static public ushort getProtoID() { return 40009; } 
        static public string getProtoName() { return "JoinSceneReq"; } 
        //members   
        public ushort spaceType;  
        public uint mapID;  
        public JoinSceneReq()  
        { 
            spaceType = 0;  
            mapID = 0;  
        } 
        public JoinSceneReq(ushort spaceType, uint mapID) 
        { 
            this.spaceType = spaceType; 
            this.mapID = mapID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.spaceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.mapID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class JoinSceneResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40010;  
        static public ushort getProtoID() { return 40010; } 
        static public string getProtoName() { return "JoinSceneResp"; } 
        //members   
        public ushort retCode;  
        public SceneTokenInfo tokenInfo;  
        public JoinSceneResp()  
        { 
            retCode = 0;  
            tokenInfo = new SceneTokenInfo();  
        } 
        public JoinSceneResp(ushort retCode, SceneTokenInfo tokenInfo) 
        { 
            this.retCode = retCode; 
            this.tokenInfo = tokenInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.tokenInfo == null) this.tokenInfo = new SceneTokenInfo(); 
            data.AddRange(this.tokenInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.tokenInfo = new SceneTokenInfo(); 
            this.tokenInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class JoinSceneNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40011;  
        static public ushort getProtoID() { return 40011; } 
        static public string getProtoName() { return "JoinSceneNotice"; } 
        //members   
        public SceneTokenInfo tokenInfo;  
        public JoinSceneNotice()  
        { 
            tokenInfo = new SceneTokenInfo();  
        } 
        public JoinSceneNotice(SceneTokenInfo tokenInfo) 
        { 
            this.tokenInfo = tokenInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.tokenInfo == null) this.tokenInfo = new SceneTokenInfo(); 
            data.AddRange(this.tokenInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.tokenInfo = new SceneTokenInfo(); 
            this.tokenInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSceneReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40012;  
        static public ushort getProtoID() { return 40012; } 
        static public string getProtoName() { return "LeaveSceneReq"; } 
        //members   
        public uint spaceID;  
        public LeaveSceneReq()  
        { 
            spaceID = 0;  
        } 
        public LeaveSceneReq(uint spaceID) 
        { 
            this.spaceID = spaceID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSceneResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40013;  
        static public ushort getProtoID() { return 40013; } 
        static public string getProtoName() { return "LeaveSceneResp"; } 
        //members   
        public ushort retCode;  
        public SceneTokenInfo tokenInfo;  
        public LeaveSceneResp()  
        { 
            retCode = 0;  
            tokenInfo = new SceneTokenInfo();  
        } 
        public LeaveSceneResp(ushort retCode, SceneTokenInfo tokenInfo) 
        { 
            this.retCode = retCode; 
            this.tokenInfo = tokenInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.tokenInfo == null) this.tokenInfo = new SceneTokenInfo(); 
            data.AddRange(this.tokenInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.tokenInfo = new SceneTokenInfo(); 
            this.tokenInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40014;  
        static public ushort getProtoID() { return 40014; } 
        static public string getProtoName() { return "ChatReq"; } 
        //members   
        public ushort channelID;  
        public ulong targetID;  
        public string msg;  
        public ChatReq()  
        { 
            channelID = 0;  
            targetID = 0;  
            msg = "";  
        } 
        public ChatReq(ushort channelID, ulong targetID, string msg) 
        { 
            this.channelID = channelID; 
            this.targetID = targetID; 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.channelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.targetID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.channelID = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.targetID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40015;  
        static public ushort getProtoID() { return 40015; } 
        static public string getProtoName() { return "ChatResp"; } 
        //members   
        public ushort channelID;  
        public ulong sourceID;  
        public string sourceName;  
        public ulong targetID;  
        public string targetName;  
        public string msg;  
        public ulong chatTime;  
        public ChatResp()  
        { 
            channelID = 0;  
            sourceID = 0;  
            sourceName = "";  
            targetID = 0;  
            targetName = "";  
            msg = "";  
            chatTime = 0;  
        } 
        public ChatResp(ushort channelID, ulong sourceID, string sourceName, ulong targetID, string targetName, string msg, ulong chatTime) 
        { 
            this.channelID = channelID; 
            this.sourceID = sourceID; 
            this.sourceName = sourceName; 
            this.targetID = targetID; 
            this.targetName = targetName; 
            this.msg = msg; 
            this.chatTime = chatTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.channelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sourceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sourceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.targetID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.targetName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.chatTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.channelID = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.sourceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sourceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.targetID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.targetName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.chatTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PingPongReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40016;  
        static public ushort getProtoID() { return 40016; } 
        static public string getProtoName() { return "PingPongReq"; } 
        //members   
        public string msg;  
        public PingPongReq()  
        { 
            msg = "";  
        } 
        public PingPongReq(string msg) 
        { 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PingPongResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40017;  
        static public ushort getProtoID() { return 40017; } 
        static public string getProtoName() { return "PingPongResp"; } 
        //members   
        public string msg;  
        public PingPongResp()  
        { 
            msg = "";  
        } 
        public PingPongResp(string msg) 
        { 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeIconIDReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40018;  
        static public ushort getProtoID() { return 40018; } 
        static public string getProtoName() { return "ChangeIconIDReq"; } 
        //members   
        public short iconID;  
        public ChangeIconIDReq()  
        { 
            iconID = 0;  
        } 
        public ChangeIconIDReq(short iconID) 
        { 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(this.iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.iconID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeIconIDResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40019;  
        static public ushort getProtoID() { return 40019; } 
        static public string getProtoName() { return "ChangeIconIDResp"; } 
        //members   
        public ushort retCode;  
        public short iconID;  
        public ChangeIconIDResp()  
        { 
            retCode = 0;  
            iconID = 0;  
        } 
        public ChangeIconIDResp(ushort retCode, short iconID) 
        { 
            this.retCode = retCode; 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(this.iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeModeIDReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40020;  
        static public ushort getProtoID() { return 40020; } 
        static public string getProtoName() { return "ChangeModeIDReq"; } 
        //members   
        public short modeID;  
        public ChangeModeIDReq()  
        { 
            modeID = 0;  
        } 
        public ChangeModeIDReq(short modeID) 
        { 
            this.modeID = modeID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(this.modeID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.modeID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeModeIDResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40021;  
        static public ushort getProtoID() { return 40021; } 
        static public string getProtoName() { return "ChangeModeIDResp"; } 
        //members   
        public ushort retCode;  
        public short modeID;  
        public ChangeModeIDResp()  
        { 
            retCode = 0;  
            modeID = 0;  
        } 
        public ChangeModeIDResp(ushort retCode, short modeID) 
        { 
            this.retCode = retCode; 
            this.modeID = modeID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(this.modeID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
