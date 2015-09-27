 
#ifndef _PROTOCHAT_H_ 
#define _PROTOCHAT_H_ 
 
 
enum  : unsigned char 
{ 
    CHANNEL_PRIVATE = 0, //私聊, 需要指明具体某个uid  
    CHANNEL_WORLD = 1, //世界  
    CHANNEL_GROUP = 2, //群组, 需要指明具体某个groupid  
}; 
 
struct JoinGropuReq //加入频道  
{ 
    static const unsigned short GetProtoID() { return 1100;} 
    static const std::string GetProtoName() { return "ID_JoinGropuReq";} 
    unsigned char chlType; //channel type  
    JoinGropuReq() 
    { 
        chlType = 0; 
    } 
    JoinGropuReq(const unsigned char & chlType) 
    { 
        this->chlType = chlType; 
    } 
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
 
struct JoinGropuAck 
{ 
    static const unsigned short GetProtoID() { return 1101;} 
    static const std::string GetProtoName() { return "ID_JoinGropuAck";} 
    unsigned short retCode;  
    unsigned char chlType; //channel type  
    JoinGropuAck() 
    { 
        retCode = 0; 
        chlType = 0; 
    } 
    JoinGropuAck(const unsigned short & retCode, const unsigned char & chlType) 
    { 
        this->retCode = retCode; 
        this->chlType = chlType; 
    } 
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
 
struct LeaveGropuReq //加入频道  
{ 
    static const unsigned short GetProtoID() { return 1102;} 
    static const std::string GetProtoName() { return "ID_LeaveGropuReq";} 
    unsigned char chlType; //channel type  
    LeaveGropuReq() 
    { 
        chlType = 0; 
    } 
    LeaveGropuReq(const unsigned char & chlType) 
    { 
        this->chlType = chlType; 
    } 
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
 
struct LeaveGropuAck 
{ 
    static const unsigned short GetProtoID() { return 1103;} 
    static const std::string GetProtoName() { return "ID_LeaveGropuAck";} 
    unsigned short retCode;  
    unsigned char chlType; //channel type  
    LeaveGropuAck() 
    { 
        retCode = 0; 
        chlType = 0; 
    } 
    LeaveGropuAck(const unsigned short & retCode, const unsigned char & chlType) 
    { 
        this->retCode = retCode; 
        this->chlType = chlType; 
    } 
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
    ChatInfo(const unsigned long long & mID, const unsigned char & chlType, const unsigned long long & srcID, const std::string & srcName, const short & srcIcon, const unsigned long long & dstID, const std::string & dstName, const short & dstIcon, const std::string & msg, const unsigned int & sendTime) 
    { 
        this->mID = mID; 
        this->chlType = chlType; 
        this->srcID = srcID; 
        this->srcName = srcName; 
        this->srcIcon = srcIcon; 
        this->dstID = dstID; 
        this->dstName = dstName; 
        this->dstIcon = dstIcon; 
        this->msg = msg; 
        this->sendTime = sendTime; 
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
 
struct ChatReq //发送聊天请求  
{ 
    static const unsigned short GetProtoID() { return 1104;} 
    static const std::string GetProtoName() { return "ID_ChatReq";} 
    unsigned char chlType; //channel type  
    unsigned long long dstID; //userID or groupID  
    std::string msg; //msg  
    ChatReq() 
    { 
        chlType = 0; 
        dstID = 0; 
    } 
    ChatReq(const unsigned char & chlType, const unsigned long long & dstID, const std::string & msg) 
    { 
        this->chlType = chlType; 
        this->dstID = dstID; 
        this->msg = msg; 
    } 
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
 
struct ChatAck //发送聊天请求  
{ 
    static const unsigned short GetProtoID() { return 1105;} 
    static const std::string GetProtoName() { return "ID_ChatAck";} 
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
    ChatAck(const unsigned short & retCode, const unsigned char & chlType, const unsigned long long & dstID, const unsigned long long & msgID) 
    { 
        this->retCode = retCode; 
        this->chlType = chlType; 
        this->dstID = dstID; 
        this->msgID = msgID; 
    } 
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
 
struct ChatNotice //聊天通知  
{ 
    static const unsigned short GetProtoID() { return 1106;} 
    static const std::string GetProtoName() { return "ID_ChatNotice";} 
    unsigned short retCode;  
    ChatInfoArray msgs;  
    ChatNotice() 
    { 
        retCode = 0; 
    } 
    ChatNotice(const unsigned short & retCode, const ChatInfoArray & msgs) 
    { 
        this->retCode = retCode; 
        this->msgs = msgs; 
    } 
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
