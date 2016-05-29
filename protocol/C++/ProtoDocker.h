 
#ifndef _PROTODOCKER_H_ 
#define _PROTODOCKER_H_ 
 
 
struct DockerPulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 40000;} 
    static const std::string getProtoName() { return "ID_DockerPulse";} 
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
 
struct CreateServiceInDocker //创建并初始化一个service  
{ 
    static const unsigned short getProtoID() { return 40001;} 
    static const std::string getProtoName() { return "ID_CreateServiceInDocker";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clientID;  
    CreateServiceInDocker() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientID = 0; 
    } 
    CreateServiceInDocker(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clientID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clientID = clientID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateServiceInDocker & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clientID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateServiceInDocker & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clientID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateServiceInDocker & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clientID=" << info.clientID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ChangeServiceClientID //更改clientID  
{ 
    static const unsigned short getProtoID() { return 40002;} 
    static const std::string getProtoName() { return "ID_ChangeServiceClientID";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int clientID;  
    ChangeServiceClientID() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        clientID = 0; 
    } 
    ChangeServiceClientID(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & clientID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->clientID = clientID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChangeServiceClientID & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.clientID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChangeServiceClientID & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.clientID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChangeServiceClientID & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "clientID=" << info.clientID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateOrRefreshServiceNotice //广播给所有docker  
{ 
    static const unsigned short getProtoID() { return 40003;} 
    static const std::string getProtoName() { return "ID_CreateOrRefreshServiceNotice";} 
    unsigned short serviceType;  
    unsigned long long serviceID;  
    unsigned int dockerID;  
    unsigned int clientID;  
    CreateOrRefreshServiceNotice() 
    { 
        serviceType = 0; 
        serviceID = 0; 
        dockerID = 0; 
        clientID = 0; 
    } 
    CreateOrRefreshServiceNotice(const unsigned short & serviceType, const unsigned long long & serviceID, const unsigned int & dockerID, const unsigned int & clientID) 
    { 
        this->serviceType = serviceType; 
        this->serviceID = serviceID; 
        this->dockerID = dockerID; 
        this->clientID = clientID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateOrRefreshServiceNotice & data) 
{ 
    ws << data.serviceType;  
    ws << data.serviceID;  
    ws << data.dockerID;  
    ws << data.clientID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateOrRefreshServiceNotice & data) 
{ 
    rs >> data.serviceType;  
    rs >> data.serviceID;  
    rs >> data.dockerID;  
    rs >> data.clientID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateOrRefreshServiceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "serviceType=" << info.serviceType << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "dockerID=" << info.dockerID << "\n"; 
    stm << "clientID=" << info.clientID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DestroyServiceInDocker //销毁一个Service  
{ 
    static const unsigned short getProtoID() { return 40004;} 
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
    static const unsigned short getProtoID() { return 40005;} 
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
 
struct ForwardToDocker //转发到其他docker  
{ 
    static const unsigned short getProtoID() { return 40006;} 
    static const std::string getProtoName() { return "ID_ForwardToDocker";} 
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
 
#endif 
