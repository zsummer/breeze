 
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
 
struct Tracing //docker间追踪数据  
{ 
    static const unsigned short getProtoID() { return 1000;} 
    static const std::string getProtoName() { return "Tracing";} 
    unsigned int toDockerID; //forward转发时候先尝试通过DockerID进行转发 然后再尝试ServiceID   
    unsigned short toServiceType;  
    unsigned long long toServiceID;  
    unsigned int fromDockerID;  
    unsigned short fromServiceType;  
    unsigned long long fromServiceID;  
    unsigned int traceID; //本地cbID    
    unsigned int traceBackID; //把远程cbID透传回去   
    Tracing() 
    { 
        toDockerID = 0; 
        toServiceType = 0; 
        toServiceID = 0; 
        fromDockerID = 0; 
        fromServiceType = 0; 
        fromServiceID = 0; 
        traceID = 0; 
        traceBackID = 0; 
    } 
    Tracing(const unsigned int & toDockerID, const unsigned short & toServiceType, const unsigned long long & toServiceID, const unsigned int & fromDockerID, const unsigned short & fromServiceType, const unsigned long long & fromServiceID, const unsigned int & traceID, const unsigned int & traceBackID) 
    { 
        this->toDockerID = toDockerID; 
        this->toServiceType = toServiceType; 
        this->toServiceID = toServiceID; 
        this->fromDockerID = fromDockerID; 
        this->fromServiceType = fromServiceType; 
        this->fromServiceID = fromServiceID; 
        this->traceID = traceID; 
        this->traceBackID = traceBackID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Tracing & data) 
{ 
    ws << data.toDockerID;  
    ws << data.toServiceType;  
    ws << data.toServiceID;  
    ws << data.fromDockerID;  
    ws << data.fromServiceType;  
    ws << data.fromServiceID;  
    ws << data.traceID;  
    ws << data.traceBackID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Tracing & data) 
{ 
    rs >> data.toDockerID;  
    rs >> data.toServiceType;  
    rs >> data.toServiceID;  
    rs >> data.fromDockerID;  
    rs >> data.fromServiceType;  
    rs >> data.fromServiceID;  
    rs >> data.traceID;  
    rs >> data.traceBackID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const Tracing & info) 
{ 
    stm << "[\n"; 
    stm << "toDockerID=" << info.toDockerID << "\n"; 
    stm << "toServiceType=" << info.toServiceType << "\n"; 
    stm << "toServiceID=" << info.toServiceID << "\n"; 
    stm << "fromDockerID=" << info.fromDockerID << "\n"; 
    stm << "fromServiceType=" << info.fromServiceType << "\n"; 
    stm << "fromServiceID=" << info.fromServiceID << "\n"; 
    stm << "traceID=" << info.traceID << "\n"; 
    stm << "traceBackID=" << info.traceBackID << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct UserPreview //用户预览信息  
{ 
    static const unsigned short getProtoID() { return 1001;} 
    static const std::string getProtoName() { return "UserPreview";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long serviceID; //用户唯一ID  
    std::string serviceName; //昵称  
    std::string account; //帐号  
    short iconID; //头像  
    int level; //等级  
    UserPreview() 
    { 
        serviceID = 0; 
        iconID = 0; 
        level = 0; 
    } 
    UserPreview(const unsigned long long & serviceID, const std::string & serviceName, const std::string & account, const short & iconID, const int & level) 
    { 
        this->serviceID = serviceID; 
        this->serviceName = serviceName; 
        this->account = account; 
        this->iconID = iconID; 
        this->level = level; 
    } 
}; 
 
const std::vector<std::string>  UserPreview::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_UserPreview` (        `serviceID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `serviceName` varchar(255) NOT NULL DEFAULT '' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`serviceID`),        UNIQUE KEY `serviceName` (`serviceName`),        KEY `account` (`account`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_UserPreview` add `serviceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserPreview` change `serviceID`  `serviceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserPreview` add `serviceName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserPreview` change `serviceName`  `serviceName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserPreview` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserPreview` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserPreview` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserPreview` change `iconID`  `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserPreview` add `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserPreview` change `level`  `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  UserPreview::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `serviceID`,`serviceName`,`account`,`iconID`,`level` from `tb_UserPreview` where `serviceID` = ? "); 
    q << this->serviceID; 
    return q.pickSQL(); 
} 
std::string  UserPreview::getDBSelectPure() 
{ 
    return "select `serviceID`,`serviceName`,`account`,`iconID`,`level` from `tb_UserPreview` "; 
} 
std::string  UserPreview::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserPreview`(`serviceID`,`serviceName`,`account`,`iconID`,`level`) values(?,?,?,?,?)"); 
    q << this->serviceID; 
    q << this->serviceName; 
    q << this->account; 
    q << this->iconID; 
    q << this->level; 
    return q.pickSQL(); 
} 
std::string  UserPreview::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_UserPreview` where `serviceID` = ? "); 
    q << this->serviceID; 
    return q.pickSQL(); 
} 
std::string  UserPreview::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserPreview`(serviceID) values(? ) on duplicate key update `serviceName` = ?,`account` = ?,`iconID` = ?,`level` = ? "); 
    q << this->serviceID; 
    q << this->serviceName; 
    q << this->account; 
    q << this->iconID; 
    q << this->level; 
    return q.pickSQL(); 
} 
bool UserPreview::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch UserPreview from table `tb_UserPreview` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->serviceID; 
            result >> this->serviceName; 
            result >> this->account; 
            result >> this->iconID; 
            result >> this->level; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch UserPreview from table `tb_UserPreview` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserPreview & data) 
{ 
    ws << data.serviceID;  
    ws << data.serviceName;  
    ws << data.account;  
    ws << data.iconID;  
    ws << data.level;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserPreview & data) 
{ 
    rs >> data.serviceID;  
    rs >> data.serviceName;  
    rs >> data.account;  
    rs >> data.iconID;  
    rs >> data.level;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserPreview & info) 
{ 
    stm << "[\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "serviceName=" << info.serviceName << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "iconID=" << info.iconID << "\n"; 
    stm << "level=" << info.level << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<UserPreview> UserPreviewArray;  
 
 
typedef std::vector<unsigned long long> ServiceIDArray;  
 
struct UserBaseInfo //用户基础数据  
{ 
    static const unsigned short getProtoID() { return 1002;} 
    static const std::string getProtoName() { return "UserBaseInfo";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long serviceID; //用户唯一ID  
    std::string serviceName; //昵称  
    std::string account; //帐号  
    short iconID; //头像  
    int level; //等级  
    UserBaseInfo() 
    { 
        serviceID = 0; 
        iconID = 0; 
        level = 0; 
    } 
    UserBaseInfo(const unsigned long long & serviceID, const std::string & serviceName, const std::string & account, const short & iconID, const int & level) 
    { 
        this->serviceID = serviceID; 
        this->serviceName = serviceName; 
        this->account = account; 
        this->iconID = iconID; 
        this->level = level; 
    } 
}; 
 
const std::vector<std::string>  UserBaseInfo::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_UserBaseInfo` (        `serviceID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `serviceName` varchar(255) NOT NULL DEFAULT '' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`serviceID`),        UNIQUE KEY `serviceName` (`serviceName`),        KEY `account` (`account`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_UserBaseInfo` add `serviceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `serviceID`  `serviceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `serviceName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `serviceName`  `serviceName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `iconID`  `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `level`  `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  UserBaseInfo::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `serviceID`,`serviceName`,`account`,`iconID`,`level` from `tb_UserBaseInfo` where `serviceID` = ? "); 
    q << this->serviceID; 
    return q.pickSQL(); 
} 
std::string  UserBaseInfo::getDBSelectPure() 
{ 
    return "select `serviceID`,`serviceName`,`account`,`iconID`,`level` from `tb_UserBaseInfo` "; 
} 
std::string  UserBaseInfo::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserBaseInfo`(`serviceID`,`serviceName`,`account`,`iconID`,`level`) values(?,?,?,?,?)"); 
    q << this->serviceID; 
    q << this->serviceName; 
    q << this->account; 
    q << this->iconID; 
    q << this->level; 
    return q.pickSQL(); 
} 
std::string  UserBaseInfo::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_UserBaseInfo` where `serviceID` = ? "); 
    q << this->serviceID; 
    return q.pickSQL(); 
} 
std::string  UserBaseInfo::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserBaseInfo`(serviceID) values(? ) on duplicate key update `serviceName` = ?,`account` = ?,`iconID` = ?,`level` = ? "); 
    q << this->serviceID; 
    q << this->serviceName; 
    q << this->account; 
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
            result >> this->serviceID; 
            result >> this->serviceName; 
            result >> this->account; 
            result >> this->iconID; 
            result >> this->level; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch UserBaseInfo from table `tb_UserBaseInfo` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserBaseInfo & data) 
{ 
    ws << data.serviceID;  
    ws << data.serviceName;  
    ws << data.account;  
    ws << data.iconID;  
    ws << data.level;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserBaseInfo & data) 
{ 
    rs >> data.serviceID;  
    rs >> data.serviceName;  
    rs >> data.account;  
    rs >> data.iconID;  
    rs >> data.level;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserBaseInfo & info) 
{ 
    stm << "[\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "serviceName=" << info.serviceName << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "iconID=" << info.iconID << "\n"; 
    stm << "level=" << info.level << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<UserBaseInfo> UserBaseInfoArray;  
 
struct MoneyTree //摇钱树功能模块  
{ 
    static const unsigned short getProtoID() { return 1003;} 
    static const std::string getProtoName() { return "MoneyTree";} 
    unsigned int lastTime; //最后一次执行时间  
    unsigned int freeCount; //今日剩余免费次数  
    unsigned int payCount; //今日已购买次数  
    unsigned int statSum; //历史总和  
    unsigned int statCount; //历史总次数  
    MoneyTree() 
    { 
        lastTime = 0; 
        freeCount = 0; 
        payCount = 0; 
        statSum = 0; 
        statCount = 0; 
    } 
    MoneyTree(const unsigned int & lastTime, const unsigned int & freeCount, const unsigned int & payCount, const unsigned int & statSum, const unsigned int & statCount) 
    { 
        this->lastTime = lastTime; 
        this->freeCount = freeCount; 
        this->payCount = payCount; 
        this->statSum = statSum; 
        this->statCount = statCount; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const MoneyTree & data) 
{ 
    ws << data.lastTime;  
    ws << data.freeCount;  
    ws << data.payCount;  
    ws << data.statSum;  
    ws << data.statCount;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, MoneyTree & data) 
{ 
    rs >> data.lastTime;  
    rs >> data.freeCount;  
    rs >> data.payCount;  
    rs >> data.statSum;  
    rs >> data.statCount;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const MoneyTree & info) 
{ 
    stm << "[\n"; 
    stm << "lastTime=" << info.lastTime << "\n"; 
    stm << "freeCount=" << info.freeCount << "\n"; 
    stm << "payCount=" << info.payCount << "\n"; 
    stm << "statSum=" << info.statSum << "\n"; 
    stm << "statCount=" << info.statCount << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SimplePack //简单示例  
{ 
    static const unsigned short getProtoID() { return 1004;} 
    static const std::string getProtoName() { return "SimplePack";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id; //id, 对应数据库的结构为自增ID,key  
    std::string name; //昵称, 唯一索引  
    unsigned int createTime; //创建时间, 普通索引  
    MoneyTree moneyTree;  
    SimplePack() 
    { 
        id = 0; 
        createTime = 0; 
    } 
    SimplePack(const unsigned int & id, const std::string & name, const unsigned int & createTime, const MoneyTree & moneyTree) 
    { 
        this->id = id; 
        this->name = name; 
        this->createTime = createTime; 
        this->moneyTree = moneyTree; 
    } 
}; 
 
const std::vector<std::string>  SimplePack::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_SimplePack` (        `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT ,        `name` varchar(255) NOT NULL DEFAULT '' ,        `createTime` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`),        UNIQUE KEY `name` (`name`),        KEY `createTime` (`createTime`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_SimplePack` add `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_SimplePack` change `id`  `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_SimplePack` add `name`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_SimplePack` change `name`  `name`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_SimplePack` add `createTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_SimplePack` change `createTime`  `createTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_SimplePack` add `moneyTree`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_SimplePack` change `moneyTree`  `moneyTree`  longblob NOT NULL "); 
    return std::move(ret); 
} 
std::string  SimplePack::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`name`,`createTime`,`moneyTree` from `tb_SimplePack` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  SimplePack::getDBSelectPure() 
{ 
    return "select `id`,`name`,`createTime`,`moneyTree` from `tb_SimplePack` "; 
} 
std::string  SimplePack::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_SimplePack`(`name`,`createTime`,`moneyTree`) values(?,?,?)"); 
    q << this->name; 
    q << this->createTime; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->moneyTree; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when insert SimplePack.moneyTree error=" << e.what()); 
    } 
    return q.pickSQL(); 
} 
std::string  SimplePack::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_SimplePack` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  SimplePack::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_SimplePack`(id) values(? ) on duplicate key update `name` = ?,`createTime` = ?,`moneyTree` = ? "); 
    q << this->id; 
    q << this->name; 
    q << this->createTime; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->moneyTree; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when update SimplePack.moneyTree error=" << e.what()); 
    } 
    return q.pickSQL(); 
} 
bool SimplePack::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch SimplePack from table `tb_SimplePack` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->name; 
            result >> this->createTime; 
            try 
            { 
                std::string blob; 
                result >> blob; 
                if(!blob.empty()) 
                { 
                    zsummer::proto4z::ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false); 
                    rs >> this->moneyTree; 
                } 
            } 
            catch(const std::exception & e) 
            { 
                LOGW("catch one except error when fetch SimplePack.moneyTree  from table `tb_SimplePack` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
            } 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch SimplePack from table `tb_SimplePack` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SimplePack & data) 
{ 
    ws << data.id;  
    ws << data.name;  
    ws << data.createTime;  
    ws << data.moneyTree;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SimplePack & data) 
{ 
    rs >> data.id;  
    rs >> data.name;  
    rs >> data.createTime;  
    rs >> data.moneyTree;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SimplePack & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "name=" << info.name << "\n"; 
    stm << "createTime=" << info.createTime << "\n"; 
    stm << "moneyTree=" << info.moneyTree << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
