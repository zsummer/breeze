 
namespace Proto4z  
{ 
 
    public class UserOffline: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 5200;  
        static public ushort getProtoID() { return 5200; } 
        static public string getProtoName() { return "UserOffline"; } 
        //members   
        public ulong id;  
        public ulong serviceID;  
        public string streamBlob;  
        public ushort status;  
        public uint timestamp;  
        public UserOffline()  
        { 
            id = 0;  
            serviceID = 0;  
            streamBlob = "";  
            status = 0;  
            timestamp = 0;  
        } 
        public UserOffline(ulong id, ulong serviceID, string streamBlob, ushort status, uint timestamp) 
        { 
            this.id = id; 
            this.serviceID = serviceID; 
            this.streamBlob = streamBlob; 
            this.status = status; 
            this.timestamp = timestamp; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.streamBlob)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.timestamp)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.streamBlob = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.timestamp = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
