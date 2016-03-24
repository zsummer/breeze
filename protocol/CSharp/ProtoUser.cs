 
namespace Proto4z  
{ 
 
    public class ClientAuthReq: Proto4z.IProtoObject //认证请求  
    {     
        //proto id   
        public const ushort protoID = 1000;  
        static public ushort getProtoID() { return 1000; } 
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
        public const ushort protoID = 1001;  
        static public ushort getProtoID() { return 1001; } 
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
 
    public class UserAuthReq: Proto4z.IProtoObject //认证请求  
    {     
        //proto id   
        public const ushort protoID = 1002;  
        static public ushort getProtoID() { return 1002; } 
        static public string getProtoName() { return "UserAuthReq"; } 
        //members   
        public string account;  
        public string token;  
        public uint clientSessionID;  
        public uint clientClusterID;  
        public UserAuthReq()  
        { 
            account = "";  
            token = "";  
            clientSessionID = 0;  
            clientClusterID = 0;  
        } 
        public UserAuthReq(string account, string token, uint clientSessionID, uint clientClusterID) 
        { 
            this.account = account; 
            this.token = token; 
            this.clientSessionID = clientSessionID; 
            this.clientClusterID = clientClusterID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientClusterID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientClusterID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserAuthResp: Proto4z.IProtoObject //认证回复  
    {     
        //proto id   
        public const ushort protoID = 1003;  
        static public ushort getProtoID() { return 1003; } 
        static public string getProtoName() { return "UserAuthResp"; } 
        //members   
        public ushort retCode;  
        public string account;  
        public string token;  
        public uint clientSessionID;  
        public uint clientClusterID;  
        public UserPreviewArray previews;  
        public UserAuthResp()  
        { 
            retCode = 0;  
            account = "";  
            token = "";  
            clientSessionID = 0;  
            clientClusterID = 0;  
            previews = new UserPreviewArray();  
        } 
        public UserAuthResp(ushort retCode, string account, string token, uint clientSessionID, uint clientClusterID, UserPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.account = account; 
            this.token = token; 
            this.clientSessionID = clientSessionID; 
            this.clientClusterID = clientClusterID; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientClusterID)); 
            if (this.previews == null) this.previews = new UserPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientClusterID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.previews = new UserPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateUserReq: Proto4z.IProtoObject //创角色请求  
    {     
        //proto id   
        public const ushort protoID = 1004;  
        static public ushort getProtoID() { return 1004; } 
        static public string getProtoName() { return "CreateUserReq"; } 
        //members   
        public string nickname;  
        public CreateUserReq()  
        { 
            nickname = "";  
        } 
        public CreateUserReq(string nickname) 
        { 
            this.nickname = nickname; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.nickname)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.nickname = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateUserResp: Proto4z.IProtoObject //创角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 1005;  
        static public ushort getProtoID() { return 1005; } 
        static public string getProtoName() { return "CreateUserResp"; } 
        //members   
        public ushort retCode;  
        public UserPreviewArray previews;  
        public CreateUserResp()  
        { 
            retCode = 0;  
            previews = new UserPreviewArray();  
        } 
        public CreateUserResp(ushort retCode, UserPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.previews == null) this.previews = new UserPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.previews = new UserPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SelectUserReq: Proto4z.IProtoObject //选角色请求  
    {     
        //proto id   
        public const ushort protoID = 1006;  
        static public ushort getProtoID() { return 1006; } 
        static public string getProtoName() { return "SelectUserReq"; } 
        //members   
        public ulong uID;  
        public SelectUserReq()  
        { 
            uID = 0;  
        } 
        public SelectUserReq(ulong uID) 
        { 
            this.uID = uID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SelectUserResp: Proto4z.IProtoObject //选角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 1007;  
        static public ushort getProtoID() { return 1007; } 
        static public string getProtoName() { return "SelectUserResp"; } 
        //members   
        public ushort retCode;  
        public string svrIP;  
        public ushort svrPort;  
        public ulong uID;  
        public string token;  
        public SelectUserResp()  
        { 
            retCode = 0;  
            svrIP = "";  
            svrPort = 0;  
            uID = 0;  
            token = "";  
        } 
        public SelectUserResp(ushort retCode, string svrIP, ushort svrPort, ulong uID, string token) 
        { 
            this.retCode = retCode; 
            this.svrIP = svrIP; 
            this.svrPort = svrPort; 
            this.uID = uID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.svrIP)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.svrPort)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.svrIP = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.svrPort = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LoginUserReq: Proto4z.IProtoObject //登录角色请求  
    {     
        //proto id   
        public const ushort protoID = 1008;  
        static public ushort getProtoID() { return 1008; } 
        static public string getProtoName() { return "LoginUserReq"; } 
        //members   
        public ulong uID;  
        public string token;  
        public LoginUserReq()  
        { 
            uID = 0;  
            token = "";  
        } 
        public LoginUserReq(ulong uID, string token) 
        { 
            this.uID = uID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LoginUserResp: Proto4z.IProtoObject //登录角色返回  
    {     
        //proto id   
        public const ushort protoID = 1009;  
        static public ushort getProtoID() { return 1009; } 
        static public string getProtoName() { return "LoginUserResp"; } 
        //members   
        public ushort retCode;  
        public LoginUserResp()  
        { 
            retCode = 0;  
        } 
        public LoginUserResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
