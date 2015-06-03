 
#ifndef _PROTOFRIEND_H_ 
#define _PROTOFRIEND_H_ 
 
const unsigned char FRIEND_DELETED = 0; //已删除好友关系 
const unsigned char FRIEND_WAITING = 1; //等待好友确认 
const unsigned char FRIEND_REQUESTING = 2; //需要确认 
const unsigned char FRIEND_BLACKLIST = 3; //黑名单 
const unsigned char FRIEND_ESTABLISHED = 4; //好友 
const unsigned char FRIEND_ADD_FRIEND = 0; //添加好友 
const unsigned char FRIEND_REMOVE_FRIEND = 1; //移除好友 
const unsigned char FRIEND_ADD_BLACKLIST = 2; //添加黑名单 
const unsigned char FRIEND_REMOVE_BLACKLIST = 3; //移除黑名单 
const unsigned char FRIEND_ALLOW = 4; //同意 
const unsigned char FRIEND_REJECT = 5; //拒绝 
const unsigned char FRIEND_IGNORE = 6; //忽略 
 
struct FriendInfo //好友信息 
{ 
	unsigned long long ownID;  
	unsigned long long fID;  
	unsigned char flag; //状态标志 
	unsigned int makeTime; //建立时间 
	FriendInfo() 
	{ 
		ownID = 0; 
		fID = 0; 
		flag = 0; 
		makeTime = 0; 
	} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendInfo & data) 
{ 
	unsigned long long tag = 15ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.ownID; 
	ws << data.fID; 
	ws << data.flag; 
	ws << data.makeTime; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendInfo & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.ownID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.fID;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.flag;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.makeTime;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FriendInfo & info) 
{ 
	stm << "ownID=" << info.ownID << ", fID=" << info.fID << ", flag=" << info.flag << ", makeTime=" << info.makeTime; 
	return stm; 
} 
 
typedef std::vector<FriendInfo> FriendInfoArray;  
 
const unsigned short ID_GetSomeStrangersReq = 1000; //获取一些陌生人 
struct GetSomeStrangersReq //获取一些陌生人 
{ 
	inline unsigned short GetProtoID() { return 1000;} 
	inline std::string GetProtoName() { return "ID_GetSomeStrangersReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSomeStrangersReq & data) 
{ 
	unsigned long long tag = 0ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSomeStrangersReq & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetSomeStrangersReq & info) 
{ 
; 
	return stm; 
} 
 
const unsigned short ID_GetSomeStrangersAck = 1001; //获取一些陌生人 
struct GetSomeStrangersAck //获取一些陌生人 
{ 
	unsigned short retCode;  
	UserIDArray uIDs;  
	GetSomeStrangersAck() 
	{ 
		retCode = 0; 
	} 
	inline unsigned short GetProtoID() { return 1001;} 
	inline std::string GetProtoName() { return "ID_GetSomeStrangersAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetSomeStrangersAck & data) 
{ 
	unsigned long long tag = 3ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.uIDs; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetSomeStrangersAck & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.retCode;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.uIDs;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetSomeStrangersAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", uIDs=" << info.uIDs; 
	return stm; 
} 
 
const unsigned short ID_FriendOperationReq = 1002; //好友操作请求 
struct FriendOperationReq //好友操作请求 
{ 
	unsigned long long uID; //目标ID 
	unsigned char oFlag; //操作指令 
	FriendOperationReq() 
	{ 
		uID = 0; 
		oFlag = 0; 
	} 
	inline unsigned short GetProtoID() { return 1002;} 
	inline std::string GetProtoName() { return "ID_FriendOperationReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendOperationReq & data) 
{ 
	unsigned long long tag = 3ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws << data.oFlag; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendOperationReq & data) 
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
		rs >> data.oFlag;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FriendOperationReq & info) 
{ 
	stm << "uID=" << info.uID << ", oFlag=" << info.oFlag; 
	return stm; 
} 
 
const unsigned short ID_FriendOperationAck = 1003; //好友操作请求结果 
struct FriendOperationAck //好友操作请求结果 
{ 
	unsigned short retCode;  
	unsigned long long srcUID;  
	unsigned char srcFlag;  
	unsigned long long dstUID;  
	FriendOperationAck() 
	{ 
		retCode = 0; 
		srcUID = 0; 
		srcFlag = 0; 
		dstUID = 0; 
	} 
	inline unsigned short GetProtoID() { return 1003;} 
	inline std::string GetProtoName() { return "ID_FriendOperationAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendOperationAck & data) 
{ 
	unsigned long long tag = 15ULL; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.srcUID; 
	ws << data.srcFlag; 
	ws << data.dstUID; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FriendOperationAck & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if (zsummer::proto4z::__localEndianType() != zsummer::proto4z::LittleEndian) tag = zsummer::proto4z::reversalInteger(tag); 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.retCode;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.srcUID;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.srcFlag;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.dstUID;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FriendOperationAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", srcUID=" << info.srcUID << ", srcFlag=" << info.srcFlag << ", dstUID=" << info.dstUID; 
	return stm; 
} 
 
#endif 
