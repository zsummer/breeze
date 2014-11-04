 
 #ifndef _PROTOCOMMON_H_ 
 #define _PROTOCOMMON_H_ 
  
 const unsigned short BEC_SUCCESS = 0; //成功 
 const unsigned short BEC_UNKOWN_ERROR = 1; //未知错误 
 const unsigned short BEC_SERVER_ERROR = 2; //服务器内部错误 
 const unsigned short BEC_DB_ERROR = 3; //服务器内部错误 
 const unsigned short BEC_INVALIDE_CHAR_ID = 4; //角色ID无效 
 const unsigned short BEC_INVALIDE_ACC_ID = 5; //帐号ID无效 
 const unsigned short BEC_AUTH_NOT_FOUND_USER = 20; //认证错误:找不到用户名 
 const unsigned short BEC_AUTH_PWD_INCORRECT = 21; //认证错误:密码错误 
 const unsigned short BEC_AUTH_ING = 22; //认证错误:正在认证中... 
 const unsigned short BEC_AUTH_AREADY_AUTH = 23; //认证错误:重复认证 
 const unsigned short BEC_AUTH_LIMITE_COUNT = 24; //认证错误:认证次数超过限制 
 const unsigned short BEC_LOGIN_CHAR_ID_NOT_FOUND = 25; //角色ID不存在 
 const unsigned short BEC_LOGIN_CHAR_ID_INCORRECT = 26; //角色ID错误 
 const unsigned short BEC_LOGIN_CHAR_NAME_INCORRECT = 27; //角色名冲突 
  
 struct CharacterInfo //角色信息 
 { 
 	unsigned long long accID;  
 	unsigned long long charID; //角色ID 
 	unsigned int iconID; //头像 
 	unsigned int level; //等级 
 	std::string charName; //昵称 
 	CharacterInfo() 
 	{ 
 		accID = 0; 
 		charID = 0; 
 		iconID = 0; 
 		level = 0; 
 	} 
 }; 
 template<class T> 
 T & operator << (T & t, const CharacterInfo & data) 
 { 
 	t << data.accID; 
 	t << data.charID; 
 	t << data.iconID; 
 	t << data.level; 
 	t << data.charName; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, CharacterInfo & data) 
 { 
 	t >> data.accID; 
 	t >> data.charID; 
 	t >> data.iconID; 
 	t >> data.level; 
 	t >> data.charName; 
 	return t; 
 } 
  
 typedef std::vector<CharacterInfo> CharacterInfoVct;  
  
 struct AccountInfo //帐号信息 
 { 
 	std::string accName;  
 	unsigned long long accID;  
 	unsigned int diamond; //当前剩余的充值钻石 
 	unsigned int hisDiamond; //历史充值钻石总额 
 	unsigned int giftDmd; //当前剩余的赠送钻石 
 	unsigned int hisGiftDmd; //历往赠送钻石总额 
 	CharacterInfoVct charInfos; //角色信息 
 	AccountInfo() 
 	{ 
 		accID = 0; 
 		diamond = 0; 
 		hisDiamond = 0; 
 		giftDmd = 0; 
 		hisGiftDmd = 0; 
 	} 
 }; 
 template<class T> 
 T & operator << (T & t, const AccountInfo & data) 
 { 
 	t << data.accName; 
 	t << data.accID; 
 	t << data.diamond; 
 	t << data.hisDiamond; 
 	t << data.giftDmd; 
 	t << data.hisGiftDmd; 
 	t << data.charInfos; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, AccountInfo & data) 
 { 
 	t >> data.accName; 
 	t >> data.accID; 
 	t >> data.diamond; 
 	t >> data.hisDiamond; 
 	t >> data.giftDmd; 
 	t >> data.hisGiftDmd; 
 	t >> data.charInfos; 
 	return t; 
 } 
  
 typedef std::vector<AccountInfo> AccountInfoVct;  
  
 #endif 
 