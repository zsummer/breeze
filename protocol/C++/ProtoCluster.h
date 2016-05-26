 
#ifndef _PROTOCLUSTER_H_ 
#define _PROTOCLUSTER_H_ 
 
 
struct ClusterPulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 40000;} 
    static const std::string getProtoName() { return "ID_ClusterPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterPulse & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterPulse & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterPulse & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateServiceInDocker //创建并初始化一个service  
{ 
    static const unsigned short getProtoID() { return 40013;} 
    static const std::string getProtoName() { return "ID_CreateServiceInDocker";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clusterID;  
    CreateServiceInDocker() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clusterID = 0; 
    } 
    CreateServiceInDocker(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clusterID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clusterID = clusterID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateServiceInDocker & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clusterID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateServiceInDocker & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clusterID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateServiceInDocker & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clusterID=" << info.clusterID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateServiceNotice //服务创建好并初始化成功,广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 40010;} 
    static const std::string getProtoName() { return "ID_CreateServiceNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clusterID;  
    CreateServiceNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clusterID = 0; 
    } 
    CreateServiceNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clusterID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clusterID = clusterID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateServiceNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clusterID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateServiceNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clusterID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateServiceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clusterID=" << info.clusterID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DestroyServiceInDocker //销毁一个Service  
{ 
    static const unsigned short getProtoID() { return 40014;} 
    static const std::string getProtoName() { return "ID_DestroyServiceInDocker";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    DestroyServiceInDocker() 
    { 
        serviceType = 0; 
        serviceID = 0; 
    } 
    DestroyServiceInDocker(const unsigned short & serviceType, const unsigned long long & serviceID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DestroyServiceInDocker & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DestroyServiceInDocker & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DestroyServiceInDocker & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DestroyServiceNotice //已卸载并完成销毁,广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 40012;} 
    static const std::string getProtoName() { return "ID_DestroyServiceNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    DestroyServiceNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
    } 
    DestroyServiceNotice(const unsigned short & serviceType, const unsigned long long & serviceID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DestroyServiceNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DestroyServiceNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DestroyServiceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClusterShellForward //壳子转发  
{ 
    static const unsigned short getProtoID() { return 40002;} 
    static const std::string getProtoName() { return "ID_ClusterShellForward";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterShellForward & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterShellForward & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterShellForward & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClusterClientForward //client转发  
{ 
    static const unsigned short getProtoID() { return 40003;} 
    static const std::string getProtoName() { return "ID_ClusterClientForward";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterClientForward & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterClientForward & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterClientForward & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
