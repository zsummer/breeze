 
#ifndef _PROTOSCENESERVER_H_ 
#define _PROTOSCENESERVER_H_ 
 
 
struct AllocateSceneReq //分配新战场  
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
 
struct AllocateSceneResp //分配新战场  
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
