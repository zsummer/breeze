 
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
 
    public class Tracing: Proto4z.IProtoObject //docker间追踪数据  
    {     
        //proto id   
        public const ushort protoID = 1000;  
        static public ushort getProtoID() { return 1000; } 
        static public string getProtoName() { return "Tracing"; } 
        //members   
        public uint toDockerID; //forward转发时候先尝试通过DockerID进行转发 然后再尝试ServiceID   
        public ushort toServiceType; //目标service类型  
        public ulong toServiceID; //目标serviceID, 如果是单例 ID为InvalidServiceID.   
        public uint fromDockerID; //来源DockerID  
        public ushort fromServiceType; //来源  
        public ulong fromServiceID; //来源  
        public uint traceID; //本地cbID    
        public uint traceBackID; //把远程cbID透传回去   
        public uint orgDockerID; //org DockerID  
        public ushort orgServiceType; //org 来源  
        public ulong orgServiceID; //org 来源  
        public Tracing()  
        { 
            toDockerID = 0;  
            toServiceType = 0;  
            toServiceID = 0;  
            fromDockerID = 0;  
            fromServiceType = 0;  
            fromServiceID = 0;  
            traceID = 0;  
            traceBackID = 0;  
            orgDockerID = 0;  
            orgServiceType = 0;  
            orgServiceID = 0;  
        } 
        public Tracing(uint toDockerID, ushort toServiceType, ulong toServiceID, uint fromDockerID, ushort fromServiceType, ulong fromServiceID, uint traceID, uint traceBackID, uint orgDockerID, ushort orgServiceType, ulong orgServiceID) 
        { 
            this.toDockerID = toDockerID; 
            this.toServiceType = toServiceType; 
            this.toServiceID = toServiceID; 
            this.fromDockerID = fromDockerID; 
            this.fromServiceType = fromServiceType; 
            this.fromServiceID = fromServiceID; 
            this.traceID = traceID; 
            this.traceBackID = traceBackID; 
            this.orgDockerID = orgDockerID; 
            this.orgServiceType = orgServiceType; 
            this.orgServiceID = orgServiceID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.toDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.toServiceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.toServiceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.fromDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.fromServiceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.fromServiceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.traceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.traceBackID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.orgDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.orgServiceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.orgServiceID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.toDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.toServiceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.toServiceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fromDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.fromServiceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.fromServiceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.traceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.traceBackID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.orgDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.orgServiceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.orgServiceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UserPreview: Proto4z.IProtoObject //用户预览信息  
    {     
        //proto id   
        public const ushort protoID = 1001;  
        static public ushort getProtoID() { return 1001; } 
        static public string getProtoName() { return "UserPreview"; } 
        //members   
        public ulong serviceID; //用户唯一ID  
        public string serviceName; //昵称  
        public string account; //帐号  
        public short iconID; //头像  
        public int level; //等级  
        public UserPreview()  
        { 
            serviceID = 0;  
            serviceName = "";  
            account = "";  
            iconID = 0;  
            level = 0;  
        } 
        public UserPreview(ulong serviceID, string serviceName, string account, short iconID, int level) 
        { 
            this.serviceID = serviceID; 
            this.serviceName = serviceName; 
            this.account = account; 
            this.iconID = iconID; 
            this.level = level; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.serviceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.level)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serviceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class UserPreviewArray : System.Collections.Generic.List<UserPreview>, Proto4z.IProtoObject  
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
                    var data = new UserPreview(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class ServiceIDArray : System.Collections.Generic.List<ulong>, Proto4z.IProtoObject  
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
 
    public class UserBaseInfo: Proto4z.IProtoObject //用户基础数据  
    {     
        //proto id   
        public const ushort protoID = 1002;  
        static public ushort getProtoID() { return 1002; } 
        static public string getProtoName() { return "UserBaseInfo"; } 
        //members   
        public ulong serviceID; //用户唯一ID  
        public string serviceName; //昵称  
        public string account; //帐号  
        public short iconID; //头像  
        public int level; //等级  
        public UserBaseInfo()  
        { 
            serviceID = 0;  
            serviceName = "";  
            account = "";  
            iconID = 0;  
            level = 0;  
        } 
        public UserBaseInfo(ulong serviceID, string serviceName, string account, short iconID, int level) 
        { 
            this.serviceID = serviceID; 
            this.serviceName = serviceName; 
            this.account = account; 
            this.iconID = iconID; 
            this.level = level; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.serviceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI16(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.level)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serviceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI16(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class UserBaseInfoArray : System.Collections.Generic.List<UserBaseInfo>, Proto4z.IProtoObject  
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
                    var data = new UserBaseInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class MoneyTree: Proto4z.IProtoObject //摇钱树功能模块  
    {     
        //proto id   
        public const ushort protoID = 1003;  
        static public ushort getProtoID() { return 1003; } 
        static public string getProtoName() { return "MoneyTree"; } 
        //members   
        public uint lastTime; //最后一次执行时间  
        public uint freeCount; //今日剩余免费次数  
        public uint payCount; //今日已购买次数  
        public uint statSum; //历史总和  
        public uint statCount; //历史总次数  
        public MoneyTree()  
        { 
            lastTime = 0;  
            freeCount = 0;  
            payCount = 0;  
            statSum = 0;  
            statCount = 0;  
        } 
        public MoneyTree(uint lastTime, uint freeCount, uint payCount, uint statSum, uint statCount) 
        { 
            this.lastTime = lastTime; 
            this.freeCount = freeCount; 
            this.payCount = payCount; 
            this.statSum = statSum; 
            this.statCount = statCount; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.lastTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.freeCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.payCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.statSum)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.statCount)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.lastTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.freeCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.payCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.statSum = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.statCount = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SimplePack: Proto4z.IProtoObject //简单示例  
    {     
        //proto id   
        public const ushort protoID = 1004;  
        static public ushort getProtoID() { return 1004; } 
        static public string getProtoName() { return "SimplePack"; } 
        //members   
        public uint id; //id, 对应数据库的结构为自增ID,key  
        public string name; //昵称, 唯一索引  
        public uint createTime; //创建时间, 普通索引  
        public MoneyTree moneyTree;  
        public SimplePack()  
        { 
            id = 0;  
            name = "";  
            createTime = 0;  
            moneyTree = new MoneyTree();  
        } 
        public SimplePack(uint id, string name, uint createTime, MoneyTree moneyTree) 
        { 
            this.id = id; 
            this.name = name; 
            this.createTime = createTime; 
            this.moneyTree = moneyTree; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.name)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.createTime)); 
            if (this.moneyTree == null) this.moneyTree = new MoneyTree(); 
            data.AddRange(this.moneyTree.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.name = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.createTime = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.moneyTree = new MoneyTree(); 
            this.moneyTree.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
