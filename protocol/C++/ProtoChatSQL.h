 
#ifndef _PROTOCHATSQL_H_ 
#define _PROTOCHATSQL_H_ 
 
 
inline std::vector<std::string> FriendInfo_BUILD() 
{ 
	std::vector<std::string> ret; 
	ret.push_back("desc `tb_FriendInfo`"); 
	ret.push_back("CREATE TABLE `tb_FriendInfo` (		`ownID` bigint(20) unsigned NOT NULL DEFAULT '0' , 		`fID` bigint(20) unsigned NOT NULL DEFAULT '0' , 		PRIMARY KEY(`ownID`,`fID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
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
 
 
inline std::vector<std::string> ContactInfo_BUILD() 
{ 
	std::vector<std::string> ret; 
	ret.push_back("desc `tb_ContactInfo`"); 
	ret.push_back("CREATE TABLE `tb_ContactInfo` (		`uID` bigint(20) unsigned NOT NULL DEFAULT '0' , 		PRIMARY KEY(`uID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
	ret.push_back("alter table `tb_ContactInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ContactInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `banned`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `groupID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `onlineFlag`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	return std::move(ret); 
} 
 
inline std::string ContactInfo_LOAD( unsigned long long curLoaded) 
{ 
	zsummer::mysql::DBQuery q(" select `uID`,`nickName`,`iconID`,`banned`,`groupID`,`onlineFlag`from `tb_ContactInfo` order by `uID` desc limit ?, 1000 "); 
	q << curLoaded; 
	return q.popSQL(); 
} 
 
inline std::string ContactInfo_SELECT(unsigned long long uID) 
{ 
	zsummer::mysql::DBQuery q(" select `uID`,`nickName`,`iconID`,`banned`,`groupID`,`onlineFlag`from `tb_ContactInfo` where `uID` = ? "); 
	q << uID; 
	return q.popSQL(); 
} 
 
inline std::map<unsigned long long, ContactInfo>  ContactInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
	std::map<unsigned long long, ContactInfo>  ret; 
	if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
	{ 
		LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
		return ret; 
	} 
	try 
	{ 
		while (ptr->haveRow()) 
		{ 
			ContactInfo info; 
			*ptr >> info.uID; 
			*ptr >> info.nickName; 
			*ptr >> info.iconID; 
			*ptr >> info.banned; 
			*ptr >> info.groupID; 
			*ptr >> info.onlineFlag; 
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
 
 
inline std::string ContactInfo_INSERT( const ContactInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_ContactInfo( `uID`,`nickName`,`iconID`,`banned`,`groupID`,`onlineFlag`) values(?,?,?,?,?,?)"); 
	q << info.uID; 
	q << info.nickName; 
	q << info.iconID; 
	q << info.banned; 
	q << info.groupID; 
	q << info.onlineFlag; 
	return q.popSQL(); 
} 
 
 
inline std::string ContactInfo_UPDATE( const ContactInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_ContactInfo(uID) values(? ) on duplicate key update `nickName` = ?,`iconID` = ?,`banned` = ?,`groupID` = ?,`onlineFlag` = ? "); 
	q << info.uID; 
	q << info.nickName; 
	q << info.iconID; 
	q << info.banned; 
	q << info.groupID; 
	q << info.onlineFlag; 
	return q.popSQL(); 
} 
 
 
inline std::vector<std::string> ChatInfo_BUILD() 
{ 
	std::vector<std::string> ret; 
	ret.push_back("desc `tb_ChatInfo`"); 
	ret.push_back("CREATE TABLE `tb_ChatInfo` (		`mID` bigint(20) unsigned NOT NULL DEFAULT '0' , 		PRIMARY KEY(`mID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
	ret.push_back("alter table `tb_ChatInfo` add `chlType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `srcID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `srcName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ChatInfo` add `srcIcon`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `dstID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `dstName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ChatInfo` add `dstIcon`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `msg`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ChatInfo` add `sendTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	return std::move(ret); 
} 
 
inline std::string ChatInfo_LOAD( unsigned long long curLoaded) 
{ 
	zsummer::mysql::DBQuery q(" select `mID`,`chlType`,`srcID`,`srcName`,`srcIcon`,`dstID`,`dstName`,`dstIcon`,`msg`,`sendTime`from `tb_ChatInfo` order by `mID` desc limit ?, 1000 "); 
	q << curLoaded; 
	return q.popSQL(); 
} 
 
inline std::string ChatInfo_SELECT(unsigned long long mID) 
{ 
	zsummer::mysql::DBQuery q(" select `mID`,`chlType`,`srcID`,`srcName`,`srcIcon`,`dstID`,`dstName`,`dstIcon`,`msg`,`sendTime`from `tb_ChatInfo` where `mID` = ? "); 
	q << mID; 
	return q.popSQL(); 
} 
 
inline std::map<unsigned long long, ChatInfo>  ChatInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
	std::map<unsigned long long, ChatInfo>  ret; 
	if (ptr->getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
	{ 
		LOGE("fetch info from db found error. ErrorCode="  <<  ptr->getErrorCode() << ", Error=" << ptr->getLastError()); 
		return ret; 
	} 
	try 
	{ 
		while (ptr->haveRow()) 
		{ 
			ChatInfo info; 
			*ptr >> info.mID; 
			*ptr >> info.chlType; 
			*ptr >> info.srcID; 
			*ptr >> info.srcName; 
			*ptr >> info.srcIcon; 
			*ptr >> info.dstID; 
			*ptr >> info.dstName; 
			*ptr >> info.dstIcon; 
			*ptr >> info.msg; 
			*ptr >> info.sendTime; 
			ret[info.mID] = info;  
		} 
	} 
	catch(std::runtime_error e) 
	{ 
		LOGE("fetch info catch one runtime error. what=" << e.what()); 
		return ret; 
	} 
	return std::move(ret); 
} 
 
 
inline std::string ChatInfo_INSERT( const ChatInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_ChatInfo( `mID`,`chlType`,`srcID`,`srcName`,`srcIcon`,`dstID`,`dstName`,`dstIcon`,`msg`,`sendTime`) values(?,?,?,?,?,?,?,?,?,?)"); 
	q << info.mID; 
	q << info.chlType; 
	q << info.srcID; 
	q << info.srcName; 
	q << info.srcIcon; 
	q << info.dstID; 
	q << info.dstName; 
	q << info.dstIcon; 
	q << info.msg; 
	q << info.sendTime; 
	return q.popSQL(); 
} 
 
 
inline std::string ChatInfo_UPDATE( const ChatInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_ChatInfo(mID) values(? ) on duplicate key update `chlType` = ?,`srcID` = ?,`srcName` = ?,`srcIcon` = ?,`dstID` = ?,`dstName` = ?,`dstIcon` = ?,`msg` = ?,`sendTime` = ? "); 
	q << info.mID; 
	q << info.chlType; 
	q << info.srcID; 
	q << info.srcName; 
	q << info.srcIcon; 
	q << info.dstID; 
	q << info.dstName; 
	q << info.dstIcon; 
	q << info.msg; 
	q << info.sendTime; 
	return q.popSQL(); 
} 
 
 
#endif 
