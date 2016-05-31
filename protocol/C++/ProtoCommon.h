 
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
    static const unsigned short getProtoID() { return 200;} 
    static const std::string getProtoName() { return "UserPreview";} 
    unsigned long long uID; //用户ID  
    std::string uName; //昵称  
    short iconID; //头像  
    std::string account; //帐号  
    UserPreview() 
    { 
        uID = 0; 
        iconID = 0; 
    } 
    UserPreview(const unsigned long long & uID, const std::string & uName, const short & iconID, const std::string & account) 
    { 
        this->uID = uID; 
        this->uName = uName; 
        this->iconID = iconID; 
        this->account = account; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserPreview & data) 
{ 
    ws << data.uID;  
    ws << data.uName;  
    ws << data.iconID;  
    ws << data.account;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserPreview & data) 
{ 
    rs >> data.uID;  
    rs >> data.uName;  
    rs >> data.iconID;  
    rs >> data.account;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserPreview & info) 
{ 
    stm << "[\n"; 
    stm << "uID=" << info.uID << "\n"; 
    stm << "uName=" << info.uName << "\n"; 
    stm << "iconID=" << info.iconID << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<UserPreview> UserPreviewArray;  
 
 
typedef std::vector<unsigned long long> UIDS;  
 
struct UserBaseInfo //用户基础数据  
{ 
    static const unsigned short getProtoID() { return 201;} 
    static const std::string getProtoName() { return "UserBaseInfo";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long uID; //用户唯一ID  
    std::string account; //帐号  
    std::string nickName; //昵称  
    short iconID; //头像  
    int level; //等级  
    UserBaseInfo() 
    { 
        uID = 0; 
        iconID = 0; 
        level = 0; 
    } 
    UserBaseInfo(const unsigned long long & uID, const std::string & account, const std::string & nickName, const short & iconID, const int & level) 
    { 
        this->uID = uID; 
        this->account = account; 
        this->nickName = nickName; 
        this->iconID = iconID; 
        this->level = level; 
    } 
}; 
 
const std::vector<std::string>  UserBaseInfo::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_UserBaseInfo` (        `uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`uID`)  ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_UserBaseInfo` add `uID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `uID`  `uID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `nickName`  `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `iconID`  `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `level`  `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  UserBaseInfo::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `uID`,`account`,`nickName`,`iconID`,`level` from `tb_UserBaseInfo` where `uID` = ? "); 
    q << this->uID; 
    return q.pickSQL(); 
} 
std::string  UserBaseInfo::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserBaseInfo`(`uID`,`account`,`nickName`,`iconID`,`level`) values(?,?,?,?,?)"); 
    q << this->uID; 
    q << this->account; 
    q << this->nickName; 
    q << this->iconID; 
    q << this->level; 
    return q.pickSQL(); 
} 
std::string  UserBaseInfo::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_UserBaseInfo` where `uID` = ? "); 
    q << this->uID; 
    return q.pickSQL(); 
} 
std::string  UserBaseInfo::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserBaseInfo`(uID) values(? ) on duplicate key update `account` = ?,`nickName` = ?,`iconID` = ?,`level` = ? "); 
    q << this->account; 
    q << this->nickName; 
    q << this->iconID; 
    q << this->level; 
    return q.pickSQL(); 
} 
bool UserBaseInfo::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch UserBaseInfo from table `tb_UserBaseInfo` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->uID; 
            result >> this->account; 
            result >> this->nickName; 
            result >> this->iconID; 
            result >> this->level; 
            return true;  
        } 
    } 
    catch(std::runtime_error e) 
    { 
        LOGE("catch one except error when fetch UserBaseInfo from table `tb_UserBaseInfo` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserBaseInfo & data) 
{ 
    ws << data.uID;  
    ws << data.account;  
    ws << data.nickName;  
    ws << data.iconID;  
    ws << data.level;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserBaseInfo & data) 
{ 
    rs >> data.uID;  
    rs >> data.account;  
    rs >> data.nickName;  
    rs >> data.iconID;  
    rs >> data.level;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserBaseInfo & info) 
{ 
    stm << "[\n"; 
    stm << "uID=" << info.uID << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "nickName=" << info.nickName << "\n"; 
    stm << "iconID=" << info.iconID << "\n"; 
    stm << "level=" << info.level << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<UserBaseInfo> UserBaseInfoArray;  
 
#endif 
