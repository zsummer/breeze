 
#ifndef _PROTOLOGIN_H_ 
#define _PROTOLOGIN_H_ 
 
 
const unsigned short ID_PlatAuthReq = 100; //平台认证 
struct PlatAuthReq //平台认证 
{ 
    std::string account; //用户名 
    std::string token; //令牌 
    static const unsigned short GetProtoID() { return 100;} 
    static const std::string GetProtoName() { return "ID_PlatAuthReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PlatAuthReq & data) 
{ 
    ws << data.account; 
    ws << data.token; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PlatAuthReq & data) 
{ 
        rs >> data.account;  
        rs >> data.token;  
    return rs; 
} 
 
const unsigned short ID_PlatAuthAck = 101; //认证结果, 包含该用户的所有用户/角色数据 
struct PlatAuthAck //认证结果, 包含该用户的所有用户/角色数据 
{ 
    unsigned short retCode;  
    UserInfoArray users; //该帐号下的所有用户信息 
    PlatAuthAck() 
    { 
        retCode = 0; 
    } 
    static const unsigned short GetProtoID() { return 101;} 
    static const std::string GetProtoName() { return "ID_PlatAuthAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PlatAuthAck & data) 
{ 
    ws << data.retCode; 
    ws << data.users; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PlatAuthAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.users;  
    return rs; 
} 
 
const unsigned short ID_CreateUserReq = 102; //创建一个新的用户数据 
struct CreateUserReq //创建一个新的用户数据 
{ 
    std::string nickName; //昵称 
    int iconID; //头像 
    CreateUserReq() 
    { 
        iconID = 0; 
    } 
    static const unsigned short GetProtoID() { return 102;} 
    static const std::string GetProtoName() { return "ID_CreateUserReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserReq & data) 
{ 
    ws << data.nickName; 
    ws << data.iconID; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserReq & data) 
{ 
        rs >> data.nickName;  
        rs >> data.iconID;  
    return rs; 
} 
 
const unsigned short ID_CreateUserAck = 103; //创建结果和所有用户数据 
struct CreateUserAck //创建结果和所有用户数据 
{ 
    unsigned short retCode;  
    UserInfoArray users; //该帐号下的所有用户信息 
    CreateUserAck() 
    { 
        retCode = 0; 
    } 
    static const unsigned short GetProtoID() { return 103;} 
    static const std::string GetProtoName() { return "ID_CreateUserAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserAck & data) 
{ 
    ws << data.retCode; 
    ws << data.users; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.users;  
    return rs; 
} 
 
const unsigned short ID_SelectUserReq = 104; //获取需要登录用户的所在服务器和认证令牌 
struct SelectUserReq //获取需要登录用户的所在服务器和认证令牌 
{ 
    unsigned long long uID;  
    SelectUserReq() 
    { 
        uID = 0; 
    } 
    static const unsigned short GetProtoID() { return 104;} 
    static const std::string GetProtoName() { return "ID_SelectUserReq";} 
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
 
const unsigned short ID_SelectUserAck = 105; //获取需要登录用户的所在服务器和认证令牌 
struct SelectUserAck //获取需要登录用户的所在服务器和认证令牌 
{ 
    unsigned short retCode;  
    unsigned long long uID;  
    std::string token;  
    std::string ip;  
    unsigned short port;  
    SelectUserAck() 
    { 
        retCode = 0; 
        uID = 0; 
        port = 0; 
    } 
    static const unsigned short GetProtoID() { return 105;} 
    static const std::string GetProtoName() { return "ID_SelectUserAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserAck & data) 
{ 
    ws << data.retCode; 
    ws << data.uID; 
    ws << data.token; 
    ws << data.ip; 
    ws << data.port; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.uID;  
        rs >> data.token;  
        rs >> data.ip;  
        rs >> data.port;  
    return rs; 
} 
 
const unsigned short ID_LinkServerReq = 106; //连接到服务器 
struct LinkServerReq //连接到服务器 
{ 
    unsigned long long uID;  
    std::string token;  
    LinkServerReq() 
    { 
        uID = 0; 
    } 
    static const unsigned short GetProtoID() { return 106;} 
    static const std::string GetProtoName() { return "ID_LinkServerReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LinkServerReq & data) 
{ 
    ws << data.uID; 
    ws << data.token; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LinkServerReq & data) 
{ 
        rs >> data.uID;  
        rs >> data.token;  
    return rs; 
} 
 
const unsigned short ID_LinkServerAck = 107; //连接到服务器 
struct LinkServerAck //连接到服务器 
{ 
    unsigned short retCode;  
    LinkServerAck() 
    { 
        retCode = 0; 
    } 
    static const unsigned short GetProtoID() { return 107;} 
    static const std::string GetProtoName() { return "ID_LinkServerAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LinkServerAck & data) 
{ 
    ws << data.retCode; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LinkServerAck & data) 
{ 
        rs >> data.retCode;  
    return rs; 
} 
 
#endif 
