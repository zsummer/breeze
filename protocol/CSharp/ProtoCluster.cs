 
namespace Proto4z  
{ 
 
    public class ClusterPulse: Proto4z.IProtoObject //集群脉冲  
    {     
        //proto id   
        public const ushort protoID = 50000;  
        static public ushort getProtoID() { return 50000; } 
        static public string getProtoName() { return "ClusterPulse"; } 
        //members   
        public ClusterPulse()  
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
 
    public class ClusterServiceInited: Proto4z.IProtoObject //服务初始化成功  
    {     
        //proto id   
        public const ushort protoID = 50001;  
        static public ushort getProtoID() { return 50001; } 
        static public string getProtoName() { return "ClusterServiceInited"; } 
        //members   
        public string entity;  
        public ClusterServiceInited()  
        { 
            entity = "";  
        } 
        public ClusterServiceInited(string entity) 
        { 
            this.entity = entity; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.entity)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entity = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
