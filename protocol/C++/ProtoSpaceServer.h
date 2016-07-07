 
#ifndef _PROTOSPACESERVER_H_ 
#define _PROTOSPACESERVER_H_ 
 
 
struct SpaceInfoToWorldNotice //数据刷给world  
{ 
    static const unsigned short getProtoID() { return 39010;} 
    static const std::string getProtoName() { return "SpaceInfoToWorldNotice";} 
    std::string host; //服务器host  
    unsigned short port; //服务器port  
    SpaceInfoArray spaceInfos; //类型  
    SpaceInfoToWorldNotice() 
    { 
        port = 0; 
    } 
    SpaceInfoToWorldNotice(const std::string & host, const unsigned short & port, const SpaceInfoArray & spaceInfos) 
    { 
        this->host = host; 
        this->port = port; 
        this->spaceInfos = spaceInfos; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SpaceInfoToWorldNotice & data) 
{ 
    ws << data.host;  
    ws << data.port;  
    ws << data.spaceInfos;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SpaceInfoToWorldNotice & data) 
{ 
    rs >> data.host;  
    rs >> data.port;  
    rs >> data.spaceInfos;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SpaceInfoToWorldNotice & info) 
{ 
    stm << "[\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "spaceInfos=" << info.spaceInfos << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct FillUserToSpaceReq //token丢给space  
{ 
    static const unsigned short getProtoID() { return 39013;} 
    static const std::string getProtoName() { return "FillUserToSpaceReq";} 
    SpaceID spaceID; //id  
    unsigned short sceneType; //类型  
    std::string token; //服务器port  
    UserBaseInfo baseInfo; //类型  
    FillUserToSpaceReq() 
    { 
        sceneType = 0; 
    } 
    FillUserToSpaceReq(const SpaceID & spaceID, const unsigned short & sceneType, const std::string & token, const UserBaseInfo & baseInfo) 
    { 
        this->spaceID = spaceID; 
        this->sceneType = sceneType; 
        this->token = token; 
        this->baseInfo = baseInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FillUserToSpaceReq & data) 
{ 
    ws << data.spaceID;  
    ws << data.sceneType;  
    ws << data.token;  
    ws << data.baseInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FillUserToSpaceReq & data) 
{ 
    rs >> data.spaceID;  
    rs >> data.sceneType;  
    rs >> data.token;  
    rs >> data.baseInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FillUserToSpaceReq & info) 
{ 
    stm << "[\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct FillUserToSpaceResp //token丢给space  
{ 
    static const unsigned short getProtoID() { return 39014;} 
    static const std::string getProtoName() { return "FillUserToSpaceResp";} 
    unsigned long long userID;  
    SpaceID spaceID; //id  
    unsigned short sceneType; //类型  
    FillUserToSpaceResp() 
    { 
        userID = 0; 
        sceneType = 0; 
    } 
    FillUserToSpaceResp(const unsigned long long & userID, const SpaceID & spaceID, const unsigned short & sceneType) 
    { 
        this->userID = userID; 
        this->spaceID = spaceID; 
        this->sceneType = sceneType; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FillUserToSpaceResp & data) 
{ 
    ws << data.userID;  
    ws << data.spaceID;  
    ws << data.sceneType;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FillUserToSpaceResp & data) 
{ 
    rs >> data.userID;  
    rs >> data.spaceID;  
    rs >> data.sceneType;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FillUserToSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
