 
#ifndef _PROTODOCKER_H_ 
#define _PROTODOCKER_H_ 
 
 
struct DockerKnock 
{ 
    static const unsigned short getProtoID() { return 3000;} 
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
    stm << "["; 
    stm << "areaID=" << info.areaID << ","; 
    stm << "dockerID=" << info.dockerID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DockerPulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 3001;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct LoadService //在Docker中装载一个Service  
{ 
    static const unsigned short getProtoID() { return 3002;} 
    static const std::string getProtoName() { return "LoadService";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned long long clientDockerID;  
    unsigned int clientSessionID;  
    LoadService() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    LoadService(const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned long long & clientDockerID, const unsigned int & clientSessionID) 
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
    stm << "["; 
    stm << "serviceType=" << info.serviceType << ","; 
    stm << "serviceID=" << info.serviceID << ","; 
    stm << "serviceName=" << info.serviceName << ","; 
    stm << "clientDockerID=" << info.clientDockerID << ","; 
    stm << "clientSessionID=" << info.clientSessionID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ServiceInfo //Service被装载或者属性更改,需要通知给其他Docker的信息  
{ 
    static const unsigned short getProtoID() { return 3003;} 
    static const std::string getProtoName() { return "ServiceInfo";} 
    unsigned long long serviceDockerID;  
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned short status;  
    unsigned long long clientDockerID;  
    unsigned int clientSessionID;  
    ServiceInfo() 
    { 
        serviceDockerID = 0; 
        serviceType = 0; 
        serviceID = 0; 
        status = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    ServiceInfo(const unsigned long long & serviceDockerID, const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned short & status, const unsigned long long & clientDockerID, const unsigned int & clientSessionID) 
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
    stm << "["; 
    stm << "serviceDockerID=" << info.serviceDockerID << ","; 
    stm << "serviceType=" << info.serviceType << ","; 
    stm << "serviceID=" << info.serviceID << ","; 
    stm << "serviceName=" << info.serviceName << ","; 
    stm << "status=" << info.status << ","; 
    stm << "clientDockerID=" << info.clientDockerID << ","; 
    stm << "clientSessionID=" << info.clientSessionID << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<ServiceInfo> ServiceInfoArray;  
 
struct LoadServiceNotice //通知其他Docker有Service已装载  
{ 
    static const unsigned short getProtoID() { return 3004;} 
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
    stm << "["; 
    stm << "shellServiceInfos=" << info.shellServiceInfos << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct RefreshServiceToMgrNotice //Multi-Servie发生状态变化时候通知给管理器  
{ 
    static const unsigned short getProtoID() { return 3005;} 
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
    stm << "["; 
    stm << "shellServiceInfos=" << info.shellServiceInfos << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SwitchServiceClientNotice //更改clientID  
{ 
    static const unsigned short getProtoID() { return 3006;} 
    static const std::string getProtoName() { return "SwitchServiceClientNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned long long clientDockerID;  
    unsigned int clientSessionID;  
    SwitchServiceClientNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    SwitchServiceClientNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned long long & clientDockerID, const unsigned int & clientSessionID) 
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
    stm << "["; 
    stm << "serviceType=" << info.serviceType << ","; 
    stm << "serviceID=" << info.serviceID << ","; 
    stm << "clientDockerID=" << info.clientDockerID << ","; 
    stm << "clientSessionID=" << info.clientSessionID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct KickRealClient //踢掉一个客户端  
{ 
    static const unsigned short getProtoID() { return 3007;} 
    static const std::string getProtoName() { return "KickRealClient";} 
    unsigned int clientSessionID;  
    KickRealClient() 
    { 
        clientSessionID = 0; 
    } 
    KickRealClient(const unsigned int & clientSessionID) 
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
    stm << "["; 
    stm << "clientSessionID=" << info.clientSessionID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct RealClientClosedNotice //客户端离线通知  
{ 
    static const unsigned short getProtoID() { return 3008;} 
    static const std::string getProtoName() { return "RealClientClosedNotice";} 
    unsigned long long serviceID;  
    unsigned long long clientDockerID;  
    unsigned int clientSessionID;  
    RealClientClosedNotice() 
    { 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    RealClientClosedNotice(const unsigned long long & serviceID, const unsigned long long & clientDockerID, const unsigned int & clientSessionID) 
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
    stm << "["; 
    stm << "serviceID=" << info.serviceID << ","; 
    stm << "clientDockerID=" << info.clientDockerID << ","; 
    stm << "clientSessionID=" << info.clientSessionID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct UnloadServiceInDocker //卸载一个Service  
{ 
    static const unsigned short getProtoID() { return 3009;} 
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
    stm << "["; 
    stm << "serviceType=" << info.serviceType << ","; 
    stm << "serviceID=" << info.serviceID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct UnloadedServiceNotice //已卸载并完成销毁,广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 3010;} 
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
    stm << "["; 
    stm << "serviceType=" << info.serviceType << ","; 
    stm << "serviceID=" << info.serviceID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ShutdownClusterServer //关闭服务器集群  
{ 
    static const unsigned short getProtoID() { return 3011;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct ForwardToService //转发到其他docker上的Service  
{ 
    static const unsigned short getProtoID() { return 3012;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct ForwardToRealClient //转发给真正的client  
{ 
    static const unsigned short getProtoID() { return 3013;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct ForwardToDocker //转发给Docker  
{ 
    static const unsigned short getProtoID() { return 3014;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct ReloadDBDictNotice //重新加载字典文件  
{ 
    static const unsigned short getProtoID() { return 3015;} 
    static const std::string getProtoName() { return "ReloadDBDictNotice";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ReloadDBDictNotice & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ReloadDBDictNotice & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ReloadDBDictNotice & info) 
{ 
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct ReloadDBDictFinish //重新加载字典文件  
{ 
    static const unsigned short getProtoID() { return 3016;} 
    static const std::string getProtoName() { return "ReloadDBDictFinish";} 
    unsigned long long dockerID;  
    double activeTime;  
    double used;  
    ReloadDBDictFinish() 
    { 
        dockerID = 0; 
        activeTime = 0.0; 
        used = 0.0; 
    } 
    ReloadDBDictFinish(const unsigned long long & dockerID, const double & activeTime, const double & used) 
    { 
        this->dockerID = dockerID; 
        this->activeTime = activeTime; 
        this->used = used; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ReloadDBDictFinish & data) 
{ 
    ws << data.dockerID;  
    ws << data.activeTime;  
    ws << data.used;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ReloadDBDictFinish & data) 
{ 
    rs >> data.dockerID;  
    rs >> data.activeTime;  
    rs >> data.used;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ReloadDBDictFinish & info) 
{ 
    stm << "["; 
    stm << "dockerID=" << info.dockerID << ","; 
    stm << "activeTime=" << info.activeTime << ","; 
    stm << "used=" << info.used << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct KickClientsNotice //踢人  
{ 
    static const unsigned short getProtoID() { return 3017;} 
    static const std::string getProtoName() { return "KickClientsNotice";} 
    unsigned short isAll;  
    ServiceIDArray avatars; //指定avatar  
    AccountArray accounts; //指定account  
    unsigned long long forbidDuration; //限制登录的持续时间(关服前有效 不记录到数据库)  
    KickClientsNotice() 
    { 
        isAll = 0; 
        forbidDuration = 0; 
    } 
    KickClientsNotice(const unsigned short & isAll, const ServiceIDArray & avatars, const AccountArray & accounts, const unsigned long long & forbidDuration) 
    { 
        this->isAll = isAll; 
        this->avatars = avatars; 
        this->accounts = accounts; 
        this->forbidDuration = forbidDuration; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const KickClientsNotice & data) 
{ 
    ws << data.isAll;  
    ws << data.avatars;  
    ws << data.accounts;  
    ws << data.forbidDuration;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, KickClientsNotice & data) 
{ 
    rs >> data.isAll;  
    rs >> data.avatars;  
    rs >> data.accounts;  
    rs >> data.forbidDuration;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const KickClientsNotice & info) 
{ 
    stm << "["; 
    stm << "isAll=" << info.isAll << ","; 
    stm << "avatars=" << info.avatars << ","; 
    stm << "accounts=" << info.accounts << ","; 
    stm << "forbidDuration=" << info.forbidDuration << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<std::string> DBStringArray;  
 
struct DBDataResult 
{ 
    static const unsigned short getProtoID() { return 3018;} 
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
    stm << "["; 
    stm << "qc=" << info.qc << ","; 
    stm << "errMsg=" << info.errMsg << ","; 
    stm << "sql=" << info.sql << ","; 
    stm << "affected=" << info.affected << ","; 
    stm << "fields=" << info.fields << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DBDataResult> DBDataResultArray;  
 
struct DBQueryReq //通用SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 3019;} 
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
    stm << "["; 
    stm << "sql=" << info.sql << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DBQueryResp //通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult  
{ 
    static const unsigned short getProtoID() { return 3020;} 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "result=" << info.result << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DBQueryArrayReq //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 3021;} 
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
    stm << "["; 
    stm << "sqls=" << info.sqls << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DBQueryArrayResp //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 3022;} 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "results=" << info.results << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::map<std::string, std::string> WebAgentHead;  
 
struct WebAgentClientRequestAPI 
{ 
    static const unsigned short getProtoID() { return 3023;} 
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
    stm << "["; 
    stm << "method=" << info.method << ","; 
    stm << "methodLine=" << info.methodLine << ","; 
    stm << "heads=" << info.heads << ","; 
    stm << "body=" << info.body << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct WebServerRequest 
{ 
    static const unsigned short getProtoID() { return 3024;} 
    static const std::string getProtoName() { return "WebServerRequest";} 
    unsigned short fromServiceType;  
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
    WebServerRequest(const unsigned short & fromServiceType, const unsigned long long & fromServiceID, const unsigned long long & traceID, const std::string & ip, const unsigned short & port, const std::string & host, const std::string & uri, const std::string & webparams, const WebAgentHead & heads, const unsigned char & isGet) 
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
    stm << "["; 
    stm << "fromServiceType=" << info.fromServiceType << ","; 
    stm << "fromServiceID=" << info.fromServiceID << ","; 
    stm << "traceID=" << info.traceID << ","; 
    stm << "ip=" << info.ip << ","; 
    stm << "port=" << info.port << ","; 
    stm << "host=" << info.host << ","; 
    stm << "uri=" << info.uri << ","; 
    stm << "webparams=" << info.webparams << ","; 
    stm << "heads=" << info.heads << ","; 
    stm << "isGet=" << info.isGet << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct WebServerResponse 
{ 
    static const unsigned short getProtoID() { return 3025;} 
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
    stm << "["; 
    stm << "method=" << info.method << ","; 
    stm << "methodLine=" << info.methodLine << ","; 
    stm << "heads=" << info.heads << ","; 
    stm << "body=" << info.body << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct AvatarOffline 
{ 
    static const unsigned short getProtoID() { return 3026;} 
    static const std::string getProtoName() { return "AvatarOffline";} 
    inline std::vector<std::string>  getDBBuild(); 
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
 
std::vector<std::string>  AvatarOffline::getDBBuild() 
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
    return ret; 
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
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "streamBlob=" << info.streamBlob << ","; 
    stm << "status=" << info.status << ","; 
    stm << "timestamp=" << info.timestamp << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 
