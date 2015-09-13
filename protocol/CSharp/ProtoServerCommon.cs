 
namespace Proto4z  
{ 
 
    class Route: Proto4z.IProtoObject //路由信息  
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
    class STATIC_ETRIGGER_USER_LOGIN //用户登录, 用户ID  
    { 
        public static System.UInt16 value = 0;  
    } 
    class STATIC_ETRIGGER_USER_LOGOUT //用户登出, 用户ID  
    { 
        public static System.UInt16 value = 1;  
    } 
 
} 
 
 
