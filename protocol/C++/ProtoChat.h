 
#ifndef _PROTOCHAT_H_ 
#define _PROTOCHAT_H_ 
 
const unsigned char FRIEND_WAITING = 0; //等待好友同意 
const unsigned char FRIEND_REQUESTING = 1; //等待确认 
const unsigned char FRIEND_BLACKLIST = 2; //黑名单 
const unsigned char FRIEND_ESTABLISHED = 3; //好友 
const unsigned char FRIEND_ADDFRIEND = 0; //添加好友 
const unsigned char FRIEND_ADDBLACK = 1; //添加黑名单 
const unsigned char FRIEND_REMOVEFRIEND = 2; //移除好友 
const unsigned char FRIEND_REMOVEBLACK = 3; //移除黑名单 
const unsigned char FRIEND_ALLOW = 4; //同意 
const unsigned char FRIEND_REJECT = 5; //拒绝 
const unsigned char FRIEND_IGNORE = 6; //忽略 
const unsigned char CHANNEL_PRIVATE = 0; //私聊, 需要指明具体某个uid 
const unsigned char CHANNEL_WORLD = 1; //世界 
const unsigned char CHANNEL_GROUP = 2; //群组, 需要指明具体某个groupid 
 
struct FriendInfo //好友信息 
{ 
	unsigned long long uID;  
	unsigned char flag; //状态标志 
	unsigned int makeTime; //建立时间 
	FriendInfo() 
	{ 
		uID = 0; 
		flag = 0; 
		makeTime = 0; 
	} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FriendInfo & data) 
{ 
	unsigned long long tag = 7ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
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
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.uID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.flag;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.makeTime;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FriendInfo & info) 
{ 
	stm << "uID=" << info.uID << ", flag=" << info.flag << ", makeTime=" << info.makeTime; 
	return stm; 
} 
 
typedef std::vector<FriendInfo> FriendInfoArray;  
 
struct ContactInfo //联系人卡片 
{ 
	unsigned long long uID;  
	std::string nickName; //用户昵称 
	short iconID; //头像 
	unsigned char banned; //禁言 
	unsigned long long groupID; //加入的群组ID, 0为没有加入任何群组 
	unsigned int totalBlacks; //被拉黑次数 
	unsigned int totalFriends; //好友个数 
	unsigned char onlineFlag; //在线状态0离线,1在线 
	FriendInfoArray friends; //好友信息/黑名单信息/好友请求 
	ContactInfo() 
	{ 
		uID = 0; 
		iconID = 0; 
		banned = 0; 
		groupID = 0; 
		totalBlacks = 0; 
		totalFriends = 0; 
		onlineFlag = 0; 
	} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ContactInfo & data) 
{ 
	unsigned long long tag = 511ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws << data.nickName; 
	ws << data.iconID; 
	ws << data.banned; 
	ws << data.groupID; 
	ws << data.totalBlacks; 
	ws << data.totalFriends; 
	ws << data.onlineFlag; 
	ws << data.friends; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ContactInfo & data) 
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
		rs >> data.banned;  
	} 
	if ( (1ULL << 4) & tag) 
	{ 
		rs >> data.groupID;  
	} 
	if ( (1ULL << 5) & tag) 
	{ 
		rs >> data.totalBlacks;  
	} 
	if ( (1ULL << 6) & tag) 
	{ 
		rs >> data.totalFriends;  
	} 
	if ( (1ULL << 7) & tag) 
	{ 
		rs >> data.onlineFlag;  
	} 
	if ( (1ULL << 8) & tag) 
	{ 
		rs >> data.friends;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ContactInfo & info) 
{ 
	stm << "uID=" << info.uID << ", nickName=" << info.nickName << ", iconID=" << info.iconID << ", banned=" << info.banned << ", groupID=" << info.groupID << ", totalBlacks=" << info.totalBlacks << ", totalFriends=" << info.totalFriends << ", onlineFlag=" << info.onlineFlag << ", friends=" << info.friends; 
	return stm; 
} 
 
