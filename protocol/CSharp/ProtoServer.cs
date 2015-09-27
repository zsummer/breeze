 
namespace Proto4z  
{ 
 
    public class Heartbeat: Proto4z.IProtoObject //心跳包  
    {     
        //proto id   
        public const ushort protoID = 50000;  
        static public ushort getProtoID() { return 50000; } 
        static public string getProtoName() { return "Heartbeat"; } 
        //members   
        public uint timeStamp; //服务器当前UTC时间戳  
        public uint timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0  
        public Heartbeat()  
        { 
            timeStamp = 0;  
            timeTick = 0;  
        } 
        public Heartbeat(uint timeStamp, uint timeTick) 
        { 
            this.timeStamp = timeStamp; 
            this.timeTick = timeTick; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeStamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeTick)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.timeStamp = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.timeTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class HeartbeatEcho: Proto4z.IProtoObject //心跳包需要立刻回复  
    {     
        //proto id   
        public const ushort protoID = 50001;  
        static public ushort getProtoID() { return 50001; } 
        static public string getProtoName() { return "HeartbeatEcho"; } 
        //members   
        public uint timeStamp; //服务器当前UTC时间戳  
        public uint timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0  
        public HeartbeatEcho()  
        { 
            timeStamp = 0;  
            timeTick = 0;  
        } 
        public HeartbeatEcho(uint timeStamp, uint timeTick) 
        { 
            this.timeStamp = timeStamp; 
            this.timeTick = timeTick; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeStamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeTick)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.timeStamp = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.timeTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PlatAuthReq: Proto4z.IProtoObject //平台认证  
    {     
        //proto id   
        public const ushort protoID = 50002;  
        static public ushort getProtoID() { return 50002; } 
        static public string getProtoName() { return "PlatAuthReq"; } 
        //members   
        public string account; //用户名  
        public string token; //令牌  
        public PlatAuthReq()  
        { 
            account = "";  
            token = "";  
        } 
        public PlatAuthReq(string account, string token) 
        { 
            this.account = account; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PlatAuthAck: Proto4z.IProtoObject //认证结果, 包含该用户的所有用户/角色数据  
    {     
        //proto id   
        public const ushort protoID = 50003;  
        static public ushort getProtoID() { return 50003; } 
        static public string getProtoName() { return "PlatAuthAck"; } 
        //members   
        public ushort retCode;  
        public BaseInfoArray users; //该帐号下的所有用户信息  
        public PlatAuthAck()  
        { 
            retCode = 0;  
            users = new BaseInfoArray();  
        } 
        public PlatAuthAck(ushort retCode, BaseInfoArray users) 
        { 
            this.retCode = retCode; 
            this.users = users; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            if (users == null) users = new BaseInfoArray(); 
            data.AddRange(users.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.users = new BaseInfoArray(); 
            this.users.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateUserReq: Proto4z.IProtoObject //创建一个新的用户数据  
    {     
        //proto id   
        public const ushort protoID = 50004;  
        static public ushort getProtoID() { return 50004; } 
        static public string getProtoName() { return "CreateUserReq"; } 
        //members   
        public string nickName; //昵称  
        public int iconID; //头像  
        public CreateUserReq()  
        { 
            nickName = "";  
            iconID = 0;  
        } 
        public CreateUserReq(string nickName, int iconID) 
        { 
            this.nickName = nickName; 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(nickName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.nickName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateUserAck: Proto4z.IProtoObject //创建结果和所有用户数据  
    {     
        //proto id   
        public const ushort protoID = 50005;  
        static public ushort getProtoID() { return 50005; } 
        static public string getProtoName() { return "CreateUserAck"; } 
        //members   
        public ushort retCode;  
        public BaseInfoArray users; //该帐号下的所有用户信息  
        public CreateUserAck()  
        { 
            retCode = 0;  
            users = new BaseInfoArray();  
        } 
        public CreateUserAck(ushort retCode, BaseInfoArray users) 
        { 
            this.retCode = retCode; 
            this.users = users; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            if (users == null) users = new BaseInfoArray(); 
            data.AddRange(users.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.users = new BaseInfoArray(); 
            this.users.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SelectUserReq: Proto4z.IProtoObject //获取需要登录用户的所在服务器和认证令牌  
    {     
        //proto id   
        public const ushort protoID = 50006;  
        static public ushort getProtoID() { return 50006; } 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SelectUserAck: Proto4z.IProtoObject //获取需要登录用户的所在服务器和认证令牌  
    {     
        //proto id   
        public const ushort protoID = 50007;  
        static public ushort getProtoID() { return 50007; } 
        static public string getProtoName() { return "SelectUserAck"; } 
        //members   
        public ushort retCode;  
        public ulong uID;  
        public string token;  
        public string ip;  
        public ushort port;  
        public SelectUserAck()  
        { 
            retCode = 0;  
            uID = 0;  
            token = "";  
            ip = "";  
            port = 0;  
        } 
        public SelectUserAck(ushort retCode, ulong uID, string token, string ip, ushort port) 
        { 
            this.retCode = retCode; 
            this.uID = uID; 
            this.token = token; 
            this.ip = ip; 
            this.port = port; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(ip)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(port)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.ip = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachLogicReq: Proto4z.IProtoObject //挂到logic服务器上  
    {     
        //proto id   
        public const ushort protoID = 50008;  
        static public ushort getProtoID() { return 50008; } 
        static public string getProtoName() { return "AttachLogicReq"; } 
        //members   
        public ulong uID;  
        public string token;  
        public AttachLogicReq()  
        { 
            uID = 0;  
            token = "";  
        } 
        public AttachLogicReq(ulong uID, string token) 
        { 
            this.uID = uID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachLogicAck: Proto4z.IProtoObject //挂到logic服务器上  
    {     
        //proto id   
        public const ushort protoID = 50009;  
        static public ushort getProtoID() { return 50009; } 
        static public string getProtoName() { return "AttachLogicAck"; } 
        //members   
        public ushort retCode;  
        public AttachLogicAck()  
        { 
            retCode = 0;  
        } 
        public AttachLogicAck(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
