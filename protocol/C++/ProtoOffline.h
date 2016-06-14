 
#ifndef _PROTOOFFLINE_H_ 
#define _PROTOOFFLINE_H_ 
 
 
struct UserOffline 
{ 
    static const unsigned short getProtoID() { return 5200;} 
    static const std::string getProtoName() { return "UserOffline";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id;  
    unsigned long long serviceID;  
    std::string streamBlob;  
    unsigned short status;  
    unsigned int timestamp;  
    UserOffline() 
    { 
        id = 0; 
        serviceID = 0; 
        status = 0; 
        timestamp = 0; 
    } 
    UserOffline(const unsigned int & id, const unsigned long long & serviceID, const std::string & streamBlob, const unsigned short & status, const unsigned int & timestamp) 
    { 
        this->id = id; 
        this->serviceID = serviceID; 
        this->streamBlob = streamBlob; 
        this->status = status; 
        this->timestamp = timestamp; 
    } 
}; 
 
const std::vector<std::string>  UserOffline::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_UserOffline` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `serviceID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `streamBlob` longblob NOT NULL ,        `status` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `timestamp` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`),        KEY `serviceID` (`serviceID`),        KEY `status` (`status`),        KEY `timestamp` (`timestamp`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_UserOffline` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` add `serviceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` change `serviceID`  `serviceID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` add `streamBlob`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_UserOffline` change `streamBlob`  `streamBlob`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_UserOffline` add `status`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` change `status`  `status`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` add `timestamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserOffline` change `timestamp`  `timestamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  UserOffline::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`serviceID`,`streamBlob`,`status`,`timestamp` from `tb_UserOffline` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  UserOffline::getDBSelectPure() 
{ 
    return "select `id`,`serviceID`,`streamBlob`,`status`,`timestamp` from `tb_UserOffline` "; 
} 
std::string  UserOffline::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserOffline`(`id`,`serviceID`,`streamBlob`,`status`,`timestamp`) values(?,?,?,?,?)"); 
    q << this->id; 
    q << this->serviceID; 
    q << this->streamBlob; 
    q << this->status; 
    q << this->timestamp; 
    return q.pickSQL(); 
} 
std::string  UserOffline::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_UserOffline` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  UserOffline::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_UserOffline`(id) values(? ) on duplicate key update `serviceID` = ?,`streamBlob` = ?,`status` = ?,`timestamp` = ? "); 
    q << this->id; 
    q << this->serviceID; 
    q << this->streamBlob; 
    q << this->status; 
    q << this->timestamp; 
    return q.pickSQL(); 
} 
bool UserOffline::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch UserOffline from table `tb_UserOffline` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->serviceID; 
            result >> this->streamBlob; 
            result >> this->status; 
            result >> this->timestamp; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch UserOffline from table `tb_UserOffline` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserOffline & data) 
{ 
    ws << data.id;  
    ws << data.serviceID;  
    ws << data.streamBlob;  
    ws << data.status;  
    ws << data.timestamp;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserOffline & data) 
{ 
    rs >> data.id;  
    rs >> data.serviceID;  
    rs >> data.streamBlob;  
    rs >> data.status;  
    rs >> data.timestamp;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserOffline & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "streamBlob=" << info.streamBlob << "\n"; 
    stm << "status=" << info.status << "\n"; 
    stm << "timestamp=" << info.timestamp << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
