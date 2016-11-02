 
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
        public int iconID; //头像  
        public int modeID; //模型  
        public int level; //等级  
        public AvatarPreview()  
        { 
            avatarID = 0;  
            avatarName = "";  
            account = "";  
            iconID = 0;  
            modeID = 0;  
            level = 0;  
        } 
        public AvatarPreview(ulong avatarID, string avatarName, string account, int iconID, int modeID, int level) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.modeID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.level)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
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
        public int iconID; //头像  
        public int modeID; //模型  
        public int level; //等级  
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
            level = 0;  
            exp = 0.0;  
            gold = 0.0;  
            diamond = 0.0;  
            createTime = 0;  
        } 
        public AvatarBaseInfo(ulong avatarID, string avatarName, string account, int iconID, int modeID, int level, double exp, double gold, double diamond, ulong createTime) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.modeID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.level)); 
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
            this.iconID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
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
 
 
    public class AvatarPropMap : System.Collections.Generic.Dictionary<string, double>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(kv.Key)); 
                ret.AddRange(Proto4z.BaseProtoObject.encodeDouble(kv.Value)); 
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
                    var key = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                    var val = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictGlobal: Proto4z.IProtoObject //全局配置  
    {     
        //proto id   
        public const ushort protoID = 1005;  
        static public ushort getProtoID() { return 1005; } 
        static public string getProtoName() { return "DictGlobal"; } 
        //members   
        public ulong id;  
        public ulong val; //整数  
        public double valFloat; //浮点数  
        public string combo; //字符串  
        public string desc;  
        public DictGlobal()  
        { 
            id = 0;  
            val = 0;  
            valFloat = 0.0;  
            combo = "";  
            desc = "";  
        } 
        public DictGlobal(ulong id, ulong val, double valFloat, string combo, string desc) 
        { 
            this.id = id; 
            this.val = val; 
            this.valFloat = valFloat; 
            this.combo = combo; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.val)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.valFloat)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.combo)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.val = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.valFloat = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.combo = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictRaffleAward: Proto4z.IProtoObject //奖池中的奖品  
    {     
        //proto id   
        public const ushort protoID = 1006;  
        static public ushort getProtoID() { return 1006; } 
        static public string getProtoName() { return "DictRaffleAward"; } 
        //members   
        public ulong id; //奖品ID  
        public ulong weight; //本奖品在奖池中的权重, 总权重在[10000~30000]之间的随机效果最好  
        public double probability; //[0~1]独立随机的概率,0为永远无法随机到 1是100%随机到  
        public DictRaffleAward()  
        { 
            id = 0;  
            weight = 0;  
            probability = 0.0;  
        } 
        public DictRaffleAward(ulong id, ulong weight, double probability) 
        { 
            this.id = id; 
            this.weight = weight; 
            this.probability = probability; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.weight)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.probability)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.weight = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.probability = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictRaffleAwardArray : System.Collections.Generic.List<DictRaffleAward>, Proto4z.IProtoObject  
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
                    var data = new DictRaffleAward(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictRafflePool: Proto4z.IProtoObject //道具抽奖,道具掉落  
    {     
        //proto id   
        public const ushort protoID = 1007;  
        static public ushort getProtoID() { return 1007; } 
        static public string getProtoName() { return "DictRafflePool"; } 
        //members   
        public ulong id;  
        public int raffleCount; //批量抽取次数  
        public DictRaffleAwardArray pool; //奖池  
        public string poolString; //奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式  
        public DictRafflePool()  
        { 
            id = 0;  
            raffleCount = 0;  
            pool = new DictRaffleAwardArray();  
            poolString = "";  
        } 
        public DictRafflePool(ulong id, int raffleCount, DictRaffleAwardArray pool, string poolString) 
        { 
            this.id = id; 
            this.raffleCount = raffleCount; 
            this.pool = pool; 
            this.poolString = poolString; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.raffleCount)); 
            if (this.pool == null) this.pool = new DictRaffleAwardArray(); 
            data.AddRange(this.pool.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.poolString)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.raffleCount = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.pool = new DictRaffleAwardArray(); 
            this.pool.__decode(binData, ref pos); 
            this.poolString = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictBaseProps: Proto4z.IProtoObject //战斗属性效果,用于装备,属性类增减益buff  
    {     
        //proto id   
        public const ushort protoID = 1008;  
        static public ushort getProtoID() { return 1008; } 
        static public string getProtoName() { return "DictBaseProps"; } 
        //members   
        public ulong id;  
        public double hp; //血量值  
        public double hpRegen; //每秒血量值恢复  
        public double attack; //伤害  
        public double defense; //防御  
        public double crit; //暴击  
        public double toughness; //韧性  
        public double moveSpeed; //移动速度  
        public double attackSpeed; //攻击速度  
        public double vampirk; //吸血  
        public DictBaseProps()  
        { 
            id = 0;  
            hp = 0.0;  
            hpRegen = 0.0;  
            attack = 0.0;  
            defense = 0.0;  
            crit = 0.0;  
            toughness = 0.0;  
            moveSpeed = 0.0;  
            attackSpeed = 0.0;  
            vampirk = 0.0;  
        } 
        public DictBaseProps(ulong id, double hp, double hpRegen, double attack, double defense, double crit, double toughness, double moveSpeed, double attackSpeed, double vampirk) 
        { 
            this.id = id; 
            this.hp = hp; 
            this.hpRegen = hpRegen; 
            this.attack = attack; 
            this.defense = defense; 
            this.crit = crit; 
            this.toughness = toughness; 
            this.moveSpeed = moveSpeed; 
            this.attackSpeed = attackSpeed; 
            this.vampirk = vampirk; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hpRegen)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.attack)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.defense)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.crit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.toughness)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.moveSpeed)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.attackSpeed)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.vampirk)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.hp = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.hpRegen = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.attack = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.defense = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.crit = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.toughness = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.moveSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.attackSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.vampirk = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictItem: Proto4z.IProtoObject //道具字典  
    {     
        //proto id   
        public const ushort protoID = 1009;  
        static public ushort getProtoID() { return 1009; } 
        static public string getProtoName() { return "DictItem"; } 
        //members   
        public ulong id;  
        public ushort primitiveType; //主类型  
        public ushort subType; //子类型  
        public ushort visible; //是否可见  
        public ushort stacks; //可堆叠个数,0和1都是1次  
        public ulong fightEffectID; //战斗属性效果,装备后生效  
        public ushort autoUse; //0 不可使用, 1 可使用, 2 获得后自动使用  
        public ulong dropID; //DictRafflePool中的id, 使用后销毁本道具并根据配置进行道具抽取  
        public ushort vocationLimit; //限制职业类型, 装备类型  
        public int levelLimit; //限制职业最小等级, 装备类型  
        public string desc;  
        public DictItem()  
        { 
            id = 0;  
            primitiveType = 0;  
            subType = 0;  
            visible = 0;  
            stacks = 0;  
            fightEffectID = 0;  
            autoUse = 0;  
            dropID = 0;  
            vocationLimit = 0;  
            levelLimit = 0;  
            desc = "";  
        } 
        public DictItem(ulong id, ushort primitiveType, ushort subType, ushort visible, ushort stacks, ulong fightEffectID, ushort autoUse, ulong dropID, ushort vocationLimit, int levelLimit, string desc) 
        { 
            this.id = id; 
            this.primitiveType = primitiveType; 
            this.subType = subType; 
            this.visible = visible; 
            this.stacks = stacks; 
            this.fightEffectID = fightEffectID; 
            this.autoUse = autoUse; 
            this.dropID = dropID; 
            this.vocationLimit = vocationLimit; 
            this.levelLimit = levelLimit; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.primitiveType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.subType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.visible)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.stacks)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.fightEffectID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.autoUse)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dropID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.vocationLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.levelLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.primitiveType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.subType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.visible = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.stacks = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.fightEffectID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.autoUse = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.dropID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.vocationLimit = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.levelLimit = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ItemInfo: Proto4z.IProtoObject //道具字典  
    {     
        //proto id   
        public const ushort protoID = 1010;  
        static public ushort getProtoID() { return 1010; } 
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
        public const ushort protoID = 1011;  
        static public ushort getProtoID() { return 1011; } 
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
        public const ushort protoID = 1012;  
        static public ushort getProtoID() { return 1012; } 
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
        public const ushort protoID = 1013;  
        static public ushort getProtoID() { return 1013; } 
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
 
 
