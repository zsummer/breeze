 
 #ifndef _PROTOAUTH_H_ 
 #define _PROTOAUTH_H_ 
  
  
 const unsigned short ID_C2AS_AuthReq = 0; //认证请求 
 struct C2AS_AuthReq //认证请求 
 { 
 	std::string user;  
 	std::string pwd;  
 	inline unsigned short GetProtoID() { return 0;} 
 	inline std::string GetProtoName() { return "ID_C2AS_AuthReq";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2AS_AuthReq & data) 
 { 
 	t << data.user; 
 	t << data.pwd; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2AS_AuthReq & data) 
 { 
 	t >> data.user; 
 	t >> data.pwd; 
 	return t; 
 } 
  
 const unsigned short ID_AS2C_AuthAck = 1; //认证回复 
 struct AS2C_AuthAck //认证回复 
 { 
 	int retCode;  
 	AccountInfo info;  
 	inline unsigned short GetProtoID() { return 1;} 
 	inline std::string GetProtoName() { return "ID_AS2C_AuthAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const AS2C_AuthAck & data) 
 { 
 	t << data.retCode; 
 	t << data.info; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, AS2C_AuthAck & data) 
 { 
 	t >> data.retCode; 
 	t >> data.info; 
 	return t; 
 } 
  
 const unsigned short ID_C2AS_ClientPulse = 2; //客户端存活脉冲 
 struct C2AS_ClientPulse //客户端存活脉冲 
 { 
 	inline unsigned short GetProtoID() { return 2;} 
 	inline std::string GetProtoName() { return "ID_C2AS_ClientPulse";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2AS_ClientPulse & data) 
 { 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2AS_ClientPulse & data) 
 { 
 	return t; 
 } 
  
 const unsigned short ID_AS2C_ClientPulseAck = 3; //客户端存活脉冲应答 
 struct AS2C_ClientPulseAck //客户端存活脉冲应答 
 { 
 	unsigned long long svrTimeStamp; //服务器当前UTC时间戳 
 	AS2C_ClientPulseAck() 
 	{ 
 		svrTimeStamp = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 3;} 
 	inline std::string GetProtoName() { return "ID_AS2C_ClientPulseAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const AS2C_ClientPulseAck & data) 
 { 
 	t << data.svrTimeStamp; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, AS2C_ClientPulseAck & data) 
 { 
 	t >> data.svrTimeStamp; 
 	return t; 
 } 
  
 #endif 
 