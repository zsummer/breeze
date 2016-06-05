 
#ifndef _PROTOUSERMGR_H_ 
#define _PROTOUSERMGR_H_ 
 
 
struct SelectUserPreviewsFromUserMgrReq //获取角色预览数据  
{ 
    static const unsigned short getProtoID() { return 4000;} 
    static const std::string getProtoName() { return "SelectUserPreviewsFromUserMgrReq";} 
    std::string account;  
    std::string token;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    SelectUserPreviewsFromUserMgrReq() 
    { 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    SelectUserPreviewsFromUserMgrReq(const std::string & account, const std::string & token, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
    { 
        this->account = account; 
        this->token = token; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserPreviewsFromUserMgrReq & data) 
{ 
    ws << data.account;  
    ws << data.token;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserPreviewsFromUserMgrReq & data) 
{ 
    rs >> data.account;  
    rs >> data.token;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SelectUserPreviewsFromUserMgrReq & info) 
{ 
    stm << "[\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SelectUserPreviewsFromUserMgrResp //获取角色预览数据  
{ 
    static const unsigned short getProtoID() { return 4001;} 
    static const std::string getProtoName() { return "SelectUserPreviewsFromUserMgrResp";} 
    unsigned short retCode;  
    std::string account;  
    std::string token;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    UserPreviewArray previews;  
    SelectUserPreviewsFromUserMgrResp() 
    { 
        retCode = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    SelectUserPreviewsFromUserMgrResp(const unsigned short & retCode, const std::string & account, const std::string & token, const unsigned int & clientDockerID, const unsigned int & clientSessionID, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->account = account; 
        this->token = token; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserPreviewsFromUserMgrResp & data) 
{ 
    ws << data.retCode;  
    ws << data.account;  
    ws << data.token;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserPreviewsFromUserMgrResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.account;  
    rs >> data.token;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    rs >> data.previews;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SelectUserPreviewsFromUserMgrResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "previews=" << info.previews << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateUserFromUserMgrReq //创角色请求  
{ 
    static const unsigned short getProtoID() { return 4002;} 
    static const std::string getProtoName() { return "CreateUserFromUserMgrReq";} 
    std::string account;  
    std::string nickname;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    CreateUserFromUserMgrReq() 
    { 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    CreateUserFromUserMgrReq(const std::string & account, const std::string & nickname, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
    { 
        this->account = account; 
        this->nickname = nickname; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserFromUserMgrReq & data) 
{ 
    ws << data.account;  
    ws << data.nickname;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserFromUserMgrReq & data) 
{ 
    rs >> data.account;  
    rs >> data.nickname;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserFromUserMgrReq & info) 
{ 
    stm << "[\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "nickname=" << info.nickname << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct CreateUserFromUserMgrResp //创角色请求返回  
{ 
    static const unsigned short getProtoID() { return 4003;} 
    static const std::string getProtoName() { return "CreateUserFromUserMgrResp";} 
    unsigned short retCode;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    UserPreviewArray previews;  
    CreateUserFromUserMgrResp() 
    { 
        retCode = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    CreateUserFromUserMgrResp(const unsigned short & retCode, const unsigned int & clientDockerID, const unsigned int & clientSessionID, const UserPreviewArray & previews) 
    { 
        this->retCode = retCode; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
        this->previews = previews; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserFromUserMgrResp & data) 
{ 
    ws << data.retCode;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    ws << data.previews;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserFromUserMgrResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    rs >> data.previews;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserFromUserMgrResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "previews=" << info.previews << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachUserFromUserMgrReq //选角色请求  
{ 
    static const unsigned short getProtoID() { return 4004;} 
    static const std::string getProtoName() { return "AttachUserFromUserMgrReq";} 
    unsigned long long userServiceID;  
    std::string account;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    AttachUserFromUserMgrReq() 
    { 
        userServiceID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    AttachUserFromUserMgrReq(const unsigned long long & userServiceID, const std::string & account, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
    { 
        this->userServiceID = userServiceID; 
        this->account = account; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachUserFromUserMgrReq & data) 
{ 
    ws << data.userServiceID;  
    ws << data.account;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachUserFromUserMgrReq & data) 
{ 
    rs >> data.userServiceID;  
    rs >> data.account;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachUserFromUserMgrReq & info) 
{ 
    stm << "[\n"; 
    stm << "userServiceID=" << info.userServiceID << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct AttachUserFromUserMgrResp //选角色请求返回  
{ 
    static const unsigned short getProtoID() { return 4005;} 
    static const std::string getProtoName() { return "AttachUserFromUserMgrResp";} 
    unsigned short retCode;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    unsigned long long userServiceID;  
    AttachUserFromUserMgrResp() 
    { 
        retCode = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
        userServiceID = 0; 
    } 
    AttachUserFromUserMgrResp(const unsigned short & retCode, const unsigned int & clientDockerID, const unsigned int & clientSessionID, const unsigned long long & userServiceID) 
    { 
        this->retCode = retCode; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
        this->userServiceID = userServiceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachUserFromUserMgrResp & data) 
{ 
    ws << data.retCode;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    ws << data.userServiceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachUserFromUserMgrResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    rs >> data.userServiceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachUserFromUserMgrResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "userServiceID=" << info.userServiceID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
