 
#ifndef _PROTOSPACE_H_ 
#define _PROTOSPACE_H_ 
 
 
enum SCENE_STATUS : unsigned short 
{ 
    SCENE_STATUS_NONE = 0, //无效  
    SCENE_STATUS_HOME = 1, //主城  
    SCENE_STATUS_INSTANCING = 2, //副本  
    SCENE_STATUS_ARENA = 3, //竞技场  
}; 
 
struct SceneStatus //场景状态数据  
{ 
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "SceneStatus";} 
    unsigned short type; //类型  
    unsigned short state; //状态  
    std::string host; //服务器host  
    unsigned short port; //服务器port  
    unsigned int spaceID; //空间(场景,房间,战场)的实例ID  
    SessionToken token; //令牌  
    SceneStatus() 
    { 
        type = 0; 
        state = 0; 
        port = 0; 
        spaceID = 0; 
    } 
    SceneStatus(const unsigned short & type, const unsigned short & state, const std::string & host, const unsigned short & port, const unsigned int & spaceID, const SessionToken & token) 
    { 
        this->type = type; 
        this->state = state; 
        this->host = host; 
        this->port = port; 
        this->spaceID = spaceID; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneStatus & data) 
{ 
    ws << data.type;  
    ws << data.state;  
    ws << data.host;  
    ws << data.port;  
    ws << data.spaceID;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneStatus & data) 
{ 
    rs >> data.type;  
    rs >> data.state;  
    rs >> data.host;  
    rs >> data.port;  
    rs >> data.spaceID;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneStatus & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "state=" << info.state << "\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
