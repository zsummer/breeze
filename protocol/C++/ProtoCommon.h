 
#ifndef _PROTOCOMMON_H_ 
#define _PROTOCOMMON_H_ 
 
 
enum ERROR_CODE : unsigned short 
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
    EC_AVATAR_NOT_FOUND = 50, //错误的用户信息  
    EC_AVATAR_COUNT_LIMITE = 51, //创建用户的数量超出限制  
    EC_AVATAR_FREQ_LIMITE = 52, //创建用户的频率超出限制  
    EC_AVATAR_NAME_CONFLICT = 53, //创建用户的昵称冲突  
    EC_FRIEND_DUPLICATE = 100, //请先删除与该好友建立的关系  
    EC_FRIEND_CEILING = 101, //达到好友上限  
    EC_FRIEND_REFUSE = 102, //不能添加对方为好友  
    EC_FRIEND_NOT_EXIST = 103, //好友不存在  
    EC_SERVICE_NOT_OPEN = 104, //服务未开放  
}; 
 
struct Routing //docker to docker 路由信息  
{ 
    static const unsigned short getProtoID() { return 1000;} 
    static const std::string getProtoName() { return "Routing";} 
    unsigned short toServiceType; //目标service类型  
    unsigned long long toServiceID; //目标serviceID, 如果是单例 ID为InvalidServiceID.   
    unsigned short fromServiceType; //来源  
    unsigned long long fromServiceID; //来源  
    unsigned long long traceID; //本地产生的回调ID  
    unsigned long long traceBackID; //远端产生的回调ID  
    Routing() 
    { 
        toServiceType = 0; 
        toServiceID = 0; 
        fromServiceType = 0; 
        fromServiceID = 0; 
        traceID = 0; 
        traceBackID = 0; 
    } 
    Routing(const unsigned short & toServiceType, const unsigned long long & toServiceID, const unsigned short & fromServiceType, const unsigned long long & fromServiceID, const unsigned long long & traceID, const unsigned long long & traceBackID) 
    { 
        this->toServiceType = toServiceType; 
        this->toServiceID = toServiceID; 
        this->fromServiceType = fromServiceType; 
        this->fromServiceID = fromServiceID; 
        this->traceID = traceID; 
        this->traceBackID = traceBackID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Routing & data) 
{ 
    ws << data.toServiceType;  
    ws << data.toServiceID;  
    ws << data.fromServiceType;  
    ws << data.fromServiceID;  
    ws << data.traceID;  
    ws << data.traceBackID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Routing & data) 
{ 
    rs >> data.toServiceType;  
    rs >> data.toServiceID;  
    rs >> data.fromServiceType;  
    rs >> data.fromServiceID;  
    rs >> data.traceID;  
    rs >> data.traceBackID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const Routing & info) 
{ 
    stm << "["; 
    stm << "toServiceType=" << info.toServiceType << ","; 
    stm << "toServiceID=" << info.toServiceID << ","; 
    stm << "fromServiceType=" << info.fromServiceType << ","; 
    stm << "fromServiceID=" << info.fromServiceID << ","; 
    stm << "traceID=" << info.traceID << ","; 
    stm << "traceBackID=" << info.traceBackID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct OutOfBand //带外信息  
{ 
    static const unsigned short getProtoID() { return 1001;} 
    static const std::string getProtoName() { return "OutOfBand";} 
    unsigned long long clientDockerID; //该数据由docker获得来自客户端的消息时自动填充.  
    unsigned int clientSessionID; //该数据由docker获得来自客户端的消息时自动填充.  
    unsigned long long clientAvatarID; //该数据由docker获得来自客户端的消息时自动填充.  
    OutOfBand() 
    { 
        clientDockerID = 0; 
        clientSessionID = 0; 
        clientAvatarID = 0; 
    } 
    OutOfBand(const unsigned long long & clientDockerID, const unsigned int & clientSessionID, const unsigned long long & clientAvatarID) 
    { 
        this->clientDockerID = clientDockerID; 
        this->clientSessionID = clientSessionID; 
        this->clientAvatarID = clientAvatarID; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const OutOfBand & data) 
{ 
    ws << data.clientDockerID;  
    ws << data.clientSessionID;  
    ws << data.clientAvatarID;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, OutOfBand & data) 
{ 
    rs >> data.clientDockerID;  
    rs >> data.clientSessionID;  
    rs >> data.clientAvatarID;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const OutOfBand & info) 
{ 
    stm << "["; 
    stm << "clientDockerID=" << info.clientDockerID << ","; 
    stm << "clientSessionID=" << info.clientSessionID << ","; 
    stm << "clientAvatarID=" << info.clientAvatarID << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct Tracing //docker间追踪数据  
{ 
    static const unsigned short getProtoID() { return 1002;} 
    static const std::string getProtoName() { return "Tracing";} 
    Routing routing; //路由信息  
    OutOfBand oob; //来自客户端的带外信息  
    Tracing() 
    { 
    } 
    Tracing(const Routing & routing, const OutOfBand & oob) 
    { 
        this->routing = routing; 
        this->oob = oob; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Tracing & data) 
{ 
    ws << data.routing;  
    ws << data.oob;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Tracing & data) 
{ 
    rs >> data.routing;  
    rs >> data.oob;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const Tracing & info) 
{ 
    stm << "["; 
    stm << "routing=" << info.routing << ","; 
    stm << "oob=" << info.oob << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<unsigned long long> ServiceIDArray;  
 
 
typedef std::map<unsigned long long, unsigned long long> ServiceIDMap;  
 
 
typedef std::vector<std::string> AccountArray;  
 
struct AvatarPreview //用户预览信息  
{ 
    static const unsigned short getProtoID() { return 1003;} 
    static const std::string getProtoName() { return "AvatarPreview";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long avatarID; //用户唯一ID, 对应AvatarService的ServiceID  
    std::string avatarName; //用户唯一昵称, 对应AvatarService的ServiceName  
    std::string account; //帐号  
    unsigned long long iconID; //头像  
    unsigned long long modeID; //模型  
    double level; //等级  
    AvatarPreview() 
    { 
        avatarID = 0; 
        iconID = 0; 
        modeID = 0; 
        level = 0.0; 
    } 
    AvatarPreview(const unsigned long long & avatarID, const std::string & avatarName, const std::string & account, const unsigned long long & iconID, const unsigned long long & modeID, const double & level) 
    { 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->account = account; 
        this->iconID = iconID; 
        this->modeID = modeID; 
        this->level = level; 
    } 
}; 
 
std::vector<std::string>  AvatarPreview::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_AvatarPreview` (        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarName` varchar(255) NOT NULL DEFAULT '' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`avatarID`),        UNIQUE KEY `avatarName` (`avatarName`),        KEY `account` (`account`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_AvatarPreview` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `avatarName`  `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `iconID`  `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `modeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `modeID`  `modeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `level`  `level`  double NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  AvatarPreview::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `avatarID`,`avatarName`,`account`,`iconID`,`modeID`,`level` from `tb_AvatarPreview` where `avatarID` = ? "); 
    q << this->avatarID; 
    return q.pickSQL(); 
} 
std::string  AvatarPreview::getDBSelectPure() 
{ 
    return "select `avatarID`,`avatarName`,`account`,`iconID`,`modeID`,`level` from `tb_AvatarPreview` "; 
} 
std::string  AvatarPreview::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarPreview`(`avatarID`,`avatarName`,`account`,`iconID`,`modeID`,`level`) values(?,?,?,?,?,?)"); 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->account; 
    q << this->iconID; 
    q << this->modeID; 
    q << this->level; 
    return q.pickSQL(); 
} 
std::string  AvatarPreview::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_AvatarPreview` where `avatarID` = ? "); 
    q << this->avatarID; 
    return q.pickSQL(); 
} 
std::string  AvatarPreview::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarPreview`(avatarID) values(? ) on duplicate key update `avatarName` = ?,`account` = ?,`iconID` = ?,`modeID` = ?,`level` = ? "); 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->account; 
    q << this->iconID; 
    q << this->modeID; 
    q << this->level; 
    return q.pickSQL(); 
} 
bool AvatarPreview::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch AvatarPreview from table `tb_AvatarPreview` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->avatarID; 
            result >> this->avatarName; 
            result >> this->account; 
            result >> this->iconID; 
            result >> this->modeID; 
            result >> this->level; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch AvatarPreview from table `tb_AvatarPreview` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AvatarPreview & data) 
{ 
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.account;  
    ws << data.iconID;  
    ws << data.modeID;  
    ws << data.level;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AvatarPreview & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.account;  
    rs >> data.iconID;  
    rs >> data.modeID;  
    rs >> data.level;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AvatarPreview & info) 
{ 
    stm << "["; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "account=" << info.account << ","; 
    stm << "iconID=" << info.iconID << ","; 
    stm << "modeID=" << info.modeID << ","; 
    stm << "level=" << info.level << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<AvatarPreview> AvatarPreviewArray;  
 
struct AvatarBaseInfo //用户基础数据  
{ 
    static const unsigned short getProtoID() { return 1004;} 
    static const std::string getProtoName() { return "AvatarBaseInfo";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long avatarID; //用户唯一ID, 对应AvatarService的ServiceID  
    std::string avatarName; //用户唯一昵称, 对应AvatarService的ServiceName  
    std::string account; //帐号  
    unsigned long long iconID; //头像  
    unsigned long long modeID; //模型  
    double level; //等级  
    double exp; //经验  
    double gold; //金币  
    double diamond; //钻石  
    unsigned long long createTime; //角色创建时间  
    AvatarBaseInfo() 
    { 
        avatarID = 0; 
        iconID = 0; 
        modeID = 0; 
        level = 0.0; 
        exp = 0.0; 
        gold = 0.0; 
        diamond = 0.0; 
        createTime = 0; 
    } 
    AvatarBaseInfo(const unsigned long long & avatarID, const std::string & avatarName, const std::string & account, const unsigned long long & iconID, const unsigned long long & modeID, const double & level, const double & exp, const double & gold, const double & diamond, const unsigned long long & createTime) 
    { 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->account = account; 
        this->iconID = iconID; 
        this->modeID = modeID; 
        this->level = level; 
        this->exp = exp; 
        this->gold = gold; 
        this->diamond = diamond; 
        this->createTime = createTime; 
    } 
}; 
 
std::vector<std::string>  AvatarBaseInfo::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_AvatarBaseInfo` (        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarName` varchar(255) NOT NULL DEFAULT '' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`avatarID`),        UNIQUE KEY `avatarName` (`avatarName`),        KEY `account` (`account`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `avatarName`  `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `iconID`  `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `modeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `modeID`  `modeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `level`  `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `exp`  `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `gold`  `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `diamond`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `diamond`  `diamond`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `createTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `createTime`  `createTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  AvatarBaseInfo::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `avatarID`,`avatarName`,`account`,`iconID`,`modeID`,`level`,`exp`,`gold`,`diamond`,`createTime` from `tb_AvatarBaseInfo` where `avatarID` = ? "); 
    q << this->avatarID; 
    return q.pickSQL(); 
} 
std::string  AvatarBaseInfo::getDBSelectPure() 
{ 
    return "select `avatarID`,`avatarName`,`account`,`iconID`,`modeID`,`level`,`exp`,`gold`,`diamond`,`createTime` from `tb_AvatarBaseInfo` "; 
} 
std::string  AvatarBaseInfo::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarBaseInfo`(`avatarID`,`avatarName`,`account`,`iconID`,`modeID`,`level`,`exp`,`gold`,`diamond`,`createTime`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->account; 
    q << this->iconID; 
    q << this->modeID; 
    q << this->level; 
    q << this->exp; 
    q << this->gold; 
    q << this->diamond; 
    q << this->createTime; 
    return q.pickSQL(); 
} 
std::string  AvatarBaseInfo::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_AvatarBaseInfo` where `avatarID` = ? "); 
    q << this->avatarID; 
    return q.pickSQL(); 
} 
std::string  AvatarBaseInfo::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarBaseInfo`(avatarID) values(? ) on duplicate key update `avatarName` = ?,`account` = ?,`iconID` = ?,`modeID` = ?,`level` = ?,`exp` = ?,`gold` = ?,`diamond` = ?,`createTime` = ? "); 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->account; 
    q << this->iconID; 
    q << this->modeID; 
    q << this->level; 
    q << this->exp; 
    q << this->gold; 
    q << this->diamond; 
    q << this->createTime; 
    return q.pickSQL(); 
} 
bool AvatarBaseInfo::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch AvatarBaseInfo from table `tb_AvatarBaseInfo` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->avatarID; 
            result >> this->avatarName; 
            result >> this->account; 
            result >> this->iconID; 
            result >> this->modeID; 
            result >> this->level; 
            result >> this->exp; 
            result >> this->gold; 
            result >> this->diamond; 
            result >> this->createTime; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch AvatarBaseInfo from table `tb_AvatarBaseInfo` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AvatarBaseInfo & data) 
{ 
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.account;  
    ws << data.iconID;  
    ws << data.modeID;  
    ws << data.level;  
    ws << data.exp;  
    ws << data.gold;  
    ws << data.diamond;  
    ws << data.createTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AvatarBaseInfo & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.account;  
    rs >> data.iconID;  
    rs >> data.modeID;  
    rs >> data.level;  
    rs >> data.exp;  
    rs >> data.gold;  
    rs >> data.diamond;  
    rs >> data.createTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AvatarBaseInfo & info) 
{ 
    stm << "["; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "account=" << info.account << ","; 
    stm << "iconID=" << info.iconID << ","; 
    stm << "modeID=" << info.modeID << ","; 
    stm << "level=" << info.level << ","; 
    stm << "exp=" << info.exp << ","; 
    stm << "gold=" << info.gold << ","; 
    stm << "diamond=" << info.diamond << ","; 
    stm << "createTime=" << info.createTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<AvatarBaseInfo> AvatarBaseInfoArray;  
 
struct ItemInfo //道具字典  
{ 
    static const unsigned short getProtoID() { return 1005;} 
    static const std::string getProtoName() { return "ItemInfo";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned short stacks; //可堆叠个数,0和1都是1次  
    ItemInfo() 
    { 
        stacks = 0; 
    } 
    ItemInfo(const unsigned short & stacks) 
    { 
        this->stacks = stacks; 
    } 
}; 
 
std::vector<std::string>  ItemInfo::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_ItemInfo` ( ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_ItemInfo` add `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_ItemInfo` change `stacks`  `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  ItemInfo::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `stacks` from `tb_ItemInfo` where "); 
    return q.pickSQL(); 
} 
std::string  ItemInfo::getDBSelectPure() 
{ 
    return "select `stacks` from `tb_ItemInfo` "; 
} 
std::string  ItemInfo::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_ItemInfo`(`stacks`) values(?)"); 
    q << this->stacks; 
    return q.pickSQL(); 
} 
std::string  ItemInfo::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_ItemInfo` where  "); 
    return q.pickSQL(); 
} 
std::string  ItemInfo::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_ItemInfo`() values( ) on duplicate key update `stacks` = ? "); 
    q << this->stacks; 
    return q.pickSQL(); 
} 
bool ItemInfo::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch ItemInfo from table `tb_ItemInfo` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->stacks; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch ItemInfo from table `tb_ItemInfo` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ItemInfo & data) 
{ 
    ws << data.stacks;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ItemInfo & data) 
{ 
    rs >> data.stacks;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ItemInfo & info) 
{ 
    stm << "["; 
    stm << "stacks=" << info.stacks << ","; 
    stm << "]"; 
    return stm; 
} 
 
enum ChatChannelEnum : unsigned short 
{ 
    CC_WORLD = 0, //世界频道  
    CC_PRIVATE = 1, //私人频道  
    CC_SYSTEM = 2, //系统频道  
    CC_GROUP = 3, //同编队频道  
    CC_CAMP = 4, //同阵营频道  
    CC_SCENE = 5, //同场景频道  
}; 
 
struct LogChat //聊天日志  
{ 
    static const unsigned short getProtoID() { return 1006;} 
    static const std::string getProtoName() { return "LogChat";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned short channelID;  
    unsigned long long sourceID;  
    std::string sourceName;  
    unsigned long long targetID;  
    std::string targetName;  
    std::string msg;  
    unsigned long long chatTime;  
    LogChat() 
    { 
        id = 0; 
        channelID = 0; 
        sourceID = 0; 
        targetID = 0; 
        chatTime = 0; 
    } 
    LogChat(const unsigned long long & id, const unsigned short & channelID, const unsigned long long & sourceID, const std::string & sourceName, const unsigned long long & targetID, const std::string & targetName, const std::string & msg, const unsigned long long & chatTime) 
    { 
        this->id = id; 
        this->channelID = channelID; 
        this->sourceID = sourceID; 
        this->sourceName = sourceName; 
        this->targetID = targetID; 
        this->targetName = targetName; 
        this->msg = msg; 
        this->chatTime = chatTime; 
    } 
}; 
 
std::vector<std::string>  LogChat::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_LogChat` (        `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT ,        `sourceID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `targetID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `chatTime` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`),        KEY `sourceID` (`sourceID`),        KEY `targetID` (`targetID`),        KEY `chatTime` (`chatTime`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_LogChat` add `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_LogChat` change `id`  `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_LogChat` add `channelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` change `channelID`  `channelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` add `sourceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` change `sourceID`  `sourceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` add `sourceName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogChat` change `sourceName`  `sourceName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogChat` add `targetID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` change `targetID`  `targetID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` add `targetName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogChat` change `targetName`  `targetName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogChat` add `msg`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogChat` change `msg`  `msg`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogChat` add `chatTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogChat` change `chatTime`  `chatTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  LogChat::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`channelID`,`sourceID`,`sourceName`,`targetID`,`targetName`,`msg`,`chatTime` from `tb_LogChat` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  LogChat::getDBSelectPure() 
{ 
    return "select `id`,`channelID`,`sourceID`,`sourceName`,`targetID`,`targetName`,`msg`,`chatTime` from `tb_LogChat` "; 
} 
std::string  LogChat::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_LogChat`(`channelID`,`sourceID`,`sourceName`,`targetID`,`targetName`,`msg`,`chatTime`) values(?,?,?,?,?,?,?)"); 
    q << this->channelID; 
    q << this->sourceID; 
    q << this->sourceName; 
    q << this->targetID; 
    q << this->targetName; 
    q << this->msg; 
    q << this->chatTime; 
    return q.pickSQL(); 
} 
std::string  LogChat::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_LogChat` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  LogChat::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_LogChat`(id) values(? ) on duplicate key update `channelID` = ?,`sourceID` = ?,`sourceName` = ?,`targetID` = ?,`targetName` = ?,`msg` = ?,`chatTime` = ? "); 
    q << this->id; 
    q << this->channelID; 
    q << this->sourceID; 
    q << this->sourceName; 
    q << this->targetID; 
    q << this->targetName; 
    q << this->msg; 
    q << this->chatTime; 
    return q.pickSQL(); 
} 
bool LogChat::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch LogChat from table `tb_LogChat` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->channelID; 
            result >> this->sourceID; 
            result >> this->sourceName; 
            result >> this->targetID; 
            result >> this->targetName; 
            result >> this->msg; 
            result >> this->chatTime; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch LogChat from table `tb_LogChat` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LogChat & data) 
{ 
    ws << data.id;  
    ws << data.channelID;  
    ws << data.sourceID;  
    ws << data.sourceName;  
    ws << data.targetID;  
    ws << data.targetName;  
    ws << data.msg;  
    ws << data.chatTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LogChat & data) 
{ 
    rs >> data.id;  
    rs >> data.channelID;  
    rs >> data.sourceID;  
    rs >> data.sourceName;  
    rs >> data.targetID;  
    rs >> data.targetName;  
    rs >> data.msg;  
    rs >> data.chatTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LogChat & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "channelID=" << info.channelID << ","; 
    stm << "sourceID=" << info.sourceID << ","; 
    stm << "sourceName=" << info.sourceName << ","; 
    stm << "targetID=" << info.targetID << ","; 
    stm << "targetName=" << info.targetName << ","; 
    stm << "msg=" << info.msg << ","; 
    stm << "chatTime=" << info.chatTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct MoneyTree //摇钱树功能模块  
{ 
    static const unsigned short getProtoID() { return 1007;} 
    static const std::string getProtoName() { return "MoneyTree";} 
    unsigned long long lastTime; //最后一次执行时间  
    unsigned long long freeCount; //今日剩余免费次数  
    unsigned long long payCount; //今日已购买次数  
    unsigned long long statSum; //历史总和  
    unsigned long long statCount; //历史总次数  
    MoneyTree() 
    { 
        lastTime = 0; 
        freeCount = 0; 
        payCount = 0; 
        statSum = 0; 
        statCount = 0; 
    } 
    MoneyTree(const unsigned long long & lastTime, const unsigned long long & freeCount, const unsigned long long & payCount, const unsigned long long & statSum, const unsigned long long & statCount) 
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
    stm << "["; 
    stm << "lastTime=" << info.lastTime << ","; 
    stm << "freeCount=" << info.freeCount << ","; 
    stm << "payCount=" << info.payCount << ","; 
    stm << "statSum=" << info.statSum << ","; 
    stm << "statCount=" << info.statCount << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct SimplePack //简单示例  
{ 
    static const unsigned short getProtoID() { return 1008;} 
    static const std::string getProtoName() { return "SimplePack";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id; //id, 对应数据库的结构为自增ID,key  
    std::string name; //昵称, 唯一索引  
    unsigned long long createTime; //创建时间, 普通索引  
    MoneyTree moneyTree;  
    SimplePack() 
    { 
        id = 0; 
        createTime = 0; 
    } 
    SimplePack(const unsigned long long & id, const std::string & name, const unsigned long long & createTime, const MoneyTree & moneyTree) 
    { 
        this->id = id; 
        this->name = name; 
        this->createTime = createTime; 
        this->moneyTree = moneyTree; 
    } 
}; 
 
std::vector<std::string>  SimplePack::getDBBuild() 
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
    return ret; 
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
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "name=" << info.name << ","; 
    stm << "createTime=" << info.createTime << ","; 
    stm << "moneyTree=" << info.moneyTree << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 
