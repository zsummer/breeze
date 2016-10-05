 
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
    stm << "[\n"; 
    stm << "toServiceType=" << info.toServiceType << "\n"; 
    stm << "toServiceID=" << info.toServiceID << "\n"; 
    stm << "fromServiceType=" << info.fromServiceType << "\n"; 
    stm << "fromServiceID=" << info.fromServiceID << "\n"; 
    stm << "traceID=" << info.traceID << "\n"; 
    stm << "traceBackID=" << info.traceBackID << "\n"; 
    stm << "]\n"; 
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
    stm << "[\n"; 
    stm << "clientDockerID=" << info.clientDockerID << "\n"; 
    stm << "clientSessionID=" << info.clientSessionID << "\n"; 
    stm << "clientAvatarID=" << info.clientAvatarID << "\n"; 
    stm << "]\n"; 
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
    stm << "[\n"; 
    stm << "routing=" << info.routing << "\n"; 
    stm << "oob=" << info.oob << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<unsigned long long> AvatarIDArray;  
 
struct AvatarPreview //用户预览信息  
{ 
    static const unsigned short getProtoID() { return 1003;} 
    static const std::string getProtoName() { return "AvatarPreview";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long avatarID; //用户唯一ID, 对应AvatarService的ServiceID  
    std::string userName; //用户唯一昵称, 对应AvatarService的ServiceName  
    std::string account; //帐号  
    int iconID; //头像  
    int modeID; //模型  
    int level; //等级  
    AvatarPreview() 
    { 
        avatarID = 0; 
        iconID = 0; 
        modeID = 0; 
        level = 0; 
    } 
    AvatarPreview(const unsigned long long & avatarID, const std::string & userName, const std::string & account, const int & iconID, const int & modeID, const int & level) 
    { 
        this->avatarID = avatarID; 
        this->userName = userName; 
        this->account = account; 
        this->iconID = iconID; 
        this->modeID = modeID; 
        this->level = level; 
    } 
}; 
 
const std::vector<std::string>  AvatarPreview::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_AvatarPreview` (        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `userName` varchar(255) NOT NULL DEFAULT '' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`avatarID`),        UNIQUE KEY `userName` (`userName`),        KEY `account` (`account`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_AvatarPreview` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `userName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `userName`  `userName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `iconID`  `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `modeID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `modeID`  `modeID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` add `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarPreview` change `level`  `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  AvatarPreview::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `avatarID`,`userName`,`account`,`iconID`,`modeID`,`level` from `tb_AvatarPreview` where `avatarID` = ? "); 
    q << this->avatarID; 
    return q.pickSQL(); 
} 
std::string  AvatarPreview::getDBSelectPure() 
{ 
    return "select `avatarID`,`userName`,`account`,`iconID`,`modeID`,`level` from `tb_AvatarPreview` "; 
} 
std::string  AvatarPreview::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarPreview`(`avatarID`,`userName`,`account`,`iconID`,`modeID`,`level`) values(?,?,?,?,?,?)"); 
    q << this->avatarID; 
    q << this->userName; 
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
    q.init("insert into `tb_AvatarPreview`(avatarID) values(? ) on duplicate key update `userName` = ?,`account` = ?,`iconID` = ?,`modeID` = ?,`level` = ? "); 
    q << this->avatarID; 
    q << this->userName; 
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
            result >> this->userName; 
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
    ws << data.userName;  
    ws << data.account;  
    ws << data.iconID;  
    ws << data.modeID;  
    ws << data.level;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AvatarPreview & data) 
{ 
    rs >> data.avatarID;  
    rs >> data.userName;  
    rs >> data.account;  
    rs >> data.iconID;  
    rs >> data.modeID;  
    rs >> data.level;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AvatarPreview & info) 
{ 
    stm << "[\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "userName=" << info.userName << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "iconID=" << info.iconID << "\n"; 
    stm << "modeID=" << info.modeID << "\n"; 
    stm << "level=" << info.level << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<AvatarPreview> AvatarPreviewArray;  
 
struct AvatarBaseInfo //用户基础数据  
{ 
    static const unsigned short getProtoID() { return 1004;} 
    static const std::string getProtoName() { return "AvatarBaseInfo";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long avatarID; //用户唯一ID, 对应AvatarService的ServiceID  
    std::string userName; //用户唯一昵称, 对应AvatarService的ServiceName  
    std::string account; //帐号  
    int iconID; //头像  
    int modeID; //模型  
    int level; //等级  
    double exp; //经验  
    double gold; //金币  
    double diamond; //钻石  
    unsigned long long createTime; //角色创建时间  
    AvatarBaseInfo() 
    { 
        avatarID = 0; 
        iconID = 0; 
        modeID = 0; 
        level = 0; 
        exp = 0.0; 
        gold = 0.0; 
        diamond = 0.0; 
        createTime = 0; 
    } 
    AvatarBaseInfo(const unsigned long long & avatarID, const std::string & userName, const std::string & account, const int & iconID, const int & modeID, const int & level, const double & exp, const double & gold, const double & diamond, const unsigned long long & createTime) 
    { 
        this->avatarID = avatarID; 
        this->userName = userName; 
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
 
const std::vector<std::string>  AvatarBaseInfo::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_AvatarBaseInfo` (        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `userName` varchar(255) NOT NULL DEFAULT '' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`avatarID`),        UNIQUE KEY `userName` (`userName`),        KEY `account` (`account`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `userName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `userName`  `userName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `iconID`  `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `modeID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `modeID`  `modeID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `level`  `level`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `exp`  `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `gold`  `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `diamond`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `diamond`  `diamond`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` add `createTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AvatarBaseInfo` change `createTime`  `createTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  AvatarBaseInfo::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `avatarID`,`userName`,`account`,`iconID`,`modeID`,`level`,`exp`,`gold`,`diamond`,`createTime` from `tb_AvatarBaseInfo` where `avatarID` = ? "); 
    q << this->avatarID; 
    return q.pickSQL(); 
} 
std::string  AvatarBaseInfo::getDBSelectPure() 
{ 
    return "select `avatarID`,`userName`,`account`,`iconID`,`modeID`,`level`,`exp`,`gold`,`diamond`,`createTime` from `tb_AvatarBaseInfo` "; 
} 
std::string  AvatarBaseInfo::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AvatarBaseInfo`(`avatarID`,`userName`,`account`,`iconID`,`modeID`,`level`,`exp`,`gold`,`diamond`,`createTime`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->avatarID; 
    q << this->userName; 
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
    q.init("insert into `tb_AvatarBaseInfo`(avatarID) values(? ) on duplicate key update `userName` = ?,`account` = ?,`iconID` = ?,`modeID` = ?,`level` = ?,`exp` = ?,`gold` = ?,`diamond` = ?,`createTime` = ? "); 
    q << this->avatarID; 
    q << this->userName; 
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
            result >> this->userName; 
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
    ws << data.userName;  
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
    rs >> data.userName;  
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
    stm << "[\n"; 
    stm << "avatarID=" << info.avatarID << "\n"; 
    stm << "userName=" << info.userName << "\n"; 
    stm << "account=" << info.account << "\n"; 
    stm << "iconID=" << info.iconID << "\n"; 
    stm << "modeID=" << info.modeID << "\n"; 
    stm << "level=" << info.level << "\n"; 
    stm << "exp=" << info.exp << "\n"; 
    stm << "gold=" << info.gold << "\n"; 
    stm << "diamond=" << info.diamond << "\n"; 
    stm << "createTime=" << info.createTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<AvatarBaseInfo> AvatarBaseInfoArray;  
 
 
typedef std::map<std::string, double> AvatarPropMap;  
 
struct DictGlobal //全局配置  
{ 
    static const unsigned short getProtoID() { return 1005;} 
    static const std::string getProtoName() { return "DictGlobal";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long val; //整数  
    double valFloat; //浮点数  
    std::string combo; //字符串  
    std::string desc;  
    DictGlobal() 
    { 
        id = 0; 
        val = 0; 
        valFloat = 0.0; 
    } 
    DictGlobal(const unsigned long long & id, const unsigned long long & val, const double & valFloat, const std::string & combo, const std::string & desc) 
    { 
        this->id = id; 
        this->val = val; 
        this->valFloat = valFloat; 
        this->combo = combo; 
        this->desc = desc; 
    } 
}; 
 
const std::vector<std::string>  DictGlobal::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictGlobal` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictGlobal` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` add `val`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` change `val`  `val`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` add `valFloat`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` change `valFloat`  `valFloat`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` add `combo`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictGlobal` change `combo`  `combo`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictGlobal` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictGlobal` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return std::move(ret); 
} 
std::string  DictGlobal::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`val`,`valFloat`,`combo`,`desc` from `tb_DictGlobal` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictGlobal::getDBSelectPure() 
{ 
    return "select `id`,`val`,`valFloat`,`combo`,`desc` from `tb_DictGlobal` "; 
} 
std::string  DictGlobal::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictGlobal`(`id`,`val`,`valFloat`,`combo`,`desc`) values(?,?,?,?,?)"); 
    q << this->id; 
    q << this->val; 
    q << this->valFloat; 
    q << this->combo; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictGlobal::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictGlobal` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictGlobal::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictGlobal`(id) values(? ) on duplicate key update `val` = ?,`valFloat` = ?,`combo` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->val; 
    q << this->valFloat; 
    q << this->combo; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictGlobal::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictGlobal from table `tb_DictGlobal` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->val; 
            result >> this->valFloat; 
            result >> this->combo; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictGlobal from table `tb_DictGlobal` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictGlobal & data) 
{ 
    ws << data.id;  
    ws << data.val;  
    ws << data.valFloat;  
    ws << data.combo;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictGlobal & data) 
{ 
    rs >> data.id;  
    rs >> data.val;  
    rs >> data.valFloat;  
    rs >> data.combo;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictGlobal & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "val=" << info.val << "\n"; 
    stm << "valFloat=" << info.valFloat << "\n"; 
    stm << "combo=" << info.combo << "\n"; 
    stm << "desc=" << info.desc << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DictRaffleAward //奖池中的奖品  
{ 
    static const unsigned short getProtoID() { return 1006;} 
    static const std::string getProtoName() { return "DictRaffleAward";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id; //奖品ID  
    unsigned long long weight; //本奖品在奖池中的权重, 总权重在[10000~30000]之间的随机效果最好  
    double probability; //[0~1]独立随机的概率,0为永远无法随机到 1是100%随机到  
    DictRaffleAward() 
    { 
        id = 0; 
        weight = 0; 
        probability = 0.0; 
    } 
    DictRaffleAward(const unsigned long long & id, const unsigned long long & weight, const double & probability) 
    { 
        this->id = id; 
        this->weight = weight; 
        this->probability = probability; 
    } 
}; 
 
const std::vector<std::string>  DictRaffleAward::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictRaffleAward` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictRaffleAward` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRaffleAward` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRaffleAward` add `weight`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRaffleAward` change `weight`  `weight`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRaffleAward` add `probability`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRaffleAward` change `probability`  `probability`  double NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  DictRaffleAward::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`weight`,`probability` from `tb_DictRaffleAward` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictRaffleAward::getDBSelectPure() 
{ 
    return "select `id`,`weight`,`probability` from `tb_DictRaffleAward` "; 
} 
std::string  DictRaffleAward::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictRaffleAward`(`id`,`weight`,`probability`) values(?,?,?)"); 
    q << this->id; 
    q << this->weight; 
    q << this->probability; 
    return q.pickSQL(); 
} 
std::string  DictRaffleAward::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictRaffleAward` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictRaffleAward::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictRaffleAward`(id) values(? ) on duplicate key update `weight` = ?,`probability` = ? "); 
    q << this->id; 
    q << this->weight; 
    q << this->probability; 
    return q.pickSQL(); 
} 
bool DictRaffleAward::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictRaffleAward from table `tb_DictRaffleAward` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->weight; 
            result >> this->probability; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictRaffleAward from table `tb_DictRaffleAward` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictRaffleAward & data) 
{ 
    ws << data.id;  
    ws << data.weight;  
    ws << data.probability;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictRaffleAward & data) 
{ 
    rs >> data.id;  
    rs >> data.weight;  
    rs >> data.probability;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictRaffleAward & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "weight=" << info.weight << "\n"; 
    stm << "probability=" << info.probability << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<DictRaffleAward> DictRaffleAwardArray;  
 
struct DictRafflePool //道具抽奖,道具掉落  
{ 
    static const unsigned short getProtoID() { return 1007;} 
    static const std::string getProtoName() { return "DictRafflePool";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    int raffleCount; //批量抽取次数  
    DictRaffleAwardArray pool; //奖池  
    std::string poolString; //奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式  
    DictRafflePool() 
    { 
        id = 0; 
        raffleCount = 0; 
    } 
    DictRafflePool(const unsigned long long & id, const int & raffleCount, const DictRaffleAwardArray & pool, const std::string & poolString) 
    { 
        this->id = id; 
        this->raffleCount = raffleCount; 
        this->pool = pool; 
        this->poolString = poolString; 
    } 
}; 
 
const std::vector<std::string>  DictRafflePool::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictRafflePool` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictRafflePool` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` add `raffleCount`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` change `raffleCount`  `raffleCount`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` add `pool`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_DictRafflePool` change `pool`  `pool`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_DictRafflePool` add `poolString`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictRafflePool` change `poolString`  `poolString`  varchar(255) NOT NULL DEFAULT '' "); 
    return std::move(ret); 
} 
std::string  DictRafflePool::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`raffleCount`,`pool`,`poolString` from `tb_DictRafflePool` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictRafflePool::getDBSelectPure() 
{ 
    return "select `id`,`raffleCount`,`pool`,`poolString` from `tb_DictRafflePool` "; 
} 
std::string  DictRafflePool::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictRafflePool`(`id`,`raffleCount`,`pool`,`poolString`) values(?,?,?,?)"); 
    q << this->id; 
    q << this->raffleCount; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->pool; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when insert DictRafflePool.pool error=" << e.what()); 
    } 
    q << this->poolString; 
    return q.pickSQL(); 
} 
std::string  DictRafflePool::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictRafflePool` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictRafflePool::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictRafflePool`(id) values(? ) on duplicate key update `raffleCount` = ?,`pool` = ?,`poolString` = ? "); 
    q << this->id; 
    q << this->raffleCount; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->pool; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when update DictRafflePool.pool error=" << e.what()); 
    } 
    q << this->poolString; 
    return q.pickSQL(); 
} 
bool DictRafflePool::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictRafflePool from table `tb_DictRafflePool` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->raffleCount; 
            try 
            { 
                std::string blob; 
                result >> blob; 
                if(!blob.empty()) 
                { 
                    zsummer::proto4z::ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false); 
                    rs >> this->pool; 
                } 
            } 
            catch(const std::exception & e) 
            { 
                LOGW("catch one except error when fetch DictRafflePool.pool  from table `tb_DictRafflePool` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
            } 
            result >> this->poolString; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictRafflePool from table `tb_DictRafflePool` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictRafflePool & data) 
{ 
    ws << data.id;  
    ws << data.raffleCount;  
    ws << data.pool;  
    ws << data.poolString;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictRafflePool & data) 
{ 
    rs >> data.id;  
    rs >> data.raffleCount;  
    rs >> data.pool;  
    rs >> data.poolString;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictRafflePool & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "raffleCount=" << info.raffleCount << "\n"; 
    stm << "pool=" << info.pool << "\n"; 
    stm << "poolString=" << info.poolString << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DictBaseProps //战斗属性效果,用于装备,属性类增减益buff  
{ 
    static const unsigned short getProtoID() { return 1008;} 
    static const std::string getProtoName() { return "DictBaseProps";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    double hp; //血量值  
    double hpRegen; //每秒血量值恢复  
    double attack; //伤害  
    double defense; //防御  
    double crit; //暴击  
    double toughness; //韧性  
    double moveSpeed; //移动速度  
    double attackSpeed; //攻击速度  
    double vampirk; //吸血  
    DictBaseProps() 
    { 
        id = 0; 
        hp = 0.0; 
        hpRegen = 0.0; 
        attack = 0.0; 
        defense = 0.0; 
        crit = 0.0; 
        toughness = 0.0; 
        moveSpeed = 0.0; 
        attackSpeed = 0.0; 
        vampirk = 0.0; 
    } 
    DictBaseProps(const unsigned long long & id, const double & hp, const double & hpRegen, const double & attack, const double & defense, const double & crit, const double & toughness, const double & moveSpeed, const double & attackSpeed, const double & vampirk) 
    { 
        this->id = id; 
        this->hp = hp; 
        this->hpRegen = hpRegen; 
        this->attack = attack; 
        this->defense = defense; 
        this->crit = crit; 
        this->toughness = toughness; 
        this->moveSpeed = moveSpeed; 
        this->attackSpeed = attackSpeed; 
        this->vampirk = vampirk; 
    } 
}; 
 
const std::vector<std::string>  DictBaseProps::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictBaseProps` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictBaseProps` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `hp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `hp`  `hp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `hpRegen`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `hpRegen`  `hpRegen`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `attack`  `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `defense`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `defense`  `defense`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `crit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `crit`  `crit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `toughness`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `toughness`  `toughness`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `moveSpeed`  `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `attackSpeed`  `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` add `vampirk`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBaseProps` change `vampirk`  `vampirk`  double NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  DictBaseProps::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk` from `tb_DictBaseProps` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBaseProps::getDBSelectPure() 
{ 
    return "select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk` from `tb_DictBaseProps` "; 
} 
std::string  DictBaseProps::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBaseProps`(`id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->hp; 
    q << this->hpRegen; 
    q << this->attack; 
    q << this->defense; 
    q << this->crit; 
    q << this->toughness; 
    q << this->moveSpeed; 
    q << this->attackSpeed; 
    q << this->vampirk; 
    return q.pickSQL(); 
} 
std::string  DictBaseProps::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictBaseProps` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBaseProps::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBaseProps`(id) values(? ) on duplicate key update `hp` = ?,`hpRegen` = ?,`attack` = ?,`defense` = ?,`crit` = ?,`toughness` = ?,`moveSpeed` = ?,`attackSpeed` = ?,`vampirk` = ? "); 
    q << this->id; 
    q << this->hp; 
    q << this->hpRegen; 
    q << this->attack; 
    q << this->defense; 
    q << this->crit; 
    q << this->toughness; 
    q << this->moveSpeed; 
    q << this->attackSpeed; 
    q << this->vampirk; 
    return q.pickSQL(); 
} 
bool DictBaseProps::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictBaseProps from table `tb_DictBaseProps` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->hp; 
            result >> this->hpRegen; 
            result >> this->attack; 
            result >> this->defense; 
            result >> this->crit; 
            result >> this->toughness; 
            result >> this->moveSpeed; 
            result >> this->attackSpeed; 
            result >> this->vampirk; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictBaseProps from table `tb_DictBaseProps` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictBaseProps & data) 
{ 
    ws << data.id;  
    ws << data.hp;  
    ws << data.hpRegen;  
    ws << data.attack;  
    ws << data.defense;  
    ws << data.crit;  
    ws << data.toughness;  
    ws << data.moveSpeed;  
    ws << data.attackSpeed;  
    ws << data.vampirk;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictBaseProps & data) 
{ 
    rs >> data.id;  
    rs >> data.hp;  
    rs >> data.hpRegen;  
    rs >> data.attack;  
    rs >> data.defense;  
    rs >> data.crit;  
    rs >> data.toughness;  
    rs >> data.moveSpeed;  
    rs >> data.attackSpeed;  
    rs >> data.vampirk;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictBaseProps & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "hp=" << info.hp << "\n"; 
    stm << "hpRegen=" << info.hpRegen << "\n"; 
    stm << "attack=" << info.attack << "\n"; 
    stm << "defense=" << info.defense << "\n"; 
    stm << "crit=" << info.crit << "\n"; 
    stm << "toughness=" << info.toughness << "\n"; 
    stm << "moveSpeed=" << info.moveSpeed << "\n"; 
    stm << "attackSpeed=" << info.attackSpeed << "\n"; 
    stm << "vampirk=" << info.vampirk << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DictItem //道具字典  
{ 
    static const unsigned short getProtoID() { return 1009;} 
    static const std::string getProtoName() { return "DictItem";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned short primitiveType; //主类型  
    unsigned short subType; //子类型  
    unsigned short visible; //是否可见  
    unsigned short stacks; //可堆叠个数,0和1都是1次  
    unsigned long long fightEffectID; //战斗属性效果,装备后生效  
    unsigned short autoUse; //0 不可使用, 1 可使用, 2 获得后自动使用  
    unsigned long long dropID; //DictRafflePool中的id, 使用后销毁本道具并根据配置进行道具抽取  
    unsigned short vocationLimit; //限制职业类型, 装备类型  
    int levelLimit; //限制职业最小等级, 装备类型  
    std::string desc;  
    DictItem() 
    { 
        id = 0; 
        primitiveType = 0; 
        subType = 0; 
        visible = 0; 
        stacks = 0; 
        fightEffectID = 0; 
        autoUse = 0; 
        dropID = 0; 
        vocationLimit = 0; 
        levelLimit = 0; 
    } 
    DictItem(const unsigned long long & id, const unsigned short & primitiveType, const unsigned short & subType, const unsigned short & visible, const unsigned short & stacks, const unsigned long long & fightEffectID, const unsigned short & autoUse, const unsigned long long & dropID, const unsigned short & vocationLimit, const int & levelLimit, const std::string & desc) 
    { 
        this->id = id; 
        this->primitiveType = primitiveType; 
        this->subType = subType; 
        this->visible = visible; 
        this->stacks = stacks; 
        this->fightEffectID = fightEffectID; 
        this->autoUse = autoUse; 
        this->dropID = dropID; 
        this->vocationLimit = vocationLimit; 
        this->levelLimit = levelLimit; 
        this->desc = desc; 
    } 
}; 
 
const std::vector<std::string>  DictItem::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictItem` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `primitiveType` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `subType` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`),        KEY `primitiveType` (`primitiveType`),        KEY `subType` (`subType`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictItem` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `primitiveType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `primitiveType`  `primitiveType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `subType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `subType`  `subType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `visible`  `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `stacks`  `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `fightEffectID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `fightEffectID`  `fightEffectID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `autoUse`  `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `dropID`  `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `vocationLimit`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `vocationLimit`  `vocationLimit`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `levelLimit`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `levelLimit`  `levelLimit`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return std::move(ret); 
} 
std::string  DictItem::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`primitiveType`,`subType`,`visible`,`stacks`,`fightEffectID`,`autoUse`,`dropID`,`vocationLimit`,`levelLimit`,`desc` from `tb_DictItem` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBSelectPure() 
{ 
    return "select `id`,`primitiveType`,`subType`,`visible`,`stacks`,`fightEffectID`,`autoUse`,`dropID`,`vocationLimit`,`levelLimit`,`desc` from `tb_DictItem` "; 
} 
std::string  DictItem::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictItem`(`id`,`primitiveType`,`subType`,`visible`,`stacks`,`fightEffectID`,`autoUse`,`dropID`,`vocationLimit`,`levelLimit`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->primitiveType; 
    q << this->subType; 
    q << this->visible; 
    q << this->stacks; 
    q << this->fightEffectID; 
    q << this->autoUse; 
    q << this->dropID; 
    q << this->vocationLimit; 
    q << this->levelLimit; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictItem` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictItem`(id) values(? ) on duplicate key update `primitiveType` = ?,`subType` = ?,`visible` = ?,`stacks` = ?,`fightEffectID` = ?,`autoUse` = ?,`dropID` = ?,`vocationLimit` = ?,`levelLimit` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->primitiveType; 
    q << this->subType; 
    q << this->visible; 
    q << this->stacks; 
    q << this->fightEffectID; 
    q << this->autoUse; 
    q << this->dropID; 
    q << this->vocationLimit; 
    q << this->levelLimit; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictItem::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictItem from table `tb_DictItem` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->primitiveType; 
            result >> this->subType; 
            result >> this->visible; 
            result >> this->stacks; 
            result >> this->fightEffectID; 
            result >> this->autoUse; 
            result >> this->dropID; 
            result >> this->vocationLimit; 
            result >> this->levelLimit; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictItem from table `tb_DictItem` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictItem & data) 
{ 
    ws << data.id;  
    ws << data.primitiveType;  
    ws << data.subType;  
    ws << data.visible;  
    ws << data.stacks;  
    ws << data.fightEffectID;  
    ws << data.autoUse;  
    ws << data.dropID;  
    ws << data.vocationLimit;  
    ws << data.levelLimit;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictItem & data) 
{ 
    rs >> data.id;  
    rs >> data.primitiveType;  
    rs >> data.subType;  
    rs >> data.visible;  
    rs >> data.stacks;  
    rs >> data.fightEffectID;  
    rs >> data.autoUse;  
    rs >> data.dropID;  
    rs >> data.vocationLimit;  
    rs >> data.levelLimit;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictItem & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "primitiveType=" << info.primitiveType << "\n"; 
    stm << "subType=" << info.subType << "\n"; 
    stm << "visible=" << info.visible << "\n"; 
    stm << "stacks=" << info.stacks << "\n"; 
    stm << "fightEffectID=" << info.fightEffectID << "\n"; 
    stm << "autoUse=" << info.autoUse << "\n"; 
    stm << "dropID=" << info.dropID << "\n"; 
    stm << "vocationLimit=" << info.vocationLimit << "\n"; 
    stm << "levelLimit=" << info.levelLimit << "\n"; 
    stm << "desc=" << info.desc << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct ItemInfo //道具字典  
{ 
    static const unsigned short getProtoID() { return 1010;} 
    static const std::string getProtoName() { return "ItemInfo";} 
    inline const std::vector<std::string>  getDBBuild(); 
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
 
const std::vector<std::string>  ItemInfo::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_ItemInfo` ( ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_ItemInfo` add `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_ItemInfo` change `stacks`  `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
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
    stm << "[\n"; 
    stm << "stacks=" << info.stacks << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
enum ChatChannelEnum : unsigned short 
{ 
    CC_WORLD = 0,  
    CC_PRIVATE = 1,  
    CC_SYSTEM = 2,  
}; 
 
struct LogChat //聊天日志  
{ 
    static const unsigned short getProtoID() { return 1011;} 
    static const std::string getProtoName() { return "LogChat";} 
    inline const std::vector<std::string>  getDBBuild(); 
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
 
const std::vector<std::string>  LogChat::getDBBuild() 
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
    return std::move(ret); 
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
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "channelID=" << info.channelID << "\n"; 
    stm << "sourceID=" << info.sourceID << "\n"; 
    stm << "sourceName=" << info.sourceName << "\n"; 
    stm << "targetID=" << info.targetID << "\n"; 
    stm << "targetName=" << info.targetName << "\n"; 
    stm << "msg=" << info.msg << "\n"; 
    stm << "chatTime=" << info.chatTime << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct MoneyTree //摇钱树功能模块  
{ 
    static const unsigned short getProtoID() { return 1012;} 
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
    static const unsigned short getProtoID() { return 1013;} 
    static const std::string getProtoName() { return "SimplePack";} 
    inline const std::vector<std::string>  getDBBuild(); 
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
