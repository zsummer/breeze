 
namespace Proto4z  
{ 
 
    public class Route: Proto4z.IProtoObject //路由信息  
    {     
        //members   
        public ulong uID;  
        public string token;  
        public uint expire;  
        public Route()  
        { 
            uID = 0;  
            token = "";  
            expire = 0;  
        } 
        public Route(ulong uID, string token, uint expire) 
        { 
            this.uID = uID; 
            this.token = token; 
            this.expire = expire; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.expire)); 
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
 
    public enum  : ushort 
    { 
        ETRIGGER_USER_LOGIN = 0, //用户登录, 用户ID  
        ETRIGGER_USER_LOGOUT = 1, //用户登出, 用户ID  
    }; 
 
} 
 
 
