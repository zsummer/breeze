 
namespace Proto4z  
{ 
 
    public class DictGlobal: Proto4z.IProtoObject //全局配置  
    {     
        //proto id   
        public const ushort protoID = 10000;  
        static public ushort getProtoID() { return 10000; } 
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
 
    public class DictReward: Proto4z.IProtoObject //奖品  
    {     
        //proto id   
        public const ushort protoID = 10007;  
        static public ushort getProtoID() { return 10007; } 
        static public string getProtoName() { return "DictReward"; } 
        //members   
        public ulong id; //奖品ID  
        public ulong count; //数量  
        public double probability; //概率[0~1], 0为永远无法随机到 1是100%随机到  
        public DictReward()  
        { 
            id = 0;  
            count = 0;  
            probability = 0.0;  
        } 
        public DictReward(ulong id, ulong count, double probability) 
        { 
            this.id = id; 
            this.count = count; 
            this.probability = probability; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.count)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.probability)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.count = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.probability = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictRewardArray : System.Collections.Generic.List<DictReward>, Proto4z.IProtoObject  
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
                    var data = new DictReward(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictDrop: Proto4z.IProtoObject //道具抽奖,道具掉落  
    {     
        //proto id   
        public const ushort protoID = 10008;  
        static public ushort getProtoID() { return 10008; } 
        static public string getProtoName() { return "DictDrop"; } 
        //members   
        public ulong id;  
        public ulong dropType; //0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到  
        public DictRewardArray rewards; //奖池  
        public string rewardsString; //奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式  
        public DictDrop()  
        { 
            id = 0;  
            dropType = 0;  
            rewards = new DictRewardArray();  
            rewardsString = "";  
        } 
        public DictDrop(ulong id, ulong dropType, DictRewardArray rewards, string rewardsString) 
        { 
            this.id = id; 
            this.dropType = dropType; 
            this.rewards = rewards; 
            this.rewardsString = rewardsString; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dropType)); 
            if (this.rewards == null) this.rewards = new DictRewardArray(); 
            data.AddRange(this.rewards.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.rewardsString)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dropType = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.rewards = new DictRewardArray(); 
            this.rewards.__decode(binData, ref pos); 
            this.rewardsString = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
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
        public ulong id;  
        public ushort visible; //是否可见  
        public ushort icon;  
        public ushort stacks; //可堆叠个数,0和1都是1次  
        public ushort autoUse; //0 不可使用, 1 可使用, 2 获得后自动使用  
        public ulong dropID;  
        public ulong propID;  
        public ushort vocationLimit; //限制职业类型, 装备类型  
        public double levelLimit; //限制职业最小等级, 装备类型  
        public string desc;  
        public DictItem()  
        { 
            id = 0;  
            visible = 0;  
            icon = 0;  
            stacks = 0;  
            autoUse = 0;  
            dropID = 0;  
            propID = 0;  
            vocationLimit = 0;  
            levelLimit = 0.0;  
            desc = "";  
        } 
        public DictItem(ulong id, ushort visible, ushort icon, ushort stacks, ushort autoUse, ulong dropID, ulong propID, ushort vocationLimit, double levelLimit, string desc) 
        { 
            this.id = id; 
            this.visible = visible; 
            this.icon = icon; 
            this.stacks = stacks; 
            this.autoUse = autoUse; 
            this.dropID = dropID; 
            this.propID = propID; 
            this.vocationLimit = vocationLimit; 
            this.levelLimit = levelLimit; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.visible)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.icon)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.stacks)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.autoUse)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dropID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.vocationLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.levelLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.visible = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.icon = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.stacks = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.autoUse = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.dropID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.vocationLimit = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.levelLimit = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictProp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10004;  
        static public ushort getProtoID() { return 10004; } 
        static public string getProtoName() { return "DictProp"; } 
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
        public DictProp()  
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
        public DictProp(ulong id, double hp, double hpRegen, double attack, double defense, double crit, double toughness, double moveSpeed, double attackSpeed, double vampirk) 
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
 
 
    public class DictPropArray : System.Collections.Generic.List<DictProp>, Proto4z.IProtoObject  
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
                    var data = new DictProp(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictPropMap : System.Collections.Generic.Dictionary<ulong, DictProp>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Key)); 
                ret.AddRange(kv.Value.__encode()); 
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
                    var val = new DictProp(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictSceneUpLevel: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10005;  
        static public ushort getProtoID() { return 10005; } 
        static public string getProtoName() { return "DictSceneUpLevel"; } 
        //members   
        public ulong id;  
        public ulong nextID; //下一等级的ID  
        public ulong propID; //对应的prop数值  
        public double upExp; //升级所需经验  
        public DictSceneUpLevel()  
        { 
            id = 0;  
            nextID = 0;  
            propID = 0;  
            upExp = 0.0;  
        } 
        public DictSceneUpLevel(ulong id, ulong nextID, ulong propID, double upExp) 
        { 
            this.id = id; 
            this.nextID = nextID; 
            this.propID = propID; 
            this.upExp = upExp; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.nextID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.upExp)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.nextID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.upExp = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictSceneUpLevelArray : System.Collections.Generic.List<DictSceneUpLevel>, Proto4z.IProtoObject  
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
                    var data = new DictSceneUpLevel(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictSceneUpLevelMap : System.Collections.Generic.Dictionary<ulong, DictSceneUpLevel>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Key)); 
                ret.AddRange(kv.Value.__encode()); 
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
                    var val = new DictSceneUpLevel(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictModel: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10006;  
        static public ushort getProtoID() { return 10006; } 
        static public string getProtoName() { return "DictModel"; } 
        //members   
        public ulong eid;  
        public ulong modelID;  
        public string modelName;  
        public ulong avatarID;  
        public string avatarName;  
        public ulong iconID; //头像  
        public double level; //等级  
        public double exp; //经验  
        public double gold; //金币  
        public ushort camp;  
        public ushort etype;  
        public ushort state;  
        public DictModel()  
        { 
            eid = 0;  
            modelID = 0;  
            modelName = "";  
            avatarID = 0;  
            avatarName = "";  
            iconID = 0;  
            level = 0.0;  
            exp = 0.0;  
            gold = 0.0;  
            camp = 0;  
            etype = 0;  
            state = 0;  
        } 
        public DictModel(ulong eid, ulong modelID, string modelName, ulong avatarID, string avatarName, ulong iconID, double level, double exp, double gold, ushort camp, ushort etype, ushort state) 
        { 
            this.eid = eid; 
            this.modelID = modelID; 
            this.modelName = modelName; 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.iconID = iconID; 
            this.level = level; 
            this.exp = exp; 
            this.gold = gold; 
            this.camp = camp; 
            this.etype = etype; 
            this.state = state; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.modelName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.level)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.exp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.gold)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.camp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.etype)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.state)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modelName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.level = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.exp = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.gold = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.camp = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.etype = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.state = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictModelArray : System.Collections.Generic.List<DictModel>, Proto4z.IProtoObject  
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
                    var data = new DictModel(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictModelMap : System.Collections.Generic.Dictionary<ulong, DictModel>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Key)); 
                ret.AddRange(kv.Value.__encode()); 
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
                    var val = new DictModel(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
} 
 
 
