 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const C2LS_LoginReq & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.user; 
	ws << data.passwd; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, C2LS_LoginReq & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.user;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.passwd;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LS2C_LoginAck & data) 
{ 
	unsigned long long tag = 7ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.needCreateUser; 
	ws << data.info; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LS2C_LoginAck & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.retCode;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.needCreateUser;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.info;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const C2LS_CreateUserReq & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.nickName; 
	ws << data.iconID; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, C2LS_CreateUserReq & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.nickName;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.iconID;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LS2C_CreateUserAck & data) 
{ 
	unsigned long long tag = 7ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.needCreateUser; 
	ws << data.info; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LS2C_CreateUserAck & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.retCode;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.needCreateUser;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.info;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
 
const unsigned short ID_C2AS_ClientPulse = 106; //客户端存活脉冲 
struct C2AS_ClientPulse //客户端存活脉冲 
{ 
	inline unsigned short GetProtoID() { return 106;} 
	inline std::string GetProtoName() { return "ID_C2AS_ClientPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const C2AS_ClientPulse & data) 
{ 
	unsigned long long tag = 0ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, C2AS_ClientPulse & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
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
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AS2C_ServerPulse & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.timeStamp; 
	ws << data.timeTick; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AS2C_ServerPulse & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
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
 
#endif 
