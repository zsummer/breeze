 
namespace Proto4z  
{ 
 
    public class ClusterPulse: Proto4z.IProtoObject //集群脉冲  
    {     
        //proto id   
        public const ushort protoID = 40000;  
        static public ushort getProtoID() { return 40000; } 
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
 
    public class ClusterServiceCreate: Proto4z.IProtoObject //创建并初始化一个service  
    {     
        //proto id   
        public const ushort protoID = 40004;  
        static public ushort getProtoID() { return 40004; } 
        static public string getProtoName() { return "ClusterServiceCreate"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clusterID;  
        public ClusterServiceCreate()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clusterID = 0;  
        } 
        public ClusterServiceCreate(ushort serviceType, ulong serviceID, uint clusterID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.clusterID = clusterID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clusterID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clusterID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClusterServiceCreateNotice: Proto4z.IProtoObject //服务创建好并初始化成功,广播给所有docker  
    {     
        //proto id   
        public const ushort protoID = 40006;  
        static public ushort getProtoID() { return 40006; } 
        static public string getProtoName() { return "ClusterServiceCreateNotice"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clusterID;  
        public ClusterServiceCreateNotice()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clusterID = 0;  
        } 
        public ClusterServiceCreateNotice(ushort serviceType, ulong serviceID, uint clusterID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.clusterID = clusterID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clusterID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clusterID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClusterServiceDestroy: Proto4z.IProtoObject //销毁一个Service  
    {     
        //proto id   
        public const ushort protoID = 40007;  
        static public ushort getProtoID() { return 40007; } 
        static public string getProtoName() { return "ClusterServiceDestroy"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clusterID;  
        public ClusterServiceDestroy()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clusterID = 0;  
        } 
        public ClusterServiceDestroy(ushort serviceType, ulong serviceID, uint clusterID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.clusterID = clusterID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clusterID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clusterID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClusterServiceDestroyNotice: Proto4z.IProtoObject //已卸载并完成销毁,广播给所有docker  
    {     
        //proto id   
        public const ushort protoID = 40008;  
        static public ushort getProtoID() { return 40008; } 
        static public string getProtoName() { return "ClusterServiceDestroyNotice"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clusterID;  
        public ClusterServiceDestroyNotice()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clusterID = 0;  
        } 
        public ClusterServiceDestroyNotice(ushort serviceType, ulong serviceID, uint clusterID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.clusterID = clusterID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clusterID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clusterID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClusterShellForward: Proto4z.IProtoObject //壳子转发  
    {     
        //proto id   
        public const ushort protoID = 40002;  
        static public ushort getProtoID() { return 40002; } 
        static public string getProtoName() { return "ClusterShellForward"; } 
        //members   
        public ClusterShellForward()  
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
 
    public class ClusterClientForward: Proto4z.IProtoObject //client转发  
    {     
        //proto id   
        public const ushort protoID = 40003;  
        static public ushort getProtoID() { return 40003; } 
        static public string getProtoName() { return "ClusterClientForward"; } 
        //members   
        public ClusterClientForward()  
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
 
} 
 
 
