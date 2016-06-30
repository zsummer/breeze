 
namespace Proto4z  
{ 
 
    public enum SCENE_STATUS : ushort 
    { 
        SCENE_STATUS_NONE = 0, //无效  
        SCENE_STATUS_HOME = 1, //主城  
        SCENE_STATUS_INSTANCING = 2, //副本  
        SCENE_STATUS_ARENA = 3, //竞技场  
    }; 
 
    public class SceneStatus: Proto4z.IProtoObject //场景状态数据  
    {     
        //proto id   
        public const ushort protoID = 10000;  
        static public ushort getProtoID() { return 10000; } 
        static public string getProtoName() { return "SceneStatus"; } 
        //members   
        public ushort type; //类型  
        public ushort state; //状态  
        public string host; //服务器host  
        public ushort port; //服务器port  
        public uint spaceID; //空间(场景,房间,战场)的实例ID  
        public SessionToken token; //令牌  
        public SceneStatus()  
        { 
            type = 0;  
            state = 0;  
            host = "";  
            port = 0;  
            spaceID = 0;  
            token = new SessionToken();  
        } 
        public SceneStatus(ushort type, ushort state, string host, ushort port, uint spaceID, SessionToken token) 
        { 
            this.type = type; 
            this.state = state; 
            this.host = host; 
            this.port = port; 
            this.spaceID = spaceID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.state)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.spaceID)); 
            if (this.token == null) this.token = new SessionToken(); 
            data.AddRange(this.token.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.state = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.token = new SessionToken(); 
            this.token.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
