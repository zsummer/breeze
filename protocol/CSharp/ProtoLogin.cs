 
 namespace Proto4z  
 { 
  
 	class C2LS_LoginReq: Proto4z.IProtoObject //登录请求 
 	{	 
 		 public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(102); } 
 		  public string getProtoName() { return "C2LS_LoginReq"; } 
 		public Proto4z.String user;  
 		public Proto4z.String passwd;  
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			ret.AddRange(user.__encode()); 
 			ret.AddRange(passwd.__encode()); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			user = new Proto4z.String(); 
 			user.__decode(binData, ref pos); 
 			passwd = new Proto4z.String(); 
 			passwd.__decode(binData, ref pos); 
 			return pos; 
 		} 
 	} 
  
 	class LS2C_LoginAck: Proto4z.IProtoObject //登录结果 
 	{	 
 		 public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(103); } 
 		  public string getProtoName() { return "LS2C_LoginAck"; } 
 		public Proto4z.i32 retCode;  
 		public Proto4z.i32 needCreateUser;  
 		public Proto4z.UserInfo info; //认证成功但昵称为空 则说明需要创建用户信息 
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			ret.AddRange(retCode.__encode()); 
 			ret.AddRange(needCreateUser.__encode()); 
 			ret.AddRange(info.__encode()); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			retCode = new Proto4z.i32(); 
 			retCode.__decode(binData, ref pos); 
 			needCreateUser = new Proto4z.i32(); 
 			needCreateUser.__decode(binData, ref pos); 
 			info = new Proto4z.UserInfo(); 
 			info.__decode(binData, ref pos); 
 			return pos; 
 		} 
 	} 
  
 	class C2LS_CreateUserReq: Proto4z.IProtoObject //填写用户信息 
 	{	 
 		 public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(108); } 
 		  public string getProtoName() { return "C2LS_CreateUserReq"; } 
 		public Proto4z.String nickName; //昵称 
 		public Proto4z.i32 iconID; //头像 
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			ret.AddRange(nickName.__encode()); 
 			ret.AddRange(iconID.__encode()); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			nickName = new Proto4z.String(); 
 			nickName.__decode(binData, ref pos); 
 			iconID = new Proto4z.i32(); 
 			iconID.__decode(binData, ref pos); 
 			return pos; 
 		} 
 	} 
  
 	class LS2C_CreateUserAck: Proto4z.IProtoObject //返回 
 	{	 
 		 public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(109); } 
 		  public string getProtoName() { return "LS2C_CreateUserAck"; } 
 		public Proto4z.ui16 retCode;  
 		public Proto4z.i32 needCreateUser; //nickname冲突需要重新创建 
 		public Proto4z.UserInfo info;  
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			ret.AddRange(retCode.__encode()); 
 			ret.AddRange(needCreateUser.__encode()); 
 			ret.AddRange(info.__encode()); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			retCode = new Proto4z.ui16(); 
 			retCode.__decode(binData, ref pos); 
 			needCreateUser = new Proto4z.i32(); 
 			needCreateUser.__decode(binData, ref pos); 
 			info = new Proto4z.UserInfo(); 
 			info.__decode(binData, ref pos); 
 			return pos; 
 		} 
 	} 
  
 	class C2AS_ClientPulse: Proto4z.IProtoObject //客户端存活脉冲 
 	{	 
 		 public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(106); } 
 		  public string getProtoName() { return "C2AS_ClientPulse"; } 
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			return pos; 
 		} 
 	} 
  
 	class AS2C_ServerPulse: Proto4z.IProtoObject //服务端存活脉冲 
 	{	 
 		 public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(107); } 
 		  public string getProtoName() { return "AS2C_ServerPulse"; } 
 		public Proto4z.ui32 timeStamp; //服务器当前UTC时间戳 
 		public Proto4z.ui32 timeTick; //服务器当前tick时间戳 毫秒, 服务启动时刻为0 
 		public System.Collections.Generic.List<byte> __encode() 
 		{ 
 			var ret = new System.Collections.Generic.List<byte>(); 
 			ret.AddRange(timeStamp.__encode()); 
 			ret.AddRange(timeTick.__encode()); 
 			return ret; 
 		} 
 		public int __decode(byte[] binData, ref int pos) 
 		{ 
 			timeStamp = new Proto4z.ui32(); 
 			timeStamp.__decode(binData, ref pos); 
 			timeTick = new Proto4z.ui32(); 
 			timeTick.__decode(binData, ref pos); 
 			return pos; 
 		} 
 	} 
  
 } 
  
  
 