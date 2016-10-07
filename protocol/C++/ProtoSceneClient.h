 
#ifndef _PROTOSCENECLIENT_H_ 
#define _PROTOSCENECLIENT_H_ 
 
 
struct SceneClientPulse //客户端脉冲请求  
{ 
    static const unsigned short getProtoID() { return 50000;} 
    static const std::string getProtoName() { return "SceneClientPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneClientPulse & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneClientPulse & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneClientPulse & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachSceneReq 
{ 
    static const unsigned short getProtoID() { return 50001;} 
    static const std::string getProtoName() { return "AttachSceneReq";} 
    unsigned long long avatarID;  
    unsigned long long sceneID;  
    std::string token; //令牌  
    AttachSceneReq() 
    { 
        avatarID = 0; 
        sceneID = 0; 
    } 
    AttachSceneReq(const unsigned long long & avatarID, const unsigned long long & sceneID, const std::string & token) 
    { 
        this->avatarID = avatarID; 
        this->sceneID = sceneID; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachSceneReq & data) 
{ 
    ws << data.avatarID;  
    ws << data.sceneID;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachSceneReq & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.sceneID;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "sceneID=" << info.sceneID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachSceneResp 
{ 
    static const unsigned short getProtoID() { return 50002;} 
    static const std::string getProtoName() { return "AttachSceneResp";} 
    unsigned short retCode; //错误码  
    unsigned long long avatarID;  
    unsigned long long sceneID;  
    AttachSceneResp() 
    { 
        retCode = 0; 
        avatarID = 0; 
        sceneID = 0; 
    } 
    AttachSceneResp(const unsigned short & retCode, const unsigned long long & avatarID, const unsigned long long & sceneID) 
    { 
        this->retCode = retCode; 
        this->avatarID = avatarID; 
        this->sceneID = sceneID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachSceneResp & data) 
{ 
    ws << data.retCode;  
    ws << data.avatarID;  
    ws << data.sceneID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachSceneResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.avatarID;  
    rs >> data.sceneID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachSceneResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "sceneID=" << info.sceneID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneSectionNotice //填充场景数据  
{ 
    static const unsigned short getProtoID() { return 50010;} 
    static const std::string getProtoName() { return "SceneSectionNotice";} 
    SceneSection section;  
    SceneSectionNotice() 
    { 
    } 
    SceneSectionNotice(const SceneSection & section) 
    { 
        this->section = section; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneSectionNotice & data) 
{ 
    ws << data.section;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneSectionNotice & data) 
{ 
    rs >> data.section;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneSectionNotice & info) 
{ 
    stm << "[\n"; 
    stm << "section=" << info.section << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RefreshEntityNotice 
{ 
    static const unsigned short getProtoID() { return 50011;} 
    static const std::string getProtoName() { return "RefreshEntityNotice";} 
    EntityInfoArray entityInfos;  
    EntityPointArray entityPoints;  
    double serverTime; //服务器当前时间  
    RefreshEntityNotice() 
    { 
        serverTime = 0.0; 
    } 
    RefreshEntityNotice(const EntityInfoArray & entityInfos, const EntityPointArray & entityPoints, const double & serverTime) 
    { 
        this->entityInfos = entityInfos; 
        this->entityPoints = entityPoints; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshEntityNotice & data) 
{ 
    ws << data.entityInfos;  
    ws << data.entityPoints;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshEntityNotice & data) 
{ 
    rs >> data.entityInfos;  
    rs >> data.entityPoints;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshEntityNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entityInfos=" << info.entityInfos << "\n"; 
    stm << "entityPoints=" << info.entityPoints << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RefreshSceneReportsNotice 
{ 
    static const unsigned short getProtoID() { return 50005;} 
    static const std::string getProtoName() { return "RefreshSceneReportsNotice";} 
    EntityReportArray reports;  
    double serverTime; //服务器当前时间  
    RefreshSceneReportsNotice() 
    { 
        serverTime = 0.0; 
    } 
    RefreshSceneReportsNotice(const EntityReportArray & reports, const double & serverTime) 
    { 
        this->reports = reports; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshSceneReportsNotice & data) 
{ 
    ws << data.reports;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshSceneReportsNotice & data) 
{ 
    rs >> data.reports;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshSceneReportsNotice & info) 
{ 
    stm << "[\n"; 
    stm << "reports=" << info.reports << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AddEntityNotice //一批实体加入场景时, 把这些实体的数据广播给其他玩家  
{ 
    static const unsigned short getProtoID() { return 50006;} 
    static const std::string getProtoName() { return "AddEntityNotice";} 
    EntityFullDataArray entitys;  
    double serverTime; //服务器当前时间  
    AddEntityNotice() 
    { 
        serverTime = 0.0; 
    } 
    AddEntityNotice(const EntityFullDataArray & entitys, const double & serverTime) 
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
    static const unsigned short getProtoID() { return 50007;} 
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
 
struct AddBuffNotice 
{ 
    static const unsigned short getProtoID() { return 50008;} 
    static const std::string getProtoName() { return "AddBuffNotice";} 
    unsigned long long eid;  
    double serverTime; //服务器当前时间  
    AddBuffNotice() 
    { 
        eid = 0; 
        serverTime = 0.0; 
    } 
    AddBuffNotice(const unsigned long long & eid, const double & serverTime) 
    { 
        this->eid = eid; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddBuffNotice & data) 
{ 
    ws << data.eid;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddBuffNotice & data) 
{ 
    rs >> data.eid;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AddBuffNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RemoveBuffNotice 
{ 
    static const unsigned short getProtoID() { return 50009;} 
    static const std::string getProtoName() { return "RemoveBuffNotice";} 
    unsigned long long eid;  
    double serverTime; //服务器当前时间  
    RemoveBuffNotice() 
    { 
        eid = 0; 
        serverTime = 0.0; 
    } 
    RemoveBuffNotice(const unsigned long long & eid, const double & serverTime) 
    { 
        this->eid = eid; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RemoveBuffNotice & data) 
{ 
    ws << data.eid;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RemoveBuffNotice & data) 
{ 
    rs >> data.eid;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RemoveBuffNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
