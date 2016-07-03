 
#ifndef _PROTOSPACECLIENT_H_ 
#define _PROTOSPACECLIENT_H_ 
 
 
struct SceneInfoReq //获取场景信息  
{ 
    static const unsigned short getProtoID() { return 50000;} 
    static const std::string getProtoName() { return "SceneInfoReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfoReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfoReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfoReq & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneInfoAck //获取场景信息  
{ 
    static const unsigned short getProtoID() { return 50001;} 
    static const std::string getProtoName() { return "SceneInfoAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes;  
    SceneInfoAck() 
    { 
        retCode = 0; 
    } 
    SceneInfoAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfoAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfoAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfoAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct TryEnterSceneReq //进入场景  
{ 
    static const unsigned short getProtoID() { return 50002;} 
    static const std::string getProtoName() { return "TryEnterSceneReq";} 
    unsigned short type; //类型, 如果是不同类型,该请求会触发场景切换动作  
    TryEnterSceneReq() 
    { 
        type = 0; 
    } 
    TryEnterSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TryEnterSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TryEnterSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TryEnterSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct TryEnterSceneAck //进入场景  
{ 
    static const unsigned short getProtoID() { return 50003;} 
    static const std::string getProtoName() { return "TryEnterSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    TryEnterSceneAck() 
    { 
        retCode = 0; 
    } 
    TryEnterSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TryEnterSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TryEnterSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TryEnterSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SceneInfoNotice //场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中  
{ 
    static const unsigned short getProtoID() { return 50004;} 
    static const std::string getProtoName() { return "SceneInfoNotice";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    SceneInfoNotice() 
    { 
        retCode = 0; 
    } 
    SceneInfoNotice(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfoNotice & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfoNotice & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfoNotice & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSceneReq //离开场景  
{ 
    static const unsigned short getProtoID() { return 50005;} 
    static const std::string getProtoName() { return "LeaveSceneReq";} 
    unsigned short type; //类型  
    LeaveSceneReq() 
    { 
        type = 0; 
    } 
    LeaveSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSceneAck //离开场景  
{ 
    static const unsigned short getProtoID() { return 50006;} 
    static const std::string getProtoName() { return "LeaveSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    LeaveSceneAck() 
    { 
        retCode = 0; 
    } 
    LeaveSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct QuitSceneReq //退出场景  
{ 
    static const unsigned short getProtoID() { return 50007;} 
    static const std::string getProtoName() { return "QuitSceneReq";} 
    unsigned short type; //类型  
    QuitSceneReq() 
    { 
        type = 0; 
    } 
    QuitSceneReq(const unsigned short & type) 
    { 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const QuitSceneReq & data) 
{ 
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, QuitSceneReq & data) 
{ 
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const QuitSceneReq & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct QuitSceneAck //退出场景  
{ 
    static const unsigned short getProtoID() { return 50008;} 
    static const std::string getProtoName() { return "QuitSceneAck";} 
    unsigned short retCode; //错误码  
    SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
    QuitSceneAck() 
    { 
        retCode = 0; 
    } 
    QuitSceneAck(const unsigned short & retCode, const SceneInfoArray & scenes) 
    { 
        this->retCode = retCode; 
        this->scenes = scenes; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const QuitSceneAck & data) 
{ 
    ws << data.retCode;  
    ws << data.scenes;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, QuitSceneAck & data) 
{ 
    rs >> data.retCode;  
    rs >> data.scenes;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const QuitSceneAck & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "scenes=" << info.scenes << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
