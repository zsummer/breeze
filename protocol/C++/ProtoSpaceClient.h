 
#ifndef _PROTOSPACECLIENT_H_ 
#define _PROTOSPACECLIENT_H_ 
 
 
struct SceneInfoReq //获取场景信息  
{ 
    static const unsigned short getProtoID() { return 50000;} 
    static const std::string getProtoName() { return "SceneInfoReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfoReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfoReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfoReq & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneInfoAck //获取场景信息  
{ 
    static const unsigned short getProtoID() { return 50001;} 
    static const std::string getProtoName() { return "SceneInfoAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes;  
    SceneInfoAck() 
    { 
        retCode = 0; 
    } 
    SceneInfoAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfoAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfoAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfoAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct TryEnterSceneReq //进入场景  
{ 
    static const unsigned short getProtoID() { return 50002;} 
    static const std::string getProtoName() { return "TryEnterSceneReq";} 
    unsigned short type; //类型, 如果是不同类型,该请求会触发场景切换动作  
    TryEnterSceneReq() 
    { 
        type = 0; 
    } 
    TryEnterSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TryEnterSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TryEnterSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TryEnterSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct TryEnterSceneAck //进入场景  
{ 
    static const unsigned short getProtoID() { return 50003;} 
    static const std::string getProtoName() { return "TryEnterSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    TryEnterSceneAck() 
    { 
        retCode = 0; 
    } 
    TryEnterSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TryEnterSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TryEnterSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TryEnterSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneInfoNotice //场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中  
{ 
    static const unsigned short getProtoID() { return 50004;} 
    static const std::string getProtoName() { return "SceneInfoNotice";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    SceneInfoNotice() 
    { 
        retCode = 0; 
    } 
    SceneInfoNotice(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfoNotice & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfoNotice & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfoNotice & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSceneReq //离开场景  
{ 
    static const unsigned short getProtoID() { return 50005;} 
    static const std::string getProtoName() { return "LeaveSceneReq";} 
    unsigned short type; //类型  
    LeaveSceneReq() 
    { 
        type = 0; 
    } 
    LeaveSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSceneAck //离开场景  
{ 
    static const unsigned short getProtoID() { return 50006;} 
    static const std::string getProtoName() { return "LeaveSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    LeaveSceneAck() 
    { 
        retCode = 0; 
    } 
    LeaveSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct QuitSceneReq //退出场景  
{ 
    static const unsigned short getProtoID() { return 50007;} 
    static const std::string getProtoName() { return "QuitSceneReq";} 
    unsigned short type; //类型  
    QuitSceneReq() 
    { 
        type = 0; 
    } 
    QuitSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const QuitSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, QuitSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const QuitSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct QuitSceneAck //退出场景  
{ 
    static const unsigned short getProtoID() { return 50008;} 
    static const std::string getProtoName() { return "QuitSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    QuitSceneAck() 
    { 
        retCode = 0; 
    } 
    QuitSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const QuitSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, QuitSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const QuitSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
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
 
struct RefreshSpaceNotice //增量更新场景中的实体数据, 服务器定时100ms广播  
{ 
    static const unsigned short getProtoID() { return 50010;} 
    static const std::string getProtoName() { return "RefreshSpaceNotice";} 
    EntityInfoArray entitys;  
    EntityReportArray reports;  
    double serverTime; //服务器当前时间  
    RefreshSpaceNotice() 
    { 
        serverTime = 0.0; 
    } 
    RefreshSpaceNotice(const EntityInfoArray & entitys, const EntityReportArray & reports, const double & serverTime) 
    { 
        this->entitys = entitys; 
        this->reports = reports; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RefreshSpaceNotice & data) 
{ 
    ws << data.entitys;  
    ws << data.reports;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RefreshSpaceNotice & data) 
{ 
    rs >> data.entitys;  
    rs >> data.reports;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RefreshSpaceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "entitys=" << info.entitys << "\n"; 
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
