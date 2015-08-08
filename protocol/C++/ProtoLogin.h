 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.account; 
    ws << data.token; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PlatAuthReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.account;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.token;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.users; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PlatAuthAck & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.retCode;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.users;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.nickName; 
    ws << data.iconID; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.nickName;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.iconID;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.users; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserAck & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.retCode;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.users;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.uID; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.uID;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 31ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.uID; 
    ws << data.token; 
    ws << data.ip; 
    ws << data.port; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserAck & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.retCode;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.uID;  
    } 
    if ( (1ULL << 2) & tag) 
    { 
        rs >> data.token;  
    } 
    if ( (1ULL << 3) & tag) 
    { 
        rs >> data.ip;  
    } 
    if ( (1ULL << 4) & tag) 
    { 
        rs >> data.port;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.uID; 
    ws << data.token; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LinkServerReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.uID;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.token;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LinkServerAck & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::byteRevese(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.retCode;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
#endif 
