 
 #ifndef _PROTOAUTH_H_ 
 #define _PROTOAUTH_H_ 
  
  
 const unsigned short ID_C2AS_AuthReq = 20000; //认证请求 
 struct C2AS_AuthReq //认证请求 
 { 
 	std::string user;  
 	std::string pwd;  
 	inline unsigned short GetProtoID() { return 20000;} 
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
  
 const unsigned short ID_AS2C_AuthAck = 20001; //认证回复 
 struct AS2C_AuthAck //认证回复 
 { 
 	int retCode;  
 	AccountInfo info;  
 	inline unsigned short GetProtoID() { return 20001;} 
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
  
 const unsigned short ID_C2AS_ClientPulse = 20002; //客户端存活脉冲 
 struct C2AS_ClientPulse //客户端存活脉冲 
 { 
 	inline unsigned short GetProtoID() { return 20002;} 
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
  
 const unsigned short ID_AS2C_ClientPulseAck = 20003; //客户端存活脉冲应答 
 struct AS2C_ClientPulseAck //客户端存活脉冲应答 
 { 
 	unsigned long long svrTimeStamp; //服务器当前UTC时间戳 
 	AS2C_ClientPulseAck() 
 	{ 
 		svrTimeStamp = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 20003;} 
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
 