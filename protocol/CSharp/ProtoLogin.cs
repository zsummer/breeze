 
namespace Proto4z  
{ 
 
	class PlatAuthReq: Proto4z.IProtoObject //平台认证 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(100); } 
		static public string getProtoName() { return "PlatAuthReq"; } 
		public Proto4z.String account; //用户名 
		public Proto4z.String token; //令牌 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(account.__encode()); 
			data.AddRange(token.__encode()); 
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
			account = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				account.__decode(binData, ref pos); 
			} 
			token = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				token.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class PlatAuthAck: Proto4z.IProtoObject //认证结果, 包含该用户的所有用户/角色数据 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(101); } 
		static public string getProtoName() { return "PlatAuthAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.UserInfoArray users; //该帐号下的所有用户信息 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(users.__encode()); 
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
			users = new Proto4z.UserInfoArray(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				users.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class CreateUserReq: Proto4z.IProtoObject //创建一个新的用户数据 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(102); } 
		static public string getProtoName() { return "CreateUserReq"; } 
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
 
	class CreateUserAck: Proto4z.IProtoObject //创建结果和所有用户数据 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(103); } 
		static public string getProtoName() { return "CreateUserAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.UserInfoArray users; //该帐号下的所有用户信息 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(users.__encode()); 
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
			users = new Proto4z.UserInfoArray(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				users.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class SelectUserReq: Proto4z.IProtoObject //获取需要登录用户的所在服务器和认证令牌 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(104); } 
		static public string getProtoName() { return "SelectUserReq"; } 
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
 
	class SelectUserAck: Proto4z.IProtoObject //获取需要登录用户的所在服务器和认证令牌 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(105); } 
		static public string getProtoName() { return "SelectUserAck"; } 
		public Proto4z.ui16 retCode;  
		public Proto4z.ui64 uID;  
		public Proto4z.String token;  
		public Proto4z.String ip;  
		public Proto4z.ui16 port;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 31; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
			data.AddRange(uID.__encode()); 
			data.AddRange(token.__encode()); 
			data.AddRange(ip.__encode()); 
			data.AddRange(port.__encode()); 
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
			uID = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				uID.__decode(binData, ref pos); 
			} 
			token = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				token.__decode(binData, ref pos); 
			} 
			ip = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				ip.__decode(binData, ref pos); 
			} 
			port = new Proto4z.ui16(); 
			if ((tag.val & ((System.UInt64)1 << 4)) != 0) 
			{ 
				port.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class LoginReq: Proto4z.IProtoObject //登录请求 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(106); } 
		static public string getProtoName() { return "LoginReq"; } 
		public Proto4z.ui64 uID;  
		public Proto4z.String token;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 3; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uID.__encode()); 
			data.AddRange(token.__encode()); 
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
			token = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				token.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class LoginAck: Proto4z.IProtoObject //登录结果 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(107); } 
		static public string getProtoName() { return "LoginAck"; } 
		public Proto4z.ui16 retCode;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 1; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(retCode.__encode()); 
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
			return (int)offset.val; 
		} 
	} 
 
} 
 
 
