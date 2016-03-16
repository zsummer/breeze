 
#ifndef _PROTOUSER_H_ 
#define _PROTOUSER_H_ 
 
 
struct AuthReq //认证请求  
{ 
    static const unsigned short GetProtoID() { return 1000;} 
    static const std::string GetProtoName() { return "ID_AuthReq";} 
    std::string account;  
    std::string token;  
    AuthReq() 
    { 
    } 
    AuthReq(const std::string & account, const std::string & token) 
    { 
        this->account = account; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AuthReq & data) 
{ 
    ws << data.account;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AuthReq & data) 
{ 
        rs >> data.account;  
        rs >> data.token;  
    return rs; 
} 
 
struct AuthResp //认证返回  
{ 
    static const unsigned short GetProtoID() { return 1001;} 
    static const std::string GetProtoName() { return "ID_AuthResp";} 
    unsigned short retCode;  
    UserPreviewArray previews;  
    AuthResp() 
    { 
        retCode = 0; 
    } 
    AuthResp(const unsigned short & retCode, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AuthResp & data) 
{ 
    ws << data.retCode;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AuthResp & data) 
{ 
        rs >> data.retCode;  
        rs >> data.previews;  
    return rs; 
} 
 
struct CreateUserReq //创角色请求  
{ 
    static const unsigned short GetProtoID() { return 1002;} 
    static const std::string GetProtoName() { return "ID_CreateUserReq";} 
    std::string nickname;  
    CreateUserReq() 
    { 
    } 
    CreateUserReq(const std::string & nickname) 
    { 
        this->nickname = nickname; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserReq & data) 
{ 
    ws << data.nickname;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserReq & data) 
{ 
        rs >> data.nickname;  
    return rs; 
} 
 
struct CreateUserResp //创角色请求返回  
{ 
    static const unsigned short GetProtoID() { return 1003;} 
    static const std::string GetProtoName() { return "ID_CreateUserResp";} 
    unsigned short retCode;  
    UserPreviewArray previews;  
    CreateUserResp() 
    { 
        retCode = 0; 
    } 
    CreateUserResp(const unsigned short & retCode, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserResp & data) 
{ 
    ws << data.retCode;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserResp & data) 
{ 
        rs >> data.retCode;  
        rs >> data.previews;  
    return rs; 
} 
 
struct SelectUserReq //选角色请求  
{ 
    static const unsigned short GetProtoID() { return 1004;} 
    static const std::string GetProtoName() { return "ID_SelectUserReq";} 
    unsigned long long uID;  
    SelectUserReq() 
    { 
        uID = 0; 
    } 
    SelectUserReq(const unsigned long long & uID) 
    { 
        this->uID = uID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserReq & data) 
{ 
    ws << data.uID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserReq & data) 
{ 
        rs >> data.uID;  
    return rs; 
} 
 
struct SelectUserResp //选角色请求返回  
{ 
    static const unsigned short GetProtoID() { return 1005;} 
    static const std::string GetProtoName() { return "ID_SelectUserResp";} 
    unsigned short retCode;  
    std::string svrIP;  
    unsigned short svrPort;  
    unsigned long long uID;  
    std::string token;  
    SelectUserResp() 
    { 
        retCode = 0; 
        svrPort = 0; 
        uID = 0; 
    } 
    SelectUserResp(const unsigned short & retCode, const std::string & svrIP, const unsigned short & svrPort, const unsigned long long & uID, const std::string & token) 
    { 
        this->retCode = retCode; 
        this->svrIP = svrIP; 
        this->svrPort = svrPort; 
        this->uID = uID; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserResp & data) 
{ 
    ws << data.retCode;  
    ws << data.svrIP;  
    ws << data.svrPort;  
    ws << data.uID;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserResp & data) 
{ 
        rs >> data.retCode;  
        rs >> data.svrIP;  
        rs >> data.svrPort;  
        rs >> data.uID;  
        rs >> data.token;  
    return rs; 
} 
 
struct LoginUserReq //登录角色请求  
{ 
    static const unsigned short GetProtoID() { return 1006;} 
    static const std::string GetProtoName() { return "ID_LoginUserReq";} 
    unsigned long long uID;  
    std::string token;  
    LoginUserReq() 
    { 
        uID = 0; 
    } 
    LoginUserReq(const unsigned long long & uID, const std::string & token) 
    { 
        this->uID = uID; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoginUserReq & data) 
{ 
    ws << data.uID;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoginUserReq & data) 
{ 
        rs >> data.uID;  
        rs >> data.token;  
    return rs; 
} 
 
struct LoginUserResp //登录角色返回  
{ 
    static const unsigned short GetProtoID() { return 1007;} 
    static const std::string GetProtoName() { return "ID_LoginUserResp";} 
    unsigned short retCode;  
    LoginUserResp() 
    { 
        retCode = 0; 
    } 
    LoginUserResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoginUserResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoginUserResp & data) 
{ 
        rs >> data.retCode;  
    return rs; 
} 
 
#endif 
