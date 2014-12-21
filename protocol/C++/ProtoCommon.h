 
 #ifndef _PROTOCOMMON_H_ 
 #define _PROTOCOMMON_H_ 
  
 const unsigned short BEC_SUCCESS = 0; //成功 
 const unsigned short BEC_UNKOWN_ERROR = 1; //未知错误 
 const unsigned short BEC_INNER_ERROR = 2; //内部错误 
 const unsigned short BEC_DB_ERROR = 3; //数据库错误 
 const unsigned short BEC_PARAM_DENIED = 4; //非法参数 
 const unsigned short BEC_PERMISSION_DENIED = 5; //权限非法 
 const unsigned short BEC_SYSTEM_ERROR = 6; //系统错误 
 const unsigned short BEC_INVALIDE_USERID = 50; //用户ID无效 
 const unsigned short BEC_AUTH_USER_NOT_EXIST = 60; //认证错误:用户不存在 
 const unsigned short BEC_AUTH_PASSWD_INCORRECT = 61; //认证错误:密码错误 
 const unsigned short BEC_AUTH_ING = 62; //认证错误:正在认证中... 
 const unsigned short BEC_AUTH_AREADY_AUTH = 63; //认证错误:已认证 
 const unsigned short BEC_AUTH_LIMITE_COUNT = 64; //认证错误:认证次数超过限制 
  
 struct UserInfo //用户信息 
 { 
 	unsigned long long uid;  
 	std::string nickName; //用户昵称 
 	unsigned int iconID; //头像 
 	unsigned int level; //等级 
 	unsigned int diamond; //当前剩余的充值钻石 
 	unsigned int hisotryDiamond; //历史充值钻石总额 
 	unsigned int giftDiamond; //当前剩余的赠送钻石 
 	unsigned int joinTime; //加入时间 
 	UserInfo() 
 	{ 
 		uid = 0; 
 		iconID = 0; 
 		level = 0; 
 		diamond = 0; 
 		hisotryDiamond = 0; 
 		giftDiamond = 0; 
 		joinTime = 0; 
 	} 
 }; 
 template<class T> 
 T & operator << (T & t, const UserInfo & data) 
 { 
 	t << data.uid; 
 	t << data.nickName; 
 	t << data.iconID; 
 	t << data.level; 
 	t << data.diamond; 
 	t << data.hisotryDiamond; 
 	t << data.giftDiamond; 
 	t << data.joinTime; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, UserInfo & data) 
 { 
 	t >> data.uid; 
 	t >> data.nickName; 
 	t >> data.iconID; 
 	t >> data.level; 
 	t >> data.diamond; 
 	t >> data.hisotryDiamond; 
 	t >> data.giftDiamond; 
 	t >> data.joinTime; 
 	return t; 
 } 
  
 typedef std::vector<UserInfo> UserInfoVct;  
  
 #endif 
 