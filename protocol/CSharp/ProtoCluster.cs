 
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
 
    public class CreateServiceInDocker: Proto4z.IProtoObject //创建并初始化一个service  
    {     
        //proto id   
        public const ushort protoID = 40013;  
        static public ushort getProtoID() { return 40013; } 
        static public string getProtoName() { return "CreateServiceInDocker"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clusterID;  
        public CreateServiceInDocker()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clusterID = 0;  
        } 
        public CreateServiceInDocker(ushort serviceType, ulong serviceID, uint clusterID) 
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
 
    public class CreateServiceNotice: Proto4z.IProtoObject //服务创建好并初始化成功,广播给所有docker  
    {     
        //proto id   
        public const ushort protoID = 40010;  
        static public ushort getProtoID() { return 40010; } 
        static public string getProtoName() { return "CreateServiceNotice"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clusterID;  
        public CreateServiceNotice()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clusterID = 0;  
        } 
        public CreateServiceNotice(ushort serviceType, ulong serviceID, uint clusterID) 
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
 
    public class DestroyServiceInDocker: Proto4z.IProtoObject //销毁一个Service  
    {     
        //proto id   
        public const ushort protoID = 40014;  
        static public ushort getProtoID() { return 40014; } 
        static public string getProtoName() { return "DestroyServiceInDocker"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public DestroyServiceInDocker()  
        { 
            serviceType = 0;  
            serviceID = 0;  
        } 
        public DestroyServiceInDocker(ushort serviceType, ulong serviceID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DestroyServiceNotice: Proto4z.IProtoObject //已卸载并完成销毁,广播给所有docker  
    {     
        //proto id   
        public const ushort protoID = 40012;  
        static public ushort getProtoID() { return 40012; } 
        static public string getProtoName() { return "DestroyServiceNotice"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public DestroyServiceNotice()  
        { 
            serviceType = 0;  
            serviceID = 0;  
        } 
        public DestroyServiceNotice(ushort serviceType, ulong serviceID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
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
 
 
