 
#ifndef _PROTOCOMMONSQL_H_ 
#define _PROTOCOMMONSQL_H_ 
 
 
inline std::vector<std::string> SessionToken_BUILD() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("desc `tb_SessionToken`"); 
    ret.push_back("CREATE TABLE `tb_SessionToken` (        `uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,         PRIMARY KEY(`uID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_SessionToken` add `token`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_SessionToken` add `expire`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
 
inline std::string SessionToken_LOAD( unsigned long long curLoaded) 
{ 
    zsummer::mysql::DBQuery q(" select `uID`,`token`,`expire`from `tb_SessionToken` order by `uID` desc limit ?, 1000 "); 
    q << curLoaded; 
    return q.popSQL(); 
} 
 
inline std::string SessionToken_SELECT(unsigned long long uID) 
{ 
    zsummer::mysql::DBQuery q(" select `uID`,`token`,`expire`from `tb_SessionToken` where `uID` = ? "); 
    q << uID; 
    return q.popSQL(); 
} 
 
inline std::map<unsigned long long, SessionToken>  SessionToken_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
    std::map<unsigned long long, SessionToken>  ret; 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
        return ret; 
    } 
    try 
    { 
        while (ptr->haveRow()) 
        { 
            SessionToken info; 
            *ptr >> info.uID; 
            *ptr >> info.token; 
            *ptr >> info.expire; 
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
 
 
inline std::string SessionToken_INSERT( const SessionToken & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_SessionToken( `uID`,`token`,`expire`) values(?,?,?)"); 
    q << info.uID; 
    q << info.token; 
    q << info.expire; 
    return q.popSQL(); 
} 
 
 
inline std::string SessionToken_UPDATE( const SessionToken & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_SessionToken(uID) values(? ) on duplicate key update `token` = ?,`expire` = ? "); 
    q << info.uID; 
    q << info.token; 
    q << info.expire; 
    return q.popSQL(); 
} 
 
 
inline std::vector<std::string> BaseInfo_BUILD() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("desc `tb_BaseInfo`"); 
    ret.push_back("CREATE TABLE `tb_BaseInfo` (        `uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,         PRIMARY KEY(`uID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_BaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_BaseInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_BaseInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_BaseInfo` add `diamond`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_BaseInfo` add `hisotryDiamond`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_BaseInfo` add `giftDiamond`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_BaseInfo` add `joinTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
 
inline std::string BaseInfo_LOAD( unsigned long long curLoaded) 
{ 
    zsummer::mysql::DBQuery q(" select `uID`,`account`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime`from `tb_BaseInfo` order by `uID` desc limit ?, 1000 "); 
    q << curLoaded; 
    return q.popSQL(); 
} 
 
inline std::string BaseInfo_SELECT(unsigned long long uID) 
{ 
    zsummer::mysql::DBQuery q(" select `uID`,`account`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime`from `tb_BaseInfo` where `uID` = ? "); 
    q << uID; 
    return q.popSQL(); 
} 
 
inline std::map<unsigned long long, BaseInfo>  BaseInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
    std::map<unsigned long long, BaseInfo>  ret; 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
        return ret; 
    } 
    try 
    { 
        while (ptr->haveRow()) 
        { 
            BaseInfo info; 
            *ptr >> info.uID; 
            *ptr >> info.account; 
            *ptr >> info.nickName; 
            *ptr >> info.iconID; 
            *ptr >> info.diamond; 
            *ptr >> info.hisotryDiamond; 
            *ptr >> info.giftDiamond; 
            *ptr >> info.joinTime; 
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
 
 
inline std::string BaseInfo_INSERT( const BaseInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_BaseInfo( `uID`,`account`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime`) values(?,?,?,?,?,?,?,?)"); 
    q << info.uID; 
    q << info.account; 
    q << info.nickName; 
    q << info.iconID; 
    q << info.diamond; 
    q << info.hisotryDiamond; 
    q << info.giftDiamond; 
    q << info.joinTime; 
    return q.popSQL(); 
} 
 
 
inline std::string BaseInfo_UPDATE( const BaseInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_BaseInfo(uID) values(? ) on duplicate key update `account` = ?,`nickName` = ?,`iconID` = ?,`diamond` = ?,`hisotryDiamond` = ?,`giftDiamond` = ?,`joinTime` = ? "); 
    q << info.uID; 
    q << info.account; 
    q << info.nickName; 
    q << info.iconID; 
    q << info.diamond; 
    q << info.hisotryDiamond; 
    q << info.giftDiamond; 
    q << info.joinTime; 
    return q.popSQL(); 
} 
 
 
#endif 
