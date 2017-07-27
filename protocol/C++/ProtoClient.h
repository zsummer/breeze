 
#ifndef _PROTOCLIENT_H_ 
#define _PROTOCLIENT_H_ 
 
 
struct ClientPulse //客户端脉冲请求  
{ 
    static const unsigned short getProtoID() { return 55000;} 
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
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientAuthReq //认证请求  
{ 
    static const unsigned short getProtoID() { return 55001;} 
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
    stm << "["; 
    stm << "account=" << info.account << ","; 
    stm << "token=" << info.token << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ClientAuthResp //认证返回  
{ 
    static const unsigned short getProtoID() { return 55002;} 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "account=" << info.account << ","; 
    stm << "token=" << info.token << ","; 
    stm << "previews=" << info.previews << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct CreateAvatarReq //创角色请求  
{ 
    static const unsigned short getProtoID() { return 55003;} 
    static const std::string getProtoName() { return "CreateAvatarReq";} 
    std::string accountName; //这个字段会被服务器填充.客户端可以不填写  
    std::string avatarName;  
    CreateAvatarReq() 
    { 
    } 
    CreateAvatarReq(const std::string & accountName, const std::string & avatarName) 
    { 
        this->accountName = accountName; 
        this->avatarName = avatarName; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateAvatarReq & data) 
{ 
    ws << data.accountName;  
    ws << data.avatarName;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateAvatarReq & data) 
{ 
    rs >> data.accountName;  
    rs >> data.avatarName;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateAvatarReq & info) 
{ 
    stm << "["; 
    stm << "accountName=" << info.accountName << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct CreateAvatarResp //创角色请求返回  
{ 
    static const unsigned short getProtoID() { return 55004;} 
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
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "previews=" << info.previews << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::map<std::string, std::string> DeviceInfo;  
 
struct AttachAvatarReq //选角色请求  
{ 
    static const unsigned short getProtoID() { return 55005;} 
    static const std::string getProtoName() { return "AttachAvatarReq";} 
    std::string accountName; //这个字段会被服务器填充.客户端可以不填写  
    unsigned long long avatarID;  
    DeviceInfo di;  
    AttachAvatarReq() 
    { 
        avatarID = 0; 
    } 
    AttachAvatarReq(const std::string & accountName, const unsigned long long & avatarID, const DeviceInfo & di) 
    { 
        this->accountName = accountName; 
        this->avatarID = avatarID; 
        this->di = di; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachAvatarReq & data) 
{ 
    ws << data.accountName;  
    ws << data.avatarID;  
    ws << data.di;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachAvatarReq & data) 
{ 
    rs >> data.accountName;  
    rs >> data.avatarID;  
    rs >> data.di;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachAvatarReq & info) 
{ 
    stm << "["; 
    stm << "accountName=" << info.accountName << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "di=" << info.di << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct AttachAvatarResp //选角色请求返回  
{ 
    static const unsigned short getProtoID() { return 55006;} 
    static const std::string getProtoName() { return "AttachAvatarResp";} 
    unsigned short retCode;  
    AvatarBaseInfo baseInfo;  
    AttachAvatarResp() 
    { 
        retCode = 0; 
    } 
    AttachAvatarResp(const unsigned short & retCode, const AvatarBaseInfo & baseInfo) 
    { 
        this->retCode = retCode; 
        this->baseInfo = baseInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AttachAvatarResp & data) 
{ 
    ws << data.retCode;  
    ws << data.baseInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AttachAvatarResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.baseInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AttachAvatarResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "baseInfo=" << info.baseInfo << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct AvatarBaseInfoNotice 
{ 
    static const unsigned short getProtoID() { return 55007;} 
    static const std::string getProtoName() { return "AvatarBaseInfoNotice";} 
    AvatarBaseInfo baseInfo;  
    AvatarBaseInfoNotice() 
    { 
    } 
    AvatarBaseInfoNotice(const AvatarBaseInfo & baseInfo) 
    { 
        this->baseInfo = baseInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AvatarBaseInfoNotice & data) 
{ 
    ws << data.baseInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AvatarBaseInfoNotice & data) 
{ 
    rs >> data.baseInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AvatarBaseInfoNotice & info) 
{ 
    stm << "["; 
    stm << "baseInfo=" << info.baseInfo << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct AvatarPropMapNotice 
{ 
    static const unsigned short getProtoID() { return 55008;} 
    static const std::string getProtoName() { return "AvatarPropMapNotice";} 
    unsigned long long avatarID;  
    AvatarPropMapNotice() 
    { 
        avatarID = 0; 
    } 
    AvatarPropMapNotice(const unsigned long long & avatarID) 
    { 
        this->avatarID = avatarID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AvatarPropMapNotice & data) 
{ 
    ws << data.avatarID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AvatarPropMapNotice & data) 
{ 
    rs >> data.avatarID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AvatarPropMapNotice & info) 
{ 
    stm << "["; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupInfoNotice //编队数据通知  
{ 
    static const unsigned short getProtoID() { return 55009;} 
    static const std::string getProtoName() { return "SceneGroupInfoNotice";} 
    SceneGroupInfo groupInfo;  
    SceneGroupInfoNotice() 
    { 
    } 
    SceneGroupInfoNotice(const SceneGroupInfo & groupInfo) 
    { 
        this->groupInfo = groupInfo; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupInfoNotice & data) 
{ 
    ws << data.groupInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupInfoNotice & data) 
{ 
    rs >> data.groupInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupInfoNotice & info) 
{ 
    stm << "["; 
    stm << "groupInfo=" << info.groupInfo << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupGetReq //获取当前角色的场景状态数据  
{ 
    static const unsigned short getProtoID() { return 55010;} 
    static const std::string getProtoName() { return "SceneGroupGetReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupGetReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupGetReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupGetReq & info) 
{ 
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupGetResp 
{ 
    static const unsigned short getProtoID() { return 55011;} 
    static const std::string getProtoName() { return "SceneGroupGetResp";} 
    unsigned short retCode;  
    SceneGroupGetResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupGetResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupGetResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupGetResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupGetResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupEnterReq //申请进入场景  
{ 
    static const unsigned short getProtoID() { return 55012;} 
    static const std::string getProtoName() { return "SceneGroupEnterReq";} 
    unsigned short sceneType;  
    unsigned long long mapID;  
    SceneGroupEnterReq() 
    { 
        sceneType = 0; 
        mapID = 0; 
    } 
    SceneGroupEnterReq(const unsigned short & sceneType, const unsigned long long & mapID) 
    { 
        this->sceneType = sceneType; 
        this->mapID = mapID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupEnterReq & data) 
{ 
    ws << data.sceneType;  
    ws << data.mapID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupEnterReq & data) 
{ 
    rs >> data.sceneType;  
    rs >> data.mapID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupEnterReq & info) 
{ 
    stm << "["; 
    stm << "sceneType=" << info.sceneType << ","; 
    stm << "mapID=" << info.mapID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupEnterResp 
{ 
    static const unsigned short getProtoID() { return 55013;} 
    static const std::string getProtoName() { return "SceneGroupEnterResp";} 
    unsigned short retCode;  
    SceneGroupEnterResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupEnterResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupEnterResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupEnterResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupEnterResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupCancelReq //取消申请(根据状态不同会有取消匹配,重置状态,结束战斗(可中途结束的场景类型)  
{ 
    static const unsigned short getProtoID() { return 55014;} 
    static const std::string getProtoName() { return "SceneGroupCancelReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupCancelReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupCancelReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupCancelReq & info) 
{ 
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupCancelResp 
{ 
    static const unsigned short getProtoID() { return 55015;} 
    static const std::string getProtoName() { return "SceneGroupCancelResp";} 
    unsigned short retCode;  
    SceneGroupCancelResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupCancelResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupCancelResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupCancelResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupCancelResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupCreateReq //发起组队请求  
{ 
    static const unsigned short getProtoID() { return 55016;} 
    static const std::string getProtoName() { return "SceneGroupCreateReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupCreateReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupCreateReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupCreateReq & info) 
{ 
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupCreateResp 
{ 
    static const unsigned short getProtoID() { return 55017;} 
    static const std::string getProtoName() { return "SceneGroupCreateResp";} 
    unsigned short retCode;  
    SceneGroupCreateResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupCreateResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupCreateResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupCreateResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupCreateResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupJoinReq //加入组队  
{ 
    static const unsigned short getProtoID() { return 55018;} 
    static const std::string getProtoName() { return "SceneGroupJoinReq";} 
    unsigned long long groupID;  
    SceneGroupJoinReq() 
    { 
        groupID = 0; 
    } 
    SceneGroupJoinReq(const unsigned long long & groupID) 
    { 
        this->groupID = groupID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupJoinReq & data) 
{ 
    ws << data.groupID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupJoinReq & data) 
{ 
    rs >> data.groupID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupJoinReq & info) 
{ 
    stm << "["; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupJoinResp 
{ 
    static const unsigned short getProtoID() { return 55019;} 
    static const std::string getProtoName() { return "SceneGroupJoinResp";} 
    unsigned short retCode;  
    SceneGroupJoinResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupJoinResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupJoinResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupJoinResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupJoinResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupInviteReq //邀请对方加入自己的编队  
{ 
    static const unsigned short getProtoID() { return 55020;} 
    static const std::string getProtoName() { return "SceneGroupInviteReq";} 
    unsigned long long avatarID;  
    SceneGroupInviteReq() 
    { 
        avatarID = 0; 
    } 
    SceneGroupInviteReq(const unsigned long long & avatarID) 
    { 
        this->avatarID = avatarID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupInviteReq & data) 
{ 
    ws << data.avatarID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupInviteReq & data) 
{ 
    rs >> data.avatarID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupInviteReq & info) 
{ 
    stm << "["; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupInviteResp 
{ 
    static const unsigned short getProtoID() { return 55021;} 
    static const std::string getProtoName() { return "SceneGroupInviteResp";} 
    unsigned short retCode;  
    SceneGroupInviteResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupInviteResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupInviteResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupInviteResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupInviteResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupInviteNotice 
{ 
    static const unsigned short getProtoID() { return 55022;} 
    static const std::string getProtoName() { return "SceneGroupInviteNotice";} 
    unsigned long long avatarID;  
    std::string avatarName;  
    unsigned long long groupID;  
    SceneGroupInviteNotice() 
    { 
        avatarID = 0; 
        groupID = 0; 
    } 
    SceneGroupInviteNotice(const unsigned long long & avatarID, const std::string & avatarName, const unsigned long long & groupID) 
    { 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->groupID = groupID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupInviteNotice & data) 
{ 
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.groupID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupInviteNotice & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.groupID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupInviteNotice & info) 
{ 
    stm << "["; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupRejectReq //拒绝对方邀请  
{ 
    static const unsigned short getProtoID() { return 55023;} 
    static const std::string getProtoName() { return "SceneGroupRejectReq";} 
    unsigned long long groupID;  
    SceneGroupRejectReq() 
    { 
        groupID = 0; 
    } 
    SceneGroupRejectReq(const unsigned long long & groupID) 
    { 
        this->groupID = groupID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupRejectReq & data) 
{ 
    ws << data.groupID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupRejectReq & data) 
{ 
    rs >> data.groupID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupRejectReq & info) 
{ 
    stm << "["; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupRejectResp 
{ 
    static const unsigned short getProtoID() { return 55024;} 
    static const std::string getProtoName() { return "SceneGroupRejectResp";} 
    unsigned short retCode;  
    SceneGroupRejectResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupRejectResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupRejectResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupRejectResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupRejectResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupLeaveReq //离开编队  
{ 
    static const unsigned short getProtoID() { return 55025;} 
    static const std::string getProtoName() { return "SceneGroupLeaveReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupLeaveReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupLeaveReq & data) 
{ 
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupLeaveReq & info) 
{ 
    stm << "["; 
    stm << "]"; 
    return stm; 
} 
 
struct SceneGroupLeaveResp 
{ 
    static const unsigned short getProtoID() { return 55026;} 
    static const std::string getProtoName() { return "SceneGroupLeaveResp";} 
    unsigned short retCode;  
    SceneGroupLeaveResp() 
    { 
        retCode = 0; 
    } 
    SceneGroupLeaveResp(const unsigned short & retCode) 
    { 
        this->retCode = retCode; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupLeaveResp & data) 
{ 
    ws << data.retCode;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupLeaveResp & data) 
{ 
    rs >> data.retCode;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupLeaveResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ChatReq 
{ 
    static const unsigned short getProtoID() { return 55027;} 
    static const std::string getProtoName() { return "ChatReq";} 
    unsigned short channelID;  
    unsigned long long targetID;  
    std::string msg;  
    ChatReq() 
    { 
        channelID = 0; 
        targetID = 0; 
    } 
    ChatReq(const unsigned short & channelID, const unsigned long long & targetID, const std::string & msg) 
    { 
        this->channelID = channelID; 
        this->targetID = targetID; 
        this->msg = msg; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatReq & data) 
{ 
    ws << data.channelID;  
    ws << data.targetID;  
    ws << data.msg;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatReq & data) 
{ 
    rs >> data.channelID;  
    rs >> data.targetID;  
    rs >> data.msg;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatReq & info) 
{ 
    stm << "["; 
    stm << "channelID=" << info.channelID << ","; 
    stm << "targetID=" << info.targetID << ","; 
    stm << "msg=" << info.msg << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ChatResp 
{ 
    static const unsigned short getProtoID() { return 55028;} 
    static const std::string getProtoName() { return "ChatResp";} 
    unsigned short channelID;  
    unsigned long long sourceID;  
    std::string sourceName;  
    unsigned long long targetID;  
    std::string targetName;  
    std::string msg;  
    unsigned long long chatTime;  
    ChatResp() 
    { 
        channelID = 0; 
        sourceID = 0; 
        targetID = 0; 
        chatTime = 0; 
    } 
    ChatResp(const unsigned short & channelID, const unsigned long long & sourceID, const std::string & sourceName, const unsigned long long & targetID, const std::string & targetName, const std::string & msg, const unsigned long long & chatTime) 
    { 
        this->channelID = channelID; 
        this->sourceID = sourceID; 
        this->sourceName = sourceName; 
        this->targetID = targetID; 
        this->targetName = targetName; 
        this->msg = msg; 
        this->chatTime = chatTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatResp & data) 
{ 
    ws << data.channelID;  
    ws << data.sourceID;  
    ws << data.sourceName;  
    ws << data.targetID;  
    ws << data.targetName;  
    ws << data.msg;  
    ws << data.chatTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatResp & data) 
{ 
    rs >> data.channelID;  
    rs >> data.sourceID;  
    rs >> data.sourceName;  
    rs >> data.targetID;  
    rs >> data.targetName;  
    rs >> data.msg;  
    rs >> data.chatTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatResp & info) 
{ 
    stm << "["; 
    stm << "channelID=" << info.channelID << ","; 
    stm << "sourceID=" << info.sourceID << ","; 
    stm << "sourceName=" << info.sourceName << ","; 
    stm << "targetID=" << info.targetID << ","; 
    stm << "targetName=" << info.targetName << ","; 
    stm << "msg=" << info.msg << ","; 
    stm << "chatTime=" << info.chatTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct PingPongReq 
{ 
    static const unsigned short getProtoID() { return 55029;} 
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
    stm << "["; 
    stm << "msg=" << info.msg << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct PingPongResp 
{ 
    static const unsigned short getProtoID() { return 55030;} 
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
    stm << "["; 
    stm << "msg=" << info.msg << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ChangeIconIDReq 
{ 
    static const unsigned short getProtoID() { return 55031;} 
    static const std::string getProtoName() { return "ChangeIconIDReq";} 
    unsigned long long iconID;  
    ChangeIconIDReq() 
    { 
        iconID = 0; 
    } 
    ChangeIconIDReq(const unsigned long long & iconID) 
    { 
        this->iconID = iconID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChangeIconIDReq & data) 
{ 
    ws << data.iconID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChangeIconIDReq & data) 
{ 
    rs >> data.iconID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChangeIconIDReq & info) 
{ 
    stm << "["; 
    stm << "iconID=" << info.iconID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ChangeIconIDResp 
{ 
    static const unsigned short getProtoID() { return 55032;} 
    static const std::string getProtoName() { return "ChangeIconIDResp";} 
    unsigned short retCode;  
    unsigned long long iconID;  
    ChangeIconIDResp() 
    { 
        retCode = 0; 
        iconID = 0; 
    } 
    ChangeIconIDResp(const unsigned short & retCode, const unsigned long long & iconID) 
    { 
        this->retCode = retCode; 
        this->iconID = iconID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChangeIconIDResp & data) 
{ 
    ws << data.retCode;  
    ws << data.iconID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChangeIconIDResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.iconID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChangeIconIDResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "iconID=" << info.iconID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ChangeModeIDReq 
{ 
    static const unsigned short getProtoID() { return 55033;} 
    static const std::string getProtoName() { return "ChangeModeIDReq";} 
    unsigned long long modeID;  
    ChangeModeIDReq() 
    { 
        modeID = 0; 
    } 
    ChangeModeIDReq(const unsigned long long & modeID) 
    { 
        this->modeID = modeID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChangeModeIDReq & data) 
{ 
    ws << data.modeID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChangeModeIDReq & data) 
{ 
    rs >> data.modeID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChangeModeIDReq & info) 
{ 
    stm << "["; 
    stm << "modeID=" << info.modeID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct ChangeModeIDResp 
{ 
    static const unsigned short getProtoID() { return 55034;} 
    static const std::string getProtoName() { return "ChangeModeIDResp";} 
    unsigned short retCode;  
    unsigned long long modeID;  
    ChangeModeIDResp() 
    { 
        retCode = 0; 
        modeID = 0; 
    } 
    ChangeModeIDResp(const unsigned short & retCode, const unsigned long long & modeID) 
    { 
        this->retCode = retCode; 
        this->modeID = modeID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChangeModeIDResp & data) 
{ 
    ws << data.retCode;  
    ws << data.modeID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChangeModeIDResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.modeID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChangeModeIDResp & info) 
{ 
    stm << "["; 
    stm << "retCode=" << info.retCode << ","; 
    stm << "modeID=" << info.modeID << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 
