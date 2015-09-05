 
#ifndef _PROTOFRIEND_H_ 
#define _PROTOFRIEND_H_ 
 
const unsigned char FRIEND_DELETED = 0; //已删除好友关系 
const unsigned char FRIEND_WAITING = 1; //等待好友确认 
const unsigned char FRIEND_REQUESTING = 2; //需要确认 
const unsigned char FRIEND_BLACKLIST = 3; //黑名单 
const unsigned char FRIEND_ESTABLISHED = 4; //好友 
const unsigned char FRIEND_ALLOW = 0; //同意 
const unsigned char FRIEND_REJECT = 1; //拒绝 
const unsigned char FRIEND_IGNORE = 2; //忽略 
 
struct FriendInfo //好友信息 
{ 
    unsigned long long ownID;  
    unsigned long long fID;  
    unsigned char flag; //状态标志 
    unsigned char online; //好友是否在线,不需要存数据库 
    unsigned int makeTime; //建立时间 
    unsigned int lastChanged; //最后更改时间 
    FriendInfo() 
    { 
        ownID = 0; 
        fID = 0; 
        flag = 0; 
        online = 0; 
        makeTime = 0; 
        lastChanged = 0; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendInfo & data) 
{ 
    ws << data.ownID; 
    ws << data.fID; 
    ws << data.flag; 
    ws << data.online; 
    ws << data.makeTime; 
    ws << data.lastChanged; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendInfo & data) 
{ 
        rs >> data.ownID;  
        rs >> data.fID;  
        rs >> data.flag;  
        rs >> data.online;  
        rs >> data.makeTime;  
        rs >> data.lastChanged;  
    return rs; 
} 
 
typedef std::vector<FriendInfo> FriendInfoArray;  
 
const unsigned short ID_GetFriendsReq = 1000; //获取好友列表 
struct GetFriendsReq //获取好友列表 
{ 
    static const unsigned short GetProtoID() { return 1000;} 
    static const std::string GetProtoName() { return "ID_GetFriendsReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetFriendsReq & data) 
{ 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetFriendsReq & data) 
{ 
    return rs; 
} 
 
const unsigned short ID_UpdateFriendsNotice = 1001; //好友列表推送通知 
struct UpdateFriendsNotice //好友列表推送通知 
{ 
    FriendInfoArray friends;  
    static const unsigned short GetProtoID() { return 1001;} 
    static const std::string GetProtoName() { return "ID_UpdateFriendsNotice";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UpdateFriendsNotice & data) 
{ 
    ws << data.friends; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UpdateFriendsNotice & data) 
{ 
        rs >> data.friends;  
    return rs; 
} 
 
const unsigned short ID_AddFriendReq = 1002; //添加好友请求 
struct AddFriendReq //添加好友请求 
{ 
    unsigned long long dst; //目标ID 
    AddFriendReq() 
    { 
        dst = 0; 
    } 
    static const unsigned short GetProtoID() { return 1002;} 
    static const std::string GetProtoName() { return "ID_AddFriendReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddFriendReq & data) 
{ 
    ws << data.dst; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddFriendReq & data) 
{ 
        rs >> data.dst;  
    return rs; 
} 
 
const unsigned short ID_AddFriendReply = 1003; //答复好友请求 
struct AddFriendReply //答复好友请求 
{ 
    unsigned long long dst; //目标ID 
    unsigned char flag; //状态标志 
    AddFriendReply() 
    { 
        dst = 0; 
        flag = 0; 
    } 
    static const unsigned short GetProtoID() { return 1003;} 
    static const std::string GetProtoName() { return "ID_AddFriendReply";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddFriendReply & data) 
{ 
    ws << data.dst; 
    ws << data.flag; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddFriendReply & data) 
{ 
        rs >> data.dst;  
        rs >> data.flag;  
    return rs; 
} 
 
const unsigned short ID_AddFriendAck = 1004; //添加好友请求结果 
struct AddFriendAck //添加好友请求结果 
{ 
    unsigned short retCode;  
    unsigned long long dst; //目标ID 
    AddFriendAck() 
    { 
        retCode = 0; 
        dst = 0; 
    } 
    static const unsigned short GetProtoID() { return 1004;} 
    static const std::string GetProtoName() { return "ID_AddFriendAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AddFriendAck & data) 
{ 
    ws << data.retCode; 
    ws << data.dst; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddFriendAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.dst;  
    return rs; 
} 
 
const unsigned short ID_DelFriendReq = 1005; //删除好友请求 
struct DelFriendReq //删除好友请求 
{ 
    unsigned long long dst; //目标ID 
    DelFriendReq() 
    { 
        dst = 0; 
    } 
    static const unsigned short GetProtoID() { return 1005;} 
    static const std::string GetProtoName() { return "ID_DelFriendReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DelFriendReq & data) 
{ 
    ws << data.dst; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DelFriendReq & data) 
{ 
        rs >> data.dst;  
    return rs; 
} 
 
const unsigned short ID_DelFriendAck = 1006; //删除好友请求结果 
struct DelFriendAck //删除好友请求结果 
{ 
    unsigned short retCode;  
    unsigned long long dst; //目标ID 
    DelFriendAck() 
    { 
        retCode = 0; 
        dst = 0; 
    } 
    static const unsigned short GetProtoID() { return 1006;} 
    static const std::string GetProtoName() { return "ID_DelFriendAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DelFriendAck & data) 
{ 
    ws << data.retCode; 
    ws << data.dst; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DelFriendAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.dst;  
    return rs; 
} 
 
#endif 
