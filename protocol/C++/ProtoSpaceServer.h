 
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
 
struct FillUserToSpaceNotice //token丢给space  
{ 
    static const unsigned short getProtoID() { return 39012;} 
    static const std::string getProtoName() { return "FillUserToSpaceNotice";} 
    unsigned long long userID;  
    std::string token; //服务器port  
    SpaceID spaceID; //id  
    unsigned short sceneType; //类型  
    UserBaseInfo baseInfo; //类型  
    FillUserToSpaceNotice() 
    { 
        userID = 0; 
        sceneType = 0; 
    } 
    FillUserToSpaceNotice(const unsigned long long & userID, const std::string & token, const SpaceID & spaceID, const unsigned short & sceneType, const UserBaseInfo & baseInfo) 
    { 
        this->userID = userID; 
        this->token = token; 
        this->spaceID = spaceID; 
        this->sceneType = sceneType; 
        this->baseInfo = baseInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FillUserToSpaceNotice & data) 
{ 
    ws << data.userID;  
    ws << data.token;  
    ws << data.spaceID;  
    ws << data.sceneType;  
    ws << data.baseInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FillUserToSpaceNotice & data) 
{ 
    rs >> data.userID;  
    rs >> data.token;  
    rs >> data.spaceID;  
    rs >> data.sceneType;  
    rs >> data.baseInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FillUserToSpaceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
