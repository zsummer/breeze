 
namespace Proto4z  
{ 
 
    public class SelfBeingPulse: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 2000;  
        static public ushort getProtoID() { return 2000; } 
        static public string getProtoName() { return "SelfBeingPulse"; } 
        //members   
        public ulong areaID;  
        public ulong dockerID;  
        public SelfBeingPulse()  
        { 
            areaID = 0;  
            dockerID = 0;  
        } 
        public SelfBeingPulse(ulong areaID, ulong dockerID) 
        { 
            this.areaID = areaID; 
            this.dockerID = dockerID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.areaID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.dockerID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.areaID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dockerID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DockerPulse: Proto4z.IProtoObject //集群脉冲  
    {     
        //proto id   
        public const ushort protoID = 2001;  
        static public ushort getProtoID() { return 2001; } 
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
 
    public class LoadService: Proto4z.IProtoObject //在Docker中装载一个Service  
    {     
        //proto id   
        public const ushort protoID = 2002;  
        static public ushort getProtoID() { return 2002; } 
        static public string getProtoName() { return "LoadService"; } 
        //members   
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public LoadService()  
        { 
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public LoadService(ushort serviceType, ulong serviceID, string serviceName, uint clientDockerID, uint clientSessionID) 
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
 
    public class ServiceInfo: Proto4z.IProtoObject //Service被装载或者属性更改,需要通知给其他Docker的信息  
    {     
        //proto id   
        public const ushort protoID = 2003;  
        static public ushort getProtoID() { return 2003; } 
        static public string getProtoName() { return "ServiceInfo"; } 
        //members   
        public uint serviceDockerID;  
        public ushort serviceType;  
        public ulong serviceID;  
        public string serviceName;  
        public ushort status;  
        public uint clientDockerID;  
        public uint clientSessionID;  
        public ServiceInfo()  
        { 
            serviceDockerID = 0;  
            serviceType = 0;  
            serviceID = 0;  
            serviceName = "";  
            status = 0;  
            clientDockerID = 0;  
            clientSessionID = 0;  
        } 
        public ServiceInfo(uint serviceDockerID, ushort serviceType, ulong serviceID, string serviceName, ushort status, uint clientDockerID, uint clientSessionID) 
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
 
 
    public class ServiceInfoArray : System.Collections.Generic.List<ServiceInfo>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
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
                    var data = new ServiceInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class LoadServiceNotice: Proto4z.IProtoObject //通知其他Docker有Service已装载  
    {     
        //proto id   
        public const ushort protoID = 2004;  
        static public ushort getProtoID() { return 2004; } 
        static public string getProtoName() { return "LoadServiceNotice"; } 
        //members   
        public ServiceInfoArray shellServiceInfos;  
        public LoadServiceNotice()  
        { 
            shellServiceInfos = new ServiceInfoArray();  
        } 
        public LoadServiceNotice(ServiceInfoArray shellServiceInfos) 
        { 
            this.shellServiceInfos = shellServiceInfos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.shellServiceInfos == null) this.shellServiceInfos = new ServiceInfoArray(); 
            data.AddRange(this.shellServiceInfos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.shellServiceInfos = new ServiceInfoArray(); 
            this.shellServiceInfos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RefreshServiceToMgrNotice: Proto4z.IProtoObject //Multi-Servie发生状态变化时候通知给管理器  
    {     
        //proto id   
        public const ushort protoID = 2005;  
        static public ushort getProtoID() { return 2005; } 
        static public string getProtoName() { return "RefreshServiceToMgrNotice"; } 
        //members   
        public ServiceInfoArray shellServiceInfos;  
        public RefreshServiceToMgrNotice()  
        { 
            shellServiceInfos = new ServiceInfoArray();  
        } 
        public RefreshServiceToMgrNotice(ServiceInfoArray shellServiceInfos) 
        { 
            this.shellServiceInfos = shellServiceInfos; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.shellServiceInfos == null) this.shellServiceInfos = new ServiceInfoArray(); 
            data.AddRange(this.shellServiceInfos.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.shellServiceInfos = new ServiceInfoArray(); 
            this.shellServiceInfos.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SwitchServiceClientNotice: Proto4z.IProtoObject //更改clientID  
    {     
        //proto id   
        public const ushort protoID = 2006;  
        static public ushort getProtoID() { return 2006; } 
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
        public const ushort protoID = 2007;  
        static public ushort getProtoID() { return 2007; } 
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
        public const ushort protoID = 2008;  
        static public ushort getProtoID() { return 2008; } 
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
        public const ushort protoID = 2009;  
        static public ushort getProtoID() { return 2009; } 
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
        public const ushort protoID = 2010;  
        static public ushort getProtoID() { return 2010; } 
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
        public const ushort protoID = 2011;  
        static public ushort getProtoID() { return 2011; } 
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
        public const ushort protoID = 2012;  
        static public ushort getProtoID() { return 2012; } 
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
        public const ushort protoID = 2013;  
        static public ushort getProtoID() { return 2013; } 
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
 
    public class ForwardToDocker: Proto4z.IProtoObject //转发给Docker  
    {     
        //proto id   
        public const ushort protoID = 2014;  
        static public ushort getProtoID() { return 2014; } 
        static public string getProtoName() { return "ForwardToDocker"; } 
        //members   
        public ForwardToDocker()  
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
 
 
    public class DBStringArray : System.Collections.Generic.List<string>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(this[i]));  
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
                    this.Add(Proto4z.BaseProtoObject.decodeString(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DBDataResult: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 2015;  
        static public ushort getProtoID() { return 2015; } 
        static public string getProtoName() { return "DBDataResult"; } 
        //members   
        public ushort qc;  
        public string errMsg;  
        public string sql;  
        public ulong affected;  
        public DBStringArray fields;  
        public DBDataResult()  
        { 
            qc = 0;  
            errMsg = "";  
            sql = "";  
            affected = 0;  
            fields = new DBStringArray();  
        } 
        public DBDataResult(ushort qc, string errMsg, string sql, ulong affected, DBStringArray fields) 
        { 
            this.qc = qc; 
            this.errMsg = errMsg; 
            this.sql = sql; 
            this.affected = affected; 
            this.fields = fields; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.qc)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.errMsg)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sql)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.affected)); 
            if (this.fields == null) this.fields = new DBStringArray(); 
            data.AddRange(this.fields.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.qc = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.errMsg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.sql = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.affected = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fields = new DBStringArray(); 
            this.fields.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DBDataResultArray : System.Collections.Generic.List<DBDataResult>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
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
                    var data = new DBDataResult(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DBQueryReq: Proto4z.IProtoObject //通用SQL语句执行协议  
    {     
        //proto id   
        public const ushort protoID = 2016;  
        static public ushort getProtoID() { return 2016; } 
        static public string getProtoName() { return "DBQueryReq"; } 
        //members   
        public string sql;  
        public DBQueryReq()  
        { 
            sql = "";  
        } 
        public DBQueryReq(string sql) 
        { 
            this.sql = sql; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sql)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sql = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DBQueryResp: Proto4z.IProtoObject //通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult  
    {     
        //proto id   
        public const ushort protoID = 2017;  
        static public ushort getProtoID() { return 2017; } 
        static public string getProtoName() { return "DBQueryResp"; } 
        //members   
        public ushort retCode;  
        public DBDataResult result;  
        public DBQueryResp()  
        { 
            retCode = 0;  
            result = new DBDataResult();  
        } 
        public DBQueryResp(ushort retCode, DBDataResult result) 
        { 
            this.retCode = retCode; 
            this.result = result; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.result == null) this.result = new DBDataResult(); 
            data.AddRange(this.result.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.result = new DBDataResult(); 
            this.result.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DBQueryArrayReq: Proto4z.IProtoObject //通用批量SQL语句执行协议  
    {     
        //proto id   
        public const ushort protoID = 2018;  
        static public ushort getProtoID() { return 2018; } 
        static public string getProtoName() { return "DBQueryArrayReq"; } 
        //members   
        public DBStringArray sqls;  
        public DBQueryArrayReq()  
        { 
            sqls = new DBStringArray();  
        } 
        public DBQueryArrayReq(DBStringArray sqls) 
        { 
            this.sqls = sqls; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.sqls == null) this.sqls = new DBStringArray(); 
            data.AddRange(this.sqls.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sqls = new DBStringArray(); 
            this.sqls.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DBQueryArrayResp: Proto4z.IProtoObject //通用批量SQL语句执行协议  
    {     
        //proto id   
        public const ushort protoID = 2019;  
        static public ushort getProtoID() { return 2019; } 
        static public string getProtoName() { return "DBQueryArrayResp"; } 
        //members   
        public ushort retCode;  
        public DBDataResultArray results; //批量返回,注意不要超出协议包最大长度  
        public DBQueryArrayResp()  
        { 
            retCode = 0;  
            results = new DBDataResultArray();  
        } 
        public DBQueryArrayResp(ushort retCode, DBDataResultArray results) 
        { 
            this.retCode = retCode; 
            this.results = results; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.results == null) this.results = new DBDataResultArray(); 
            data.AddRange(this.results.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.results = new DBDataResultArray(); 
            this.results.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
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
        public const ushort protoID = 2020;  
        static public ushort getProtoID() { return 2020; } 
        static public string getProtoName() { return "WebAgentClientRequestAPI"; } 
        //members   
        public string method;  
        public string methodLine;  
        public WebAgentHead heads;  
        public string body;  
        public WebAgentClientRequestAPI()  
        { 
            method = "";  
            methodLine = "";  
            heads = new WebAgentHead();  
            body = "";  
        } 
        public WebAgentClientRequestAPI(string method, string methodLine, WebAgentHead heads, string body) 
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
 
    public class WebServerRequest: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 2021;  
        static public ushort getProtoID() { return 2021; } 
        static public string getProtoName() { return "WebServerRequest"; } 
        //members   
        public uint fromServiceType;  
        public ulong fromServiceID;  
        public uint traceID;  
        public string ip;  
        public ushort port;  
        public string host;  
        public string uri;  
        public string webparams;  
        public WebAgentHead heads;  
        public byte isGet; //get or post  
        public WebServerRequest()  
        { 
            fromServiceType = 0;  
            fromServiceID = 0;  
            traceID = 0;  
            ip = "";  
            port = 0;  
            host = "";  
            uri = "";  
            webparams = "";  
            heads = new WebAgentHead();  
            isGet = 0;  
        } 
        public WebServerRequest(uint fromServiceType, ulong fromServiceID, uint traceID, string ip, ushort port, string host, string uri, string webparams, WebAgentHead heads, byte isGet) 
        { 
            this.fromServiceType = fromServiceType; 
            this.fromServiceID = fromServiceID; 
            this.traceID = traceID; 
            this.ip = ip; 
            this.port = port; 
            this.host = host; 
            this.uri = uri; 
            this.webparams = webparams; 
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
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.uri)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.webparams)); 
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
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.uri = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.webparams = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.heads = new WebAgentHead(); 
            this.heads.__decode(binData, ref pos); 
            this.isGet = Proto4z.BaseProtoObject.decodeUI8(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class WebServerResponse: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 2022;  
        static public ushort getProtoID() { return 2022; } 
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
 
    public class AvatarOffline: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 2023;  
        static public ushort getProtoID() { return 2023; } 
        static public string getProtoName() { return "AvatarOffline"; } 
        //members   
        public ulong id;  
        public ulong avatarID;  
        public string streamBlob;  
        public ushort status;  
        public ulong timestamp;  
        public AvatarOffline()  
        { 
            id = 0;  
            avatarID = 0;  
            streamBlob = "";  
            status = 0;  
            timestamp = 0;  
        } 
        public AvatarOffline(ulong id, ulong avatarID, string streamBlob, ushort status, ulong timestamp) 
        { 
            this.id = id; 
            this.avatarID = avatarID; 
            this.streamBlob = streamBlob; 
            this.status = status; 
            this.timestamp = timestamp; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.id)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.streamBlob)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.status)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.timestamp)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.id = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.streamBlob = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.status = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.timestamp = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 
