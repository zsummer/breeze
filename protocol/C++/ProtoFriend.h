 
#ifndef _PROTOFRIEND_H_ 
#define _PROTOFRIEND_H_ 
 
const unsigned char FRIEND_DELETED = 0; //已删除好友关系 
const unsigned char FRIEND_WAITING = 1; //等待好友确认 
const unsigned char FRIEND_REQUESTING = 2; //需要确认 
const unsigned char FRIEND_BLACKLIST = 3; //黑名单 
const unsigned char FRIEND_ESTABLISHED = 4; //好友 
const unsigned char FRIEND_ADD_FRIEND = 0; //添加好友 
const unsigned char FRIEND_REMOVE_FRIEND = 1; //移除好友 
const unsigned char FRIEND_ADD_BLACKLIST = 2; //添加黑名单 
const unsigned char FRIEND_REMOVE_BLACKLIST = 3; //移除黑名单 
const unsigned char FRIEND_ALLOW = 4; //同意 
const unsigned char FRIEND_REJECT = 5; //拒绝 
const unsigned char FRIEND_IGNORE = 6; //忽略 
 
struct FriendInfo //好友信息 
{ 
    unsigned long long ownID;  
    unsigned long long fID;  
    unsigned char flag; //状态标志 
    unsigned char online; //好友是否在线,不需要存数据库 
    unsigned int makeTime; //建立时间 
    FriendInfo() 
    { 
        ownID = 0; 
        fID = 0; 
        flag = 0; 
        online = 0; 
        makeTime = 0; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendInfo & data) 
{ 
    unsigned long long tag = 31ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.ownID; 
    ws << data.fID; 
    ws << data.flag; 
    ws << data.online; 
    ws << data.makeTime; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendInfo & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.ownID;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.fID;  
    } 
    if ( (1ULL << 2) & tag) 
    { 
        rs >> data.flag;  
    } 
    if ( (1ULL << 3) & tag) 
    { 
        rs >> data.online;  
    } 
    if ( (1ULL << 4) & tag) 
    { 
        rs >> data.makeTime;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
typedef std::vector<FriendInfo> FriendInfoArray;  
 
const unsigned short ID_GetFriendsReq = 1005; //获取好友列表 
struct GetFriendsReq //获取好友列表 
{ 
    inline unsigned short GetProtoID() { return 1005;} 
    inline std::string GetProtoName() { return "ID_GetFriendsReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetFriendsReq & data) 
{ 
    unsigned long long tag = 0ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetFriendsReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_UpdateFriendsNotice = 1006; //好友列表推送通知 
struct UpdateFriendsNotice //好友列表推送通知 
{ 
    FriendInfoArray friends;  
    inline unsigned short GetProtoID() { return 1006;} 
    inline std::string GetProtoName() { return "ID_UpdateFriendsNotice";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UpdateFriendsNotice & data) 
{ 
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.friends; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UpdateFriendsNotice & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.friends;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_FriendOperationReq = 1002; //好友操作请求 
struct FriendOperationReq //好友操作请求 
{ 
    unsigned long long dst; //目标ID 
    unsigned char instruct; //操作指令 
    FriendOperationReq() 
    { 
        dst = 0; 
        instruct = 0; 
    } 
    inline unsigned short GetProtoID() { return 1002;} 
    inline std::string GetProtoName() { return "ID_FriendOperationReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendOperationReq & data) 
{ 
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.dst; 
    ws << data.instruct; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendOperationReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.dst;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.instruct;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_FriendOperationNotice = 1004; //好友操作推送通知 
struct FriendOperationNotice //好友操作推送通知 
{ 
    unsigned short retCode;  
    unsigned long long src; //发起操作的用户 
    unsigned char instruct; //发起的操作指令 
    unsigned long long dst; //操作目标用户 
    FriendOperationNotice() 
    { 
        retCode = 0; 
        src = 0; 
        instruct = 0; 
        dst = 0; 
    } 
    inline unsigned short GetProtoID() { return 1004;} 
    inline std::string GetProtoName() { return "ID_FriendOperationNotice";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendOperationNotice & data) 
{ 
    unsigned long long tag = 15ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.src; 
    ws << data.instruct; 
    ws << data.dst; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendOperationNotice & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.retCode;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.src;  
    } 
    if ( (1ULL << 2) & tag) 
    { 
        rs >> data.instruct;  
    } 
    if ( (1ULL << 3) & tag) 
    { 
        rs >> data.dst;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_GetSomeStrangersReq = 1000; //获取一些陌生人 
struct GetSomeStrangersReq //获取一些陌生人 
{ 
    inline unsigned short GetProtoID() { return 1000;} 
    inline std::string GetProtoName() { return "ID_GetSomeStrangersReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSomeStrangersReq & data) 
{ 
    unsigned long long tag = 0ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSomeStrangersReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_GetSomeStrangersAck = 1001; //获取一些陌生人 
struct GetSomeStrangersAck //获取一些陌生人 
{ 
    unsigned short retCode;  
    UserIDArray uIDs;  
    GetSomeStrangersAck() 
    { 
        retCode = 0; 
    } 
    inline unsigned short GetProtoID() { return 1001;} 
    inline std::string GetProtoName() { return "ID_GetSomeStrangersAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSomeStrangersAck & data) 
{ 
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.uIDs; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSomeStrangersAck & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.retCode;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.uIDs;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
#endif 
