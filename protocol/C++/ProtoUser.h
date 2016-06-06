 
#ifndef _PROTOUSER_H_ 
#define _PROTOUSER_H_ 
 
 
struct ClientPulse //客户端脉冲请求  
{ 
    static const unsigned short getProtoID() { return 40000;} 
    static const std::string getProtoName() { return "ClientPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientPulse & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientPulse & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientPulse & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClientAuthReq //认证请求  
{ 
    static const unsigned short getProtoID() { return 40001;} 
    static const std::string getProtoName() { return "ClientAuthReq";} 
    std::string account;  
    std::string token;  
    ClientAuthReq() 
    { 
    } 
    ClientAuthReq(const std::string & account, const std::string & token) 
    { 
        this->account = account; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientAuthReq & data) 
{ 
    ws << data.account;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientAuthReq & data) 
{ 
    rs >> data.account;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientAuthReq & info) 
{ 
    stm << "[\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ClientAuthResp //认证返回  
{ 
    static const unsigned short getProtoID() { return 40002;} 
    static const std::string getProtoName() { return "ClientAuthResp";} 
    unsigned short retCode;  
    std::string account;  
    std::string token;  
    UserPreviewArray previews;  
    ClientAuthResp() 
    { 
        retCode = 0; 
    } 
    ClientAuthResp(const unsigned short & retCode, const std::string & account, const std::string & token, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->account = account; 
        this->token = token; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ClientAuthResp & data) 
{ 
    ws << data.retCode;  
    ws << data.account;  
    ws << data.token;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ClientAuthResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.account;  
    rs >> data.token;  
    rs >> data.previews;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ClientAuthResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "previews=" << info.previews << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateUserReq //创角色请求  
{ 
    static const unsigned short getProtoID() { return 40003;} 
    static const std::string getProtoName() { return "CreateUserReq";} 
    std::string serviceName;  
    CreateUserReq() 
    { 
    } 
    CreateUserReq(const std::string & serviceName) 
    { 
        this->serviceName = serviceName; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserReq & data) 
{ 
    ws << data.serviceName;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserReq & data) 
{ 
    rs >> data.serviceName;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserReq & info) 
{ 
    stm << "[\n"; 
    stm << "serviceName=" << info.serviceName << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateUserResp //创角色请求返回  
{ 
    static const unsigned short getProtoID() { return 40004;} 
    static const std::string getProtoName() { return "CreateUserResp";} 
    unsigned short retCode;  
    unsigned long long serviceID;  
    UserPreviewArray previews;  
    CreateUserResp() 
    { 
        retCode = 0; 
        serviceID = 0; 
    } 
    CreateUserResp(const unsigned short & retCode, const unsigned long long & serviceID, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->serviceID = serviceID; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserResp & data) 
{ 
    ws << data.retCode;  
    ws << data.serviceID;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.serviceID;  
    rs >> data.previews;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "previews=" << info.previews << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachUserReq //选角色请求  
{ 
    static const unsigned short getProtoID() { return 40005;} 
    static const std::string getProtoName() { return "AttachUserReq";} 
    unsigned long long serviceID;  
    AttachUserReq() 
    { 
        serviceID = 0; 
    } 
    AttachUserReq(const unsigned long long & serviceID) 
    { 
        this->serviceID = serviceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachUserReq & data) 
{ 
    ws << data.serviceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachUserReq & data) 
{ 
    rs >> data.serviceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachUserReq & info) 
{ 
    stm << "[\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachUserResp //选角色请求返回  
{ 
    static const unsigned short getProtoID() { return 40006;} 
    static const std::string getProtoName() { return "AttachUserResp";} 
    unsigned short retCode;  
    AttachUserResp() 
    { 
        retCode = 0; 
    } 
    AttachUserResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachUserResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachUserResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachUserResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserChatReq 
{ 
    static const unsigned short getProtoID() { return 40007;} 
    static const std::string getProtoName() { return "UserChatReq";} 
    unsigned long long toServiceID;  
    std::string msg;  
    UserChatReq() 
    { 
        toServiceID = 0; 
    } 
    UserChatReq(const unsigned long long & toServiceID, const std::string & msg) 
    { 
        this->toServiceID = toServiceID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserChatReq & data) 
{ 
    ws << data.toServiceID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserChatReq & data) 
{ 
    rs >> data.toServiceID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserChatReq & info) 
{ 
    stm << "[\n"; 
    stm << "toServiceID=" << info.toServiceID << "\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserChatResp 
{ 
    static const unsigned short getProtoID() { return 40008;} 
    static const std::string getProtoName() { return "UserChatResp";} 
    unsigned long long fromServiceID;  
    std::string msg;  
    UserChatResp() 
    { 
        fromServiceID = 0; 
    } 
    UserChatResp(const unsigned long long & fromServiceID, const std::string & msg) 
    { 
        this->fromServiceID = fromServiceID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserChatResp & data) 
{ 
    ws << data.fromServiceID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserChatResp & data) 
{ 
    rs >> data.fromServiceID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserChatResp & info) 
{ 
    stm << "[\n"; 
    stm << "fromServiceID=" << info.fromServiceID << "\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserPingPongReq 
{ 
    static const unsigned short getProtoID() { return 40009;} 
    static const std::string getProtoName() { return "UserPingPongReq";} 
    std::string msg;  
    UserPingPongReq() 
    { 
    } 
    UserPingPongReq(const std::string & msg) 
    { 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserPingPongReq & data) 
{ 
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserPingPongReq & data) 
{ 
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserPingPongReq & info) 
{ 
    stm << "[\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserPingPongResp 
{ 
    static const unsigned short getProtoID() { return 40010;} 
    static const std::string getProtoName() { return "UserPingPongResp";} 
    std::string msg;  
    UserPingPongResp() 
    { 
    } 
    UserPingPongResp(const std::string & msg) 
    { 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserPingPongResp & data) 
{ 
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserPingPongResp & data) 
{ 
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserPingPongResp & info) 
{ 
    stm << "[\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
