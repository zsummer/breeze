 
#ifndef _PROTOSPACESERVER_H_ 
#define _PROTOSPACESERVER_H_ 
 
 
struct WorldSceneInfoReq //获取场景信息  
{ 
    static const unsigned short getProtoID() { return 39000;} 
    static const std::string getProtoName() { return "WorldSceneInfoReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldSceneInfoReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldSceneInfoReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldSceneInfoReq & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldSceneInfoAck //获取场景信息  
{ 
    static const unsigned short getProtoID() { return 39001;} 
    static const std::string getProtoName() { return "WorldSceneInfoAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes;  
    WorldSceneInfoAck() 
    { 
        retCode = 0; 
    } 
    WorldSceneInfoAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldSceneInfoAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldSceneInfoAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldSceneInfoAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldTryEnterSceneReq //进入场景  
{ 
    static const unsigned short getProtoID() { return 39002;} 
    static const std::string getProtoName() { return "WorldTryEnterSceneReq";} 
    unsigned short type; //类型, 如果是不同类型,该请求会触发场景切换动作  
    WorldTryEnterSceneReq() 
    { 
        type = 0; 
    } 
    WorldTryEnterSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldTryEnterSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldTryEnterSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldTryEnterSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldTryEnterSceneAck //进入场景  
{ 
    static const unsigned short getProtoID() { return 39003;} 
    static const std::string getProtoName() { return "WorldTryEnterSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    WorldTryEnterSceneAck() 
    { 
        retCode = 0; 
    } 
    WorldTryEnterSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldTryEnterSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldTryEnterSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldTryEnterSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldSceneInfoNotice //场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中  
{ 
    static const unsigned short getProtoID() { return 39004;} 
    static const std::string getProtoName() { return "WorldSceneInfoNotice";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    WorldSceneInfoNotice() 
    { 
        retCode = 0; 
    } 
    WorldSceneInfoNotice(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldSceneInfoNotice & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldSceneInfoNotice & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldSceneInfoNotice & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldLeaveSceneReq //离开场景  
{ 
    static const unsigned short getProtoID() { return 39005;} 
    static const std::string getProtoName() { return "WorldLeaveSceneReq";} 
    unsigned short type; //类型  
    WorldLeaveSceneReq() 
    { 
        type = 0; 
    } 
    WorldLeaveSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldLeaveSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldLeaveSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldLeaveSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldLeaveSceneAck //离开场景  
{ 
    static const unsigned short getProtoID() { return 39006;} 
    static const std::string getProtoName() { return "WorldLeaveSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    WorldLeaveSceneAck() 
    { 
        retCode = 0; 
    } 
    WorldLeaveSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldLeaveSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldLeaveSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldLeaveSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldQuitSceneReq //退出场景  
{ 
    static const unsigned short getProtoID() { return 39007;} 
    static const std::string getProtoName() { return "WorldQuitSceneReq";} 
    unsigned short type; //类型  
    WorldQuitSceneReq() 
    { 
        type = 0; 
    } 
    WorldQuitSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldQuitSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldQuitSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldQuitSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WorldQuitSceneAck //退出场景  
{ 
    static const unsigned short getProtoID() { return 39008;} 
    static const std::string getProtoName() { return "WorldQuitSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    WorldQuitSceneAck() 
    { 
        retCode = 0; 
    } 
    WorldQuitSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WorldQuitSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WorldQuitSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WorldQuitSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
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
 
struct TokenInfoToSpaceNotice //token丢给space  
{ 
    static const unsigned short getProtoID() { return 39011;} 
    static const std::string getProtoName() { return "TokenInfoToSpaceNotice";} 
    unsigned long long userID;  
    std::string token; //服务器port  
    spaceID spaceID; //类型  
    UserBaseInfo baseInfo; //类型  
    FightEffect effects; //类型  
    TokenInfoToSpaceNotice() 
    { 
        userID = 0; 
    } 
    TokenInfoToSpaceNotice(const unsigned long long & userID, const std::string & token, const spaceID & spaceID, const UserBaseInfo & baseInfo, const FightEffect & effects) 
    { 
        this->userID = userID; 
        this->token = token; 
        this->spaceID = spaceID; 
        this->baseInfo = baseInfo; 
        this->effects = effects; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TokenInfoToSpaceNotice & data) 
{ 
    ws << data.userID;  
    ws << data.token;  
    ws << data.spaceID;  
    ws << data.baseInfo;  
    ws << data.effects;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TokenInfoToSpaceNotice & data) 
{ 
    rs >> data.userID;  
    rs >> data.token;  
    rs >> data.spaceID;  
    rs >> data.baseInfo;  
    rs >> data.effects;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TokenInfoToSpaceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "effects=" << info.effects << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
