 
#ifndef _PROTOUSERMGR_H_ 
#define _PROTOUSERMGR_H_ 
 
 
struct SelectUserPreviewsFromUserMgrReq //获取角色预览数据  
{ 
    static const unsigned short getProtoID() { return 20000;} 
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
    static const unsigned short getProtoID() { return 20001;} 
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
    static const unsigned short getProtoID() { return 20002;} 
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
    static const unsigned short getProtoID() { return 20003;} 
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
 
struct SelectUserFromUserMgrReq //选角色请求  
{ 
    static const unsigned short getProtoID() { return 20004;} 
    static const std::string getProtoName() { return "SelectUserFromUserMgrReq";} 
    unsigned long long uID;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    SelectUserFromUserMgrReq() 
    { 
        uID = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
    } 
    SelectUserFromUserMgrReq(const unsigned long long & uID, const unsigned int & clientDockerID, const unsigned int & clientSessionID) 
    { 
        this->uID = uID; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserFromUserMgrReq & data) 
{ 
    ws << data.uID;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserFromUserMgrReq & data) 
{ 
    rs >> data.uID;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SelectUserFromUserMgrReq & info) 
{ 
    stm << "[\n"; 
    stm << "uID=" << info.uID << "\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SelectUserFromUserMgrResp //选角色请求返回  
{ 
    static const unsigned short getProtoID() { return 20005;} 
    static const std::string getProtoName() { return "SelectUserFromUserMgrResp";} 
    unsigned short retCode;  
    unsigned int clientDockerID;  
    unsigned int clientSessionID;  
    unsigned long long userServiceID;  
    SelectUserFromUserMgrResp() 
    { 
        retCode = 0; 
        clientDockerID = 0; 
        clientSessionID = 0; 
        userServiceID = 0; 
    } 
    SelectUserFromUserMgrResp(const unsigned short & retCode, const unsigned int & clientDockerID, const unsigned int & clientSessionID, const unsigned long long & userServiceID) 
    { 
        this->retCode = retCode; 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
        this->userServiceID = userServiceID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserFromUserMgrResp & data) 
{ 
    ws << data.retCode;  
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    ws << data.userServiceID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserFromUserMgrResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    rs >> data.userServiceID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SelectUserFromUserMgrResp & info) 
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
