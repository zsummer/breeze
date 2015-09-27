 
namespace Proto4z  
{ 
 
    public enum  : ushort 
    { 
        EC_SUCCESS = 0, //成功  
        EC_ERROR = 1, //错误  
        EC_INNER_ERROR = 2, //内部错误  
        EC_DB_ERROR = 3, //数据库错误  
        EC_PARAM_DENIED = 4, //非法参数  
        EC_PERMISSION_DENIED = 5, //权限错误  
        EC_REQUEST_EXPIRE = 6, //请求操作已过期  
        EC_TARGET_NOT_EXIST = 7, //操作目标不存在  
        EC_TOKEN_EXPIRE = 8, //令牌过期  
        EC_USER_NOT_FOUND = 50, //错误的用户信息  
        EC_USER_OFFLINE = 51, //错误的用户信息  
        EC_FRIEND_DUPLICATE = 100, //请先删除与该好友建立的关系  
        EC_FRIEND_CEILING = 101, //达到好友上限  
        EC_FRIEND_REFUSE = 102, //不能添加对方为好友  
        EC_FRIEND_NOT_EXIST = 103, //好友不存在  
    }; 
 
    public class SessionToken: Proto4z.IProtoObject //认证令牌  
    {     
        //members   
        public ulong uID;  
        public string token;  
        public uint expire;  
        public SessionToken()  
        { 
            uID = 0;  
            token = "";  
            expire = 0;  
        } 
        public SessionToken(ulong uID, string token, uint expire) 
        { 
            this.uID = uID; 
            this.token = token; 
            this.expire = expire; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(expire)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.expire = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class BaseInfo: Proto4z.IProtoObject //用户基础信息  
    {     
        //members   
        public ulong uID; //用户唯一ID  
        public string account; //帐号  
        public string nickName; //昵称  
        public short iconID; //头像  
        public int diamond; //当前剩余的充值钻石  
        public int hisotryDiamond; //历史充值钻石总额  
        public int giftDiamond; //当前剩余的赠送钻石  
        public uint joinTime; //加入时间  
        public BaseInfo()  
        { 
            uID = 0;  
            account = "";  
            nickName = "";  
            iconID = 0;  
            diamond = 0;  
            hisotryDiamond = 0;  
            giftDiamond = 0;  
            joinTime = 0;  
        } 
        public BaseInfo(ulong uID, string account, string nickName, short iconID, int diamond, int hisotryDiamond, int giftDiamond, uint joinTime) 
        { 
            this.uID = uID; 
            this.account = account; 
            this.nickName = nickName; 
            this.iconID = iconID; 
            this.diamond = diamond; 
            this.hisotryDiamond = hisotryDiamond; 
            this.giftDiamond = giftDiamond; 
            this.joinTime = joinTime; 
        } 
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
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.uID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.nickName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            this.diamond = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.hisotryDiamond = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.giftDiamond = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.joinTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class BaseInfoArray : System.Collections.Generic.List<BaseInfo>, Proto4z.IProtoObject  
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
                    var data = new BaseInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class UIDS : System.Collections.Generic.List<ulong>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI64(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public enum  : ushort 
    { 
        ETRIGGER_USER_LOGIN = 0, //用户登录, 用户ID  
        ETRIGGER_USER_LOGOUT = 1, //用户登出, 用户ID  
    }; 
 
} 
 
 
