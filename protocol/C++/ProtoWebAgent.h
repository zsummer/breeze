 
#ifndef _PROTOWEBAGENT_H_ 
#define _PROTOWEBAGENT_H_ 
 
 
 
typedef std::map<std::string, std::string> WebAgentHead;  
 
struct WebAgentToService 
{ 
    static const unsigned short getProtoID() { return 3000;} 
    static const std::string getProtoName() { return "WebAgentToService";} 
    unsigned int webClientID;  
    std::string method;  
    std::string methodLine;  
    WebAgentHead heads;  
    std::string body;  
    WebAgentToService() 
    { 
        webClientID = 0; 
    } 
    WebAgentToService(const unsigned int & webClientID, const std::string & method, const std::string & methodLine, const WebAgentHead & heads, const std::string & body) 
    { 
        this->webClientID = webClientID; 
        this->method = method; 
        this->methodLine = methodLine; 
        this->heads = heads; 
        this->body = body; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebAgentToService & data) 
{ 
    ws << data.webClientID;  
    ws << data.method;  
    ws << data.methodLine;  
    ws << data.heads;  
    ws << data.body;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebAgentToService & data) 
{ 
    rs >> data.webClientID;  
    rs >> data.method;  
    rs >> data.methodLine;  
    rs >> data.heads;  
    rs >> data.body;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebAgentToService & info) 
{ 
    stm << "[\n"; 
    stm << "webClientID=" << info.webClientID << "\n"; 
    stm << "method=" << info.method << "\n"; 
    stm << "methodLine=" << info.methodLine << "\n"; 
    stm << "heads=" << info.heads << "\n"; 
    stm << "body=" << info.body << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WebAgentToClient 
{ 
    static const unsigned short getProtoID() { return 3001;} 
    static const std::string getProtoName() { return "WebAgentToClient";} 
    std::string method;  
    std::string methodLine;  
    WebAgentHead heads;  
    std::string body;  
    WebAgentToClient() 
    { 
    } 
    WebAgentToClient(const std::string & method, const std::string & methodLine, const WebAgentHead & heads, const std::string & body) 
    { 
        this->method = method; 
        this->methodLine = methodLine; 
        this->heads = heads; 
        this->body = body; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebAgentToClient & data) 
{ 
    ws << data.method;  
    ws << data.methodLine;  
    ws << data.heads;  
    ws << data.body;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebAgentToClient & data) 
{ 
    rs >> data.method;  
    rs >> data.methodLine;  
    rs >> data.heads;  
    rs >> data.body;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebAgentToClient & info) 
{ 
    stm << "[\n"; 
    stm << "method=" << info.method << "\n"; 
    stm << "methodLine=" << info.methodLine << "\n"; 
    stm << "heads=" << info.heads << "\n"; 
    stm << "body=" << info.body << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
