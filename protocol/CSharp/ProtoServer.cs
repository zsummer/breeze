 
namespace Proto4z  
{ 
 
    class Heartbeat: Proto4z.IProtoObject //心跳包  
    {     
        static public System.UInt16 getProtoID() { return 50000; } 
        static public string getProtoName() { return "Heartbeat"; } 
        public System.UInt32 timeStamp; //服务器当前UTC时间戳  
        public System.UInt32 timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeStamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeTick)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            timeStamp = 0; 
                timeStamp = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            timeTick = 0; 
                timeTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class HeartbeatEcho: Proto4z.IProtoObject //心跳包需要立刻回复  
    {     
        static public System.UInt16 getProtoID() { return 50001; } 
        static public string getProtoName() { return "HeartbeatEcho"; } 
        public System.UInt32 timeStamp; //服务器当前UTC时间戳  
        public System.UInt32 timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeStamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(timeTick)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            timeStamp = 0; 
                timeStamp = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            timeTick = 0; 
                timeTick = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class PlatAuthReq: Proto4z.IProtoObject //平台认证  
    {     
        static public System.UInt16 getProtoID() { return 50002; } 
        static public string getProtoName() { return "PlatAuthReq"; } 
        public System.String account; //用户名  
        public System.String token; //令牌  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
                account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class PlatAuthAck: Proto4z.IProtoObject //认证结果, 包含该用户的所有用户/角色数据  
    {     
        static public System.UInt16 getProtoID() { return 50003; } 
        static public string getProtoName() { return "PlatAuthAck"; } 
        public System.UInt16 retCode;  
        public BaseInfoArray users; //该帐号下的所有用户信息  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(users.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            users = new BaseInfoArray(); 
                users.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class CreateUserReq: Proto4z.IProtoObject //创建一个新的用户数据  
    {     
        static public System.UInt16 getProtoID() { return 50004; } 
        static public string getProtoName() { return "CreateUserReq"; } 
        public System.String nickName; //昵称  
        public System.Int32 iconID; //头像  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(nickName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(iconID)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
                nickName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            iconID = 0; 
                iconID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class CreateUserAck: Proto4z.IProtoObject //创建结果和所有用户数据  
    {     
        static public System.UInt16 getProtoID() { return 50005; } 
        static public string getProtoName() { return "CreateUserAck"; } 
        public System.UInt16 retCode;  
        public BaseInfoArray users; //该帐号下的所有用户信息  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(users.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            users = new BaseInfoArray(); 
                users.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class SelectUserReq: Proto4z.IProtoObject //获取需要登录用户的所在服务器和认证令牌  
    {     
        static public System.UInt16 getProtoID() { return 50006; } 
        static public string getProtoName() { return "SelectUserReq"; } 
        public System.UInt64 uID;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class SelectUserAck: Proto4z.IProtoObject //获取需要登录用户的所在服务器和认证令牌  
    {     
        static public System.UInt16 getProtoID() { return 50007; } 
        static public string getProtoName() { return "SelectUserAck"; } 
        public System.UInt16 retCode;  
        public System.UInt64 uID;  
        public System.String token;  
        public System.String ip;  
        public System.UInt16 port;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(ip)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(port)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                ip = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            port = 0; 
                port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class AttachLogicReq: Proto4z.IProtoObject //挂到logic服务器上  
    {     
        static public System.UInt16 getProtoID() { return 50008; } 
        static public string getProtoName() { return "AttachLogicReq"; } 
        public System.UInt64 uID;  
        public System.String token;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class AttachLogicAck: Proto4z.IProtoObject //挂到logic服务器上  
    {     
        static public System.UInt16 getProtoID() { return 50009; } 
        static public string getProtoName() { return "AttachLogicAck"; } 
        public System.UInt16 retCode;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
