 
#ifndef _PROTOLOGIN_H_ 
#define _PROTOLOGIN_H_ 
 
 
const unsigned short ID_PlatAuthReq = 100; //平台认证 
struct PlatAuthReq //平台认证 
{ 
	std::string account; //用户名 
	std::string token; //令牌 
	inline unsigned short GetProtoID() { return 100;} 
	inline std::string GetProtoName() { return "ID_PlatAuthReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PlatAuthReq & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.account; 
	ws << data.token; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PlatAuthReq & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.account;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.token;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const PlatAuthReq & info) 
{ 
	stm << "account=" << info.account << ", token=" << info.token; 
	return stm; 
} 
 
const unsigned short ID_PlatAuthAck = 101; //认证结果, 包含该用户的所有用户/角色数据 
struct PlatAuthAck //认证结果, 包含该用户的所有用户/角色数据 
{ 
	unsigned short retCode;  
	UserInfoArray users; //该帐号下的所有用户信息 
	PlatAuthAck() 
	{ 
		retCode = 0; 
	} 
	inline unsigned short GetProtoID() { return 101;} 
	inline std::string GetProtoName() { return "ID_PlatAuthAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const PlatAuthAck & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.users; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, PlatAuthAck & data) 
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
		rs >> data.users;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const PlatAuthAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", users=" << info.users; 
	return stm; 
} 
 
const unsigned short ID_CreateUserReq = 102; //创建一个新的用户数据 
struct CreateUserReq //创建一个新的用户数据 
{ 
	std::string nickName; //昵称 
	int iconID; //头像 
	CreateUserReq() 
	{ 
		iconID = 0; 
	} 
	inline unsigned short GetProtoID() { return 102;} 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserReq & info) 
{ 
	stm << "nickName=" << info.nickName << ", iconID=" << info.iconID; 
	return stm; 
} 
 
const unsigned short ID_CreateUserAck = 103; //创建结果和所有用户数据 
struct CreateUserAck //创建结果和所有用户数据 
{ 
	unsigned short retCode;  
	UserInfoArray users; //该帐号下的所有用户信息 
	CreateUserAck() 
	{ 
		retCode = 0; 
	} 
	inline unsigned short GetProtoID() { return 103;} 
	inline std::string GetProtoName() { return "ID_CreateUserAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const CreateUserAck & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.users; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, CreateUserAck & data) 
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
		rs >> data.users;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const CreateUserAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", users=" << info.users; 
	return stm; 
} 
 
const unsigned short ID_SelectUserReq = 104; //获取需要登录用户的所在服务器和认证令牌 
struct SelectUserReq //获取需要登录用户的所在服务器和认证令牌 
{ 
	unsigned long long uID;  
	SelectUserReq() 
	{ 
		uID = 0; 
	} 
	inline unsigned short GetProtoID() { return 104;} 
	inline std::string GetProtoName() { return "ID_SelectUserReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserReq & data) 
{ 
	unsigned long long tag = 1ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserReq & data) 
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
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SelectUserReq & info) 
{ 
	stm << "uID=" << info.uID; 
	return stm; 
} 
 
const unsigned short ID_SelectUserAck = 105; //获取需要登录用户的所在服务器和认证令牌 
struct SelectUserAck //获取需要登录用户的所在服务器和认证令牌 
{ 
	unsigned short retCode;  
	unsigned long long uID;  
	std::string token;  
	std::string ip;  
	unsigned short port;  
	SelectUserAck() 
	{ 
		retCode = 0; 
		uID = 0; 
		port = 0; 
	} 
	inline unsigned short GetProtoID() { return 105;} 
	inline std::string GetProtoName() { return "ID_SelectUserAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SelectUserAck & data) 
{ 
	unsigned long long tag = 31ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.uID; 
	ws << data.token; 
	ws << data.ip; 
	ws << data.port; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SelectUserAck & data) 
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
		rs >> data.uID;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.token;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.ip;  
	} 
	if ( (1ULL << 4) & tag) 
	{ 
		rs >> data.port;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SelectUserAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", uID=" << info.uID << ", token=" << info.token << ", ip=" << info.ip << ", port=" << info.port; 
	return stm; 
} 
 
const unsigned short ID_LoginReq = 106; //登录请求 
struct LoginReq //登录请求 
{ 
	unsigned long long uID;  
	std::string token;  
	LoginReq() 
	{ 
		uID = 0; 
	} 
	inline unsigned short GetProtoID() { return 106;} 
	inline std::string GetProtoName() { return "ID_LoginReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoginReq & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws << data.token; 
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
		rs >> data.uID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.token;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LoginReq & info) 
{ 
	stm << "uID=" << info.uID << ", token=" << info.token; 
	return stm; 
} 
 
const unsigned short ID_LoginAck = 107; //登录结果 
struct LoginAck //登录结果 
{ 
	unsigned short retCode;  
	LoginAck() 
	{ 
		retCode = 0; 
	} 
	inline unsigned short GetProtoID() { return 107;} 
	inline std::string GetProtoName() { return "ID_LoginAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const LoginAck & data) 
{ 
	unsigned long long tag = 1ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
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
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const LoginAck & info) 
{ 
	stm << "retCode=" << info.retCode; 
	return stm; 
} 
 
#endif 
