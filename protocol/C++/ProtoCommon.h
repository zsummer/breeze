 
#ifndef _PROTOCOMMON_H_ 
#define _PROTOCOMMON_H_ 
 
const unsigned short EC_SUCCESS = 0; //成功 
const unsigned short EC_UNKOWN_ERROR = 1; //未知错误 
const unsigned short EC_INNER_ERROR = 2; //内部错误 
const unsigned short EC_DB_ERROR = 3; //数据库错误 
const unsigned short EC_PARAM_DENIED = 4; //非法参数 
const unsigned short EC_PERMISSION_DENIED = 5; //权限非法 
const unsigned short EC_SYSTEM_ERROR = 6; //系统错误 
const unsigned short EC_INVALIDE_USERID = 50; //用户ID无效 
const unsigned short EC_AUTH_USER_NOT_EXIST = 60; //认证错误:用户不存在 
const unsigned short EC_AUTH_PASSWD_INCORRECT = 61; //认证错误:密码错误 
 
struct UserInfo //用户信息 
{ 
	unsigned long long uID;  
	std::string nickName; //用户昵称 
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
	unsigned long long tag = 127ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
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
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.uID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.nickName;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.iconID;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.diamond;  
	} 
	if ( (1ULL << 4) & tag) 
	{ 
		rs >> data.hisotryDiamond;  
	} 
	if ( (1ULL << 5) & tag) 
	{ 
		rs >> data.giftDiamond;  
	} 
	if ( (1ULL << 6) & tag) 
	{ 
		rs >> data.joinTime;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
 
typedef std::vector<UserInfo> UserInfoVct;  
 
typedef std::vector<unsigned long long> UserIDVct;  
const unsigned short ETRIGGER_USER_LOGIN = 0; //用户登录, 用户ID 
const unsigned short ETRIGGER_USER_LOGOUT = 1; //用户登出, 用户ID 
 
#endif 
