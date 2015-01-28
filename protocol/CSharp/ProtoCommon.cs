 
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
 	class STATIC_BEC_AUTH_ING //认证错误:正在认证中... 
 	{ 
 		public static Proto4z.ui16 value = 62;  
 	} 
 	class STATIC_BEC_AUTH_AREADY_AUTH //认证错误:已认证 
 	{ 
 		public static Proto4z.ui16 value = 63;  
 	} 
 	class STATIC_BEC_AUTH_LIMITE_COUNT //认证错误:认证次数超过限制 
 	{ 
 		public static Proto4z.ui16 value = 64;  
 	} 
  
 	class UserInfo: Proto4z.IProtoObject //用户信息 
 	{	 
 		public Proto4z.ui64 uid;  
 		public Proto4z.String nickName; //用户昵称 
 		public Proto4z.i32 iconID; //头像 
 		public Proto4z.i32 level; //等级 
 		public Proto4z.i32 diamond; //当前剩余的充值钻石 
 		public Proto4z.i32 hisotryDiamond; //历史充值钻石总额 
 		public Proto4z.i32 giftDiamond; //当前剩余的赠送钻石 
 		public Proto4z.ui32 joinTime; //加入时间 
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			ret.AddRange(uid.__encode()); 
 			ret.AddRange(nickName.__encode()); 
 			ret.AddRange(iconID.__encode()); 
 			ret.AddRange(level.__encode()); 
 			ret.AddRange(diamond.__encode()); 
 			ret.AddRange(hisotryDiamond.__encode()); 
 			ret.AddRange(giftDiamond.__encode()); 
 			ret.AddRange(joinTime.__encode()); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			uid = new Proto4z.ui64(); 
 			uid.__decode(binData, ref pos); 
 			nickName = new Proto4z.String(); 
 			nickName.__decode(binData, ref pos); 
 			iconID = new Proto4z.i32(); 
 			iconID.__decode(binData, ref pos); 
 			level = new Proto4z.i32(); 
 			level.__decode(binData, ref pos); 
 			diamond = new Proto4z.i32(); 
 			diamond.__decode(binData, ref pos); 
 			hisotryDiamond = new Proto4z.i32(); 
 			hisotryDiamond.__decode(binData, ref pos); 
 			giftDiamond = new Proto4z.i32(); 
 			giftDiamond.__decode(binData, ref pos); 
 			joinTime = new Proto4z.ui32(); 
 			joinTime.__decode(binData, ref pos); 
 			return pos; 
 		} 
 	} 
  
 	class UserInfoVct : System.Collections.Generic.List<Proto4z.UserInfo>, Proto4z.IProtoObject  
 	{ 
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			 var len = new Proto4z.ui16((System.UInt16)this.Count); 
 			ret.AddRange(len.__encode()); 
 			for (int i = 0; i < this.Count; i++ ) 
 			{ 
 				ret.AddRange(this[i].__encode()); 
 			} 
 			return ret; 
 		} 
  
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			var len = new Proto4z.ui16(0); 
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
  
 } 
  
  
 