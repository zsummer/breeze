 
#ifndef _PROTOSCENESERVER_H_ 
#define _PROTOSCENESERVER_H_ 
 
 
struct SceneKnock //战场服务器挂载  
{ 
    static const unsigned short getProtoID() { return 39000;} 
    static const std::string getProtoName() { return "SceneKnock";} 
    unsigned long long lineID; //分线ID  
    std::string pubHost;  
    unsigned short pubPort;  
    SceneKnock() 
    { 
        lineID = 0; 
        pubPort = 0; 
    } 
    SceneKnock(const unsigned long long & lineID, const std::string & pubHost, const unsigned short & pubPort) 
    { 
        this->lineID = lineID; 
        this->pubHost = pubHost; 
        this->pubPort = pubPort; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneKnock & data) 
{ 
    ws << data.lineID;  
    ws << data.pubHost;  
    ws << data.pubPort;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneKnock & data) 
{ 
    rs >> data.lineID;  
    rs >> data.pubHost;  
    rs >> data.pubPort;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneKnock & info) 
{ 
    stm << "[\n"; 
    stm << "lineID=" << info.lineID << "\n"; 
    stm << "pubHost=" << info.pubHost << "\n"; 
    stm << "pubPort=" << info.pubPort << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ScenePulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 39001;} 
    static const std::string getProtoName() { return "ScenePulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ScenePulse & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ScenePulse & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ScenePulse & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneServerJoinGroupIns //创建/加入编队, 来自docker的指令  
{ 
    static const unsigned short getProtoID() { return 39002;} 
    static const std::string getProtoName() { return "SceneServerJoinGroupIns";} 
    unsigned long long groupID; //编队ID, 0为创建  
    AvatarBaseInfo baseInfo; //角色数据  
    AvatarPropMap baseProps; //角色属性数据  
    SceneServerJoinGroupIns() 
    { 
        groupID = 0; 
    } 
    SceneServerJoinGroupIns(const unsigned long long & groupID, const AvatarBaseInfo & baseInfo, const AvatarPropMap & baseProps) 
    { 
        this->groupID = groupID; 
        this->baseInfo = baseInfo; 
        this->baseProps = baseProps; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerJoinGroupIns & data) 
{ 
    ws << data.groupID;  
    ws << data.baseInfo;  
    ws << data.baseProps;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerJoinGroupIns & data) 
{ 
    rs >> data.groupID;  
    rs >> data.baseInfo;  
    rs >> data.baseProps;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerJoinGroupIns & info) 
{ 
    stm << "[\n"; 
    stm << "groupID=" << info.groupID << "\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "baseProps=" << info.baseProps << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneServerJoinGroupAck //创建/加入编队响应结果  
{ 
    static const unsigned short getProtoID() { return 39003;} 
    static const std::string getProtoName() { return "SceneServerJoinGroupAck";} 
    unsigned short retCode;  
    unsigned long long newGroupID;  
    unsigned long long oldGroupID;  
    SceneServerJoinGroupAck() 
    { 
        retCode = 0; 
        newGroupID = 0; 
        oldGroupID = 0; 
    } 
    SceneServerJoinGroupAck(const unsigned short & retCode, const unsigned long long & newGroupID, const unsigned long long & oldGroupID) 
    { 
        this->retCode = retCode; 
        this->newGroupID = newGroupID; 
        this->oldGroupID = oldGroupID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerJoinGroupAck & data) 
{ 
    ws << data.retCode;  
    ws << data.newGroupID;  
    ws << data.oldGroupID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerJoinGroupAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.newGroupID;  
    rs >> data.oldGroupID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerJoinGroupAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "newGroupID=" << info.newGroupID << "\n"; 
    stm << "oldGroupID=" << info.oldGroupID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneServerEnterSceneIns //开辟场景  
{ 
    static const unsigned short getProtoID() { return 39006;} 
    static const std::string getProtoName() { return "SceneServerEnterSceneIns";} 
    unsigned short sceneType; //类型  
    unsigned long long mapID;  
    SceneGroupInfoArray groups; //多个编队  
    SceneServerEnterSceneIns() 
    { 
        sceneType = 0; 
        mapID = 0; 
    } 
    SceneServerEnterSceneIns(const unsigned short & sceneType, const unsigned long long & mapID, const SceneGroupInfoArray & groups) 
    { 
        this->sceneType = sceneType; 
        this->mapID = mapID; 
        this->groups = groups; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerEnterSceneIns & data) 
{ 
    ws << data.sceneType;  
    ws << data.mapID;  
    ws << data.groups;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerEnterSceneIns & data) 
{ 
    rs >> data.sceneType;  
    rs >> data.mapID;  
    rs >> data.groups;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerEnterSceneIns & info) 
{ 
    stm << "[\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "mapID=" << info.mapID << "\n"; 
    stm << "groups=" << info.groups << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneServerGroupStatusChangeIns //scene ==> world  
{ 
    static const unsigned short getProtoID() { return 39007;} 
    static const std::string getProtoName() { return "SceneServerGroupStatusChangeIns";} 
    unsigned long long groupID;  
    unsigned long long sceneID;  
    unsigned short status; //如果是NONE 说明离开场景  
    SceneServerGroupStatusChangeIns() 
    { 
        groupID = 0; 
        sceneID = 0; 
        status = 0; 
    } 
    SceneServerGroupStatusChangeIns(const unsigned long long & groupID, const unsigned long long & sceneID, const unsigned short & status) 
    { 
        this->groupID = groupID; 
        this->sceneID = sceneID; 
        this->status = status; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerGroupStatusChangeIns & data) 
{ 
    ws << data.groupID;  
    ws << data.sceneID;  
    ws << data.status;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerGroupStatusChangeIns & data) 
{ 
    rs >> data.groupID;  
    rs >> data.sceneID;  
    rs >> data.status;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerGroupStatusChangeIns & info) 
{ 
    stm << "[\n"; 
    stm << "groupID=" << info.groupID << "\n"; 
    stm << "sceneID=" << info.sceneID << "\n"; 
    stm << "status=" << info.status << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
