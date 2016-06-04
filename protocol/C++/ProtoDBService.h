 
#ifndef _PROTODBSERVICE_H_ 
#define _PROTODBSERVICE_H_ 
 
 
 
typedef std::vector<std::string> SQLStringArray;  
 
struct SQLResult 
{ 
    static const unsigned short getProtoID() { return 41000;} 
    static const std::string getProtoName() { return "SQLResult";} 
    unsigned short qc;  
    std::string errMsg;  
    std::string sql;  
    unsigned long long affected;  
    SQLStringArray fields;  
    SQLResult() 
    { 
        qc = 0; 
        affected = 0; 
    } 
    SQLResult(const unsigned short & qc, const std::string & errMsg, const std::string & sql, const unsigned long long & affected, const SQLStringArray & fields) 
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
 
 
typedef std::vector<SQLResult> SQLResultArray;  
 
struct SQLQueryReq //通用SQL语句执行协议  
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
 
struct SQLQueryResp //通用SQL语句执行协议返回,SQLResult可以借助dbHepler进行构建DBResult  
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
 
struct SQLQueryArrayReq //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 41003;} 
    static const std::string getProtoName() { return "SQLQueryArrayReq";} 
    SQLStringArray sqls;  
    SQLQueryArrayReq() 
    { 
    } 
    SQLQueryArrayReq(const SQLStringArray & sqls) 
    { 
        this->sqls = sqls; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SQLQueryArrayReq & data) 
{ 
    ws << data.sqls;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SQLQueryArrayReq & data) 
{ 
    rs >> data.sqls;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SQLQueryArrayReq & info) 
{ 
    stm << "[\n"; 
    stm << "sqls=" << info.sqls << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SQLQueryArrayResp //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 41004;} 
    static const std::string getProtoName() { return "SQLQueryArrayResp";} 
    unsigned short retCode;  
    SQLResultArray results; //批量返回,注意不要超出协议包最大长度  
    SQLQueryArrayResp() 
    { 
        retCode = 0; 
    } 
    SQLQueryArrayResp(const unsigned short & retCode, const SQLResultArray & results) 
    { 
        this->retCode = retCode; 
        this->results = results; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SQLQueryArrayResp & data) 
{ 
    ws << data.retCode;  
    ws << data.results;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SQLQueryArrayResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.results;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SQLQueryArrayResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "results=" << info.results << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 
