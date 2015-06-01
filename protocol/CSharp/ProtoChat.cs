 
namespace Proto4z  
{ 
	class STATIC_FRIEND_WAITING //等待好友同意 
	{ 
		public static Proto4z.ui8 value = 0;  
	} 
	class STATIC_FRIEND_REQUESTING //等待确认 
	{ 
		public static Proto4z.ui8 value = 1;  
	} 
	class STATIC_FRIEND_BLACKLIST //黑名单 
	{ 
		public static Proto4z.ui8 value = 2;  
	} 
	class STATIC_FRIEND_ESTABLISHED //好友 
	{ 
		public static Proto4z.ui8 value = 3;  
	} 
	class STATIC_FRIEND_ADDFRIEND //添加好友 
	{ 
		public static Proto4z.ui8 value = 0;  
	} 
	class STATIC_FRIEND_ADDBLACK //添加黑名单 
	{ 
		public static Proto4z.ui8 value = 1;  
	} 
	class STATIC_FRIEND_REMOVEFRIEND //移除好友 
	{ 
		public static Proto4z.ui8 value = 2;  
	} 
	class STATIC_FRIEND_REMOVEBLACK //移除黑名单 
	{ 
		public static Proto4z.ui8 value = 3;  
	} 
	class STATIC_FRIEND_ALLOW //同意 
	{ 
		public static Proto4z.ui8 value = 4;  
	} 
	class STATIC_FRIEND_REJECT //拒绝 
	{ 
		public static Proto4z.ui8 value = 5;  
	} 
	class STATIC_FRIEND_IGNORE //忽略 
	{ 
		public static Proto4z.ui8 value = 6;  
	} 
	class STATIC_CHANNEL_PRIVATE //私聊, 需要指明具体某个uid 
	{ 
		public static Proto4z.ui8 value = 0;  
	} 
	class STATIC_CHANNEL_WORLD //世界 
	{ 
		public static Proto4z.ui8 value = 1;  
	} 
	class STATIC_CHANNEL_GROUP //群组, 需要指明具体某个groupid 
	{ 
		public static Proto4z.ui8 value = 2;  
	} 
 
