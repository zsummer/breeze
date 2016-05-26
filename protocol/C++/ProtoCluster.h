 
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
 
struct ClusterServiceCreate //创建并初始化一个service  
{ 
    static const unsigned short getProtoID() { return 40004;} 
    static const std::string getProtoName() { return "ID_ClusterServiceCreate";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clusterID;  
    ClusterServiceCreate() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clusterID = 0; 
    } 
    ClusterServiceCreate(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clusterID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clusterID = clusterID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterServiceCreate & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clusterID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterServiceCreate & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clusterID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterServiceCreate & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clusterID=" << info.clusterID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClusterServiceCreateNotice //服务创建好并初始化成功,广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 40006;} 
    static const std::string getProtoName() { return "ID_ClusterServiceCreateNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clusterID;  
    ClusterServiceCreateNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clusterID = 0; 
    } 
    ClusterServiceCreateNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clusterID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clusterID = clusterID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterServiceCreateNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clusterID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterServiceCreateNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clusterID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterServiceCreateNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clusterID=" << info.clusterID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClusterServiceDestroy //销毁一个Service  
{ 
    static const unsigned short getProtoID() { return 40007;} 
    static const std::string getProtoName() { return "ID_ClusterServiceDestroy";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clusterID;  
    ClusterServiceDestroy() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clusterID = 0; 
    } 
    ClusterServiceDestroy(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clusterID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clusterID = clusterID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterServiceDestroy & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clusterID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterServiceDestroy & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clusterID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterServiceDestroy & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clusterID=" << info.clusterID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClusterServiceDestroyNotice //已卸载并完成销毁,广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 40008;} 
    static const std::string getProtoName() { return "ID_ClusterServiceDestroyNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clusterID;  
    ClusterServiceDestroyNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clusterID = 0; 
    } 
    ClusterServiceDestroyNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clusterID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clusterID = clusterID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterServiceDestroyNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clusterID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterServiceDestroyNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clusterID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterServiceDestroyNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clusterID=" << info.clusterID << "\n"; 
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
