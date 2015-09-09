 
#ifndef _PROTOCOMMON_H_ 
#define _PROTOCOMMON_H_ 
 
const unsigned short EC_SUCCESS = 0; //成功 
const unsigned short EC_ERROR = 1; //错误 
const unsigned short EC_INNER_ERROR = 2; //内部错误 
const unsigned short EC_DB_ERROR = 3; //数据库错误 
const unsigned short EC_PARAM_DENIED = 4; //非法参数 
const unsigned short EC_PERMISSION_DENIED = 5; //权限错误 
const unsigned short EC_REQUEST_EXPIRE = 6; //请求操作已过期 
const unsigned short EC_TARGET_NOT_EXIST = 7; //操作目标不存在 
const unsigned short EC_TOKEN_EXPIRE = 8; //令牌过期 
const unsigned short EC_USER_NOT_FOUND = 50; //错误的用户信息 
const unsigned short EC_USER_OFFLINE = 51; //错误的用户信息 
const unsigned short EC_FRIEND_DUPLICATE = 100; //请先删除与该好友建立的关系 
const unsigned short EC_FRIEND_CEILING = 101; //达到好友上限 
const unsigned short EC_FRIEND_REFUSE = 102; //不能添加对方为好友 
const unsigned short EC_FRIEND_NOT_EXIST = 103; //好友不存在 
 
struct SessionToken //认证令牌 
{ 
    unsigned long long uID;  
    std::string token;  
    unsigned int expire;  
    SessionToken() 
    { 
        uID = 0; 
        expire = 0; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SessionToken & data) 
{ 
    ws << data.uID; 
    ws << data.token; 
    ws << data.expire; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SessionToken & data) 
{ 
        rs >> data.uID;  
        rs >> data.token;  
        rs >> data.expire;  
    return rs; 
} 
 
struct BaseInfo //用户基础信息 
{ 
    unsigned long long uID; //用户唯一ID 
    std::string account; //帐号 
    std::string nickName; //昵称 
    short iconID; //头像 
    int diamond; //当前剩余的充值钻石 
    int hisotryDiamond; //历史充值钻石总额 
    int giftDiamond; //当前剩余的赠送钻石 
    unsigned int joinTime; //加入时间 
    BaseInfo() 
    { 
        uID = 0; 
        iconID = 0; 
        diamond = 0; 
        hisotryDiamond = 0; 
        giftDiamond = 0; 
        joinTime = 0; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const BaseInfo & data) 
{ 
    ws << data.uID; 
    ws << data.account; 
    ws << data.nickName; 
    ws << data.iconID; 
    ws << data.diamond; 
    ws << data.hisotryDiamond; 
    ws << data.giftDiamond; 
    ws << data.joinTime; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, BaseInfo & data) 
{ 
        rs >> data.uID;  
        rs >> data.account;  
        rs >> data.nickName;  
        rs >> data.iconID;  
        rs >> data.diamond;  
        rs >> data.hisotryDiamond;  
        rs >> data.giftDiamond;  
        rs >> data.joinTime;  
    return rs; 
} 
 
typedef std::vector<BaseInfo> BaseInfoArray;  
 
typedef std::vector<unsigned long long> UIDS;  
const unsigned short ETRIGGER_USER_LOGIN = 0; //用户登录, 用户ID 
const unsigned short ETRIGGER_USER_LOGOUT = 1; //用户登出, 用户ID 
 
const unsigned short ID_Heartbeat = 200; //心跳包 
struct Heartbeat //心跳包 
{ 
    unsigned int timeStamp; //服务器当前UTC时间戳 
    unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
    Heartbeat() 
    { 
        timeStamp = 0; 
        timeTick = 0; 
    } 
    static const unsigned short GetProtoID() { return 200;} 
    static const std::string GetProtoName() { return "ID_Heartbeat";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Heartbeat & data) 
{ 
    ws << data.timeStamp; 
    ws << data.timeTick; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Heartbeat & data) 
{ 
        rs >> data.timeStamp;  
        rs >> data.timeTick;  
    return rs; 
} 
 
const unsigned short ID_HeartbeatEcho = 201; //心跳包需要立刻回复 
struct HeartbeatEcho //心跳包需要立刻回复 
{ 
    unsigned int timeStamp; //服务器当前UTC时间戳 
    unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
    HeartbeatEcho() 
    { 
        timeStamp = 0; 
        timeTick = 0; 
    } 
    static const unsigned short GetProtoID() { return 201;} 
    static const std::string GetProtoName() { return "ID_HeartbeatEcho";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const HeartbeatEcho & data) 
{ 
    ws << data.timeStamp; 
    ws << data.timeTick; 
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, HeartbeatEcho & data) 
{ 
        rs >> data.timeStamp;  
        rs >> data.timeTick;  
    return rs; 
} 
 
#endif 
