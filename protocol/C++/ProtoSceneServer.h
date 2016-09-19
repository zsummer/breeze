 
#ifndef _PROTOSCENESERVER_H_ 
#define _PROTOSCENESERVER_H_ 
 
 
 
typedef std::vector<unsigned short> SceneTypeArray;  
 
struct SceneKnock //战场服务器挂载  
{ 
    static const unsigned short getProtoID() { return 39004;} 
    static const std::string getProtoName() { return "SceneKnock";} 
    unsigned int sceneID; //断线检测  
    std::string pubHost;  
    unsigned short pubPort;  
    SceneKnock() 
    { 
        sceneID = 0; 
        pubPort = 0; 
    } 
    SceneKnock(const unsigned int & sceneID, const std::string & pubHost, const unsigned short & pubPort) 
    { 
        this->sceneID = sceneID; 
        this->pubHost = pubHost; 
        this->pubPort = pubPort; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneKnock & data) 
{ 
    ws << data.sceneID;  
    ws << data.pubHost;  
    ws << data.pubPort;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneKnock & data) 
{ 
    rs >> data.sceneID;  
    rs >> data.pubHost;  
    rs >> data.pubPort;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneKnock & info) 
{ 
    stm << "[\n"; 
    stm << "sceneID=" << info.sceneID << "\n"; 
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
 
struct AllocateSceneReq //分配战场  
{ 
    static const unsigned short getProtoID() { return 39000;} 
    static const std::string getProtoName() { return "AllocateSceneReq";} 
    unsigned short sceneType; //类型  
    unsigned int mapID;  
    AvatarBaseInfoArray involeds; //匹配列表中的玩家  
    AllocateSceneReq() 
    { 
        sceneType = 0; 
        mapID = 0; 
    } 
    AllocateSceneReq(const unsigned short & sceneType, const unsigned int & mapID, const AvatarBaseInfoArray & involeds) 
    { 
        this->sceneType = sceneType; 
        this->mapID = mapID; 
        this->involeds = involeds; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AllocateSceneReq & data) 
{ 
    ws << data.sceneType;  
    ws << data.mapID;  
    ws << data.involeds;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AllocateSceneReq & data) 
{ 
    rs >> data.sceneType;  
    rs >> data.mapID;  
    rs >> data.involeds;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AllocateSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "mapID=" << info.mapID << "\n"; 
    stm << "involeds=" << info.involeds << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AllocateSceneResp //分配战场  
{ 
    static const unsigned short getProtoID() { return 39001;} 
    static const std::string getProtoName() { return "AllocateSceneResp";} 
    unsigned short retCode;  
    SceneTokenInfoArray tokens; //匹配列表中的玩家  
    AllocateSceneResp() 
    { 
        retCode = 0; 
    } 
    AllocateSceneResp(const unsigned short & retCode, const SceneTokenInfoArray & tokens) 
    { 
        this->retCode = retCode; 
        this->tokens = tokens; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AllocateSceneResp & data) 
{ 
    ws << data.retCode;  
    ws << data.tokens;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AllocateSceneResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.tokens;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AllocateSceneResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "tokens=" << info.tokens << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