typedef std::vector<ContactInfo> ContactInfoArray;  
 
struct ChatInfo //聊天消息 
{ 
	unsigned long long mID; //msg id 
	unsigned char chlType; //channel type 
	unsigned long long srcID;  
	std::string srcName; //src 
	short srcIcon; //src 
	unsigned long long dstID; //userid or groupid 
	std::string dstName; //src 
	short dstIcon; //src 
	std::string msg;  
	unsigned int sendTime;  
	ChatInfo() 
	{ 
		mID = 0; 
		chlType = 0; 
		srcID = 0; 
		srcIcon = 0; 
		dstID = 0; 
		dstIcon = 0; 
		sendTime = 0; 
	} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatInfo & data) 
{ 
	unsigned long long tag = 1023ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.mID; 
	ws << data.chlType; 
	ws << data.srcID; 
	ws << data.srcName; 
	ws << data.srcIcon; 
	ws << data.dstID; 
	ws << data.dstName; 
	ws << data.dstIcon; 
	ws << data.msg; 
	ws << data.sendTime; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatInfo & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.mID;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.chlType;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.srcID;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.srcName;  
	} 
	if ( (1ULL << 4) & tag) 
	{ 
		rs >> data.srcIcon;  
	} 
	if ( (1ULL << 5) & tag) 
	{ 
		rs >> data.dstID;  
	} 
	if ( (1ULL << 6) & tag) 
	{ 
		rs >> data.dstName;  
	} 
	if ( (1ULL << 7) & tag) 
	{ 
		rs >> data.dstIcon;  
	} 
	if ( (1ULL << 8) & tag) 
	{ 
		rs >> data.msg;  
	} 
	if ( (1ULL << 9) & tag) 
	{ 
		rs >> data.sendTime;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatInfo & info) 
{ 
	stm << "mID=" << info.mID << ", chlType=" << info.chlType << ", srcID=" << info.srcID << ", srcName=" << info.srcName << ", srcIcon=" << info.srcIcon << ", dstID=" << info.dstID << ", dstName=" << info.dstName << ", dstIcon=" << info.dstIcon << ", msg=" << info.msg << ", sendTime=" << info.sendTime; 
	return stm; 
} 
 
typedef std::vector<ChatInfo> ChatInfoArray;  
 
