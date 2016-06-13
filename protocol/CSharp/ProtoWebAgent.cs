 
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
 
    public class WebAgentToService: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 5100;  
        static public ushort getProtoID() { return 5100; } 
        static public string getProtoName() { return "WebAgentToService"; } 
        //members   
        public uint webClientID;  
        public string method;  
        public string methodLine;  
        public WebAgentHead heads;  
        public string body;  
        public WebAgentToService()  
        { 
            webClientID = 0;  
            method = "";  
            methodLine = "";  
            heads = new WebAgentHead();  
            body = "";  
        } 
        public WebAgentToService(uint webClientID, string method, string methodLine, WebAgentHead heads, string body) 
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
 
    public class WebAgentToClient: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 5101;  
        static public ushort getProtoID() { return 5101; } 
        static public string getProtoName() { return "WebAgentToClient"; } 
        //members   
        public string method;  
        public string methodLine;  
        public WebAgentHead heads;  
        public string body;  
        public WebAgentToClient()  
        { 
            method = "";  
            methodLine = "";  
            heads = new WebAgentHead();  
            body = "";  
        } 
        public WebAgentToClient(string method, string methodLine, WebAgentHead heads, string body) 
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
 
 
