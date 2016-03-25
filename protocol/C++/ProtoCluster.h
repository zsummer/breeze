 
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
 
struct ClusterServiceInited //服务初始化成功  
{ 
    static const unsigned short getProtoID() { return 40001;} 
    static const std::string getProtoName() { return "ID_ClusterServiceInited";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    ClusterServiceInited() 
    { 
        serviceType = 0; 
        serviceID = 0; 
    } 
    ClusterServiceInited(const unsigned short & serviceType, const unsigned long long & serviceID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterServiceInited & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterServiceInited & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClusterServiceInited & info) 
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
