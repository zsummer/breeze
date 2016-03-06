 
#ifndef _PROTOCLUSTER_H_ 
#define _PROTOCLUSTER_H_ 
 
 
struct ClusterPulse //集群脉冲  
{ 
    static const unsigned short GetProtoID() { return 50000;} 
    static const std::string GetProtoName() { return "ID_ClusterPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterPulse & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterPulse & data) 
{ 
    return rs; 
} 
 
struct ClusterServiceInited //服务初始化成功  
{ 
    static const unsigned short GetProtoID() { return 50001;} 
    static const std::string GetProtoName() { return "ID_ClusterServiceInited";} 
    std::string entity;  
    ClusterServiceInited() 
    { 
    } 
    ClusterServiceInited(const std::string & entity) 
    { 
        this->entity = entity; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClusterServiceInited & data) 
{ 
    ws << data.entity;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClusterServiceInited & data) 
{ 
        rs >> data.entity;  
    return rs; 
} 
 
#endif 
