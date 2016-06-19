 
namespace Proto4z  
{ 
 
    public class DictGlobal: Proto4z.IProtoObject //全局配置  
    {     
        //proto id   
        public const ushort protoID = 10000;  
        static public ushort getProtoID() { return 10000; } 
        static public string getProtoName() { return "DictGlobal"; } 
        //members   
        public uint id;  
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
        public DictGlobal(uint id, ulong val, double valFloat, string combo, string desc) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.val)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.valFloat)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.combo)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.val = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.valFloat = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.combo = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RaffleAward: Proto4z.IProtoObject //奖池中的奖品  
    {     
        //proto id   
        public const ushort protoID = 10004;  
        static public ushort getProtoID() { return 10004; } 
        static public string getProtoName() { return "RaffleAward"; } 
        //members   
        public uint id; //奖品ID  
        public uint weight; //本奖品在奖池中的权重, 总权重在[10000~30000]之间的随机效果最好  
        public double probability; //[0~1]独立随机的概率,0为永远无法随机到 1是100%随机到  
        public RaffleAward()  
        { 
            id = 0;  
            weight = 0;  
            probability = 0.0;  
        } 
        public RaffleAward(uint id, uint weight, double probability) 
        { 
            this.id = id; 
            this.weight = weight; 
            this.probability = probability; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.weight)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.probability)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.weight = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.probability = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class RaffleAwardArray : System.Collections.Generic.List<RaffleAward>, Proto4z.IProtoObject  
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
                    var data = new RaffleAward(); 
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
        public const ushort protoID = 10001;  
        static public ushort getProtoID() { return 10001; } 
        static public string getProtoName() { return "DictRafflePool"; } 
        //members   
        public uint id;  
        public int raffleCount; //批量抽取次数  
        public RaffleAwardArray pool; //奖池  
        public string poolString; //奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式  
        public DictRafflePool()  
        { 
            id = 0;  
            raffleCount = 0;  
            pool = new RaffleAwardArray();  
            poolString = "";  
        } 
        public DictRafflePool(uint id, int raffleCount, RaffleAwardArray pool, string poolString) 
        { 
            this.id = id; 
            this.raffleCount = raffleCount; 
            this.pool = pool; 
            this.poolString = poolString; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.raffleCount)); 
            if (this.pool == null) this.pool = new RaffleAwardArray(); 
            data.AddRange(this.pool.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.poolString)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.raffleCount = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.pool = new RaffleAwardArray(); 
            this.pool.__decode(binData, ref pos); 
            this.poolString = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictFightEffect: Proto4z.IProtoObject //战斗属性效果,用于装备,属性类增减益buff  
    {     
        //proto id   
        public const ushort protoID = 10002;  
        static public ushort getProtoID() { return 10002; } 
        static public string getProtoName() { return "DictFightEffect"; } 
        //members   
        public uint id;  
        public double hp; //血量值  
        public double hpRegen; //每秒血量值恢复  
        public double attack; //伤害  
        public double defense; //防御  
        public double crit; //暴击  
        public double toughness; //韧性  
        public double moveSpeed; //移动速度  
        public double attackSpeed; //攻击速度  
        public double vampirk; //吸血  
        public DictFightEffect()  
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
        public DictFightEffect(uint id, double hp, double hpRegen, double attack, double defense, double crit, double toughness, double moveSpeed, double attackSpeed, double vampirk) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.id)); 
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
            this.id = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
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
        public const ushort protoID = 10003;  
        static public ushort getProtoID() { return 10003; } 
        static public string getProtoName() { return "DictItem"; } 
        //members   
        public uint id;  
        public ushort primitiveType; //主类型  
        public ushort subType; //子类型  
        public ushort visible; //是否可见  
        public ushort stacks; //可堆叠个数,0和1都是1次  
        public uint fightEffectID; //战斗属性效果,装备后生效  
        public ushort autoUse; //0 不可使用, 1 可使用, 2 获得后自动使用  
        public uint dropID; //DictRafflePool中的id, 使用后销毁本道具并根据配置进行道具抽取  
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
        public DictItem(uint id, ushort primitiveType, ushort subType, ushort visible, ushort stacks, uint fightEffectID, ushort autoUse, uint dropID, ushort vocationLimit, int levelLimit, string desc) 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.primitiveType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.subType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.visible)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.stacks)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.fightEffectID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.autoUse)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.dropID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.vocationLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.levelLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.primitiveType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.subType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.visible = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.stacks = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.fightEffectID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.autoUse = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.dropID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.vocationLimit = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.levelLimit = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