const unsigned short ID_GetContactInfoReq = 1000; //获取联系人名片请求 
struct GetContactInfoReq //获取联系人名片请求 
{ 
	unsigned long long uID;  
	GetContactInfoReq() 
	{ 
		uID = 0; 
	} 
	inline unsigned short GetProtoID() { return 1000;} 
	inline std::string GetProtoName() { return "ID_GetContactInfoReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetContactInfoReq & data) 
{ 
	unsigned long long tag = 1ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.uID; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetContactInfoReq & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetContactInfoReq & info) 
{ 
	stm << "uID=" << info.uID; 
	return stm; 
} 
 
const unsigned short ID_GetContactInfoAck = 1001; //获取联系人名片结果 
struct GetContactInfoAck //获取联系人名片结果 
{ 
	unsigned short retCode;  
	ContactInfo contact;  
	GetContactInfoAck() 
	{ 
		retCode = 0; 
	} 
	inline unsigned short GetProtoID() { return 1001;} 
	inline std::string GetProtoName() { return "ID_GetContactInfoAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const GetContactInfoAck & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.contact; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, GetContactInfoAck & data) 
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
		rs >> data.contact;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const GetContactInfoAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", contact=" << info.contact; 
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
 
const unsigned short ID_JoinGropuReq = 1007; //加入群组 
struct JoinGropuReq //加入群组 
{ 
	inline unsigned short GetProtoID() { return 1007;} 
	inline std::string GetProtoName() { return "ID_JoinGropuReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinGropuReq & data) 
{ 
	unsigned long long tag = 0ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinGropuReq & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinGropuReq & info) 
{ 
; 
	return stm; 
} 
 
const unsigned short ID_JoinGropuAck = 1008; //加入群组 
struct JoinGropuAck //加入群组 
{ 
	inline unsigned short GetProtoID() { return 1008;} 
	inline std::string GetProtoName() { return "ID_JoinGropuAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const JoinGropuAck & data) 
{ 
	unsigned long long tag = 0ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, JoinGropuAck & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const JoinGropuAck & info) 
{ 
; 
	return stm; 
} 
 
const unsigned short ID_ChatReq = 1004; //发送聊天请求 
struct ChatReq //发送聊天请求 
{ 
	unsigned char chlType; //channel type 
	unsigned long long dstID; //userID or groupID 
	std::string msg; //msg 
	ChatReq() 
	{ 
		chlType = 0; 
		dstID = 0; 
	} 
	inline unsigned short GetProtoID() { return 1004;} 
	inline std::string GetProtoName() { return "ID_ChatReq";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatReq & data) 
{ 
	unsigned long long tag = 7ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.chlType; 
	ws << data.dstID; 
	ws << data.msg; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatReq & data) 
{ 
	zsummer::proto4z::Integer sttLen = 0; 
	rs >> sttLen; 
	zsummer::proto4z::Integer cursor = rs.getStreamUnreadLen(); 
	unsigned long long tag = 0; 
	rs >> tag; 
	if ( (1ULL << 0) & tag) 
	{ 
		rs >> data.chlType;  
	} 
	if ( (1ULL << 1) & tag) 
	{ 
		rs >> data.dstID;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.msg;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatReq & info) 
{ 
	stm << "chlType=" << info.chlType << ", dstID=" << info.dstID << ", msg=" << info.msg; 
	return stm; 
} 
 
const unsigned short ID_ChatAck = 1005; //发送聊天请求 
struct ChatAck //发送聊天请求 
{ 
	unsigned short retCode;  
	unsigned char chlType; //channel type 
	unsigned long long dstID; //userID or groupID 
	unsigned long long msgID;  
	ChatAck() 
	{ 
		retCode = 0; 
		chlType = 0; 
		dstID = 0; 
		msgID = 0; 
	} 
	inline unsigned short GetProtoID() { return 1005;} 
	inline std::string GetProtoName() { return "ID_ChatAck";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatAck & data) 
{ 
	unsigned long long tag = 15ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.chlType; 
	ws << data.dstID; 
	ws << data.msgID; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatAck & data) 
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
		rs >> data.chlType;  
	} 
	if ( (1ULL << 2) & tag) 
	{ 
		rs >> data.dstID;  
	} 
	if ( (1ULL << 3) & tag) 
	{ 
		rs >> data.msgID;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatAck & info) 
{ 
	stm << "retCode=" << info.retCode << ", chlType=" << info.chlType << ", dstID=" << info.dstID << ", msgID=" << info.msgID; 
	return stm; 
} 
 
const unsigned short ID_ChatNotice = 1006; //聊天通知 
struct ChatNotice //聊天通知 
{ 
	unsigned short retCode;  
	ChatInfoArray msgs;  
	ChatNotice() 
	{ 
		retCode = 0; 
	} 
	inline unsigned short GetProtoID() { return 1006;} 
	inline std::string GetProtoName() { return "ID_ChatNotice";} 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const ChatNotice & data) 
{ 
	unsigned long long tag = 3ULL; 
	ws << (zsummer::proto4z::Integer)0; 
	zsummer::proto4z::Integer offset = ws.getStreamLen(); 
	ws << tag; 
	ws << data.retCode; 
	ws << data.msgs; 
	ws.fixOriginalData(offset - 4, ws.getStreamLen() - offset); 
	return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, ChatNotice & data) 
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
		rs >> data.msgs;  
	} 
	cursor = cursor - rs.getStreamUnreadLen(); 
	rs.skipOriginalData(sttLen - cursor); 
	return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const ChatNotice & info) 
{ 
	stm << "retCode=" << info.retCode << ", msgs=" << info.msgs; 
	return stm; 
} 
 
#endif 
