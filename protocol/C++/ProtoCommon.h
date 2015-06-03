 
#ifndef _PROTOCOMMON_H_ 
#define _PROTOCOMMON_H_ 
 
const unsigned short EC_SUCCESS = 0; //成功 
const unsigned short EC_ERROR = 1; //错误 
const unsigned short EC_INNER_ERROR = 2; //内部错误 
const unsigned short EC_DB_ERROR = 3; //数据库错误 
const unsigned short EC_PARAM_DENIED = 4; //非法参数 
const unsigned short EC_PERMISSION_DENIED = 5; //权限错误 
const unsigned short EC_INVALIDE_USER = 50; //错误的用户信息 
const unsigned short EC_TOKEN_EXPIRE = 51; //令牌过期 
const unsigned short EC_OWNER_FRIEND = 100; //自己的好友 
const unsigned short EC_OWNER_BLACKLIST = 101; //自己的黑名单用户 
const unsigned short EC_TARGET_BLACKLIST = 102; //对方的黑名单用户 
 
struct SessionToken //认证令牌 
{ 
	unsigned long long uID;  
	std::string token;  
	unsigned int tokenExpire;  
	SessionToken() 
	{ 
		uID = 0; 
		tokenExpire = 0; 
	} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SessionToken & data) 
{ 
	unsigned long long tag = 7ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws << data.token; 
	ws << data.tokenExpire; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SessionToken & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.uID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.token;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.tokenExpire;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SessionToken & info) 
{ 
	stm << "uID=" << info.uID << ", token=" << info.token << ", tokenExpire=" << info.tokenExpire; 
	return stm; 
} 
 
struct UserInfo //用户信息 
{ 
	unsigned long long uID; //用户唯一ID 
	std::string account; //帐号 
	std::string nickName; //昵称 
	short iconID; //头像 
	int diamond; //当前剩余的充值钻石 
	int hisotryDiamond; //历史充值钻石总额 
	int giftDiamond; //当前剩余的赠送钻石 
	unsigned int joinTime; //加入时间 
	UserInfo() 
	{ 
		uID = 0; 
		iconID = 0; 
		diamond = 0; 
		hisotryDiamond = 0; 
		giftDiamond = 0; 
		joinTime = 0; 
	} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const UserInfo & data) 
{ 
	unsigned long long tag = 255ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws << data.account; 
	ws << data.nickName; 
	ws << data.iconID; 
	ws << data.diamond; 
	ws << data.hisotryDiamond; 
	ws << data.giftDiamond; 
	ws << data.joinTime; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, UserInfo & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.uID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.account;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.nickName;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.iconID;  
	} 
	if ( (1ULL << 4) & tag) 
	{ 
		rs >> data.diamond;  
	} 
	if ( (1ULL << 5) & tag) 
	{ 
		rs >> data.hisotryDiamond;  
	} 
	if ( (1ULL << 6) & tag) 
	{ 
		rs >> data.giftDiamond;  
	} 
	if ( (1ULL << 7) & tag) 
	{ 
		rs >> data.joinTime;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const UserInfo & info) 
{ 
	stm << "uID=" << info.uID << ", account=" << info.account << ", nickName=" << info.nickName << ", iconID=" << info.iconID << ", diamond=" << info.diamond << ", hisotryDiamond=" << info.hisotryDiamond << ", giftDiamond=" << info.giftDiamond << ", joinTime=" << info.joinTime; 
	return stm; 
} 
 
typedef std::vector<UserInfo> UserInfoArray;  
 
typedef std::vector<unsigned long long> UserIDArray;  
const unsigned short ETRIGGER_USER_LOGIN = 0; //用户登录, 用户ID 
const unsigned short ETRIGGER_USER_LOGOUT = 1; //用户登出, 用户ID 
 
const unsigned short ID_Heartbeat = 200; //心跳包 
struct Heartbeat //心跳包 
{ 
	unsigned int timeStamp; //服务器当前UTC时间戳 
	unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
	Heartbeat() 
	{ 
		timeStamp = 0; 
		timeTick = 0; 
	} 
	inline unsigned short GetProtoID() { return 200;} 
	inline std::string GetProtoName() { return "ID_Heartbeat";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const Heartbeat & data) 
{ 
	unsigned long long tag = 3ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.timeStamp; 
	ws << data.timeTick; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, Heartbeat & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.timeStamp;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.timeTick;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const Heartbeat & info) 
{ 
	stm << "timeStamp=" << info.timeStamp << ", timeTick=" << info.timeTick; 
	return stm; 
} 
 
const unsigned short ID_HeartbeatEcho = 201; //心跳包需要立刻回复 
struct HeartbeatEcho //心跳包需要立刻回复 
{ 
	unsigned int timeStamp; //服务器当前UTC时间戳 
	unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
	HeartbeatEcho() 
	{ 
		timeStamp = 0; 
		timeTick = 0; 
	} 
	inline unsigned short GetProtoID() { return 201;} 
	inline std::string GetProtoName() { return "ID_HeartbeatEcho";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const HeartbeatEcho & data) 
{ 
	unsigned long long tag = 3ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.timeStamp; 
	ws << data.timeTick; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, HeartbeatEcho & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.timeStamp;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.timeTick;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const HeartbeatEcho & info) 
{ 
	stm << "timeStamp=" << info.timeStamp << ", timeTick=" << info.timeTick; 
	return stm; 
} 
 
#endif 
