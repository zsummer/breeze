 
namespace Proto4z  
{ 
 
    public class SpaceInfoToWorldNotice: Proto4z.IProtoObject //数据刷给world  
    {     
        //proto id   
        public const ushort protoID = 39010;  
        static public ushort getProtoID() { return 39010; } 
        static public string getProtoName() { return "SpaceInfoToWorldNotice"; } 
        //members   
        public string host; //服务器host  
        public ushort port; //服务器port  
        public SpaceInfoArray spaceInfos; //类型  
        public SpaceInfoToWorldNotice()  
        { 
            host = "";  
            port = 0;  
            spaceInfos = new SpaceInfoArray();  
        } 
        public SpaceInfoToWorldNotice(string host, ushort port, SpaceInfoArray spaceInfos) 
        { 
            this.host = host; 
            this.port = port; 
            this.spaceInfos = spaceInfos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            if (this.spaceInfos == null) this.spaceInfos = new SpaceInfoArray(); 
            data.AddRange(this.spaceInfos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.spaceInfos = new SpaceInfoArray(); 
            this.spaceInfos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class FillUserToSpaceReq: Proto4z.IProtoObject //token丢给space  
    {     
        //proto id   
        public const ushort protoID = 39013;  
        static public ushort getProtoID() { return 39013; } 
        static public string getProtoName() { return "FillUserToSpaceReq"; } 
        //members   
        public SpaceID spaceID; //id  
        public ushort sceneType; //类型  
        public string token; //服务器port  
        public UserBaseInfo baseInfo; //类型  
        public FillUserToSpaceReq()  
        { 
            spaceID = new SpaceID();  
            sceneType = 0;  
            token = "";  
            baseInfo = new UserBaseInfo();  
        } 
        public FillUserToSpaceReq(SpaceID spaceID, ushort sceneType, string token, UserBaseInfo baseInfo) 
        { 
            this.spaceID = spaceID; 
            this.sceneType = sceneType; 
            this.token = token; 
            this.baseInfo = baseInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.spaceID == null) this.spaceID = new SpaceID(); 
            data.AddRange(this.spaceID.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            if (this.baseInfo == null) this.baseInfo = new UserBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.spaceID = new SpaceID(); 
            this.spaceID.__decode(binData, ref pos); 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.baseInfo = new UserBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class FillUserToSpaceResp: Proto4z.IProtoObject //token丢给space  
    {     
        //proto id   
        public const ushort protoID = 39014;  
        static public ushort getProtoID() { return 39014; } 
        static public string getProtoName() { return "FillUserToSpaceResp"; } 
        //members   
        public ulong userID;  
        public SpaceID spaceID; //id  
        public ushort sceneType; //类型  
        public FillUserToSpaceResp()  
        { 
            userID = 0;  
            spaceID = new SpaceID();  
            sceneType = 0;  
        } 
        public FillUserToSpaceResp(ulong userID, SpaceID spaceID, ushort sceneType) 
        { 
            this.userID = userID; 
            this.spaceID = spaceID; 
            this.sceneType = sceneType; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.userID)); 
            if (this.spaceID == null) this.spaceID = new SpaceID(); 
            data.AddRange(this.spaceID.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.userID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.spaceID = new SpaceID(); 
            this.spaceID.__decode(binData, ref pos); 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
