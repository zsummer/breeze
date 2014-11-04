 
 #ifndef _PROTOLOGIN_H_ 
 #define _PROTOLOGIN_H_ 
  
  
 const unsigned short ID_C2LS_CharacterCreateReq = 104; //创建角色 
 struct C2LS_CharacterCreateReq //创建角色 
 { 
 	std::string charName; //昵称 
 	inline unsigned short GetProtoID() { return 104;} 
 	inline std::string GetProtoName() { return "ID_C2LS_CharacterCreateReq";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2LS_CharacterCreateReq & data) 
 { 
 	t << data.charName; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2LS_CharacterCreateReq & data) 
 { 
 	t >> data.charName; 
 	return t; 
 } 
  
 const unsigned short ID_LS2C_CharacterCreateAck = 105; //创建角色应答 
 struct LS2C_CharacterCreateAck //创建角色应答 
 { 
 	unsigned short retCode;  
 	CharacterInfo info;  
 	LS2C_CharacterCreateAck() 
 	{ 
 		retCode = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 105;} 
 	inline std::string GetProtoName() { return "ID_LS2C_CharacterCreateAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const LS2C_CharacterCreateAck & data) 
 { 
 	t << data.retCode; 
 	t << data.info; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, LS2C_CharacterCreateAck & data) 
 { 
 	t >> data.retCode; 
 	t >> data.info; 
 	return t; 
 } 
  
 const unsigned short ID_C2LS_CharacterLoginReq = 102; //角色登录 
 struct C2LS_CharacterLoginReq //角色登录 
 { 
 	unsigned long long charID; //要登录的角色ID 
 	C2LS_CharacterLoginReq() 
 	{ 
 		charID = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 102;} 
 	inline std::string GetProtoName() { return "ID_C2LS_CharacterLoginReq";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2LS_CharacterLoginReq & data) 
 { 
 	t << data.charID; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2LS_CharacterLoginReq & data) 
 { 
 	t >> data.charID; 
 	return t; 
 } 
  
 const unsigned short ID_LS2C_CharacterLoginAck = 103; //角色登录应答 
 struct LS2C_CharacterLoginAck //角色登录应答 
 { 
 	unsigned short retCode;  
 	LS2C_CharacterLoginAck() 
 	{ 
 		retCode = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 103;} 
 	inline std::string GetProtoName() { return "ID_LS2C_CharacterLoginAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const LS2C_CharacterLoginAck & data) 
 { 
 	t << data.retCode; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, LS2C_CharacterLoginAck & data) 
 { 
 	t >> data.retCode; 
 	return t; 
 } 
  
 #endif 
 