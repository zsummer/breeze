 
#ifndef _PROTOFRIENDSQL_H_ 
#define _PROTOFRIENDSQL_H_ 
 
 
inline std::vector<std::string> FriendInfo_BUILD() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("desc `tb_FriendInfo`"); 
    ret.push_back("CREATE TABLE `tb_FriendInfo` (        `ownID` bigint(20) unsigned NOT NULL DEFAULT '0' ,         `fID` bigint(20) unsigned NOT NULL DEFAULT '0' ,         PRIMARY KEY(`ownID`,`fID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_FriendInfo` add `flag`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FriendInfo` add `makeTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
 
inline std::string FriendInfo_LOAD( unsigned long long curLoaded) 
{ 
    zsummer::mysql::DBQuery q(" select `ownID`,`fID`,`flag`,`makeTime`from `tb_FriendInfo` order by `ownID`,`fID` desc limit ?, 1000 "); 
    q << curLoaded; 
    return q.popSQL(); 
} 
 
inline std::string FriendInfo_SELECT(unsigned long long ownID, unsigned long long fID) 
{ 
    zsummer::mysql::DBQuery q(" select `ownID`,`fID`,`flag`,`makeTime`from `tb_FriendInfo` where `ownID` = ? and `fID` = ? "); 
    q << ownID; 
    q << fID; 
    return q.popSQL(); 
} 
 
inline std::map<unsigned long long, std::map<unsigned long long, FriendInfo> >  FriendInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
    std::map<unsigned long long, std::map<unsigned long long, FriendInfo> >  ret; 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
        return ret; 
    } 
    try 
    { 
        while (ptr->haveRow()) 
        { 
            FriendInfo info; 
            *ptr >> info.ownID; 
            *ptr >> info.fID; 
            *ptr >> info.flag; 
            *ptr >> info.makeTime; 
            ret[info.ownID][info.fID] = info;  
        } 
    } 
    catch(std::runtime_error e) 
    { 
        LOGE("fetch info catch one runtime error. what=" << e.what()); 
        return ret; 
    } 
    return std::move(ret); 
} 
 
 
inline std::string FriendInfo_INSERT( const FriendInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_FriendInfo( `ownID`,`fID`,`flag`,`makeTime`) values(?,?,?,?)"); 
    q << info.ownID; 
    q << info.fID; 
    q << info.flag; 
    q << info.makeTime; 
    return q.popSQL(); 
} 
 
 
inline std::string FriendInfo_UPDATE( const FriendInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_FriendInfo(ownID,fID) values(?,? ) on duplicate key update `flag` = ?,`makeTime` = ? "); 
    q << info.ownID; 
    q << info.fID; 
    q << info.flag; 
    q << info.makeTime; 
    return q.popSQL(); 
} 
 
 
#endif 
