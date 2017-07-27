 
#ifndef _PROTOSCENESERVER_H_ 
#define _PROTOSCENESERVER_H_ 
 
 
struct SceneKnock //战场服务器挂载  
{ 
    static const unsigned short getProtoID() { return 4000;} 
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
    stm << "["; 
    stm << "lineID=" << info.lineID << ","; 
    stm << "pubHost=" << info.pubHost << ","; 
    stm << "pubPort=" << info.pubPort << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ScenePulse //集群脉冲  
{ 
    static const unsigned short getProtoID() { return 4001;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneServerJoinGroupIns //创建/加入编队, 来自docker的指令  
{ 
    static const unsigned short getProtoID() { return 4002;} 
    static const std::string getProtoName() { return "SceneServerJoinGroupIns";} 
    unsigned long long refresh; //0为客户端请求操作, 1为仅仅刷新数据  
    unsigned long long groupID; //编队ID, 0为创建  
    unsigned long long modelID; //模型ID  
    DictArrayKey equips; //额外装备  
    unsigned long long avatarID;  
    std::string avatarName;  
    double rankScore; //天梯分数  
    SceneServerJoinGroupIns() 
    { 
        refresh = 0; 
        groupID = 0; 
        modelID = 0; 
        avatarID = 0; 
        rankScore = 0.0; 
    } 
    SceneServerJoinGroupIns(const unsigned long long & refresh, const unsigned long long & groupID, const unsigned long long & modelID, const DictArrayKey & equips, const unsigned long long & avatarID, const std::string & avatarName, const double & rankScore) 
    { 
        this->refresh = refresh; 
        this->groupID = groupID; 
        this->modelID = modelID; 
        this->equips = equips; 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->rankScore = rankScore; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerJoinGroupIns & data) 
{ 
    ws << data.refresh;  
    ws << data.groupID;  
    ws << data.modelID;  
    ws << data.equips;  
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.rankScore;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerJoinGroupIns & data) 
{ 
    rs >> data.refresh;  
    rs >> data.groupID;  
    rs >> data.modelID;  
    rs >> data.equips;  
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.rankScore;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerJoinGroupIns & info) 
{ 
    stm << "["; 
    stm << "refresh=" << info.refresh << ","; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "modelID=" << info.modelID << ","; 
    stm << "equips=" << info.equips << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "rankScore=" << info.rankScore << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneServerJoinGroupAck //创建/加入编队响应结果  
{ 
    static const unsigned short getProtoID() { return 4003;} 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "newGroupID=" << info.newGroupID << ","; 
    stm << "oldGroupID=" << info.oldGroupID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneServerEnterSceneIns //开辟场景  
{ 
    static const unsigned short getProtoID() { return 4004;} 
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
    stm << "["; 
    stm << "sceneType=" << info.sceneType << ","; 
    stm << "mapID=" << info.mapID << ","; 
    stm << "groups=" << info.groups << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneServerCancelSceneIns //退出场景  
{ 
    static const unsigned short getProtoID() { return 4005;} 
    static const std::string getProtoName() { return "SceneServerCancelSceneIns";} 
    unsigned long long sceneID; //sceneID  
    unsigned long long groupID; //groupID  
    SceneServerCancelSceneIns() 
    { 
        sceneID = 0; 
        groupID = 0; 
    } 
    SceneServerCancelSceneIns(const unsigned long long & sceneID, const unsigned long long & groupID) 
    { 
        this->sceneID = sceneID; 
        this->groupID = groupID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerCancelSceneIns & data) 
{ 
    ws << data.sceneID;  
    ws << data.groupID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerCancelSceneIns & data) 
{ 
    rs >> data.sceneID;  
    rs >> data.groupID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerCancelSceneIns & info) 
{ 
    stm << "["; 
    stm << "sceneID=" << info.sceneID << ","; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneServerGroupStateFeedback //scene ==> world  
{ 
    static const unsigned short getProtoID() { return 4006;} 
    static const std::string getProtoName() { return "SceneServerGroupStateFeedback";} 
    unsigned long long sceneID;  
    unsigned long long groupID;  
    unsigned short state; //如果是NONE 说明离开场景  
    SceneServerGroupStateFeedback() 
    { 
        sceneID = 0; 
        groupID = 0; 
        state = 0; 
    } 
    SceneServerGroupStateFeedback(const unsigned long long & sceneID, const unsigned long long & groupID, const unsigned short & state) 
    { 
        this->sceneID = sceneID; 
        this->groupID = groupID; 
        this->state = state; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerGroupStateFeedback & data) 
{ 
    ws << data.sceneID;  
    ws << data.groupID;  
    ws << data.state;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerGroupStateFeedback & data) 
{ 
    rs >> data.sceneID;  
    rs >> data.groupID;  
    rs >> data.state;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerGroupStateFeedback & info) 
{ 
    stm << "["; 
    stm << "sceneID=" << info.sceneID << ","; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "state=" << info.state << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct EntityScriptNotice //同步给脚本  
{ 
    static const unsigned short getProtoID() { return 4008;} 
    static const std::string getProtoName() { return "EntityScriptNotice";} 
    EntityControlArray controls;  
    EntitySkillSystemArray skills;  
    EntityScriptNotice() 
    { 
    } 
    EntityScriptNotice(const EntityControlArray & controls, const EntitySkillSystemArray & skills) 
    { 
        this->controls = controls; 
        this->skills = skills; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityScriptNotice & data) 
{ 
    ws << data.controls;  
    ws << data.skills;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityScriptNotice & data) 
{ 
    rs >> data.controls;  
    rs >> data.skills;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityScriptNotice & info) 
{ 
    stm << "["; 
    stm << "controls=" << info.controls << ","; 
    stm << "skills=" << info.skills << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 
