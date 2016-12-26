 
namespace Proto4z  
{ 
 
    public enum ERROR_CODE : ushort 
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
        EC_AVATAR_NOT_FOUND = 50, //错误的用户信息  
        EC_AVATAR_COUNT_LIMITE = 51, //创建用户的数量超出限制  
        EC_AVATAR_FREQ_LIMITE = 52, //创建用户的频率超出限制  
        EC_AVATAR_NAME_CONFLICT = 53, //创建用户的昵称冲突  
        EC_FRIEND_DUPLICATE = 100, //请先删除与该好友建立的关系  
        EC_FRIEND_CEILING = 101, //达到好友上限  
        EC_FRIEND_REFUSE = 102, //不能添加对方为好友  
        EC_FRIEND_NOT_EXIST = 103, //好友不存在  
        EC_SERVICE_NOT_OPEN = 104, //服务未开放  
    }; 
 
    public class Routing: Proto4z.IProtoObject //docker to docker 路由信息  
    {     
        //proto id   
        public const ushort protoID = 1000;  
        static public ushort getProtoID() { return 1000; } 
        static public string getProtoName() { return "Routing"; } 
        //members   
        public ushort toServiceType; //目标service类型  
        public ulong toServiceID; //目标serviceID, 如果是单例 ID为InvalidServiceID.   
        public ushort fromServiceType; //来源  
        public ulong fromServiceID; //来源  
        public ulong traceID; //本地产生的回调ID  
        public ulong traceBackID; //远端产生的回调ID  
        public Routing()  
        { 
            toServiceType = 0;  
            toServiceID = 0;  
            fromServiceType = 0;  
            fromServiceID = 0;  
            traceID = 0;  
            traceBackID = 0;  
        } 
        public Routing(ushort toServiceType, ulong toServiceID, ushort fromServiceType, ulong fromServiceID, ulong traceID, ulong traceBackID) 
        { 
            this.toServiceType = toServiceType; 
            this.toServiceID = toServiceID; 
            this.fromServiceType = fromServiceType; 
            this.fromServiceID = fromServiceID; 
            this.traceID = traceID; 
            this.traceBackID = traceBackID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.toServiceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.toServiceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.fromServiceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.fromServiceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.traceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.traceBackID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.toServiceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.toServiceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fromServiceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.fromServiceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.traceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.traceBackID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class OutOfBand: Proto4z.IProtoObject //带外信息  
    {     
        //proto id   
        public const ushort protoID = 1001;  
        static public ushort getProtoID() { return 1001; } 
        static public string getProtoName() { return "OutOfBand"; } 
        //members   
        public ulong clientDockerID; //该数据由docker获得来自客户端的消息时自动填充.  
        public uint clientSessionID; //该数据由docker获得来自客户端的消息时自动填充.  
        public ulong clientAvatarID; //该数据由docker获得来自客户端的消息时自动填充.  
        public OutOfBand()  
        { 
            clientDockerID = 0;  
            clientSessionID = 0;  
            clientAvatarID = 0;  
        } 
        public OutOfBand(ulong clientDockerID, uint clientSessionID, ulong clientAvatarID) 
        { 
            this.clientDockerID = clientDockerID; 
            this.clientSessionID = clientSessionID; 
            this.clientAvatarID = clientAvatarID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.clientDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.clientAvatarID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientAvatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class Tracing: Proto4z.IProtoObject //docker间追踪数据  
    {     
        //proto id   
        public const ushort protoID = 1002;  
        static public ushort getProtoID() { return 1002; } 
        static public string getProtoName() { return "Tracing"; } 
        //members   
        public Routing routing; //路由信息  
        public OutOfBand oob; //来自客户端的带外信息  
        public Tracing()  
        { 
            routing = new Routing();  
            oob = new OutOfBand();  
        } 
        public Tracing(Routing routing, OutOfBand oob) 
        { 
            this.routing = routing; 
            this.oob = oob; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.routing == null) this.routing = new Routing(); 
            data.AddRange(this.routing.__encode()); 
            if (this.oob == null) this.oob = new OutOfBand(); 
            data.AddRange(this.oob.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.routing = new Routing(); 
            this.routing.__decode(binData, ref pos); 
            this.oob = new OutOfBand(); 
            this.oob.__decode(binData, ref pos); 
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
 
 
    public class ServiceIDMap : System.Collections.Generic.Dictionary<ulong, ulong>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Key)); 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Value)); 
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
                    var key = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                    var val = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class AvatarPreview: Proto4z.IProtoObject //用户预览信息  
    {     
        //proto id   
        public const ushort protoID = 1003;  
        static public ushort getProtoID() { return 1003; } 
        static public string getProtoName() { return "AvatarPreview"; } 
        //members   
        public ulong avatarID; //用户唯一ID, 对应AvatarService的ServiceID  
        public string avatarName; //用户唯一昵称, 对应AvatarService的ServiceName  
        public string account; //帐号  
        public ulong iconID; //头像  
        public ulong modeID; //模型  
        public double level; //等级  
        public AvatarPreview()  
        { 
            avatarID = 0;  
            avatarName = "";  
            account = "";  
            iconID = 0;  
            modeID = 0;  
            level = 0.0;  
        } 
        public AvatarPreview(ulong avatarID, string avatarName, string account, ulong iconID, ulong modeID, double level) 
        { 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.account = account; 
            this.iconID = iconID; 
            this.modeID = modeID; 
            this.level = level; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modeID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.level)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class AvatarPreviewArray : System.Collections.Generic.List<AvatarPreview>, Proto4z.IProtoObject  
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
                    var data = new AvatarPreview(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class AvatarBaseInfo: Proto4z.IProtoObject //用户基础数据  
    {     
        //proto id   
        public const ushort protoID = 1004;  
        static public ushort getProtoID() { return 1004; } 
        static public string getProtoName() { return "AvatarBaseInfo"; } 
        //members   
        public ulong avatarID; //用户唯一ID, 对应AvatarService的ServiceID  
        public string avatarName; //用户唯一昵称, 对应AvatarService的ServiceName  
        public string account; //帐号  
        public ulong iconID; //头像  
        public ulong modeID; //模型  
        public double level; //等级  
        public double exp; //经验  
        public double gold; //金币  
        public double diamond; //钻石  
        public ulong createTime; //角色创建时间  
        public AvatarBaseInfo()  
        { 
            avatarID = 0;  
            avatarName = "";  
            account = "";  
            iconID = 0;  
            modeID = 0;  
            level = 0.0;  
            exp = 0.0;  
            gold = 0.0;  
            diamond = 0.0;  
            createTime = 0;  
        } 
        public AvatarBaseInfo(ulong avatarID, string avatarName, string account, ulong iconID, ulong modeID, double level, double exp, double gold, double diamond, ulong createTime) 
        { 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.account = account; 
            this.iconID = iconID; 
            this.modeID = modeID; 
            this.level = level; 
            this.exp = exp; 
            this.gold = gold; 
            this.diamond = diamond; 
            this.createTime = createTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modeID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.level)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.exp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.gold)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.diamond)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.createTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.exp = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.gold = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.diamond = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.createTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class AvatarBaseInfoArray : System.Collections.Generic.List<AvatarBaseInfo>, Proto4z.IProtoObject  
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
                    var data = new AvatarBaseInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class ItemInfo: Proto4z.IProtoObject //道具字典  
    {     
        //proto id   
        public const ushort protoID = 1005;  
        static public ushort getProtoID() { return 1005; } 
        static public string getProtoName() { return "ItemInfo"; } 
        //members   
        public ushort stacks; //可堆叠个数,0和1都是1次  
        public ItemInfo()  
        { 
            stacks = 0;  
        } 
        public ItemInfo(ushort stacks) 
        { 
            this.stacks = stacks; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.stacks)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.stacks = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum ChatChannelEnum : ushort 
    { 
        CC_WORLD = 0, //世界频道  
        CC_PRIVATE = 1, //私人频道  
        CC_SYSTEM = 2, //系统频道  
        CC_GROUP = 3, //同编队频道  
        CC_CAMP = 4, //同阵营频道  
        CC_SCENE = 5, //同场景频道  
    }; 
 
    public class LogChat: Proto4z.IProtoObject //聊天日志  
    {     
        //proto id   
        public const ushort protoID = 1006;  
        static public ushort getProtoID() { return 1006; } 
        static public string getProtoName() { return "LogChat"; } 
        //members   
        public ulong id;  
        public ushort channelID;  
        public ulong sourceID;  
        public string sourceName;  
        public ulong targetID;  
        public string targetName;  
        public string msg;  
        public ulong chatTime;  
        public LogChat()  
        { 
            id = 0;  
            channelID = 0;  
            sourceID = 0;  
            sourceName = "";  
            targetID = 0;  
            targetName = "";  
            msg = "";  
            chatTime = 0;  
        } 
        public LogChat(ulong id, ushort channelID, ulong sourceID, string sourceName, ulong targetID, string targetName, string msg, ulong chatTime) 
        { 
            this.id = id; 
            this.channelID = channelID; 
            this.sourceID = sourceID; 
            this.sourceName = sourceName; 
            this.targetID = targetID; 
            this.targetName = targetName; 
            this.msg = msg; 
            this.chatTime = chatTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.channelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sourceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sourceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.targetID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.targetName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.chatTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.channelID = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.sourceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sourceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.targetID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.targetName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.chatTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoneyTree: Proto4z.IProtoObject //摇钱树功能模块  
    {     
        //proto id   
        public const ushort protoID = 1007;  
        static public ushort getProtoID() { return 1007; } 
        static public string getProtoName() { return "MoneyTree"; } 
        //members   
        public ulong lastTime; //最后一次执行时间  
        public ulong freeCount; //今日剩余免费次数  
        public ulong payCount; //今日已购买次数  
        public ulong statSum; //历史总和  
        public ulong statCount; //历史总次数  
        public MoneyTree()  
        { 
            lastTime = 0;  
            freeCount = 0;  
            payCount = 0;  
            statSum = 0;  
            statCount = 0;  
        } 
        public MoneyTree(ulong lastTime, ulong freeCount, ulong payCount, ulong statSum, ulong statCount) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.lastTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.freeCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.payCount)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.statSum)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.statCount)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.lastTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.freeCount = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.payCount = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.statSum = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.statCount = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SimplePack: Proto4z.IProtoObject //简单示例  
    {     
        //proto id   
        public const ushort protoID = 1008;  
        static public ushort getProtoID() { return 1008; } 
        static public string getProtoName() { return "SimplePack"; } 
        //members   
        public ulong id; //id, 对应数据库的结构为自增ID,key  
        public string name; //昵称, 唯一索引  
        public ulong createTime; //创建时间, 普通索引  
        public MoneyTree moneyTree;  
        public SimplePack()  
        { 
            id = 0;  
            name = "";  
            createTime = 0;  
            moneyTree = new MoneyTree();  
        } 
        public SimplePack(ulong id, string name, ulong createTime, MoneyTree moneyTree) 
        { 
            this.id = id; 
            this.name = name; 
            this.createTime = createTime; 
            this.moneyTree = moneyTree; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.name)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.createTime)); 
            if (this.moneyTree == null) this.moneyTree = new MoneyTree(); 
            data.AddRange(this.moneyTree.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.name = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.createTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.moneyTree = new MoneyTree(); 
            this.moneyTree.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
