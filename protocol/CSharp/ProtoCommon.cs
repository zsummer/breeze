 
namespace Proto4z  
{ 
	class STATIC_BEC_SUCCESS //成功 
	{ 
		public static Proto4z.ui16 value = 0;  
	} 
	class STATIC_BEC_UNKOWN_ERROR //未知错误 
	{ 
		public static Proto4z.ui16 value = 1;  
	} 
	class STATIC_BEC_INNER_ERROR //内部错误 
	{ 
		public static Proto4z.ui16 value = 2;  
	} 
	class STATIC_BEC_DB_ERROR //数据库错误 
	{ 
		public static Proto4z.ui16 value = 3;  
	} 
	class STATIC_BEC_PARAM_DENIED //非法参数 
	{ 
		public static Proto4z.ui16 value = 4;  
	} 
	class STATIC_BEC_PERMISSION_DENIED //权限非法 
	{ 
		public static Proto4z.ui16 value = 5;  
	} 
	class STATIC_BEC_SYSTEM_ERROR //系统错误 
	{ 
		public static Proto4z.ui16 value = 6;  
	} 
	class STATIC_BEC_INVALIDE_USERID //用户ID无效 
	{ 
		public static Proto4z.ui16 value = 50;  
	} 
	class STATIC_BEC_AUTH_USER_NOT_EXIST //认证错误:用户不存在 
	{ 
		public static Proto4z.ui16 value = 60;  
	} 
	class STATIC_BEC_AUTH_PASSWD_INCORRECT //认证错误:密码错误 
	{ 
		public static Proto4z.ui16 value = 61;  
	} 
	class STATIC_BEC_AUTH_ACCOUNT_INCORRECT //认证错误:角色名冲突(创建角色) 
	{ 
		public static Proto4z.ui16 value = 62;  
	} 
	class STATIC_BEC_AUTH_ING //认证错误:正在认证中... 
	{ 
		public static Proto4z.ui16 value = 63;  
	} 
	class STATIC_BEC_AUTH_AREADY_AUTH //认证错误:已认证 
	{ 
		public static Proto4z.ui16 value = 64;  
	} 
	class STATIC_BEC_AUTH_LIMITE_COUNT //认证错误:认证次数超过限制 
	{ 
		public static Proto4z.ui16 value = 65;  
	} 
 
	class UserInfo: Proto4z.IProtoObject //用户信息 
	{	 
		public Proto4z.ui64 uid;  
		public Proto4z.String nickName; //用户昵称 
		public Proto4z.i16 iconID; //头像 
		public Proto4z.i32 diamond; //当前剩余的充值钻石 
		public Proto4z.i32 hisotryDiamond; //历史充值钻石总额 
		public Proto4z.i32 giftDiamond; //当前剩余的赠送钻石 
		public Proto4z.ui32 joinTime; //加入时间 
		public System.Collections.Generic.List<byte> __encode() 
		{ 
			Proto4z.ui32 sttLen = 0; 
			Proto4z.ui64 tag = 127; 
			 
			var data = new System.Collections.Generic.List<byte>(); 
			data.AddRange(uid.__encode()); 
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
			uid = new Proto4z.ui64(); 
			if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
			{ 
				uid.__decode(binData, ref pos); 
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
			diamond = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
			{ 
				diamond.__decode(binData, ref pos); 
			} 
			hisotryDiamond = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 4)) != 0) 
			{ 
				hisotryDiamond.__decode(binData, ref pos); 
			} 
			giftDiamond = new Proto4z.i32(); 
			if ((tag.val & ((System.UInt64)1 << 5)) != 0) 
			{ 
				giftDiamond.__decode(binData, ref pos); 
			} 
			joinTime = new Proto4z.ui32(); 
			if ((tag.val & ((System.UInt64)1 << 6)) != 0) 
			{ 
				joinTime.__decode(binData, ref pos); 
			} 
			return (int)offset.val; 
		} 
	} 
 
	class UserInfoVct : System.Collections.Generic.List<Proto4z.UserInfo>, Proto4z.IProtoObject  
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
					var data = new Proto4z.UserInfo(); 
					 data.__decode(binData, ref pos); 
					this.Add(data); 
				} 
			} 
			return pos; 
		} 
	} 
 
	class UserIDVct : System.Collections.Generic.List<Proto4z.ui64>, Proto4z.IProtoObject  
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
 
} 
 
 
