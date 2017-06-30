 
#ifndef _LOGCOMMON_H_ 
#define _LOGCOMMON_H_ 
 
 
struct LogLogin 
{ 
    static const unsigned short getProtoID() { return 20000;} 
    static const std::string getProtoName() { return "LogLogin";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long logTime;  
    unsigned long long avatarID;  
    std::string avatarName;  
    std::string deviceInfo;  
    LogLogin() 
    { 
        id = 0; 
        logTime = 0; 
        avatarID = 0; 
    } 
    LogLogin(const unsigned long long & id, const unsigned long long & logTime, const unsigned long long & avatarID, const std::string & avatarName, const std::string & deviceInfo) 
    { 
        this->id = id; 
        this->logTime = logTime; 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->deviceInfo = deviceInfo; 
    } 
}; 
 
std::vector<std::string>  LogLogin::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_LogLogin` (        `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT ,        `logTime` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarName` varchar(255) NOT NULL DEFAULT '' ,        `deviceInfo` longblob NOT NULL ,        PRIMARY KEY(`id`),        KEY `logTime` (`logTime`),        KEY `avatarID` (`avatarID`),        KEY `avatarName` (`avatarName`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_LogLogin` add `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_LogLogin` change `id`  `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_LogLogin` add `logTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogLogin` change `logTime`  `logTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogLogin` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogLogin` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogLogin` add `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogLogin` change `avatarName`  `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogLogin` add `deviceInfo`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_LogLogin` change `deviceInfo`  `deviceInfo`  longblob NOT NULL "); 
    return ret; 
} 
std::string  LogLogin::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`logTime`,`avatarID`,`avatarName`,`deviceInfo` from `tb_LogLogin` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  LogLogin::getDBSelectPure() 
{ 
    return "select `id`,`logTime`,`avatarID`,`avatarName`,`deviceInfo` from `tb_LogLogin` "; 
} 
std::string  LogLogin::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_LogLogin`(`logTime`,`avatarID`,`avatarName`,`deviceInfo`) values(?,?,?,?)"); 
    q << this->logTime; 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->deviceInfo; 
    return q.pickSQL(); 
} 
std::string  LogLogin::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_LogLogin` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  LogLogin::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_LogLogin`(id) values(? ) on duplicate key update `logTime` = ?,`avatarID` = ?,`avatarName` = ?,`deviceInfo` = ? "); 
    q << this->id; 
    q << this->logTime; 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->deviceInfo; 
    return q.pickSQL(); 
} 
bool LogLogin::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch LogLogin from table `tb_LogLogin` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->logTime; 
            result >> this->avatarID; 
            result >> this->avatarName; 
            result >> this->deviceInfo; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch LogLogin from table `tb_LogLogin` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LogLogin & data) 
{ 
    ws << data.id;  
    ws << data.logTime;  
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.deviceInfo;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LogLogin & data) 
{ 
    rs >> data.id;  
    rs >> data.logTime;  
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.deviceInfo;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LogLogin & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "logTime=" << info.logTime << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "deviceInfo=" << info.deviceInfo << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct LogQuit 
{ 
    static const unsigned short getProtoID() { return 20001;} 
    static const std::string getProtoName() { return "LogQuit";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long logTime;  
    unsigned long long avatarID;  
    std::string avatarName;  
    LogQuit() 
    { 
        id = 0; 
        logTime = 0; 
        avatarID = 0; 
    } 
    LogQuit(const unsigned long long & id, const unsigned long long & logTime, const unsigned long long & avatarID, const std::string & avatarName) 
    { 
        this->id = id; 
        this->logTime = logTime; 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
    } 
}; 
 
std::vector<std::string>  LogQuit::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_LogQuit` (        `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT ,        `logTime` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `avatarName` varchar(255) NOT NULL DEFAULT '' ,        PRIMARY KEY(`id`),        KEY `logTime` (`logTime`),        KEY `avatarID` (`avatarID`),        KEY `avatarName` (`avatarName`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_LogQuit` add `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_LogQuit` change `id`  `id`  bigint(20) unsigned NOT NULL AUTO_INCREMENT "); 
    ret.push_back("alter table `tb_LogQuit` add `logTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogQuit` change `logTime`  `logTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogQuit` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogQuit` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_LogQuit` add `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_LogQuit` change `avatarName`  `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  LogQuit::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`logTime`,`avatarID`,`avatarName` from `tb_LogQuit` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  LogQuit::getDBSelectPure() 
{ 
    return "select `id`,`logTime`,`avatarID`,`avatarName` from `tb_LogQuit` "; 
} 
std::string  LogQuit::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_LogQuit`(`logTime`,`avatarID`,`avatarName`) values(?,?,?)"); 
    q << this->logTime; 
    q << this->avatarID; 
    q << this->avatarName; 
    return q.pickSQL(); 
} 
std::string  LogQuit::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_LogQuit` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  LogQuit::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_LogQuit`(id) values(? ) on duplicate key update `logTime` = ?,`avatarID` = ?,`avatarName` = ? "); 
    q << this->id; 
    q << this->logTime; 
    q << this->avatarID; 
    q << this->avatarName; 
    return q.pickSQL(); 
} 
bool LogQuit::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch LogQuit from table `tb_LogQuit` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->logTime; 
            result >> this->avatarID; 
            result >> this->avatarName; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch LogQuit from table `tb_LogQuit` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LogQuit & data) 
{ 
    ws << data.id;  
    ws << data.logTime;  
    ws << data.avatarID;  
    ws << data.avatarName;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LogQuit & data) 
{ 
    rs >> data.id;  
    rs >> data.logTime;  
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LogQuit & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "logTime=" << info.logTime << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 
