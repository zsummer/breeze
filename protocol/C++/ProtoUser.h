 
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
    std::string accountName; //这个字段会被服务器填充.客户端可以不填写  
    std::string userName;  
    CreateUserReq() 
    { 
    } 
    CreateUserReq(const std::string & accountName, const std::string & userName) 
    { 
        this->accountName = accountName; 
        this->userName = userName; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserReq & data) 
{ 
    ws << data.accountName;  
    ws << data.userName;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserReq & data) 
{ 
    rs >> data.accountName;  
    rs >> data.userName;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserReq & info) 
{ 
    stm << "[\n"; 
    stm << "accountName=" << info.accountName << "\n"; 
    stm << "userName=" << info.userName << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateUserResp //创角色请求返回  
{ 
    static const unsigned short getProtoID() { return 40004;} 
    static const std::string getProtoName() { return "CreateUserResp";} 
    unsigned short retCode;  
    unsigned long long userID;  
    UserPreviewArray previews;  
    CreateUserResp() 
    { 
        retCode = 0; 
        userID = 0; 
    } 
    CreateUserResp(const unsigned short & retCode, const unsigned long long & userID, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->userID = userID; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserResp & data) 
{ 
    ws << data.retCode;  
    ws << data.userID;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.userID;  
    rs >> data.previews;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "previews=" << info.previews << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachUserReq //选角色请求  
{ 
    static const unsigned short getProtoID() { return 40005;} 
    static const std::string getProtoName() { return "AttachUserReq";} 
    std::string accountName; //这个字段会被服务器填充.客户端可以不填写  
    unsigned long long userID;  
    AttachUserReq() 
    { 
        userID = 0; 
    } 
    AttachUserReq(const std::string & accountName, const unsigned long long & userID) 
    { 
        this->accountName = accountName; 
        this->userID = userID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachUserReq & data) 
{ 
    ws << data.accountName;  
    ws << data.userID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachUserReq & data) 
{ 
    rs >> data.accountName;  
    rs >> data.userID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachUserReq & info) 
{ 
    stm << "[\n"; 
    stm << "accountName=" << info.accountName << "\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachUserResp //选角色请求返回  
{ 
    static const unsigned short getProtoID() { return 40006;} 
    static const std::string getProtoName() { return "AttachUserResp";} 
    unsigned short retCode;  
    unsigned long long userID;  
    AttachUserResp() 
    { 
        retCode = 0; 
        userID = 0; 
    } 
    AttachUserResp(const unsigned short & retCode, const unsigned long long & userID) 
    { 
        this->retCode = retCode; 
        this->userID = userID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachUserResp & data) 
{ 
    ws << data.retCode;  
    ws << data.userID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachUserResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.userID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachUserResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct GetSpaceInfoReq 
{ 
    static const unsigned short getProtoID() { return 40022;} 
    static const std::string getProtoName() { return "GetSpaceInfoReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSpaceInfoReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSpaceInfoReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetSpaceInfoReq & info) 
{ 
    stm << "[\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct GetSpaceInfoResp 
{ 
    static const unsigned short getProtoID() { return 40023;} 
    static const std::string getProtoName() { return "GetSpaceInfoResp";} 
    SpaceTokenInfo spaceInfo;  
    GetSpaceInfoResp() 
    { 
    } 
    GetSpaceInfoResp(const SpaceTokenInfo & spaceInfo) 
    { 
        this->spaceInfo = spaceInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSpaceInfoResp & data) 
{ 
    ws << data.spaceInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSpaceInfoResp & data) 
{ 
    rs >> data.spaceInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetSpaceInfoResp & info) 
{ 
    stm << "[\n"; 
    stm << "spaceInfo=" << info.spaceInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct JoinSpaceReq 
{ 
    static const unsigned short getProtoID() { return 40020;} 
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
    static const unsigned short getProtoID() { return 40021;} 
    static const std::string getProtoName() { return "JoinSpaceResp";} 
    unsigned short retCode;  
    SpaceTokenInfo spaceInfo;  
    JoinSpaceResp() 
    { 
        retCode = 0; 
    } 
    JoinSpaceResp(const unsigned short & retCode, const SpaceTokenInfo & spaceInfo) 
    { 
        this->retCode = retCode; 
        this->spaceInfo = spaceInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinSpaceResp & data) 
{ 
    ws << data.retCode;  
    ws << data.spaceInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinSpaceResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.spaceInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "spaceInfo=" << info.spaceInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct JoinSpaceNotice 
{ 
    static const unsigned short getProtoID() { return 40024;} 
    static const std::string getProtoName() { return "JoinSpaceNotice";} 
    SpaceTokenInfo spaceInfo;  
    JoinSpaceNotice() 
    { 
    } 
    JoinSpaceNotice(const SpaceTokenInfo & spaceInfo) 
    { 
        this->spaceInfo = spaceInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinSpaceNotice & data) 
{ 
    ws << data.spaceInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinSpaceNotice & data) 
{ 
    rs >> data.spaceInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinSpaceNotice & info) 
{ 
    stm << "[\n"; 
    stm << "spaceInfo=" << info.spaceInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct LeaveSpaceReq 
{ 
    static const unsigned short getProtoID() { return 40025;} 
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
    static const unsigned short getProtoID() { return 40026;} 
    static const std::string getProtoName() { return "LeaveSpaceResp";} 
    unsigned short retCode;  
    SpaceTokenInfo spaceInfo;  
    LeaveSpaceResp() 
    { 
        retCode = 0; 
    } 
    LeaveSpaceResp(const unsigned short & retCode, const SpaceTokenInfo & spaceInfo) 
    { 
        this->retCode = retCode; 
        this->spaceInfo = spaceInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveSpaceResp & data) 
{ 
    ws << data.retCode;  
    ws << data.spaceInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveSpaceResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.spaceInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LeaveSpaceResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "spaceInfo=" << info.spaceInfo << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserChatReq 
{ 
    static const unsigned short getProtoID() { return 40007;} 
    static const std::string getProtoName() { return "UserChatReq";} 
    unsigned long long userID;  
    std::string msg;  
    UserChatReq() 
    { 
        userID = 0; 
    } 
    UserChatReq(const unsigned long long & userID, const std::string & msg) 
    { 
        this->userID = userID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserChatReq & data) 
{ 
    ws << data.userID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserChatReq & data) 
{ 
    rs >> data.userID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserChatReq & info) 
{ 
    stm << "[\n"; 
    stm << "userID=" << info.userID << "\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserChatResp 
{ 
    static const unsigned short getProtoID() { return 40008;} 
    static const std::string getProtoName() { return "UserChatResp";} 
    unsigned long long fromUserID;  
    std::string msg;  
    UserChatResp() 
    { 
        fromUserID = 0; 
    } 
    UserChatResp(const unsigned long long & fromUserID, const std::string & msg) 
    { 
        this->fromUserID = fromUserID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserChatResp & data) 
{ 
    ws << data.fromUserID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserChatResp & data) 
{ 
    rs >> data.fromUserID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserChatResp & info) 
{ 
    stm << "[\n"; 
    stm << "fromUserID=" << info.fromUserID << "\n"; 
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
