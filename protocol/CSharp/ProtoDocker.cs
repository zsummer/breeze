 
namespace Proto4z  
{ 
 
    public class DockerPulse: Proto4z.IProtoObject //集群脉冲  
    {     
        //proto id   
        public const ushort protoID = 2000;  
        static public ushort getProtoID() { return 2000; } 
        static public string getProtoName() { return "DockerPulse"; } 
        //members   
        public DockerPulse()  
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
        public const ushort protoID = 2001;  
        static public ushort getProtoID() { return 2001; } 
        static public string getProtoName() { return "CreateServiceInDocker"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public CreateServiceInDocker()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public CreateServiceInDocker(ushort serviceType, ulong serviceID, string serviceName, uint clientDockerID, uint clientSessionID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.serviceName = serviceName; 
            this.clientDockerID = clientDockerID; 
            this.clientSessionID = clientSessionID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.serviceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serviceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateOrRefreshServiceNotice: Proto4z.IProtoObject //广播给所有docker  
    {     
        //proto id   
        public const ushort protoID = 2003;  
        static public ushort getProtoID() { return 2003; } 
        static public string getProtoName() { return "CreateOrRefreshServiceNotice"; } 
        //members   
        public uint serviceDockerID;  
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public CreateOrRefreshServiceNotice()  
        { 
            serviceDockerID = 0;  
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public CreateOrRefreshServiceNotice(uint serviceDockerID, ushort serviceType, ulong serviceID, string serviceName, uint clientDockerID, uint clientSessionID) 
        { 
            this.serviceDockerID = serviceDockerID; 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.serviceName = serviceName; 
            this.clientDockerID = clientDockerID; 
            this.clientSessionID = clientSessionID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.serviceDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.serviceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.serviceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeServiceClient: Proto4z.IProtoObject //更改clientID  
    {     
        //proto id   
        public const ushort protoID = 2002;  
        static public ushort getProtoID() { return 2002; } 
        static public string getProtoName() { return "ChangeServiceClient"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public ChangeServiceClient()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public ChangeServiceClient(ushort serviceType, ulong serviceID, uint clientDockerID, uint clientSessionID) 
        { 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.clientDockerID = clientDockerID; 
            this.clientSessionID = clientSessionID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.serviceType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DestroyServiceInDocker: Proto4z.IProtoObject //销毁一个Service  
    {     
        //proto id   
        public const ushort protoID = 2004;  
        static public ushort getProtoID() { return 2004; } 
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
        public const ushort protoID = 2005;  
        static public ushort getProtoID() { return 2005; } 
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
 
    public class ForwardToService: Proto4z.IProtoObject //转发到其他docker上的Service  
    {     
        //proto id   
        public const ushort protoID = 2006;  
        static public ushort getProtoID() { return 2006; } 
        static public string getProtoName() { return "ForwardToService"; } 
        //members   
        public ForwardToService()  
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
 
    public class ForwardToRealClient: Proto4z.IProtoObject //转发给真正的client  
    {     
        //proto id   
        public const ushort protoID = 2007;  
        static public ushort getProtoID() { return 2007; } 
        static public string getProtoName() { return "ForwardToRealClient"; } 
        //members   
        public ForwardToRealClient()  
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
 
 
