 
#ifndef _PROTOSPACECLIENT_H_ 
#define _PROTOSPACECLIENT_H_ 
 
 
struct AttachSpaceReq 
{ 
    static const unsigned short getProtoID() { return 50013;} 
    static const std::string getProtoName() { return "AttachSpaceReq";} 
    unsigned long long userID;  
    unsigned int spaceID;  
    std::string token; //令牌  
    AttachSpaceReq() 
    { 
        userID = 0; 
        spaceID = 0; 
    } 
    AttachSpaceReq(const unsigned long long & userID, const unsigned int & spaceID, const std::string & token) 
    { 
        this->userID = userID; 
        this->spaceID = spaceID; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachSpaceReq & data) 
{ 
    ws << data.userID;  
    ws << data.spaceID;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachSpaceReq & data) 
{ 
    rs >> data.userID;  
    rs >> data.spaceID;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachSpaceReq & info) 
{ 
    stm << "[\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachSpaceResp 
{ 
    static const unsigned short getProtoID() { return 50014;} 
    static const std::string getProtoName() { return "AttachSpaceResp";} 
    unsigned short retCode; //错误码  
    unsigned long long userID;  
    unsigned int spaceID;  
    AttachSpaceResp() 
    { 
        retCode = 0; 
        userID = 0; 
        spaceID = 0; 
    } 
    AttachSpaceResp(const unsigned short & retCode, const unsigned long long & userID, const unsigned int & spaceID) 
    { 
        this->retCode = retCode; 
        this->userID = userID; 
        this->spaceID = spaceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachSpaceResp & data) 
{ 
    ws << data.retCode;  
    ws << data.userID;  
    ws << data.spaceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachSpaceResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.userID;  
    rs >> data.spaceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct FillSpaceNotice //填充场景数据  
{ 
    static const unsigned short getProtoID() { return 50009;} 
    static const std::string getProtoName() { return "FillSpaceNotice";} 
    EntityFullInfoArray entitys; //这里包含有所有当前场景下的实体属性和状态数据  
    double spaceStartTime; //服务器战场开始时间  
    double spaceEndTime; //服务器战场结束时间  
    double serverTime; //服务器当前时间  
    FillSpaceNotice() 
    { 
        spaceStartTime = 0.0; 
        spaceEndTime = 0.0; 
        serverTime = 0.0; 
    } 
    FillSpaceNotice(const EntityFullInfoArray & entitys, const double & spaceStartTime, const double & spaceEndTime, const double & serverTime) 
    { 
        this->entitys = entitys; 
        this->spaceStartTime = spaceStartTime; 
        this->spaceEndTime = spaceEndTime; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FillSpaceNotice & data) 
{ 
    ws << data.entitys;  
    ws << data.spaceStartTime;  
    ws << data.spaceEndTime;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FillSpaceNotice & data) 
{ 
    rs >> data.entitys;  
    rs >> data.spaceStartTime;  
    rs >> data.spaceEndTime;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FillSpaceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entitys=" << info.entitys << "\n"; 
    stm << "spaceStartTime=" << info.spaceStartTime << "\n"; 
    stm << "spaceEndTime=" << info.spaceEndTime << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RefreshSpaceEntitysNotice 
{ 
    static const unsigned short getProtoID() { return 50015;} 
    static const std::string getProtoName() { return "RefreshSpaceEntitysNotice";} 
    EntityInfoArray entitys;  
    double serverTime; //服务器当前时间  
    RefreshSpaceEntitysNotice() 
    { 
        serverTime = 0.0; 
    } 
    RefreshSpaceEntitysNotice(const EntityInfoArray & entitys, const double & serverTime) 
    { 
        this->entitys = entitys; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshSpaceEntitysNotice & data) 
{ 
    ws << data.entitys;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshSpaceEntitysNotice & data) 
{ 
    rs >> data.entitys;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshSpaceEntitysNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entitys=" << info.entitys << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RefreshSpaceReportsNotice 
{ 
    static const unsigned short getProtoID() { return 50016;} 
    static const std::string getProtoName() { return "RefreshSpaceReportsNotice";} 
    EntityReportArray reports;  
    double serverTime; //服务器当前时间  
    RefreshSpaceReportsNotice() 
    { 
        serverTime = 0.0; 
    } 
    RefreshSpaceReportsNotice(const EntityReportArray & reports, const double & serverTime) 
    { 
        this->reports = reports; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshSpaceReportsNotice & data) 
{ 
    ws << data.reports;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshSpaceReportsNotice & data) 
{ 
    rs >> data.reports;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshSpaceReportsNotice & info) 
{ 
    stm << "[\n"; 
    stm << "reports=" << info.reports << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AddEntityNotice //一批实体加入场景时, 把这些实体的数据广播给其他玩家  
{ 
    static const unsigned short getProtoID() { return 50011;} 
    static const std::string getProtoName() { return "AddEntityNotice";} 
    EntityFullInfoArray entitys;  
    double serverTime; //服务器当前时间  
    AddEntityNotice() 
    { 
        serverTime = 0.0; 
    } 
    AddEntityNotice(const EntityFullInfoArray & entitys, const double & serverTime) 
    { 
        this->entitys = entitys; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddEntityNotice & data) 
{ 
    ws << data.entitys;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddEntityNotice & data) 
{ 
    rs >> data.entitys;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AddEntityNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entitys=" << info.entitys << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RemoveEntityNotice //实体离开场景时, 把该实体的数据广播给其他玩家  
{ 
    static const unsigned short getProtoID() { return 50012;} 
    static const std::string getProtoName() { return "RemoveEntityNotice";} 
    EntityIDArray eids;  
    double serverTime; //服务器当前时间  
    RemoveEntityNotice() 
    { 
        serverTime = 0.0; 
    } 
    RemoveEntityNotice(const EntityIDArray & eids, const double & serverTime) 
    { 
        this->eids = eids; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RemoveEntityNotice & data) 
{ 
    ws << data.eids;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RemoveEntityNotice & data) 
{ 
    rs >> data.eids;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RemoveEntityNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eids=" << info.eids << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
