 
#ifndef _PROTOLOGIN_H_ 
#define _PROTOLOGIN_H_ 
 
 
const unsigned short ID_LoginReq = 100; //登录请求 
struct LoginReq //登录请求 
{ 
	std::string user;  
	std::string passwd;  
	inline unsigned short GetProtoID() { return 100;} 
	inline std::string GetProtoName() { return "ID_LoginReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoginReq & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoginReq & data) 
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
 
const unsigned short ID_CreateUserReq = 101; //填写用户信息 
struct CreateUserReq //填写用户信息 
{ 
	std::string nickName; //昵称 
	int iconID; //头像 
	CreateUserReq() 
	{ 
		iconID = 0; 
	} 
	inline unsigned short GetProtoID() { return 101;} 
	inline std::string GetProtoName() { return "ID_CreateUserReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserReq & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserReq & data) 
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
 
const unsigned short ID_LoginAck = 102; //登录结果 
struct LoginAck //登录结果 
{ 
	unsigned short retCode;  
	unsigned short needCreate;  
	UserInfo info; //用户信息 
	LoginAck() 
	{ 
		retCode = 0; 
		needCreate = 0; 
	} 
	inline unsigned short GetProtoID() { return 102;} 
	inline std::string GetProtoName() { return "ID_LoginAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoginAck & data) 
{ 
	unsigned long long tag = 7ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.needCreate; 
	ws << data.info; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, LoginAck & data) 
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
		rs >> data.needCreate;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.info;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
 
const unsigned short ID_ServerPulse = 103; //服务器生命脉冲 
struct ServerPulse //服务器生命脉冲 
{ 
	unsigned int timeStamp; //服务器当前UTC时间戳 
	unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
	ServerPulse() 
	{ 
		timeStamp = 0; 
		timeTick = 0; 
	} 
	inline unsigned short GetProtoID() { return 103;} 
	inline std::string GetProtoName() { return "ID_ServerPulse";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ServerPulse & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ServerPulse & data) 
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
 
const unsigned short ID_ServerPulseEcho = 104; //服务器生命脉冲客户端回放 
struct ServerPulseEcho //服务器生命脉冲客户端回放 
{ 
	unsigned int timeStamp; //服务器当前UTC时间戳 
	unsigned int timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
	ServerPulseEcho() 
	{ 
		timeStamp = 0; 
		timeTick = 0; 
	} 
	inline unsigned short GetProtoID() { return 104;} 
	inline std::string GetProtoName() { return "ID_ServerPulseEcho";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ServerPulseEcho & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ServerPulseEcho & data) 
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
