 
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
    AvatarPropMap props; //角色属性数据  
    SceneServerJoinGroupIns() 
    { 
        groupID = 0; 
    } 
    SceneServerJoinGroupIns(const unsigned long long & groupID, const AvatarBaseInfo & baseInfo, const AvatarPropMap & props) 
    { 
        this->groupID = groupID; 
        this->baseInfo = baseInfo; 
        this->props = props; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneServerJoinGroupIns & data) 
{ 
    ws << data.groupID;  
    ws << data.baseInfo;  
    ws << data.props;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneServerJoinGroupIns & data) 
{ 
    rs >> data.groupID;  
    rs >> data.baseInfo;  
    rs >> data.props;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneServerJoinGroupIns & info) 
{ 
    stm << "[\n"; 
    stm << "groupID=" << info.groupID << "\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "props=" << info.props << "\n"; 
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
 
struct ApplyForSceneServerReq //请求战场  
{ 
    static const unsigned short getProtoID() { return 39004;} 
    static const std::string getProtoName() { return "ApplyForSceneServerReq";} 
    unsigned short sceneType; //类型  
    unsigned long long mapID;  
    AvatarBaseInfoArray avatars; //匹配列表中的玩家  
    ApplyForSceneServerReq() 
    { 
        sceneType = 0; 
        mapID = 0; 
    } 
    ApplyForSceneServerReq(const unsigned short & sceneType, const unsigned long long & mapID, const AvatarBaseInfoArray & avatars) 
    { 
        this->sceneType = sceneType; 
        this->mapID = mapID; 
        this->avatars = avatars; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ApplyForSceneServerReq & data) 
{ 
    ws << data.sceneType;  
    ws << data.mapID;  
    ws << data.avatars;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ApplyForSceneServerReq & data) 
{ 
    rs >> data.sceneType;  
    rs >> data.mapID;  
    rs >> data.avatars;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ApplyForSceneServerReq & info) 
{ 
    stm << "[\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "mapID=" << info.mapID << "\n"; 
    stm << "avatars=" << info.avatars << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct FeedbackAvatarStatusNotice //scene ==> world  
{ 
    static const unsigned short getProtoID() { return 39005;} 
    static const std::string getProtoName() { return "FeedbackAvatarStatusNotice";} 
    unsigned long long avatarID;  
    unsigned short status;  
    std::string token;  
    FeedbackAvatarStatusNotice() 
    { 
        avatarID = 0; 
        status = 0; 
    } 
    FeedbackAvatarStatusNotice(const unsigned long long & avatarID, const unsigned short & status, const std::string & token) 
    { 
        this->avatarID = avatarID; 
        this->status = status; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FeedbackAvatarStatusNotice & data) 
{ 
    ws << data.avatarID;  
    ws << data.status;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FeedbackAvatarStatusNotice & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.status;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FeedbackAvatarStatusNotice & info) 
{ 
    stm << "[\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "status=" << info.status << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
