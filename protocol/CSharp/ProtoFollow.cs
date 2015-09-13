 
namespace Proto4z  
{ 
    class STATIC_FOLLOW_INVALID  
    { 
        public static System.Byte value = 0;  
    } 
    class STATIC_FOLLOW_DELETED //路人  
    { 
        public static System.Byte value = 1;  
    } 
    class STATIC_FOLLOW_HATE //黑  
    { 
        public static System.Byte value = 2;  
    } 
    class STATIC_FOLLOW_FOLLOWING //粉  
    { 
        public static System.Byte value = 3;  
    } 
 
    class FollowingInfo: Proto4z.IProtoObject //关注  
    {     
        public System.UInt64 following;  
        public System.UInt64 follower;  
        public System.Byte status; //状态标志  
        public System.UInt32 makeTime; //建立时间  
        public System.UInt32 lastChanged; //最后更改时间  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(following)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(follower)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(makeTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(lastChanged)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            following = 0; 
                following = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            follower = 0; 
                follower = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            status = 0; 
                status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            makeTime = 0; 
                makeTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            lastChanged = 0; 
                lastChanged = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class FollowingInfoArray : System.Collections.Generic.List<FollowingInfo>, Proto4z.IProtoObject  
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
                    var data = new FollowingInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    class GetFollowerReq: Proto4z.IProtoObject //获取粉丝列表  
    {     
        static public System.UInt16 getProtoID() { return 1000; } 
        static public string getProtoName() { return "GetFollowerReq"; } 
        public System.UInt64 uID;  
        public System.Byte status; //所有/路人/黑/粉  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(status)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            status = 0; 
                status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class GetFollowerAck: Proto4z.IProtoObject //获取粉丝列表  
    {     
        static public System.UInt16 getProtoID() { return 1001; } 
        static public string getProtoName() { return "GetFollowerAck"; } 
        public System.Byte status; //所有/路人/黑/粉  
        public FollowingInfoArray follower;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(status)); 
            data.AddRange(follower.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            status = 0; 
                status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            follower = new FollowingInfoArray(); 
                follower.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class GetFollowingReq: Proto4z.IProtoObject //获取关注列表  
    {     
        static public System.UInt16 getProtoID() { return 1010; } 
        static public string getProtoName() { return "GetFollowingReq"; } 
        public System.UInt64 uID;  
        public System.Byte status; //所有/路人/黑/粉  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(status)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            status = 0; 
                status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class GetFollowingAck: Proto4z.IProtoObject //获取关注列表  
    {     
        static public System.UInt16 getProtoID() { return 1011; } 
        static public string getProtoName() { return "GetFollowingAck"; } 
        public System.Byte status; //所有/路人/黑/粉  
        public FollowingInfoArray following;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(status)); 
            data.AddRange(following.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            status = 0; 
                status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            following = new FollowingInfoArray(); 
                following.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class PokeReq: Proto4z.IProtoObject //操作  
    {     
        static public System.UInt16 getProtoID() { return 1008; } 
        static public string getProtoName() { return "PokeReq"; } 
        public System.Byte dstStatus; //路人/黑/粉  
        public System.UInt64 following; //关注目标ID  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(dstStatus)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(following)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            dstStatus = 0; 
                dstStatus = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            following = 0; 
                following = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class PokeAck: Proto4z.IProtoObject //操作  
    {     
        static public System.UInt16 getProtoID() { return 1009; } 
        static public string getProtoName() { return "PokeAck"; } 
        public FollowingInfo follow;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(follow.__encode()); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            follow = new FollowingInfo(); 
                follow.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
