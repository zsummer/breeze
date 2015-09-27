 
namespace Proto4z  
{ 
 
    public enum  : byte 
    { 
        CHANNEL_PRIVATE = 0, //私聊, 需要指明具体某个uid  
        CHANNEL_WORLD = 1, //世界  
        CHANNEL_GROUP = 2, //群组, 需要指明具体某个groupid  
    }; 
 
    public class JoinGropuReq: Proto4z.IProtoObject //加入频道  
    {     
        //proto id   
        public const ushort protoID = 1100;  
        static public ushort getProtoID() { return 1100; } 
        static public string getProtoName() { return "JoinGropuReq"; } 
        //members   
        public byte chlType; //channel type  
        public JoinGropuReq()  
        { 
            chlType = 0;  
        } 
        public JoinGropuReq(byte chlType) 
        { 
            this.chlType = chlType; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class JoinGropuAck: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 1101;  
        static public ushort getProtoID() { return 1101; } 
        static public string getProtoName() { return "JoinGropuAck"; } 
        //members   
        public ushort retCode;  
        public byte chlType; //channel type  
        public JoinGropuAck()  
        { 
            retCode = 0;  
            chlType = 0;  
        } 
        public JoinGropuAck(ushort retCode, byte chlType) 
        { 
            this.retCode = retCode; 
            this.chlType = chlType; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveGropuReq: Proto4z.IProtoObject //加入频道  
    {     
        //proto id   
        public const ushort protoID = 1102;  
        static public ushort getProtoID() { return 1102; } 
        static public string getProtoName() { return "LeaveGropuReq"; } 
        //members   
        public byte chlType; //channel type  
        public LeaveGropuReq()  
        { 
            chlType = 0;  
        } 
        public LeaveGropuReq(byte chlType) 
        { 
            this.chlType = chlType; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveGropuAck: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 1103;  
        static public ushort getProtoID() { return 1103; } 
        static public string getProtoName() { return "LeaveGropuAck"; } 
        //members   
        public ushort retCode;  
        public byte chlType; //channel type  
        public LeaveGropuAck()  
        { 
            retCode = 0;  
            chlType = 0;  
        } 
        public LeaveGropuAck(ushort retCode, byte chlType) 
        { 
            this.retCode = retCode; 
            this.chlType = chlType; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatInfo: Proto4z.IProtoObject //聊天消息  
    {     
        //members   
        public ulong mID; //msg id  
        public byte chlType; //channel type  
        public ulong srcID;  
        public string srcName; //src  
        public short srcIcon; //src  
        public ulong dstID; //userid or groupid  
        public string dstName; //src  
        public short dstIcon; //src  
        public string msg;  
        public uint sendTime;  
        public ChatInfo()  
        { 
            mID = 0;  
            chlType = 0;  
            srcID = 0;  
            srcName = "";  
            srcIcon = 0;  
            dstID = 0;  
            dstName = "";  
            dstIcon = 0;  
            msg = "";  
            sendTime = 0;  
        } 
        public ChatInfo(ulong mID, byte chlType, ulong srcID, string srcName, short srcIcon, ulong dstID, string dstName, short dstIcon, string msg, uint sendTime) 
        { 
            this.mID = mID; 
            this.chlType = chlType; 
            this.srcID = srcID; 
            this.srcName = srcName; 
            this.srcIcon = srcIcon; 
            this.dstID = dstID; 
            this.dstName = dstName; 
            this.dstIcon = dstIcon; 
            this.msg = msg; 
            this.sendTime = sendTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(mID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(srcID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(srcName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(srcIcon)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dstID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(dstName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(dstIcon)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(msg)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(sendTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.mID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.srcID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.srcName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.srcIcon = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            this.dstID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dstName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.dstIcon = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.sendTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class ChatInfoArray : System.Collections.Generic.List<ChatInfo>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            int len = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            if(len > 0) 
            { 
                for (int i=0; i<len; i++) 
                { 
                    var data = new ChatInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class ChatReq: Proto4z.IProtoObject //发送聊天请求  
    {     
        //proto id   
        public const ushort protoID = 1104;  
        static public ushort getProtoID() { return 1104; } 
        static public string getProtoName() { return "ChatReq"; } 
        //members   
        public byte chlType; //channel type  
        public ulong dstID; //userID or groupID  
        public string msg; //msg  
        public ChatReq()  
        { 
            chlType = 0;  
            dstID = 0;  
            msg = "";  
        } 
        public ChatReq(byte chlType, ulong dstID, string msg) 
        { 
            this.chlType = chlType; 
            this.dstID = dstID; 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dstID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.dstID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatAck: Proto4z.IProtoObject //发送聊天请求  
    {     
        //proto id   
        public const ushort protoID = 1105;  
        static public ushort getProtoID() { return 1105; } 
        static public string getProtoName() { return "ChatAck"; } 
        //members   
        public ushort retCode;  
        public byte chlType; //channel type  
        public ulong dstID; //userID or groupID  
        public ulong msgID;  
        public ChatAck()  
        { 
            retCode = 0;  
            chlType = 0;  
            dstID = 0;  
            msgID = 0;  
        } 
        public ChatAck(ushort retCode, byte chlType, ulong dstID, ulong msgID) 
        { 
            this.retCode = retCode; 
            this.chlType = chlType; 
            this.dstID = dstID; 
            this.msgID = msgID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dstID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(msgID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.dstID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.msgID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatNotice: Proto4z.IProtoObject //聊天通知  
    {     
        //proto id   
        public const ushort protoID = 1106;  
        static public ushort getProtoID() { return 1106; } 
        static public string getProtoName() { return "ChatNotice"; } 
        //members   
        public ushort retCode;  
        public ChatInfoArray msgs;  
        public ChatNotice()  
        { 
            retCode = 0;  
            msgs = new ChatInfoArray();  
        } 
        public ChatNotice(ushort retCode, ChatInfoArray msgs) 
        { 
            this.retCode = retCode; 
            this.msgs = msgs; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            if (msgs == null) msgs = new ChatInfoArray(); 
            data.AddRange(msgs.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.msgs = new ChatInfoArray(); 
            this.msgs.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
