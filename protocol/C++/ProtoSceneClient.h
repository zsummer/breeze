 
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
    static const unsigned short getProtoID() { return 50003;} 
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
 
struct SceneRefreshNotice 
{ 
    static const unsigned short getProtoID() { return 50004;} 
    static const std::string getProtoName() { return "SceneRefreshNotice";} 
    EntityInfoArray entityInfos;  
    EntityMoveArray entityMoves;  
    SceneRefreshNotice() 
    { 
    } 
    SceneRefreshNotice(const EntityInfoArray & entityInfos, const EntityMoveArray & entityMoves) 
    { 
        this->entityInfos = entityInfos; 
        this->entityMoves = entityMoves; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneRefreshNotice & data) 
{ 
    ws << data.entityInfos;  
    ws << data.entityMoves;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneRefreshNotice & data) 
{ 
    rs >> data.entityInfos;  
    rs >> data.entityMoves;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneRefreshNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entityInfos=" << info.entityInfos << "\n"; 
    stm << "entityMoves=" << info.entityMoves << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneReportsNotice 
{ 
    static const unsigned short getProtoID() { return 50005;} 
    static const std::string getProtoName() { return "SceneReportsNotice";} 
    EntityReportArray reports;  
    SceneReportsNotice() 
    { 
    } 
    SceneReportsNotice(const EntityReportArray & reports) 
    { 
        this->reports = reports; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneReportsNotice & data) 
{ 
    ws << data.reports;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneReportsNotice & data) 
{ 
    rs >> data.reports;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneReportsNotice & info) 
{ 
    stm << "[\n"; 
    stm << "reports=" << info.reports << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AddEntityNotice //一批实体加入场景时, 把这些实体的数据广播给其他玩家  
{ 
    static const unsigned short getProtoID() { return 50006;} 
    static const std::string getProtoName() { return "AddEntityNotice";} 
    EntityFullDataArray entitys;  
    AddEntityNotice() 
    { 
    } 
    AddEntityNotice(const EntityFullDataArray & entitys) 
    { 
        this->entitys = entitys; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddEntityNotice & data) 
{ 
    ws << data.entitys;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddEntityNotice & data) 
{ 
    rs >> data.entitys;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AddEntityNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entitys=" << info.entitys << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RemoveEntityNotice //实体离开场景时, 把该实体的数据广播给其他玩家  
{ 
    static const unsigned short getProtoID() { return 50007;} 
    static const std::string getProtoName() { return "RemoveEntityNotice";} 
    EntityIDArray eids;  
    RemoveEntityNotice() 
    { 
    } 
    RemoveEntityNotice(const EntityIDArray & eids) 
    { 
        this->eids = eids; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RemoveEntityNotice & data) 
{ 
    ws << data.eids;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RemoveEntityNotice & data) 
{ 
    rs >> data.eids;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RemoveEntityNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eids=" << info.eids << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct MoveReq 
{ 
    static const unsigned short getProtoID() { return 50008;} 
    static const std::string getProtoName() { return "MoveReq";} 
    unsigned long long eid;  
    unsigned short action;  
    EPoint clientPos;  
    EPoint dstPos;  
    unsigned long long follow;  
    MoveReq() 
    { 
        eid = 0; 
        action = 0; 
        follow = 0; 
    } 
    MoveReq(const unsigned long long & eid, const unsigned short & action, const EPoint & clientPos, const EPoint & dstPos, const unsigned long long & follow) 
    { 
        this->eid = eid; 
        this->action = action; 
        this->clientPos = clientPos; 
        this->dstPos = dstPos; 
        this->follow = follow; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const MoveReq & data) 
{ 
    ws << data.eid;  
    ws << data.action;  
    ws << data.clientPos;  
    ws << data.dstPos;  
    ws << data.follow;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, MoveReq & data) 
{ 
    rs >> data.eid;  
    rs >> data.action;  
    rs >> data.clientPos;  
    rs >> data.dstPos;  
    rs >> data.follow;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const MoveReq & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "action=" << info.action << "\n"; 
    stm << "clientPos=" << info.clientPos << "\n"; 
    stm << "dstPos=" << info.dstPos << "\n"; 
    stm << "follow=" << info.follow << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct MoveResp //只有失败时才会使用该协议  
{ 
    static const unsigned short getProtoID() { return 50009;} 
    static const std::string getProtoName() { return "MoveResp";} 
    unsigned short retCode;  
    unsigned long long eid;  
    unsigned short action;  
    MoveResp() 
    { 
        retCode = 0; 
        eid = 0; 
        action = 0; 
    } 
    MoveResp(const unsigned short & retCode, const unsigned long long & eid, const unsigned short & action) 
    { 
        this->retCode = retCode; 
        this->eid = eid; 
        this->action = action; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const MoveResp & data) 
{ 
    ws << data.retCode;  
    ws << data.eid;  
    ws << data.action;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, MoveResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.eid;  
    rs >> data.action;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const MoveResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "action=" << info.action << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct MoveNotice //移动开始/结束通知  
{ 
    static const unsigned short getProtoID() { return 50010;} 
    static const std::string getProtoName() { return "MoveNotice";} 
    EntityMove moveInfo;  
    MoveNotice() 
    { 
    } 
    MoveNotice(const EntityMove & moveInfo) 
    { 
        this->moveInfo = moveInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const MoveNotice & data) 
{ 
    ws << data.moveInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, MoveNotice & data) 
{ 
    rs >> data.moveInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const MoveNotice & info) 
{ 
    stm << "[\n"; 
    stm << "moveInfo=" << info.moveInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AddBuffNotice 
{ 
    static const unsigned short getProtoID() { return 50011;} 
    static const std::string getProtoName() { return "AddBuffNotice";} 
    unsigned long long eid;  
    AddBuffNotice() 
    { 
        eid = 0; 
    } 
    AddBuffNotice(const unsigned long long & eid) 
    { 
        this->eid = eid; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddBuffNotice & data) 
{ 
    ws << data.eid;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddBuffNotice & data) 
{ 
    rs >> data.eid;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AddBuffNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RemoveBuffNotice 
{ 
    static const unsigned short getProtoID() { return 50012;} 
    static const std::string getProtoName() { return "RemoveBuffNotice";} 
    unsigned long long eid;  
    RemoveBuffNotice() 
    { 
        eid = 0; 
    } 
    RemoveBuffNotice(const unsigned long long & eid) 
    { 
        this->eid = eid; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RemoveBuffNotice & data) 
{ 
    ws << data.eid;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RemoveBuffNotice & data) 
{ 
    rs >> data.eid;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RemoveBuffNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UseSkillReq 
{ 
    static const unsigned short getProtoID() { return 50016;} 
    static const std::string getProtoName() { return "UseSkillReq";} 
    unsigned long long eid;  
    UseSkillReq() 
    { 
        eid = 0; 
    } 
    UseSkillReq(const unsigned long long & eid) 
    { 
        this->eid = eid; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UseSkillReq & data) 
{ 
    ws << data.eid;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UseSkillReq & data) 
{ 
    rs >> data.eid;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UseSkillReq & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UseSkillResp //只有失败时才会使用该协议  
{ 
    static const unsigned short getProtoID() { return 50017;} 
    static const std::string getProtoName() { return "UseSkillResp";} 
    unsigned short retCode;  
    unsigned long long eid;  
    UseSkillResp() 
    { 
        retCode = 0; 
        eid = 0; 
    } 
    UseSkillResp(const unsigned short & retCode, const unsigned long long & eid) 
    { 
        this->retCode = retCode; 
        this->eid = eid; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UseSkillResp & data) 
{ 
    ws << data.retCode;  
    ws << data.eid;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UseSkillResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.eid;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UseSkillResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UseSkillNotice 
{ 
    static const unsigned short getProtoID() { return 50018;} 
    static const std::string getProtoName() { return "UseSkillNotice";} 
    unsigned long long eid;  
    UseSkillNotice() 
    { 
        eid = 0; 
    } 
    UseSkillNotice(const unsigned long long & eid) 
    { 
        this->eid = eid; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UseSkillNotice & data) 
{ 
    ws << data.eid;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UseSkillNotice & data) 
{ 
    rs >> data.eid;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UseSkillNotice & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
