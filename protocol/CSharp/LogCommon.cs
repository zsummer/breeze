 
namespace Proto4z  
{ 
 
    public class LogLogin: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 20000;  
        static public ushort getProtoID() { return 20000; } 
        static public string getProtoName() { return "LogLogin"; } 
        //members   
        public ulong id;  
        public ulong logTime;  
        public ulong avatarID;  
        public string avatarName;  
        public string deviceInfo;  
        public LogLogin()  
        { 
            id = 0;  
            logTime = 0;  
            avatarID = 0;  
            avatarName = "";  
            deviceInfo = "";  
        } 
        public LogLogin(ulong id, ulong logTime, ulong avatarID, string avatarName, string deviceInfo) 
        { 
            this.id = id; 
            this.logTime = logTime; 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.deviceInfo = deviceInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.logTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.deviceInfo)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.logTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.deviceInfo = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LogQuit: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 20001;  
        static public ushort getProtoID() { return 20001; } 
        static public string getProtoName() { return "LogQuit"; } 
        //members   
        public ulong id;  
        public ulong logTime;  
        public ulong avatarID;  
        public string avatarName;  
        public LogQuit()  
        { 
            id = 0;  
            logTime = 0;  
            avatarID = 0;  
            avatarName = "";  
        } 
        public LogQuit(ulong id, ulong logTime, ulong avatarID, string avatarName) 
        { 
            this.id = id; 
            this.logTime = logTime; 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.logTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.logTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
