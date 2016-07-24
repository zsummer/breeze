 
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
        public UserPreviewArray previews;  
        public ClientAuthResp()  
        { 
            retCode = 0;  
            account = "";  
            token = "";  
            previews = new UserPreviewArray();  
        } 
        public ClientAuthResp(ushort retCode, string account, string token, UserPreviewArray previews) 
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
            if (this.previews == null) this.previews = new UserPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.previews = new UserPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateUserReq: Proto4z.IProtoObject //创角色请求  
    {     
        //proto id   
        public const ushort protoID = 40003;  
        static public ushort getProtoID() { return 40003; } 
        static public string getProtoName() { return "CreateUserReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public string userName;  
        public CreateUserReq()  
        { 
            accountName = "";  
            userName = "";  
        } 
        public CreateUserReq(string accountName, string userName) 
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
 
    public class CreateUserResp: Proto4z.IProtoObject //创角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 40004;  
        static public ushort getProtoID() { return 40004; } 
        static public string getProtoName() { return "CreateUserResp"; } 
        //members   
        public ushort retCode;  
        public ulong userID;  
        public UserPreviewArray previews;  
        public CreateUserResp()  
        { 
            retCode = 0;  
            userID = 0;  
            previews = new UserPreviewArray();  
        } 
        public CreateUserResp(ushort retCode, ulong userID, UserPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.previews == null) this.previews = new UserPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.previews = new UserPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachUserReq: Proto4z.IProtoObject //选角色请求  
    {     
        //proto id   
        public const ushort protoID = 40005;  
        static public ushort getProtoID() { return 40005; } 
        static public string getProtoName() { return "AttachUserReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public ulong userID;  
        public AttachUserReq()  
        { 
            accountName = "";  
            userID = 0;  
        } 
        public AttachUserReq(string accountName, ulong userID) 
        { 
            this.accountName = accountName; 
            this.userID = userID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachUserResp: Proto4z.IProtoObject //选角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 40006;  
        static public ushort getProtoID() { return 40006; } 
        static public string getProtoName() { return "AttachUserResp"; } 
        //members   
        public ushort retCode;  
        public ulong userID;  
        public AttachUserResp()  
        { 
            retCode = 0;  
            userID = 0;  
        } 
        public AttachUserResp(ushort retCode, ulong userID) 
        { 
            this.retCode = retCode; 
            this.userID = userID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class GetSpaceInfoReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40022;  
        static public ushort getProtoID() { return 40022; } 
        static public string getProtoName() { return "GetSpaceInfoReq"; } 
        //members   
        public GetSpaceInfoReq()  
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
 
    public class GetSpaceInfoResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40023;  
        static public ushort getProtoID() { return 40023; } 
        static public string getProtoName() { return "GetSpaceInfoResp"; } 
        //members   
        public SpaceTokenInfo spaceInfo;  
        public GetSpaceInfoResp()  
        { 
            spaceInfo = new SpaceTokenInfo();  
        } 
        public GetSpaceInfoResp(SpaceTokenInfo spaceInfo) 
        { 
            this.spaceInfo = spaceInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.spaceInfo == null) this.spaceInfo = new SpaceTokenInfo(); 
            data.AddRange(this.spaceInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceInfo = new SpaceTokenInfo(); 
            this.spaceInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class JoinSpaceReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40020;  
        static public ushort getProtoID() { return 40020; } 
        static public string getProtoName() { return "JoinSpaceReq"; } 
        //members   
        public ushort spaceType;  
        public uint mapID;  
        public JoinSpaceReq()  
        { 
            spaceType = 0;  
            mapID = 0;  
        } 
        public JoinSpaceReq(ushort spaceType, uint mapID) 
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
 
    public class JoinSpaceResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40021;  
        static public ushort getProtoID() { return 40021; } 
        static public string getProtoName() { return "JoinSpaceResp"; } 
        //members   
        public ushort retCode;  
        public SpaceTokenInfo spaceInfo;  
        public JoinSpaceResp()  
        { 
            retCode = 0;  
            spaceInfo = new SpaceTokenInfo();  
        } 
        public JoinSpaceResp(ushort retCode, SpaceTokenInfo spaceInfo) 
        { 
            this.retCode = retCode; 
            this.spaceInfo = spaceInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.spaceInfo == null) this.spaceInfo = new SpaceTokenInfo(); 
            data.AddRange(this.spaceInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceInfo = new SpaceTokenInfo(); 
            this.spaceInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class JoinSpaceNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40024;  
        static public ushort getProtoID() { return 40024; } 
        static public string getProtoName() { return "JoinSpaceNotice"; } 
        //members   
        public SpaceTokenInfo spaceInfo;  
        public JoinSpaceNotice()  
        { 
            spaceInfo = new SpaceTokenInfo();  
        } 
        public JoinSpaceNotice(SpaceTokenInfo spaceInfo) 
        { 
            this.spaceInfo = spaceInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.spaceInfo == null) this.spaceInfo = new SpaceTokenInfo(); 
            data.AddRange(this.spaceInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceInfo = new SpaceTokenInfo(); 
            this.spaceInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSpaceReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40025;  
        static public ushort getProtoID() { return 40025; } 
        static public string getProtoName() { return "LeaveSpaceReq"; } 
        //members   
        public uint spaceID;  
        public LeaveSpaceReq()  
        { 
            spaceID = 0;  
        } 
        public LeaveSpaceReq(uint spaceID) 
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
 
    public class LeaveSpaceResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40026;  
        static public ushort getProtoID() { return 40026; } 
        static public string getProtoName() { return "LeaveSpaceResp"; } 
        //members   
        public ushort retCode;  
        public SpaceTokenInfo spaceInfo;  
        public LeaveSpaceResp()  
        { 
            retCode = 0;  
            spaceInfo = new SpaceTokenInfo();  
        } 
        public LeaveSpaceResp(ushort retCode, SpaceTokenInfo spaceInfo) 
        { 
            this.retCode = retCode; 
            this.spaceInfo = spaceInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.spaceInfo == null) this.spaceInfo = new SpaceTokenInfo(); 
            data.AddRange(this.spaceInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceInfo = new SpaceTokenInfo(); 
            this.spaceInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserChatReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40007;  
        static public ushort getProtoID() { return 40007; } 
        static public string getProtoName() { return "UserChatReq"; } 
        //members   
        public ulong userID;  
        public string msg;  
        public UserChatReq()  
        { 
            userID = 0;  
            msg = "";  
        } 
        public UserChatReq(ulong userID, string msg) 
        { 
            this.userID = userID; 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserChatResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40008;  
        static public ushort getProtoID() { return 40008; } 
        static public string getProtoName() { return "UserChatResp"; } 
        //members   
        public ulong fromUserID;  
        public string msg;  
        public UserChatResp()  
        { 
            fromUserID = 0;  
            msg = "";  
        } 
        public UserChatResp(ulong fromUserID, string msg) 
        { 
            this.fromUserID = fromUserID; 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.fromUserID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.fromUserID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserPingPongReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40009;  
        static public ushort getProtoID() { return 40009; } 
        static public string getProtoName() { return "UserPingPongReq"; } 
        //members   
        public string msg;  
        public UserPingPongReq()  
        { 
            msg = "";  
        } 
        public UserPingPongReq(string msg) 
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
 
    public class UserPingPongResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40010;  
        static public ushort getProtoID() { return 40010; } 
        static public string getProtoName() { return "UserPingPongResp"; } 
        //members   
        public string msg;  
        public UserPingPongResp()  
        { 
            msg = "";  
        } 
        public UserPingPongResp(string msg) 
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
 
} 
 
 
