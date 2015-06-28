 
#ifndef _PROTOCHAT_H_ 
#define _PROTOCHAT_H_ 
 
const unsigned char CHANNEL_PRIVATE = 0; //私聊, 需要指明具体某个uid 
const unsigned char CHANNEL_WORLD = 1; //世界 
const unsigned char CHANNEL_GROUP = 2; //群组, 需要指明具体某个groupid 
 
const unsigned short ID_JoinGropuReq = 1100; //加入频道 
struct JoinGropuReq //加入频道 
{ 
    unsigned char chlType; //channel type 
    JoinGropuReq() 
    { 
        chlType = 0; 
    } 
    static const unsigned short GetProtoID() { return 1100;} 
    static const std::string GetProtoName() { return "ID_JoinGropuReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinGropuReq & data) 
{ 
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.chlType; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinGropuReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.chlType;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_JoinGropuAck = 1101;  
struct JoinGropuAck 
{ 
    unsigned short retCode;  
    unsigned char chlType; //channel type 
    JoinGropuAck() 
    { 
        retCode = 0; 
        chlType = 0; 
    } 
    static const unsigned short GetProtoID() { return 1101;} 
    static const std::string GetProtoName() { return "ID_JoinGropuAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinGropuAck & data) 
{ 
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.chlType; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinGropuAck & data) 
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
        rs >> data.chlType;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_LeaveGropuReq = 1102; //加入频道 
struct LeaveGropuReq //加入频道 
{ 
    unsigned char chlType; //channel type 
    LeaveGropuReq() 
    { 
        chlType = 0; 
    } 
    static const unsigned short GetProtoID() { return 1102;} 
    static const std::string GetProtoName() { return "ID_LeaveGropuReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveGropuReq & data) 
{ 
    unsigned long long tag = 1ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.chlType; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveGropuReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.chlType;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_LeaveGropuAck = 1103;  
struct LeaveGropuAck 
{ 
    unsigned short retCode;  
    unsigned char chlType; //channel type 
    LeaveGropuAck() 
    { 
        retCode = 0; 
        chlType = 0; 
    } 
    static const unsigned short GetProtoID() { return 1103;} 
    static const std::string GetProtoName() { return "ID_LeaveGropuAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LeaveGropuAck & data) 
{ 
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.chlType; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveGropuAck & data) 
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
        rs >> data.chlType;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
struct ChatInfo //聊天消息 
{ 
    unsigned long long mID; //msg id 
    unsigned char chlType; //channel type 
    unsigned long long srcID;  
    std::string srcName; //src 
    short srcIcon; //src 
    unsigned long long dstID; //userid or groupid 
    std::string dstName; //src 
    short dstIcon; //src 
    std::string msg;  
    unsigned int sendTime;  
    ChatInfo() 
    { 
        mID = 0; 
        chlType = 0; 
        srcID = 0; 
        srcIcon = 0; 
        dstID = 0; 
        dstIcon = 0; 
        sendTime = 0; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatInfo & data) 
{ 
    unsigned long long tag = 1023ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.mID; 
    ws << data.chlType; 
    ws << data.srcID; 
    ws << data.srcName; 
    ws << data.srcIcon; 
    ws << data.dstID; 
    ws << data.dstName; 
    ws << data.dstIcon; 
    ws << data.msg; 
    ws << data.sendTime; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatInfo & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.mID;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.chlType;  
    } 
    if ( (1ULL << 2) & tag) 
    { 
        rs >> data.srcID;  
    } 
    if ( (1ULL << 3) & tag) 
    { 
        rs >> data.srcName;  
    } 
    if ( (1ULL << 4) & tag) 
    { 
        rs >> data.srcIcon;  
    } 
    if ( (1ULL << 5) & tag) 
    { 
        rs >> data.dstID;  
    } 
    if ( (1ULL << 6) & tag) 
    { 
        rs >> data.dstName;  
    } 
    if ( (1ULL << 7) & tag) 
    { 
        rs >> data.dstIcon;  
    } 
    if ( (1ULL << 8) & tag) 
    { 
        rs >> data.msg;  
    } 
    if ( (1ULL << 9) & tag) 
    { 
        rs >> data.sendTime;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
typedef std::vector<ChatInfo> ChatInfoArray;  
 
const unsigned short ID_ChatReq = 1104; //发送聊天请求 
struct ChatReq //发送聊天请求 
{ 
    unsigned char chlType; //channel type 
    unsigned long long dstID; //userID or groupID 
    std::string msg; //msg 
    ChatReq() 
    { 
        chlType = 0; 
        dstID = 0; 
    } 
    static const unsigned short GetProtoID() { return 1104;} 
    static const std::string GetProtoName() { return "ID_ChatReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatReq & data) 
{ 
    unsigned long long tag = 7ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.chlType; 
    ws << data.dstID; 
    ws << data.msg; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatReq & data) 
{ 
    zsummer::proto4z::Integer sttLen = 0; 
    rs >> sttLen; 
    zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
    unsigned long long tag = 0; 
    rs >> tag; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    if ( (1ULL << 0) & tag) 
    { 
        rs >> data.chlType;  
    } 
    if ( (1ULL << 1) & tag) 
    { 
        rs >> data.dstID;  
    } 
    if ( (1ULL << 2) & tag) 
    { 
        rs >> data.msg;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_ChatAck = 1105; //发送聊天请求 
struct ChatAck //发送聊天请求 
{ 
    unsigned short retCode;  
    unsigned char chlType; //channel type 
    unsigned long long dstID; //userID or groupID 
    unsigned long long msgID;  
    ChatAck() 
    { 
        retCode = 0; 
        chlType = 0; 
        dstID = 0; 
        msgID = 0; 
    } 
    static const unsigned short GetProtoID() { return 1105;} 
    static const std::string GetProtoName() { return "ID_ChatAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatAck & data) 
{ 
    unsigned long long tag = 15ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.chlType; 
    ws << data.dstID; 
    ws << data.msgID; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatAck & data) 
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
        rs >> data.chlType;  
    } 
    if ( (1ULL << 2) & tag) 
    { 
        rs >> data.dstID;  
    } 
    if ( (1ULL << 3) & tag) 
    { 
        rs >> data.msgID;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
const unsigned short ID_ChatNotice = 1106; //聊天通知 
struct ChatNotice //聊天通知 
{ 
    unsigned short retCode;  
    ChatInfoArray msgs;  
    ChatNotice() 
    { 
        retCode = 0; 
    } 
    static const unsigned short GetProtoID() { return 1106;} 
    static const std::string GetProtoName() { return "ID_ChatNotice";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatNotice & data) 
{ 
    unsigned long long tag = 3ULL; 
    if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
    ws << (zsummer::proto4z::Integer)0; 
    zsummer::proto4z::Integer offset = ws.getStreamLen(); 
    ws << tag; 
    ws << data.retCode; 
    ws << data.msgs; 
    ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatNotice & data) 
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
        rs >> data.msgs;  
    } 
    cursor = cursor - rs.getStreamUnreadLen(); 
    rs.skipOriginalData(sttLen - cursor); 
    return rs; 
} 
 
#endif 
