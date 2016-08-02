 
#ifndef _PROTOCLIENT_H_ 
#define _PROTOCLIENT_H_ 
 
 
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
    AvatarPreviewArray previews;  
    ClientAuthResp() 
    { 
        retCode = 0; 
    } 
    ClientAuthResp(const unsigned short & retCode, const std::string & account, const std::string & token, const AvatarPreviewArray & previews) 
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
 
struct CreateAvatarReq //创角色请求  
{ 
    static const unsigned short getProtoID() { return 40003;} 
    static const std::string getProtoName() { return "CreateAvatarReq";} 
    std::string accountName; //这个字段会被服务器填充.客户端可以不填写  
    std::string userName;  
    CreateAvatarReq() 
    { 
    } 
    CreateAvatarReq(const std::string & accountName, const std::string & userName) 
    { 
        this->accountName = accountName; 
        this->userName = userName; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateAvatarReq & data) 
{ 
    ws << data.accountName;  
    ws << data.userName;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateAvatarReq & data) 
{ 
    rs >> data.accountName;  
    rs >> data.userName;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateAvatarReq & info) 
{ 
    stm << "[\n"; 
    stm << "accountName=" << info.accountName << "\n"; 
    stm << "userName=" << info.userName << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateAvatarResp //创角色请求返回  
{ 
    static const unsigned short getProtoID() { return 40004;} 
    static const std::string getProtoName() { return "CreateAvatarResp";} 
    unsigned short retCode;  
    unsigned long long avatarID;  
    AvatarPreviewArray previews;  
    CreateAvatarResp() 
    { 
        retCode = 0; 
        avatarID = 0; 
    } 
    CreateAvatarResp(const unsigned short & retCode, const unsigned long long & avatarID, const AvatarPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->avatarID = avatarID; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateAvatarResp & data) 
{ 
    ws << data.retCode;  
    ws << data.avatarID;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateAvatarResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.avatarID;  
    rs >> data.previews;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateAvatarResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "previews=" << info.previews << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachAvatarReq //选角色请求  
{ 
    static const unsigned short getProtoID() { return 40005;} 
    static const std::string getProtoName() { return "AttachAvatarReq";} 
    std::string accountName; //这个字段会被服务器填充.客户端可以不填写  
    unsigned long long avatarID;  
    AttachAvatarReq() 
    { 
        avatarID = 0; 
    } 
    AttachAvatarReq(const std::string & accountName, const unsigned long long & avatarID) 
    { 
        this->accountName = accountName; 
        this->avatarID = avatarID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachAvatarReq & data) 
{ 
    ws << data.accountName;  
    ws << data.avatarID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachAvatarReq & data) 
{ 
    rs >> data.accountName;  
    rs >> data.avatarID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachAvatarReq & info) 
{ 
    stm << "[\n"; 
    stm << "accountName=" << info.accountName << "\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachAvatarResp //选角色请求返回  
{ 
    static const unsigned short getProtoID() { return 40006;} 
    static const std::string getProtoName() { return "AttachAvatarResp";} 
    unsigned short retCode;  
    unsigned long long avatarID;  
    AttachAvatarResp() 
    { 
        retCode = 0; 
        avatarID = 0; 
    } 
    AttachAvatarResp(const unsigned short & retCode, const unsigned long long & avatarID) 
    { 
        this->retCode = retCode; 
        this->avatarID = avatarID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachAvatarResp & data) 
{ 
    ws << data.retCode;  
    ws << data.avatarID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachAvatarResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.avatarID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachAvatarResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct GetSpaceTokenInfoReq 
{ 
    static const unsigned short getProtoID() { return 40007;} 
    static const std::string getProtoName() { return "GetSpaceTokenInfoReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSpaceTokenInfoReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSpaceTokenInfoReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetSpaceTokenInfoReq & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct GetSpaceTokenInfoResp 
{ 
    static const unsigned short getProtoID() { return 40008;} 
    static const std::string getProtoName() { return "GetSpaceTokenInfoResp";} 
    unsigned short retCode;  
    SpaceTokenInfo tokenInfo;  
    GetSpaceTokenInfoResp() 
    { 
        retCode = 0; 
    } 
    GetSpaceTokenInfoResp(const unsigned short & retCode, const SpaceTokenInfo & tokenInfo) 
    { 
        this->retCode = retCode; 
        this->tokenInfo = tokenInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSpaceTokenInfoResp & data) 
{ 
    ws << data.retCode;  
    ws << data.tokenInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSpaceTokenInfoResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.tokenInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetSpaceTokenInfoResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "tokenInfo=" << info.tokenInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct JoinSpaceReq 
{ 
    static const unsigned short getProtoID() { return 40009;} 
    static const std::string getProtoName() { return "JoinSpaceReq";} 
    unsigned short spaceType;  
    unsigned int mapID;  
    JoinSpaceReq() 
    { 
        spaceType = 0; 
        mapID = 0; 
    } 
    JoinSpaceReq(const unsigned short & spaceType, const unsigned int & mapID) 
    { 
        this->spaceType = spaceType; 
        this->mapID = mapID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinSpaceReq & data) 
{ 
    ws << data.spaceType;  
    ws << data.mapID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinSpaceReq & data) 
{ 
    rs >> data.spaceType;  
    rs >> data.mapID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinSpaceReq & info) 
{ 
    stm << "[\n"; 
    stm << "spaceType=" << info.spaceType << "\n"; 
    stm << "mapID=" << info.mapID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct JoinSpaceResp 
{ 
    static const unsigned short getProtoID() { return 40010;} 
    static const std::string getProtoName() { return "JoinSpaceResp";} 
    unsigned short retCode;  
    SpaceTokenInfo tokenInfo;  
    JoinSpaceResp() 
    { 
        retCode = 0; 
    } 
    JoinSpaceResp(const unsigned short & retCode, const SpaceTokenInfo & tokenInfo) 
    { 
        this->retCode = retCode; 
        this->tokenInfo = tokenInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinSpaceResp & data) 
{ 
    ws << data.retCode;  
    ws << data.tokenInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinSpaceResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.tokenInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "tokenInfo=" << info.tokenInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct JoinSpaceNotice 
{ 
    static const unsigned short getProtoID() { return 40011;} 
    static const std::string getProtoName() { return "JoinSpaceNotice";} 
    SpaceTokenInfo tokenInfo;  
    JoinSpaceNotice() 
    { 
    } 
    JoinSpaceNotice(const SpaceTokenInfo & tokenInfo) 
    { 
        this->tokenInfo = tokenInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinSpaceNotice & data) 
{ 
    ws << data.tokenInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinSpaceNotice & data) 
{ 
    rs >> data.tokenInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinSpaceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "tokenInfo=" << info.tokenInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSpaceReq 
{ 
    static const unsigned short getProtoID() { return 40012;} 
    static const std::string getProtoName() { return "LeaveSpaceReq";} 
    unsigned int spaceID;  
    LeaveSpaceReq() 
    { 
        spaceID = 0; 
    } 
    LeaveSpaceReq(const unsigned int & spaceID) 
    { 
        this->spaceID = spaceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSpaceReq & data) 
{ 
    ws << data.spaceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSpaceReq & data) 
{ 
    rs >> data.spaceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSpaceReq & info) 
{ 
    stm << "[\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSpaceResp 
{ 
    static const unsigned short getProtoID() { return 40013;} 
    static const std::string getProtoName() { return "LeaveSpaceResp";} 
    unsigned short retCode;  
    SpaceTokenInfo tokenInfo;  
    LeaveSpaceResp() 
    { 
        retCode = 0; 
    } 
    LeaveSpaceResp(const unsigned short & retCode, const SpaceTokenInfo & tokenInfo) 
    { 
        this->retCode = retCode; 
        this->tokenInfo = tokenInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSpaceResp & data) 
{ 
    ws << data.retCode;  
    ws << data.tokenInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSpaceResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.tokenInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "tokenInfo=" << info.tokenInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ChatReq 
{ 
    static const unsigned short getProtoID() { return 40014;} 
    static const std::string getProtoName() { return "ChatReq";} 
    unsigned long long avatarID;  
    std::string msg;  
    ChatReq() 
    { 
        avatarID = 0; 
    } 
    ChatReq(const unsigned long long & avatarID, const std::string & msg) 
    { 
        this->avatarID = avatarID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatReq & data) 
{ 
    ws << data.avatarID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatReq & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatReq & info) 
{ 
    stm << "[\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ChatResp 
{ 
    static const unsigned short getProtoID() { return 40015;} 
    static const std::string getProtoName() { return "ChatResp";} 
    unsigned long long fromAvatarID;  
    std::string msg;  
    ChatResp() 
    { 
        fromAvatarID = 0; 
    } 
    ChatResp(const unsigned long long & fromAvatarID, const std::string & msg) 
    { 
        this->fromAvatarID = fromAvatarID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatResp & data) 
{ 
    ws << data.fromAvatarID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatResp & data) 
{ 
    rs >> data.fromAvatarID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatResp & info) 
{ 
    stm << "[\n"; 
    stm << "fromAvatarID=" << info.fromAvatarID << "\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct PingPongReq 
{ 
    static const unsigned short getProtoID() { return 40016;} 
    static const std::string getProtoName() { return "PingPongReq";} 
    std::string msg;  
    PingPongReq() 
    { 
    } 
    PingPongReq(const std::string & msg) 
    { 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PingPongReq & data) 
{ 
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PingPongReq & data) 
{ 
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const PingPongReq & info) 
{ 
    stm << "[\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct PingPongResp 
{ 
    static const unsigned short getProtoID() { return 40017;} 
    static const std::string getProtoName() { return "PingPongResp";} 
    std::string msg;  
    PingPongResp() 
    { 
    } 
    PingPongResp(const std::string & msg) 
    { 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PingPongResp & data) 
{ 
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PingPongResp & data) 
{ 
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const PingPongResp & info) 
{ 
    stm << "[\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
