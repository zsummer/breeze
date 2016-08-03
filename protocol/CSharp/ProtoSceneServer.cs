 
namespace Proto4z  
{ 
 
    public class AllocateSceneReq: Proto4z.IProtoObject //分配新战场  
    {     
        //proto id   
        public const ushort protoID = 39000;  
        static public ushort getProtoID() { return 39000; } 
        static public string getProtoName() { return "AllocateSceneReq"; } 
        //members   
        public ushort sceneType; //类型  
        public uint mapID;  
        public AvatarBaseInfoArray involeds; //匹配列表中的玩家  
        public AllocateSceneReq()  
        { 
            sceneType = 0;  
            mapID = 0;  
            involeds = new AvatarBaseInfoArray();  
        } 
        public AllocateSceneReq(ushort sceneType, uint mapID, AvatarBaseInfoArray involeds) 
        { 
            this.sceneType = sceneType; 
            this.mapID = mapID; 
            this.involeds = involeds; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.mapID)); 
            if (this.involeds == null) this.involeds = new AvatarBaseInfoArray(); 
            data.AddRange(this.involeds.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.involeds = new AvatarBaseInfoArray(); 
            this.involeds.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AllocateSceneResp: Proto4z.IProtoObject //分配新战场  
    {     
        //proto id   
        public const ushort protoID = 39001;  
        static public ushort getProtoID() { return 39001; } 
        static public string getProtoName() { return "AllocateSceneResp"; } 
        //members   
        public ushort retCode;  
        public SceneTokenInfoArray tokens; //匹配列表中的玩家  
        public AllocateSceneResp()  
        { 
            retCode = 0;  
            tokens = new SceneTokenInfoArray();  
        } 
        public AllocateSceneResp(ushort retCode, SceneTokenInfoArray tokens) 
        { 
            this.retCode = retCode; 
            this.tokens = tokens; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.tokens == null) this.tokens = new SceneTokenInfoArray(); 
            data.AddRange(this.tokens.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.tokens = new SceneTokenInfoArray(); 
            this.tokens.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
