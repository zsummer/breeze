 
#ifndef _PROTODBSERVICE_H_ 
#define _PROTODBSERVICE_H_ 
 
 
 
typedef std::vector<std::string> SQLFieldArray;  
 
struct SQLResult 
{ 
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
 
struct SQLQueryReq 
{ 
    static const unsigned short GetProtoID() { return 41000;} 
    static const std::string GetProtoName() { return "ID_SQLQueryReq";} 
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
 
struct SQLQueryResp 
{ 
    static const unsigned short GetProtoID() { return 41001;} 
    static const std::string GetProtoName() { return "ID_SQLQueryResp";} 
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
 
#endif 
