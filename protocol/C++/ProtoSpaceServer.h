 
#ifndef _PROTOSPACESERVER_H_ 
#define _PROTOSPACESERVER_H_ 
 
 
struct AllocateSpaceReq //分配新战场  
{ 
    static const unsigned short getProtoID() { return 39015;} 
    static const std::string getProtoName() { return "AllocateSpaceReq";} 
    unsigned short spaceType; //类型  
    unsigned int mapID;  
    AvatarBaseInfoArray involeds; //匹配列表中的玩家  
    AllocateSpaceReq() 
    { 
        spaceType = 0; 
        mapID = 0; 
    } 
    AllocateSpaceReq(const unsigned short & spaceType, const unsigned int & mapID, const AvatarBaseInfoArray & involeds) 
    { 
        this->spaceType = spaceType; 
        this->mapID = mapID; 
        this->involeds = involeds; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AllocateSpaceReq & data) 
{ 
    ws << data.spaceType;  
    ws << data.mapID;  
    ws << data.involeds;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AllocateSpaceReq & data) 
{ 
    rs >> data.spaceType;  
    rs >> data.mapID;  
    rs >> data.involeds;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AllocateSpaceReq & info) 
{ 
    stm << "[\n"; 
    stm << "spaceType=" << info.spaceType << "\n"; 
    stm << "mapID=" << info.mapID << "\n"; 
    stm << "involeds=" << info.involeds << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AllocateSpaceResp //分配新战场  
{ 
    static const unsigned short getProtoID() { return 39016;} 
    static const std::string getProtoName() { return "AllocateSpaceResp";} 
    unsigned short retCode;  
    SpaceTokenInfoArray tokens; //匹配列表中的玩家  
    AllocateSpaceResp() 
    { 
        retCode = 0; 
    } 
    AllocateSpaceResp(const unsigned short & retCode, const SpaceTokenInfoArray & tokens) 
    { 
        this->retCode = retCode; 
        this->tokens = tokens; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AllocateSpaceResp & data) 
{ 
    ws << data.retCode;  
    ws << data.tokens;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AllocateSpaceResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.tokens;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AllocateSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "tokens=" << info.tokens << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
