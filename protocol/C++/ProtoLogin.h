 
 #ifndef _PROTOLOGIN_H_ 
 #define _PROTOLOGIN_H_ 
  
  
 const unsigned short ID_C2LS_CreateCharacterReq = 20200; //创建角色 
 struct C2LS_CreateCharacterReq //创建角色 
 { 
 	std::string charName; //昵称 
 	inline unsigned short GetProtoID() { return 20200;} 
 	inline std::string GetProtoName() { return "ID_C2LS_CreateCharacterReq";} 
 }; 
 template<class T> 
 T & operator << (T & t, const C2LS_CreateCharacterReq & data) 
 { 
 	t << data.charName; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, C2LS_CreateCharacterReq & data) 
 { 
 	t >> data.charName; 
 	return t; 
 } 
  
 const unsigned short ID_LS2C_CreateCharacterAck = 20201; //创建角色应答 
 struct LS2C_CreateCharacterAck //创建角色应答 
 { 
 	unsigned short retCode;  
 	LittleCharInfo lci;  
 	LS2C_CreateCharacterAck() 
 	{ 
 		retCode = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 20201;} 
 	inline std::string GetProtoName() { return "ID_LS2C_CreateCharacterAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const LS2C_CreateCharacterAck & data) 
 { 
 	t << data.retCode; 
 	t << data.lci; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, LS2C_CreateCharacterAck & data) 
 { 
 	t >> data.retCode; 
 	t >> data.lci; 
 	return t; 
 } 
  
 const unsigned short ID_C2LS_CharacterLoginReq = 20202; //角色登录 
 struct C2LS_CharacterLoginReq //角色登录 
 { 
 	unsigned long long charID; //要登录的角色ID 
 	C2LS_CharacterLoginReq() 
 	{ 
 		charID = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 20202;} 
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
  
 const unsigned short ID_LS2C_CharacterLoginAck = 20203; //角色登录应答 
 struct LS2C_CharacterLoginAck //角色登录应答 
 { 
 	unsigned short retCode;  
 	CharacterInfo info; //角色信息 
 	LS2C_CharacterLoginAck() 
 	{ 
 		retCode = 0; 
 	} 
 	inline unsigned short GetProtoID() { return 20203;} 
 	inline std::string GetProtoName() { return "ID_LS2C_CharacterLoginAck";} 
 }; 
 template<class T> 
 T & operator << (T & t, const LS2C_CharacterLoginAck & data) 
 { 
 	t << data.retCode; 
 	t << data.info; 
 	return t; 
 } 
 template<class T> 
 T & operator >> (T & t, LS2C_CharacterLoginAck & data) 
 { 
 	t >> data.retCode; 
 	t >> data.info; 
 	return t; 
 } 
  
 #endif 
 