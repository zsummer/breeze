 
#ifndef _PROTOSCENESERVER_H_ 
#define _PROTOSCENESERVER_H_ 
 
 
 
typedef std::vector<unsigned short> SceneTypeArray;  
 
struct SceneKnock //战场服务器挂载  
{ 
    static const unsigned short getProtoID() { return 39004;} 
    static const std::string getProtoName() { return "SceneKnock";} 
    unsigned int lineID; //分线ID  
    std::string pubHost;  
    unsigned short pubPort;  
    SceneKnock() 
    { 
        lineID = 0; 
        pubPort = 0; 
    } 
    SceneKnock(const unsigned int & lineID, const std::string & pubHost, const unsigned short & pubPort) 
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
    static const unsigned short getProtoID() { return 39005;} 
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
 
struct ApplyForSceneServerReq //请求战场  
{ 
    static const unsigned short getProtoID() { return 39007;} 
    static const std::string getProtoName() { return "ApplyForSceneServerReq";} 
    unsigned short sceneType; //类型  
    unsigned int mapID;  
    AvatarBaseInfoArray avatars; //匹配列表中的玩家  
    ApplyForSceneServerReq() 
    { 
        sceneType = 0; 
        mapID = 0; 
    } 
    ApplyForSceneServerReq(const unsigned short & sceneType, const unsigned int & mapID, const AvatarBaseInfoArray & avatars) 
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
    static const unsigned short getProtoID() { return 39006;} 
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
