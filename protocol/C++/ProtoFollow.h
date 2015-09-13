 
#ifndef _PROTOFOLLOW_H_ 
#define _PROTOFOLLOW_H_ 
 
/*--enum--[name=FOLLOW_STATUS, type=ui8, desc=关系]--*/ 
const unsigned char FOLLOW_INVALID = 0;  
const unsigned char FOLLOW_DELETED = 1; //路人  
const unsigned char FOLLOW_HATE = 2; //黑  
const unsigned char FOLLOW_FOLLOWING = 3; //粉  
 
struct FollowingInfo //关注  
{ 
    unsigned long long following;  
    unsigned long long follower;  
    unsigned char status; //状态标志  
    unsigned int makeTime; //建立时间  
    unsigned int lastChanged; //最后更改时间  
    FollowingInfo() 
    { 
        following = 0; 
        follower = 0; 
        status = 0; 
        makeTime = 0; 
        lastChanged = 0; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FollowingInfo & data) 
{ 
    ws << data.following;  
    ws << data.follower;  
    ws << data.status;  
    ws << data.makeTime;  
    ws << data.lastChanged;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FollowingInfo & data) 
{ 
        rs >> data.following;  
        rs >> data.follower;  
        rs >> data.status;  
        rs >> data.makeTime;  
        rs >> data.lastChanged;  
    return rs; 
} 
 
typedef std::vector<FollowingInfo> FollowingInfoArray;  
 
const unsigned short ID_GetFollowerReq = 1000; //获取粉丝列表  
struct GetFollowerReq //获取粉丝列表  
{ 
    unsigned long long uID;  
    unsigned char status; //所有/路人/黑/粉  
    GetFollowerReq() 
    { 
        uID = 0; 
        status = 0; 
    } 
    static const unsigned short GetProtoID() { return 1000;} 
    static const std::string GetProtoName() { return "ID_GetFollowerReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetFollowerReq & data) 
{ 
    ws << data.uID;  
    ws << data.status;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetFollowerReq & data) 
{ 
        rs >> data.uID;  
        rs >> data.status;  
    return rs; 
} 
 
const unsigned short ID_GetFollowerAck = 1001; //获取粉丝列表  
struct GetFollowerAck //获取粉丝列表  
{ 
    unsigned char status; //所有/路人/黑/粉  
    FollowingInfoArray follower;  
    GetFollowerAck() 
    { 
        status = 0; 
    } 
    static const unsigned short GetProtoID() { return 1001;} 
    static const std::string GetProtoName() { return "ID_GetFollowerAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetFollowerAck & data) 
{ 
    ws << data.status;  
    ws << data.follower;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetFollowerAck & data) 
{ 
        rs >> data.status;  
        rs >> data.follower;  
    return rs; 
} 
 
const unsigned short ID_GetFollowingReq = 1010; //获取关注列表  
struct GetFollowingReq //获取关注列表  
{ 
    unsigned long long uID;  
    unsigned char status; //所有/路人/黑/粉  
    GetFollowingReq() 
    { 
        uID = 0; 
        status = 0; 
    } 
    static const unsigned short GetProtoID() { return 1010;} 
    static const std::string GetProtoName() { return "ID_GetFollowingReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetFollowingReq & data) 
{ 
    ws << data.uID;  
    ws << data.status;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetFollowingReq & data) 
{ 
        rs >> data.uID;  
        rs >> data.status;  
    return rs; 
} 
 
const unsigned short ID_GetFollowingAck = 1011; //获取关注列表  
struct GetFollowingAck //获取关注列表  
{ 
    unsigned char status; //所有/路人/黑/粉  
    FollowingInfoArray following;  
    GetFollowingAck() 
    { 
        status = 0; 
    } 
    static const unsigned short GetProtoID() { return 1011;} 
    static const std::string GetProtoName() { return "ID_GetFollowingAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetFollowingAck & data) 
{ 
    ws << data.status;  
    ws << data.following;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetFollowingAck & data) 
{ 
        rs >> data.status;  
        rs >> data.following;  
    return rs; 
} 
 
const unsigned short ID_PokeReq = 1008; //操作  
struct PokeReq //操作  
{ 
    unsigned char dstStatus; //路人/黑/粉  
    unsigned long long following; //关注目标ID  
    PokeReq() 
    { 
        dstStatus = 0; 
        following = 0; 
    } 
    static const unsigned short GetProtoID() { return 1008;} 
    static const std::string GetProtoName() { return "ID_PokeReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PokeReq & data) 
{ 
    ws << data.dstStatus;  
    ws << data.following;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PokeReq & data) 
{ 
        rs >> data.dstStatus;  
        rs >> data.following;  
    return rs; 
} 
 
const unsigned short ID_PokeAck = 1009; //操作  
struct PokeAck //操作  
{ 
    FollowingInfo follow;  
    static const unsigned short GetProtoID() { return 1009;} 
    static const std::string GetProtoName() { return "ID_PokeAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PokeAck & data) 
{ 
    ws << data.follow;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PokeAck & data) 
{ 
        rs >> data.follow;  
    return rs; 
} 
 
#endif 
