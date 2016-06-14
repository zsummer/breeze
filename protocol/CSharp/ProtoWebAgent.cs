 
namespace Proto4z  
{ 
 
 
    public class WebAgentHead : System.Collections.Generic.Dictionary<string, string>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(kv.Key)); 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(kv.Value)); 
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
                    var val = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class WebAgentClientRequestAPI: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 5105;  
        static public ushort getProtoID() { return 5105; } 
        static public string getProtoName() { return "WebAgentClientRequestAPI"; } 
        //members   
        public uint webClientID;  
        public string method;  
        public string methodLine;  
        public WebAgentHead heads;  
        public string body;  
        public WebAgentClientRequestAPI()  
        { 
            webClientID = 0;  
            method = "";  
            methodLine = "";  
            heads = new WebAgentHead();  
            body = "";  
        } 
        public WebAgentClientRequestAPI(uint webClientID, string method, string methodLine, WebAgentHead heads, string body) 
        { 
            this.webClientID = webClientID; 
            this.method = method; 
            this.methodLine = methodLine; 
            this.heads = heads; 
            this.body = body; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.webClientID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.method)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.methodLine)); 
            if (this.heads == null) this.heads = new WebAgentHead(); 
            data.AddRange(this.heads.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.body)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.webClientID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.method = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.methodLine = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.heads = new WebAgentHead(); 
            this.heads.__decode(binData, ref pos); 
            this.body = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WebServerRequest: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 5106;  
        static public ushort getProtoID() { return 5106; } 
        static public string getProtoName() { return "WebServerRequest"; } 
        //members   
        public uint fromServiceType;  
        public ulong fromServiceID;  
        public uint traceID;  
        public string ip;  
        public ushort port;  
        public string uri;  
        public string params;  
        public WebAgentHead heads;  
        public byte isGet; //get or post  
        public WebServerRequest()  
        { 
            fromServiceType = 0;  
            fromServiceID = 0;  
            traceID = 0;  
            ip = "";  
            port = 0;  
            uri = "";  
            params = "";  
            heads = new WebAgentHead();  
            isGet = 0;  
        } 
        public WebServerRequest(uint fromServiceType, ulong fromServiceID, uint traceID, string ip, ushort port, string uri, string params, WebAgentHead heads, byte isGet) 
        { 
            this.fromServiceType = fromServiceType; 
            this.fromServiceID = fromServiceID; 
            this.traceID = traceID; 
            this.ip = ip; 
            this.port = port; 
            this.uri = uri; 
            this.params = params; 
            this.heads = heads; 
            this.isGet = isGet; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.fromServiceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.fromServiceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.traceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.ip)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.uri)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.params)); 
            if (this.heads == null) this.heads = new WebAgentHead(); 
            data.AddRange(this.heads.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI8(this.isGet)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.fromServiceType = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.fromServiceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.traceID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.ip = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.uri = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.params = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.heads = new WebAgentHead(); 
            this.heads.__decode(binData, ref pos); 
            this.isGet = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WebServerResponse: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 5107;  
        static public ushort getProtoID() { return 5107; } 
        static public string getProtoName() { return "WebServerResponse"; } 
        //members   
        public string method;  
        public string methodLine;  
        public WebAgentHead heads;  
        public string body;  
        public WebServerResponse()  
        { 
            method = "";  
            methodLine = "";  
            heads = new WebAgentHead();  
            body = "";  
        } 
        public WebServerResponse(string method, string methodLine, WebAgentHead heads, string body) 
        { 
            this.method = method; 
            this.methodLine = methodLine; 
            this.heads = heads; 
            this.body = body; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.method)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.methodLine)); 
            if (this.heads == null) this.heads = new WebAgentHead(); 
            data.AddRange(this.heads.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.body)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.method = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.methodLine = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.heads = new WebAgentHead(); 
            this.heads.__decode(binData, ref pos); 
            this.body = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
