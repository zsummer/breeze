 
 #ifndef _PROTOLOGIN_H_ 
 #define _PROTOLOGIN_H_ 
  
  
 const unsigned short ID_C2LS_LoginReq = 102; //登录请求 
 struct C2LS_LoginReq //登录请求 
 { 
 	std::string user;  
 	std::string passwd;  
 	inline unsigned short GetProtoID() { return 102;} 
 	inline std::string GetProtoName() { return "ID_C2LS_LoginReq";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2LS_LoginReq & data) 
 { 
 	t << data.user; 
 	t << data.passwd; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2LS_LoginReq & data) 
 { 
 	t >> data.user; 
 	t >> data.passwd; 
 	return t; 
 } 
  
 const unsigned short ID_LS2C_LoginAck = 103; //登录结果 
 struct LS2C_LoginAck //登录结果 
 { 
 	unsigned int retCode;  
 	unsigned int needCreateUser;  
 	UserInfo info; //认证成功但昵称为空 则说明需要创建用户信息 
 	LS2C_LoginAck() 
 	{ 
 		retCode = 0; 
 		needCreateUser = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 103;} 
 	inline std::string GetProtoName() { return "ID_LS2C_LoginAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const LS2C_LoginAck & data) 
 { 
 	t << data.retCode; 
 	t << data.needCreateUser; 
 	t << data.info; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, LS2C_LoginAck & data) 
 { 
 	t >> data.retCode; 
 	t >> data.needCreateUser; 
 	t >> data.info; 
 	return t; 
 } 
  
 const unsigned short ID_C2LS_CreateUserReq = 108; //填写用户信息 
 struct C2LS_CreateUserReq //填写用户信息 
 { 
 	std::string nickName; //昵称 
 	unsigned int iconID; //头像 
 	C2LS_CreateUserReq() 
 	{ 
 		iconID = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 108;} 
 	inline std::string GetProtoName() { return "ID_C2LS_CreateUserReq";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2LS_CreateUserReq & data) 
 { 
 	t << data.nickName; 
 	t << data.iconID; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2LS_CreateUserReq & data) 
 { 
 	t >> data.nickName; 
 	t >> data.iconID; 
 	return t; 
 } 
  
 const unsigned short ID_LS2C_CreateUserAck = 109; //返回 
 struct LS2C_CreateUserAck //返回 
 { 
 	unsigned short retCode;  
 	unsigned int needCreateUser; //nickname冲突需要重新创建 
 	UserInfo info;  
 	LS2C_CreateUserAck() 
 	{ 
 		retCode = 0; 
 		needCreateUser = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 109;} 
 	inline std::string GetProtoName() { return "ID_LS2C_CreateUserAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const LS2C_CreateUserAck & data) 
 { 
 	t << data.retCode; 
 	t << data.needCreateUser; 
 	t << data.info; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, LS2C_CreateUserAck & data) 
 { 
 	t >> data.retCode; 
 	t >> data.needCreateUser; 
 	t >> data.info; 
 	return t; 
 } 
  
 const unsigned short ID_C2AS_ClientPulse = 106; //客户端存活脉冲 
 struct C2AS_ClientPulse //客户端存活脉冲 
 { 
 	inline unsigned short GetProtoID() { return 106;} 
 	inline std::string GetProtoName() { return "ID_C2AS_ClientPulse";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2AS_ClientPulse & data) 
 { 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2AS_ClientPulse & data) 
 { 
 	return t; 
 } 
  
 const unsigned short ID_AS2C_ServerPulse = 107; //服务端存活脉冲 
 struct AS2C_ServerPulse //服务端存活脉冲 
 { 
 	unsigned int timeStamp; //服务器当前UTC时间戳 
 	unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 	AS2C_ServerPulse() 
 	{ 
 		timeStamp = 0; 
 		timeTick = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 107;} 
 	inline std::string GetProtoName() { return "ID_AS2C_ServerPulse";} 
 }; 
 template<class T> 
 T & operator << (T & t, const AS2C_ServerPulse & data) 
 { 
 	t << data.timeStamp; 
 	t << data.timeTick; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, AS2C_ServerPulse & data) 
 { 
 	t >> data.timeStamp; 
 	t >> data.timeTick; 
 	return t; 
 } 
  
 #endif 
 