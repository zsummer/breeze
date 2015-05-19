 
#ifndef _PROTOCHATSQL_H_ 
#define _PROTOCHATSQL_H_ 
 
 
inline std::vector<std::string> ContactInfo_BUILD() 
{ 
	std::vector<std::string> ret; 
	ret.push_back("desc `tb_ContactInfo`"); 
	ret.push_back("CREATE TABLE `tb_ContactInfo` (`uID` bigint(20) unsigned NOT NULL DEFAULT '0' ,  PRIMARY KEY(`uID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
	ret.push_back("alter table `tb_ContactInfo` add `nickName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ContactInfo` add `iconID`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `banned`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `totalBlacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `totalFriends`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ContactInfo` add `friends`  blob "); 
	return std::move(ret); 
} 
 
inline std::string ContactInfo_LOAD( unsigned long long curLoaded) 
{ 
	zsummer::mysql::DBQuery q(" select `uID`,`nickName`,`iconID`,`banned`,`totalBlacks`,`totalFriends`,`friends` from `tb_ContactInfo` order by `uID` desc limit ?, 1000 "); 
	q << curLoaded; 
	return q.popSQL(); 
} 
 
inline std::string ContactInfo_SELECT(unsigned long long uID) 
{ 
	zsummer::mysql::DBQuery q(" select `uID`,`nickName`,`iconID`,`banned`,`totalBlacks`,`totalFriends`,`friends` from `tb_ContactInfo` where `uID` = ? "); 
	q << uID; 
	return q.popSQL(); 
} 
 
inline std::map<unsigned long long, ContactInfo> ContactInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
	std::map<unsigned long long, ContactInfo> ret; 
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
			*ptr >> info.totalBlacks; 
			*ptr >> info.totalFriends; 
			try 
			{ 
				std::string blob; 
				*ptr >> blob; 
				if(!blob.empty()) 
				{ 
					zsummer::proto4z::ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false); 
					rs >> info.friends; 
				} 
			} 
			catch(std::runtime_error e) 
			{ 
				LOGW("fetch blob catch one runtime warning. what=" << e.what()); 
			} 
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
	zsummer::mysql::DBQuery q(" insert into tb_ContactInfo( `uID`,`nickName`,`iconID`,`banned`,`totalBlacks`,`totalFriends`,`friends` ) values(?,?,?,?,?,?,?  )"); 
	q << info.uID; 
	q << info.nickName; 
	q << info.iconID; 
	q << info.banned; 
	q << info.totalBlacks; 
	q << info.totalFriends; 
	try 
	{ 
		zsummer::proto4z::WriteStream ws(0); 
		ws << info.friends; 
		q << std::string(ws.getStreamBody(), ws.getStreamBodyLen()); 
	} 
	catch(std::runtime_error e) 
	{ 
		LOGW("write blob catch one runtime warning. what=" << e.what()); 
		return ""; 
	} 
	return q.popSQL(); 
} 
 
 
inline std::string ContactInfo_UPDATE( const ContactInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_ContactInfo(uID) values(?) on duplicate key update `nickName` = ?,`iconID` = ?,`banned` = ?,`totalBlacks` = ?,`totalFriends` = ?,`friends` = ?  "); 
	q << info.uID; 
	q << info.nickName; 
	q << info.iconID; 
	q << info.banned; 
	q << info.totalBlacks; 
	q << info.totalFriends; 
	try 
	{ 
		zsummer::proto4z::WriteStream ws(0); 
		ws << info.friends; 
		q << std::string(ws.getStreamBody(), ws.getStreamBodyLen()); 
	} 
	catch(std::runtime_error e) 
	{ 
		LOGW("write blob catch one runtime warning. what=" << e.what()); 
		return ""; 
	} 
	return q.popSQL(); 
} 
 
 
inline std::vector<std::string> ChatInfo_BUILD() 
{ 
	std::vector<std::string> ret; 
	ret.push_back("desc `tb_ChatInfo`"); 
	ret.push_back("CREATE TABLE `tb_ChatInfo` (`id` bigint(20) unsigned NOT NULL DEFAULT '0' ,  PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
	ret.push_back("alter table `tb_ChatInfo` add `chlType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `srcid`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `srcName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ChatInfo` add `srcIcon`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `dstid`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `dstName`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ChatInfo` add `dstIcon`  bigint(20) NOT NULL DEFAULT '0' "); 
	ret.push_back("alter table `tb_ChatInfo` add `msg`  varchar(255) NOT NULL DEFAULT '' "); 
	ret.push_back("alter table `tb_ChatInfo` add `sendTime`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
	return std::move(ret); 
} 
 
inline std::string ChatInfo_LOAD( unsigned long long curLoaded) 
{ 
	zsummer::mysql::DBQuery q(" select `id`,`chlType`,`srcid`,`srcName`,`srcIcon`,`dstid`,`dstName`,`dstIcon`,`msg`,`sendTime` from `tb_ChatInfo` order by `id` desc limit ?, 1000 "); 
	q << curLoaded; 
	return q.popSQL(); 
} 
 
inline std::string ChatInfo_SELECT(unsigned long long id) 
{ 
	zsummer::mysql::DBQuery q(" select `id`,`chlType`,`srcid`,`srcName`,`srcIcon`,`dstid`,`dstName`,`dstIcon`,`msg`,`sendTime` from `tb_ChatInfo` where `id` = ? "); 
	q << id; 
	return q.popSQL(); 
} 
 
inline std::map<unsigned long long, ChatInfo> ChatInfo_FETCH(zsummer::mysql::DBResultPtr ptr) 
{ 
	std::map<unsigned long long, ChatInfo> ret; 
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
			*ptr >> info.id; 
			*ptr >> info.chlType; 
			*ptr >> info.srcid; 
			*ptr >> info.srcName; 
			*ptr >> info.srcIcon; 
			*ptr >> info.dstid; 
			*ptr >> info.dstName; 
			*ptr >> info.dstIcon; 
			*ptr >> info.msg; 
			*ptr >> info.sendTime; 
			ret[info.id] = info; 
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
	zsummer::mysql::DBQuery q(" insert into tb_ChatInfo( `id`,`chlType`,`srcid`,`srcName`,`srcIcon`,`dstid`,`dstName`,`dstIcon`,`msg`,`sendTime` ) values(?,?,?,?,?,?,?,?,?,?  )"); 
	q << info.id; 
	q << info.chlType; 
	q << info.srcid; 
	q << info.srcName; 
	q << info.srcIcon; 
	q << info.dstid; 
	q << info.dstName; 
	q << info.dstIcon; 
	q << info.msg; 
	q << info.sendTime; 
	return q.popSQL(); 
} 
 
 
inline std::string ChatInfo_UPDATE( const ChatInfo & info)  
{ 
	zsummer::mysql::DBQuery q(" insert into tb_ChatInfo(id) values(?) on duplicate key update `chlType` = ?,`srcid` = ?,`srcName` = ?,`srcIcon` = ?,`dstid` = ?,`dstName` = ?,`dstIcon` = ?,`msg` = ?,`sendTime` = ?  "); 
	q << info.id; 
	q << info.chlType; 
	q << info.srcid; 
	q << info.srcName; 
	q << info.srcIcon; 
	q << info.dstid; 
	q << info.dstName; 
	q << info.dstIcon; 
	q << info.msg; 
	q << info.sendTime; 
	return q.popSQL(); 
} 
 
 
#endif 
