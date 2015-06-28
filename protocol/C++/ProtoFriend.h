 
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
    unsigned long long tag = 63ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.ownID; 
    ws << data.fID; 
    ws << data.flag; 
    ws << data.online; 
    ws << data.makeTime; 
    ws << data.lastChanged; 
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
    if ( (1ULL << 5) & tag) 
    { 
        rs >> data.lastChanged;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
 
const unsigned short ID_UpdateFriendsNotice = 1001; //好友列表推送通知 
struct UpdateFriendsNotice //好友列表推送通知 
{ 
    FriendInfoArray friends;  
    static const unsigned short GetProtoID() { return 1001;} 
    static const std::string GetProtoName() { return "ID_UpdateFriendsNotice";} 
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
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.dst; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddFriendReq & data) 
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
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.dst; 
    ws << data.flag; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddFriendReply & data) 
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
        rs >> data.flag;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.dst; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AddFriendAck & data) 
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
        rs >> data.dst;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.dst; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DelFriendReq & data) 
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
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
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
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.dst; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DelFriendAck & data) 
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
        rs >> data.dst;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
#endif 
