 
#ifndef _PROTODOCKER_H_ 
#define _PROTODOCKER_H_ 
 
 
struct DockerPulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 2000;} 
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
 
struct SessionPulse //对于建立了UserService的客户端,通过该消息驱动onTick  
{ 
    static const unsigned short getProtoID() { return 2001;} 
    static const std::string getProtoName() { return "SessionPulse";} 
    unsigned long long serviceID;  
    SessionPulse() 
    { 
        serviceID = 0; 
    } 
    SessionPulse(const unsigned long long & serviceID) 
    { 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SessionPulse & data) 
{ 
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SessionPulse & data) 
{ 
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SessionPulse & info) 
{ 
    stm << "[\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LoadServiceInDocker //在Docker中装载一个Service  
{ 
    static const unsigned short getProtoID() { return 2002;} 
    static const std::string getProtoName() { return "LoadServiceInDocker";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    LoadServiceInDocker() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    LoadServiceInDocker(const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->serviceName = serviceName; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoadServiceInDocker & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.serviceName;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoadServiceInDocker & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.serviceName;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LoadServiceInDocker & info) 
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
 
struct LoadServiceNotice //通知其他Docker有Service已装载  
{ 
    static const unsigned short getProtoID() { return 2003;} 
    static const std::string getProtoName() { return "LoadServiceNotice";} 
    unsigned int serviceDockerID;  
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned short status;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    LoadServiceNotice() 
    { 
        serviceDockerID = 0; 
        serviceType = 0; 
        serviceID = 0; 
        status = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    LoadServiceNotice(const unsigned int & serviceDockerID, const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned short & status, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoadServiceNotice & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoadServiceNotice & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LoadServiceNotice & info) 
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
 
struct RefreshServiceToMgrNotice //Multi-Servie发生状态变化时候通知给管理器  
{ 
    static const unsigned short getProtoID() { return 2004;} 
    static const std::string getProtoName() { return "RefreshServiceToMgrNotice";} 
    unsigned int serviceDockerID;  
    unsigned short serviceType;  
    unsigned long long serviceID;  
    std::string serviceName;  
    unsigned short status;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    RefreshServiceToMgrNotice() 
    { 
        serviceDockerID = 0; 
        serviceType = 0; 
        serviceID = 0; 
        status = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    RefreshServiceToMgrNotice(const unsigned int & serviceDockerID, const unsigned short & serviceType, const unsigned long long & serviceID, const std::string & serviceName, const unsigned short & status, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshServiceToMgrNotice & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshServiceToMgrNotice & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshServiceToMgrNotice & info) 
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
 
struct SwitchServiceClientNotice //更改clientID  
{ 
    static const unsigned short getProtoID() { return 2005;} 
    static const std::string getProtoName() { return "SwitchServiceClientNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    SwitchServiceClientNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    SwitchServiceClientNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
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
    static const unsigned short getProtoID() { return 2006;} 
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
    stm << "[\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RealClientClosedNotice //客户端离线通知  
{ 
    static const unsigned short getProtoID() { return 2007;} 
    static const std::string getProtoName() { return "RealClientClosedNotice";} 
    unsigned long long serviceID;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    RealClientClosedNotice() 
    { 
        serviceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    RealClientClosedNotice(const unsigned long long & serviceID, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
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
    static const unsigned short getProtoID() { return 2008;} 
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
    static const unsigned short getProtoID() { return 2009;} 
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
    static const unsigned short getProtoID() { return 2010;} 
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
    static const unsigned short getProtoID() { return 2011;} 
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
    static const unsigned short getProtoID() { return 2012;} 
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
 
#endif 
