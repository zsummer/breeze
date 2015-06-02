 
namespace Proto4z  
{ 
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
 
	class JoinGropuReq: Proto4z.IProtoObject //加入频道 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1100); } 
		static public string getProtoName() { return "JoinGropuReq"; } 
		public Proto4z.ui8 chlType; //channel type 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 1; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(chlType.__encode()); 
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
			return (int)offset.val; 
		} 
	} 
 
	class JoinGropuAck: Proto4z.IProtoObject 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1101); } 
		static public string getProtoName() { return "JoinGropuAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.ui8 chlType; //channel type 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(chlType.__encode()); 
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
			return (int)offset.val; 
		} 
	} 
 
	class LeaveGropuReq: Proto4z.IProtoObject //加入频道 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1102); } 
		static public string getProtoName() { return "LeaveGropuReq"; } 
		public Proto4z.ui8 chlType; //channel type 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 1; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(chlType.__encode()); 
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
			return (int)offset.val; 
		} 
	} 
 
	class LeaveGropuAck: Proto4z.IProtoObject 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1103); } 
		static public string getProtoName() { return "LeaveGropuAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.ui8 chlType; //channel type 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(chlType.__encode()); 
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
			return (int)offset.val; 
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
 
	class ChatReq: Proto4z.IProtoObject //发送聊天请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1104); } 
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
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1105); } 
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
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1106); } 
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
 
 
