 
#ifndef _PROTOWEBAGENT_H_ 
#define _PROTOWEBAGENT_H_ 
 
 
 
typedef std::map<std::string, std::string> WebAgentHead;  
 
struct WebAgentClientRequestAPI 
{ 
    static const unsigned short getProtoID() { return 5105;} 
    static const std::string getProtoName() { return "WebAgentClientRequestAPI";} 
    unsigned int webClientID;  
    std::string method;  
    std::string methodLine;  
    WebAgentHead heads;  
    std::string body;  
    WebAgentClientRequestAPI() 
    { 
        webClientID = 0; 
    } 
    WebAgentClientRequestAPI(const unsigned int & webClientID, const std::string & method, const std::string & methodLine, const WebAgentHead & heads, const std::string & body) 
    { 
        this->webClientID = webClientID; 
        this->method = method; 
        this->methodLine = methodLine; 
        this->heads = heads; 
        this->body = body; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebAgentClientRequestAPI & data) 
{ 
    ws << data.webClientID;  
    ws << data.method;  
    ws << data.methodLine;  
    ws << data.heads;  
    ws << data.body;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebAgentClientRequestAPI & data) 
{ 
    rs >> data.webClientID;  
    rs >> data.method;  
    rs >> data.methodLine;  
    rs >> data.heads;  
    rs >> data.body;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebAgentClientRequestAPI & info) 
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
 
struct WebServerRequest 
{ 
    static const unsigned short getProtoID() { return 5106;} 
    static const std::string getProtoName() { return "WebServerRequest";} 
    unsigned int fromServiceType;  
    unsigned long long fromServiceID;  
    unsigned int traceID;  
    std::string ip;  
    unsigned short port;  
    std::string host;  
    std::string uri;  
    std::string params;  
    WebAgentHead heads;  
    unsigned char isGet; //get or post  
    WebServerRequest() 
    { 
        fromServiceType = 0; 
        fromServiceID = 0; 
        traceID = 0; 
        port = 0; 
        isGet = 0; 
    } 
    WebServerRequest(const unsigned int & fromServiceType, const unsigned long long & fromServiceID, const unsigned int & traceID, const std::string & ip, const unsigned short & port, const std::string & host, const std::string & uri, const std::string & params, const WebAgentHead & heads, const unsigned char & isGet) 
    { 
        this->fromServiceType = fromServiceType; 
        this->fromServiceID = fromServiceID; 
        this->traceID = traceID; 
        this->ip = ip; 
        this->port = port; 
        this->host = host; 
        this->uri = uri; 
        this->params = params; 
        this->heads = heads; 
        this->isGet = isGet; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebServerRequest & data) 
{ 
    ws << data.fromServiceType;  
    ws << data.fromServiceID;  
    ws << data.traceID;  
    ws << data.ip;  
    ws << data.port;  
    ws << data.host;  
    ws << data.uri;  
    ws << data.params;  
    ws << data.heads;  
    ws << data.isGet;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebServerRequest & data) 
{ 
    rs >> data.fromServiceType;  
    rs >> data.fromServiceID;  
    rs >> data.traceID;  
    rs >> data.ip;  
    rs >> data.port;  
    rs >> data.host;  
    rs >> data.uri;  
    rs >> data.params;  
    rs >> data.heads;  
    rs >> data.isGet;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebServerRequest & info) 
{ 
    stm << "[\n"; 
    stm << "fromServiceType=" << info.fromServiceType << "\n"; 
    stm << "fromServiceID=" << info.fromServiceID << "\n"; 
    stm << "traceID=" << info.traceID << "\n"; 
    stm << "ip=" << info.ip << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "uri=" << info.uri << "\n"; 
    stm << "params=" << info.params << "\n"; 
    stm << "heads=" << info.heads << "\n"; 
    stm << "isGet=" << info.isGet << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct WebServerResponse 
{ 
    static const unsigned short getProtoID() { return 5107;} 
    static const std::string getProtoName() { return "WebServerResponse";} 
    std::string method;  
    std::string methodLine;  
    WebAgentHead heads;  
    std::string body;  
    WebServerResponse() 
    { 
    } 
    WebServerResponse(const std::string & method, const std::string & methodLine, const WebAgentHead & heads, const std::string & body) 
    { 
        this->method = method; 
        this->methodLine = methodLine; 
        this->heads = heads; 
        this->body = body; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const WebServerResponse & data) 
{ 
    ws << data.method;  
    ws << data.methodLine;  
    ws << data.heads;  
    ws << data.body;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, WebServerResponse & data) 
{ 
    rs >> data.method;  
    rs >> data.methodLine;  
    rs >> data.heads;  
    rs >> data.body;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const WebServerResponse & info) 
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
