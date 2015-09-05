 
namespace Proto4z  
{ 
    class STATIC_CHANNEL_PRIVATE //私聊, 需要指明具体某个uid 
    { 
        public static System.Byte value = 0;  
    } 
    class STATIC_CHANNEL_WORLD //世界 
    { 
        public static System.Byte value = 1;  
    } 
    class STATIC_CHANNEL_GROUP //群组, 需要指明具体某个groupid 
    { 
        public static System.Byte value = 2;  
    } 
 
    class JoinGropuReq: Proto4z.IProtoObject //加入频道 
    {     
        static public System.UInt16 getProtoID() { return 1100; } 
        static public string getProtoName() { return "JoinGropuReq"; } 
        public System.Byte chlType; //channel type 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class JoinGropuAck: Proto4z.IProtoObject 
    {     
        static public System.UInt16 getProtoID() { return 1101; } 
        static public string getProtoName() { return "JoinGropuAck"; } 
        public System.UInt16 retCode;  
        public System.Byte chlType; //channel type 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class LeaveGropuReq: Proto4z.IProtoObject //加入频道 
    {     
        static public System.UInt16 getProtoID() { return 1102; } 
        static public string getProtoName() { return "LeaveGropuReq"; } 
        public System.Byte chlType; //channel type 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class LeaveGropuAck: Proto4z.IProtoObject 
    {     
        static public System.UInt16 getProtoID() { return 1103; } 
        static public string getProtoName() { return "LeaveGropuAck"; } 
        public System.UInt16 retCode;  
        public System.Byte chlType; //channel type 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class ChatInfo: Proto4z.IProtoObject //聊天消息 
    {     
        public System.UInt64 mID; //msg id 
        public System.Byte chlType; //channel type 
        public System.UInt64 srcID;  
        public System.String srcName; //src 
        public System.Int16 srcIcon; //src 
        public System.UInt64 dstID; //userid or groupid 
        public System.String dstName; //src 
        public System.Int16 dstIcon; //src 
        public System.String msg;  
        public System.UInt32 sendTime;  
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
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            mID = 0; 
                mID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            srcID = 0; 
                srcID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                srcName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            srcIcon = 0; 
                srcIcon = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            dstID = 0; 
                dstID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                dstName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            dstIcon = 0; 
                dstIcon = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
                msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            sendTime = 0; 
                sendTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class ChatInfoArray : System.Collections.Generic.List<ChatInfo>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            System.Int32 len = (System.Int32)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            System.Int32 len = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
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
 
    class ChatReq: Proto4z.IProtoObject //发送聊天请求 
    {     
        static public System.UInt16 getProtoID() { return 1104; } 
        static public string getProtoName() { return "ChatReq"; } 
        public System.Byte chlType; //channel type 
        public System.UInt64 dstID; //userID or groupID 
        public System.String msg; //msg 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dstID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(msg)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            dstID = 0; 
                dstID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class ChatAck: Proto4z.IProtoObject //发送聊天请求 
    {     
        static public System.UInt16 getProtoID() { return 1105; } 
        static public string getProtoName() { return "ChatAck"; } 
        public System.UInt16 retCode;  
        public System.Byte chlType; //channel type 
        public System.UInt64 dstID; //userID or groupID 
        public System.UInt64 msgID;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(chlType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dstID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(msgID)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            chlType = 0; 
                chlType = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            dstID = 0; 
                dstID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            msgID = 0; 
                msgID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class ChatNotice: Proto4z.IProtoObject //聊天通知 
    {     
        static public System.UInt16 getProtoID() { return 1106; } 
        static public string getProtoName() { return "ChatNotice"; } 
        public System.UInt16 retCode;  
        public ChatInfoArray msgs;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(msgs.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            msgs = new ChatInfoArray(); 
                msgs.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
