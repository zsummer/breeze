 
namespace Proto4z  
{ 
    class STATIC_FRIEND_DELETED //已删除好友关系 
    { 
        public static System.Byte value = 0;  
    } 
    class STATIC_FRIEND_WAITING //等待好友确认 
    { 
        public static System.Byte value = 1;  
    } 
    class STATIC_FRIEND_REQUESTING //需要确认 
    { 
        public static System.Byte value = 2;  
    } 
    class STATIC_FRIEND_BLACKLIST //黑名单 
    { 
        public static System.Byte value = 3;  
    } 
    class STATIC_FRIEND_ESTABLISHED //好友 
    { 
        public static System.Byte value = 4;  
    } 
    class STATIC_FRIEND_ALLOW //同意 
    { 
        public static System.Byte value = 0;  
    } 
    class STATIC_FRIEND_REJECT //拒绝 
    { 
        public static System.Byte value = 1;  
    } 
    class STATIC_FRIEND_IGNORE //忽略 
    { 
        public static System.Byte value = 2;  
    } 
 
    class FriendInfo: Proto4z.IProtoObject //好友信息 
    {     
        public System.UInt64 ownID;  
        public System.UInt64 fID;  
        public System.Byte flag; //状态标志 
        public System.Byte online; //好友是否在线,不需要存数据库 
        public System.UInt32 makeTime; //建立时间 
        public System.UInt32 lastChanged; //最后更改时间 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(ownID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(fID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(flag)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(online)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(makeTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(lastChanged)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            ownID = 0; 
                ownID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            fID = 0; 
                fID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            flag = 0; 
                flag = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            online = 0; 
                online = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            makeTime = 0; 
                makeTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            lastChanged = 0; 
                lastChanged = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class FriendInfoArray : System.Collections.Generic.List<FriendInfo>, Proto4z.IProtoObject  
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
                    var data = new FriendInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    class GetFriendsReq: Proto4z.IProtoObject //获取好友列表 
    {     
        static public System.UInt16 getProtoID() { return 1000; } 
        static public string getProtoName() { return "GetFriendsReq"; } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            return pos; 
        } 
    } 
 
    class UpdateFriendsNotice: Proto4z.IProtoObject //好友列表推送通知 
    {     
        static public System.UInt16 getProtoID() { return 1001; } 
        static public string getProtoName() { return "UpdateFriendsNotice"; } 
        public FriendInfoArray friends;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(friends.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            friends = new FriendInfoArray(); 
                friends.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class AddFriendReq: Proto4z.IProtoObject //添加好友请求 
    {     
        static public System.UInt16 getProtoID() { return 1002; } 
        static public string getProtoName() { return "AddFriendReq"; } 
        public System.UInt64 dst; //目标ID 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dst)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            dst = 0; 
                dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class AddFriendReply: Proto4z.IProtoObject //答复好友请求 
    {     
        static public System.UInt16 getProtoID() { return 1003; } 
        static public string getProtoName() { return "AddFriendReply"; } 
        public System.UInt64 dst; //目标ID 
        public System.Byte flag; //状态标志 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dst)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(flag)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            dst = 0; 
                dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            flag = 0; 
                flag = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class AddFriendAck: Proto4z.IProtoObject //添加好友请求结果 
    {     
        static public System.UInt16 getProtoID() { return 1004; } 
        static public string getProtoName() { return "AddFriendAck"; } 
        public System.UInt16 retCode;  
        public System.UInt64 dst; //目标ID 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dst)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            dst = 0; 
                dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class DelFriendReq: Proto4z.IProtoObject //删除好友请求 
    {     
        static public System.UInt16 getProtoID() { return 1005; } 
        static public string getProtoName() { return "DelFriendReq"; } 
        public System.UInt64 dst; //目标ID 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dst)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            dst = 0; 
                dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class DelFriendAck: Proto4z.IProtoObject //删除好友请求结果 
    {     
        static public System.UInt16 getProtoID() { return 1006; } 
        static public string getProtoName() { return "DelFriendAck"; } 
        public System.UInt16 retCode;  
        public System.UInt64 dst; //目标ID 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(dst)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            retCode = 0; 
                retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            dst = 0; 
                dst = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
