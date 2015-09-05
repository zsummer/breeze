 
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
    ws << data.chlType; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinGropuReq & data) 
{ 
        rs >> data.chlType;  
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
    ws << data.retCode; 
    ws << data.chlType; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinGropuAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.chlType;  
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
    ws << data.chlType; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveGropuReq & data) 
{ 
        rs >> data.chlType;  
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
    ws << data.retCode; 
    ws << data.chlType; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LeaveGropuAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.chlType;  
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
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatInfo & data) 
{ 
        rs >> data.mID;  
        rs >> data.chlType;  
        rs >> data.srcID;  
        rs >> data.srcName;  
        rs >> data.srcIcon;  
        rs >> data.dstID;  
        rs >> data.dstName;  
        rs >> data.dstIcon;  
        rs >> data.msg;  
        rs >> data.sendTime;  
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
    ws << data.chlType; 
    ws << data.dstID; 
    ws << data.msg; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatReq & data) 
{ 
        rs >> data.chlType;  
        rs >> data.dstID;  
        rs >> data.msg;  
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
    ws << data.retCode; 
    ws << data.chlType; 
    ws << data.dstID; 
    ws << data.msgID; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatAck & data) 
{ 
        rs >> data.retCode;  
        rs >> data.chlType;  
        rs >> data.dstID;  
        rs >> data.msgID;  
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
    ws << data.retCode; 
    ws << data.msgs; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatNotice & data) 
{ 
        rs >> data.retCode;  
        rs >> data.msgs;  
    return rs; 
} 
 
#endif 
