 
namespace Proto4z  
{ 
 
    public enum FOLLOW_STATUS : byte 
    { 
        FOLLOW_INVALID = 0,  
        FOLLOW_DELETED = 1, //路人  
        FOLLOW_HATE = 2, //黑  
        FOLLOW_FOLLOWING = 3, //粉  
    }; 
 
    public class FollowingInfo: Proto4z.IProtoObject //关注  
    {     
        //members   
        public ulong following;  
        public ulong follower;  
        public byte status; //状态标志  
        public uint makeTime; //建立时间  
        public uint lastChanged; //最后更改时间  
        public FollowingInfo()  
        { 
            following = 0;  
            follower = 0;  
            status = 0;  
            makeTime = 0;  
            lastChanged = 0;  
        } 
        public FollowingInfo(ulong following, ulong follower, byte status, uint makeTime, uint lastChanged) 
        { 
            this.following = following; 
            this.follower = follower; 
            this.status = status; 
            this.makeTime = makeTime; 
            this.lastChanged = lastChanged; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.following)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.follower)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.makeTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.lastChanged)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.following = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.follower = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.makeTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.lastChanged = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class FollowingInfoArray : System.Collections.Generic.List<FollowingInfo>, Proto4z.IProtoObject  
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
                    var data = new FollowingInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class GetFollowerReq: Proto4z.IProtoObject //获取粉丝列表  
    {     
        //proto id   
        public const ushort protoID = 1000;  
        static public ushort getProtoID() { return 1000; } 
        static public string getProtoName() { return "GetFollowerReq"; } 
        //members   
        public ulong uID;  
        public byte status; //所有/路人/黑/粉  
        public GetFollowerReq()  
        { 
            uID = 0;  
            status = 0;  
        } 
        public GetFollowerReq(ulong uID, byte status) 
        { 
            this.uID = uID; 
            this.status = status; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.status)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class GetFollowerAck: Proto4z.IProtoObject //获取粉丝列表  
    {     
        //proto id   
        public const ushort protoID = 1001;  
        static public ushort getProtoID() { return 1001; } 
        static public string getProtoName() { return "GetFollowerAck"; } 
        //members   
        public byte status; //所有/路人/黑/粉  
        public FollowingInfoArray follower;  
        public GetFollowerAck()  
        { 
            status = 0;  
            follower = new FollowingInfoArray();  
        } 
        public GetFollowerAck(byte status, FollowingInfoArray follower) 
        { 
            this.status = status; 
            this.follower = follower; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.status)); 
            if (this.follower == null) this.follower = new FollowingInfoArray(); 
            data.AddRange(this.follower.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.follower = new FollowingInfoArray(); 
            this.follower.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class GetFollowingReq: Proto4z.IProtoObject //获取关注列表  
    {     
        //proto id   
        public const ushort protoID = 1002;  
        static public ushort getProtoID() { return 1002; } 
        static public string getProtoName() { return "GetFollowingReq"; } 
        //members   
        public ulong uID;  
        public byte status; //所有/路人/黑/粉  
        public GetFollowingReq()  
        { 
            uID = 0;  
            status = 0;  
        } 
        public GetFollowingReq(ulong uID, byte status) 
        { 
            this.uID = uID; 
            this.status = status; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.status)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class GetFollowingAck: Proto4z.IProtoObject //获取关注列表  
    {     
        //proto id   
        public const ushort protoID = 1003;  
        static public ushort getProtoID() { return 1003; } 
        static public string getProtoName() { return "GetFollowingAck"; } 
        //members   
        public byte status; //所有/路人/黑/粉  
        public FollowingInfoArray following;  
        public GetFollowingAck()  
        { 
            status = 0;  
            following = new FollowingInfoArray();  
        } 
        public GetFollowingAck(byte status, FollowingInfoArray following) 
        { 
            this.status = status; 
            this.following = following; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.status)); 
            if (this.following == null) this.following = new FollowingInfoArray(); 
            data.AddRange(this.following.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.status = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.following = new FollowingInfoArray(); 
            this.following.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PokeReq: Proto4z.IProtoObject //操作  
    {     
        //proto id   
        public const ushort protoID = 1004;  
        static public ushort getProtoID() { return 1004; } 
        static public string getProtoName() { return "PokeReq"; } 
        //members   
        public byte dstStatus; //路人/黑/粉  
        public ulong following; //关注目标ID  
        public PokeReq()  
        { 
            dstStatus = 0;  
            following = 0;  
        } 
        public PokeReq(byte dstStatus, ulong following) 
        { 
            this.dstStatus = dstStatus; 
            this.following = following; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.dstStatus)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.following)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.dstStatus = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            this.following = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PokeAck: Proto4z.IProtoObject //操作  
    {     
        //proto id   
        public const ushort protoID = 1005;  
        static public ushort getProtoID() { return 1005; } 
        static public string getProtoName() { return "PokeAck"; } 
        //members   
        public FollowingInfo follow;  
        public PokeAck()  
        { 
            follow = new FollowingInfo();  
        } 
        public PokeAck(FollowingInfo follow) 
        { 
            this.follow = follow; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.follow == null) this.follow = new FollowingInfo(); 
            data.AddRange(this.follow.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.follow = new FollowingInfo(); 
            this.follow.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
