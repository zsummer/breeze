 
#ifndef _PROTODOCKER_H_ 
#define _PROTODOCKER_H_ 
 
 
struct DockerKnock 
{ 
    static const unsigned short getProtoID() { return 2026;} 
    static const std::string getProtoName() { return "DockerKnock";} 
    unsigned long long areaID;  
    unsigned long long dockerID;  
    DockerKnock() 
    { 
        areaID = 0; 
        dockerID = 0; 
    } 
    DockerKnock(const unsigned long long & areaID, const unsigned long long & dockerID) 
    { 
        this->areaID = areaID; 
        this->dockerID = dockerID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DockerKnock & data) 
{ 
    ws << data.areaID;  
    ws << data.dockerID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DockerKnock & data) 
{ 
    rs >> data.areaID;  
    rs >> data.dockerID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DockerKnock & info) 
{ 
    stm << "[\n"; 
    stm << "areaID=" << info.areaID << "\n"; 
    stm << "dockerID=" << info.dockerID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DockerPulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 2027;} 
    static const std::string getProtoName() { return "DockerPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DockerPulse & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DockerPulse & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DockerPulse & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LoadService //在Docker中装载一个Service  
{ 
    static const unsigned short getProtoID() { return 2028;} 
    static const std::string getProtoName() { return "LoadService";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned long long clientDockerID;  
    unsigned long long clientSessionID;  
    LoadService() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    LoadService(const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned long long & clientDockerID, const unsigned long long & clientSessionID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->serviceName = serviceName; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoadService & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.serviceName;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoadService & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.serviceName;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LoadService & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "serviceName=" << info.serviceName << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ServiceInfo //Service被装载或者属性更改,需要通知给其他Docker的信息  
{ 
    static const unsigned short getProtoID() { return 2029;} 
    static const std::string getProtoName() { return "ServiceInfo";} 
    unsigned long long serviceDockerID;  
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned short status;  
    unsigned long long clientDockerID;  
    unsigned long long clientSessionID;  
    ServiceInfo() 
    { 
        serviceDockerID = 0; 
        serviceType = 0; 
        serviceID = 0; 
        status = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    ServiceInfo(const unsigned long long & serviceDockerID, const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned short & status, const unsigned long long & clientDockerID, const unsigned long long & clientSessionID) 
    { 
        this->serviceDockerID = serviceDockerID; 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->serviceName = serviceName; 
        this->status = status; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ServiceInfo & data) 
{ 
    ws << data.serviceDockerID;  
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.serviceName;  
    ws << data.status;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ServiceInfo & data) 
{ 
    rs >> data.serviceDockerID;  
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.serviceName;  
    rs >> data.status;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ServiceInfo & info) 
{ 
    stm << "[\n"; 
    stm << "serviceDockerID=" << info.serviceDockerID << "\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "serviceName=" << info.serviceName << "\n"; 
    stm << "status=" << info.status << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<ServiceInfo> ServiceInfoArray;  
 
struct LoadServiceNotice //通知其他Docker有Service已装载  
{ 
    static const unsigned short getProtoID() { return 2030;} 
    static const std::string getProtoName() { return "LoadServiceNotice";} 
    ServiceInfoArray shellServiceInfos;  
    LoadServiceNotice() 
    { 
    } 
    LoadServiceNotice(const ServiceInfoArray & shellServiceInfos) 
    { 
        this->shellServiceInfos = shellServiceInfos; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoadServiceNotice & data) 
{ 
    ws << data.shellServiceInfos;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoadServiceNotice & data) 
{ 
    rs >> data.shellServiceInfos;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LoadServiceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "shellServiceInfos=" << info.shellServiceInfos << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RefreshServiceToMgrNotice //Multi-Servie发生状态变化时候通知给管理器  
{ 
    static const unsigned short getProtoID() { return 2031;} 
    static const std::string getProtoName() { return "RefreshServiceToMgrNotice";} 
    ServiceInfoArray shellServiceInfos;  
    RefreshServiceToMgrNotice() 
    { 
    } 
    RefreshServiceToMgrNotice(const ServiceInfoArray & shellServiceInfos) 
    { 
        this->shellServiceInfos = shellServiceInfos; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshServiceToMgrNotice & data) 
{ 
    ws << data.shellServiceInfos;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshServiceToMgrNotice & data) 
{ 
    rs >> data.shellServiceInfos;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshServiceToMgrNotice & info) 
{ 
    stm << "[\n"; 
    stm << "shellServiceInfos=" << info.shellServiceInfos << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SwitchServiceClientNotice //更改clientID  
{ 
    static const unsigned short getProtoID() { return 2032;} 
    static const std::string getProtoName() { return "SwitchServiceClientNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned long long clientDockerID;  
    unsigned long long clientSessionID;  
    SwitchServiceClientNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    SwitchServiceClientNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned long long & clientDockerID, const unsigned long long & clientSessionID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SwitchServiceClientNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SwitchServiceClientNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SwitchServiceClientNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct KickRealClient //踢掉一个客户端  
{ 
    static const unsigned short getProtoID() { return 2033;} 
    static const std::string getProtoName() { return "KickRealClient";} 
    unsigned long long clientSessionID;  
    KickRealClient() 
    { 
        clientSessionID = 0; 
    } 
    KickRealClient(const unsigned long long & clientSessionID) 
    { 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const KickRealClient & data) 
{ 
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, KickRealClient & data) 
{ 
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const KickRealClient & info) 
{ 
    stm << "[\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RealClientClosedNotice //客户端离线通知  
{ 
    static const unsigned short getProtoID() { return 2034;} 
    static const std::string getProtoName() { return "RealClientClosedNotice";} 
    unsigned long long serviceID;  
    unsigned long long clientDockerID;  
    unsigned long long clientSessionID;  
    RealClientClosedNotice() 
    { 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    RealClientClosedNotice(const unsigned long long & serviceID, const unsigned long long & clientDockerID, const unsigned long long & clientSessionID) 
    { 
        this->serviceID = serviceID; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RealClientClosedNotice & data) 
{ 
    ws << data.serviceID;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RealClientClosedNotice & data) 
{ 
    rs >> data.serviceID;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RealClientClosedNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UnloadServiceInDocker //卸载一个Service  
{ 
    static const unsigned short getProtoID() { return 2035;} 
    static const std::string getProtoName() { return "UnloadServiceInDocker";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    UnloadServiceInDocker() 
    { 
        serviceType = 0; 
        serviceID = 0; 
    } 
    UnloadServiceInDocker(const unsigned short & serviceType, const unsigned long long & serviceID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UnloadServiceInDocker & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UnloadServiceInDocker & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UnloadServiceInDocker & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UnloadedServiceNotice //已卸载并完成销毁,广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 2036;} 
    static const std::string getProtoName() { return "UnloadedServiceNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    UnloadedServiceNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
    } 
    UnloadedServiceNotice(const unsigned short & serviceType, const unsigned long long & serviceID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UnloadedServiceNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UnloadedServiceNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UnloadedServiceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ShutdownClusterServer //关闭服务器集群  
{ 
    static const unsigned short getProtoID() { return 2037;} 
    static const std::string getProtoName() { return "ShutdownClusterServer";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ShutdownClusterServer & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ShutdownClusterServer & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ShutdownClusterServer & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ForwardToService //转发到其他docker上的Service  
{ 
    static const unsigned short getProtoID() { return 2038;} 
    static const std::string getProtoName() { return "ForwardToService";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ForwardToService & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ForwardToService & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ForwardToService & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ForwardToRealClient //转发给真正的client  
{ 
    static const unsigned short getProtoID() { return 2039;} 
    static const std::string getProtoName() { return "ForwardToRealClient";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ForwardToRealClient & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ForwardToRealClient & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ForwardToRealClient & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ForwardToDocker //转发给Docker  
{ 
    static const unsigned short getProtoID() { return 2040;} 
    static const std::string getProtoName() { return "ForwardToDocker";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ForwardToDocker & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ForwardToDocker & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ForwardToDocker & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<std::string> DBStringArray;  
 
struct DBDataResult 
{ 
    static const unsigned short getProtoID() { return 2041;} 
    static const std::string getProtoName() { return "DBDataResult";} 
    unsigned short qc;  
    std::string errMsg;  
    std::string sql;  
    unsigned long long affected;  
    DBStringArray fields;  
    DBDataResult() 
    { 
        qc = 0; 
        affected = 0; 
    } 
    DBDataResult(const unsigned short & qc, const std::string & errMsg, const std::string & sql, const unsigned long long & affected, const DBStringArray & fields) 
    { 
        this->qc = qc; 
        this->errMsg = errMsg; 
        this->sql = sql; 
        this->affected = affected; 
        this->fields = fields; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBDataResult & data) 
{ 
    ws << data.qc;  
    ws << data.errMsg;  
    ws << data.sql;  
    ws << data.affected;  
    ws << data.fields;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBDataResult & data) 
{ 
    rs >> data.qc;  
    rs >> data.errMsg;  
    rs >> data.sql;  
    rs >> data.affected;  
    rs >> data.fields;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBDataResult & info) 
{ 
    stm << "[\n"; 
    stm << "qc=" << info.qc << "\n"; 
    stm << "errMsg=" << info.errMsg << "\n"; 
    stm << "sql=" << info.sql << "\n"; 
    stm << "affected=" << info.affected << "\n"; 
    stm << "fields=" << info.fields << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<DBDataResult> DBDataResultArray;  
 
struct DBQueryReq //通用SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 2042;} 
    static const std::string getProtoName() { return "DBQueryReq";} 
    std::string sql;  
    DBQueryReq() 
    { 
    } 
    DBQueryReq(const std::string & sql) 
    { 
        this->sql = sql; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryReq & data) 
{ 
    ws << data.sql;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryReq & data) 
{ 
    rs >> data.sql;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryReq & info) 
{ 
    stm << "[\n"; 
    stm << "sql=" << info.sql << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DBQueryResp //通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult  
{ 
    static const unsigned short getProtoID() { return 2043;} 
    static const std::string getProtoName() { return "DBQueryResp";} 
    unsigned short retCode;  
    DBDataResult result;  
    DBQueryResp() 
    { 
        retCode = 0; 
    } 
    DBQueryResp(const unsigned short & retCode, const DBDataResult & result) 
    { 
        this->retCode = retCode; 
        this->result = result; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryResp & data) 
{ 
    ws << data.retCode;  
    ws << data.result;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.result;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "result=" << info.result << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DBQueryArrayReq //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 2044;} 
    static const std::string getProtoName() { return "DBQueryArrayReq";} 
    DBStringArray sqls;  
    DBQueryArrayReq() 
    { 
    } 
    DBQueryArrayReq(const DBStringArray & sqls) 
    { 
        this->sqls = sqls; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryArrayReq & data) 
{ 
    ws << data.sqls;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryArrayReq & data) 
{ 
    rs >> data.sqls;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryArrayReq & info) 
{ 
    stm << "[\n"; 
    stm << "sqls=" << info.sqls << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DBQueryArrayResp //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 2045;} 
    static const std::string getProtoName() { return "DBQueryArrayResp";} 
    unsigned short retCode;  
    DBDataResultArray results; //批量返回,注意不要超出协议包最大长度  
    DBQueryArrayResp() 
    { 
        retCode = 0; 
    } 
    DBQueryArrayResp(const unsigned short & retCode, const DBDataResultArray & results) 
    { 
        this->retCode = retCode; 
        this->results = results; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryArrayResp & data) 
{ 
    ws << data.retCode;  
    ws << data.results;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryArrayResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.results;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryArrayResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "results=" << info.results << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::map<std::string, std::string> WebAgentHead;  
 
struct WebAgentClientRequestAPI 
{ 
    static const unsigned short getProtoID() { return 2046;} 
    static const std::string getProtoName() { return "WebAgentClientRequestAPI";} 
    std::string method;  
    std::string methodLine;  
    WebAgentHead heads;  
    std::string body;  
    WebAgentClientRequestAPI() 
    { 
    } 
    WebAgentClientRequestAPI(const std::string & method, const std::string & methodLine, const WebAgentHead & heads, const std::string & body) 
    { 
        this->method = method; 
        this->methodLine = methodLine; 
        this->heads = heads; 
        this->body = body; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebAgentClientRequestAPI & data) 
{ 
    ws << data.method;  
    ws << data.methodLine;  
    ws << data.heads;  
    ws << data.body;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebAgentClientRequestAPI & data) 
{ 
    rs >> data.method;  
    rs >> data.methodLine;  
    rs >> data.heads;  
    rs >> data.body;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebAgentClientRequestAPI & info) 
{ 
    stm << "[\n"; 
    stm << "method=" << info.method << "\n"; 
    stm << "methodLine=" << info.methodLine << "\n"; 
    stm << "heads=" << info.heads << "\n"; 
    stm << "body=" << info.body << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WebServerRequest 
{ 
    static const unsigned short getProtoID() { return 2047;} 
    static const std::string getProtoName() { return "WebServerRequest";} 
    unsigned long long fromServiceType;  
    unsigned long long fromServiceID;  
    unsigned long long traceID;  
    std::string ip;  
    unsigned short port;  
    std::string host;  
    std::string uri;  
    std::string webparams;  
    WebAgentHead heads;  
    unsigned char isGet; //get or post  
    WebServerRequest() 
    { 
        fromServiceType = 0; 
        fromServiceID = 0; 
        traceID = 0; 
        port = 0; 
        isGet = 0; 
    } 
    WebServerRequest(const unsigned long long & fromServiceType, const unsigned long long & fromServiceID, const unsigned long long & traceID, const std::string & ip, const unsigned short & port, const std::string & host, const std::string & uri, const std::string & webparams, const WebAgentHead & heads, const unsigned char & isGet) 
    { 
        this->fromServiceType = fromServiceType; 
        this->fromServiceID = fromServiceID; 
        this->traceID = traceID; 
        this->ip = ip; 
        this->port = port; 
        this->host = host; 
        this->uri = uri; 
        this->webparams = webparams; 
        this->heads = heads; 
        this->isGet = isGet; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebServerRequest & data) 
{ 
    ws << data.fromServiceType;  
    ws << data.fromServiceID;  
    ws << data.traceID;  
    ws << data.ip;  
    ws << data.port;  
    ws << data.host;  
    ws << data.uri;  
    ws << data.webparams;  
    ws << data.heads;  
    ws << data.isGet;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebServerRequest & data) 
{ 
    rs >> data.fromServiceType;  
    rs >> data.fromServiceID;  
    rs >> data.traceID;  
    rs >> data.ip;  
    rs >> data.port;  
    rs >> data.host;  
    rs >> data.uri;  
    rs >> data.webparams;  
    rs >> data.heads;  
    rs >> data.isGet;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebServerRequest & info) 
{ 
    stm << "[\n"; 
    stm << "fromServiceType=" << info.fromServiceType << "\n"; 
    stm << "fromServiceID=" << info.fromServiceID << "\n"; 
    stm << "traceID=" << info.traceID << "\n"; 
    stm << "ip=" << info.ip << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "uri=" << info.uri << "\n"; 
    stm << "webparams=" << info.webparams << "\n"; 
    stm << "heads=" << info.heads << "\n"; 
    stm << "isGet=" << info.isGet << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WebServerResponse 
{ 
    static const unsigned short getProtoID() { return 2048;} 
    static const std::string getProtoName() { return "WebServerResponse";} 
    std::string method;  
    std::string methodLine;  
    WebAgentHead heads;  
    std::string body;  
    WebServerResponse() 
    { 
    } 
    WebServerResponse(const std::string & method, const std::string & methodLine, const WebAgentHead & heads, const std::string & body) 
    { 
        this->method = method; 
        this->methodLine = methodLine; 
        this->heads = heads; 
        this->body = body; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebServerResponse & data) 
{ 
    ws << data.method;  
    ws << data.methodLine;  
    ws << data.heads;  
    ws << data.body;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebServerResponse & data) 
{ 
    rs >> data.method;  
    rs >> data.methodLine;  
    rs >> data.heads;  
    rs >> data.body;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebServerResponse & info) 
{ 
    stm << "[\n"; 
    stm << "method=" << info.method << "\n"; 
    stm << "methodLine=" << info.methodLine << "\n"; 
    stm << "heads=" << info.heads << "\n"; 
    stm << "body=" << info.body << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AvatarOffline 
{ 
    static const unsigned short getProtoID() { return 2049;} 
    static const std::string getProtoName() { return "AvatarOffline";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long avatarID;  
    std::string streamBlob;  
    unsigned short status;  
    unsigned long long timestamp;  
    AvatarOffline() 
    { 
        id = 0; 
        avatarID = 0; 
        status = 0; 
        timestamp = 0; 
    } 
    AvatarOffline(const unsigned long long & id, const unsigned long long & avatarID, const std::string & streamBlob, const unsigned short & status, const unsigned long long & timestamp) 
    { 
        this->id = id; 
        this->avatarID = avatarID; 
        this->streamBlob = streamBlob; 
        this->status = status; 
        this->timestamp = timestamp; 
    } 
}; 
 
const std::vector<std::string>  AvatarOffline::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_AvatarOffline` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `streamBlob` longblob NOT NULL ,        `status` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `timestamp` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`),        KEY `avatarID` (`avatarID`),        KEY `status` (`status`),        KEY `timestamp` (`timestamp`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_AvatarOffline` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` add `streamBlob`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_AvatarOffline` change `streamBlob`  `streamBlob`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_AvatarOffline` add `status`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` change `status`  `status`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` add `timestamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarOffline` change `timestamp`  `timestamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  AvatarOffline::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`avatarID`,`streamBlob`,`status`,`timestamp` from `tb_AvatarOffline` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  AvatarOffline::getDBSelectPure() 
{ 
    return "select `id`,`avatarID`,`streamBlob`,`status`,`timestamp` from `tb_AvatarOffline` "; 
} 
std::string  AvatarOffline::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarOffline`(`id`,`avatarID`,`streamBlob`,`status`,`timestamp`) values(?,?,?,?,?)"); 
    q << this->id; 
    q << this->avatarID; 
    q << this->streamBlob; 
    q << this->status; 
    q << this->timestamp; 
    return q.pickSQL(); 
} 
std::string  AvatarOffline::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_AvatarOffline` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  AvatarOffline::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarOffline`(id) values(? ) on duplicate key update `avatarID` = ?,`streamBlob` = ?,`status` = ?,`timestamp` = ? "); 
    q << this->id; 
    q << this->avatarID; 
    q << this->streamBlob; 
    q << this->status; 
    q << this->timestamp; 
    return q.pickSQL(); 
} 
bool AvatarOffline::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch AvatarOffline from table `tb_AvatarOffline` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->avatarID; 
            result >> this->streamBlob; 
            result >> this->status; 
            result >> this->timestamp; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch AvatarOffline from table `tb_AvatarOffline` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AvatarOffline & data) 
{ 
    ws << data.id;  
    ws << data.avatarID;  
    ws << data.streamBlob;  
    ws << data.status;  
    ws << data.timestamp;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AvatarOffline & data) 
{ 
    rs >> data.id;  
    rs >> data.avatarID;  
    rs >> data.streamBlob;  
    rs >> data.status;  
    rs >> data.timestamp;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AvatarOffline & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "streamBlob=" << info.streamBlob << "\n"; 
    stm << "status=" << info.status << "\n"; 
    stm << "timestamp=" << info.timestamp << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
