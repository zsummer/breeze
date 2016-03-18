 
#ifndef _PROTOCOMMON_H_ 
#define _PROTOCOMMON_H_ 
 
 
enum  : unsigned short 
{ 
    EC_SUCCESS = 0, //成功  
    EC_ERROR = 1, //错误  
    EC_INNER_ERROR = 2, //内部错误  
    EC_DB_ERROR = 3, //数据库错误  
    EC_PARAM_DENIED = 4, //非法参数  
    EC_PERMISSION_DENIED = 5, //权限错误  
    EC_REQUEST_EXPIRE = 6, //请求操作已过期  
    EC_TARGET_NOT_EXIST = 7, //操作目标不存在  
    EC_TOKEN_EXPIRE = 8, //令牌过期  
    EC_USER_NOT_FOUND = 50, //错误的用户信息  
    EC_USER_OFFLINE = 51, //错误的用户信息  
    EC_FRIEND_DUPLICATE = 100, //请先删除与该好友建立的关系  
    EC_FRIEND_CEILING = 101, //达到好友上限  
    EC_FRIEND_REFUSE = 102, //不能添加对方为好友  
    EC_FRIEND_NOT_EXIST = 103, //好友不存在  
}; 
 
struct UserPreview //用户预览信息  
{ 
    unsigned long long uID; //用户唯一ID  
    std::string account; //帐号  
    std::string nickName; //昵称  
    short iconID; //头像  
    UserPreview() 
    { 
        uID = 0; 
        iconID = 0; 
    } 
    UserPreview(const unsigned long long & uID, const std::string & account, const std::string & nickName, const short & iconID) 
    { 
        this->uID = uID; 
        this->account = account; 
        this->nickName = nickName; 
        this->iconID = iconID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserPreview & data) 
{ 
    ws << data.uID;  
    ws << data.account;  
    ws << data.nickName;  
    ws << data.iconID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserPreview & data) 
{ 
        rs >> data.uID;  
        rs >> data.account;  
        rs >> data.nickName;  
        rs >> data.iconID;  
    return rs; 
} 
 
 
typedef std::vector<UserPreview> UserPreviewArray;  
 
 
typedef std::vector<unsigned long long> UIDS;  
 
struct UserBaseInfo //用户预览信息  
{ 
    unsigned long long uID; //用户唯一ID  
    std::string account; //帐号  
    std::string nickName; //昵称  
    short iconID; //头像  
    UserBaseInfo() 
    { 
        uID = 0; 
        iconID = 0; 
    } 
    UserBaseInfo(const unsigned long long & uID, const std::string & account, const std::string & nickName, const short & iconID) 
    { 
        this->uID = uID; 
        this->account = account; 
        this->nickName = nickName; 
        this->iconID = iconID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserBaseInfo & data) 
{ 
    ws << data.uID;  
    ws << data.account;  
    ws << data.nickName;  
    ws << data.iconID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserBaseInfo & data) 
{ 
        rs >> data.uID;  
        rs >> data.account;  
        rs >> data.nickName;  
        rs >> data.iconID;  
    return rs; 
} 
 
 
typedef std::vector<UserPreview> UserPreviewArray;  
 
 
typedef std::vector<unsigned long long> UIDS;  
 
#endif 
