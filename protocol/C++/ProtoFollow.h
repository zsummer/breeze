 
#ifndef _PROTOFOLLOW_H_ 
#define _PROTOFOLLOW_H_ 
 
 
enum FOLLOW_STATUS : unsigned char 
{ 
    FOLLOW_INVALID = 0,  
    FOLLOW_DELETED = 1, //路人  
    FOLLOW_HATE = 2, //黑  
    FOLLOW_FOLLOWING = 3, //粉  
}; 
 
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
    FollowingInfo(const unsigned long long & following, const unsigned long long & follower, const unsigned char & status, const unsigned int & makeTime, const unsigned int & lastChanged) 
    { 
        this->following = following; 
        this->follower = follower; 
        this->status = status; 
        this->makeTime = makeTime; 
        this->lastChanged = lastChanged; 
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
 
struct GetFollowerReq //获取粉丝列表  
{ 
    static const unsigned short GetProtoID() { return 1000;} 
    static const std::string GetProtoName() { return "ID_GetFollowerReq";} 
    unsigned long long uID;  
    unsigned char status; //所有/路人/黑/粉  
    GetFollowerReq() 
    { 
        uID = 0; 
        status = 0; 
    } 
    GetFollowerReq(const unsigned long long & uID, const unsigned char & status) 
    { 
        this->uID = uID; 
        this->status = status; 
    } 
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
 
struct GetFollowerAck //获取粉丝列表  
{ 
    static const unsigned short GetProtoID() { return 1001;} 
    static const std::string GetProtoName() { return "ID_GetFollowerAck";} 
    unsigned char status; //所有/路人/黑/粉  
    FollowingInfoArray follower;  
    GetFollowerAck() 
    { 
        status = 0; 
    } 
    GetFollowerAck(const unsigned char & status, const FollowingInfoArray & follower) 
    { 
        this->status = status; 
        this->follower = follower; 
    } 
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
 
struct GetFollowingReq //获取关注列表  
{ 
    static const unsigned short GetProtoID() { return 1002;} 
    static const std::string GetProtoName() { return "ID_GetFollowingReq";} 
    unsigned long long uID;  
    unsigned char status; //所有/路人/黑/粉  
    GetFollowingReq() 
    { 
        uID = 0; 
        status = 0; 
    } 
    GetFollowingReq(const unsigned long long & uID, const unsigned char & status) 
    { 
        this->uID = uID; 
        this->status = status; 
    } 
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
 
struct GetFollowingAck //获取关注列表  
{ 
    static const unsigned short GetProtoID() { return 1003;} 
    static const std::string GetProtoName() { return "ID_GetFollowingAck";} 
    unsigned char status; //所有/路人/黑/粉  
    FollowingInfoArray following;  
    GetFollowingAck() 
    { 
        status = 0; 
    } 
    GetFollowingAck(const unsigned char & status, const FollowingInfoArray & following) 
    { 
        this->status = status; 
        this->following = following; 
    } 
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
 
struct PokeReq //操作  
{ 
    static const unsigned short GetProtoID() { return 1004;} 
    static const std::string GetProtoName() { return "ID_PokeReq";} 
    unsigned char dstStatus; //路人/黑/粉  
    unsigned long long following; //关注目标ID  
    PokeReq() 
    { 
        dstStatus = 0; 
        following = 0; 
    } 
    PokeReq(const unsigned char & dstStatus, const unsigned long long & following) 
    { 
        this->dstStatus = dstStatus; 
        this->following = following; 
    } 
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
 
struct PokeAck //操作  
{ 
    static const unsigned short GetProtoID() { return 1005;} 
    static const std::string GetProtoName() { return "ID_PokeAck";} 
    FollowingInfo follow;  
    PokeAck() 
    { 
    } 
    PokeAck(const FollowingInfo & follow) 
    { 
        this->follow = follow; 
    } 
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
