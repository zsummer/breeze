 
#ifndef _PROTOCOMMONSQL_H_ 
#define _PROTOCOMMONSQL_H_ 
 
 
inline std::vector<std::string> UserBaseInfo_BUILD() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("desc `tb_UserBaseInfo`"); 
    ret.push_back("CREATE TABLE `tb_UserBaseInfo` (        `uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,         PRIMARY KEY(`uID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_UserBaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
 
inline std::string UserBaseInfo_LOAD( unsigned long long curLoaded) 
{ 
    zsummer::mysql::DBQuery q(" select `uID`,`account`,`nickName`,`iconID`from `tb_UserBaseInfo` order by `uID` desc limit ?, 1000 "); 
    q << curLoaded; 
    return q.pickSQL(); 
} 
 
inline std::string UserBaseInfo_SELECT(unsigned long long uID) 
{ 
    zsummer::mysql::DBQuery q(" select `uID`,`account`,`nickName`,`iconID`from `tb_UserBaseInfo` where `uID` = ? "); 
    q << uID; 
    return q.pickSQL(); 
} 
 
typedef std::map<unsigned long long, UserBaseInfo>  MapDBUserBaseInfo; 
inline MapDBUserBaseInfo UserBaseInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
    MapDBUserBaseInfo ret; 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getErrorMsg()); 
        return ret; 
    } 
    try 
    { 
        while (ptr->haveRow()) 
        { 
            UserBaseInfo info; 
            *ptr >> info.uID; 
            *ptr >> info.account; 
            *ptr >> info.nickName; 
            *ptr >> info.iconID; 
            ret[info.uID] = info;  
        } 
    } 
    catch(std::runtime_error e) 
    { 
        LOGE("fetch info catch one runtime error. what=" << e.what()); 
        return ret; 
    } 
    return std::move(ret); 
} 
 
 
inline bool UserBaseInfo_FETCH(zsummer::mysql::DBResultPtr ptr, UserBaseInfo & info) 
{ 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getErrorMsg()); 
        return false; 
    } 
    try 
    { 
        if (ptr->haveRow()) 
        { 
            *ptr >> info.uID; 
            *ptr >> info.account; 
            *ptr >> info.nickName; 
            *ptr >> info.iconID; 
            return true;  
        } 
    } 
    catch(std::runtime_error e) 
    { 
        LOGE("fetch info catch one runtime error. what=" << e.what()); 
        return false; 
    } 
    return false; 
} 
 
 
inline std::string UserBaseInfo_INSERT( const UserBaseInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_UserBaseInfo( `uID`,`account`,`nickName`,`iconID`) values(?,?,?,?)"); 
    q << info.uID; 
    q << info.account; 
    q << info.nickName; 
    q << info.iconID; 
    return q.pickSQL(); 
} 
 
 
inline std::string UserBaseInfo_UPDATE( const UserBaseInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_UserBaseInfo(uID) values(? ) on duplicate key update `account` = ?,`nickName` = ?,`iconID` = ? "); 
    q << info.uID; 
    q << info.account; 
    q << info.nickName; 
    q << info.iconID; 
    return q.pickSQL(); 
} 
 
 
#endif 
