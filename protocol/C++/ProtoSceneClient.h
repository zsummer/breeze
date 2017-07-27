 
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
    stm << "["; 
    stm << "]"; 
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
    stm << "["; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "sceneID=" << info.sceneID << ","; 
    stm << "token=" << info.token << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "sceneID=" << info.sceneID << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "section=" << info.section << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneRefreshNotice 
{ 
    static const unsigned short getProtoID() { return 50004;} 
    static const std::string getProtoName() { return "SceneRefreshNotice";} 
    EntityStateArray entityStates;  
    EntityMoveArray entityMoves;  
    SceneRefreshNotice() 
    { 
    } 
    SceneRefreshNotice(const EntityStateArray & entityStates, const EntityMoveArray & entityMoves) 
    { 
        this->entityStates = entityStates; 
        this->entityMoves = entityMoves; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneRefreshNotice & data) 
{ 
    ws << data.entityStates;  
    ws << data.entityMoves;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneRefreshNotice & data) 
{ 
    rs >> data.entityStates;  
    rs >> data.entityMoves;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneRefreshNotice & info) 
{ 
    stm << "["; 
    stm << "entityStates=" << info.entityStates << ","; 
    stm << "entityMoves=" << info.entityMoves << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "reports=" << info.reports << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct AddEntityNotice //一批实体加入场景时, 把这些实体的数据广播给其他玩家  
{ 
    static const unsigned short getProtoID() { return 50006;} 
    static const std::string getProtoName() { return "AddEntityNotice";} 
    EntityClientSyncArray syncs;  
    AddEntityNotice() 
    { 
    } 
    AddEntityNotice(const EntityClientSyncArray & syncs) 
    { 
        this->syncs = syncs; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddEntityNotice & data) 
{ 
    ws << data.syncs;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddEntityNotice & data) 
{ 
    rs >> data.syncs;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AddEntityNotice & info) 
{ 
    stm << "["; 
    stm << "syncs=" << info.syncs << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "eids=" << info.eids << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct MoveReq 
{ 
    static const unsigned short getProtoID() { return 50008;} 
    static const std::string getProtoName() { return "MoveReq";} 
    unsigned long long eid;  
    unsigned short action;  
    EPosition clientPos;  
    EPositionArray waypoints;  
    unsigned long long follow;  
    MoveReq() 
    { 
        eid = 0; 
        action = 0; 
        follow = 0; 
    } 
    MoveReq(const unsigned long long & eid, const unsigned short & action, const EPosition & clientPos, const EPositionArray & waypoints, const unsigned long long & follow) 
    { 
        this->eid = eid; 
        this->action = action; 
        this->clientPos = clientPos; 
        this->waypoints = waypoints; 
        this->follow = follow; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const MoveReq & data) 
{ 
    ws << data.eid;  
    ws << data.action;  
    ws << data.clientPos;  
    ws << data.waypoints;  
    ws << data.follow;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, MoveReq & data) 
{ 
    rs >> data.eid;  
    rs >> data.action;  
    rs >> data.clientPos;  
    rs >> data.waypoints;  
    rs >> data.follow;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const MoveReq & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "action=" << info.action << ","; 
    stm << "clientPos=" << info.clientPos << ","; 
    stm << "waypoints=" << info.waypoints << ","; 
    stm << "follow=" << info.follow << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "eid=" << info.eid << ","; 
    stm << "action=" << info.action << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "moveInfo=" << info.moveInfo << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "]"; 
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
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct UseSkillReq 
{ 
    static const unsigned short getProtoID() { return 50013;} 
    static const std::string getProtoName() { return "UseSkillReq";} 
    unsigned long long eid;  
    unsigned long long skillID;  
    EPosition dst;  
    unsigned short foeFirst;  
    UseSkillReq() 
    { 
        eid = 0; 
        skillID = 0; 
        foeFirst = 0; 
    } 
    UseSkillReq(const unsigned long long & eid, const unsigned long long & skillID, const EPosition & dst, const unsigned short & foeFirst) 
    { 
        this->eid = eid; 
        this->skillID = skillID; 
        this->dst = dst; 
        this->foeFirst = foeFirst; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UseSkillReq & data) 
{ 
    ws << data.eid;  
    ws << data.skillID;  
    ws << data.dst;  
    ws << data.foeFirst;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UseSkillReq & data) 
{ 
    rs >> data.eid;  
    rs >> data.skillID;  
    rs >> data.dst;  
    rs >> data.foeFirst;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UseSkillReq & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "skillID=" << info.skillID << ","; 
    stm << "dst=" << info.dst << ","; 
    stm << "foeFirst=" << info.foeFirst << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct UseSkillResp //只有失败时才会使用该协议  
{ 
    static const unsigned short getProtoID() { return 50014;} 
    static const std::string getProtoName() { return "UseSkillResp";} 
    unsigned short retCode;  
    unsigned long long eid;  
    unsigned long long skillID;  
    EPosition dst;  
    unsigned short foeFirst;  
    UseSkillResp() 
    { 
        retCode = 0; 
        eid = 0; 
        skillID = 0; 
        foeFirst = 0; 
    } 
    UseSkillResp(const unsigned short & retCode, const unsigned long long & eid, const unsigned long long & skillID, const EPosition & dst, const unsigned short & foeFirst) 
    { 
        this->retCode = retCode; 
        this->eid = eid; 
        this->skillID = skillID; 
        this->dst = dst; 
        this->foeFirst = foeFirst; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UseSkillResp & data) 
{ 
    ws << data.retCode;  
    ws << data.eid;  
    ws << data.skillID;  
    ws << data.dst;  
    ws << data.foeFirst;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UseSkillResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.eid;  
    rs >> data.skillID;  
    rs >> data.dst;  
    rs >> data.foeFirst;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UseSkillResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "eid=" << info.eid << ","; 
    stm << "skillID=" << info.skillID << ","; 
    stm << "dst=" << info.dst << ","; 
    stm << "foeFirst=" << info.foeFirst << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct UseSkillNotice 
{ 
    static const unsigned short getProtoID() { return 50015;} 
    static const std::string getProtoName() { return "UseSkillNotice";} 
    unsigned long long eid;  
    EntitySkillInfo skill;  
    UseSkillNotice() 
    { 
        eid = 0; 
    } 
    UseSkillNotice(const unsigned long long & eid, const EntitySkillInfo & skill) 
    { 
        this->eid = eid; 
        this->skill = skill; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UseSkillNotice & data) 
{ 
    ws << data.eid;  
    ws << data.skill;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UseSkillNotice & data) 
{ 
    rs >> data.eid;  
    rs >> data.skill;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UseSkillNotice & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "skill=" << info.skill << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneEventNotice 
{ 
    static const unsigned short getProtoID() { return 50016;} 
    static const std::string getProtoName() { return "SceneEventNotice";} 
    SceneEventInfoArray info;  
    SceneEventNotice() 
    { 
    } 
    SceneEventNotice(const SceneEventInfoArray & info) 
    { 
        this->info = info; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneEventNotice & data) 
{ 
    ws << data.info;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneEventNotice & data) 
{ 
    rs >> data.info;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneEventNotice & info) 
{ 
    stm << "["; 
    stm << "info=" << info.info << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientCustomReq 
{ 
    static const unsigned short getProtoID() { return 50017;} 
    static const std::string getProtoName() { return "ClientCustomReq";} 
    unsigned long long eid;  
    unsigned long long customID;  
    double fValue;  
    unsigned long long uValue;  
    std::string sValue;  
    ClientCustomReq() 
    { 
        eid = 0; 
        customID = 0; 
        fValue = 0.0; 
        uValue = 0; 
    } 
    ClientCustomReq(const unsigned long long & eid, const unsigned long long & customID, const double & fValue, const unsigned long long & uValue, const std::string & sValue) 
    { 
        this->eid = eid; 
        this->customID = customID; 
        this->fValue = fValue; 
        this->uValue = uValue; 
        this->sValue = sValue; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientCustomReq & data) 
{ 
    ws << data.eid;  
    ws << data.customID;  
    ws << data.fValue;  
    ws << data.uValue;  
    ws << data.sValue;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientCustomReq & data) 
{ 
    rs >> data.eid;  
    rs >> data.customID;  
    rs >> data.fValue;  
    rs >> data.uValue;  
    rs >> data.sValue;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientCustomReq & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "customID=" << info.customID << ","; 
    stm << "fValue=" << info.fValue << ","; 
    stm << "uValue=" << info.uValue << ","; 
    stm << "sValue=" << info.sValue << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientCustomResp //只有失败时才会使用该协议  
{ 
    static const unsigned short getProtoID() { return 50018;} 
    static const std::string getProtoName() { return "ClientCustomResp";} 
    unsigned short retCode;  
    unsigned long long eid;  
    unsigned long long customID;  
    ClientCustomResp() 
    { 
        retCode = 0; 
        eid = 0; 
        customID = 0; 
    } 
    ClientCustomResp(const unsigned short & retCode, const unsigned long long & eid, const unsigned long long & customID) 
    { 
        this->retCode = retCode; 
        this->eid = eid; 
        this->customID = customID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientCustomResp & data) 
{ 
    ws << data.retCode;  
    ws << data.eid;  
    ws << data.customID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientCustomResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.eid;  
    rs >> data.customID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientCustomResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "eid=" << info.eid << ","; 
    stm << "customID=" << info.customID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientCustomNotice 
{ 
    static const unsigned short getProtoID() { return 50019;} 
    static const std::string getProtoName() { return "ClientCustomNotice";} 
    unsigned long long eid;  
    unsigned long long customID;  
    double fValue;  
    unsigned long long uValue;  
    std::string sValue;  
    ClientCustomNotice() 
    { 
        eid = 0; 
        customID = 0; 
        fValue = 0.0; 
        uValue = 0; 
    } 
    ClientCustomNotice(const unsigned long long & eid, const unsigned long long & customID, const double & fValue, const unsigned long long & uValue, const std::string & sValue) 
    { 
        this->eid = eid; 
        this->customID = customID; 
        this->fValue = fValue; 
        this->uValue = uValue; 
        this->sValue = sValue; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientCustomNotice & data) 
{ 
    ws << data.eid;  
    ws << data.customID;  
    ws << data.fValue;  
    ws << data.uValue;  
    ws << data.sValue;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientCustomNotice & data) 
{ 
    rs >> data.eid;  
    rs >> data.customID;  
    rs >> data.fValue;  
    rs >> data.uValue;  
    rs >> data.sValue;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientCustomNotice & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "customID=" << info.customID << ","; 
    stm << "fValue=" << info.fValue << ","; 
    stm << "uValue=" << info.uValue << ","; 
    stm << "sValue=" << info.sValue << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientPingTestReq 
{ 
    static const unsigned short getProtoID() { return 50020;} 
    static const std::string getProtoName() { return "ClientPingTestReq";} 
    unsigned long long seqID;  
    double clientTime;  
    ClientPingTestReq() 
    { 
        seqID = 0; 
        clientTime = 0.0; 
    } 
    ClientPingTestReq(const unsigned long long & seqID, const double & clientTime) 
    { 
        this->seqID = seqID; 
        this->clientTime = clientTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientPingTestReq & data) 
{ 
    ws << data.seqID;  
    ws << data.clientTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientPingTestReq & data) 
{ 
    rs >> data.seqID;  
    rs >> data.clientTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientPingTestReq & info) 
{ 
    stm << "["; 
    stm << "seqID=" << info.seqID << ","; 
    stm << "clientTime=" << info.clientTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientPingTestResp 
{ 
    static const unsigned short getProtoID() { return 50021;} 
    static const std::string getProtoName() { return "ClientPingTestResp";} 
    unsigned short retCode;  
    unsigned long long seqID;  
    double clientTime;  
    ClientPingTestResp() 
    { 
        retCode = 0; 
        seqID = 0; 
        clientTime = 0.0; 
    } 
    ClientPingTestResp(const unsigned short & retCode, const unsigned long long & seqID, const double & clientTime) 
    { 
        this->retCode = retCode; 
        this->seqID = seqID; 
        this->clientTime = clientTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientPingTestResp & data) 
{ 
    ws << data.retCode;  
    ws << data.seqID;  
    ws << data.clientTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientPingTestResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.seqID;  
    rs >> data.clientTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientPingTestResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "seqID=" << info.seqID << ","; 
    stm << "clientTime=" << info.clientTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 
