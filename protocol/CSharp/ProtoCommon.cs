 
namespace Proto4z  
{ 
    class STATIC_EC_SUCCESS //成功 
    { 
        public static System.UInt16 value = 0;  
    } 
    class STATIC_EC_ERROR //错误 
    { 
        public static System.UInt16 value = 1;  
    } 
    class STATIC_EC_INNER_ERROR //内部错误 
    { 
        public static System.UInt16 value = 2;  
    } 
    class STATIC_EC_DB_ERROR //数据库错误 
    { 
        public static System.UInt16 value = 3;  
    } 
    class STATIC_EC_PARAM_DENIED //非法参数 
    { 
        public static System.UInt16 value = 4;  
    } 
    class STATIC_EC_PERMISSION_DENIED //权限错误 
    { 
        public static System.UInt16 value = 5;  
    } 
    class STATIC_EC_REQUEST_EXPIRE //请求操作已过期 
    { 
        public static System.UInt16 value = 6;  
    } 
    class STATIC_EC_TARGET_NOT_EXIST //操作目标不存在 
    { 
        public static System.UInt16 value = 7;  
    } 
    class STATIC_EC_TOKEN_EXPIRE //令牌过期 
    { 
        public static System.UInt16 value = 8;  
    } 
    class STATIC_EC_USER_NOT_FOUND //错误的用户信息 
    { 
        public static System.UInt16 value = 50;  
    } 
    class STATIC_EC_USER_OFFLINE //错误的用户信息 
    { 
        public static System.UInt16 value = 51;  
    } 
    class STATIC_EC_FRIEND_DUPLICATE //请先删除与该好友建立的关系 
    { 
        public static System.UInt16 value = 100;  
    } 
    class STATIC_EC_FRIEND_CEILING //达到好友上限 
    { 
        public static System.UInt16 value = 101;  
    } 
    class STATIC_EC_FRIEND_REFUSE //不能添加对方为好友 
    { 
        public static System.UInt16 value = 102;  
    } 
    class STATIC_EC_FRIEND_NOT_EXIST //好友不存在 
    { 
        public static System.UInt16 value = 103;  
    } 
 
    class SessionToken: Proto4z.IProtoObject //认证令牌 
    {     
        public System.UInt64 uID;  
        public System.String token;  
        public System.UInt32 expire;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(expire)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            expire = 0; 
                expire = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class BaseInfo: Proto4z.IProtoObject //用户基础信息 
    {     
        public System.UInt64 uID; //用户唯一ID 
        public System.String account; //帐号 
        public System.String nickName; //昵称 
        public System.Int16 iconID; //头像 
        public System.Int32 diamond; //当前剩余的充值钻石 
        public System.Int32 hisotryDiamond; //历史充值钻石总额 
        public System.Int32 giftDiamond; //当前剩余的赠送钻石 
        public System.UInt32 joinTime; //加入时间 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(nickName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(diamond)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(hisotryDiamond)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(giftDiamond)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(joinTime)); 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            uID = 0; 
                uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                nickName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            iconID = 0; 
                iconID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            diamond = 0; 
                diamond = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            hisotryDiamond = 0; 
                hisotryDiamond = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            giftDiamond = 0; 
                giftDiamond = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            joinTime = 0; 
                joinTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    class BaseInfoArray : System.Collections.Generic.List<BaseInfo>, Proto4z.IProtoObject  
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
                    var data = new BaseInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    class UIDS : System.Collections.Generic.List<System.UInt64>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            System.Int32 len = (System.Int32)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI64(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
    class STATIC_ETRIGGER_USER_LOGIN //用户登录, 用户ID 
    { 
        public static System.UInt16 value = 0;  
    } 
    class STATIC_ETRIGGER_USER_LOGOUT //用户登出, 用户ID 
    { 
        public static System.UInt16 value = 1;  
    } 
 
    class Heartbeat: Proto4z.IProtoObject //心跳包 
    {     
        static public System.UInt16 getProtoID() { return 200; } 
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
        static public System.UInt16 getProtoID() { return 201; } 
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
 
} 
 
 
