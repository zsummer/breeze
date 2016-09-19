 
namespace Proto4z  
{ 
 
 
    public class SceneTypeArray : System.Collections.Generic.List<ushort>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeUI16(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeUI16(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class SceneKnock: Proto4z.IProtoObject //战场服务器挂载  
    {     
        //proto id   
        public const ushort protoID = 39004;  
        static public ushort getProtoID() { return 39004; } 
        static public string getProtoName() { return "SceneKnock"; } 
        //members   
        public uint sceneID; //断线检测  
        public string pubHost;  
        public ushort pubPort;  
        public SceneKnock()  
        { 
            sceneID = 0;  
            pubHost = "";  
            pubPort = 0;  
        } 
        public SceneKnock(uint sceneID, string pubHost, ushort pubPort) 
        { 
            this.sceneID = sceneID; 
            this.pubHost = pubHost; 
            this.pubPort = pubPort; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.pubHost)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.pubPort)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.pubHost = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.pubPort = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ScenePulse: Proto4z.IProtoObject //集群脉冲  
    {     
        //proto id   
        public const ushort protoID = 39005;  
        static public ushort getProtoID() { return 39005; } 
        static public string getProtoName() { return "ScenePulse"; } 
        //members   
        public ScenePulse()  
        { 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            return pos; 
        } 
    } 
 
    public class AllocateSceneReq: Proto4z.IProtoObject //分配战场  
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
 
    public class AllocateSceneResp: Proto4z.IProtoObject //分配战场  
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
 
 
