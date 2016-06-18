 
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
 
    public class SessionPulse: Proto4z.IProtoObject //对于建立了UserService的客户端,通过该消息驱动onTick  
    {     
        //proto id   
        public const ushort protoID = 2014;  
        static public ushort getProtoID() { return 2014; } 
        static public string getProtoName() { return "SessionPulse"; } 
        //members   
        public ulong serviceID;  
        public SessionPulse()  
        { 
            serviceID = 0;  
        } 
        public SessionPulse(ulong serviceID) 
        { 
            this.serviceID = serviceID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LoadServiceInDocker: Proto4z.IProtoObject //在Docker中装载一个Service  
    {     
        //proto id   
        public const ushort protoID = 2001;  
        static public ushort getProtoID() { return 2001; } 
        static public string getProtoName() { return "LoadServiceInDocker"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public LoadServiceInDocker()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public LoadServiceInDocker(ushort serviceType, ulong serviceID, string serviceName, uint clientDockerID, uint clientSessionID) 
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
 
    public class LoadServiceNotice: Proto4z.IProtoObject //通知其他Docker有Service已装载  
    {     
        //proto id   
        public const ushort protoID = 2002;  
        static public ushort getProtoID() { return 2002; } 
        static public string getProtoName() { return "LoadServiceNotice"; } 
        //members   
        public uint serviceDockerID;  
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public ushort status;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public LoadServiceNotice()  
        { 
            serviceDockerID = 0;  
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            status = 0;  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public LoadServiceNotice(uint serviceDockerID, ushort serviceType, ulong serviceID, string serviceName, ushort status, uint clientDockerID, uint clientSessionID) 
        { 
            this.serviceDockerID = serviceDockerID; 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.serviceName = serviceName; 
            this.status = status; 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
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
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RefreshServiceToMgrNotice: Proto4z.IProtoObject //Multi-Servie发生状态变化时候通知给管理器  
    {     
        //proto id   
        public const ushort protoID = 2003;  
        static public ushort getProtoID() { return 2003; } 
        static public string getProtoName() { return "RefreshServiceToMgrNotice"; } 
        //members   
        public uint serviceDockerID;  
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public ushort status;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public RefreshServiceToMgrNotice()  
        { 
            serviceDockerID = 0;  
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            status = 0;  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public RefreshServiceToMgrNotice(uint serviceDockerID, ushort serviceType, ulong serviceID, string serviceName, ushort status, uint clientDockerID, uint clientSessionID) 
        { 
            this.serviceDockerID = serviceDockerID; 
            this.serviceType = serviceType; 
            this.serviceID = serviceID; 
            this.serviceName = serviceName; 
            this.status = status; 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
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
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SwitchServiceClientNotice: Proto4z.IProtoObject //更改clientID  
    {     
        //proto id   
        public const ushort protoID = 2005;  
        static public ushort getProtoID() { return 2005; } 
        static public string getProtoName() { return "SwitchServiceClientNotice"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public SwitchServiceClientNotice()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public SwitchServiceClientNotice(ushort serviceType, ulong serviceID, uint clientDockerID, uint clientSessionID) 
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
 
    public class KickRealClient: Proto4z.IProtoObject //踢掉一个客户端  
    {     
        //proto id   
        public const ushort protoID = 2006;  
        static public ushort getProtoID() { return 2006; } 
        static public string getProtoName() { return "KickRealClient"; } 
        //members   
        public uint clientSessionID;  
        public KickRealClient()  
        { 
            clientSessionID = 0;  
        } 
        public KickRealClient(uint clientSessionID) 
        { 
            this.clientSessionID = clientSessionID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RealClientClosedNotice: Proto4z.IProtoObject //客户端离线通知  
    {     
        //proto id   
        public const ushort protoID = 2007;  
        static public ushort getProtoID() { return 2007; } 
        static public string getProtoName() { return "RealClientClosedNotice"; } 
        //members   
        public ulong serviceID;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public RealClientClosedNotice()  
        { 
            serviceID = 0;  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public RealClientClosedNotice(ulong serviceID, uint clientDockerID, uint clientSessionID) 
        { 
            this.serviceID = serviceID; 
            this.clientDockerID = clientDockerID; 
            this.clientSessionID = clientSessionID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.serviceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientDockerID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI32(this.clientSessionID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.serviceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clientDockerID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            this.clientSessionID = Proto4z.BaseProtoObject.decodeUI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UnloadServiceInDocker: Proto4z.IProtoObject //卸载一个Service  
    {     
        //proto id   
        public const ushort protoID = 2008;  
        static public ushort getProtoID() { return 2008; } 
        static public string getProtoName() { return "UnloadServiceInDocker"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public UnloadServiceInDocker()  
        { 
            serviceType = 0;  
            serviceID = 0;  
        } 
        public UnloadServiceInDocker(ushort serviceType, ulong serviceID) 
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
 
    public class UnloadedServiceNotice: Proto4z.IProtoObject //已卸载并完成销毁,广播给所有docker  
    {     
        //proto id   
        public const ushort protoID = 2009;  
        static public ushort getProtoID() { return 2009; } 
        static public string getProtoName() { return "UnloadedServiceNotice"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public UnloadedServiceNotice()  
        { 
            serviceType = 0;  
            serviceID = 0;  
        } 
        public UnloadedServiceNotice(ushort serviceType, ulong serviceID) 
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
 
    public class ShutdownClusterServer: Proto4z.IProtoObject //关闭服务器集群  
    {     
        //proto id   
        public const ushort protoID = 2010;  
        static public ushort getProtoID() { return 2010; } 
        static public string getProtoName() { return "ShutdownClusterServer"; } 
        //members   
        public ShutdownClusterServer()  
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
 
    public class ForwardToService: Proto4z.IProtoObject //转发到其他docker上的Service  
    {     
        //proto id   
        public const ushort protoID = 2011;  
        static public ushort getProtoID() { return 2011; } 
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
        public const ushort protoID = 2012;  
        static public ushort getProtoID() { return 2012; } 
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
 
 