	class FriendInfo: Proto4z.IProtoObject //好友信息 
	{	 
		public Proto4z.ui64 ownID;  
		public Proto4z.ui64 fID;  
		public Proto4z.ui8 flag; //状态标志 
		public Proto4z.ui32 makeTime; //建立时间 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 15; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(ownID.__encode()); 
			data.AddRange(fID.__encode()); 
			data.AddRange(flag.__encode()); 
			data.AddRange(makeTime.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			ownID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				ownID.__decode(binData, ref pos); 
			} 
			fID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				fID.__decode(binData, ref pos); 
			} 
			flag = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				flag.__decode(binData, ref pos); 
			} 
			makeTime = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				makeTime.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class FriendInfoArray : System.Collections.Generic.List<FriendInfo>, Proto4z.IProtoObject  
	{ 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			var ret = new System.Collections.Generic.List<byte>(); 
			 var len = new Proto4z.ui32((System.UInt32)this.Count); 
			ret.AddRange(len.__encode()); 
			for (int i = 0; i < this.Count; i++ ) 
			{ 
				ret.AddRange(this[i].__encode()); 
			} 
			return ret; 
		} 
 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			var len = new Proto4z.ui32(0); 
			len.__decode(binData, ref pos); 
			if(len.val > 0) 
			{ 
				for (int i=0; i<len.val; i++) 
				{ 
					var data = new FriendInfo(); 
					 data.__decode(binData, ref pos); 
					this.Add(data); 
				} 
			} 
			return pos; 
		} 
	} 
 
	class ContactInfo: Proto4z.IProtoObject //联系人卡片 
	{	 
		public Proto4z.ui64 uID;  
		public Proto4z.String nickName; //用户昵称 
		public Proto4z.i16 iconID; //头像 
		public Proto4z.ui8 banned; //禁言 
		public Proto4z.ui64 groupID; //加入的群组ID, 0为没有加入任何群组 
		public Proto4z.ui8 onlineFlag; //在线状态0离线,1在线 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 63; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uID.__encode()); 
			data.AddRange(nickName.__encode()); 
			data.AddRange(iconID.__encode()); 
			data.AddRange(banned.__encode()); 
			data.AddRange(groupID.__encode()); 
			data.AddRange(onlineFlag.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			uID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				uID.__decode(binData, ref pos); 
			} 
			nickName = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				nickName.__decode(binData, ref pos); 
			} 
			iconID = new Proto4z.i16(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				iconID.__decode(binData, ref pos); 
			} 
			banned = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				banned.__decode(binData, ref pos); 
			} 
			groupID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 4)) != 0) 
			{ 
				groupID.__decode(binData, ref pos); 
			} 
			onlineFlag = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 5)) != 0) 
			{ 
				onlineFlag.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class ContactInfoArray : System.Collections.Generic.List<ContactInfo>, Proto4z.IProtoObject  
	{ 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			var ret = new System.Collections.Generic.List<byte>(); 
			 var len = new Proto4z.ui32((System.UInt32)this.Count); 
			ret.AddRange(len.__encode()); 
			for (int i = 0; i < this.Count; i++ ) 
			{ 
				ret.AddRange(this[i].__encode()); 
			} 
			return ret; 
		} 
 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			var len = new Proto4z.ui32(0); 
			len.__decode(binData, ref pos); 
			if(len.val > 0) 
			{ 
				for (int i=0; i<len.val; i++) 
				{ 
					var data = new ContactInfo(); 
					 data.__decode(binData, ref pos); 
					this.Add(data); 
				} 
			} 
			return pos; 
		} 
	} 
 
	class ChatInfo: Proto4z.IProtoObject //聊天消息 
	{	 
		public Proto4z.ui64 mID; //msg id 
		public Proto4z.ui8 chlType; //channel type 
		public Proto4z.ui64 srcID;  
		public Proto4z.String srcName; //src 
		public Proto4z.i16 srcIcon; //src 
		public Proto4z.ui64 dstID; //userid or groupid 
		public Proto4z.String dstName; //src 
		public Proto4z.i16 dstIcon; //src 
		public Proto4z.String msg;  
		public Proto4z.ui32 sendTime;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 1023; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(mID.__encode()); 
			data.AddRange(chlType.__encode()); 
			data.AddRange(srcID.__encode()); 
			data.AddRange(srcName.__encode()); 
			data.AddRange(srcIcon.__encode()); 
			data.AddRange(dstID.__encode()); 
			data.AddRange(dstName.__encode()); 
			data.AddRange(dstIcon.__encode()); 
			data.AddRange(msg.__encode()); 
			data.AddRange(sendTime.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			mID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				mID.__decode(binData, ref pos); 
			} 
			chlType = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				chlType.__decode(binData, ref pos); 
			} 
			srcID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				srcID.__decode(binData, ref pos); 
			} 
			srcName = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				srcName.__decode(binData, ref pos); 
			} 
			srcIcon = new Proto4z.i16(); 
			if ((tag.val & ((System.UInt64)1 << 4)) != 0) 
			{ 
				srcIcon.__decode(binData, ref pos); 
			} 
			dstID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 5)) != 0) 
			{ 
				dstID.__decode(binData, ref pos); 
			} 
			dstName = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 6)) != 0) 
			{ 
				dstName.__decode(binData, ref pos); 
			} 
			dstIcon = new Proto4z.i16(); 
			if ((tag.val & ((System.UInt64)1 << 7)) != 0) 
			{ 
				dstIcon.__decode(binData, ref pos); 
			} 
			msg = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 8)) != 0) 
			{ 
				msg.__decode(binData, ref pos); 
			} 
			sendTime = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 9)) != 0) 
			{ 
				sendTime.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class ChatInfoArray : System.Collections.Generic.List<ChatInfo>, Proto4z.IProtoObject  
	{ 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			var ret = new System.Collections.Generic.List<byte>(); 
			 var len = new Proto4z.ui32((System.UInt32)this.Count); 
			ret.AddRange(len.__encode()); 
			for (int i = 0; i < this.Count; i++ ) 
			{ 
				ret.AddRange(this[i].__encode()); 
			} 
			return ret; 
		} 
 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			var len = new Proto4z.ui32(0); 
			len.__decode(binData, ref pos); 
			if(len.val > 0) 
			{ 
				for (int i=0; i<len.val; i++) 
				{ 
					var data = new ChatInfo(); 
					 data.__decode(binData, ref pos); 
					this.Add(data); 
				} 
			} 
			return pos; 
		} 
	} 
 
	class GetContactInfoReq: Proto4z.IProtoObject //获取联系人名片请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1000); } 
		static public string getProtoName() { return "GetContactInfoReq"; } 
		public Proto4z.ui64 uID;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 1; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uID.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			uID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				uID.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class GetContactInfoAck: Proto4z.IProtoObject //获取联系人名片结果 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1001); } 
		static public string getProtoName() { return "GetContactInfoAck"; } 
		public Proto4z.ui16 retCode;  
		public ContactInfo contact;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(contact.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			retCode = new Proto4z.ui16(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				retCode.__decode(binData, ref pos); 
			} 
			contact = new ContactInfo(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				contact.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class GetSomeStrangersReq: Proto4z.IProtoObject //获取一些陌生人 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1002); } 
		static public string getProtoName() { return "GetSomeStrangersReq"; } 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 0; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			return (int)offset.val; 
		} 
	} 
 
	class GetSomeStrangersAck: Proto4z.IProtoObject //获取一些陌生人 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1003); } 
		static public string getProtoName() { return "GetSomeStrangersAck"; } 
		public Proto4z.ui16 retCode;  
		public UserIDArray uIDs;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(uIDs.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			retCode = new Proto4z.ui16(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				retCode.__decode(binData, ref pos); 
			} 
			uIDs = new UserIDArray(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				uIDs.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class FriendOperationReq: Proto4z.IProtoObject //好友操作请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1004); } 
		static public string getProtoName() { return "FriendOperationReq"; } 
		public Proto4z.ui64 uID; //目标ID 
		public Proto4z.ui8 oFlag; //操作指令 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uID.__encode()); 
			data.AddRange(oFlag.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			uID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				uID.__decode(binData, ref pos); 
			} 
			oFlag = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				oFlag.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class FriendOperationAck: Proto4z.IProtoObject //好友操作请求结果 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1005); } 
		static public string getProtoName() { return "FriendOperationAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.ui64 srcUID;  
		public Proto4z.ui8 srcFlag;  
		public Proto4z.ui64 dstUID;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 15; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(srcUID.__encode()); 
			data.AddRange(srcFlag.__encode()); 
			data.AddRange(dstUID.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			retCode = new Proto4z.ui16(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				retCode.__decode(binData, ref pos); 
			} 
			srcUID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				srcUID.__decode(binData, ref pos); 
			} 
			srcFlag = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				srcFlag.__decode(binData, ref pos); 
			} 
			dstUID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				dstUID.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class JoinGropuReq: Proto4z.IProtoObject //加入群组 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1006); } 
		static public string getProtoName() { return "JoinGropuReq"; } 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 0; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			return (int)offset.val; 
		} 
	} 
 
	class JoinGropuAck: Proto4z.IProtoObject //加入群组 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1007); } 
		static public string getProtoName() { return "JoinGropuAck"; } 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 0; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			return (int)offset.val; 
		} 
	} 
 
	class ChatReq: Proto4z.IProtoObject //发送聊天请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1008); } 
		static public string getProtoName() { return "ChatReq"; } 
		public Proto4z.ui8 chlType; //channel type 
		public Proto4z.ui64 dstID; //userID or groupID 
		public Proto4z.String msg; //msg 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 7; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(chlType.__encode()); 
			data.AddRange(dstID.__encode()); 
			data.AddRange(msg.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			chlType = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				chlType.__decode(binData, ref pos); 
			} 
			dstID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				dstID.__decode(binData, ref pos); 
			} 
			msg = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				msg.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class ChatAck: Proto4z.IProtoObject //发送聊天请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1009); } 
		static public string getProtoName() { return "ChatAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.ui8 chlType; //channel type 
		public Proto4z.ui64 dstID; //userID or groupID 
		public Proto4z.ui64 msgID;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 15; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(chlType.__encode()); 
			data.AddRange(dstID.__encode()); 
			data.AddRange(msgID.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			retCode = new Proto4z.ui16(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				retCode.__decode(binData, ref pos); 
			} 
			chlType = new Proto4z.ui8(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				chlType.__decode(binData, ref pos); 
			} 
			dstID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				dstID.__decode(binData, ref pos); 
			} 
			msgID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				msgID.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class ChatNotice: Proto4z.IProtoObject //聊天通知 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1010); } 
		static public string getProtoName() { return "ChatNotice"; } 
		public Proto4z.ui16 retCode;  
		public ChatInfoArray msgs;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(msgs.__encode()); 
			sttLen = (System.UInt32)data.Count + 8; 
			var ret = new System.Collections.Generic.List<byte>(); 
			ret.AddRange(sttLen.__encode()); 
			ret.AddRange(tag.__encode()); 
			ret.AddRange(data); 
			return ret; 
		} 
		public int __decode(byte[] binData, ref int pos) 
		{ 
			Proto4z.ui32 offset = 0; 
			Proto4z.ui64 tag = 0; 
			offset.__decode(binData, ref pos); 
			offset.val += (System.UInt32)pos; 
			tag.__decode(binData, ref pos); 
			retCode = new Proto4z.ui16(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				retCode.__decode(binData, ref pos); 
			} 
			msgs = new ChatInfoArray(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				msgs.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
} 
 
 
