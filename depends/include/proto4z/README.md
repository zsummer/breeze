Welcome to the proto4z wiki!  
# Introduction:    

proto4z  is an efficient serialization library for C++ and lua, and will support C# in the near future , It's like Google protocol buffers, but much faster.  

The design is simple. It can be easily integrate to the C++ servers, or  quick-cocos2dx.  

#example  
  
##lua code  
_-- make a struct. genProto tools generate _  
  
`Protoz.AuthInfo = {}`  
`Protoz.AuthInfo.__getName = "AuthInfo" `  
`Protoz.AuthInfo[1] = {name="user", type="string"}  `  
`Protoz.AuthInfo[2] = {name="pwd", type="string"}  `  
`Protoz.AuthInfo[3] = {name="accID", type="ui32"} `    
`  `  
  
_-- make a protocol pack desc.  genProto tools generate _  
`  `  
`Protoz.register(30000,"XS2OS_ServerInitNotify")Protoz.XS2OS_ServerInitNotify = {} `  
`Protoz.XS2OS_ServerInitNotify.__getID = 30000 `  
`Protoz.XS2OS_ServerInitNotify.__getName = "XS2OS_ServerInitNotify" `  
`Protoz.XS2OS_ServerInitNotify[1] = {name="serverID", type="i16"}  `  
`Protoz.XS2OS_ServerInitNotify[2] = {name="info", type="AuthInfo"}  `  
`  `  
  
_--fill data _   
`local notify = {serverID = 100, info = {user="user", pwd="pwd", accID=200}}`  
  
_--encode protocol to a binary data_  
`local data = Protoz.encode(notify, "XS2OS_ServerInitNotify")`  
  
_--decode protocol from a binary data_  
`local dr = Protoz.decode(data, "XS2OS_ServerInitNotify")`  
  
_-- show binary data _  
`Protoz.putbin(data)`  
  
_--show decoded data_  
`Protoz.dump(dr)`  
`  `  
## lua output  
`[len:17]64 00 04 00 75 73 65 72 03 00 70 77 64 c8 00 00 00`  
`dump from: main.lua:101: in main chunk`  
`- "<var>" = {`  
`-     "info" = {`  
`-         "accID" = 200`  
`-         "pwd"   = "pwd"`  
`-         "user"  = "user"`  
`-     }`  
`-     "serverID" = 100`  
`- }`  
  
##c++ code  
  
_//make a struct. genProto tools generate _   
`struct AuthInfo  `  
` { `  
` 	std::string user;  `  
` 	std::string pwd;  `  
` 	unsigned int accID; `  
` 	AuthInfo() `  
` 	{ `  
`		accID = 0; `  
` 	} `  
` }; `  
` template<class T> `  
` T & operator << (T & t, const AuthInfo & data) `  
` { `  
` 	t << data.user; `  
` 	t << data.pwd; `  
` 	t << data.accID; `  
` 	return t; `  
` } `  
` template<class T> `  
` T & operator >> (T & t, AuthInfo & data) `  
` { `  
` 	t >> data.user; `  
` 	t >> data.pwd; `  
` 	t >> data.accID; `  
` 	return t; `  
` } `  

  
_//make a proto pack. genProto tools generate _  
`const unsigned short ID_XS2OS_ServerInitNotify = 30000; `  
` struct XS2OS_ServerInitNotify `  
` { `  
` 	short serverID;  `  
` 	AuthInfo info;  `  
` 	XS2OS_ServerInitNotify() `  
` 	{ `  
` 		serverID = 0; `  
` 	} `  
` 	inline unsigned short GetProtoID() { return 30000;} `  
` 	inline std::string GetProtoName() { return "ID_XS2OS_ServerInitNotify";} `  
` }; `  
` template<class T> `  
` T & operator << (T & t, const XS2OS_ServerInitNotify & data) `  
` { `  
` 	t << data.serverID; `  
` 	t << data.info; `  
` 	return t; `  
` } `  
` template<class T> `  
` T & operator >> (T & t, XS2OS_ServerInitNotify & data) `  
` { `  
`       t >> data.serverID; `  
` 	t >> data.info; `  
` 	return t; `  
` } `  
`  `  
  
  
_//  used to encode/decode _  
`	XS2OS_ServerInitNotify notify;`  
`	notify.serverID = 100;`  
`	notify.info.user = "node1";`  
`	notify.info.pwd = "passwd";`  
`	notify.info.accID = 100;`  
`	zsummer::proto4z::WriteStream<FrameStreamTraits> ws(ID_XS2OS_ServerInitNotify);`  
`	ws << notify;`  
`  `  
`  `  
`	zsummer::proto4z::ReadStream<FrameStreamTraits> rs(ws.getStreamBody(), ws.getStreamBodyLen());`  
`	XS2OS_ServerInitNotify msg;`  
`	rs >> msg;`  

#About The Author  
Auther: YaweiZhang  
Mail: yawei_zhang@foxmail.com  
GitHub: https://github.com/zsummer  
