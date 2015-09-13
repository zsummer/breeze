 
#ifndef _PROTOFOLLOWSQL_H_ 
#define _PROTOFOLLOWSQL_H_ 
 
 
inline std::vector<std::string> FollowingInfo_BUILD() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("desc `tb_FollowingInfo`"); 
    ret.push_back("CREATE TABLE `tb_FollowingInfo` (        `following` bigint(20) unsigned NOT NULL DEFAULT '0' ,         `follower` bigint(20) unsigned NOT NULL DEFAULT '0' ,         PRIMARY KEY(`following`,`follower`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_FollowingInfo` add `status`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FollowingInfo` add `makeTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FollowingInfo` add `lastChanged`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
 
inline std::string FollowingInfo_LOAD( unsigned long long curLoaded) 
{ 
    zsummer::mysql::DBQuery q(" select `following`,`follower`,`status`,`makeTime`,`lastChanged`from `tb_FollowingInfo` order by `following`,`follower` desc limit ?, 1000 "); 
    q << curLoaded; 
    return q.popSQL(); 
} 
 
inline std::string FollowingInfo_SELECT(unsigned long long following, unsigned long long follower) 
{ 
    zsummer::mysql::DBQuery q(" select `following`,`follower`,`status`,`makeTime`,`lastChanged`from `tb_FollowingInfo` where `following` = ? and `follower` = ? "); 
    q << following; 
    q << follower; 
    return q.popSQL(); 
} 
 
inline std::map<unsigned long long, std::map<unsigned long long, FollowingInfo> >  FollowingInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
    std::map<unsigned long long, std::map<unsigned long long, FollowingInfo> >  ret; 
    if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
        return ret; 
    } 
    try 
    { 
        while (ptr->haveRow()) 
        { 
            FollowingInfo info; 
            *ptr >> info.following; 
            *ptr >> info.follower; 
            *ptr >> info.status; 
            *ptr >> info.makeTime; 
            *ptr >> info.lastChanged; 
            ret[info.following][info.follower] = info;  
        } 
    } 
    catch(std::runtime_error e) 
    { 
        LOGE("fetch info catch one runtime error. what=" << e.what()); 
        return ret; 
    } 
    return std::move(ret); 
} 
 
 
inline std::string FollowingInfo_INSERT( const FollowingInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_FollowingInfo( `following`,`follower`,`status`,`makeTime`,`lastChanged`) values(?,?,?,?,?)"); 
    q << info.following; 
    q << info.follower; 
    q << info.status; 
    q << info.makeTime; 
    q << info.lastChanged; 
    return q.popSQL(); 
} 
 
 
inline std::string FollowingInfo_UPDATE( const FollowingInfo & info)  
{ 
    zsummer::mysql::DBQuery q(" insert into tb_FollowingInfo(following,follower) values(?,? ) on duplicate key update `status` = ?,`makeTime` = ?,`lastChanged` = ? "); 
    q << info.following; 
    q << info.follower; 
    q << info.status; 
    q << info.makeTime; 
    q << info.lastChanged; 
    return q.popSQL(); 
} 
 
 
#endif 
