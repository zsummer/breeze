 
namespace Proto4z  
{ 
 
    public class AllocateSpaceReq: Proto4z.IProtoObject //分配新战场  
    {     
        //proto id   
        public const ushort protoID = 39015;  
        static public ushort getProtoID() { return 39015; } 
        static public string getProtoName() { return "AllocateSpaceReq"; } 
        //members   
        public ushort spaceType; //类型  
        public uint mapID;  
        public UserBaseInfoArray involeds; //匹配列表中的玩家  
        public AllocateSpaceReq()  
        { 
            spaceType = 0;  
            mapID = 0;  
            involeds = new UserBaseInfoArray();  
        } 
        public AllocateSpaceReq(ushort spaceType, uint mapID, UserBaseInfoArray involeds) 
        { 
            this.spaceType = spaceType; 
            this.mapID = mapID; 
            this.involeds = involeds; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.spaceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.mapID)); 
            if (this.involeds == null) this.involeds = new UserBaseInfoArray(); 
            data.AddRange(this.involeds.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.involeds = new UserBaseInfoArray(); 
            this.involeds.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AllocateSpaceResp: Proto4z.IProtoObject //分配新战场  
    {     
        //proto id   
        public const ushort protoID = 39016;  
        static public ushort getProtoID() { return 39016; } 
        static public string getProtoName() { return "AllocateSpaceResp"; } 
        //members   
        public ushort retCode;  
        public SpaceTokenInfoArray tokens; //匹配列表中的玩家  
        public AllocateSpaceResp()  
        { 
            retCode = 0;  
            tokens = new SpaceTokenInfoArray();  
        } 
        public AllocateSpaceResp(ushort retCode, SpaceTokenInfoArray tokens) 
        { 
            this.retCode = retCode; 
            this.tokens = tokens; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.tokens == null) this.tokens = new SpaceTokenInfoArray(); 
            data.AddRange(this.tokens.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.tokens = new SpaceTokenInfoArray(); 
            this.tokens.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
