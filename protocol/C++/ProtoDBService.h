 
#ifndef _PROTODBSERVICE_H_ 
#define _PROTODBSERVICE_H_ 
 
 
 
typedef std::vector<std::string> SQLFieldArray;  
 
struct SQLResult 
{ 
    static const unsigned short getProtoID() { return 41000;} 
    static const std::string getProtoName() { return "SQLResult";} 
    unsigned short qc;  
    std::string errMsg;  
    std::string sql;  
    unsigned long long affected;  
    SQLFieldArray fields;  
    SQLResult() 
    { 
        qc = 0; 
        affected = 0; 
    } 
    SQLResult(const unsigned short & qc, const std::string & errMsg, const std::string & sql, const unsigned long long & affected, const SQLFieldArray & fields) 
    { 
        this->qc = qc; 
        this->errMsg = errMsg; 
        this->sql = sql; 
        this->affected = affected; 
        this->fields = fields; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SQLResult & data) 
{ 
    ws << data.qc;  
    ws << data.errMsg;  
    ws << data.sql;  
    ws << data.affected;  
    ws << data.fields;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SQLResult & data) 
{ 
    rs >> data.qc;  
    rs >> data.errMsg;  
    rs >> data.sql;  
    rs >> data.affected;  
    rs >> data.fields;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SQLResult & info) 
{ 
    stm << "[\n"; 
    stm << "qc=" << info.qc << "\n"; 
    stm << "errMsg=" << info.errMsg << "\n"; 
    stm << "sql=" << info.sql << "\n"; 
    stm << "affected=" << info.affected << "\n"; 
    stm << "fields=" << info.fields << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SQLQueryReq 
{ 
    static const unsigned short getProtoID() { return 41001;} 
    static const std::string getProtoName() { return "SQLQueryReq";} 
    std::string sql;  
    SQLQueryReq() 
    { 
    } 
    SQLQueryReq(const std::string & sql) 
    { 
        this->sql = sql; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SQLQueryReq & data) 
{ 
    ws << data.sql;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SQLQueryReq & data) 
{ 
    rs >> data.sql;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SQLQueryReq & info) 
{ 
    stm << "[\n"; 
    stm << "sql=" << info.sql << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SQLQueryResp 
{ 
    static const unsigned short getProtoID() { return 41002;} 
    static const std::string getProtoName() { return "SQLQueryResp";} 
    unsigned short retCode;  
    SQLResult result;  
    SQLQueryResp() 
    { 
        retCode = 0; 
    } 
    SQLQueryResp(const unsigned short & retCode, const SQLResult & result) 
    { 
        this->retCode = retCode; 
        this->result = result; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SQLQueryResp & data) 
{ 
    ws << data.retCode;  
    ws << data.result;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SQLQueryResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.result;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SQLQueryResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "result=" << info.result << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
