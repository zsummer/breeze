 
namespace Proto4z  
{ 
 
	class C2LS_LoginReq: Proto4z.IProtoObject //登录请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(102); } 
		static public string getProtoName() { return "C2LS_LoginReq"; } 
		public Proto4z.String user;  
		public Proto4z.String passwd;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(user.__encode()); 
			data.AddRange(passwd.__encode()); 
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
			user = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				user.__decode(binData, ref pos); 
			} 
			passwd = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				passwd.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class LS2C_LoginAck: Proto4z.IProtoObject //登录结果 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(103); } 
		static public string getProtoName() { return "LS2C_LoginAck"; } 
		public Proto4z.i32 retCode;  
		public Proto4z.i32 needCreateUser;  
		public Proto4z.UserInfo info; //用户信息 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 7; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(needCreateUser.__encode()); 
			data.AddRange(info.__encode()); 
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
			retCode = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				retCode.__decode(binData, ref pos); 
			} 
			needCreateUser = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				needCreateUser.__decode(binData, ref pos); 
			} 
			info = new Proto4z.UserInfo(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				info.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class C2LS_CreateUserReq: Proto4z.IProtoObject //填写用户信息 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(108); } 
		static public string getProtoName() { return "C2LS_CreateUserReq"; } 
		public Proto4z.String nickName; //昵称 
		public Proto4z.i32 iconID; //头像 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(nickName.__encode()); 
			data.AddRange(iconID.__encode()); 
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
			nickName = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				nickName.__decode(binData, ref pos); 
			} 
			iconID = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				iconID.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class LS2C_CreateUserAck: Proto4z.IProtoObject //返回 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(109); } 
		static public string getProtoName() { return "LS2C_CreateUserAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.i32 needCreateUser; //nickname冲突需要重新创建 
		public Proto4z.UserInfo info;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 7; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(needCreateUser.__encode()); 
			data.AddRange(info.__encode()); 
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
			needCreateUser = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				needCreateUser.__decode(binData, ref pos); 
			} 
			info = new Proto4z.UserInfo(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				info.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class X2X_ServerPulse: Proto4z.IProtoObject //服务端存活脉冲 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(111); } 
		static public string getProtoName() { return "X2X_ServerPulse"; } 
		public Proto4z.ui32 timeStamp; //服务器当前UTC时间戳 
		public Proto4z.ui32 timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(timeStamp.__encode()); 
			data.AddRange(timeTick.__encode()); 
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
			timeStamp = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				timeStamp.__decode(binData, ref pos); 
			} 
			timeTick = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				timeTick.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
} 
 
 
