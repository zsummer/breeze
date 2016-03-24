 
#ifndef _PROTOCOMMONSQL_H_ 
#define _PROTOCOMMONSQL_H_ 
 
 
inline std::vector<std::string> UserBaseInfo_BUILD() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("desc `tb_UserBaseInfo`"); 
    ret.push_back("CREATE TABLE `tb_UserBaseInfo` (        `uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `account` varchar(255) NOT NULL DEFAULT '' ,        `nickName` varchar(255) NOT NULL DEFAULT '' ,        `iconID` bigint(20) NOT NULL DEFAULT '0' ,        PRIMARY KEY(`uID`)  ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_UserBaseInfo` add `uID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `uID`  `uID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `account`  `account`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `nickName`  `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_UserBaseInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_UserBaseInfo` change `iconID`  `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
 
inline std::vector<std::string> UserBaseInfo_DCL() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("select `uID`,`account`,`nickName`,`iconID` from `tb_UserBaseInfo` where `uID` = ? "); 
    ret.push_back("insert into `tb_UserBaseInfo`(`uID`,`account`,`nickName`,`iconID`) values(?,?,?,?)"); 
    ret.push_back("delete from `tb_UserBaseInfo` where `uID` = ? "); 
    ret.push_back("insert into `tb_UserBaseInfo`(uID) values(? ) on duplicate key update `account` = ?,`nickName` = ?,`iconID` = ? "); 
    return std::move(ret); 
} 
 
inline bool UserBaseInfo_FETCH(zsummer::mysql::DBResultPtr ptr, UserBaseInfo & info) 
{ 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch UserBaseInfo from table `tb_UserBaseInfo` . ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getErrorMsg() << ", sql=" << ptr->peekSQL()); 
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
        LOGE("catch one except error when fetch UserBaseInfo from table `tb_UserBaseInfo` . what=" << e.what() << "  ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getErrorMsg() << ", sql=" << ptr->peekSQL()); 
        return false; 
    } 
    return false; 
} 
 
 
 
#endif 
