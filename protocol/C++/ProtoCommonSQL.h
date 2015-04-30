 
#ifndef _PROTOCOMMONSQL_H_ 
#define _PROTOCOMMONSQL_H_ 
 
 
inline std::vector<std::string> UserInfo_BUILD() 
{ 
	std::vector<std::string> ret; 
	ret.push_back("desc `tb_UserInfo`"); 
	ret.push_back("CREATE TABLE `tb_UserInfo` (`uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,  PRIMARY KEY(`uID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
	ret.push_back("alter table `tb_UserInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_UserInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_UserInfo` add `diamond`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_UserInfo` add `hisotryDiamond`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_UserInfo` add `giftDiamond`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_UserInfo` add `joinTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	return std::move(ret); 
} 
 
inline std::string UserInfo_LOAD( unsigned long long curLoaded) 
{ 
	zsummer::mysql::DBQuery q(" select `uID`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime` from `tb_UserInfo` order by `uID` desc limit ?, 1000 "); 
	q << curLoaded; 
	return q.popSQL(); 
} 
 
inline std::string UserInfo_SELECT(unsigned long long uID) 
{ 
	zsummer::mysql::DBQuery q(" select `uID`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime` from `tb_UserInfo` where `uID` = ? "); 
	q << uID; 
	return q.popSQL(); 
} 
 
inline std::map<unsigned long long, UserInfo> UserInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
	std::map<unsigned long long, UserInfo> ret; 
	if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
	{ 
		LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
		return ret; 
	} 
	try 
	{ 
		while (ptr->haveRow()) 
		{ 
			UserInfo info; 
			*ptr >> info.uID; 
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
 
 
inline std::string UserInfo_INSERT( const UserInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_UserInfo( `uID`,`nickName`,`iconID`,`diamond`,`hisotryDiamond`,`giftDiamond`,`joinTime` ) values(?,?,?,?,?,?,?  )"); 
	q << info.uID; 
	q << info.nickName; 
	q << info.iconID; 
	q << info.diamond; 
	q << info.hisotryDiamond; 
	q << info.giftDiamond; 
	q << info.joinTime; 
	return q.popSQL(); 
} 
 
 
inline std::string UserInfo_UPDATE( const UserInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_UserInfo(uID) values(?) on duplicate key update `nickName` = ?,`iconID` = ?,`diamond` = ?,`hisotryDiamond` = ?,`giftDiamond` = ?,`joinTime` = ?  "); 
	q << info.uID; 
	q << info.nickName; 
	q << info.iconID; 
	q << info.diamond; 
	q << info.hisotryDiamond; 
	q << info.giftDiamond; 
	q << info.joinTime; 
	return q.popSQL(); 
} 
 
 
#endif 
