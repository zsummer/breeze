 
namespace Proto4z  
{ 
 
 
    public class DictArrayValue : System.Collections.Generic.List<double>, Proto4z.IProtoObject //通用Value数组  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeDouble(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeDouble(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictArrayKey : System.Collections.Generic.List<ulong>, Proto4z.IProtoObject //通用KEY数组  
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
 
 
    public class DictMapKeyValue : System.Collections.Generic.Dictionary<ulong, double>, Proto4z.IProtoObject //通用Key value  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI64(kv.Key)); 
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
                    var key = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
                    var val = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictPairValue: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10009;  
        static public ushort getProtoID() { return 10009; } 
        static public string getProtoName() { return "DictPairValue"; } 
        //members   
        public ulong val1;  
        public ulong val2;  
        public DictPairValue()  
        { 
            val1 = 0;  
            val2 = 0;  
        } 
        public DictPairValue(ulong val1, ulong val2) 
        { 
            this.val1 = val1; 
            this.val2 = val2; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.val1)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.val2)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.val1 = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.val2 = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictMapKeyPairValue : System.Collections.Generic.Dictionary<ulong, DictPairValue>, Proto4z.IProtoObject  
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
                    var val = new DictPairValue(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
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
 
 
    public class DictGlobalArray : System.Collections.Generic.List<DictGlobal>, Proto4z.IProtoObject  
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
                    var data = new DictGlobal(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictGlobalMap : System.Collections.Generic.Dictionary<ulong, DictGlobal>, Proto4z.IProtoObject  
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
                    var val = new DictGlobal(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
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
        public ushort dropType; //0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到  
        public DictMapKeyPairValue rewards; //奖池  
        public string rewardsText; //奖池 格式为 id|count|prob,id|count|prob   
        public string desc;  
        public DictDrop()  
        { 
            id = 0;  
            dropType = 0;  
            rewards = new DictMapKeyPairValue();  
            rewardsText = "";  
            desc = "";  
        } 
        public DictDrop(ulong id, ushort dropType, DictMapKeyPairValue rewards, string rewardsText, string desc) 
        { 
            this.id = id; 
            this.dropType = dropType; 
            this.rewards = rewards; 
            this.rewardsText = rewardsText; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.dropType)); 
            if (this.rewards == null) this.rewards = new DictMapKeyPairValue(); 
            data.AddRange(this.rewards.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.rewardsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dropType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.rewards = new DictMapKeyPairValue(); 
            this.rewards.__decode(binData, ref pos); 
            this.rewardsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
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
        public ushort icon;  
        public ushort autoUse; //0 手动, 其他 自动使用  
        public double stacks; //可堆叠个数,0和1都是1次  
        public DictMapKeyValue costItems; //使用该道具需要消耗的其他道具  
        public DictMapKeyValue costItemsText; //使用该道具需要消耗的其他道具  
        public ulong dropID; //使用该道具后会产生掉落效果 0为无效  
        public ulong propID; //装备该道具带来的属性加成  
        public DictArrayKey skills; //装备该道具带来的可用技能  
        public string skillsText; //装备该道具带来的可用技能 格式id,id,id   
        public DictArrayKey buffs; //装备该道具带来的可用buff  
        public string buffsText; //装备该道具带来的可用buff 格式id,id,id  
        public ushort visible; //是否可见  
        public string desc;  
        public DictItem()  
        { 
            id = 0;  
            icon = 0;  
            autoUse = 0;  
            stacks = 0.0;  
            costItems = new DictMapKeyValue();  
            costItemsText = new DictMapKeyValue();  
            dropID = 0;  
            propID = 0;  
            skills = new DictArrayKey();  
            skillsText = "";  
            buffs = new DictArrayKey();  
            buffsText = "";  
            visible = 0;  
            desc = "";  
        } 
        public DictItem(ulong id, ushort icon, ushort autoUse, double stacks, DictMapKeyValue costItems, DictMapKeyValue costItemsText, ulong dropID, ulong propID, DictArrayKey skills, string skillsText, DictArrayKey buffs, string buffsText, ushort visible, string desc) 
        { 
            this.id = id; 
            this.icon = icon; 
            this.autoUse = autoUse; 
            this.stacks = stacks; 
            this.costItems = costItems; 
            this.costItemsText = costItemsText; 
            this.dropID = dropID; 
            this.propID = propID; 
            this.skills = skills; 
            this.skillsText = skillsText; 
            this.buffs = buffs; 
            this.buffsText = buffsText; 
            this.visible = visible; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.icon)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.autoUse)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.stacks)); 
            if (this.costItems == null) this.costItems = new DictMapKeyValue(); 
            data.AddRange(this.costItems.__encode()); 
            if (this.costItemsText == null) this.costItemsText = new DictMapKeyValue(); 
            data.AddRange(this.costItemsText.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dropID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            if (this.skills == null) this.skills = new DictArrayKey(); 
            data.AddRange(this.skills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.skillsText)); 
            if (this.buffs == null) this.buffs = new DictArrayKey(); 
            data.AddRange(this.buffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.buffsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.visible)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.icon = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.autoUse = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.stacks = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.costItems = new DictMapKeyValue(); 
            this.costItems.__decode(binData, ref pos); 
            this.costItemsText = new DictMapKeyValue(); 
            this.costItemsText.__decode(binData, ref pos); 
            this.dropID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skills = new DictArrayKey(); 
            this.skills.__decode(binData, ref pos); 
            this.skillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.buffs = new DictArrayKey(); 
            this.buffs.__decode(binData, ref pos); 
            this.buffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.visible = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictItemArray : System.Collections.Generic.List<DictItem>, Proto4z.IProtoObject  
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
                    var data = new DictItem(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictItemMap : System.Collections.Generic.Dictionary<ulong, DictItem>, Proto4z.IProtoObject  
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
                    var val = new DictItem(); 
                    val.__decode(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DictProp: Proto4z.IProtoObject //战斗属性  
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
        public string desc;  
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
            desc = "";  
        } 
        public DictProp(ulong id, double hp, double hpRegen, double attack, double defense, double crit, double toughness, double moveSpeed, double attackSpeed, double vampirk, string desc) 
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
            this.desc = desc; 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
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
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
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
 
    public class DictModelLevel: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10010;  
        static public ushort getProtoID() { return 10010; } 
        static public string getProtoName() { return "DictModelLevel"; } 
        //members   
        public ulong modelID;  
        public ulong levelID;  
        public double needExp; //升级所需经验  
        public ulong propID; //战斗属性  
        public DictArrayKey skills; //该等级带来的可用技能  
        public string skillsText; //该等级带来的可用技能 格式id,id,id   
        public DictArrayKey buffs; //该等级带来的可用buff  
        public string buffsText; //该等级带来的可用buff 格式id,id,id  
        public DictModelLevel()  
        { 
            modelID = 0;  
            levelID = 0;  
            needExp = 0.0;  
            propID = 0;  
            skills = new DictArrayKey();  
            skillsText = "";  
            buffs = new DictArrayKey();  
            buffsText = "";  
        } 
        public DictModelLevel(ulong modelID, ulong levelID, double needExp, ulong propID, DictArrayKey skills, string skillsText, DictArrayKey buffs, string buffsText) 
        { 
            this.modelID = modelID; 
            this.levelID = levelID; 
            this.needExp = needExp; 
            this.propID = propID; 
            this.skills = skills; 
            this.skillsText = skillsText; 
            this.buffs = buffs; 
            this.buffsText = buffsText; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.levelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.needExp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            if (this.skills == null) this.skills = new DictArrayKey(); 
            data.AddRange(this.skills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.skillsText)); 
            if (this.buffs == null) this.buffs = new DictArrayKey(); 
            data.AddRange(this.buffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.buffsText)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.modelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.levelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.needExp = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skills = new DictArrayKey(); 
            this.skills.__decode(binData, ref pos); 
            this.skillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.buffs = new DictArrayKey(); 
            this.buffs.__decode(binData, ref pos); 
            this.buffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DictModelLevelArray : System.Collections.Generic.List<DictModelLevel>, Proto4z.IProtoObject  
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
                    var data = new DictModelLevel(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
 
    public class DictModelLevelMap : System.Collections.Generic.Dictionary<ulong, DictModelLevel>, Proto4z.IProtoObject  
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
                    var val = new DictModelLevel(); 
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
        public ulong modelID;  
        public string modelName;  
        public double modelRedius; //碰撞半径  
        public ulong iconID; //头像  
        public double initLevel; //等级  
        public ushort initCamp;  
        public DictMapKeyPairValue initItems;  
        public string initItemsText;  
        public ushort initState; //初始化状态  
        public string actionScriptPath; //行为树脚本路径  
        public string clientModelPath; //客户端模型路径  
        public string desc;  
        public DictModel()  
        { 
            modelID = 0;  
            modelName = "";  
            modelRedius = 0.0;  
            iconID = 0;  
            initLevel = 0.0;  
            initCamp = 0;  
            initItems = new DictMapKeyPairValue();  
            initItemsText = "";  
            initState = 0;  
            actionScriptPath = "";  
            clientModelPath = "";  
            desc = "";  
        } 
        public DictModel(ulong modelID, string modelName, double modelRedius, ulong iconID, double initLevel, ushort initCamp, DictMapKeyPairValue initItems, string initItemsText, ushort initState, string actionScriptPath, string clientModelPath, string desc) 
        { 
            this.modelID = modelID; 
            this.modelName = modelName; 
            this.modelRedius = modelRedius; 
            this.iconID = iconID; 
            this.initLevel = initLevel; 
            this.initCamp = initCamp; 
            this.initItems = initItems; 
            this.initItemsText = initItemsText; 
            this.initState = initState; 
            this.actionScriptPath = actionScriptPath; 
            this.clientModelPath = clientModelPath; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.modelName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.modelRedius)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.iconID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.initLevel)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.initCamp)); 
            if (this.initItems == null) this.initItems = new DictMapKeyPairValue(); 
            data.AddRange(this.initItems.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.initItemsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.initState)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.actionScriptPath)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.clientModelPath)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.modelID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.modelName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.modelRedius = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.initLevel = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.initCamp = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.initItems = new DictMapKeyPairValue(); 
            this.initItems.__decode(binData, ref pos); 
            this.initItemsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.initState = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.actionScriptPath = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.clientModelPath = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
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
 
    public enum TARGET_CAMP : ulong 
    { 
        SEARCH_CAMP_NONE = 0, //自身  
        SEARCH_CAMP_SELF = 1, //自身  
        SEARCH_CAMP_SAME_WITHOUT_SELF = 2, //同阵营非自己  
        SEARCH_CAMP_ALIEN = 3, //非己方阵营  
    }; 
 
    public class AOESearch: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10011;  
        static public ushort getProtoID() { return 10011; } 
        static public string getProtoName() { return "AOESearch"; } 
        //members   
        public ulong id;  
        public ushort etype; //实体类型, 玩家/AI 或者是NONE忽略该选项  
        public ulong camp; //0忽略改选项, 1位标识自己, 2位标识同阵营非自己, 3其他阵营,   逗号分割 多选 SearchCampType  
        public string campText;  
        public ushort isRect; //0扇形, 其他矩形  
        public double distance; //伤害距离  
        public double radian; //弧度或者宽度  
        public double offsetX; //坐标偏移量, 以caster为原点, 朝向为y轴  
        public double offsetY; //坐标偏移量, 以caster为原点, 朝向为y轴  
        public ulong limitEntitys; //最大目标数  
        public AOESearch()  
        { 
            id = 0;  
            etype = 0;  
            camp = 0;  
            campText = "";  
            isRect = 0;  
            distance = 0.0;  
            radian = 0.0;  
            offsetX = 0.0;  
            offsetY = 0.0;  
            limitEntitys = 0;  
        } 
        public AOESearch(ulong id, ushort etype, ulong camp, string campText, ushort isRect, double distance, double radian, double offsetX, double offsetY, ulong limitEntitys) 
        { 
            this.id = id; 
            this.etype = etype; 
            this.camp = camp; 
            this.campText = campText; 
            this.isRect = isRect; 
            this.distance = distance; 
            this.radian = radian; 
            this.offsetX = offsetX; 
            this.offsetY = offsetY; 
            this.limitEntitys = limitEntitys; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.etype)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.camp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.campText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.isRect)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.distance)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.radian)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.offsetX)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.offsetY)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.limitEntitys)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.etype = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.camp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.campText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.isRect = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.distance = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.radian = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.offsetX = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.offsetY = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.limitEntitys = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum BUFF_STAMP : ulong 
    { 
        BUFF_HALO = 1, //描述性类型: 光环  
        BUFF_BUFF = 2, //描述性类型: 增益buff  
        BUFF_DEBUFF = 3, //描述性类型: 减益BUFF  
        BUFF_HIDE = 4, //描述性类型: 客户端不表现  
        BUFF_PASSIVE = 5, //描述性类型: 被动技能, 无法永久存在, 但死亡会停止任何触发  
        BUFF_HOLD_MOVE = 10, //控制: 禁止移动  
        BUFF_REVERSE_MOVE = 11, //控制: 移动反向  
        BUFF_SILENCE_GENERAL = 12, //控制: 沉默普攻  
        BUFF_SILENCE_PHYSICAL = 13, //控制: 沉默物攻  
        BUFF_SILENCE_MAGIC = 14, //控制: 沉默法攻  
        BUFF_IMMUNE_MOVE = 20, //免疫: 免疫移动类控制  
        BUFF_IMMUNE_SILENCE_GENERAL = 21, //免疫: 免疫普攻沉默  
        BUFF_IMMUNE_SILENCE_PHYSICAL = 22, //免疫: 免疫物攻沉默  
        BUFF_IMMUNE_SILENCE_MAGIC = 23, //免疫: 免疫法攻沉默  
        BUFF_IMMUNE_DEBUFF = 30, //免疫: 免疫DEBUFF  
        BUFF_IMMUNE_BUFF = 31, //免疫: 免疫增益BUFF  
        BUFF_IMMUNE_OCCUPIED = 32, //免疫: 免疫占据  
        BUFF_IMMUNE_FLOAT = 33, //免疫: 免疫击飞  
        BUFF_IMMUNE_MOVEBACK = 34, //免疫: 免疫击退  
        BUFF_IMMUNE_BREAK = 35, //免疫: 免疫技能中断  
    }; 
 
    public enum BUFF_EFFECT_STAMP : ulong 
    { 
        BUFF_EFFECT_TRIGGER_WHEN_LOAD = 1, //加载buff立刻触发  
        BUFF_EFFECT_TRIGGER_WHEN_UNLOAD = 2, //卸载buff立刻触发  
        BUFF_EFFECT_PROP_MULTIPLICATION = 3, //属性求积, 没有该标记为求和  
        BUFF_EFFECT_TRIGGER_PRE_DEATH = 10, //死亡前触发  
        BUFF_EFFECT_TRIGGER_AFT_DEATH = 11, //死亡后触发  
        BUFF_EFFECT_TRIGGER_WHEN_GENERAL = 15, //攻击触发  
        BUFF_EFFECT_TRIGGER_WHEN_PHYSICAL = 16, //攻击触发  
        BUFF_EFFECT_TRIGGER_WHEN_MAGIC = 17, //攻击触发  
        BUFF_EFFECT_TRIGGER_ON_GENERAL = 20, //被攻击触发  
        BUFF_EFFECT_TRIGGER_ON_PHYSICAL = 21, //被攻击触发  
        BUFF_EFFECT_TRIGGER_ON_MAGIC = 22, //被攻击触发  
        BUFF_EFFECT_TRIGGER_WHEN_ATTACH_GENERAL = 30, //攻击触发  
        BUFF_EFFECT_TRIGGER_WHEN_ON_ATTACH = 31, //被攻击触发  
    }; 
 
    public class DictBuffEffect: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10012;  
        static public ushort getProtoID() { return 10012; } 
        static public string getProtoName() { return "DictBuffEffect"; } 
        //members   
        public ulong id;  
        public ulong stamp; //BUFF_EFFECT_STAMP  
        public string stampText;  
        public ulong propID; //提升的属性效果, 求积方式的参数是基础属性 不算其他装备  
        public DictArrayKey skills; //触发技能  
        public string skillsText; //触发技能 格式id,id,id   
        public DictArrayKey buffs; //触发buff  
        public string buffsText; //触发buff 格式id,id,id  
        public double delayTrigger; //延迟触发, 0为无效  
        public double areaTrigger; //距离触发, 0为无效  
        public double intervalLimit; //最小触发间隔时间, 0为无效  
        public double countLimit; //触发次数限制  
        public string desc;  
        public DictBuffEffect()  
        { 
            id = 0;  
            stamp = 0;  
            stampText = "";  
            propID = 0;  
            skills = new DictArrayKey();  
            skillsText = "";  
            buffs = new DictArrayKey();  
            buffsText = "";  
            delayTrigger = 0.0;  
            areaTrigger = 0.0;  
            intervalLimit = 0.0;  
            countLimit = 0.0;  
            desc = "";  
        } 
        public DictBuffEffect(ulong id, ulong stamp, string stampText, ulong propID, DictArrayKey skills, string skillsText, DictArrayKey buffs, string buffsText, double delayTrigger, double areaTrigger, double intervalLimit, double countLimit, string desc) 
        { 
            this.id = id; 
            this.stamp = stamp; 
            this.stampText = stampText; 
            this.propID = propID; 
            this.skills = skills; 
            this.skillsText = skillsText; 
            this.buffs = buffs; 
            this.buffsText = buffsText; 
            this.delayTrigger = delayTrigger; 
            this.areaTrigger = areaTrigger; 
            this.intervalLimit = intervalLimit; 
            this.countLimit = countLimit; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.stamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.stampText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.propID)); 
            if (this.skills == null) this.skills = new DictArrayKey(); 
            data.AddRange(this.skills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.skillsText)); 
            if (this.buffs == null) this.buffs = new DictArrayKey(); 
            data.AddRange(this.buffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.buffsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.delayTrigger)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.areaTrigger)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.intervalLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.countLimit)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stamp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stampText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.propID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skills = new DictArrayKey(); 
            this.skills.__decode(binData, ref pos); 
            this.skillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.buffs = new DictArrayKey(); 
            this.buffs.__decode(binData, ref pos); 
            this.buffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.delayTrigger = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.areaTrigger = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.intervalLimit = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.countLimit = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictBuff: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10013;  
        static public ushort getProtoID() { return 10013; } 
        static public string getProtoName() { return "DictBuff"; } 
        //members   
        public ulong id;  
        public ulong stamp; //BUFF_STAMP  
        public string stampText;  
        public DictArrayKey effects; //DictBuffEffect ID  
        public string effectsText;  
        public double keepTime;  
        public ushort mutexType; //0无互斥, 1 同ID时间叠加, 2 同ID时间最长的覆盖, 3 同ID最强的覆盖  
        public ulong mutexID; //0  
        public double mutexStrength;  
        public double limitTime;  
        public string desc;  
        public DictBuff()  
        { 
            id = 0;  
            stamp = 0;  
            stampText = "";  
            effects = new DictArrayKey();  
            effectsText = "";  
            keepTime = 0.0;  
            mutexType = 0;  
            mutexID = 0;  
            mutexStrength = 0.0;  
            limitTime = 0.0;  
            desc = "";  
        } 
        public DictBuff(ulong id, ulong stamp, string stampText, DictArrayKey effects, string effectsText, double keepTime, ushort mutexType, ulong mutexID, double mutexStrength, double limitTime, string desc) 
        { 
            this.id = id; 
            this.stamp = stamp; 
            this.stampText = stampText; 
            this.effects = effects; 
            this.effectsText = effectsText; 
            this.keepTime = keepTime; 
            this.mutexType = mutexType; 
            this.mutexID = mutexID; 
            this.mutexStrength = mutexStrength; 
            this.limitTime = limitTime; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.stamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.stampText)); 
            if (this.effects == null) this.effects = new DictArrayKey(); 
            data.AddRange(this.effects.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.effectsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.keepTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.mutexType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.mutexID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.mutexStrength)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.limitTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stamp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stampText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.effects = new DictArrayKey(); 
            this.effects.__decode(binData, ref pos); 
            this.effectsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.keepTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.mutexType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mutexID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.mutexStrength = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.limitTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public enum SKILL_STAMP : ulong 
    { 
        SKILL_NONE = 0,  
        SKILL_AUTO_LOCK = 1, //自动锁敌  
        SKILL_AUTO_USE = 2, //自动施法  
        SKILL_PASSIVE = 3, //被动技能  
        SKILL_ON_HIT_BREAK = 4, //可被中断  
        SKILL_ON_MOVE_BREAK = 5, //可被中断  
        SKILL_CAN_MOVE = 6, //可移动  
        SKILL_PHYSICAL = 7, //物理类型  
        SKILL_MAGIC = 8, //魔法类型  
    }; 
 
    public enum SKILL_BEHAVIOUR_STAMP : ulong 
    { 
        SKILL_BEHAVIOUR_NONE = 0,  
        SKILL_BEHAVIOUR_HIT = 1, //攻击  
        SKILL_BEHAVIOUR_HILL = 2, //治疗  
        SKILL_BEHAVIOUR_TELEPORT_TARGET = 3, //瞬移到目标  
        SKILL_BEHAVIOUR_REMOVE_DEBUFF = 4, //驱散减益BUFF  
        SKILL_BEHAVIOUR_REMOVE_BUFF = 5, //驱散增益BUFF  
        SKILL_BEHAVIOUR_TRIGGER_BUFF = 6, //触发buff  
        SKILL_BEHAVIOUR_TRIGGER_SKILL = 7, //触发技能  
    }; 
 
    public class DictSkillEffect: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10014;  
        static public ushort getProtoID() { return 10014; } 
        static public string getProtoName() { return "DictSkillEffect"; } 
        //members   
        public ulong id;  
        public ulong stamp;  
        public ushort hpMode; //血量变化类型:0 相加, 1与总血量相乘后再相加, 2与剩余血量相乘后再相加, 3与已损失血量相乘后叠加  
        public double hpLeft; //血量变化参数  
        public double hitKeepTime; //击退,浮空,牵引,的持续时间  
        public double hitKeepSpeed; //击退,浮空,牵引,的持速度  
        public DictArrayKey skills; //触发技能  
        public string skillsText; //触发技能 格式id,id,id   
        public DictArrayKey buffs; //触发buff  
        public string buffsText; //触发buff 格式id,id,id  
        public string desc;  
        public DictSkillEffect()  
        { 
            id = 0;  
            stamp = 0;  
            hpMode = 0;  
            hpLeft = 0.0;  
            hitKeepTime = 0.0;  
            hitKeepSpeed = 0.0;  
            skills = new DictArrayKey();  
            skillsText = "";  
            buffs = new DictArrayKey();  
            buffsText = "";  
            desc = "";  
        } 
        public DictSkillEffect(ulong id, ulong stamp, ushort hpMode, double hpLeft, double hitKeepTime, double hitKeepSpeed, DictArrayKey skills, string skillsText, DictArrayKey buffs, string buffsText, string desc) 
        { 
            this.id = id; 
            this.stamp = stamp; 
            this.hpMode = hpMode; 
            this.hpLeft = hpLeft; 
            this.hitKeepTime = hitKeepTime; 
            this.hitKeepSpeed = hitKeepSpeed; 
            this.skills = skills; 
            this.skillsText = skillsText; 
            this.buffs = buffs; 
            this.buffsText = buffsText; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.stamp)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.hpMode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hpLeft)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hitKeepTime)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hitKeepSpeed)); 
            if (this.skills == null) this.skills = new DictArrayKey(); 
            data.AddRange(this.skills.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.skillsText)); 
            if (this.buffs == null) this.buffs = new DictArrayKey(); 
            data.AddRange(this.buffs.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.buffsText)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.stamp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.hpMode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.hpLeft = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.hitKeepTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.hitKeepSpeed = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.skills = new DictArrayKey(); 
            this.skills.__decode(binData, ref pos); 
            this.skillsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.buffs = new DictArrayKey(); 
            this.buffs.__decode(binData, ref pos); 
            this.buffsText = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DictSkill: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 10015;  
        static public ushort getProtoID() { return 10015; } 
        static public string getProtoName() { return "DictSkill"; } 
        //members   
        public ulong id;  
        public ulong effectID;  
        public ushort hpMode; //0 相加, 1与总血量相乘后再相加, 2与剩余血量相乘后再相加, 3与已损失血量相乘后叠加  
        public double hpLeft; //当前血量提升, 如果是求积 则是  
        public string desc;  
        public DictSkill()  
        { 
            id = 0;  
            effectID = 0;  
            hpMode = 0;  
            hpLeft = 0.0;  
            desc = "";  
        } 
        public DictSkill(ulong id, ulong effectID, ushort hpMode, double hpLeft, string desc) 
        { 
            this.id = id; 
            this.effectID = effectID; 
            this.hpMode = hpMode; 
            this.hpLeft = hpLeft; 
            this.desc = desc; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.effectID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.hpMode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.hpLeft)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.desc)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.effectID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.hpMode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.hpLeft = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.desc = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
