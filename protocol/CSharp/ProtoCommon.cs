 
namespace Proto4z  
{ 
	class STATIC_EC_SUCCESS //成功 
	{ 
		public static Proto4z.ui16 value = 0;  
	} 
	class STATIC_EC_ERROR //错误 
	{ 
		public static Proto4z.ui16 value = 1;  
	} 
	class STATIC_EC_INNER_ERROR //内部错误 
	{ 
		public static Proto4z.ui16 value = 2;  
	} 
	class STATIC_EC_DB_ERROR //数据库错误 
	{ 
		public static Proto4z.ui16 value = 3;  
	} 
	class STATIC_EC_PARAM_DENIED //非法参数 
	{ 
		public static Proto4z.ui16 value = 4;  
	} 
	class STATIC_EC_PERMISSION_DENIED //权限错误 
	{ 
		public static Proto4z.ui16 value = 5;  
	} 
	class STATIC_EC_INVALIDE_USER //错误的用户信息 
	{ 
		public static Proto4z.ui16 value = 50;  
	} 
	class STATIC_EC_TOKEN_EXPIRE //令牌过期 
	{ 
		public static Proto4z.ui16 value = 51;  
	} 
	class STATIC_EC_OWNER_FRIEND //自己的好友 
	{ 
		public static Proto4z.ui16 value = 100;  
	} 
	class STATIC_EC_OWNER_BLACKLIST //自己的黑名单用户 
	{ 
		public static Proto4z.ui16 value = 101;  
	} 
	class STATIC_EC_TARGET_BLACKLIST //对方的黑名单用户 
	{ 
		public static Proto4z.ui16 value = 102;  
	} 
	class STATIC_EC_TARGET_REQUESTING //已在对方的请求列表中 
	{ 
		public static Proto4z.ui16 value = 103;  
	} 
 
	class SessionToken: Proto4z.IProtoObject //认证令牌 
	{	 
		public Proto4z.ui64 uID;  
		public Proto4z.String token;  
		public Proto4z.ui32 tokenExpire;  
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 7; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uID.__encode()); 
			data.AddRange(token.__encode()); 
			data.AddRange(tokenExpire.__encode()); 
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
			tokenExpire = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				tokenExpire.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class UserInfo: Proto4z.IProtoObject //用户信息 
	{	 
		public Proto4z.ui64 uID; //用户唯一ID 
		public Proto4z.String account; //帐号 
		public Proto4z.String nickName; //昵称 
		public Proto4z.i16 iconID; //头像 
		public Proto4z.i32 diamond; //当前剩余的充值钻石 
		public Proto4z.i32 hisotryDiamond; //历史充值钻石总额 
		public Proto4z.i32 giftDiamond; //当前剩余的赠送钻石 
		public Proto4z.ui32 joinTime; //加入时间 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 255; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uID.__encode()); 
			data.AddRange(account.__encode()); 
			data.AddRange(nickName.__encode()); 
			data.AddRange(iconID.__encode()); 
			data.AddRange(diamond.__encode()); 
			data.AddRange(hisotryDiamond.__encode()); 
			data.AddRange(giftDiamond.__encode()); 
			data.AddRange(joinTime.__encode()); 
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
			account = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
			{ 
				account.__decode(binData, ref pos); 
			} 
			nickName = new Proto4z.String(); 
			if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
			{ 
				nickName.__decode(binData, ref pos); 
			} 
			iconID = new Proto4z.i16(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				iconID.__decode(binData, ref pos); 
			} 
			diamond = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 4)) != 0) 
			{ 
				diamond.__decode(binData, ref pos); 
			} 
			hisotryDiamond = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 5)) != 0) 
			{ 
				hisotryDiamond.__decode(binData, ref pos); 
			} 
			giftDiamond = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 6)) != 0) 
			{ 
				giftDiamond.__decode(binData, ref pos); 
			} 
			joinTime = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 7)) != 0) 
			{ 
				joinTime.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class UserInfoArray : System.Collections.Generic.List<UserInfo>, Proto4z.IProtoObject  
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
					var data = new UserInfo(); 
					 data.__decode(binData, ref pos); 
					this.Add(data); 
				} 
			} 
			return pos; 
		} 
	} 
 
	class UserIDArray : System.Collections.Generic.List<Proto4z.ui64>, Proto4z.IProtoObject  
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
					var data = new Proto4z.ui64(); 
					 data.__decode(binData, ref pos); 
					this.Add(data); 
				} 
			} 
			return pos; 
		} 
	} 
	class STATIC_ETRIGGER_USER_LOGIN //用户登录, 用户ID 
	{ 
		public static Proto4z.ui16 value = 0;  
	} 
	class STATIC_ETRIGGER_USER_LOGOUT //用户登出, 用户ID 
	{ 
		public static Proto4z.ui16 value = 1;  
	} 
 
	class Heartbeat: Proto4z.IProtoObject //心跳包 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(200); } 
		static public string getProtoName() { return "Heartbeat"; } 
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
 
	class HeartbeatEcho: Proto4z.IProtoObject //心跳包需要立刻回复 
	{	 
		static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(201); } 
		static public string getProtoName() { return "HeartbeatEcho"; } 
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
 
 
